#include "qstring_conversion.hpp"
#include "../generic/string_conversion.hpp"
#include <QString>


QString sak::gui::To_QString<bool>::operator()(bool a_value, Bool_Text_Format a_format) const
{
  return QString::fromStdString(generic::To_Std_String<bool>()(a_value, a_format));
}

QString sak::gui::To_QString<std::int8_t>::operator()(std::int8_t a_value, Int_Text_Format a_format) const
{
  return QString::fromStdString(generic::To_Std_String<std::int8_t>()(a_value, a_format));
}

QString sak::gui::To_QString<std::int16_t>::operator()(std::int16_t a_value, Int_Text_Format a_format) const
{
  return QString::fromStdString(generic::To_Std_String<std::int16_t>()(a_value, a_format));
}

QString sak::gui::To_QString<std::int32_t>::operator()(std::int32_t a_value, Int_Text_Format a_format) const
{
  return QString::fromStdString(generic::To_Std_String<std::int32_t>()(a_value, a_format));
}

QString sak::gui::To_QString<std::int64_t>::operator()(std::int64_t a_value, Int_Text_Format a_format) const
{
  return QString::fromStdString(generic::To_Std_String<std::int64_t>()(a_value, a_format));
}

QString sak::gui::To_QString<std::uint8_t>::operator()(std::uint8_t a_value, Int_Text_Format a_format) const
{
  return QString::fromStdString(generic::To_Std_String<std::uint8_t>()(a_value, a_format));
}

QString sak::gui::To_QString<std::uint16_t>::operator()(std::uint16_t a_value, Int_Text_Format a_format) const
{
  return QString::fromStdString(generic::To_Std_String<std::uint16_t>()(a_value, a_format));
}

QString sak::gui::To_QString<std::uint32_t>::operator()(std::uint32_t a_value, Int_Text_Format a_format) const
{
  return QString::fromStdString(generic::To_Std_String<std::uint32_t>()(a_value, a_format));
}

QString sak::gui::To_QString<std::uint64_t>::operator()(std::uint64_t a_value, Int_Text_Format a_format) const
{
  return QString::fromStdString(generic::To_Std_String<std::uint64_t>()(a_value, a_format));
}

QString sak::gui::To_QString<float>::operator()(float a_value, Float_Text_Format a_format) const
{
  return QString::fromStdString(generic::To_Std_String<float>()(a_value, a_format));
}

QString sak::gui::To_QString<double>::operator()(double a_value, Float_Text_Format a_format) const
{
  return QString::fromStdString(generic::To_Std_String<double>()(a_value, a_format));
}

QString sak::gui::To_QString<long double>::operator()(long double a_value, Float_Text_Format a_format) const
{
  return QString::fromStdString(generic::To_Std_String<long double>()(a_value, a_format));
}

QString sak::gui::To_QString<std::string>::operator()(std::string const& a_value) const
{
  return QString::fromStdString(a_value);
}

QString sak::gui::To_QString<std::u16string>::operator()(std::u16string const& a_value) const
{
  return QString::fromStdU16String(a_value);
}

QString sak::gui::To_QString<std::u32string>::operator()(std::u32string const& a_value) const
{
  return QString::fromStdU32String(a_value);
}

QString sak::gui::To_QString<std::wstring>::operator()(std::wstring const& a_value) const
{
  return QString::fromStdWString(a_value);
}

QString sak::gui::To_QString<QString>::operator()(QString const& a_value) const
{
  return a_value;
}



bool sak::gui::From_QString<bool>::operator()(QString const& a_string) const
{
  return generic::From_Std_String<bool>()(a_string.toStdString());
}

std::int8_t sak::gui::From_QString<std::int8_t>::operator()(QString const& a_string) const
{
  return static_cast<std::int8_t>(a_string.toLongLong());
}

std::int16_t sak::gui::From_QString<std::int16_t>::operator()(QString const& a_string) const
{
  return static_cast<std::int16_t>(a_string.toLongLong());
}

std::int32_t sak::gui::From_QString<std::int32_t>::operator()(QString const& a_string) const
{
  return static_cast<std::int32_t>(a_string.toLongLong());
}

std::int64_t sak::gui::From_QString<std::int64_t>::operator()(QString const& a_string) const
{
  return static_cast<std::int64_t>(a_string.toLongLong());
}

std::uint8_t sak::gui::From_QString<std::uint8_t>::operator()(QString const& a_string) const
{
  return static_cast<std::uint8_t>(a_string.toULongLong());
}

std::uint16_t sak::gui::From_QString<std::uint16_t>::operator()(QString const& a_string) const
{
  return static_cast<std::uint16_t>(a_string.toULongLong());
}

std::uint32_t sak::gui::From_QString<std::uint32_t>::operator()(QString const& a_string) const
{
  return static_cast<std::uint32_t>(a_string.toULongLong());
}

std::uint64_t sak::gui::From_QString<std::uint64_t>::operator()(QString const& a_string) const
{
  return static_cast<std::uint64_t>(a_string.toULongLong());
}

float sak::gui::From_QString<float>::operator()(QString const& a_string) const
{
  return a_string.toFloat();
}

double sak::gui::From_QString<double>::operator()(QString const& a_string) const
{
  return a_string.toDouble();
}

long double sak::gui::From_QString<long double>::operator()(QString const& a_string) const
{
  // not proper...
  return static_cast<long double>(a_string.toDouble());
}

std::string sak::gui::From_QString<std::string>::operator()(QString const& a_string) const
{
  return a_string.toStdString();
}

std::u16string sak::gui::From_QString<std::u16string>::operator()(QString const& a_string) const
{
  return a_string.toStdU16String();
}

std::u32string sak::gui::From_QString<std::u32string>::operator()(QString const& a_string) const
{
  return a_string.toStdU32String();
}

std::wstring sak::gui::From_QString<std::wstring>::operator()(QString const& a_string) const
{
  return a_string.toStdWString();
}

QString sak::gui::From_QString<QString>::operator()(QString const& a_string) const
{
  return a_string;
}
