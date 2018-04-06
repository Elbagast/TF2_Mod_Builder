#include "string_conversion.hpp"
#include <array>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cassert>
#include <array>
#include <algorithm>

namespace
{
  std::array<std::string,5> const c_true_strings = {u8"true",u8"TRUE",u8"True",u8"1",u8"0x01" };
  std::array<std::string,5> const c_false_strings = {u8"false",u8"FALSE",u8"False",u8"0",u8"0x00" };
}


std::string sak::generic::To_Std_String<bool>::operator()(bool a_value, sak::generic::Bool_Text_Format a_format) const
{
    switch(a_format)
    {
    case Bool_Text_Format::Lowercase:
        return a_value ? c_true_strings[0] : c_false_strings[0];
    case Bool_Text_Format::Uppercase:
        return a_value ? c_true_strings[1] : c_false_strings[1];
    case Bool_Text_Format::Capitalised:
        return a_value ? c_true_strings[2] : c_false_strings[2];
    case Bool_Text_Format::Number:
        return a_value ? c_true_strings[3] : c_false_strings[3];
    case Bool_Text_Format::Hexadecimal:
        return a_value ? c_true_strings[4] : c_false_strings[4];
    default:
        return std::string();
    }
}

namespace
{
    constexpr char const hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                     '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    template <typename T>
    std::string to_string_hex(T a_value)
    {
        //char const* lp_memory{ static_cast<char const*>(static_cast<void const*>(&a_value)) };
        char l_buffer[sizeof(T)]{0};
        memcpy(l_buffer, static_cast<void const*>(&a_value), sizeof(T));

        std::string l_string{};
        l_string.reserve((sizeof(T) * 2) + 2);
        l_string.push_back('0');
        l_string.push_back('x');

        for (int l_index = sizeof(T) - 1; l_index >= 0; --l_index)
        {
            l_string.push_back(hexmap[(l_buffer[l_index] & 0xF0) >> 4]);
            l_string.push_back(hexmap[l_buffer[l_index] & 0x0F]);
        }
        return l_string;
    }

    template <typename Signed_Int>
    char int_sign_char(Signed_Int a_value)
    {
        return a_value < 0 ? '-': '+';
    }

    template <typename T>
    std::string to_string_int_default(T a_value)
    {
        //std::ostringstream l_stream{};
        //l_stream << a_value;
        //return l_stream.str();
        return std::to_string(a_value);
    }


    template <typename T>
    std::string to_string_int_signed_if_negative(T a_value)
    {
        return to_string_int_default(a_value);
    }

    template <typename T>
    std::string to_string_int_signed(T a_value)
    {
        return a_value < 0 ? to_string_int_default(a_value) : '+' + to_string_int_default(a_value);
    }

    template <typename T>
    std::string to_string_int_hex(T a_value)
    {
        return to_string_hex(a_value);
    }


    template <typename T_Int>
    std::string to_string_int_implementation(T_Int a_value, sak::generic::Int_Text_Format a_format)
    {
        switch(a_format)
        {
        case sak::generic::Int_Text_Format::Signed_If_Negative:
            return to_string_int_signed_if_negative(a_value);
        case sak::generic::Int_Text_Format::Signed:
            return to_string_int_signed(a_value);
        case sak::generic::Int_Text_Format::Hexadecimal:
            //return to_string_int_hex(static_cast<typename Get_Unsigned_Type<T_Int>::type>(a_value));
            return to_string_int_hex(a_value);
        default:
            return std::string();
        }
    }

    template <typename T_Unt>
    std::string to_string_uint_implementation(T_Unt a_value, sak::generic::Int_Text_Format a_format)
    {
        switch(a_format)
        {
            case sak::generic::Int_Text_Format::Signed_If_Negative:
                return to_string_int_default(a_value);
            case sak::generic::Int_Text_Format::Signed:
                return '+' + to_string_int_default(a_value);
            case sak::generic::Int_Text_Format::Hexadecimal:
                return to_string_int_hex(a_value);
        default:
            return std::string();
        }
    }
}

std::string sak::generic::To_Std_String<std::int8_t>::operator()(std::int8_t a_value, sak::generic::Int_Text_Format a_format) const
{
    return to_string_int_implementation(a_value, a_format);
}

std::string sak::generic::To_Std_String<std::int16_t>::operator()(std::int16_t a_value, sak::generic::Int_Text_Format a_format) const
{
    return to_string_int_implementation(a_value, a_format);
}

std::string sak::generic::To_Std_String<std::int32_t>::operator()(std::int32_t a_value, sak::generic::Int_Text_Format a_format) const
{
    return to_string_int_implementation(a_value, a_format);
}

std::string sak::generic::To_Std_String<std::int64_t>::operator()(std::int64_t a_value, sak::generic::Int_Text_Format a_format) const
{
    return to_string_int_implementation(a_value, a_format);
}

std::string sak::generic::To_Std_String<std::uint8_t>::operator()(std::uint8_t a_value, sak::generic::Int_Text_Format a_format) const
{
    return to_string_uint_implementation(a_value, a_format);
}

std::string sak::generic::To_Std_String<std::uint16_t>::operator()(std::uint16_t a_value, sak::generic::Int_Text_Format a_format) const
{
    return to_string_uint_implementation(a_value, a_format);
}

std::string sak::generic::To_Std_String<std::uint32_t>::operator()(std::uint32_t a_value, sak::generic::Int_Text_Format a_format) const
{
    return to_string_uint_implementation(a_value, a_format);
}

std::string sak::generic::To_Std_String<std::uint64_t>::operator()(std::uint64_t a_value, sak::generic::Int_Text_Format a_format) const
{
    return to_string_uint_implementation(a_value, a_format);
}

namespace
{

    // hmmmm
    template <typename T_Float>
    std::string to_string_float_default(T_Float a_value)
    {
        std::ostringstream l_ostream{};
        l_ostream
                //<< std::defaultfloat
                << a_value;

        return l_ostream.str();
    }

    // hmmmm
    template <typename T_Float>
    std::string to_string_float_calculator(T_Float a_value)
    {
        std::ostringstream l_ostream{};
        l_ostream.precision(std::numeric_limits<T_Float>::max_digits10);
        l_ostream
                //<< std::defaultfloat
                << a_value;

        return l_ostream.str();
    }

    template <typename T_Float>
    std::string to_string_float_scientific(T_Float a_value)
    {
        std::ostringstream l_ostream{};
        l_ostream.precision(std::numeric_limits<T_Float>::max_digits10);
        l_ostream
                << std::scientific
                << a_value;

        return l_ostream.str();
    }

    template <typename T_Float>
    std::string to_string_float_hex(T_Float a_value)
    {
        /*
        //return to_string_hex(a_value);
        std::ostringstream l_ostream{};
        l_ostream
                << std::hexfloat
                << a_value;

        return l_ostream.str();
        */
        // raw memory hex
        return to_string_hex(a_value);
    }

    template <typename T_Float>
    std::string to_string_float_implementation(T_Float a_value, sak::generic::Float_Text_Format a_format)
    {
        switch(a_format)
        {
        case sak::generic::Float_Text_Format::Simplest:
            return to_string_float_calculator(a_value);
        case sak::generic::Float_Text_Format::Scientific:
            return to_string_float_scientific(a_value);
        case sak::generic::Float_Text_Format::Hexadecimal:
            return to_string_float_hex(a_value);
        default:
            return std::string();
        }
    }
}

std::string sak::generic::To_Std_String<float>::operator()(float a_value, sak::generic::Float_Text_Format a_format) const
{
    return to_string_float_implementation<float>(a_value, a_format);
}

std::string sak::generic::To_Std_String<double>::operator()(double a_value, sak::generic::Float_Text_Format a_format) const
{
    return to_string_float_implementation<double>(a_value, a_format);
}

std::string sak::generic::To_Std_String<long double>::operator()(long double a_value, sak::generic::Float_Text_Format a_format) const
{
    return to_string_float_implementation<long double>(a_value, a_format);
}

std::string sak::generic::To_Std_String<std::string>::operator()(std::string const& a_value) const
{
    return a_value;
}

std::string sak::generic::To_Std_String<std::u16string>::operator()(std::u16string const&) const
{
    return "!!!std::u16string to std::string not implemented.";
}

std::string sak::generic::To_Std_String<std::u32string>::operator()(std::u32string const&) const
{
    return "!!!std::u32string to std::string not implemented.";
}

std::string sak::generic::To_Std_String<std::wstring>::operator()(std::wstring const&) const
{
    return "!!!std::wstring to std::string not implemented.";
}



bool sak::generic::From_Std_String<bool>::operator()(std::string const& a_string) const
{
  if (std::find(c_true_strings.cbegin(), c_true_strings.cend(), a_string) != c_true_strings.cend())
  {
    return true;
  }
  else if (std::find(c_false_strings.cbegin(), c_false_strings.cend(), a_string) != c_false_strings.cend())
  {
    return false;
  }
  else
  {
    // unrecognised...therefore
    return false;
  }
}
