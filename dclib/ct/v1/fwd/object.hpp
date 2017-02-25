#ifndef DCLIB_CT_V1_FWD_OBJECT_HPP
#define DCLIB_CT_V1_FWD_OBJECT_HPP

namespace dclib
{
  namespace ct
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // object<T1, Args...>
      //---------------------------------------------------------------------------
      // Data class object. Acceptable template instantiations:
      //
      // A Data type with members.
      // class object<litype::string<...>, members<...>...>
      //
      template <typename S_Type, typename...T_Members>
      class object;

      namespace mf
      {
        //---------------------------------------------------------------------------
        // Metafunction is_object<T>
        //---------------------------------------------------------------------------
        // Identify whether or not a type is an object.
        template <typename T>
        struct is_object;
      } // namespace mf

    } // namespace v1
  } // namespace ct
} // namespace dclib

#endif // DCLIB_CT_V1_FWD_OBJECT_HPP
