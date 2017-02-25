#ifndef DCLIB_CT_V1_NAME_IMPL_HPP
#define DCLIB_CT_V1_NAME_IMPL_HPP

#include "template_string_impl.hpp"

namespace dclib
{
  namespace ct
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // name_impl<T>
      //---------------------------------------------------------------------------
      // Implementation of standardised access to a static name that was supplied
      // via a template parameter with DCLIB_LITYPE_STRING.

      template <typename T>
      class name_impl;

      template <typename C, C...Name>
      class name_impl<dclib::litype::string<C,Name...>>
      {
      private:
        using impl_type = template_string_impl<dclib::litype::string<C,Name...>>;
      public:
        using literal_type = typename impl_type::literal_type;
        using char_type = typename impl_type::char_type;
        using string_type = typename impl_type::string_type;

        static string_type make_name()
        {
          return impl_type::make_string();
        }

        static string_type const& name()
        {
          return impl_type::get_string();
        }
      };

    } // namespace v1
  } // namespace ct
} // namespace dclib

#endif // DCLIB_CT_V1_NAME_IMPL_HPP
