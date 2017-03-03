#include "project_access.hpp"

#include <sak/shared/object.hpp>
#include <sak/shared/extended_manager.hpp>
#include <sak/project/object.hpp>

//---------------------------------------------------------------------------
// shared::project_access<file::object>
//---------------------------------------------------------------------------
// This is a adapter interface so the project::object interface can be unambiguous and
// also used by templates.

// Are there any objects in this Project?
bool sak::shared::project_access<sak::file::object>::empty(project::object& a_project)
{
  return !a_project.has_files();
}

// How many objects are in this Project?
std::size_t sak::shared::project_access<sak::file::object>::count(project::object& a_project)
{
  return a_project.file_count();
}


// Get the objects at this index
typename sak::shared::project_access<sak::file::object>::extended_handle_type sak::shared::project_access<sak::file::object>::get_at(project::object& a_project, std::size_t a_index)
{
  return a_project.get_file_at(a_index);
}


// Get all the objects
std::vector<typename sak::shared::project_access<sak::file::object>::extended_handle_type> sak::shared::project_access<sak::file::object>::get_all(project::object& a_project)
{
  return a_project.get_all_files();
}


// Get all the object names
std::vector<QString> sak::shared::project_access<sak::file::object>::get_all_names(project::object& a_project)
{
  return a_project.get_all_file_names();
}


// Undoable create a new default object and add it.
void sak::shared::project_access<sak::file::object>::add_new(project::object& a_project)
{
  a_project.file_add_new();
}


// Undoable create a new object using the supplied data.
void sak::shared::project_access<sak::file::object>::add_emplace(project::object& a_project, object_type&& a_object)
{
  a_project.file_add_emplace(std::move(a_object));
}


// Undoable add a new object using the supplied handle. If this handle is invalid or already in the data
// then nothing happens.
void sak::shared::project_access<sak::file::object>::add(project::object& a_project, extended_handle_type const& a_ehandle)
{
  a_project.file_add(a_ehandle);
}


// Undoable remove object. If this handle is invalid or not in the data nothing happens.
// Data is not deleted until the last reference is deleted.
void sak::shared::project_access<sak::file::object>::remove(project::object* a_project, extended_handle_type const& a_ehandle)
{
  a_project->file_remove(a_ehandle);
}


// Undoable change an object's maember value. If this handle is invalid or not in the data nothing happens.
// If the variant data is the wrong type for the member at the index nothing happens.
void sak::shared::project_access<sak::file::object>::change_at(project::object* a_project, extended_handle_type const& a_ehandle, std::size_t a_index, typename object_type::member_value_variant const& a_variant)
{
  a_project->file_change_at(a_ehandle, a_index, a_variant);
}


// Request that the editor for this file be opened or switched to.
void sak::shared::project_access<sak::file::object>::request_editor(project::object* a_project, extended_handle_type const& a_ehandle)
{
  a_project->file_request_editor(a_ehandle);
}


// Request that the focus change to this object.
void sak::shared::project_access<sak::file::object>::request_focus(project::object* a_project, extended_handle_type const& a_ehandle)
{
  a_project->file_request_focus(a_ehandle);
}





// Forced Instantiations
//============================================================
