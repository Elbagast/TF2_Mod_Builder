#ifndef QTLIB_STRING_CONVERSION_H
#define QTLIB_STRING_CONVERSION_H

#include <string>
#include <generic/string_conversion_formats.hpp>
class QString;

namespace qtlib
{
  using Bool_Text_Format = generic::Bool_Text_Format;
  using Int_Text_Format = generic::Int_Text_Format;
  using Float_Text_Format = generic::Float_Text_Format;

  template <typename T>
  struct To_QString {};

  template <>
  struct To_QString<bool>
  {
    QString operator()(bool a_value, Bool_Text_Format a_format = Bool_Text_Format::Default) const;
  };


  template <>
  struct To_QString<std::int8_t>
  {
    QString operator()(std::int8_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };

  template <>
  struct To_QString<std::int16_t>
  {
    QString operator()(std::int16_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };

  template <>
  struct To_QString<std::int32_t>
  {
    QString operator()(std::int32_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };

  template <>
  struct To_QString<std::int64_t>
  {
    QString operator()(std::int64_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };


  template <>
  struct To_QString<std::uint8_t>
  {
    QString operator()(std::uint8_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };

  template <>
  struct To_QString<std::uint16_t>
  {
    QString operator()(std::uint16_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };

  template <>
  struct To_QString<std::uint32_t>
  {
    QString operator()(std::uint32_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };

  template <>
  struct To_QString<std::uint64_t>
  {
    QString operator()(std::uint64_t a_value, Int_Text_Format a_format = Int_Text_Format::Default) const;
  };


  template <>
  struct To_QString<float>
  {
    QString operator()(float a_value, Float_Text_Format a_format = Float_Text_Format::Default) const;
  };

  template <>
  struct To_QString<double>
  {
    QString operator()(double a_value, Float_Text_Format a_format = Float_Text_Format::Default) const;
  };

  template <>
  struct To_QString<long double>
  {
    QString operator()(long double a_value, Float_Text_Format a_format = Float_Text_Format::Default) const;
  };


  template <>
  struct To_QString<std::string>
  {
    QString operator()(std::string const& a_value) const;
  };

  template <>
  struct To_QString<std::u16string>
  {
    QString operator()(std::u16string const& a_value) const;
  };

  template <>
  struct To_QString<std::u32string>
  {
    QString operator()(std::u32string const& a_value) const;
  };

  template <>
  struct To_QString<std::wstring>
  {
    QString operator()(std::wstring const& a_value) const;
  };


  template <>
  struct To_QString<QString>
  {
    QString operator()(QString const& a_value) const;
  };



  template <typename T>
  struct From_QString {};


  template <>
  struct From_QString<bool>
  {
    bool operator()(QString const& a_string) const;
  };


  template <>
  struct From_QString<std::int8_t>
  {
    std::int8_t operator()(QString const& a_string) const;
  };

  template <>
  struct From_QString<std::int16_t>
  {
    std::int16_t operator()(QString const& a_string) const;
  };

  template <>
  struct From_QString<std::int32_t>
  {
    std::int32_t operator()(QString const& a_string) const;
  };

  template <>
  struct From_QString<std::int64_t>
  {
    std::int64_t operator()(QString const& a_string) const;
  };


  template <>
  struct From_QString<std::uint8_t>
  {
    std::uint8_t operator()(QString const& a_string) const;
  };

  template <>
  struct From_QString<std::uint16_t>
  {
    std::uint16_t operator()(QString const& a_string) const;
  };

  template <>
  struct From_QString<std::uint32_t>
  {
    std::uint32_t operator()(QString const& a_string) const;
  };

  template <>
  struct From_QString<std::uint64_t>
  {
    std::uint64_t operator()(QString const& a_string) const;
  };


  template <>
  struct From_QString<float>
  {
    float operator()(QString const& a_string) const;
  };

  template <>
  struct From_QString<double>
  {
    double operator()(QString const& a_string) const;
  };

  template <>
  struct From_QString<long double>
  {
    long double operator()(QString const& a_string) const;
  };


  template <>
  struct From_QString<std::string>
  {
    std::string operator()(QString const& a_string) const;
  };

  template <>
  struct From_QString<std::u16string>
  {
    std::u16string operator()(QString const& a_string) const;
  };

  template <>
  struct From_QString<std::u32string>
  {
    std::u32string operator()(QString const& a_string) const;
  };

  template <>
  struct From_QString<std::wstring>
  {
    std::wstring operator()(QString const& a_string) const;
  };


  template <>
  struct From_QString<QString>
  {
    QString operator()(QString const& a_string) const;
  };

} // namespace qtlib

#endif // QTLIB_STRING_CONVERSION_H
