#ifndef DCLIB_CT_V1_TYPE_IMPL_HPP
#define DCLIB_CT_V1_TYPE_IMPL_HPP

#include "template_string_impl.hpp"

namespace dclib
{
  namespace ct
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // type_impl<T>
      //---------------------------------------------------------------------------
      // Implementation of standardised access to a static type string that was
      // supplied via a template parameter with DCLIB_LITYPE_STRING.

      template <typename T>
      class type_impl;

      template <typename C, C...Name>
      class type_impl<dclib::litype::string<C,Name...>>
      {
      private:
        using impl_type = template_string_impl<dclib::litype::string<C,Name...>>;
      public:
        using literal_type = typename impl_type::literal_type;
        using char_type = typename impl_type::char_type;
        using string_type = typename impl_type::string_type;

        static string_type make_type()
        {
          return impl_type::make_string();
        }

        static string_type const& type()
        {
          return impl_type::get_string();
        }
      };

    } // namespace v1
  } // namespace ct
} // namespace dclib

#endif // DCLIB_CT_V1_TYPE_IMPL_HPP
