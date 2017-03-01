#ifndef GENERIC_STRING_CONVERSION_H
#define GENERIC_STRING_CONVERSION_H

#include "string_conversion_formats.hpp"
#include <string>

namespace generic
{
  // Going to want some way of being able to alter the string representations.
  // Also std::to_string for float types is not exact

  template <typename T>
  struct To_Std_String {};


  template <>
  struct To_Std_String<bool>
  {
    std::string operator()(bool a_value, Bool_Text_Format a_format = Bool_Text_Format::Default) const;
  };


  template <>
  struct To_Std_String<std::int8_t>
  {
    std::string operator()(std::int8_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };

  template <>
  struct To_Std_String<std::int16_t>
  {
    std::string operator()(std::int16_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };

  template <>
  struct To_Std_String<std::int32_t>
  {
    std::string operator()(std::int32_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };

  template <>
  struct To_Std_String<std::int64_t>
  {
    std::string operator()(std::int64_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };


  template <>
  struct To_Std_String<std::uint8_t>
  {
    std::string operator()(std::uint8_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };

  template <>
  struct To_Std_String<std::uint16_t>
  {
    std::string operator()(std::uint16_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };

  template <>
  struct To_Std_String<std::uint32_t>
  {
    std::string operator()(std::uint32_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };

  template <>
  struct To_Std_String<std::uint64_t>
  {
    std::string operator()(std::uint64_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };


  template <>
  struct To_Std_String<float>
  {
    std::string operator()(float a_value, Float_Text_Format a_format = Float_Text_Format::Default) const;
  };

  template <>
  struct To_Std_String<double>
  {
    std::string operator()(double a_value, Float_Text_Format a_format = Float_Text_Format::Default) const;
  };

  template <>
  struct To_Std_String<long double>
  {
    std::string operator()(long double a_value, Float_Text_Format a_format = Float_Text_Format::Default) const;
  };


  template <>
  struct To_Std_String<std::string>
  {
    std::string operator()(std::string const& a_value) const;
  };

  template <>
  struct To_Std_String<std::u16string>
  {
    std::string operator()(std::u16string const& a_value) const;
  };

  template <>
  struct To_Std_String<std::u32string>
  {
    std::string operator()(std::u32string const& a_value) const;
  };

  template <>
  struct To_Std_String<std::wstring>
  {
    std::string operator()(std::wstring const& a_value) const;
  };



  template <typename T>
  struct From_Std_String {};

  template <>
  struct From_Std_String<bool>
  {
    bool operator()(std::string const& a_string) const;
  };
} // namespace generic

#endif // GENERIC_STRING_CONVERSION_H
