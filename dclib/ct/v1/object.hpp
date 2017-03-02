#ifndef DCLIB_CT_V1_OBJECT_HPP
#define DCLIB_CT_V1_OBJECT_HPP

#include <dclib/ct/v1/fwd/object.hpp>
#include <dclib/ct/v1/member.hpp>
#include <dclib/litype/string.hpp>
#include <dclib/meta/typelist.hpp>
#include "type_impl.hpp"
#include <tuple>

#include <boost/variant.hpp>

namespace dclib
{
  namespace ct
  {
    namespace v1
    {
      template <typename List>
      struct typelist_to_variant;

      template <typename... Args>
      struct typelist_to_variant<meta::typelist<Args...>>
      {
        using type = boost::variant<Args...>;
      };

      template <typename List>
      using typelist_to_variant_t = typename typelist_to_variant<List>::type;

      //---------------------------------------------------------------------------
      // object<T1, Args...>
      //---------------------------------------------------------------------------
      // Data class object. Acceptable template instantiations:
      //
      // A Data type with members.
      // class object<litype::string<...>, members<...>...>
      //

      template <typename C, C...Name, typename...T1, typename...T2>
      class object<dclib::litype::string<C,Name...>,member<T1,T2>...>
      {
      private:
        using type_impl_type = type_impl<dclib::litype::string<C,Name...>>;
      public:
        using type_literal_type = typename type_impl_type::literal_type;
        using type_char_type = typename type_impl_type::char_type;
        using type_string_type = typename type_impl_type::string_type;

        using member_typelist = meta::typelist<member<T1,T2>...>;
        using member_name_typelist = meta::typelist<typename member<T1,T2>::name_literal_type...>;
        using member_value_typelist = meta::typelist<typename member<T1,T2>::value_type...>;

        using member_value_variant = typelist_to_variant_t<meta::mf::remove_duplicates_t<member_value_typelist>>;

        template <std::size_t Index>
        using member_type = meta::mf::type_at_t<member_typelist, Index>;

        using member_tuple = std::tuple<member<T1,T2>...>;
        using value_tuple = std::tuple<typename member<T1,T2>::value_type...>;

        object():
          m_data{}
        {}
        explicit object(value_tuple const& a_member_values):
            m_data{ std::move(repackage_values(a_member_values)) }
        {}

        // Get the type string for this object.
        static type_string_type const& type()
        {
          return type_impl_type::type();
        }

        // How many members does this object have?
        static constexpr std::size_t size()
        {
          return meta::mf::size<member_typelist>::value;
        }

        // Compile-time meber access by index.
        template <std::size_t I>
        member_type<I>& at()
        {
            static_assert(I < meta::mf::size<member_typelist>::value,
                          "No member with that index.");
            return std::get<I>(m_data);
        }

        template <std::size_t I>
        member_type<I> const& cat() const
        {
            static_assert(I < meta::mf::size<member_typelist>::value,
                          "No member with that index.");
            return std::get<I>(m_data);
        }

        // Compile-time meber access by name string literal.
        template <typename S>
        decltype(auto) get()
        {
            static_assert(meta::mf::find_first<member_name_typelist,S>::value < meta::mf::size<member_name_typelist>::value,
                          "No member with that name found.");
            return at<meta::mf::find_first<member_name_typelist,S>::value>();
        }

        template <typename S>
        decltype(auto) cget() const
        {
          static_assert(meta::mf::find_first<member_name_typelist,S>::value < meta::mf::size<member_name_typelist>::value,
                        "No member with that name found.");
          return cat<meta::mf::find_first<member_name_typelist,S>::value>();
        }

      private:
        member_tuple m_data;

        // Must convert the supplied data values into a tuple of members (only the values have state) so
        // the data_type can construct with them. We do this by making a tuple of the true member types
        // then calling set_value on each of them with the supplied value.
        template <std::size_t Index = 0, std::size_t End = size()>
        struct Repackage_Values
        {
            void operator()(member_tuple& a_target, value_tuple const& a_values)
            {
                std::get<Index>(a_target).get() = (std::get<Index>(a_values));
                Repackage_Values<Index+1,End>()(a_target, a_values);
            }
        };

        template <std::size_t End>
        struct Repackage_Values<End,End>
        {
            void operator()(member_tuple& , value_tuple const& )
            {
            }
        };

        static member_tuple repackage_values(value_tuple const& a_values)
        {
            member_tuple l_result{};
            Repackage_Values<0u>()(l_result, a_values);
            return l_result;
        }

      };

      namespace mf
      {
        //---------------------------------------------------------------------------
        // Metafunction is_object<T>
        //---------------------------------------------------------------------------
        // Identify whether or not a type is an object.
        template <typename T>
        struct is_object : public std::false_type {};

        template <typename T, typename... Args>
        struct is_object<object<T,Args...>> : public std::true_type {};

        //---------------------------------------------------------------------------
        // Metafunction object_member<T,I>
        //---------------------------------------------------------------------------
        // For a given object type retrieve the member type at the supplied index.
        template <typename T, std::size_t I>
        struct object_member
        {
          using type = meta::mf::type_at_t<typename T::member_typelist, I>;
        };

        template <std::size_t I, typename T, typename...Ms >
        struct object_member<object<T,Ms...>,I>
        {
          using type = meta::mf::type_at_t<typename object<T,Ms...>::member_typelist, I>;
        };

        template <typename T, std::size_t I>
        using object_member_t = typename object_member<T,I>::type;


      } // namespace mf

    } // namespace v1
  } // namespace ct
} // namespace dclib


#endif // DCLIB_CT_V1_OBJECT_HPP
