#ifndef FLOAT_MACRO_HPP
#define FLOAT_MACRO_HPP

#include "float_class.hpp"
#include "float_tools.hpp"
#include "string_macro.hpp"

#define DCLIB_LITYPE_V1_FLOAT(_literal_float) \
    dclib::litype::v1::Float_String_Literal_Analyser<decltype(_literal_float), DCLIB_LITYPE_V1_STRING(#_literal_float) >::type

#endif // FLOAT_MACRO_HPP
