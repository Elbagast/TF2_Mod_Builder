#include "section_data_manager.hpp"

#include "section_data.hpp"
#include "handle.hpp"
#include "abstract_section_signalbox.hpp"

#include <sak/name_utilities.hpp>

#include <cassert>

#include <QDebug>

//---------------------------------------------------------------------------
// sak::Section_Data_Manager<T>
//---------------------------------------------------------------------------
// Splitting out the repeated backend management system for project.

// Special 6
//============================================================
template <typename T>
sak::Section_Data_Manager<T>::Section_Data_Manager():
  m_factory{},
  //m_manager{std::make_unique<Manager_Type>()},
  m_handles{},
  m_signalboxes{}
{}

template <typename T>
sak::Section_Data_Manager<T>::~Section_Data_Manager() = default;

// Virtuals
//============================================================

// When a handle has its data changed drastically, or in an unknown place, this is called.
template <typename T>
void sak::Section_Data_Manager<T>::changed(Handle_Type const& a_handle)
{
  qDebug() << "sak::Section_Data_Manager<T>::changed "<< a_handle.id();
  // This thing must exist
  assert(not_null(a_handle));
  //assert(m_manager.get() == a_handle.manager());
  assert(std::find(m_handles.cbegin(), m_handles.cend(), a_handle) != m_handles.cend());

  for (Signalbox_Type* l_item : m_signalboxes) l_item->changed(a_handle);
}


// When a handle has its data changed in a specific place, this is called.
template <typename T>
void sak::Section_Data_Manager<T>::changed_at(Handle_Type const& a_handle, std::size_t a_section)
{
  qDebug() << "sak::Section_Data_Manager<T>::changed_at "<< a_handle.id() << ", " << a_section;
  // This thing must exist
  assert(not_null(a_handle));
  //assert(m_manager.get() == a_handle.manager());
  assert(std::find(m_handles.cbegin(), m_handles.cend(), a_handle) != m_handles.cend());

  for (Signalbox_Type* l_item : m_signalboxes) l_item->changed_at(a_handle, a_section);
}

// When a handle has been added, this is called.
template <typename T>
void sak::Section_Data_Manager<T>::added(Handle_Type const& a_handle)
{
  qDebug() << "sak::Section_Data_Manager<T>::added "<< a_handle.id();
  // This thing must exist
  assert(not_null(a_handle));
  //assert(m_manager.get() == a_handle.manager());
  //assert(m_manager->is_valid(a_handle.id()));
  // but not yet be part of the Project
  assert(std::find(m_handles.cbegin(), m_handles.cend(), a_handle) == m_handles.cend());
  m_handles.push_back(a_handle);

  for (Signalbox_Type* l_item : m_signalboxes) l_item->added(a_handle);
}

// When a handle has been removed, this is called.
template <typename T>
void sak::Section_Data_Manager<T>::removed(Handle_Type const& a_handle)
{
  qDebug() << "sak::Section_Data_Manager<T>::removed "<< a_handle.id();
  assert(not_null(a_handle));
  //assert(m_manager.get() == a_handle.manager());
  auto l_found = std::find(m_handles.begin(), m_handles.end(), a_handle);
  assert(l_found != m_handles.cend());
  assert(std::addressof(a_handle) != std::addressof(*l_found));

  // Copy the file::extended_handle locally. We don't know where it came from and have to propagate
  // the signal from here rather than who knows where to insure the signal reference stays
  // valid for all that need it.
  Handle_Type l_handle = a_handle;

  // Now kill it, because if it's still in the project the signal will call back to find it
  // is still present.
  m_handles.erase(l_found);

  for (Signalbox_Type* l_item : m_signalboxes) l_item->removed(l_handle);
}

// When a handle requests an editor, this is called.
template <typename T>
void sak::Section_Data_Manager<T>::requests_editor(Handle_Type const& a_handle)
{
  qDebug() << "sak::Section_Data_Manager<T>::requests_editor "<< a_handle.id();
  // This thing must exist
  assert(not_null(a_handle));
  //assert(m_manager.get() == a_handle.manager());
  assert(std::find(m_handles.cbegin(), m_handles.cend(), a_handle) != m_handles.cend());

  for (Signalbox_Type* l_item : m_signalboxes) l_item->requests_editor(a_handle);
}

// When a handle requests an editor, this is called.
template <typename T>
void sak::Section_Data_Manager<T>::requests_focus(Handle_Type const& a_handle)
{
  qDebug() << "sak::Section_Data_Manager<T>::requests_focus "<< a_handle.id();
  // This thing must exist
  assert(not_null(a_handle));
  //assert(m_manager.get() == a_handle.manager());
  assert(std::find(m_handles.cbegin(), m_handles.cend(), a_handle) != m_handles.cend());

  for (Signalbox_Type* l_item : m_signalboxes) l_item->requests_focus(a_handle);
}

// Public Interface
//============================================================
// Are there any handles of this type in the currently active project data?
template <typename T>
bool sak::Section_Data_Manager<T>::empty() const
{
  return m_handles.empty();
}

// How handles of this type in the currently active project data?
template <typename T>
std::size_t sak::Section_Data_Manager<T>::count() const
{
  return m_handles.size();
}

// Is this handle in the currently active project data?
template <typename T>
bool sak::Section_Data_Manager<T>::has_handle(Handle_Type const& a_handle) const
{
  if (not_null(a_handle))
  {
    // search for the handle in the active handles.
    return std::find(m_handles.cbegin(), m_handles.cend(), a_handle) != m_handles.cend();
  }
  else
  {
    // null handles are always inactive
    return false;
  }
}

// Get the handle at this index. Handles are sorted alphabetically by the name
template <typename T>
typename sak::Section_Data_Manager<T>::Handle_Type sak::Section_Data_Manager<T>::get_at(std::size_t a_index) const
{
  return m_handles.at(a_index);
}

// Get all the handles alphabetically sorted by name
template <typename T>
std::vector<typename sak::Section_Data_Manager<T>::Handle_Type> sak::Section_Data_Manager<T>::get_all() const
{
  return m_handles;
}

// Get all the objects' alphabetically sorted names
template <typename T>
std::vector<QString> sak::Section_Data_Manager<T>::get_all_names() const
{
  std::vector<QString> l_result{};
  l_result.reserve(m_handles.size());
  for (auto const& l_handle : m_handles)
  {
    l_result.push_back(l_handle->cmember_at<0>());
  }
  return l_result;
}

// You may create new objects using these two functions. Objects created in this way
// are part of the data management system but nothing outside of it has been notified
// of their presense. Calling has_handle on the handle returned by these functions
// immediately after will return false.

// Make a new object using the supplied data. Project's data management system owns it but
// it is not part of the Project.
template <typename T>
typename sak::Section_Data_Manager<T>::Handle_Type sak::Section_Data_Manager<T>::make_emplace(Data_Type&& a_object)
{
  // Capture the name.
  auto l_name = a_object.cmember_at<0>();

  // Uniqueify the name.
  uniqueify_name(l_name, get_all_names());

  // Capture the data
  auto l_object = std::make_shared<Data_Type>(std::move(a_object));

  // Set the name.
  l_object->member_at<0>() = l_name;

  // Make a handle out of the data.
  return m_factory.make_handle(std::move(l_object));
}

// Make a new file using the default parameters. Project's data management system owns it
// but it is not part of the Project.
template <typename T>
typename sak::Section_Data_Manager<T>::Handle_Type sak::Section_Data_Manager<T>::make_default()
{
  // The default name for a new object.
  static QString const s_name{u8"New " + QString::fromStdString(Data_Type::type())};

  // Copy the name locally so we can edit it.
  auto l_name = s_name;

  // Uniqueify the name.
  uniqueify_name(l_name, get_all_names());

  // Make a new object.
  auto l_object = std::make_shared<Data_Type>(Data_Type{});

  // Set the name.
  l_object->member_at<0>() = s_name;

  // Make a handle out of the data.
  return m_factory.make_handle(std::move(l_object));
}

// Add an object that will rely on the outbound data signals. If nulltpr, nothing happens.
template <typename T>
void sak::Section_Data_Manager<T>::add_signalbox(Signalbox_Type* a_signalbox)
{
  if (a_signalbox != nullptr
      && std::find(m_signalboxes.cbegin(), m_signalboxes.cend(), a_signalbox) == m_signalboxes.cend())
  {
    m_signalboxes.push_back(a_signalbox);
  }
}

// Remove an object that will rely on the outbound data signals. If nulltpr, nothing happens.
template <typename T>
void sak::Section_Data_Manager<T>::remove_signalbox(Signalbox_Type* a_signalbox)
{
  auto l_found = std::find(m_signalboxes.cbegin(), m_signalboxes.cend(), a_signalbox);
  if (l_found != m_signalboxes.cend())
  {
    m_signalboxes.erase(l_found);
  }
}


// Remove all signalboxes
template <typename T>
void sak::Section_Data_Manager<T>::clear_signalboxes()
{
  m_signalboxes.clear();
}

// Swap the data with that of another
template <typename T>
void sak::Section_Data_Manager<T>::swap(Section_Data_Manager& a_other)
{
  using std::swap;

  swap(m_factory, a_other.m_factory);
  swap(m_handles, a_other.m_handles);
  swap(m_signalboxes, a_other.m_signalboxes);
}

/*
template <typename T>
void sak::swap(Section_Data_Manager<T>& a_lhs, Section_Data_Manager<T>& a_rhs)
{
  a_lhs.swap(a_rhs);
}
*/
// Forced Instantiations
//============================================================
template sak::File_Data_Manager;
template sak::Texture_Data_Manager;
