#include "test_float.hpp"
#include <dclib/litype/floating_point.hpp>
#include <dclib/meta/power.hpp>
#include <iostream>
#include <iomanip>

// verify that all the different ways you can write zero are dealt with correctly
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(.0), dclib::litype::floating_point<double,0,0,0> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(0.), dclib::litype::floating_point<double,0,0,0> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(0.0), dclib::litype::floating_point<double,0,0,0> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(0.e0), dclib::litype::floating_point<double,0,0,0> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(0.e-0), dclib::litype::floating_point<double,0,0,0> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(.0e0), dclib::litype::floating_point<double,0,0,0> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(.0e-0), dclib::litype::floating_point<double,0,0,0> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(0.0e0), dclib::litype::floating_point<double,0,0,0> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(0.0e-0), dclib::litype::floating_point<double,0,0,0> >::value,"Bad float analysis");

// same with negative zeros
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(-.0), dclib::litype::floating_point<double,0,0,1> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(-0.), dclib::litype::floating_point<double,0,0,1> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(-0.0), dclib::litype::floating_point<double,0,0,1> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(-0.e0), dclib::litype::floating_point<double,0,0,1> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(-0.e-0), dclib::litype::floating_point<double,0,0,1> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(-.0e0), dclib::litype::floating_point<double,0,0,1> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(-.0e-0), dclib::litype::floating_point<double,0,0,1> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(-0.0e0), dclib::litype::floating_point<double,0,0,1> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(-0.0e-0), dclib::litype::floating_point<double,0,0,1> >::value,"Bad float analysis");

static_assert(std::is_same<DCLIB_LITYPE_FLOAT(1.0e1f), dclib::litype::floating_point<float,1,1,0> >::value,"Bad float analysis");
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(1.0e1l), dclib::litype::floating_point<long double,1,1,0> >::value,"Bad float analysis");

// This works because the template generation works but it doesn't actually use the type.
static_assert(std::is_same<DCLIB_LITYPE_FLOAT(1), dclib::litype::floating_point<int,1,0,0> >::value,"Bad float analysis");


using float_string = DCLIB_LITYPE_V1_STRING(".0");
using float_literal = dclib::litype::v1::Float_String_Literal_Analyser<decltype(.0), float_string >::type;

static_assert(std::is_same<
float_literal,
dclib::litype::floating_point<double,0,0,0>
>::value,"Bad float analysis");


void dclib::litype::test_float()
{
    // This doesn't work because input type is tested and literal 1 is type int
    //using Float_Input_Int = DCLIB_LITYPE_FLOAT(1);
    //std::cout <<Float_Input_Int::exponent() << std::endl;

    std::cout << "sizeof(float): " << sizeof(float) << std::endl;
    std::cout << "sizeof(double): " << sizeof(double) << std::endl;
    std::cout << "sizeof(long double): " << sizeof(long double) << std::endl;

    std::cout << "sizeof(mantissa_type): " << sizeof(dclib::litype::float_mantissa_type) << std::endl;
    std::cout << "sizeof(exponent_type): " << sizeof(dclib::litype::float_exponent_type) << std::endl;
    std::cout << "sizeof(sign_type): " << sizeof(dclib::litype::float_sign_type) << std::endl;

    static_assert(DCLIB_LITYPE_FLOAT(1.234l)::sign() == false,"");
    static_assert(DCLIB_LITYPE_FLOAT(-1.234l)::sign() == true,"");

    static_assert(DCLIB_LITYPE_FLOAT(0.0)::sign() == false,"");
    static_assert(DCLIB_LITYPE_FLOAT(-0.0)::sign() == true,"");



    using TestFloatString1 = DCLIB_LITYPE_V1_STRING("0012.34500e-05");
    using Analyser1 = v1::Float_String_Literal_Analyser<float,TestFloatString1>;

    std::cout << "Raw:          \"" << TestFloatString1::data() << "\"" << std::endl;
    std::cout << "Sign:         \"" << Analyser1::sign << "\"" << std::endl;
    std::cout << "Mantissa:  \"" << Analyser1::mantissa << "\"" << std::endl;
    std::cout << "Exponent:     \"" << Analyser1::exponent << "\"" << std::endl;
    std::cout << std::endl;

    std::cout << "value_type:                                   \""
              << (std::is_same<Analyser1::value_type,float>::value ? "float" :
                 std::is_same<Analyser1::value_type,double>::value ? "double" :
                 std::is_same<Analyser1::value_type,long double>::value ? "long double" :
                 "bad type") << "\"" << std::endl;
    std::cout << "input_type:                                   \"" << Analyser1::input_type::data() << std::endl;
    std::cout << "clean_input_type:                             \"" << Analyser1::clean_input_type::data() << std::endl;
    std::cout << "signed_mantissa_string_type:               \"" << Analyser1::signed_mantissa_string_type::data() << "\"" << std::endl;
    std::cout << "signed_exponent_string_type:                  \"" << Analyser1::signed_exponent_string_type::data() << "\"" << std::endl;
    std::cout << "unsigned_mantissa_string_type:             \"" << Analyser1::unsigned_mantissa_string_type::data() << "\"" << std::endl;
    std::cout << "front_clean_unsigned_mantissa_string_type: \"" << Analyser1::front_clean_unsigned_mantissa_string_type::data() << "\"" << std::endl;
    std::cout << "clean_unsigned_mantissa_string_type:       \"" << Analyser1::clean_unsigned_mantissa_string_type::data() << "\"" << std::endl;
    std::cout << "exponent_sign:                                \"" << Analyser1::exponent_sign << "\"" << std::endl;
    std::cout << "exponent_correction:                          \"" << Analyser1::exponent_correction << "\"" << std::endl;
    std::cout << "exponent_raw:                                 \"" << Analyser1::exponent_raw << "\"" << std::endl;
    std::cout << "exponent:                                     \"" << Analyser1::exponent << "\"" << std::endl;

   // std::cout << "reversed_digits_string:  \"" << Analyser1::reversed_digits_string::data() << "\"" << std::endl;
    std::cout << std::endl;

    using TestFloatString2 = DCLIB_LITYPE_V1_STRING("-0012.34500e-05f");
    using Analyser2 = v1::Float_String_Literal_Analyser<float,TestFloatString2>;

    std::cout << "Raw:          \"" << TestFloatString2::data() << "\"" << std::endl;
    std::cout << "Sign:         \"" << Analyser2::sign << std::endl;
    std::cout << "Mantissa:  \"" << Analyser2::mantissa << std::endl;
    std::cout << "Exponent:     \"" << Analyser2::exponent << std::endl;
    std::cout << std::endl;
/*
    std::cout << "Raw:                     \"" << TestFloatString2::data() << "\"" << std::endl;
    std::cout << "Sign:                    \"" << Analyser2::sign << std::endl;
    std::cout << "signless_string_type:    \"" << Analyser2::signless_string_type::data() << "\"" << std::endl;
    std::cout << "mantissa_string_type: \"" << Analyser2::mantissa_string_type::data() << "\"" << std::endl;
    std::cout << "exponent_string_type:    \"" << Analyser2::exponent_string_type::data() << "\"" << std::endl;
    std::cout << "mantissa as string:   \"" << Analyser2::mantissa_integer_string_type::data() << "\"" << std::endl;
    std::cout << "mantissa as integer:  \"" << Analyser2::mantissa << "\"" << std::endl;
    std::cout << "e_position:              \"" << Analyser2::e_position << "\"" << std::endl;
    //std::cout << "mantissa_integer:     \"" << Analyser2::reversed_digits_string::data() << "\"" << std::endl;
    std::cout << std::endl;
*/
    using TestFloatString3 = DCLIB_LITYPE_V1_STRING("0.0000e12");
    using Analyser3 = v1::Float_String_Literal_Analyser<float,TestFloatString3>;
    std::cout << "mantissa as integer:  \"" << Analyser3::mantissa << "\"" << std::endl;


    std::cout << Analyser3::type::value() << std::endl;

    using Float_Test_Type = DCLIB_LITYPE_FLOAT(1234.5678e10f);
    std::cout << "value as float:  \"" << std::setprecision(20) << std::scientific << Float_Test_Type::value() << "\"" << std::endl;

    using Double_Test_Type = DCLIB_LITYPE_FLOAT(-00001234.5678e10);
    std::cout <<  "value as float:  \"" << std::setprecision(20) << std::scientific << Double_Test_Type::value() << "\"" << std::endl;

    using LDouble_Test_Type = DCLIB_LITYPE_FLOAT(1234.5678e-1l);
    std::cout <<  "value as float:  \"" << std::setprecision(20) << std::scientific << LDouble_Test_Type::value() << "\"" << std::endl;


    std::cout << meta::mf::power<int, 10, 0>::value << std::endl;
    std::cout << meta::mf::power<int, 10, 1>::value << std::endl;
    std::cout << meta::mf::power<int, 10, 2>::value << std::endl;
    std::cout << meta::mf::power<int, 10, 3>::value << std::endl;

}
