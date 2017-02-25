#ifndef DCLIB_RT_FWD_OBJECT_HPP
#define DCLIB_RT_FWD_OBJECT_HPP

#include <dclib/rt/v1/fwd/object.hpp>

namespace dclib
{
  namespace rt
  {
    //---------------------------------------------------------------------------
    // abstract::object
    //---------------------------------------------------------------------------
    // Abstract class that describes the runtime interface of objects.
    namespace abstract
    {
      template <typename C>
      using object = v1::abstract::object<C>;
    }

    //---------------------------------------------------------------------------
    // object<T1, Args...>
    //---------------------------------------------------------------------------
    // Data class object. Acceptable template instantiations:
    //
    // A Data type with members.
    // class object<litype::string<...>, members<...>...>
    //
    template <typename T, typename... Args>
    using object = v1::object<T,Args...>;
    namespace mf
    {
      //---------------------------------------------------------------------------
      // Metafunction is_object<T>
      //---------------------------------------------------------------------------
      // Identify whether or not a type is an object.
      template <typename T>
      using is_object = v1::mf::is_object<T>;
    } // namespace mf
  } // namespace rt
} // namespace dclib

#endif // DCLIB_RT_FWD_OBJECT_HPP
