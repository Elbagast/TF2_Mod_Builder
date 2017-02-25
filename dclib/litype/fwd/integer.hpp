#ifndef DCLIB_LITYPE_FWD_INTEGER_HPP
#define DCLIB_LITYPE_FWD_INTEGER_HPP

#include <dclib/litype/v1/fwd/integer_class.hpp>

namespace dclib
{
  namespace litype
  {
    //---------------------------------------------------------------------------
    // ineger<T, Value>
    //---------------------------------------------------------------------------
    // Class that wraps an integer literal making it useable as a template parameter
    // type.
    template <typename T, T Value>
    using integer = v1::integer<T, Value>;

  } // namespace litype
} // namespace opliteral

#endif // DCLIB_LITYPE_FWD_INTEGER_HPP
