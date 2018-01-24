#ifndef SAK_TYPESTRING_QSTRING_HPP
#define SAK_TYPESTRING_QSTRING_HPP

#ifndef SAK_TYPESTRING_QSTRING_FWD_HPP
#include "typestring_qstring_fwd.hpp"
#endif

#ifndef FLAMINGO_LITYPE_STRING_HPP
#include <flamingo/litype/string.hpp>
#endif

#ifndef INCLUDE_QT_QSTRING
#define INCLUDE_QT_QSTRING
#include <QString>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Typestring_QString<flamingo::litype::string<C,C...>
  //---------------------------------------------------------------------------
  // Provide a conversion for literal strings to QString runtime values

  template <char...T_Chars>
  class Typestring_QString<flamingo::litype::string<char,T_Chars...>>
  {
  public:
    static QString value()
    {
      static QString const s_value = QString::fromUtf8(flamingo::litype::string<char,T_Chars...>::data(), flamingo::litype::string<char,T_Chars...>::size());
      return s_value;
    }
  };

  template <char16_t...T_Chars>
  class Typestring_QString<flamingo::litype::string<char16_t,T_Chars...>>
  {
  public:
    static QString value()
    {
      static QString const s_value = QString::fromUtf16(flamingo::litype::string<char16_t,T_Chars...>::data(), flamingo::litype::string<char16_t,T_Chars...>::size());
      return s_value;
    }
  };

  template <char32_t...T_Chars>
  class Typestring_QString<flamingo::litype::string<char32_t,T_Chars...>>
  {
  public:
    static QString value()
    {
      static QString const s_value = QString::fromUtf32(flamingo::litype::string<char32_t,T_Chars...>::data(), flamingo::litype::string<char32_t,T_Chars...>::size());
      return s_value;
    }
  };

  template <wchar_t...T_Chars>
  class Typestring_QString<flamingo::litype::string<wchar_t,T_Chars...>>
  {
  public:
    static QString value()
    {
      static QString const s_value = QString::fromWCharArray(flamingo::litype::string<wchar_t,T_Chars...>::data(), flamingo::litype::string<wchar_t,T_Chars...>::size());
      return s_value;
    }
  };
}

#endif // SAK_TYPESTRING_QSTRING_HPP
