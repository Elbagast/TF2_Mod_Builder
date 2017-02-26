#include "interface.hpp"
#include "object.hpp"
#include "manager.hpp"
#include "extended_manager.hpp"
#include <vector>
#include <QString>
#include <algorithm>
#include <limits>
#include "../project.hpp"
#include "../name_utilities.hpp"
#include "../common_data_command.hpp"

//---------------------------------------------------------------------------
// file::interface
//---------------------------------------------------------------------------
sak::file::interface::interface(extended_handle const& a_ehandle, handle& a_handle, Project* a_project):
  m_ehandle{a_ehandle},
  m_handle{a_handle},
  m_project{a_project}
{}

void sak::file::interface::set_name(QString const& a_value)
{
  // If it is the same as the name we already have, we don't bother making a change.
  if (a_value == m_ehandle.cget().cat<0>())
  {
      return;
  }

  // We must make sure the name does not already exist among the other names.
  auto l_names = m_project->get_all_file_names();
  // Get rid of the name of this one, since it is going to change.
  auto l_old_name_found = std::find(l_names.cbegin(), l_names.cend(), m_data.cget().cget_name());
  l_names.erase(l_old_name_found);

  QString l_final_name{a_name};
  uniqueify_name(l_final_name, l_names);

  m_project->emplace_execute(make_command_assign<0>(m_project, m_ehandle, l_final_name));
}

void sak::file::interface::set_description(QString const& a_value)
{
  // If it is the same as the name we already have, we don't bother making a change.
  if (a_value == m_ehandle.cget().cat<1>())
  {
      return;
  }

  m_project->emplace_execute(make_command_assign<1>(m_project, m_ehandle, a_value));
}

void sak::file::interface::set_buildpath(QString const& a_value)
{
  // If it is the same as the name we already have, we don't bother making a change.
  if (a_value == m_ehandle.cget().cat<2>())
  {
      return;
  }

  m_project->emplace_execute(make_command_assign<2>(m_project, m_ehandle, a_value));
}

void sak::file::interface::set_sourcepath(QString const& a_value)
{
  // If it is the same as the name we already have, we don't bother making a change.
  if (a_value == m_ehandle.cget().cat<3>())
  {
      return;
  }

  m_project->emplace_execute(make_command_assign<3>(m_project, m_ehandle, a_value));
}


//---------------------------------------------------------------------------
// file::const_interface
//---------------------------------------------------------------------------
sak::file::const_interface::const_interface(extended_handle const& a_ehandle, handle const& a_handle):
  m_ehandle{a_ehandle},
  m_handle{a_handle}
{}

QString const& sak::file::const_interface::cget_name() const
{
  return m_ehandle.cget().cat<0>();
}

QString const& sak::file::const_interface::cget_description() const
{
  return m_ehandle.cget().cat<1>();
}

QString const& sak::file::const_interface::cget_buildpath() const
{
  return m_ehandle.cget().cat<2>();
}

QString const& sak::file::const_interface::cget_sourcepath() const
{
  return m_ehandle.cget().cat<3>();
}
