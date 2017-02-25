#ifndef DCLIB_CT_V1_FWD_MEMBER_HPP
#define DCLIB_CT_V1_FWD_MEMBER_HPP

namespace dclib
{
  namespace ct
  {
    namespace v1
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
      class member;

      namespace mf
      {
        //---------------------------------------------------------------------------
        // Metafunction is_member<T>
        //---------------------------------------------------------------------------
        // Identify whether or not a type is a member.
        template <typename T>
        struct is_member;

        //---------------------------------------------------------------------------
        // Metafunction all_member<T>
        //---------------------------------------------------------------------------
        // Identify whether a typelist contains lonly member types.
        template <typename T>
        struct all_member;
      } // namespace mf
    } // namespace v1
  } // namespace ct
} // namespace dclib

#endif // DCLIB_CT_V1_FWD_MEMBER_HPP
