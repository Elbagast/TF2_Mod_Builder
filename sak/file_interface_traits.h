#ifndef FILE_INTERFACE_TRAITS_H
#define FILE_INTERFACE_TRAITS_H

#include "file_basic_manager.h"
class QString;
#include "common_data_interface_traits.h"

namespace sak
{
    class Project;

    class File_Const_Interface
    {
    public:
        explicit File_Const_Interface(File_Basic_Handle const& a_handle);

        QString const& cget_name() const;
        QString const& cget_description() const;

    protected:
        File_Basic_Handle m_handle;
    };

    class File_Interface :
            public File_Const_Interface
    {
    public:
        explicit File_Interface(File_Basic_Handle const& a_handle, Project* a_project);

        void set_name(QString const& a_name);
        void set_description(QString const& a_description);
    private:
        Project* m_project;
    };


    class File_Interface_Traits
    {
    public:
        using basic_handle_type = File_Basic_Handle;

        using interface_type = File_Interface;
        using const_interface_type = File_Const_Interface;

        explicit File_Interface_Traits(Project* a_project);

        interface_type get(basic_handle_type& a_ref);
        const_interface_type cget(basic_handle_type const& a_ref) const;
    private:
        Project* m_project;
    };
}


#endif // FILE_INTERFACE_TRAITS_H
