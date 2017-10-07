#include "interface.hpp"

#include "data_manager.hpp"
#include "command.hpp"
#include <sak/name_utilities.hpp>
#include <generic/command_history.hpp>

// Special 6
//============================================================
template <typename T>
sak::shared::interface<T>::interface(data_manager<object_type>& a_data_manager, generic::Command_History& a_command_history):
  m_data_manager{a_data_manager},
  m_command_history{a_command_history}
{}

// Interface
//============================================================
// Everything you can do with a data_class derived object.

// Are there any objects in this Project?
template <typename T>
bool sak::shared::interface<T>::is_empty() const
{
  return m_data_manager.empty();
}

template <typename T>
bool sak::shared::interface<T>::not_empty() const
{
  return !is_empty();
}

// How many objects are in this Project?
template <typename T>
std::size_t sak::shared::interface<T>::count() const
{
  return m_data_manager.count();
}

// Get the objects at this index
template <typename T>
typename sak::shared::interface<T>::handle_type sak::shared::interface<T>::get_at(std::size_t a_index) const
{
  return m_data_manager.get_at(a_index);
}

// Get all the objects
template <typename T>
std::vector<typename sak::shared::interface<T>::handle_type> sak::shared::interface<T>::get_all() const
{
  return m_data_manager.get_all();
}

// Get all the object names
template <typename T>
std::vector<QString> sak::shared::interface<T>::get_all_names() const
{
  return m_data_manager.get_all_names();
}

// Make a new object using the default parameters. Project's data management system owns it
// but it is not part of the Project. Does not trigger any commands.
template <typename T>
typename sak::shared::interface<T>::handle_type sak::shared::interface<T>::make_default()
{
  return m_data_manager.make();
}

// Make a new object using the supplied data. Project's data management system owns it but
// it is not part of the Project. Does not trigger any commands.
template <typename T>
typename sak::shared::interface<T>::handle_type sak::shared::interface<T>::make_emplace(object_type&& a_object)
{
  return m_data_manager.make_emplace(std::move(a_object));
}

// Undoable add a new object made using the default parameters. The name will be modified if it is
// currently in use by another object.
template <typename T>
void sak::shared::interface<T>::add_default()
{
  m_command_history.add_execute(make_command_added<object_type>(m_data_manager, m_data_manager.make()));
}

// Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
// be modified if it is currently in use by another object.
template <typename T>
void sak::shared::interface<T>::add_emplace(object_type&& a_object)
{
  m_command_history.add_execute(make_command_added<object_type>(m_data_manager, m_data_manager.make_emplace(std::move(a_object))));
}

// Undoable add a new object using the supplied handle. The name will be modified if it is currently in
// use by another object. If this handle is invalid or already in the data then nothing happens.
template <typename T>
void sak::shared::interface<T>::add(handle_type const& a_handle)
{
  if (flamingo::not_null(a_handle) && !(m_data_manager.has_handle(a_handle)))
  {
    m_command_history.add_execute(make_command_added<object_type>(m_data_manager, a_handle));
  }
}

// Undoable remove object. If this handle is invalid or not in the data nothing happens.
// Data is not deleted until the last reference is deleted.
template <typename T>
void sak::shared::interface<T>::remove(handle_type const& a_handle)
{
  if (flamingo::not_null(a_handle) && m_data_manager.has_handle(a_handle))
  {
    m_command_history.add_execute(make_command_removed<object_type>(m_data_manager, a_handle));
  }
}

// Undoable change an object's maember value. If this handle is invalid or not in the data nothing happens.
// If the variant data is the wrong type for the member at the index nothing happens.

// Got to separate out the actual work so the specialisation for the first member is hidden.

template <typename T, std::size_t Index>
void sak::shared::do_change_at<T,Index>::operator()(
    data_manager<T>& a_data_manager,
    generic::Command_History& a_command_history,
    handle<T> const& a_handle,
    data_class_member_t<T,Index> const& a_value)
{
  if (a_value == a_handle->cmember_at<Index>())
  {
    return;
  }
  a_command_history.add_execute(make_command_assign<T, Index>(a_data_manager, a_handle, a_value));
}


template <typename T>
void sak::shared::do_change_at<T,0>::operator()(
    data_manager<T>& a_data_manager,
    generic::Command_History& a_command_history,
    handle<T> const& a_handle,
    data_class_member_t<T,0> const& a_value)
{
  static_assert(std::is_same<data_class_member_t<T,0>, QString>::value, "Member 0 has a type that is not QString...");

  if (a_value == a_handle->cmember_at<0>())
  {
    return;
  }
  // We must make sure the name does not already exist among the other names.
  auto l_names = a_data_manager.get_all_names();
  // Get rid of the name of this one, since it is going to change.
  auto l_old_name_found = std::find(l_names.cbegin(), l_names.cend(), a_handle->cmember_at<0>());
  l_names.erase(l_old_name_found);

  QString l_final_name{a_value};
  uniqueify_name(l_final_name, l_names);
  a_command_history.add_execute(make_command_assign<T, 0>(a_data_manager, a_handle, l_final_name));
}


/*
namespace sak
{
  namespace shared
  {
    namespace
    {
      template <typename T, std::size_t Index>
      struct do_change_at
      {
        void operator()(
            data_manager<T>& a_data_manager,
            generic::Command_History& a_command_history,
            shared::handle<T> const& a_handle,
            typename flamingo::data_class_member_t<T,Index>::value_type const& a_value)
        {
          if (a_value == a_handle.cget().cmember_at<Index>().cget())
          {
            return;
          }
          a_command_history.add_execute(make_command_assign<T, Index>(a_data_manager, a_handle, a_value));
        }
      };


      template <typename T>
      struct do_change_at<T,0>
      {
        void operator()(
            data_manager<T>& a_data_manager,
            generic::Command_History& a_command_history,
            shared::handle<T> const& a_handle,
            typename flamingo::data_class_member_t<T,0>::value_type const& a_value)
        {
          static_assert(std::is_same<value_type, QString>::value, "Member 0 has a type that is not QString...");

          if (a_value == a_handle.cget().cmember_at<0>().cget())
          {
            return;
          }
          // We must make sure the name does not already exist among the other names.
          auto l_names = a_data_manager.get_all_names();
          // Get rid of the name of this one, since it is going to change.
          auto l_old_name_found = std::find(l_names.cbegin(), l_names.cend(), a_handle.cget().cmember_at<0>().cget());
          l_names.erase(l_old_name_found);

          QString l_final_name{a_value};
          uniqueify_name(l_final_name, l_names);
          a_command_history.add_execute(make_command_assign<T, 0>(a_data_manager, a_handle, l_final_name));
        }
      };
    }
  }
}


template <typename T>
template <std::size_t Index>
void sak::shared::interface<T>::change_at(handle_type const& a_handle, typename member_type<Index>::value_type const& a_value)
{
  do_change_at<T,Index>()(m_data_manager, m_command_history, a_handle, a_value);
}
*/

// Request that the editor for this file be opened or switched to.
template <typename T>
void sak::shared::interface<T>::request_editor(handle_type const& a_handle)
{
  if (flamingo::not_null(a_handle) && m_data_manager.has_handle(a_handle))
  {
    m_data_manager.requests_editor(a_handle);
  }
}

// Request that the focus change to this object.
template <typename T>
void sak::shared::interface<T>::request_focus(handle_type const& a_handle)
{
  if (flamingo::not_null(a_handle) && m_data_manager.has_handle(a_handle))
  {
    m_data_manager.requests_focus(a_handle);
  }
}

// Forced Instantiations
//============================================================
// As annoying as it is we have to explicitly instantiate the logic for each index if we want to keep it
// hidden. Otherwise this would all be public so the compiler can find it.

template sak::file::interface;

template sak::shared::do_change_at<sak::file::object,0>;
template sak::shared::do_change_at<sak::file::object,1>;
template sak::shared::do_change_at<sak::file::object,2>;
template sak::shared::do_change_at<sak::file::object,3>;
template sak::shared::do_change_at<sak::file::object,4>;
template sak::shared::do_change_at<sak::file::object,5>;

template sak::texture::interface;

template sak::shared::do_change_at<sak::texture::object,0>;
template sak::shared::do_change_at<sak::texture::object,1>;
template sak::shared::do_change_at<sak::texture::object,2>;
template sak::shared::do_change_at<sak::texture::object,3>;
