#ifndef SAK_GENERIC_STRING_CONVERSION_FORMATS_HPP
#define SAK_GENERIC_STRING_CONVERSION_FORMATS_HPP

namespace sak
{
  namespace generic
  {
    enum class Bool_Text_Format
    {
      Lowercase,
      Uppercase,
      Capitalised,
      Number,
      Hexadecimal,

      Default = Bool_Text_Format::Lowercase
    };

    enum class Int_Text_Format
    {
      Signed_If_Negative,
      Signed,
      Hexadecimal,

      Default = Int_Text_Format::Signed_If_Negative
    };

    enum class Float_Text_Format
    {
      Simplest, // output as if a calculator screen
      Scientific,
      Hexadecimal,

      Default = Float_Text_Format::Simplest
    };

  } // namespace generic
} // namespace sak

#endif // SAK_GENERIC_STRING_CONVERSION_FORMATS_HPP
