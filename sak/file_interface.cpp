#include "file_interface.hpp"

#include "fwd_file.hpp"
#include "file_basic_manager.hpp"
#include "file_manager.hpp"
#include "file_command.hpp"
#include "project.hpp"

sak::File_Const_Interface::File_Const_Interface(File_Handle const& a_handle, File_Basic_Handle const& a_data):
    common_interface_type(a_handle, a_data)
{}

QString const& sak::File_Const_Interface::cget_buildpath() const
{
    return m_data.cget().cget_buildpath();
}

QString const& sak::File_Const_Interface::cget_sourcepath() const
{
    return m_data.cget().cget_sourcepath();
}

sak::File_Interface::File_Interface(File_Handle const& a_handle, File_Basic_Handle& a_data, Project* a_project):
    common_interface_type(a_handle, a_data, a_project)
{}

void sak::File_Interface::set_buildpath(QString const& a_value)
{
    // If it is the same as the name we already have, we don't bother making a change.
    if (a_value == m_data.cget().cget_buildpath())
    {
        return;
    }

    m_project->emplace_execute(make_command_set_buildpath(a_value, m_handle, m_project));
}

void sak::File_Interface::set_sourcepath(QString const& a_value)
{
    // If it is the same as the name we already have, we don't bother making a change.
    if (a_value == m_data.cget().cget_sourcepath())
    {
        return;
    }

    m_project->emplace_execute(make_command_set_sourcepath(a_value, m_handle, m_project));
}
