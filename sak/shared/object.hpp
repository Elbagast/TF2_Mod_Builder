#ifndef SAK_SHARED_OBJECT_HPP
#define SAK_SHARED_OBJECT_HPP

#include "fwd/object.hpp"
#include <flamingo/data_class.hpp>
#include <flamingo/litype/string.hpp>

#include <boost/variant.hpp>

#include <string>
#include <QString>

namespace sak
{

  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::template_string_impl
    //---------------------------------------------------------------------------
    // Part of shared::object's implementation.

    template <typename T>
    class template_string_impl;

    template <typename C, C...Name>
    class template_string_impl<flamingo::litype::string<C,Name...>>
    {
    public:
      using literal_type = flamingo::litype::string<C,Name...>;
      using char_type = C;
      using string_type = std::basic_string<C>;

      static string_type make_string()
      {
        return string_type(literal_type::cbegin(),literal_type::cend() );
      }

      static string_type const& get_string()
      {
        static string_type const s_name{make_string()};
        return s_name;
      }
    };

    //---------------------------------------------------------------------------
    // shared::type_impl
    //---------------------------------------------------------------------------
    // Part of shared::object's implementation.

    template <typename T>
    class type_impl;

    template <typename C, C...Name>
    class type_impl<flamingo::litype::string<C,Name...>>
    {
    private:
      using impl_type = template_string_impl<flamingo::litype::string<C,Name...>>;
    public:
      using type_literal_type = typename impl_type::literal_type;
      using type_char_type = typename impl_type::char_type;
      using type_string_type = typename impl_type::string_type;

      static type_string_type const& type()
      {
        return impl_type::get_string();
      }
    };

    //---------------------------------------------------------------------------
    // shared::typelist_to_variant
    //---------------------------------------------------------------------------
    // Part of shared::object's implementation.

    template <typename List>
    struct typelist_to_variant;

    template <typename... Args>
    struct typelist_to_variant<flamingo::typelist<Args...>>
    {
      using type = boost::variant<Args...>;
    };

    template <typename List>
    using typelist_to_variant_t = typename typelist_to_variant<List>::type;

    //---------------------------------------------------------------------------
    // shared::data_class
    //---------------------------------------------------------------------------
    // Since flamingo::data_class doesn't have everything we need we make ourselves an object
    // that extends it to - the typename embedded into the class and also member_value_variant.

    template <typename S_Type, typename...T_Members>
    class data_class :
        public shared::type_impl<S_Type>,
        public flamingo::data_class<T_Members...>
    {
    public:
      using member_value_variant = typelist_to_variant_t<flamingo::typelist_remove_duplicates_t<typename flamingo::data_class<T_Members...>::member_value_typelist>>;
    };

    namespace mf
    {
      template <typename T, std::size_t I>
      struct object_member_type
      {
        //using type = typename T::member_type<N>;
        using type = flamingo::typelist_type_at_t<typename T::member_typelist, I>;
      };

      template <typename T, std::size_t I>
      using object_member_t = typename object_member_type<T,I>::type;

    }

  }

  namespace file
  {
    //---------------------------------------------------------------------------
    // file::object
    //---------------------------------------------------------------------------
    // So it turns out we need to inherit this type to hide the huuuuuge name that
    // comes from having strings in the type.
    class object :
        public shared::data_class
    <
    FLAMINGO_LITYPE_STRING(u8"File")
    ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Name")>
    ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Description")>
    ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Buildpath")>
    ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Sourcepath")>
    ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Booltest")>
    ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"std_stringtest")>
    >
    {};
  }

  namespace texture
  {
    //---------------------------------------------------------------------------
    // texture::object
    //---------------------------------------------------------------------------
    // So it turns out we need to inherit this type to hide the huuuuuge name that
    // comes from having strings in the type.
    class object :
        public shared::data_class
    <
    FLAMINGO_LITYPE_STRING(u8"Texture")
    ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Name")>
    ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Description")>
    ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Buildpath")>
    ,flamingo::data_member<QString, FLAMINGO_LITYPE_STRING(u8"Sourcepath")>
    >
    {};
  }
}

#endif // SAK_SHARED_OBJECT_HPP
