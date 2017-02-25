#ifndef DCLIB_LITYPE_FWD_FLOATING_POINT_HPP
#define DCLIB_LITYPE_FWD_FLOATING_POINT_HPP

#include <dclib/litype/v1/fwd/float_class.hpp>

namespace dclib
{
  namespace litype
  {
    using float_mantissa_type = v1::float_mantissa_type;
    using float_exponent_type = v1::float_exponent_type;
    using float_sign_type = v1::float_sign_type;

    //---------------------------------------------------------------------------
    // ineger<T, Value>
    //---------------------------------------------------------------------------
    // Class that wraps an integer literal making it useable as a template parameter
    // type.
    template
    <
        typename T_Float
       ,float_mantissa_type Mantissa
       ,float_exponent_type Exponent
       ,float_sign_type Sign
    >
    using floating_point = v1::floating_point<T_Float,Mantissa,Exponent,Sign>;

  } // namespace litype
} // namespace opliteral

#endif // DCLIB_LITYPE_FWD_FLOATING_POINT_HPP
