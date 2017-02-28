#include "dispatch_signals.hpp"

#include <sak/shared/object.hpp>
#include <sak/shared/extended_manager.hpp>
#include <sak/project.hpp>
#include <sak/project_signalbox.hpp>
#include <sak/shared/command.hpp>

// Interface
//============================================================
template <typename T>
void sak::shared::dispatch_signals<T>::changed_at(Project* a_project, extended_handle_type const& a_ehandle, std::size_t a_index)
{
  a_project->get_signalbox()->changed_at(a_ehandle,a_index); // outbound signal to project
}

template <typename T>
void sak::shared::dispatch_signals<T>::added(Project* a_project, extended_handle_type const& a_ehandle)
{
  a_project->get_signalbox()->added(a_ehandle); // outbound signal to project
}

template <typename T>
void sak::shared::dispatch_signals<T>::removed(Project* a_project, extended_handle_type const& a_ehandle)
{
  a_project->get_signalbox()->removed(a_ehandle); // outbound signal to project
}
template <typename T>
void sak::shared::dispatch_signals<T>::requests_editor(Project* a_project, extended_handle_type const& a_ehandle)
{
  a_project->get_signalbox()->requests_editor(a_ehandle); // outbound signal to project
}

template <typename T>
void sak::shared::dispatch_signals<T>::requests_focus(Project* a_project, extended_handle_type const& a_ehandle)
{
  a_project->get_signalbox()->requests_focus(a_ehandle); // outbound signal to project
}

// make a new default object and dispatch the command.
template <typename T>
void sak::shared::dispatch_signals<T>::command_make_new(Project* a_project)
{
  // Either this call triggers the data change in model, or we have to make that call here.
  auto l_file = a_project->make_file(); // going to need to change this...

  // we need to wrap this as a command so it can be undone.
  a_project->emplace_execute(make_command_added<T>(a_project, std::move(l_file)));
}

// Dispatch the command to remove this object.
template <typename T>
void sak::shared::dispatch_signals<T>::command_remove(Project* a_project, extended_handle_type const& a_ehandle)
{
  a_project->emplace_execute(make_command_removed<T>(a_project, a_ehandle));
}

// Forced Instantiations
//============================================================
template sak::file::dispatch_signals;
