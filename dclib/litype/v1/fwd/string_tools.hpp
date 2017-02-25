#ifndef DCLIB_LITYPE_V1_FWD_STRING_TOOLS_HPP
#define DCLIB_LITYPE_V1_FWD_STRING_TOOLS_HPP

#include <cstddef>

namespace dclib
{
  namespace litype
  {
    namespace v1
    {
      namespace mf
      {
        //---------------------------------------------------------------------------
        // Metafunction to_typelist<String_Literal_Type<>>
        //---------------------------------------------------------------------------
        template <typename>
        struct to_typelist;

        //---------------------------------------------------------------------------
        // Metafunction from_typelist<typelist<>>
        //---------------------------------------------------------------------------
        template <typename,typename>
        struct from_typelist;

        //---------------------------------------------------------------------------
        // Metafunction is_string<T>
        //---------------------------------------------------------------------------
        template <typename T>
        struct is_string;

        //---------------------------------------------------------------------------
        // Metafunction concatenate<T...>
        //---------------------------------------------------------------------------
        // Concatenate any number of literals of the same character type.
        template <typename...T_Strings>
        struct concatenate;

        //---------------------------------------------------------------------------
        // Metafunction pop_front<String, Count>
        //---------------------------------------------------------------------------
        // Remove Count characters from the front of the string.
        template <typename T_String, std::size_t Count = 1>
        struct pop_front;

        //---------------------------------------------------------------------------
        // Metafunction pop_front<String, Count>
        //---------------------------------------------------------------------------
        // Remove Count characters from the back of the string.
        template <typename T_String, std::size_t Count = 1>
        struct pop_back;

        //---------------------------------------------------------------------------
        // Metafunction substring<String, Position, Length>
        //---------------------------------------------------------------------------
        // Remove Count characters from the back of the string.
        // Create a substring starting at index 'Position' with length 'Length'.
        // If position is out of bounds return an empty string.
        // If there are not enough characters end the result at the end of the input string.
        template <typename T_String, std::size_t Position, std::size_t Length>
        struct substring;

        //---------------------------------------------------------------------------
        // Metafunction find_first<String, Char_Type, Char>
        //---------------------------------------------------------------------------
        // Determine the index position of the first char equal to 'Target' in the string.
        template <typename T_String, typename T_Char, T_Char Target>
        struct find_first;

        //---------------------------------------------------------------------------
        // Metafunction reverse<String>
        //---------------------------------------------------------------------------
        // Reverse the string, i.e. "abcd" -> "dcba" etc.
        template <typename T_String>
        struct reverse;

        //---------------------------------------------------------------------------
        // Metafunction remove<String, Index>
        //---------------------------------------------------------------------------
        // Remove the char at position 'Index'.
        // Does nothing if 'Index' is out of bounds.
        template <typename T_String, std::size_t Index>
        struct remove;
      } // namespace mf
    } // namespace v1
  } // namespace litype
} // namespace dclib

#endif // DCLIB_LITYPE_V1_FWD_STRING_TOOLS_HPP
