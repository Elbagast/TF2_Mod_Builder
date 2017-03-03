#ifndef SAK_SHARED_OBJECT_HPP
#define SAK_SHARED_OBJECT_HPP

#include "fwd/object.hpp"
#include <dclib/ct/object.hpp>
#include <dclib/ct/member.hpp>
#include <dclib/litype/string.hpp>

#include <string>
#include <QString>

namespace sak
{
  namespace shared
  {
    namespace mf
    {
      //---------------------------------------------------------------------------
      // Metafunction object_member<T,I>
      //---------------------------------------------------------------------------
      // For a given object type retrieve the member type at the supplied index.
      template <typename T, std::size_t I>
      using object_member_t = typename object_member<T,I>::type;
    } // namespace mf
  }

  namespace file
  {
    //---------------------------------------------------------------------------
    // file::object
    //---------------------------------------------------------------------------
    // So it turns out we need to inherit this type to hide the huuuuuge name that
    // comes from having strings in the type.
    class object :
        public
    shared::object
    <
    DCLIB_LITYPE_STRING(u8"File")
    ,shared::member<DCLIB_LITYPE_STRING(u8"Name"),QString>
    ,shared::member<DCLIB_LITYPE_STRING(u8"Description"),QString>
    ,shared::member<DCLIB_LITYPE_STRING(u8"Buildpath"),QString>
    ,shared::member<DCLIB_LITYPE_STRING(u8"Sourcepath"),QString>
    ,shared::member<DCLIB_LITYPE_STRING(u8"Booltest"),bool>
    ,shared::member<DCLIB_LITYPE_STRING(u8"std_stringtest"),std::string>
    >
    {};
  }

  namespace texture
  {
    //---------------------------------------------------------------------------
    // texture::object
    //---------------------------------------------------------------------------
    // So it turns out we need to inherit this type to hide the huuuuuge name that
    // comes from having strings in the type.
    class object :
        public
    shared::object
    <
    DCLIB_LITYPE_STRING(u8"Texture")
    ,shared::member<DCLIB_LITYPE_STRING(u8"Name"),QString>
    ,shared::member<DCLIB_LITYPE_STRING(u8"Description"),QString>
    ,shared::member<DCLIB_LITYPE_STRING(u8"Buildpath"),QString>
    ,shared::member<DCLIB_LITYPE_STRING(u8"Sourcepath"),QString>
    >
    {};
  }
}

#endif // SAK_SHARED_OBJECT_HPP
