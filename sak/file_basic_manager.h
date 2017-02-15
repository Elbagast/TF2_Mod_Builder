#ifndef FILE_BASIC_MANAGER_H
#define FILE_BASIC_MANAGER_H

#include "fwd_file.h"
#include "file.h"
#include "../generic/uintid.h"
#include "../generic/uintid_manager.h"
#include "../generic/manager.h"

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

#endif // FILE_BASIC_MANAGER_H
