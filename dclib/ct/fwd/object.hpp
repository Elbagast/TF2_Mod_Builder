#ifndef DCLIB_CT_FWD_OBJECT_HPP
#define DCLIB_CT_FWD_OBJECT_HPP

#include <dclib/ct/v1/fwd/object.hpp>

namespace dclib
{
  namespace ct
  {
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

      //---------------------------------------------------------------------------
      // Metafunction object_member<T,I>
      //---------------------------------------------------------------------------
      // For a given object type retrieve the member type at the supplied index.
      template <typename T, std::size_t I>
      using object_member = v1::mf::object_member<T,I>;
    } // namespace mf
  } // namespace ct
} // namespace dclib

#endif // DCLIB_CT_FWD_OBJECT_HPP