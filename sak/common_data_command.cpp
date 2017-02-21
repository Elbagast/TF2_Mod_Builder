#include "common_data_command.h"
#include "common_data.h"
#include "file.h"
#include "file_manager.h"
#include "project.h"

namespace sak
{
    namespace
    {

        template <typename H, typename BH, typename T>
        class Common_Data_Command_Get_Set_Base:
                public generic::abstract::Command
        {
        public:
            using inherited_type = generic::abstract::Command;
            using value_type = T;
            using handle_type = H;
            using basic_handle_type = BH;

            Common_Data_Command_Get_Set_Base(handle_type const& a_handle, Project* a_project, value_type const& a_new, value_type const& a_old):
                inherited_type(),
                m_handle{a_handle},
                m_project{a_project},
                m_new_value{a_new},
                m_old_value{a_old}
            {
            }
            ~Common_Data_Command_Get_Set_Base() override = default;

        protected:
            void do_execute() override = 0;
            void do_unexecute() override = 0;

            handle_type m_handle;
            Project* m_project;
            value_type m_new_value;
            value_type m_old_value;
        };


        template <typename H, typename BH>
        class Common_Data_Command_Set_Name :
                public Common_Data_Command_Get_Set_Base<H,BH, QString>
        {
        public:
            using inherited_type = Common_Data_Command_Get_Set_Base<H,BH, QString>;

            Common_Data_Command_Set_Name(QString const& a_value, handle_type const& a_handle, Project* a_project):
                inherited_type(a_handle, a_project, a_value, a_handle.cget_basic_handle().cget().cget_common_data().cget_name())
            {}

            ~Common_Data_Command_Set_Name() = default;
        protected:
            void do_execute() override final
            {
                // open the handle, then the common data, then set that part of it.
                m_handle.get_basic_handle().get().get_common_data().set_name(m_new_value);
                m_project->get_signalbox()->name_changed(m_handle); // outbound signal to project
            }
            void do_unexecute() override final
            {
                // open the handle, then the common data, then set that part of it.
                m_handle.get_basic_handle().get().get_common_data().set_name(m_old_value);
                m_project->get_signalbox()->name_changed(m_handle); // outbound signal to project
            }
        };


        template <typename H, typename BH>
        class Common_Data_Command_Set_Description :
                public Common_Data_Command_Get_Set_Base<H,BH,QString>
        {
        public:
            using inherited_type = Common_Data_Command_Get_Set_Base<H,BH, QString>;

            Common_Data_Command_Set_Description(QString const& a_value, handle_type const& a_handle, Project* a_project):
                inherited_type(a_handle, a_project, a_value, a_handle.cget_basic_handle().cget().cget_common_data().cget_description())
            {}

            ~Common_Data_Command_Set_Description() = default;
        protected:
            void do_execute() override final
            {
                // open the handle, then the common data, then set that part of it.
                m_handle.get_basic_handle().get().get_common_data().set_description(m_new_value);
                m_project->get_signalbox()->description_changed(m_handle); // outbound signal to project
            }
            void do_unexecute() override final
            {
                // open the handle, then the common data, then set that part of it.
                m_handle.get_basic_handle().get().get_common_data().set_description(m_old_value);
                m_project->get_signalbox()->description_changed(m_handle); // outbound signal to project
            }
        };

        using File_Common_Data_Command_Set_Name = Common_Data_Command_Set_Name<File_Handle, File_Basic_Handle>;
        using File_Common_Data_Command_Set_Description = Common_Data_Command_Set_Description<File_Handle, File_Basic_Handle>;
    }
}


template sak::Common_Data_Command_Set_Name<sak::File_Handle, sak::File_Basic_Handle>;
template sak::Common_Data_Command_Set_Description<sak::File_Handle, sak::File_Basic_Handle>;


std::unique_ptr<generic::abstract::Command> sak::make_command_set_name(QString const& a_value, File_Handle const& a_handle, Project* a_project)
{
    return std::unique_ptr<generic::abstract::Command>(std::make_unique<File_Common_Data_Command_Set_Name>(a_value, a_handle, a_project).release());
}

std::unique_ptr<generic::abstract::Command> sak::make_command_set_description(QString const& a_value, File_Handle const& a_handle, Project* a_project)
{
    return std::unique_ptr<generic::abstract::Command>(std::make_unique<File_Common_Data_Command_Set_Description>(a_value, a_handle, a_project).release());
}
