#ifndef DCLIB_RT_V1_MEMBER_HPP
#define DCLIB_RT_V1_MEMBER_HPP

#include <dclib/rt/v1/fwd/member.hpp>
#include <dclib/litype/string.hpp>
#include <dclib/meta/typelist.hpp>

#include <dclib/ct/v1/member.hpp>
#include <type_traits>
#include <string>
#include <typeinfo>

namespace dclib
{
  namespace rt
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // abstract::member
      //---------------------------------------------------------------------------
      // Abstract class that describes the runtime interface of members.
      namespace abstract
      {
        template <typename C>
        class member
        {
        public:
          using char_type = C;
          using name_string_type = std::basic_string<C>;

          virtual ~member() = default;

          virtual name_string_type const& name() const = 0;
          virtual std::type_info const& type() const = 0;
          virtual bool is_type(std::type_info const& a_type) const = 0;
        };

        template <typename C, typename T>
        bool member_is(member<C> const* a_member)
        {
          return typeid(T).hash_code() == a_member->type().hash_code();
        }

        template <typename C, typename T>
        class member_type :
            public member<C>
        {
          using inherited_type = member<C>;
        public:
          using char_type = typename inherited_type::char_type;
          using name_string_type = typename inherited_type::name_string_type;

          using value_type = T;

          ~member_type() override = default;

          name_string_type const& name() const override = 0;
          std::type_info const& type() const override = 0;
          bool is_type(std::type_info const& a_type) const override = 0;

          virtual value_type& get() = 0;
          virtual value_type const& cget() const = 0;
        };

      }

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
      class member<dclib::litype::string<C,Name...>,T> :
          public abstract::member_type<C,T>

      {
      private:
        using inherited_type = abstract::member_type<C,T>;

        using ct_member_type = ct::v1::member<dclib::litype::string<C,Name...>,T>;

        ct_member_type m_data;

      public:
        using name_literal_type = typename ct_member_type::name_literal_type;
        using name_char_type = typename ct_member_type::name_char_type;
        using name_string_type = typename ct_member_type::name_string_type;

        using value_type = typename ct_member_type::value_type;

        member():
          inherited_type(),
          m_data{}
        {
        }
        explicit member(value_type const& a_value):
          inherited_type(),
          m_data{a_value}
        {
        }
        explicit member(value_type && a_value):
          inherited_type(),
          m_data{std::move(a_value)}
        {
        }
        ~member() override = default;

        member(member const& a_other) = default;
        member& operator=(member const& a_other) = default;

        member(member && a_other) = default;
        member& operator=(member && a_other) = default;

        name_string_type const& name() const override final
        {
          return ct_member_type::name();
        }

        std::type_info const& type() const override final
        {
          return typeid(T);
        }

        bool is_type(std::type_info const& a_type) const override final
        {
          return a_type.hash_code() == typeid(T).hash_code();
        }

        value_type& get() override final
        {
          return m_data.get();
        }
        value_type const& cget() const override final
        {
          return m_data.cget();
        }
      };


      template <typename C, typename T>
      decltype(auto) member_cast(abstract::member<C>* a_member)
      {
        return dynamic_cast<member<C,T>*>(a_member);
      }

      template <typename C, typename T>
      decltype(auto) member_cast(abstract::member<C> const* a_member)
      {
        return dynamic_cast<member<C,T>const*>(a_member);
      }



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
  } // namespace rt
} // namespace dclib

#endif // DCLIB_RT_V1_MEMBER_HPP
