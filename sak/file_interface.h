#ifndef FILE_INTERFACE_H
#define FILE_INTERFACE_H

#include "fwd_file.h"
#include "common_data_interface.h"

namespace sak
{
    class Project;

    class File_Const_Interface :
            public Common_Data_Const_Interface<File_Handle, File_Basic_Handle>
    {
    public:
        File_Const_Interface(File_Handle const& a_handle, File_Basic_Handle const& a_data);
    };

    class File_Interface :
            public Common_Data_Interface<File_Handle, File_Basic_Handle>
    {
    public:
        File_Interface(File_Handle const& a_handle, File_Basic_Handle& a_data, Project* a_project);
    };
}
#endif // FILE_INTERFACE_H
