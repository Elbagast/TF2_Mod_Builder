#ifndef DCLIB_CT_V1_TEMPLATE_STRING_IMPL_HPP
#define DCLIB_CT_V1_TEMPLATE_STRING_IMPL_HPP

#include <dclib/litype/string.hpp>
#include <string>

namespace dclib
{
  namespace ct
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // template_string<T>
      //---------------------------------------------------------------------------
      // Implementation of standardised access to a static string that was supplied
      // via a template parameter with DCLIB_LITYPE_STRING.

      template <typename T>
      class template_string_impl;

      template <typename C, C...Name>
      class template_string_impl<dclib::litype::string<C,Name...>>
      {
      public:
        using literal_type = dclib::litype::string<C,Name...>;
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

    } // namespace v1
  } // namespace ct
} // namespace dclib

#endif // DCLIB_CT_V1_TEMPLATE_STRING_IMPL_HPP
