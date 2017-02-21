#include "file_interface.h"

sak::File_Const_Interface::File_Const_Interface(File_Handle const& a_handle, File_Basic_Handle const& a_data):
    common_interface_type(a_handle, a_data)
{}


sak::File_Interface::File_Interface(File_Handle const& a_handle, File_Basic_Handle& a_data, Project* a_project):
    common_interface_type(a_handle, a_data, a_project)
{}
