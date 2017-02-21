#include "common_data_interface.h"

#include "fwd_file.h"
#include "file_basic_manager.h"
#include "file_manager.h"
#include <vector>
#include <QString>
#include <algorithm>
#include <limits>
#include "project.h"
//#include "project_signalbox.h"
#include "name_utilities.h"
#include "common_data_command.h"

template <typename H, typename BH>
sak::Common_Data_Const_Interface<H,BH>::Common_Data_Const_Interface(handle_type const& a_handle, basic_handle_type const& a_data):
    m_handle{a_handle},
    m_data{a_data}
{}

template <typename H, typename BH>
sak::Common_Data_Const_Interface<H,BH>::~Common_Data_Const_Interface() = default;

template <typename H, typename BH>
QString const& sak::Common_Data_Const_Interface<H,BH>::cget_name() const
{
    return m_data.cget().cget_common_data().cget_name();
}

template <typename H, typename BH>
QString const& sak::Common_Data_Const_Interface<H,BH>::cget_description() const
{
    return m_data.cget().cget_common_data().cget_description();
}

template <typename H, typename BH>
sak::Common_Data_Interface<H,BH>::Common_Data_Interface(handle_type const& a_handle, basic_handle_type& a_data, Project* a_project):
    m_handle{a_handle},
    m_data{a_data},
    m_project{a_project}
{}

template <typename H, typename BH>
sak::Common_Data_Interface<H,BH>::~Common_Data_Interface() = default;

template <typename H, typename BH>
void sak::Common_Data_Interface<H,BH>::set_name(QString const& a_name)
{
    // If it is the same as the name we already have, we don't bother making a change.
    if (a_name == m_data.cget().cget_common_data().cget_name())
    {
        return;
    }
    // We must make sure the name does not already exist among the other names.
    auto l_names = m_project->get_all_file_names();
    // Get rid of the name of this one, since it is going to change.
    auto l_old_name_found = std::find(l_names.cbegin(), l_names.cend(), m_data.cget().cget_common_data().cget_name());
    l_names.erase(l_old_name_found);

    QString l_final_name{a_name};
    uniqueify_name(l_final_name, l_names);


    m_project->emplace_execute(make_command_set_name(l_final_name, m_handle, m_project));



    // open the handle, then the common data, then set that part of it.
    //m_data.get().get_common_data().set_name(l_final_name);
    // signal the change through m_project...
    //m_project->get_signalbox()->name_changed(m_handle); // outbound signal to project
}

template <typename H, typename BH>
void sak::Common_Data_Interface<H,BH>::set_description(QString const& a_description)
{
    // If it is the same as the name we already have, we don't bother making a change.
    if (a_description == m_data.cget().cget_common_data().cget_description())
    {
        return;
    }

    // So what do we do make this into a Command?
    // We have to hand the data over to a Command object and send that to where it will be held.
    // the Command will signal, not the interface.

    m_project->emplace_execute(make_command_set_description(a_description, m_handle, m_project));

    // open the handle, then the common data, then set that part of it.
    //m_data.get().get_common_data().set_description(a_description);
    // signal the change through m_project...
    //m_project->get_signalbox()->description_changed(m_handle); // outbound signal to project
}


template sak::Common_Data_Interface<sak::File_Handle, sak::File_Basic_Handle>;
template sak::Common_Data_Const_Interface<sak::File_Handle, sak::File_Basic_Handle>;
