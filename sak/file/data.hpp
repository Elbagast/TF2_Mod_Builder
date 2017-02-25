#ifndef SAK_FILE_DATA_HPP
#define SAK_FILE_DATA_HPP

#include "fwd/data.hpp"
#include <dclib/ct/object.hpp>
#include <dclib/ct/member.hpp>
#include <QString>

namespace sak
{
  namespace file
  {
    //---------------------------------------------------------------------------
    // file::data
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
  }
}


#endif // SAK_FILE_DATA_HPP
