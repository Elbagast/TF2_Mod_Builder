#ifndef DCLIB_CT_V1_MEMBER_HPP
#define DCLIB_CT_V1_MEMBER_HPP

#include <dclib/ct/v1/fwd/member.hpp>
#include <dclib/litype/string.hpp>
#include <dclib/meta/typelist.hpp>
#include "name_impl.hpp"
#include "value_impl.hpp"
#include <type_traits>

namespace dclib
{
  namespace ct
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // member<Name, T>
      //---------------------------------------------------------------------------
      // Data class member. Associates a type with a compile-time fixeed name.
      // Acceptable template instantiations:
      //
      // class member<litype::string<...>, T>
      //
      // Member does not link to any capacity for a typestring because the user may
      // be using this to hold a type that is not truely a given type, but an
      // abstraction to one e.g. a handle.

      template <typename T, typename C, C...Name>
      class member<dclib::litype::string<C,Name...>,T>

      {
      private:
        using name_impl_type = name_impl<dclib::litype::string<C,Name...>>;
        using value_impl_type = value_impl<T>;

        value_impl_type m_value;

      public:
        using name_literal_type = typename name_impl_type::literal_type;
        using name_char_type = typename name_impl_type::char_type;
        using name_string_type = typename name_impl_type::string_type;

        using value_type = typename value_impl_type::value_type;

        member():
          m_value{}
        {
        }
        explicit member(value_type const& a_value):
          m_value{a_value}
        {
        }
        explicit member(value_type && a_value):
          m_value{std::move(a_value)}
        {
        }
        ~member() = default;

        member(member const& a_other) = default;
        member& operator=(member const& a_other) = default;

        member(member && a_other) = default;
        member& operator=(member && a_other) = default;

        static name_string_type const& name()
        {
          return name_impl_type::name();
        }
        value_type& get()
        {
          return m_value.get();
        }
        value_type const& cget() const
        {
          return m_value.cget();
        }
      };

      namespace mf
      {
        //---------------------------------------------------------------------------
        // Metafunction is_member<T>
        //---------------------------------------------------------------------------
        // Identify whether or not a type is a member.
        template <typename T>
        struct is_member : public std::false_type {};

        template <typename T1, typename T2>
        struct is_member<member<T1,T2>> : public std::true_type {};

        //---------------------------------------------------------------------------
        // Metafunction all_member<T>
        //---------------------------------------------------------------------------
        // Identify whether a typelist contains lonly member types.
        template <typename T, typename...Args>
        struct all_member<meta::typelist<T,Args...>> : public std::conditional< is_member<T>::value, all_member<meta::typelist<Args...>>, std::false_type>::type {};

        template <typename T>
        struct all_member<meta::typelist<T>> : public is_member<T> {};

        template <>
        struct all_member<meta::typelist<>> : public std::false_type {};


      } // namespace mf

    } // namespace v1
  } // namespace ct
} // namespace dclib

#endif // DCLIB_CT_V1_MEMBER_HPP
