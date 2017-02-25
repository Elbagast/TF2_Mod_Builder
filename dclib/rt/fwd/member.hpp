#ifndef DCLIB_RT_FWD_MEMBER_HPP
#define DCLIB_RT_FWD_MEMBER_HPP

#include <dclib/rt/v1/fwd/member.hpp>

namespace dclib
{
  namespace rt
  {
    //---------------------------------------------------------------------------
    // abstract::member<Char_Type>
    //---------------------------------------------------------------------------
    // Abstract class that describes the runtime interface of members.
    namespace abstract
    {
      template <typename C>
      using member = v1::abstract::member<C>;
    }


    //---------------------------------------------------------------------------
    // member<Name, T>
    //---------------------------------------------------------------------------
    // Data class member. Associates a type with a compile-time fixeed name.
    // Acceptable template instantiations:
    //
    // class member<litype::string<...>, T>
    //
    // Member does not link to any capacity for a typestring because the user may
    // be using this to hold a type that is not truely a given type, but an
    // abstraction to one e.g. a handle.

    template <typename S_Name, typename T>
    using member = v1::member<S_Name, T>;

    namespace mf
    {
      //---------------------------------------------------------------------------
      // Metafunction is_member<T>
      //---------------------------------------------------------------------------
      // Identify whether or not a type is a member.
      template <typename T>
      using is_member = v1::mf::is_member<T>;
    } // namespace mf
  } // namespace rt
} // namespace dclib

#endif // DCLIB_RT_FWD_MEMBER_HPP
