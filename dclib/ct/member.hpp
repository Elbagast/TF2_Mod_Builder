#ifndef DCLIB_CT_MEMBER_HPP
#define DCLIB_CT_MEMBER_HPP

#include <dclib/ct/fwd/member.hpp>
#include <dclib/ct/v1/member.hpp>

namespace dclib
{
  namespace ct
  {
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

  } // namespace ct
} // namespace dclib

#endif // DCLIB_CT_MEMBER_HPP
