#include "section_interface.hpp"

//#include "section_data.hpp"
#include "section_data_manager.hpp"
#include "section_command.hpp"
#include "command_history.hpp"
#include <sak/name_utilities.hpp>

// Special 6
//============================================================
template <typename T>
sak::Section_Interface<T>::Section_Interface(Data_Manager_Type* a_data_manager, Command_History* a_command_history):
  m_data_manager{a_data_manager},
  m_command_history{a_command_history}
{}

template <typename T>
sak::Section_Interface<T>::~Section_Interface() = default;

template <typename T>
sak::Section_Interface<T>::Section_Interface(Section_Interface<T> const&) = default;

template <typename T>
sak::Section_Interface<T>& sak::Section_Interface<T>::operator=(Section_Interface<T> const&) = default;

template <typename T>
sak::Section_Interface<T>::Section_Interface(Section_Interface<T> &&) = default;

template <typename T>
sak::Section_Interface<T>& sak::Section_Interface<T>::operator=(Section_Interface<T> &&) = default;

// Interface
//============================================================
// Everything you can do with a data_class derived object.

// Are there any objects in this Project?
template <typename T>
bool sak::Section_Interface<T>::is_empty() const
{
  return m_data_manager->empty();
}

template <typename T>
bool sak::Section_Interface<T>::not_empty() const
{
  return !is_empty();
}

// How many objects are in this Project?
template <typename T>
std::size_t sak::Section_Interface<T>::count() const
{
  return m_data_manager->count();
}

// Get the objects at this index
template <typename T>
typename sak::Section_Interface<T>::Handle_Type sak::Section_Interface<T>::get_at(std::size_t a_index) const
{
  return m_data_manager->get_at(a_index);
}

// Get all the objects
template <typename T>
std::vector<typename sak::Section_Interface<T>::Handle_Type> sak::Section_Interface<T>::get_all() const
{
  return m_data_manager->get_all();
}

// Get all the object names
template <typename T>
std::vector<QString> sak::Section_Interface<T>::get_all_names() const
{
  return m_data_manager->get_all_names();
}

// Make a new object using the default parameters. Project's data management system owns it
// but it is not part of the Project. Does not trigger any commands.
template <typename T>
typename sak::Section_Interface<T>::Handle_Type sak::Section_Interface<T>::make_default()
{
  return m_data_manager->make();
}

// Make a new object using the supplied data. Project's data management system owns it but
// it is not part of the Project. Does not trigger any commands.
template <typename T>
typename sak::Section_Interface<T>::Handle_Type sak::Section_Interface<T>::make_emplace(Data_Type&& a_object)
{
  return m_data_manager->make_emplace(std::move(a_object));
}

// Undoable add a new object made using the default parameters. The name will be modified if it is
// currently in use by another object.
template <typename T>
void sak::Section_Interface<T>::add_default()
{
  m_command_history->add_execute(make_command_added<Data_Type>(m_data_manager, m_data_manager->make()));
}

// Undoable add a new object using the supplied data. This data is assigned a new handle. The name will
// be modified if it is currently in use by another object.
template <typename T>
void sak::Section_Interface<T>::add_emplace(Data_Type&& a_object)
{
  m_command_history->add_execute(make_command_added<Data_Type>(m_data_manager, m_data_manager->make_emplace(std::move(a_object))));
}

// Undoable add a new object using the supplied handle. The name will be modified if it is currently in
// use by another object. If this handle is invalid or already in the data then nothing happens.
template <typename T>
void sak::Section_Interface<T>::add(Handle_Type const& a_handle)
{
  if (flamingo::not_null(a_handle) && !(m_data_manager->has_handle(a_handle)))
  {
    m_command_history->add_execute(make_command_added<Data_Type>(m_data_manager, a_handle));
  }
}

// Undoable remove object. If this handle is invalid or not in the data nothing happens.
// Data is not deleted until the last reference is deleted.
template <typename T>
void sak::Section_Interface<T>::remove(Handle_Type const& a_handle)
{
  if (flamingo::not_null(a_handle) && m_data_manager->has_handle(a_handle))
  {
    m_command_history->add_execute(make_command_removed<Data_Type>(m_data_manager, a_handle));
  }
}

// Undoable change an object's member value. If this handle is invalid or not in the data nothing happens.
// If the variant data is the wrong type for the member at the index nothing happens.

// Got to separate out the actual work so the specialisation for the first member is hidden.

template <std::size_t Index, typename T>
void sak::internal::Do_Change_At<Index,T>::operator()(
    Data_Manager_Type* a_data_manager,
    Command_History* a_command_history,
    Handle_Type const& a_handle,
    Member_Value_Type const& a_value)
{
  // If the input equals the old value
  if (a_value == a_handle->cmember_at<Index>())
  {
    // Nothing happens to the value, but we need to tell things to update
    // to keep the gui correct.
    a_data_manager->changed_at(a_handle,Index );
    return;
  }
  a_command_history->add_execute(make_command_assign<Index,T>(a_data_manager, a_handle, a_value));
}


template <typename T>
void sak::internal::Do_Change_At<0,T>::operator()(
    Data_Manager_Type* a_data_manager,
    Command_History* a_command_history,
    Handle_Type const& a_handle,
    Member_Value_Type const& a_value)
{
  static_assert(std::is_same<Section_Data_Member_Value_Type<0,T>, QString>::value, "Member 0 has a type that is not QString...");

  // If the input name equals the old name
  if (a_value == a_handle->cmember_at<0>())
  {
    // Nothing happens to the value, but we need to tell things to update
    // to keep the gui correct.
    a_data_manager->changed_at(a_handle,0);
    return;
  }
  // We must make sure the name does not already exist among the other names.
  auto l_names = a_data_manager->get_all_names();
  // Get rid of the name of this one, since it is going to change.
  auto l_old_name_found = std::find(l_names.cbegin(), l_names.cend(), a_handle->cmember_at<0>());
  l_names.erase(l_old_name_found);

  QString l_final_name{a_value};
  uniqueify_name(l_final_name, l_names);

  // If the modified name equals the old name
  if (l_final_name == a_handle->cmember_at<0>())
  {
    // Nothing happens to the value, but we need to tell things to update
    // to keep the gui correct.
    a_data_manager->changed_at(a_handle,0);
    return;
  }
  a_command_history->add_execute(make_command_assign<0,T>(a_data_manager, a_handle, l_final_name));
}


// Request that the editor for this file be opened or switched to.
template <typename T>
void sak::Section_Interface<T>::request_editor(Handle_Type const& a_handle)
{
  if (flamingo::not_null(a_handle) && m_data_manager->has_handle(a_handle))
  {
    m_data_manager->requests_editor(a_handle);
  }
}

// Request that the focus change to this object.
template <typename T>
void sak::Section_Interface<T>::request_focus(Handle_Type const& a_handle)
{
  if (flamingo::not_null(a_handle) && m_data_manager->has_handle(a_handle))
  {
    m_data_manager->requests_focus(a_handle);
  }
}

// Forced Instantiations
//============================================================
// As annoying as it is we have to explicitly instantiate the logic for each index if we want to keep it
// hidden. Otherwise this would all be public so the compiler can find it.

template sak::File_Interface;

template sak::internal::Do_Change_At<0,sak::File_Data>;
template sak::internal::Do_Change_At<1,sak::File_Data>;
//template sak::internal::Do_Change_At<2,sak::File_Data>;
//template sak::internal::Do_Change_At<3,sak::File_Data>;
//template sak::internal::Do_Change_At<4,sak::File_Data>;
//template sak::internal::Do_Change_At<5,sak::File_Data>;

template sak::Texture_Interface;

template sak::internal::Do_Change_At<0,sak::Texture_Data>;
template sak::internal::Do_Change_At<1,sak::Texture_Data>;
//template sak::internal::Do_Change_At<2,sak::Texture_Data>;
//template sak::internal::Do_Change_At<3,sak::Texture_Data>;

