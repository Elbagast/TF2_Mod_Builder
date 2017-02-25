#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include "fwd_file.hpp"
#include "file.hpp"
#include "file_basic_manager.hpp"
#include "file_interface_traits.hpp"
#include "../generic/uintid.hpp"
#include "../generic/uintid_manager.hpp"
#include "../generic/extended_manager.hpp"

namespace sak
{
    //---------------------------------------------------------------------------
    // using File_Manager_Types
    //---------------------------------------------------------------------------
    // Allows use of:
    //using File_Manager_Types = generic::Extended_Manager_Types<generic::Uint32ID_Manager, File, File_Interface_Traits>;

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

    class File_Handle_Less_By_Name
    {
    public:
        bool operator()(File_Handle const& a_lhs, File_Handle const& a_rhs) const;
    };
}

#endif // FILE_MANAGER_HPP
