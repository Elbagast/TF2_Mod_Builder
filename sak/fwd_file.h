#ifndef FWD_FILE_H
#define FWD_FILE_H

#include "../generic/fwd_uintid.h"
#include "../generic/fwd_uintid_manager.h"
#include "../generic/fwd_manager.h"
#include "../generic/fwd_extended_manager.h"

namespace sak
{
    //---------------------------------------------------------------------------
    // sak::File and related forward declarations
    //---------------------------------------------------------------------------
    // Since lots of components are coming from templates, we get all the related
    // names together and forard declare them. The includes required to use these
    // symbols are included below.

    //#include "file.h"
    class File;

    //#include "file_manager.h"
    using File_Basic_Manager = generic::Manager<generic::Uint32ID_Manager, File>;
    using File_Basic_Handle = generic::Handle<generic::Uint32ID_Manager, File>;

    //#include "file_interface_traits.h"
    class File_Const_Interface;
    class File_Interface;
    class File_Interface_Traits;

    //#include "file_manager.h"
    using File_Manager = generic::Extended_Manager<generic::Uint32ID_Manager, File, File_Interface_Traits>;
    using File_Handle = generic::Extended_Handle<generic::Uint32ID_Manager, File, File_Interface_Traits>;
}

#endif // FWD_FILE_H
