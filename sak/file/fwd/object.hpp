#ifndef SAK_FILE_FWD_DATA_HPP
#define SAK_FILE_FWD_DATA_HPP

#include <sak/shared/fwd/object.hpp>
#include <dclib/litype/string.hpp>
class QString;

namespace sak
{
  namespace file
  {
    //---------------------------------------------------------------------------
    // file::object
    //---------------------------------------------------------------------------
    // Forward declare the file data class
    /*
    Common Data:
    - Name
    - Description
    Unique Data:
    - Build target
        - Game location
        or
        - Game file to replace
        or
        - Inform user that it will replace a game file without storing whether or not it will.
    - Source file
        - File path
        - Edited by having the user browse for a file with a valid extension.
        - When selected ask the user whether we are going to cache the file or not.
    */

    //---------------------------------------------------------------------------
    // shared::member
    //---------------------------------------------------------------------------
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


#endif // SAK_FILE_FWD_DATA_HPP
