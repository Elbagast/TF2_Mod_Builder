#ifndef DCLIB_LITYPE_V1_INTEGER_CLASS_HPP
#define DCLIB_LITYPE_V1_INTEGER_CLASS_HPP

#include "fwd/integer_class.hpp"
#include <type_traits>

namespace dclib
{
  namespace litype
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // ineger<T, Value>
      //---------------------------------------------------------------------------
      // Class that wraps an integer literal making it useable as a template parameter
      // type.
      template <typename T, T Value>
      struct integer : public std::integral_constant<T, Value> {};

    } // namespace v1
  } // namespace litype
} // namespace dclib


#endif // DCLIB_LITYPE_V1_INTEGER_CLASS_HPP
