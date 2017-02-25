#ifndef DCLIB_LITYPE_V1_FWD_INTEGER_CLASS_HPP
#define DCLIB_LITYPE_V1_FWD_INTEGER_CLASS_HPP

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
      struct integer;

    } // namespace v1
  } // namespace litype
} // namespace dclib


#endif // DCLIB_LITYPE_V1_FWD_INTEGER_CLASS_HPP
