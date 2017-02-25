#include "file_command.hpp"
#include "file.hpp"
#include "file_manager.hpp"
#include "project.hpp"

namespace sak
{
    namespace
    {

        template <typename T>
        class File_Data_Command_Get_Set_Base:
                public generic::abstract::Command
        {
        public:
            using inherited_type = generic::abstract::Command;
            using value_type = T;
            using handle_type = File_Handle;
            using basic_handle_type = File_Basic_Handle;

            File_Data_Command_Get_Set_Base(handle_type const& a_handle, Project* a_project, value_type const& a_new, value_type const& a_old):
                inherited_type(),
                m_handle{a_handle},
                m_project{a_project},
                m_new_value{a_new},
                m_old_value{a_old}
            {
            }
            ~File_Data_Command_Get_Set_Base() override = default;

        protected:
            void do_execute() override = 0;
            void do_unexecute() override = 0;

            handle_type m_handle;
            Project* m_project;
            value_type m_new_value;
            value_type m_old_value;
        };

        class File_Data_Command_Get_Set_Buildpath :
                public File_Data_Command_Get_Set_Base<QString>
        {
        public:
            using inherited_type = File_Data_Command_Get_Set_Base<QString>;

            File_Data_Command_Get_Set_Buildpath(QString const& a_value, handle_type const& a_handle, Project* a_project):
                inherited_type(a_handle, a_project, a_value, a_handle.cget_basic_handle().cget().cget_buildpath())
            {}

            ~File_Data_Command_Get_Set_Buildpath() override = default;
        protected:
            void do_execute() override final
            {
                // open the handle, then the common data, then set that part of it.
                m_handle.get_basic_handle().get().set_buildpath(m_new_value);
                m_project->get_signalbox()->data_changed_at(m_handle,0); // outbound signal to project
            }
            void do_unexecute() override final
            {
                // open the handle, then the common data, then set that part of it.
                m_handle.get_basic_handle().get().set_buildpath(m_old_value);
                m_project->get_signalbox()->data_changed_at(m_handle,0); // outbound signal to project
            }
        };

        class File_Data_Command_Get_Set_Sorucepath :
                public File_Data_Command_Get_Set_Base<QString>
        {
        public:
            using inherited_type = File_Data_Command_Get_Set_Base<QString>;

            File_Data_Command_Get_Set_Sorucepath(QString const& a_value, handle_type const& a_handle, Project* a_project):
                inherited_type(a_handle, a_project, a_value, a_handle.cget_basic_handle().cget().cget_sourcepath())
            {}

            ~File_Data_Command_Get_Set_Sorucepath() override = default;
        protected:
            void do_execute() override final
            {
                // open the handle, then the common data, then set that part of it.
                m_handle.get_basic_handle().get().set_sourcepath(m_new_value);
                m_project->get_signalbox()->data_changed_at(m_handle, 1); // outbound signal to project
            }
            void do_unexecute() override final
            {
                // open the handle, then the common data, then set that part of it.
                m_handle.get_basic_handle().get().set_sourcepath(m_old_value);
                m_project->get_signalbox()->data_changed_at(m_handle,1); // outbound signal to project
            }
        };
    }
}



std::unique_ptr<generic::abstract::Command> sak::make_command_set_buildpath(QString const& a_value, File_Handle const& a_handle, Project* a_project)
{
    return std::unique_ptr<generic::abstract::Command>(std::make_unique<File_Data_Command_Get_Set_Buildpath>(a_value, a_handle, a_project).release());
}

std::unique_ptr<generic::abstract::Command> sak::make_command_set_sourcepath(QString const& a_value, File_Handle const& a_handle, Project* a_project)
{
    return std::unique_ptr<generic::abstract::Command>(std::make_unique<File_Data_Command_Get_Set_Sorucepath>(a_value, a_handle, a_project).release());
}
