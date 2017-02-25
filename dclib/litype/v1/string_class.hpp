#ifndef DCLIB_LITYPE_V1_STRING_CLASS_HPP
#define DCLIB_LITYPE_V1_STRING_CLASS_HPP

#include "fwd/string_class.hpp"
#include <cstddef>

namespace dclib
{
  namespace litype
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // String_Literal_Type<Char, Char...>
      //---------------------------------------------------------------------------
      template <typename T_Char, T_Char... C>
      class string
      {
      private:
        static constexpr std::size_t const s_size = { sizeof...(C) };
        static constexpr T_Char const s_data[sizeof...(C)+1] = { C...,'\0' };
      public:
        using char_type = T_Char;

        // Return the null terminated string at compile or runtime.
        static constexpr char_type const * data() noexcept
        {
          return &(s_data[0]);
        }

        // Return the size of the string at compile or runtime.
        static constexpr std::size_t size() noexcept
        {
          return s_size;
        }

        // Return the begining of the string at compile or runtime.
        static constexpr char_type const * begin() noexcept
        {
          return &(s_data[0]);
        }

        // Return the end of the string at compile or runtime.
        static constexpr char_type const * end() noexcept
        {
          return &(s_data[s_size]);
        }

        // Manual const specifier of begin(), unfortunately not called by the ranged for loop.
        static constexpr char_type const * cbegin() noexcept
        {
          return &(s_data[0]);
        }

        // Manual const specifier of end(), unfortunately not called by the ranged for loop.
        static constexpr char_type const * cend() noexcept
        {
          return &(s_data[s_size]);
        }
      };
    } // namespace v1
  } // namespace litype
} // namespace dclib


template <typename T_Char, T_Char... C>
constexpr std::size_t const dclib::litype::v1::string<T_Char,C...>::s_size;
template <typename T_Char, T_Char... C>
constexpr T_Char const dclib::litype::v1::string<T_Char,C...>::s_data[sizeof...(C)+1];

#endif // DCLIB_LITYPE_V1_STRING_CLASS_HPP
