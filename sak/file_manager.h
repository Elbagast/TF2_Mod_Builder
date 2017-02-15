#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "fwd_file.h"
#include "file.h"
#include "file_interface_traits.h"
#include "../generic/uintid.h"
#include "../generic/uintid_manager.h"
#include "../generic/extended_manager.h"

namespace sak
{
    //---------------------------------------------------------------------------
    // using File_Manager
    //---------------------------------------------------------------------------
    // Allows use of:
    //using File_Manager = generic::Extended_Manager<generic::Uint32ID_Manager, File, File_Interface_Traits>;

    //---------------------------------------------------------------------------
    // using File_Handle
    //---------------------------------------------------------------------------
    // Allows use of:
    //using File_Handle = generic::Extended_Handle<generic::Uint32ID_Manager, File, File_Interface_Traits>;
}

#endif // FILE_MANAGER_H
