#include "file_interface_traits.h"

#include <vector>
#include <QString>
#include <algorithm>
#include <limits>
#include "project.h"
#include "name_utilities.h"

sak::File_Const_Interface::File_Const_Interface(File_Basic_Handle const& a_handle):
    m_handle{a_handle}
{}

QString const& sak::File_Const_Interface::cget_name() const
{
    return m_handle.cget().cget_name();
}

QString const& sak::File_Const_Interface::cget_description() const
{
    return m_handle.cget().cget_description();
}

sak::File_Interface::File_Interface(File_Basic_Handle const& a_handle, Project* a_project):
    File_Const_Interface(a_handle),
    m_project{a_project}
{}

void sak::File_Interface::set_name(QString const& a_name)
{
    // If it is the same as the name we already have, we don't bother making a change.
    if (a_name == cget_name())
    {
        return;
    }
    // We must make sure the name does not already exist among the other names.
    auto l_names = m_project->get_all_file_names();
    // Get rid of the name of this one, since it is going to change.
    auto l_old_name_found = std::find(l_names.cbegin(), l_names.cend(), cget_name());
    l_names.erase(l_old_name_found);

    QString l_final_name{a_name};
    uniqueify_name(l_final_name, l_names);

    m_handle.get().set_name(l_final_name);
    // signal the change through m_project...
    m_project->file_name_changed(m_handle);
}

void sak::File_Interface::set_description(QString const& a_description)
{
    // If it is the same as the name we already have, we don't bother making a change.
    if (a_description == m_handle.cget().cget_description())
    {
        return;
    }

    m_handle.get().set_description(a_description);
    // signal the change through m_project...
    m_project->file_data_changed(m_handle);
}


sak::File_Interface_Traits::File_Interface_Traits(Project* a_project):
    m_project{a_project}
{}

sak::File_Interface_Traits::interface_type sak::File_Interface_Traits::get(basic_handle_type& a_ref)
{
    return interface_type(a_ref, m_project);
}

sak::File_Interface_Traits::const_interface_type sak::File_Interface_Traits::cget(basic_handle_type const& a_ref) const
{
    return const_interface_type(a_ref);
}
