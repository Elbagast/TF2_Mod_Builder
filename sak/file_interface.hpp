#ifndef FILE_INTERFACE_HPP
#define FILE_INTERFACE_HPP

#include "fwd_file.hpp"
#include "common_data_interface.hpp"

namespace sak
{
    class Project;

    class File_Const_Interface :
            public Common_Data_Const_Interface<File_Handle, File_Basic_Handle>
    {
    public:
        File_Const_Interface(File_Handle const& a_handle, File_Basic_Handle const& a_data);

        QString const& cget_buildpath() const;
        QString const& cget_sourcepath() const;
    };

    class File_Interface :
            public Common_Data_Interface<File_Handle, File_Basic_Handle>
    {
    public:
        File_Interface(File_Handle const& a_handle, File_Basic_Handle& a_data, Project* a_project);

        void set_buildpath(QString const& a_buildpath);
        void set_sourcepath(QString const& a_sourcepath);
    };
}
#endif // FILE_INTERFACE_HPP
