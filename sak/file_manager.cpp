#include "file_manager.h"

bool sak::File_Handle_Less_By_Name::operator()(File_Handle const& a_lhs, File_Handle const& a_rhs) const
{
    return a_lhs.cget().cget_name() < a_rhs.cget().cget_name();
}
