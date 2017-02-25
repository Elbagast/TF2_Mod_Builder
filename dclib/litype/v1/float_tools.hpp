#ifndef FLOAT_TOOLS_HPP
#define FLOAT_TOOLS_HPP

#include "fwd/float_class.hpp"
#include <dclib/litype/v1/string_class.hpp>
#include <dclib/litype/v1/string_tools.hpp>
#include <dclib/meta/power.hpp>
#include <type_traits>
#include <cmath>

namespace dclib
{
  namespace litype
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // floating_point<T, Mantissa, Exponent, Sign>
      //---------------------------------------------------------------------------
      // Class that wraps a float literal making it useable as a template parameter
      // type.


      // Using the supplied integer values, generate the given floating point type.
      //float make_float(float_mantissa_type a_mantissa, float_exponent_type a_exponent, float_sign_type a_sign);
      //double make_double(float_mantissa_type a_mantissa, float_exponent_type a_exponent, float_sign_type a_sign);
      //long double make_long_double(float_mantissa_type a_mantissa, float_exponent_type a_exponent, float_sign_type a_sign);

      template <typename T>
      T make_float_type(float_mantissa_type a_mantissa, float_exponent_type a_exponent, float_sign_type a_sign)
      {
        static_assert(std::is_floating_point<T>::value, "Can't use this function to make a non floating point type.");
        T l_result{ static_cast<T>(a_mantissa) };
        l_result *= std::pow(static_cast<T>(10),static_cast<T>(a_exponent));
        l_result = std::copysign(l_result, static_cast<T>(0 - a_sign));
        return l_result;
      }

      // For an input string that is assumed to be a number, extract the sign and
      // unsigned number string.

      // To reduce repetitive declarations, the values are extracted into these types
      // which are inherited. Also this is being declared as a template so that this
      // library can become header only.
      template <bool V>
      struct Sign_Bit_Values
      {
        static constexpr bool const bool_value = { V };
        static constexpr int const int_value = { V ? -1 : 1 };
      };

      using Positive_Number_Sign = Sign_Bit_Values<false>;
      using Negative_Number_Sign = Sign_Bit_Values<true>;

      template <typename>
      struct Sign_Of_Number_String;

      template <char A,char... C>
      struct Sign_Of_Number_String<string<char,A,C...>> :
          public Positive_Number_Sign
      {
        using unsigned_string_type = string<char,A,C...>;
      };

      template <char... C>
      struct Sign_Of_Number_String<string<char,'+',C...>> :
          public Positive_Number_Sign
      {
         using unsigned_string_type = string<char,C...>;
      };

      template <char... C>
      struct Sign_Of_Number_String<string<char,'-',C...>> :
          public Negative_Number_Sign
      {
        using unsigned_string_type = string<char,C...>;
      };

      template <>
      struct Sign_Of_Number_String<string<char>> :
          public Positive_Number_Sign
      {
        using unsigned_string_type = string<char>;
      };

      // Template for static_assert in the next metafunction.
      template <char C>
      struct Is_Digit_Char : public std::false_type {};

      template <> struct Is_Digit_Char<'0'> : public std::true_type {};
      template <> struct Is_Digit_Char<'1'> : public std::true_type {};
      template <> struct Is_Digit_Char<'2'> : public std::true_type {};
      template <> struct Is_Digit_Char<'3'> : public std::true_type {};
      template <> struct Is_Digit_Char<'4'> : public std::true_type {};
      template <> struct Is_Digit_Char<'5'> : public std::true_type {};
      template <> struct Is_Digit_Char<'6'> : public std::true_type {};
      template <> struct Is_Digit_Char<'7'> : public std::true_type {};
      template <> struct Is_Digit_Char<'8'> : public std::true_type {};
      template <> struct Is_Digit_Char<'9'> : public std::true_type {};


      // Turn a char into the supplied integer number type.
      template <typename I, char C>
      struct Digit_To_Int_Type
      {
          static_assert(Is_Digit_Char<C>::value, "Cannot convert the templated character into a digit.");
          static constexpr I const value = { C - '0' };
      };

      // Turn a char into the supplied integer number type x10 to the power supplied
      template <typename T_Int, char C, std::size_t T_Power>
      struct Digit_N10_To_Int_Type
      {
          static constexpr T_Int const value = { Digit_To_Int_Type<T_Int,C>::value * meta::mf::power<T_Int,10,T_Power>::value  };
      };



      // Take a tuple of constant letters, then convert them to digits as accumulating
      template <typename, std::size_t, typename>
      struct Accumulate_Digits;

      template <typename T_Int, std::size_t N, char A, char...C>
      struct Accumulate_Digits
      <
          T_Int,
          N,
          meta::typelist
          <
              std::integral_constant<char,A>,
              std::integral_constant<char,C>...
          >
      >
      {
          static constexpr T_Int const value =
          {
              Digit_To_Int_Type
              <
                  T_Int,
                  A
              >::value
              *
              meta::mf::power<T_Int,10,N>::value
              +
              Accumulate_Digits
              <
                  T_Int,
                  N+1,
                  meta::typelist<std::integral_constant<char,C>...>
              >::value
          };
      };

      template <typename T_Int, std::size_t N, char A, char...C>
      constexpr T_Int const Accumulate_Digits<T_Int,N, meta::typelist<std::integral_constant<char,A>,std::integral_constant<char,C>...>>::value;

      template <typename T_Int, std::size_t N, char A>
      struct Accumulate_Digits
      <
          T_Int,
          N,
          meta::typelist
          <
              std::integral_constant<char,A>
          >
      >
      {
          static constexpr T_Int const value =
          {
              Digit_To_Int_Type
              <
                  T_Int,
                  A
              >::value
              *
              meta::mf::power<T_Int,10,N>::value
          };
      };

      template <typename T_Int, std::size_t N, char A>
      constexpr T_Int const Accumulate_Digits<T_Int,N, meta::typelist<std::integral_constant<char,A>>>::value;

      template <typename T_Int, std::size_t N>
      struct Accumulate_Digits<T_Int, N, meta::typelist<>>
      {
          static constexpr T_Int const value = { 0 };
      };

      template <typename T_Int, std::size_t N>
      constexpr T_Int const Accumulate_Digits<T_Int,N, meta::typelist<>>::value;


      // Remove the float suffix from a string that represents a float value
      template <typename>
      struct Remove_Float_Suffix;

      template <char...C>
      struct Remove_Float_Suffix<string<char,C...>>
      {
      private:
          template <typename T>
          struct Do_Remove_Float_Suffix
          {
              using type = T;
          };
          template <char...D>
          struct Do_Remove_Float_Suffix<string<char,'f',D...>>
          {
              using type = string<char,D...>;
          };
          template <char...D>
          struct Do_Remove_Float_Suffix<string<char,'F',D...>>
          {
              using type = string<char,D...>;
          };
          template <char...D>
          struct Do_Remove_Float_Suffix<string<char,'l',D...>>
          {
              using type = string<char,D...>;
          };
          template <char...D>
          struct Do_Remove_Float_Suffix<string<char,'L',D...>>
          {
              using type = string<char,D...>;
          };

          using input_type = string<char,C...>;
          using reversed_input_type = typename mf::reverse<input_type>::type;
          using edited_type = typename Do_Remove_Float_Suffix<reversed_input_type>::type;
      public:
          using type = typename mf::reverse<edited_type>::type;
      };


      // Collapse zero values
      template <typename>
      struct Remove_Leading_Zeros;

      template <char...C>
      struct Remove_Leading_Zeros<string<char,'0',C...>> :
              public Remove_Leading_Zeros<string<char,C...>>
      {
      };

      template <>
      struct Remove_Leading_Zeros<string<char,'0'>>
      {
          using type = string<char,'0'>;
      };

      template <char A,char...C>
      struct Remove_Leading_Zeros<string<char,A,C...>>
      {
          using type = string<char,A,C...>;
      };


      // Collapse zero values at the end of number string. Searches for a decimal point first
      // so that meaningful zeros are not removed.
      template <typename>
      struct Remove_Trailing_Zeros;

      template <char...C>
      struct Remove_Trailing_Zeros<string<char,C...>>
      {
      private:
          using decimal_point_find_type = mf::find_first<string<char,C...>,char, '.'>;
      public:
          using type =
          typename std::conditional
          <
              decimal_point_find_type::value == sizeof...(C),
              string<char,C...>,
              typename mf::reverse
              <
                  typename Remove_Leading_Zeros
                  <
                      typename mf::reverse
                      <
                          string<char,C...>
                      >::type
                  >::type
              >::type
          >::type;
      };


      // Convert a string that contains an unsigned integer into an integer value
      template <typename>
      struct String_To_Unsigned_Integer;

      // Collapse zero values
      template <char...C>
      struct String_To_Unsigned_Integer<string<char,'0',C...>>
              :
              public String_To_Unsigned_Integer<string<char,C...>>
      {
      };
      //If we got this far then it was zero all along
      template <>
      struct String_To_Unsigned_Integer<string<char,'0'>>
      {
          using input_type = string<char,'0'>;
          using reversed_char_string = typename mf::reverse< input_type >::type;

          using int_type = float_mantissa_type;
          static constexpr int_type const value = { 0ull };
      };

      // at this point leading zeros should have been chopped off
      template <char...C>
      struct String_To_Unsigned_Integer<string<char,C...>>
      {
          using input_type = string<char,C...>;
          using reversed_char_typelist = typename meta::mf::reverse< typename mf::to_typelist<input_type>::type >::type;

          using int_type = unsigned long long;
          static constexpr int_type const value = { Accumulate_Digits<int_type,0,reversed_char_typelist>::value  };
      };


      // Split the float string into the Mantissa and the Exponent
      template <typename>
      struct Mantissa_Exponent_Split_Float_String;

      template <char...C>
      struct Mantissa_Exponent_Split_Float_String<string<char,C...>>
      {
          using input_type = string<char,C...>;

          using find_type = mf::find_first<input_type, char, 'e'>;

          static constexpr std::size_t const e_position = { find_type::value };
          using mantissa_string_type = typename mf::substring<input_type,0,e_position>::type;



          using raw_exponent_string_type = typename mf::substring<input_type,e_position+1,-1>::type;

          using exponent_string_type =
          typename std::conditional
          <
              std::is_same<raw_exponent_string_type,string<char>>::value,
              string<char,'0'>,
              raw_exponent_string_type
          >::type;
      };


      // Determine the location of the decimal point in the mantissa string and also
      // create an integer string out of it.
      template <typename>
      struct Mantissa_Point;

      template <char...C>
      struct Mantissa_Point<string<char,C...>>
      {
          // should be of the form [digits].[digits]
          using input_type = string<char,C...>;

          using find_type = typename mf::find_first<input_type,char,'.'>::type;

          using integer_string =
          typename mf::remove
          <
              input_type,
              find_type::value
          >::type;
      };


      // Assume we get here with a float type literal
      template <typename,typename>
      struct Float_String_Literal_Analyser;

      template <typename F,char...C>
      struct Float_String_Literal_Analyser<F,string<char,C...>>
      {
          using value_type = F;

          // e.g. INPUT = "-0012.3450e-05f"
          using input_type = string<char,C...>;


          // STEP 1
          // Cleanup and split the string.

          // If present, remove the suffix from the end.
          // e.g.   "-0012.3450e-5"
          using clean_input_type = typename Remove_Float_Suffix<input_type>::type;

          // Split the input string into 2 strings, the mantissa and the exponent.
          // Both strings are signed at this time.
          using splitter_type = Mantissa_Exponent_Split_Float_String<clean_input_type>;

          // e.g.   "-0012.3450"
          using signed_mantissa_string_type = typename splitter_type::mantissa_string_type;

          // e.g.   "-05"
          using signed_exponent_string_type = typename splitter_type::exponent_string_type;

          // STEP 2
          // Analyse the mantissa.

          // Determine the sign bit, true if negative.
          // e.g.   "true"
          static constexpr float_sign_type const sign = { Sign_Of_Number_String<signed_mantissa_string_type>::bool_value };

          // Remove the sign from mantissa string.
          // e.g.   "0012.34500"
          using unsigned_mantissa_string_type = typename Sign_Of_Number_String<signed_mantissa_string_type>::unsigned_string_type;

          // Remove any leading zeros from the string.
          // e.g.   "12.34500"
          using front_clean_unsigned_mantissa_string_type = typename Remove_Leading_Zeros<unsigned_mantissa_string_type>::type;

          // Remove any trailing zeros from the string. This automatically checks if a decimal point is present before proceeding.
          // e.g.   "12.345"
          using clean_unsigned_mantissa_string_type = typename Remove_Trailing_Zeros<front_clean_unsigned_mantissa_string_type>::type;

          // Find the location of the decimal point.
          // If not found, the result is equal to the size of the string.
          // e.g.   2
          using decimal_point_find_type = mf::find_first<clean_unsigned_mantissa_string_type,char, '.'>;

          // Make an exponent correction value out of it
          // e.g.   2 == 6 ? 0 : 6 - 2 -1 = 3
          static constexpr float_exponent_type const exponent_correction =
          {
              static_cast<float_exponent_type>
              (
                  decimal_point_find_type::value == clean_unsigned_mantissa_string_type::size()
                  ? 0
                  : clean_unsigned_mantissa_string_type::size() - decimal_point_find_type::value - 1
              )
          };

          // Now remove the point from the string to make it into an integer string.
          // We need to check though to see if the string was reduced to just a decimal point.
          // e.g.   "12345"
          using unsigned_integer_mantissa_string_type =
          typename std::conditional
          <
              std::is_same<clean_unsigned_mantissa_string_type, string<char,'.'>>::value,
              string<char,'0'>,
              typename mf::remove<clean_unsigned_mantissa_string_type,decimal_point_find_type::value>::type
          >::type;

          // Make an unsigned integer value out of this string.
          // e.g.   12345
          static constexpr float_mantissa_type const mantissa = { String_To_Unsigned_Integer<unsigned_integer_mantissa_string_type>::value };

          // STEP 3
          // Analyse the exponent.

          // Determine the exponent sign.
          // This is not an exposed value but is applied after analysis.
          // e.g.   -1
          static constexpr float_exponent_type const exponent_sign = { Sign_Of_Number_String<signed_exponent_string_type>::int_value };

          // Remove the sign of the exponent if present.
          // e.g.   "05"
          using unsigned_exponent_string_type = typename Sign_Of_Number_String<signed_exponent_string_type>::unsigned_string_type;

          // Remove any leading zeros from the string.
          // e.g.   "5"
          //using clean_unsigned_exponent_string_type = typename Remove_Leading_Zeros<unsigned_exponent_string_type>::type;

          // Since the conversion to integer already strips leading zeros we can skip the cleanup step.
          // e.g.   5
          static constexpr float_exponent_type const exponent_raw = { static_cast<float_exponent_type>(String_To_Unsigned_Integer<unsigned_exponent_string_type>::value) };

          // Build the exponent, which is set to zero if the mantissa is zero.
          // e.g.   12345 == 0 ? 0 : 5 * - 1 + 3 = -5 + 3 = -2
          static constexpr float_exponent_type const exponent = { mantissa == 0 ? 0 : (exponent_raw * exponent_sign - exponent_correction) };

          // e.g. Result is 12345e-8

          using type = floating_point<value_type,mantissa,exponent,sign>;
      };

    } // namespace v1
  } // namespace litype
} // namespace dclib

template <typename F,char...C>
constexpr dclib::litype::v1::float_sign_type const dclib::litype::v1::Float_String_Literal_Analyser<F,dclib::litype::v1::string<char,C...>>::sign;

template <typename F,char...C>
constexpr dclib::litype::v1::float_exponent_type const dclib::litype::v1::Float_String_Literal_Analyser<F,dclib::litype::v1::string<char,C...>>::exponent_correction;

template <typename F,char...C>
constexpr dclib::litype::v1::float_mantissa_type const dclib::litype::v1::Float_String_Literal_Analyser<F,dclib::litype::v1::string<char,C...>>::mantissa;

template <typename F,char...C>
constexpr dclib::litype::v1::float_exponent_type const dclib::litype::v1::Float_String_Literal_Analyser<F,dclib::litype::v1::string<char,C...>>::exponent_sign;

template <typename F,char...C>
constexpr dclib::litype::v1::float_exponent_type const dclib::litype::v1::Float_String_Literal_Analyser<F,dclib::litype::v1::string<char,C...>>::exponent_raw;

template <typename F,char...C>
constexpr dclib::litype::v1::float_exponent_type const dclib::litype::v1::Float_String_Literal_Analyser<F,dclib::litype::v1::string<char,C...>>::exponent;



// Now we make sure it all works...


#endif // FLOAT_TOOLS_HPP
