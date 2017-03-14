#ifndef SAK_SHARED_PROJECT_ACCESS_HPP
#define SAK_SHARED_PROJECT_ACCESS_HPP

#include "fwd/project_access.hpp"
#include "fwd/manager.hpp"
#include "object.hpp"
#include <sak/project/fwd/object.hpp>
#include <vector>

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::project_access<T>
    //---------------------------------------------------------------------------
    // Supply an interface to send signals back to the Project. This allows us to
    // hide the signalling methods from the templates so we can have template
    // classes only expose things that need to be exposed.
    template <typename T>
    struct project_access
    {
      using object_type = T;
      using handle_type = handle<T>;

      // This is a adapter interface so the project::object interface can be unambiguous and
      // also used by templates.

      // Are there any objects in this Project?
      static bool empty(project::object& a_project);

      // How many objects are in this Project?
      static std::size_t count(project::object& a_project);

      // Get the objects at this index
      static handle_type get_at(project::object& a_project, std::size_t a_index);

      // Get all the objects
      static std::vector<handle_type> get_all(project::object& a_project);

      // Get all the object names
      static std::vector<QString> get_all_names(project::object& a_project);

      // Undoable create a new default object and add it.
      static void add_new(project::object& a_project);

      // Undoable create a new object using the supplied data.
      static void add_emplace(project::object& a_project, object_type&& a_object);

      // Undoable add a new object using the supplied handle. If this handle is invalid or already in the data
      // then nothing happens.
      static void add(project::object& a_project, handle_type const& a_handle);

      // Undoable remove object. If this handle is invalid or not in the data nothing happens.
      // Data is not deleted until the last reference is deleted.
      static void remove(project::object* a_project, handle_type const& a_handle);

      // Undoable change an object's maember value. If this handle is invalid or not in the data nothing happens.
      // If the variant data is the wrong type for the member at the index nothing happens.
      static void change_at(project::object* a_project, handle_type const& a_handle, std::size_t a_index, typename object_type::member_value_variant const& a_variant);

      // Request that the editor for this file be opened or switched to.
      static void request_editor(project::object* a_project, handle_type const& a_handle);

      // Request that the focus change to this object.
      static void request_focus(project::object* a_project, handle_type const& a_handle);
    };


    //---------------------------------------------------------------------------
    // shared::project_access<file::object>
    //---------------------------------------------------------------------------
    template <>
    struct project_access<file::object>
    {
      using object_type = file::object;
      using handle_type = handle<object_type>;

      // This is a adapter interface so the project::object interface can be unambiguous and
      // also used by templates.

      // Are there any objects in this Project?
      static bool empty(project::object& a_project);

      // How many objects are in this Project?
      static std::size_t count(project::object& a_project);

      // Get the objects at this index
      static handle_type get_at(project::object& a_project, std::size_t a_index);

      // Get all the objects
      static std::vector<handle_type> get_all(project::object& a_project);

      // Get all the object names
      static std::vector<QString> get_all_names(project::object& a_project);

      // Undoable create a new default object and add it.
      static void add_new(project::object& a_project);

      // Undoable create a new object using the supplied data.
      static void add_emplace(project::object& a_project, object_type&& a_object);

      // Undoable add a new object using the supplied handle. If this handle is invalid or already in the data
      // then nothing happens.
      static void add(project::object& a_project, handle_type const& a_handle);

      // Undoable remove object. If this handle is invalid or not in the data nothing happens.
      // Data is not deleted until the last reference is deleted.
      static void remove(project::object* a_project, handle_type const& a_handle);

      // Undoable change an object's maember value. If this handle is invalid or not in the data nothing happens.
      // If the variant data is the wrong type for the member at the index nothing happens.
      static void change_at(project::object* a_project, handle_type const& a_handle, std::size_t a_index, typename object_type::member_value_variant const& a_variant);

      // Request that the editor for this file be opened or switched to.
      static void request_editor(project::object* a_project, handle_type const& a_handle);

      // Request that the focus change to this object.
      static void request_focus(project::object* a_project, handle_type const& a_handle);
    };


    //---------------------------------------------------------------------------
    // shared::project_access<texture::object>
    //---------------------------------------------------------------------------
    template <>
    struct project_access<texture::object>
    {
      using object_type = texture::object;
      using handle_type = handle<object_type>;

      // This is a adapter interface so the project::object interface can be unambiguous and
      // also used by templates.

      // Are there any objects in this Project?
      static bool empty(project::object& a_project);

      // How many objects are in this Project?
      static std::size_t count(project::object& a_project);

      // Get the objects at this index
      static handle_type get_at(project::object& a_project, std::size_t a_index);

      // Get all the objects
      static std::vector<handle_type> get_all(project::object& a_project);

      // Get all the object names
      static std::vector<QString> get_all_names(project::object& a_project);

      // Undoable create a new default object and add it.
      static void add_new(project::object& a_project);

      // Undoable create a new object using the supplied data.
      static void add_emplace(project::object& a_project, object_type&& a_object);

      // Undoable add a new object using the supplied handle. If this handle is invalid or already in the data
      // then nothing happens.
      static void add(project::object& a_project, handle_type const& a_handle);

      // Undoable remove object. If this handle is invalid or not in the data nothing happens.
      // Data is not deleted until the last reference is deleted.
      static void remove(project::object* a_project, handle_type const& a_handle);

      // Undoable change an object's maember value. If this handle is invalid or not in the data nothing happens.
      // If the variant data is the wrong type for the member at the index nothing happens.
      static void change_at(project::object* a_project, handle_type const& a_handle, std::size_t a_index, typename object_type::member_value_variant const& a_variant);

      // Request that the editor for this file be opened or switched to.
      static void request_editor(project::object* a_project, handle_type const& a_handle);

      // Request that the focus change to this object.
      static void request_focus(project::object* a_project, handle_type const& a_handle);
    };
  }
}

#endif // SAK_SHARED_PROJECT_ACCESS_HPP
