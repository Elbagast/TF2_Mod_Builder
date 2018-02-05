#include "project_data.hpp"

#include "data_definitions.hpp"
#include "class_definitions.hpp"
#include "data.hpp"
#include "handle.hpp"
#include "handle_factory.hpp"
#include "tag.hpp"
#include "abstract_project_signalbox.hpp"
#include "name_utilities.hpp"

#include <cassert>
#include <algorithm>
#include <iterator>
#include <type_traits>

#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>



//---------------------------------------------------------------------------
// Project_Base_Data
//---------------------------------------------------------------------------
// The bit that is detached from everything else.

// Special 6
//============================================================
sak::internal::Project_Base_Data::Project_Base_Data(QString const& a_filepath):
  m_filepath{a_filepath}
{}
sak::internal::Project_Base_Data::~Project_Base_Data() = default;

// Interface
//============================================================
QString sak::internal::Project_Base_Data::name() const
{
  return m_filepath.baseName();
}

QString sak::internal::Project_Base_Data::location() const
{
  return m_filepath.absolutePath();
}

QString sak::internal::Project_Base_Data::filepath() const
{
  return m_filepath.absoluteFilePath();
}

//---------------------------------------------------------------------------
// Project_Signalbox_Imp<T,Args...>
//---------------------------------------------------------------------------
// Implement the things that are not section dependent and will be used by
// other parts of the implementation.

// Special 6
//============================================================
template <typename T, typename...Args>
sak::internal::Project_Signalbox_Imp<T,Args...>::Project_Signalbox_Imp():
  m_signalboxes{}
{}

template <typename T, typename...Args>
sak::internal::Project_Signalbox_Imp<T,Args...>::~Project_Signalbox_Imp() = default;

// Virtuals
//============================================================
// Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
template <typename T, typename...Args>
void sak::internal::Project_Signalbox_Imp<T,Args...>::add_signalbox(Signalbox_Type* a_signalbox)
{
  if (a_signalbox != nullptr
      && std::find(m_signalboxes.cbegin(), m_signalboxes.cend(), a_signalbox) == m_signalboxes.cend())
  {
    m_signalboxes.push_back(a_signalbox);
  }
}

// Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
template <typename T, typename...Args>
void sak::internal::Project_Signalbox_Imp<T,Args...>::remove_signalbox(Signalbox_Type* a_signalbox)
{
  if (a_signalbox == nullptr)
  {
    return;
  }
  auto l_found = std::find(m_signalboxes.cbegin(), m_signalboxes.cend(), a_signalbox);
  if (l_found != m_signalboxes.cend())
  {
    m_signalboxes.erase(l_found);
  }
}

// Clear all the signalboxes so that nothing relies on changes to this.
template <typename T, typename...Args>
void sak::internal::Project_Signalbox_Imp<T,Args...>::clear_signalboxes()
{
  m_signalboxes.clear();
}

// Internal Interface
//============================================================
template <typename T, typename...Args>
std::vector<typename sak::internal::Project_Signalbox_Imp<T,Args...>::Signalbox_Type*>& sak::internal::Project_Signalbox_Imp<T,Args...>::get_signalboxes()
{
  return m_signalboxes;
}

template <typename T, typename...Args>
std::vector<typename sak::internal::Project_Signalbox_Imp<T,Args...>::Signalbox_Type*> const& sak::internal::Project_Signalbox_Imp<T,Args...>::cget_signalboxes() const
{
  return m_signalboxes;
}

//---------------------------------------------------------------------------
// Project_Chained_Signalbox_Imp<ASBD,Args...>
//---------------------------------------------------------------------------
// Create a class that allows triggering the signals

template <typename T_Base, typename T>
sak::internal::Project_Chained_Signalbox_Imp<T_Base,T>::Project_Chained_Signalbox_Imp() = default;

template <typename T_Base, typename T>
sak::internal::Project_Chained_Signalbox_Imp<T_Base,T>::~Project_Chained_Signalbox_Imp() = default;

// calls each of these on all the stored signalboxes.

// When a handle has its data changed, this is called.
template <typename T_Base, typename T>
void sak::internal::Project_Chained_Signalbox_Imp<T_Base,T>::changed(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->changed(a_handle);
}

// When a handle has its name changed, this is called.
template <typename T_Base, typename T>
void sak::internal::Project_Chained_Signalbox_Imp<T_Base,T>::changed_name(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->changed_name(a_handle);
}

// When a handle has its data changed in a specific place, this is called.
// a_section == 0 denotes the name and may have special logic requirements.
template <typename T_Base, typename T>
void sak::internal::Project_Chained_Signalbox_Imp<T_Base,T>::changed_at(Handle<T> const& a_handle, std::size_t a_section)
{
  for (auto l_item : get_signalboxes()) l_item->changed_at(a_handle, a_section);
}

// When a handle has been added, this is called.
template <typename T_Base, typename T>
void sak::internal::Project_Chained_Signalbox_Imp<T_Base,T>::added(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->added(a_handle);
}

// When a handle has been removed, this is called.
template <typename T_Base, typename T>
void sak::internal::Project_Chained_Signalbox_Imp<T_Base,T>::removed(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->removed(a_handle);
}

// When a handle editor is to be opened, this is called.
template <typename T_Base, typename T>
void sak::internal::Project_Chained_Signalbox_Imp<T_Base,T>::requests_editor(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->requests_editor(a_handle);
}

// When focus is changed to be on a handle, call this
template <typename T_Base, typename T>
void sak::internal::Project_Chained_Signalbox_Imp<T_Base,T>::requests_focus(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->requests_focus(a_handle);
}

//---------------------------------------------------------------------------
// Project_Section_Data_Imp<T>
//---------------------------------------------------------------------------
// the bit that manages data for a given type. No signals emitted.

// Special 6
//============================================================
template <typename T>
sak::internal::Project_Section_Data_Imp<T>::Project_Section_Data_Imp():
  m_factory{},
  m_handles{}
{}

template <typename T>
sak::internal::Project_Section_Data_Imp<T>::~Project_Section_Data_Imp() = default;

// Public Interface
//============================================================
// Are there any handles of this type in the currently active project data?
template <typename T>
bool sak::internal::Project_Section_Data_Imp<T>::empty(Tag<T>&&) const
{
  return m_handles.empty();
}

// How handles of this type in the currently active project data?
template <typename T>
std::size_t sak::internal::Project_Section_Data_Imp<T>::count(Tag<T>&&) const
{
  return m_handles.size();
}

// Is this handle in the currently active project data?
template <typename T>
bool sak::internal::Project_Section_Data_Imp<T>::has_handle(Handle<T> const& a_handle) const
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

// Is this handle in the currently active project data?
template <typename T>
bool sak::internal::Project_Section_Data_Imp<T>::has_name(Tag<T>&&, QString const& a_name) const
{
  // MAKE THIS
  return false;
}

// Get the handle at this index. Handles are sorted alphabetically by the name
// member of the objects they reference.
template <typename T>
sak::Handle<T> sak::internal::Project_Section_Data_Imp<T>::get_handle_at(Tag<T>&&, std::size_t a_index) const
{
  if (a_index < m_handles.size())
  {
    return m_handles.at(a_index);
  }
  else
  {
    return Handle<T>{};
  }
}

// Get the handle with this name. If the name is invalid a null handle is returned.
template <typename T>
sak::Handle<T> sak::internal::Project_Section_Data_Imp<T>::get_handle_named(Tag<T>&&, QString const& a_name) const
{
  // MAKE THIS
  return sak::Handle<T>{};
}
// Get all the handles alphabetically sorted by name
template <typename T>
std::vector<sak::Handle<T>> sak::internal::Project_Section_Data_Imp<T>::get_all_handles(Tag<T>&&) const
{
  return m_handles;
}

// Get all the objects' alphabetically sorted names
template <typename T>
std::vector<QString> sak::internal::Project_Section_Data_Imp<T>::get_all_names(Tag<T>&&) const
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
sak::Handle<T> sak::internal::Project_Section_Data_Imp<T>::make_emplace(Data<T>&& a_object) const
{
  // Capture the name.
  auto l_name = a_object.cmember_at<0>();

  // Uniqueify the name.
  uniqueify_name(l_name, get_all_names(Tag<T>()));

  // Capture the data
  auto l_object = std::make_shared<Data<T>>(std::move(a_object));

  // Set the name.
  l_object->member_at<0>() = l_name;

  // Make a handle out of the data.
  return m_factory.make_handle(std::move(l_object));
}

// Make a new file using the default parameters. Project's data management system owns it
// but it is not part of the Project.
template <typename T>
sak::Handle<T> sak::internal::Project_Section_Data_Imp<T>::make_default(Tag<T>&&) const
{
  static_assert(std::is_same_v<T,File_Definition> || std::is_same_v<T,Texture_Definition>,
                "bad type here.");

  using Typestring_Type = typename T::Typestring_Type;
  // The default name for a new object.
  static QString const s_name{u8"New " + QString::fromStdString(Typestring_Type::data())};

  // Copy the name locally so we can edit it.
  auto l_name = s_name;

  // Uniqueify the name.
  uniqueify_name(l_name, get_all_names(Tag<T>()));

  // Make a new object.
  auto l_object = std::make_shared<Data<T>>();

  // Set the name.
  //l_object->member_at<0>() = s_name;
  l_object->name() = l_name;

  // Make a handle out of the data.
  return m_factory.make_handle(std::move(l_object));
}

// Attempt to add a handle to the data and return true if it succeeds. Will
// fail and return false if the handle is null or already present in the data.
template <typename T>
bool sak::internal::Project_Section_Data_Imp<T>::add(Handle<T> const& a_handle)
{
  if (this->has_handle(a_handle)
      && std::find(m_handles.cbegin(), m_handles.cend(), a_handle) == m_handles.cend())
  {
    m_handles.push_back(a_handle);
    return true;
  }
  return false;
}

// Attempt to remove a handle from the data and return true if it succeeds. Will
// fail and return false if the handle is null or not present in the data.
template <typename T>
bool sak::internal::Project_Section_Data_Imp<T>::remove(Handle<T> const& a_handle)
{
  if (this->has_handle(a_handle))
  {
    auto l_found = std::find(m_handles.cbegin(), m_handles.cend(), a_handle);
    if (l_found != m_handles.cend())
    {
      m_handles.erase(l_found);
      return true;
    }
  }
  return false;
}

//---------------------------------------------------------------------------
// Project_Chained_Data<T,Args...>
//---------------------------------------------------------------------------
// Special 6
//============================================================
template <typename T, typename...Args>
sak::Project_Chained_Data<T,Args...>::Project_Chained_Data(QString const& a_filepath):
  Inh1(a_filepath),
  Inh2(),
  Inh3()
{
}

template <typename T, typename...Args>
sak::Project_Chained_Data<T,Args...>::~Project_Chained_Data() = default;

//template class sak::internal::Project_Signalbox_Imp<sak::File_Definition,sak::Texture_Definition>;
//template class sak::internal::Project_Section_Data_Imp<sak::File_Definition>;
//template class sak::internal::Project_Section_Data_Imp<sak::Texture_Definition>;

template class sak::Project_Data;


