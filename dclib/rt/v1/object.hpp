#ifndef DCLIB_RT_V1_OBJECT_HPP
#define DCLIB_RT_V1_OBJECT_HPP

#include <dclib/rt/v1/fwd/object.hpp>
#include <dclib/rt/v1/member.hpp>
#include <dclib/ct/v1/type_impl.hpp>
#include <dclib/litype/string.hpp>
#include <dclib/meta/typelist.hpp>
#include "polymorhpic_tuple.hpp"

namespace dclib
{
  namespace rt
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // abstract::object
      //---------------------------------------------------------------------------
      // Abstract class that describes the runtime interface of objects.
      namespace abstract
      {
        template <typename C>
        class object
        {
        public:
          using abstract_member_type = member<C>;

          using char_type = C;
          using string_type = std::basic_string<C>;

          virtual ~object() = default;

          virtual string_type const& type() const = 0;

          virtual std::size_t size() const = 0;

          virtual abstract_member_type& at(std::size_t a_index) = 0;
          virtual abstract_member_type const& cat(std::size_t a_index) const = 0;

          virtual abstract_member_type& get(string_type const& a_name) = 0;
          virtual abstract_member_type const& cget(string_type const& a_name) const = 0;
        };
      }

      //---------------------------------------------------------------------------
      // object<T1, Args...>
      //---------------------------------------------------------------------------
      // Data class object. Acceptable template instantiations:
      //
      // A Data type with members.
      // class object<litype::string<...>, members<...>...>
      //

      template <typename C, C...Name, typename...T1, typename...T2>
      class object<dclib::litype::string<C,Name...>,member<T1,T2>...>:
          public abstract::object<C>
      {
      private:
        using inherited_type = abstract::object<C>;
        using type_impl_type = ct::v1::type_impl<dclib::litype::string<C,Name...>>;

        using member_tuple = polymorphic_tuple<abstract::member<C>,member<T1,T2>...>;

      public:
        using type_literal_type = typename type_impl_type::literal_type;
        using type_char_type = typename type_impl_type::char_type;
        using type_string_type = typename type_impl_type::string_type;

        using member_typelist = meta::typelist<member<T1,T2>...>;
        using member_name_typelist = meta::typelist<typename member<T1,T2>::name_literal_type...>;
        using member_value_typelist = meta::typelist<typename member<T1,T2>::value_type...>;

        template <std::size_t Index>
        using member_type = meta::mf::type_at_t<member_typelist, Index>;

        using abstract_member_type = typename inherited_type::abstract_member_type;

        //using member_tuple = typename ct_object_type::member_tuple;
        using value_tuple = std::tuple<typename member<T1,T2>::value_type...>;

        object():
          inherited_type(),
          m_data{}
        {}
        explicit object(value_tuple const& a_member_values):
          inherited_type(),
          m_data{ a_member_values }
        {}
        ~object() override = default;

        // Get the type string for this object.
        type_string_type const& type() const override final
        {
          return type_impl_type::type();
        }

        // How many members does this object have?
        std::size_t size() const override final
        {
          return m_data.size();
        }

        abstract_member_type& at(std::size_t a_index) override final
        {
          return m_data.get_base_at(a_index);
        }

        abstract_member_type const& cat(std::size_t a_index) const override final
        {
          return m_data.cget_base_at(a_index);
        }

        abstract_member_type& get(string_type const& a_name) override final
        {
          for (std::size_t l_index = 0, l_end = m_data.size(); l_index != l_end; ++l_index)
          {
            auto& l_member = m_data.get_base_at(l_index);
            if (l_member.name() == a_name)
            {
              return l_member;
            }
          }
          throw std::range_error("No member has that name.");
        }

        abstract_member_type const& cget(string_type const& a_name) const override final
        {
          for (std::size_t l_index = 0, l_end = m_data.size(); l_index != l_end; ++l_index)
          {
            auto const& l_member = m_data.cget_base_at(l_index);
            if (l_member.name() == a_name)
            {
              return l_member;
            }
          }
          throw std::range_error("No member has that name.");
        }

        // Compile-time member access by index.
        template <std::size_t I>
        member_type<I>& at()
        {
          return m_data.get_derived_at<I>();
        }

        template <std::size_t I>
        member_type<I> const& cat() const
        {
          return m_data.cget_derived_at<I>();
        }

        // Compile-time meber access by name string literal.
        template <typename S>
        decltype(auto) get()
        {
          static_assert(meta::mf::find_first<member_name_typelist,S>::value < meta::mf::size<member_name_typelist>::value,
                        "No member with that name found.");
          return m_data.get_derived_at<meta::mf::find_first<member_name_typelist, S>::value>();
        }

        template <typename S>
        decltype(auto) cget() const
        {
          static_assert(meta::mf::find_first<member_name_typelist,S>::value < meta::mf::size<member_name_typelist>::value,
                        "No member with that name found.");
          return m_data.cget_derived_at<meta::mf::find_first<member_name_typelist, S>::value>();
        }

      private:
        member_tuple m_data;
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

      } // namespace mf

    } // namespace v1
  } // namespace rt
} // namespace dclib


#endif // DCLIB_RT_V1_OBJECT_HPP
