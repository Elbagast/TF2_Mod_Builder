#ifndef DCLIB_LITYPE_V1_STRING_TOOLS_HPP
#define DCLIB_LITYPE_V1_STRING_TOOLS_HPP

#include "fwd/string_tools.hpp"
#include <type_traits>
#include "string_class.hpp"
#include <dclib/meta/typelist.hpp>


namespace dclib
{
  namespace litype
  {
    namespace v1
    {
      namespace mf
      {
        //---------------------------------------------------------------------------
        // Metafunction to_typelist<string<>>
        //---------------------------------------------------------------------------
        template <typename T_Char, T_Char...C>
        struct to_typelist<string<T_Char,C...> >
        {
          using type = meta::typelist<std::integral_constant<T_Char,C>...>;
        };

        template <typename T>
        using to_typelist_t = typename to_typelist<T>::type;


        static_assert(std::is_same<to_typelist_t<string<char,'a','b','c'>>, meta::typelist<std::integral_constant<char,'a'>,std::integral_constant<char,'b'>,std::integral_constant<char,'c'>>>::value,"bad type converison.");

        //---------------------------------------------------------------------------
        // Metafunction from_typelist<char_type, typelist<>>
        //---------------------------------------------------------------------------
        template <typename T_Char, T_Char...C>
        struct from_typelist<T_Char,meta::typelist<std::integral_constant<T_Char,C>...> >
        {
          using type = string<T_Char,C...>;
        };

        template <typename T_Char>
        struct from_typelist<T_Char, meta::typelist<>>
        {
          using type = string<T_Char>;
        };

        template <typename C, typename T>
        using from_typelist_t = typename from_typelist<C,T>::type;


        static_assert(std::is_same<string<char,'a','b','c'>, from_typelist_t<char,meta::typelist<std::integral_constant<char,'a'>,std::integral_constant<char,'b'>,std::integral_constant<char,'c'>>>>::value,"bad type converison.");
        static_assert(std::is_same<string<char,'a','b','c'>, from_typelist_t<char,to_typelist_t<string<char,'a','b','c'>>>>::value,"bad type converison.");

        //---------------------------------------------------------------------------
        // Metafunction is_string<T>
        //---------------------------------------------------------------------------
        template <typename T>
        struct is_string : public std::false_type {};

        template <typename T_Char, T_Char... C>
        struct is_string<string<T_Char,C...>> : public std::true_type {};


        //---------------------------------------------------------------------------
        // Metafunction concatenate<T...>
        //---------------------------------------------------------------------------
        // Concatenate any number of literals of the same character type.
        template <typename T_Char, T_Char...First>
        struct concatenate<string<T_Char, First...>>
        {
          using type = string<T_Char, First...>;
        };

        template <typename T_Char, T_Char...First, T_Char...Second, typename... Args>
        struct concatenate<string<T_Char, First...>,string<T_Char, Second...>,Args...>
        {
          using type =
          typename concatenate
          <
            string<T_Char, First..., Second...>,
            Args...
          >::type;
        };

        //---------------------------------------------------------------------------
        // Metafunction pop_front<String, Count>
        //---------------------------------------------------------------------------
        // Remove Count characters from the front of the string.
        template <std::size_t N, typename T_Char, T_Char...C>
        struct pop_front<string<T_Char, C...>, N>
        {
          using type =
          typename from_typelist
          <
            T_Char,
            typename meta::mf::pop_front
            <
              typename to_typelist<string<T_Char, C...>>::type,
              N
            >::type
          >::type;
        };

        //---------------------------------------------------------------------------
        // Metafunction pop_back<String, Count>
        //---------------------------------------------------------------------------
        // Remove Count characters from the back of the string.
        template <std::size_t N, typename T_Char, T_Char...C>
        struct pop_back<string<T_Char, C...>, N>
        {
          using type =
          typename from_typelist
          <
            T_Char,
            typename meta::mf::pop_back
            <
              typename to_typelist<string<T_Char, C...>>::type,
              N
            >::type
          >::type;
        };

        //---------------------------------------------------------------------------
        // Metafunction substring<String, Position, Length>
        //---------------------------------------------------------------------------
        // Remove Count characters from the back of the string.
        // Create a substring starting at index 'Position' with length 'Length'.
        // If position is out of bounds return an empty string.
        // If there are not enough characters end the result at the end of the input string.
        template <std::size_t Position, std::size_t Length, typename T_Char, T_Char...C>
        struct substring<string<T_Char, C...>, Position, Length>
        {
          using type =
          typename from_typelist
          <
            T_Char,
            typename meta::mf::sublist
            <
              typename to_typelist<string<T_Char, C...>>::type,
              Position,
              Length
            >::type
          >::type;
        };


        //---------------------------------------------------------------------------
        // Metafunction find_first<String, Char_Type, Char>
        //---------------------------------------------------------------------------
        // Determine the index position of the first char equal to 'Target' in the string.
        template <typename T_Char, T_Char Target, T_Char...C>
        struct find_first<string<T_Char,C...>, T_Char, Target> :
            public meta::mf::find_first<typename mf::to_typelist< string<T_Char,C...> >::type, std::integral_constant<T_Char,Target>>
        {
        };

        //---------------------------------------------------------------------------
        // Metafunction reverse<String>
        //---------------------------------------------------------------------------
        // Reverse the string, i.e. "abcd" -> "dcba" etc.
        template <typename T_Char, T_Char...C>
        struct reverse<string<T_Char,C...>>
        {
          using type =
          typename from_typelist
          <
            T_Char,
            typename meta::mf::reverse
            <
              typename to_typelist
              <
                string<T_Char,C...>
              >::type
            >::type
          >::type;
        };

        //---------------------------------------------------------------------------
        // Metafunction remove<String, Index>
        //---------------------------------------------------------------------------
        // Remove the char at position 'Index'.
        // Does nothing if 'Index' is out of bounds.
        template <std::size_t Index, typename T_Char, T_Char...C>
        struct remove<string<T_Char,C...>, Index>
        {
          using type =
          typename from_typelist
          <
            T_Char,
            typename meta::mf::remove
            <
              typename to_typelist
              <
                    string<T_Char,C...>
              >::type,
              Index
            >::type
          >::type;
        };

      } // namespace mf
    } // namespace v1
  } // namespace litype
} // namespace dclib

#endif // DCLIB_LITYPE_V1_STRING_TOOLS_HPP
