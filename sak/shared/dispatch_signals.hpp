#ifndef SAK_SHARED_DISPATCH_SIGNALS_HPP
#define SAK_SHARED_DISPATCH_SIGNALS_HPP

#include "fwd/dispatch_signals.hpp"
#include "fwd/extended_manager.hpp"
#include "object.hpp"
#include <sak/project/fwd/object.hpp>
#include <vector>

namespace sak
{
  class Project;

  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::dispatch_signals<T>
    //---------------------------------------------------------------------------
    // Supply an interface to send signals back to the Project. This allows us to
    // hide the signalling methods from the templates so we can have template
    // classes only expose things that need to be exposed.
    template <typename T>
    struct dispatch_signals
    {
      using object_type = T;
      using extended_handle_type = extended_handle<T>;

      static void changed_at(Project* a_project, extended_handle_type const& a_ehandle, std::size_t a_index);
      static void added(Project* a_project, extended_handle_type const& a_ehandle);
      static void removed(Project* a_project, extended_handle_type const& a_ehandle);
      static void requests_editor(Project* a_project, extended_handle_type const& a_ehandle);
      static void requests_focus(Project* a_project, extended_handle_type const& a_ehandle);

      // make a new default object and dispatch the command.
      static void command_make_new(Project* a_project);

      // Dispatch the command to remove this object.
      static void command_remove(Project* a_project, extended_handle_type const& a_ehandle);

      // The newer signals...



      // This is a adapter interface so the project::object interface can be unambiguous and
      // also used by templates.

      // Are there any objects in this Project?
      static bool empty(project::object& a_project) const;

      // How many objects are in this Project?
      static std::size_t count(project::object& a_project) const;

      // Get the objects at this index
      static extended_handle_type get_at(project::object& a_project, std::size_t a_index) const;

      // Get all the objects
      static std::vector<extended_handle_type> get_all(project::object& a_project) const;

      // Get all the object names
      static std::vector<QString> get_all_names(project::object& a_project) const;

      // Undoable create a new default object and add it.
      static void add_new(project::object& a_project);

      // Undoable create a new object using the supplied data.
      static void add_emplace(project::object& a_project, object_type&& a_object);

      // Undoable add a new object using the supplied handle. If this handle is invalid or already in the data
      // then nothing happens.
      static void add(project::object& a_project, extended_handle_type const& a_ehandle);

      // Undoable remove object. If this handle is invalid or not in the data nothing happens.
      // Data is not deleted until the last reference is deleted.
      static void remove(project::object* a_project, extended_handle_type const& a_ehandle);

      // Undoable change an object's maember value. If this handle is invalid or not in the data nothing happens.
      // If the variant data is the wrong type for the member at the index nothing happens.
      static void change_at(project::object* a_project, extended_handle_type const& a_ehandle, std::size_t a_index, typename object_type::member_value_variant const& a_variant);

      // Request that the editor for this file be opened or switched to.
      static void request_editor(project::object* a_project, extended_handle_type const& a_ehandle);

      // Request that the focus change to this object.
      static void request_focus(project::object* a_project, extended_handle_type const& a_ehandle);
    };
  }
}

#endif // SAK_SHARED_DISPATCH_SIGNALS_HPP
