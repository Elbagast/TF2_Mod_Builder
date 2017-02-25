#ifndef DCLIB_LITYPE_V1_FWD_FLOAT_CLASS_HPP
#define DCLIB_LITYPE_V1_FWD_FLOAT_CLASS_HPP

namespace dclib
{
  namespace litype
  {
    namespace v1
    {
      using float_mantissa_type = unsigned long long;
      using float_exponent_type = int;
      using float_sign_type = bool;


      //---------------------------------------------------------------------------
      // floating_point<T, Mantissa, Exponent, Sign>
      //---------------------------------------------------------------------------
      // Class that wraps a float literal making it useable as a template parameter
      // type.

      template
      <
          typename T_Float
         ,float_mantissa_type Mantissa
         ,float_exponent_type Exponent
         ,float_sign_type Sign
      >
      class floating_point;

    } // namespace v1
  } // namespace litype
} // namespace dclib

#endif // DCLIB_LITYPE_V1_FWD_FLOAT_CLASS_HPP
