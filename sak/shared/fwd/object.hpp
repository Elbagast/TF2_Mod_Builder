#ifndef SAK_SHARED_FWD_OBJECT_HPP
#define SAK_SHARED_FWD_OBJECT_HPP

#include <dclib/ct/fwd/object.hpp>
#include <dclib/ct/fwd/member.hpp>
#include <dclib/litype/string.hpp>
class QString;

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::member
    //---------------------------------------------------------------------------
    template <typename N, typename T>
    using member = dclib::ct::member<N,T>;

    //---------------------------------------------------------------------------
    // shared::object
    //---------------------------------------------------------------------------
    template <typename T, typename... Args>
    using object = dclib::ct::object<T,Args...>;

    namespace mf
    {
      //---------------------------------------------------------------------------
      // Metafunction is_member<T>
      //---------------------------------------------------------------------------
      // Identify whether or not a type is a member.
      template <typename T>
      using is_member = dclib::ct::mf::is_member<T>;

      //---------------------------------------------------------------------------
      // Metafunction is_object<T>
      //---------------------------------------------------------------------------
      // Identify whether or not a type is an object.
      template <typename T>
      using is_object = dclib::ct::mf::is_object<T>;

      //---------------------------------------------------------------------------
      // Metafunction object_member<T,I>
      //---------------------------------------------------------------------------
      // For a given object type retrieve the member type at the supplied index.
      template <typename T, std::size_t I>
      using object_member = dclib::ct::mf::object_member<T,I>;
    } // namespace mf
  }

  namespace file
  {
    using object =
    shared::object
    <
    DCLIB_LITYPE_STRING(u8"File")
    ,shared::member<DCLIB_LITYPE_STRING(u8"Name"),QString>
    ,shared::member<DCLIB_LITYPE_STRING(u8"Description"),QString>
    ,shared::member<DCLIB_LITYPE_STRING(u8"Buildpath"),QString>
    ,shared::member<DCLIB_LITYPE_STRING(u8"Sourcepath"),QString>
    >;
  }

}

#endif // SAK_SHARED_FWD_OBJECT_HPP
