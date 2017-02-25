#include "file_manager.hpp"
#include "file.hpp"
#include "file_interface.hpp"

//---------------------------------------------------------------------------
// using File_Manager_Types
//---------------------------------------------------------------------------
// Allows use of:
template generic::Extended_Manager_Types<generic::Uint32ID_Manager, sak::File, sak::File_Interface_Traits>;

//---------------------------------------------------------------------------
// using File_Manager
//---------------------------------------------------------------------------
// Allows use of:
template generic::Extended_Manager<generic::Uint32ID_Manager, sak::File, sak::File_Interface_Traits>;

//---------------------------------------------------------------------------
// using File_Handle
//---------------------------------------------------------------------------
// Allows use of:
template generic::Extended_Handle<generic::Uint32ID_Manager, sak::File, sak::File_Interface_Traits>;


bool sak::File_Handle_Less_By_Name::operator()(File_Handle const& a_lhs, File_Handle const& a_rhs) const
{
    return a_lhs.cget().cget_name() < a_rhs.cget().cget_name();
}
