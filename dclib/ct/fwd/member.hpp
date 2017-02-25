#ifndef DCLIB_CT_FWD_MEMBER_HPP
#define DCLIB_CT_FWD_MEMBER_HPP

#include <dclib/ct/v1/fwd/member.hpp>

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
  } // namespace ct
} // namespace dclib

#endif // DCLIB_CT_FWD_MEMBER_HPP
