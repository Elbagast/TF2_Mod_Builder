#ifndef DCLIB_LITYPE_V1_INTEGER_MACRO_HPP
#define DCLIB_LITYPE_V1_INTEGER_MACRO_HPP

#include "integer_class.hpp"

#define DCLIB_LITYPE_V1_INTEGER(_integer_literal) dclib::litype::v1::integer<decltype(_integer_literal), _integer_literal>

#endif // DCLIB_LITYPE_V1_INTEGER_MACRO_HPP
