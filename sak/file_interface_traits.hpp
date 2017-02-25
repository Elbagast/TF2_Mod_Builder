#ifndef FILE_INTERFACE_TRAITS_HPP
#define FILE_INTERFACE_TRAITS_HPP

#include "fwd_file.hpp"
#include "../generic/extended_manager.hpp"

namespace sak
{
    class Project;

    class File_Interface_Traits :
            public File_Manager_Types
    {
    public:
        using interface_type = File_Interface;
        using const_interface_type = File_Const_Interface;

        File_Interface_Traits();
        explicit File_Interface_Traits(Project* a_project);

        interface_type get(handle_type const& a_handle, basic_handle_type& a_data);
        const_interface_type cget(handle_type const& a_handle, basic_handle_type const& a_data) const;
    private:
        Project* m_project;
    };
}


#endif // FILE_INTERFACE_TRAITS_HPP
