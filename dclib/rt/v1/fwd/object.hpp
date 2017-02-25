#ifndef DCLIB_RT_V1_FWD_OBJECT_HPP
#define DCLIB_RT_V1_FWD_OBJECT_HPP

namespace dclib
{
  namespace rt
  {
    namespace v1
    {
      //---------------------------------------------------------------------------
      // abstract::object
      //---------------------------------------------------------------------------
      // Abstract class that describes the runtime interface of objects.
      namespace abstract
      {
        template <typename C>
        class object;
      }

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
  } // namespace rt
} // namespace dclib

#endif // DCLIB_RT_V1_FWD_OBJECT_HPP
