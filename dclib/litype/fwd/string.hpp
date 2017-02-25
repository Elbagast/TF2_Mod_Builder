#ifndef STRING_HPP
#define STRING_HPP


#include <dclib/litype/v1/fwd/string_class.hpp>
#include <dclib/litype/v1/fwd/string_tools.hpp>
#include <dclib/litype/v1/fwd/string_macro.hpp>

namespace dclib
{
  namespace litype
  {
    //---------------------------------------------------------------------------
    // string<Char, Char...>
    //---------------------------------------------------------------------------
    // Class that wraps a string literal making it useable as a template parameter.
    template <typename T_Char, T_Char... C>
    using string = v1::string<T_Char, C...>;

    //---------------------------------------------------------------------------
    // Constant struct string_max_size
    //---------------------------------------------------------------------------
    // Object that makes the string literal buffer size available at compiletime.
    using string_max_size = v1::string_max_size;

    namespace mf
    {
      //---------------------------------------------------------------------------
      // Metafunction to_typelist<String_Literal_Type<>>
      //---------------------------------------------------------------------------
      template <typename T>
      using to_typelist = v1::mf::to_typelist<T>;

      //---------------------------------------------------------------------------
      // Metafunction from_typelist<typelist<>>
      //---------------------------------------------------------------------------
      template <typename T1, typename T2>
      using from_typelist = v1::mf::from_typelist<T1, T2>;

      //---------------------------------------------------------------------------
      // Metafunction is_string<T>
      //---------------------------------------------------------------------------
      template <typename T>
      using is_string = v1::mf::is_string<T>;

      //---------------------------------------------------------------------------
      // Metafunction concatenate<T...>
      //---------------------------------------------------------------------------
      // Concatenate any number of literals of the same character type.
      template <typename...T>
      using concatenate = v1::mf::concatenate<T...>;

      //---------------------------------------------------------------------------
      // Metafunction pop_front<String, Count>
      //---------------------------------------------------------------------------
      // Remove Count characters from the front of the string.
      template <typename T_String, std::size_t Count = 1>
      using pop_front = v1::mf::pop_front<T_String,Count>;

      //---------------------------------------------------------------------------
      // Metafunction pop_back<String, Count>
      //---------------------------------------------------------------------------
      // Remove Count characters from the back of the string.
      template <typename T_String, std::size_t Count = 1>
      using pop_back = v1::mf::pop_back<T_String,Count>;

      //---------------------------------------------------------------------------
      // Metafunction substring<String, Position, Length>
      //---------------------------------------------------------------------------
      // Remove Count characters from the back of the string.
      // Create a substring starting at index 'Position' with length 'Length'.
      // If position is out of bounds return an empty string.
      // If there are not enough characters end the result at the end of the input string.
      template <typename T_String, std::size_t Position, std::size_t Length>
      using substring = v1::mf::substring<T_String,Position,Length>;

      //---------------------------------------------------------------------------
      // Metafunction find_first<String, Char_Type, Char>
      //---------------------------------------------------------------------------
      // Determine the index position of the first char equal to 'Target' in the string.
      template <typename T_String, typename T_Char, T_Char Target>
      using find_first = v1::mf::find_first<T_String,T_Char,Target>;

      //---------------------------------------------------------------------------
      // Metafunction reverse<String>
      //---------------------------------------------------------------------------
      // Reverse the string, i.e. "abcd" -> "dcba" etc.
      template <typename T_String>
      using reverse = v1::mf::reverse<T_String>;

      //---------------------------------------------------------------------------
      // Metafunction remove<String, Index>
      //---------------------------------------------------------------------------
      // Remove the char at position 'Index'.
      // Does nothing if 'Index' is out of bounds.
      template <typename T_String, std::size_t Index>
      using remove = v1::mf::remove<T_String,Index>;
    } // namespace mf

  } // namespace litype
} // namespace opliteral

#endif // STRING_HPP
