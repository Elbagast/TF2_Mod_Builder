#ifndef DCLIB_LITYPE_V1_STRING_MACRO_HPP
#define DCLIB_LITYPE_V1_STRING_MACRO_HPP

#include "fwd/string_macro.hpp"
#include <type_traits>
#include <dclib/meta/power.hpp>
#include "string_class.hpp"
#include "string_tools.hpp"

#define DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER 8

namespace dclib
{
  namespace litype
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // Constant struct string_max_size
      //---------------------------------------------------------------------------
      // Object that makes the string literal buffer size available at compiletime.
      // Object that makes the string literal buffer size available at compiletime.
      struct string_max_size :
              public std::integral_constant<std::size_t, meta::mf::power_2<DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER>::value>
      {};


      // Get char type from a string literal
      template <typename T_Char, std::size_t N>
      T_Char get_char_type(T_Char const(&)[N]);

      // Get the constexpr value of a char at position N in a string literal
      template <typename T_Char, std::size_t Index, std::size_t N>
      constexpr T_Char get_char(T_Char const(&a_literal)[N]) noexcept
      {
          return a_literal[Index < N ? Index : N - 1];
      }

      // Get the raw (null terminated) size of a string literal
      template <typename T_Char, std::size_t N>
      constexpr std::size_t get_raw_size(T_Char const(&)[N]) noexcept
      {
          return N;
      }

      // Get the size of a string literal without the null terminator
      template <typename T_Char, std::size_t N>
      constexpr std::size_t get_size(T_Char const(&)[N]) noexcept
      {
          return N-1;
      }
    } // namespace v1
  } // namespace litype
} // namespace dclib


// For each index of the buffer, get the char value and wrap it in a std::integral_constant type.
// For indexes higher than the string literal size, use the null character.
#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_1(_bin_front, _char_type, _string_literal) \
    std::integral_constant<_char_type,dclib::litype::v1::get_char<_char_type,0b##_bin_front##0>(_string_literal)>

#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_2(_bin_front, _char_type, _string_literal) \
    std::integral_constant<_char_type,dclib::litype::v1::get_char<_char_type,0b##_bin_front##0>(_string_literal)>, \
    std::integral_constant<_char_type,dclib::litype::v1::get_char<_char_type,0b##_bin_front##1>(_string_literal)> \

#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_4(_bin_front, _char_type, _string_literal) \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_2(_bin_front##0, _char_type, _string_literal), \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_2(_bin_front##1, _char_type, _string_literal) \

#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_8(_bin_front, _char_type, _string_literal) \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_4(_bin_front##0, _char_type, _string_literal), \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_4(_bin_front##1, _char_type, _string_literal) \

#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_16(_bin_front, _char_type, _string_literal) \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_8(_bin_front##0, _char_type, _string_literal), \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_8(_bin_front##1, _char_type, _string_literal) \

#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_32(_bin_front, _char_type, _string_literal) \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_16(_bin_front##0, _char_type, _string_literal), \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_16(_bin_front##1, _char_type, _string_literal) \

#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_64(_bin_front, _char_type, _string_literal) \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_32(_bin_front##0, _char_type, _string_literal), \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_32(_bin_front##1, _char_type, _string_literal) \

#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_128(_bin_front, _char_type, _string_literal) \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_64(_bin_front##0, _char_type, _string_literal), \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_64(_bin_front##1, _char_type, _string_literal) \

#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_256(_bin_front, _char_type, _string_literal) \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_128(_bin_front##0, _char_type, _string_literal), \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_128(_bin_front##1, _char_type, _string_literal) \

#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_512(_bin_front, _char_type, _string_literal) \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_256(_bin_front##0, _char_type, _string_literal), \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_256(_bin_front##1, _char_type, _string_literal) \

#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_1024(_bin_front, _char_type, _string_literal) \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_512(_bin_front##0, _char_type, _string_literal), \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_512(_bin_front##1, _char_type, _string_literal) \

#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_2048(_bin_front, _char_type, _string_literal) \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_1024(_bin_front##0, _char_type, _string_literal), \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_1024(_bin_front##1, _char_type, _string_literal) \

#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_4096(_bin_front, _char_type, _string_literal) \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_2048(_bin_front##0, _char_type, _string_literal), \
    DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_2048(_bin_front##1, _char_type, _string_literal) \

// Depending on the value of the user-set macro, build the buffer, which is a list of types.

#define DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_DEFAULT(_char_type, _string_literal) DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_64(,_char_type, _string_literal)

#ifdef DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER
#if DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER == 0
#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal)  DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_1(,_char_type, _string_literal)
#elif DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER == 1
#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal)  DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_2(,_char_type, _string_literal)
#elif DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER == 2
#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal)  DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_4(,_char_type, _string_literal)
#elif DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER == 3
#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal)  DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_8(,_char_type, _string_literal)
#elif DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER == 4
#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal)  DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_16(,_char_type, _string_literal)
#elif DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER == 5
#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal)  DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_32(,_char_type, _string_literal)
#elif DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER == 6
#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal)  DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_64(,_char_type, _string_literal)
#elif DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER == 7
#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal)  DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_128(,_char_type, _string_literal)
#elif DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER == 8
#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal)  DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_256(,_char_type, _string_literal)
#elif DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER == 9
#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal)  DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_512(,_char_type, _string_literal)
#elif DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER == 10
#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal)  DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_1024(,_char_type, _string_literal)
#elif DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER == 11
#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal)  DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_2048(,_char_type, _string_literal)
#elif DCLIB_LITYPE_V1_USE_STRING_BUFFER_SIZE_POWER == 12
#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal)  DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_4096(,_char_type, _string_literal)
#endif
#else

#define DCLIB_LITYPE_V1_STRING_BUFFER(_char_type, _string_literal) DCLIB_LITYPE_V1_STRING_BUFFER_SIZE_DEFAULT(,_char_type, _string_literal)
#endif

// Turn the list of times into a typelist of the required length, then convert it into the correct String_Literal_Type
#define DCLIB_LITYPE_V1_STRING(_string_literal) \
    dclib::litype::v1::mf::from_typelist \
    < \
        decltype(dclib::litype::v1::get_char_type(_string_literal)), \
        dclib::meta::mf::sublist\
        <\
            dclib::meta::typelist< DCLIB_LITYPE_V1_STRING_BUFFER(decltype(dclib::litype::v1::get_char_type(_string_literal)), _string_literal) >, \
            0, \
            dclib::litype::v1::get_size(_string_literal) \
        >::type\
    >::type\


// Does the type work?
static_assert(std::is_same<DCLIB_LITYPE_V1_STRING(""), dclib::litype::v1::string<char>>::value, "Bad string literal type.");
static_assert(std::is_same<DCLIB_LITYPE_V1_STRING(u""), dclib::litype::v1::string<char16_t>>::value, "Bad string literal type.");
static_assert(std::is_same<DCLIB_LITYPE_V1_STRING(U""), dclib::litype::v1::string<char32_t>>::value, "Bad string literal type.");
static_assert(std::is_same<DCLIB_LITYPE_V1_STRING(L""), dclib::litype::v1::string<wchar_t>>::value, "Bad string literal type.");

// Is it empty?
static_assert(DCLIB_LITYPE_V1_STRING("")::size() == 0, "Bad empty literal type.");
static_assert(DCLIB_LITYPE_V1_STRING(u"")::size() == 0, "Bad empty literal type.");
static_assert(DCLIB_LITYPE_V1_STRING(U"")::size() == 0, "Bad empty literal type.");
static_assert(DCLIB_LITYPE_V1_STRING(L"")::size() == 0, "Bad empty literal type.");

// Does deferencing it equal the null character?
static_assert(*(DCLIB_LITYPE_V1_STRING("")::data()) == '\0', "Bad empty literal data.");
static_assert(*(DCLIB_LITYPE_V1_STRING(u"")::data()) == u'\0', "Bad empty literal data.");
static_assert(*(DCLIB_LITYPE_V1_STRING(U"")::data()) == U'\0', "Bad empty literal data.");
static_assert(*(DCLIB_LITYPE_V1_STRING(L"")::data()) == L'\0', "Bad empty literal data.");


#endif // DCLIB_LITYPE_V1_STRING_MACRO_HPP
