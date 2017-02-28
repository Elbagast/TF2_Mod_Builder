#ifndef SAK_SHARED_DISPATCH_SIGNALS_HPP
#define SAK_SHARED_DISPATCH_SIGNALS_HPP

#include "fwd/dispatch_signals.hpp"
#include "fwd/extended_manager.hpp"

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
    };
  }
}

#endif // SAK_SHARED_DISPATCH_SIGNALS_HPP
