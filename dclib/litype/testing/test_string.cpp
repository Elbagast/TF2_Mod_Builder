#include "test_string.hpp"
#include <dclib/litype/string.hpp>
#include <dclib/litype/v1/string_macro.hpp>
#include <iostream>
#include <iomanip>
#include <string>

namespace
{
    template <char... C>
    std::ostream& operator<<(std::ostream& ar_ostream, dclib::litype::string<char,C...>&& a_c_string_type)
    {
        for (auto const& l_char : a_c_string_type)
        {
            ar_ostream << l_char;
        }
        return ar_ostream;
    }

    template <char... C>
    std::ostream& hex_output(std::ostream& ar_ostream, dclib::litype::string<char,C...>&& a_c_string_type)
    {
        ar_ostream << std::hex;
        for (auto const& l_char : a_c_string_type)
        {
            ar_ostream << static_cast<int>(static_cast<unsigned char>(l_char)) << ' ';
        }
        ar_ostream << std::dec;
        return ar_ostream;
    }

    std::ostream& hex_output(std::ostream& ar_ostream, std::string const& a_string)
    {
        ar_ostream << std::hex;
        for (auto const& l_char : a_string)
        {
            ar_ostream << static_cast<int>(static_cast<unsigned char>(l_char)) << ' ';
        }
        ar_ostream << std::dec;
        return ar_ostream;
    }

    template <char... C>
    std::ostream& dec_output(std::ostream& ar_ostream, dclib::litype::string<char,C...>&& a_c_string_type)
    {
        ar_ostream << std::dec;
        for (auto const& l_char : a_c_string_type)
        {
            ar_ostream << static_cast<int>(static_cast<unsigned char>(l_char)) << ' ';
        }
        ar_ostream << std::dec;
        return ar_ostream;
    }

    std::ostream& dec_output(std::ostream& ar_ostream, std::string const& a_string)
    {
        ar_ostream << std::dec;
        for (auto const& l_char : a_string)
        {
            ar_ostream << static_cast<int>(static_cast<unsigned char>(l_char)) << ' ';
        }
        ar_ostream << std::dec;
        return ar_ostream;
    }

    template <wchar_t... C>
    std::wostream& operator<<(std::wostream& ar_ostream, dclib::litype::string<char,C...>&& a_c_string_type)
    {
        for (auto const& l_char : a_c_string_type)
        {
            ar_ostream << l_char;
        }
        return ar_ostream;
    }

    template <wchar_t... C>
    std::wostream& hex_output(std::wostream& ar_ostream, dclib::litype::string<char,C...>&& a_c_string_type)
    {
        ar_ostream << std::hex;
        for (auto const& l_char : a_c_string_type)
        {
            ar_ostream << static_cast<int>(static_cast<unsigned char>(l_char)) << ' ';
        }
        ar_ostream << std::dec;
        return ar_ostream;
    }

    std::wostream& hex_output(std::wostream& ar_ostream, std::wstring const& a_string)
    {
        ar_ostream << std::hex;
        for (auto const& l_char : a_string)
        {
            ar_ostream << static_cast<int>(static_cast<unsigned char>(l_char)) << ' ';
        }
        ar_ostream << std::dec;
        return ar_ostream;
    }

    template <wchar_t... C>
    std::wostream& dec_output(std::wostream& ar_ostream, dclib::litype::string<char,C...>&& a_c_string_type)
    {
        ar_ostream << std::dec;
        for (auto const& l_char : a_c_string_type)
        {
            ar_ostream << static_cast<int>(static_cast<unsigned char>(l_char)) << ' ';
        }
        ar_ostream << std::dec;
        return ar_ostream;
    }

    std::wostream& dec_output(std::wostream& ar_ostream, std::wstring const& a_string)
    {
        ar_ostream << std::dec;
        for (auto const& l_char : a_string)
        {
            ar_ostream << static_cast<int>(static_cast<unsigned char>(l_char)) << ' ';
        }
        ar_ostream << std::dec;
        return ar_ostream;
    }

    //using Output_Test1 = string_literal(1);
    //using Output_Test2 = string_literal(1.0);
    //using Output_Test3 = string_literal(1.0l);
} // namespace

// A load of tests on using the empty literal.

// Does the type work?
static_assert(std::is_same<DCLIB_LITYPE_STRING(""), dclib::litype::string<char>>::value, "Bad string literal type.");
static_assert(std::is_same<DCLIB_LITYPE_STRING(u""), dclib::litype::string<char16_t>>::value, "Bad string literal type.");
static_assert(std::is_same<DCLIB_LITYPE_STRING(U""), dclib::litype::string<char32_t>>::value, "Bad string literal type.");
static_assert(std::is_same<DCLIB_LITYPE_STRING(L""), dclib::litype::string<wchar_t>>::value, "Bad string literal type.");

// Is it empty?
static_assert(DCLIB_LITYPE_STRING("")::size() == 0, "Bad empty literal type.");
static_assert(DCLIB_LITYPE_STRING(u"")::size() == 0, "Bad empty literal type.");
static_assert(DCLIB_LITYPE_STRING(U"")::size() == 0, "Bad empty literal type.");
static_assert(DCLIB_LITYPE_STRING(L"")::size() == 0, "Bad empty literal type.");

// Does deferencing it equal the null character?
static_assert(*(DCLIB_LITYPE_STRING("")::data()) == '\0', "Bad empty literal data.");
static_assert(*(DCLIB_LITYPE_STRING(u"")::data()) == u'\0', "Bad empty literal data.");
static_assert(*(DCLIB_LITYPE_STRING(U"")::data()) == U'\0', "Bad empty literal data.");
static_assert(*(DCLIB_LITYPE_STRING(L"")::data()) == L'\0', "Bad empty literal data.");

void dclib::litype::test_string()
{
    // This first bit is unrelated to this library....should put it somewhere else...
    // Copyright Sign U+00A9
    // ©
    // UTF-8
    // hex C2 A9
    // dec 194 169
    // bin 11000010 10101001

    // These seem to complain in QtCreator and I don't know why. It works.
    std::cout << "Unicode (c) logo:" << std::endl;
    std::cout << "out: " << DCLIB_LITYPE_STRING("©")() << std::endl;
    std::cout << "hex(c2 a9): ";
    hex_output(std::cout, DCLIB_LITYPE_STRING("©")()) << std::endl;
    std::cout << "dec("<< 0b11000010 << ' '<< 0b10101001 <<"): ";
    dec_output(std::cout, DCLIB_LITYPE_STRING("©")()) << std::endl;
    std::cout <<  std::endl;

    std::cout << "Unicode (c) logo with u8 prefix:" << std::endl;
    std::cout << "out: " << DCLIB_LITYPE_STRING(u8"©")() << std::endl;
    std::cout << "hex(c2 a9): ";
    hex_output(std::cout, DCLIB_LITYPE_STRING(u8"©")()) << std::endl;
    std::cout << "dec("<< 0b11000010 << ' '<< 0b10101001 <<"): ";
    dec_output(std::cout, DCLIB_LITYPE_STRING(u8"©")()) << std::endl;
    std::cout <<  std::endl;

    std::cout << "Unicode (c) logo as escape char:" << std::endl;
    std::cout << "out: " << DCLIB_LITYPE_STRING("\u00a9")() << std::endl;
    std::cout << "hex(c2 a9): ";
    hex_output(std::cout, DCLIB_LITYPE_STRING("\u00a9")()) << std::endl;
    std::cout << "dec("<< 0b11000010 << ' '<< 0b10101001 <<"): ";
    dec_output(std::cout, DCLIB_LITYPE_STRING("\u00a9")()) << std::endl;
    std::cout <<  std::endl;


    std::cout << "Unicode (c) logo as escape char with u8 prefix:" << std::endl;
    std::cout << "out: " << DCLIB_LITYPE_STRING(u8"\u00a9")() << std::endl;
    std::cout << "hex(c2 a9): ";
    hex_output(std::cout, DCLIB_LITYPE_STRING(u8"\u00a9")()) << std::endl;
    std::cout << "dec("<< 0b11000010 << ' '<< 0b10101001 <<"): ";
    dec_output(std::cout, DCLIB_LITYPE_STRING(u8"\u00a9")()) << std::endl;
    std::cout <<  std::endl;


    std::cout << "Unicode std::string((c) logo) :" << std::endl;
    std::cout << "out: " << std::string("©") << std::endl;
    std::cout << "hex(c2 a9): ";
    hex_output(std::cout, std::string("©")) << std::endl;
    std::cout << "dec("<< 0b11000010 << ' '<< 0b10101001 <<"): ";
    dec_output(std::cout, std::string("©")) << std::endl;
    std::cout <<  std::endl;

    std::cout << "Unicode std::string((c) logo) with u8 prefix:" << std::endl;
    std::cout << "out: " << std::string(u8"©") << std::endl;
    std::cout << "hex(c2 a9): ";
    hex_output(std::cout, std::string(u8"©")) << std::endl;
    std::cout << "dec("<< 0b11000010 << ' '<< 0b10101001 <<"): ";
    dec_output(std::cout, std::string(u8"©")) << std::endl;
    std::cout <<  std::endl;

    std::cout << "Unicode std::string((c) logo) as escape character:" << std::endl;
    std::cout << "out: " << std::string("\u00a9") << std::endl;
    std::cout << "hex(c2 a9): ";
    hex_output(std::cout, std::string("\u00a9")) << std::endl;
    std::cout << "dec("<< 0b11000010 << ' '<< 0b10101001 <<"): ";
    dec_output(std::cout, std::string("\u00a9")) << std::endl;
    std::cout <<  std::endl;

    std::cout << "Unicode std::string((c) logo) as escape character with u8 prefix:" << std::endl;
    std::cout << "out: " << std::string(u8"\u00a9") << std::endl;
    std::cout << "hex(c2 a9): ";
    hex_output(std::cout, std::string(u8"\u00a9")) << std::endl;
    std::cout << "dec("<< 0b11000010 << ' '<< 0b10101001 <<"): ";
    dec_output(std::cout, std::string(u8"\u00a9")) << std::endl;
    std::cout <<  std::endl;

    //assert(std::string("©").size() == 2);
    //assert(std::string(u8"©").size() == 2);

    // is this buggery just Qt?...




    std::cout << DCLIB_LITYPE_STRING("a""b")() << std::endl;

    std::cout << DCLIB_LITYPE_STRING("")() << std::endl;

    static_assert(DCLIB_LITYPE_STRING("")::size() == 0, "");
    static_assert(std::is_same<DCLIB_LITYPE_STRING("a"),string<char,'a'>>::value, "");

    static_assert(*("") == '\0',"empty string literal is not a null character");
    static_assert(v1::get_raw_size("") == 1,"empty string literal is not size 1");


    using LiteralFoo = DCLIB_LITYPE_STRING("Foo");
    using LiteralBar = DCLIB_LITYPE_STRING("Bar");
    using LiteralFooBar = DCLIB_LITYPE_STRING("FooBar");

    using ConcatResult = mf::concatenate<LiteralFoo,LiteralBar>::type;
    static_assert(std::is_same<LiteralFooBar, ConcatResult>::value, "Bad concatenation");
    std::cout << ConcatResult::size() << std::endl;
    std::cout << ConcatResult::data() << std::endl;

    using PopF3Result = mf::pop_front<LiteralFooBar,3>::type;
    static_assert(std::is_same<LiteralBar, PopF3Result>::value, "Bad pop front n");
    std::cout << PopF3Result::size() << std::endl;
    std::cout << PopF3Result::data() << std::endl;

    using PopBF3Result = mf::pop_back<LiteralFooBar,3>::type;
    static_assert(std::is_same<LiteralFoo, PopBF3Result>::value, "Bad pop back n");
    std::cout << PopBF3Result::size() << std::endl;
    std::cout << PopBF3Result::data() << std::endl;


    using LiteralFooBar_popf3 = mf::pop_front<LiteralFooBar,3>::type;
    std::cout << LiteralFooBar_popf3::data() << std::endl;

    //static_assert(std::is_same<String_Literal_Type<char>, LiteralFooBar_popf3>::value, "Bad pop N");
    static_assert(std::is_same<DCLIB_LITYPE_STRING("234"), mf::pop_front<DCLIB_LITYPE_STRING("1234")>::type>::value, "Bad pop front");
    static_assert(std::is_same<DCLIB_LITYPE_STRING("123"), mf::pop_back<DCLIB_LITYPE_STRING("1234")>::type>::value, "Bad pop back");
    std::cout << mf::pop_front<DCLIB_LITYPE_STRING("1234")>::type::data() << std::endl;
    std::cout << mf::pop_back<DCLIB_LITYPE_STRING("1234")>::type::data() << std::endl;


    using Numbers_Literal = DCLIB_LITYPE_STRING("0123456789");

    std::cout << std::endl;
    std::cout << "start =            \"" << Numbers_Literal::data() << "\"" << std::endl;
    std::cout << "pop_back =         \"" << mf::pop_back<Numbers_Literal>::type::data() << "\"" << std::endl;
    std::cout << "pop_back_n(0) =    \"" << mf::pop_back<Numbers_Literal,0>::type::data() << "\"" << std::endl;
    std::cout << "pop_back_n(1) =    \"" << mf::pop_back<Numbers_Literal,1>::type::data() << "\"" << std::endl;
    std::cout << "pop_back_n(2) =    \"" << mf::pop_back<Numbers_Literal,2>::type::data() << "\"" << std::endl;
    std::cout << "pop_back_n(3) =    \"" << mf::pop_back<Numbers_Literal,3>::type::data() << "\"" << std::endl;
    std::cout << "pop_back_n(4) =    \"" << mf::pop_back<Numbers_Literal,4>::type::data() << "\"" << std::endl;
    std::cout << "pop_back_n(5) =    \"" << mf::pop_back<Numbers_Literal,5>::type::data() << "\"" << std::endl;
    std::cout << "pop_back_n(6) =    \"" << mf::pop_back<Numbers_Literal,6>::type::data() << "\"" << std::endl;
    std::cout << "pop_back_n(7) =    \"" << mf::pop_back<Numbers_Literal,7>::type::data() << "\"" << std::endl;
    std::cout << "pop_back_n(8) =    \"" << mf::pop_back<Numbers_Literal,8>::type::data() << "\"" << std::endl;
    std::cout << "pop_back_n(9) =    \"" << mf::pop_back<Numbers_Literal,9>::type::data() << "\"" << std::endl;
    std::cout << "pop_back_n(10) =   \"" << mf::pop_back<Numbers_Literal,10>::type::data() << "\"" << std::endl;
    std::cout << "pop_back_n(11) =   \"" << mf::pop_back<Numbers_Literal,11>::type::data() << "\"" << std::endl;

    std::cout << std::endl;
    std::cout << "start =            \"" << Numbers_Literal::data() << "\"" << std::endl;
    std::cout << "pop_front =        \"" << mf::pop_front<Numbers_Literal>::type::data() << "\"" << std::endl;
    std::cout << "pop_front_n(0) =   \"" << mf::pop_front<Numbers_Literal,0>::type::data() << "\"" << std::endl;
    std::cout << "pop_front_n(1) =   \"" << mf::pop_front<Numbers_Literal,1>::type::data() << "\"" << std::endl;
    std::cout << "pop_front_n(2) =   \"" << mf::pop_front<Numbers_Literal,2>::type::data() << "\"" << std::endl;
    std::cout << "pop_front_n(3) =   \"" << mf::pop_front<Numbers_Literal,3>::type::data() << "\"" << std::endl;
    std::cout << "pop_front_n(4) =   \"" << mf::pop_front<Numbers_Literal,4>::type::data() << "\"" << std::endl;
    std::cout << "pop_front_n(5) =   \"" << mf::pop_front<Numbers_Literal,5>::type::data() << "\"" << std::endl;
    std::cout << "pop_front_n(6) =   \"" << mf::pop_front<Numbers_Literal,6>::type::data() << "\"" << std::endl;
    std::cout << "pop_front_n(7) =   \"" << mf::pop_front<Numbers_Literal,7>::type::data() << "\"" << std::endl;
    std::cout << "pop_front_n(8) =   \"" << mf::pop_front<Numbers_Literal,8>::type::data() << "\"" << std::endl;
    std::cout << "pop_front_n(9) =   \"" << mf::pop_front<Numbers_Literal,9>::type::data() << "\"" << std::endl;
    std::cout << "pop_front_n(10) =  \"" << mf::pop_front<Numbers_Literal,10>::type::data() << "\"" << std::endl;
    std::cout << "pop_front_n(11) =  \"" << mf::pop_front<Numbers_Literal,11>::type::data() << "\"" << std::endl;

    std::cout << std::endl;
    std::cout << "Substrings of pos = X, len = 1" << std::endl;
    std::cout << "start =            \"" << Numbers_Literal::data() << "\"" << std::endl;
    std::cout << "substring(0,1) =   \"" << mf::substring<Numbers_Literal,0,1>::type::data() << "\"" << std::endl;
    std::cout << "substring(1,1) =   \"" << mf::substring<Numbers_Literal,1,1>::type::data() << "\"" << std::endl;
    std::cout << "substring(2,1) =   \"" << mf::substring<Numbers_Literal,2,1>::type::data() << "\"" << std::endl;
    std::cout << "substring(3,1) =   \"" << mf::substring<Numbers_Literal,3,1>::type::data() << "\"" << std::endl;
    std::cout << "substring(4,1) =   \"" << mf::substring<Numbers_Literal,4,1>::type::data() << "\"" << std::endl;
    std::cout << "substring(5,1) =   \"" << mf::substring<Numbers_Literal,5,1>::type::data() << "\"" << std::endl;
    std::cout << "substring(6,1) =   \"" << mf::substring<Numbers_Literal,6,1>::type::data() << "\"" << std::endl;
    std::cout << "substring(7,1) =   \"" << mf::substring<Numbers_Literal,7,1>::type::data() << "\"" << std::endl;
    std::cout << "substring(8,1) =   \"" << mf::substring<Numbers_Literal,8,1>::type::data() << "\"" << std::endl;
    std::cout << "substring(9,1) =   \"" << mf::substring<Numbers_Literal,9,1>::type::data() << "\"" << std::endl;
    std::cout << "substring(10,1) =  \"" << mf::substring<Numbers_Literal,10,1>::type::data() << "\"" << std::endl;
    std::cout << "substring(11,1) =  \"" << mf::substring<Numbers_Literal,11,1>::type::data() << "\"" << std::endl;

    std::cout << std::endl;
    std::cout << "Substrings of pos = X, len = 3" << std::endl;
    std::cout << "start =            \"" << Numbers_Literal::data() << "\"" << std::endl;
    std::cout << "substring(0,3) =   \"" << mf::substring<Numbers_Literal,0,3>::type::data() << "\"" << std::endl;
    std::cout << "substring(1,3) =   \"" << mf::substring<Numbers_Literal,1,3>::type::data() << "\"" << std::endl;
    std::cout << "substring(2,3) =   \"" << mf::substring<Numbers_Literal,2,3>::type::data() << "\"" << std::endl;
    std::cout << "substring(3,3) =   \"" << mf::substring<Numbers_Literal,3,3>::type::data() << "\"" << std::endl;
    std::cout << "substring(4,3) =   \"" << mf::substring<Numbers_Literal,4,3>::type::data() << "\"" << std::endl;
    std::cout << "substring(5,3) =   \"" << mf::substring<Numbers_Literal,5,3>::type::data() << "\"" << std::endl;
    std::cout << "substring(6,3) =   \"" << mf::substring<Numbers_Literal,6,3>::type::data() << "\"" << std::endl;
    std::cout << "substring(7,3) =   \"" << mf::substring<Numbers_Literal,7,3>::type::data() << "\"" << std::endl;
    std::cout << "substring(8,3) =   \"" << mf::substring<Numbers_Literal,8,3>::type::data() << "\"" << std::endl;
    std::cout << "substring(9,3) =   \"" << mf::substring<Numbers_Literal,9,3>::type::data() << "\"" << std::endl;
    std::cout << "substring(10,3) =  \"" << mf::substring<Numbers_Literal,10,3>::type::data() << "\"" << std::endl;
    std::cout << "substring(11,3) =  \"" << mf::substring<Numbers_Literal,11,3>::type::data() << "\"" << std::endl;

    std::cout << std::endl;

    using Advanced_String1 = DCLIB_LITYPE_STRING("why haven't I tested one with spaces yet?");
    std::cout << Advanced_String1() << std::endl;

    using Advanced_String2 = DCLIB_LITYPE_STRING("what about ""concatenated literals?");
    std::cout << Advanced_String2() << std::endl;

    using Advanced_String3 = DCLIB_LITYPE_STRING("how about " "space seperated concatenated literals?");
    std::cout << Advanced_String3() << std::endl;


    using Advanced_String4 = DCLIB_LITYPE_STRING("how ""far " "can"    " we "   "take "   "this?");
    std::cout << Advanced_String4() << std::endl;
}
