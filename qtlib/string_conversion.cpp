#include "string_conversion.hpp"
#include <generic/string_conversion.hpp>
#include <QString>


QString qtlib::To_QString<bool>::operator()(bool a_value, Bool_Text_Format a_format) const
{
    return QString::fromStdString(To_Std_String<bool>()(a_value, a_format));
}

QString qtlib::To_QString<std::int8_t>::operator()(std::int8_t a_value, Int_Text_Format a_format) const
{
    return QString::fromStdString(To_Std_String<std::int8_t>()(a_value, a_format));
}

QString qtlib::To_QString<std::int16_t>::operator()(std::int16_t a_value, Int_Text_Format a_format) const
{
    return QString::fromStdString(To_Std_String<std::int16_t>()(a_value, a_format));
}

QString qtlib::To_QString<std::int32_t>::operator()(std::int32_t a_value, Int_Text_Format a_format) const
{
    return QString::fromStdString(To_Std_String<std::int32_t>()(a_value, a_format));
}

QString qtlib::To_QString<std::int64_t>::operator()(std::int64_t a_value, Int_Text_Format a_format) const
{
    return QString::fromStdString(To_Std_String<std::int64_t>()(a_value, a_format));
}

QString qtlib::To_QString<std::uint8_t>::operator()(std::uint8_t a_value, Int_Text_Format a_format) const
{
    return QString::fromStdString(To_Std_String<std::uint8_t>()(a_value, a_format));
}

QString qtlib::To_QString<std::uint16_t>::operator()(std::uint16_t a_value, Int_Text_Format a_format) const
{
    return QString::fromStdString(To_Std_String<std::uint16_t>()(a_value, a_format));
}

QString qtlib::To_QString<std::uint32_t>::operator()(std::uint32_t a_value, Int_Text_Format a_format) const
{
    return QString::fromStdString(To_Std_String<std::uint32_t>()(a_value, a_format));
}

QString qtlib::To_QString<std::uint64_t>::operator()(std::uint64_t a_value, Int_Text_Format a_format) const
{
    return QString::fromStdString(To_Std_String<std::uint64_t>()(a_value, a_format));
}

QString qtlib::To_QString<float>::operator()(float a_value, Float_Text_Format a_format) const
{
    return QString::fromStdString(To_Std_String<float>()(a_value, a_format));
}

QString qtlib::To_QString<double>::operator()(double a_value, Float_Text_Format a_format) const
{
    return QString::fromStdString(To_Std_String<double>()(a_value, a_format));
}

QString qtlib::To_QString<long double>::operator()(long double a_value, Float_Text_Format a_format) const
{
    return QString::fromStdString(To_Std_String<long double>()(a_value, a_format));
}

QString qtlib::To_QString<std::string>::operator()(std::string const& a_value) const
{
    return QString::fromStdString(a_value);
}

QString qtlib::To_QString<std::u16string>::operator()(std::u16string const& a_value) const
{
    return QString::fromStdU16String(a_value);
}

QString qtlib::To_QString<std::u32string>::operator()(std::u32string const& a_value) const
{
    return QString::fromStdU32String(a_value);
}

QString qtlib::To_QString<std::wstring>::operator()(std::wstring const& a_value) const
{
    return QString::fromStdWString(a_value);
}
