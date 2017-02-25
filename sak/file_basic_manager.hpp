#ifndef FILE_BASIC_MANAGER_HPP
#define FILE_BASIC_MANAGER_HPP

#include "fwd_file.hpp"
#include "file.hpp"
#include "../generic/uintid.hpp"
#include "../generic/uintid_manager.hpp"
#include "../generic/manager.hpp"

namespace sak
{
    //---------------------------------------------------------------------------
    // using File_Basic_Manager
    //---------------------------------------------------------------------------
    // Allows use of:
    //using File_Basic_Manager = generic::Manager<generic::Uint32ID_Manager, File>;

    //---------------------------------------------------------------------------
    // using File_Basic_Handle
    //---------------------------------------------------------------------------
    // Allows use of:
    //using File_Basic_Handle = generic::Handle<generic::Uint32ID_Manager, File>;
}

#endif // FILE_BASIC_MANAGER_HPP
