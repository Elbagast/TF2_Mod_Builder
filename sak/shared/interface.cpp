#include "interface.hpp"

#include <type_traits>
#include <QString>
#include <sak/name_utilities.hpp>
#include "manager.hpp"
#include "extended_manager.hpp"
#include "command.hpp"
#include <sak/project.hpp>

//---------------------------------------------------------------------------
// shared::internal::fixup_value<T,I>
//---------------------------------------------------------------------------
// Seperating out the call to constrain the name so we can hide the workings.

template <typename T, std::size_t I>
void sak::shared::internal::do_set<T,I>::operator()(value_type const& a_value, extended_handle_type const& a_ehandle, Project* a_project) const
{
  if (a_value == a_ehandle.cget().cat<I>().cget())
  {
      return;
  }
  a_project->emplace_execute(make_command_assign<object_type, I>(a_project, a_ehandle, a_value));
}

template <typename T>
void sak::shared::internal::do_set<T,0>::operator()(value_type const& a_value, extended_handle_type const& a_ehandle, Project* a_project) const
{
  static_assert(std::is_same<value_type, QString>::value, "Member 0 has a type that is not QString...");

  if (a_value == a_ehandle.cget().cat<0>().cget())
  {
      return;
  }
  // We must make sure the name does not already exist among the other names.
  auto l_names = a_project->get_all_file_names();
  // Get rid of the name of this one, since it is going to change.
  auto l_old_name_found = std::find(l_names.cbegin(), l_names.cend(), a_ehandle.cget().cat<0>().cget());
  l_names.erase(l_old_name_found);

  QString l_final_name{a_value};
  uniqueify_name(l_final_name, l_names);

  a_project->emplace_execute(make_command_assign<object_type, 0>(a_project, a_ehandle, l_final_name));
}


// Forced Instantiations
//============================================================
template sak::shared::internal::do_set<sak::file::object,0>;
template sak::shared::internal::do_set<sak::file::object,1>;
template sak::shared::internal::do_set<sak::file::object,2>;
template sak::shared::internal::do_set<sak::file::object,3>;
template sak::shared::internal::do_set<sak::file::object,4>;
template sak::shared::internal::do_set<sak::file::object,5>;
