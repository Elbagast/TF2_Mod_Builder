#include "project_data.hpp"

#include "abstract_project_signalbox.hpp"
#include "section_data.hpp"
#include "handle.hpp"
#include "section_data_manager.hpp"
#include "abstract_section_signalbox.hpp"
#include "xml_traits.hpp"
#include "name_utilities.hpp"
#include "tag.hpp"

#include <cassert>
#include <algorithm>
#include <iterator>

#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

#include <sak/name_utilities.hpp>

//---------------------------------------------------------------------------
// Project_Data::Implementation
//---------------------------------------------------------------------------

namespace sak
{
  class Project_Data::Implementation
  {
  public:
    QFileInfo m_filepath;
    File_Data_Manager m_file_manager;
    Texture_Data_Manager m_texture_manager;

    explicit Implementation(QString const& a_filepath):
      m_filepath{a_filepath},
      m_file_manager{},
      m_texture_manager{}
    {
    }
    ~Implementation() = default;

  };
} // namespace sak

//---------------------------------------------------------------------------
// Project_Data
//---------------------------------------------------------------------------

// Special 6
//============================================================
// Construct the project using the supplied filename. If the directory
// does not exist or is inaccessible it will fail. If the file does
// not exist it will attempt to create it and save the initial data
// to it. If the file exists it will attempt to load the data from it.
sak::Project_Data::Project_Data(QString const& a_filepath):
    m_data{std::make_unique<Implementation>(a_filepath)}
{
}
sak::Project_Data::~Project_Data() = default;

sak::Project_Data::Project_Data(Project_Data &&) = default;
sak::Project_Data& sak::Project_Data::operator=(Project_Data &&) = default;

// Interface
//============================================================
QString sak::Project_Data::name() const
{
  return cimp().m_filepath.baseName();
}

QString sak::Project_Data::location() const
{
  return cimp().m_filepath.absolutePath();
}

QString sak::Project_Data::filepath() const
{
  return cimp().m_filepath.absoluteFilePath();
}


// Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::Project_Data::add_signalbox(Abstract_Project_Signalbox* a_signalbox)
{
  qDebug() << "sak::Project_Data::add_signalbox";
  //qDebug() << "adding file signalbox";
  imp().m_file_manager.add_signalbox(a_signalbox);
  //qDebug() << "adding texture signalbox";
  imp().m_texture_manager.add_signalbox(a_signalbox);
  //qDebug() << "done";
}

// Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::Project_Data::remove_signalbox(Abstract_Project_Signalbox* a_signalbox)
{
  qDebug() << "sak::Project_Data::remove_signalbox";
  imp().m_file_manager.remove_signalbox(a_signalbox);
  imp().m_texture_manager.remove_signalbox(a_signalbox);
}


// Clear all the signalboxes so that nothing relies on changes to this.
void sak::Project_Data::clear_signalboxes()
{
  qDebug() << "sak::Project_Data::clear_signalboxes";
  imp().m_file_manager.clear_signalboxes();
  imp().m_texture_manager.clear_signalboxes();
}

template <>
sak::Section_Data_Manager<sak::File_Data>* sak::Project_Data::get_manager<sak::File_Data>()
{
  return get_file_manager();
}

template <>
sak::Section_Data_Manager<sak::Texture_Data>* sak::Project_Data::get_manager<sak::Texture_Data>()
{
  return get_texture_manager();
}

sak::File_Data_Manager* sak::Project_Data::get_file_manager()
{
  return std::addressof(imp().m_file_manager);
}

sak::Texture_Data_Manager* sak::Project_Data::get_texture_manager()
{
  return std::addressof(imp().m_texture_manager);
}


template <>
sak::Section_Data_Manager<sak::File_Data> const* sak::Project_Data::cget_manager<sak::File_Data>() const
{
  return cget_file_manager();
}

template <>
sak::Section_Data_Manager<sak::Texture_Data> const* sak::Project_Data::cget_manager<sak::Texture_Data>() const
{
  return cget_texture_manager();
}

sak::File_Data_Manager const* sak::Project_Data::cget_file_manager() const
{
  return std::addressof(cimp().m_file_manager);
}

sak::Texture_Data_Manager const* sak::Project_Data::cget_texture_manager() const
{
  return std::addressof(cimp().m_texture_manager);
}




// build Project_Data in a way that results in the full interface in the top class.

//---------------------------------------------------------------------------
// Project_Base_Data
//---------------------------------------------------------------------------
// The bit that is detached from everything else.

// Special 6
//============================================================
sak::v2::internal::Project_Base_Data::Project_Base_Data(QString const& a_filepath):
  m_filepath{a_filepath}
{}
sak::v2::internal::Project_Base_Data::~Project_Base_Data() = default;

// Interface
//============================================================
QString sak::v2::internal::Project_Base_Data::name() const
{
  return m_filepath.baseName();
}

QString sak::v2::internal::Project_Base_Data::location() const
{
  return m_filepath.absolutePath();
}

QString sak::v2::internal::Project_Base_Data::filepath() const
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
sak::v2::internal::Project_Signalbox_Imp<T,Args...>::Project_Signalbox_Imp():
  m_signalboxes{}
{}

template <typename T, typename...Args>
sak::v2::internal::Project_Signalbox_Imp<T,Args...>::~Project_Signalbox_Imp() = default;

// Virtuals
//============================================================
// Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
template <typename T, typename...Args>
void sak::v2::internal::Project_Signalbox_Imp<T,Args...>::add_signalbox(v2::Abstract_Chained_Signalbox<T,Args...>* a_signalbox)
{
  if (a_signalbox != nullptr
      && std::find(m_signalboxes.cbegin(), m_signalboxes.cend(), a_signalbox) == m_signalboxes.cend())
  {
    m_signalboxes.push_back(a_signalbox);
  }
}

// Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
template <typename T, typename...Args>
void sak::v2::internal::Project_Signalbox_Imp<T,Args...>::remove_signalbox(v2::Abstract_Chained_Signalbox<T,Args...>* a_signalbox)
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
void sak::v2::internal::Project_Signalbox_Imp<T,Args...>::clear_signalboxes()
{
  m_signalboxes.clear();
}

// Internal Interface
//============================================================
template <typename T, typename...Args>
std::vector<sak::v2::Abstract_Chained_Signalbox<T,Args...>*>& sak::v2::internal::Project_Signalbox_Imp<T,Args...>::get_signalboxes()
{
  return m_signalboxes;
}

template <typename T, typename...Args>
std::vector<sak::v2::Abstract_Chained_Signalbox<T,Args...>*> const& sak::v2::internal::Project_Signalbox_Imp<T,Args...>::cget_signalboxes() const
{
  return m_signalboxes;
}

//---------------------------------------------------------------------------
// Project_Chained_Signalbox_Imp<ASBD,Args...>
//---------------------------------------------------------------------------
// Create a class that allows triggering the signals

template <typename T_Base, typename T>
sak::v2::internal::Project_Chained_Signalbox_Imp<T_Base,T>::Project_Chained_Signalbox_Imp() = default;

template <typename T_Base, typename T>
sak::v2::internal::Project_Chained_Signalbox_Imp<T_Base,T>::~Project_Chained_Signalbox_Imp() = default;

// calls each of these on all the stored signalboxes.

// When a handle has its data changed, this is called.
template <typename T_Base, typename T>
void sak::v2::internal::Project_Chained_Signalbox_Imp<T_Base,T>::changed(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->changed(a_handle);
}

// When a handle has its data changed in a specific place, this is called.
// a_section == 0 denotes the name and may have special logic requirements.
template <typename T_Base, typename T>
void sak::v2::internal::Project_Chained_Signalbox_Imp<T_Base,T>::changed_at(Handle<T> const& a_handle, std::size_t a_section)
{
  for (auto l_item : get_signalboxes()) l_item->changed_at(a_handle, a_section);
}

// When a handle has been added, this is called.
template <typename T_Base, typename T>
void sak::v2::internal::Project_Chained_Signalbox_Imp<T_Base,T>::added(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->added(a_handle);
}

// When a handle has been removed, this is called.
template <typename T_Base, typename T>
void sak::v2::internal::Project_Chained_Signalbox_Imp<T_Base,T>::removed(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->removed(a_handle);
}

// When a handle editor is to be opened, this is called.
template <typename T_Base, typename T>
void sak::v2::internal::Project_Chained_Signalbox_Imp<T_Base,T>::requests_editor(Handle<T> const& a_handle)
{
  for (auto l_item : get_signalboxes()) l_item->requests_editor(a_handle);
}

// When focus is changed to be on a handle, call this
template <typename T_Base, typename T>
void sak::v2::internal::Project_Chained_Signalbox_Imp<T_Base,T>::requests_focus(Handle<T> const& a_handle)
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
sak::v2::internal::Project_Section_Data_Imp<T>::Project_Section_Data_Imp():
  m_factory{},
  m_handles{}
{}

template <typename T>
sak::v2::internal::Project_Section_Data_Imp<T>::~Project_Section_Data_Imp() = default;

// Public Interface
//============================================================
// Are there any handles of this type in the currently active project data?
template <typename T>
bool sak::v2::internal::Project_Section_Data_Imp<T>::empty(Tag<T>&&) const
{
  return m_handles.empty();
}

// How handles of this type in the currently active project data?
template <typename T>
std::size_t sak::v2::internal::Project_Section_Data_Imp<T>::count(Tag<T>&&) const
{
  return m_handles.size();
}

// Is this handle in the currently active project data?
template <typename T>
bool sak::v2::internal::Project_Section_Data_Imp<T>::has_handle(Handle<T> const& a_handle) const
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
// member of the objects they reference.
template <typename T>
sak::Handle<T> sak::v2::internal::Project_Section_Data_Imp<T>::get_handle_at(Tag<T>&&, std::size_t a_index) const
{
  return m_handles.at(a_index);
}

// Get all the handles alphabetically sorted by name
template <typename T>
std::vector<sak::Handle<T>> sak::v2::internal::Project_Section_Data_Imp<T>::get_all_handles(Tag<T>&&) const
{
  return m_handles;
}

// Get all the objects' alphabetically sorted names
template <typename T>
std::vector<QString> sak::v2::internal::Project_Section_Data_Imp<T>::get_all_names(Tag<T>&&) const
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
sak::Handle<T> sak::v2::internal::Project_Section_Data_Imp<T>::make_emplace(T&& a_object)
{
  // Capture the name.
  auto l_name = a_object.cmember_at<0>();

  // Uniqueify the name.
  uniqueify_name(l_name, get_all_names(Tag<T>()));

  // Capture the data
  auto l_object = std::make_shared<T>(std::move(a_object));

  // Set the name.
  l_object->member_at<0>() = l_name;

  // Make a handle out of the data.
  return m_factory.make_handle(std::move(l_object));
}

// Make a new file using the default parameters. Project's data management system owns it
// but it is not part of the Project.
template <typename T>
sak::Handle<T> sak::v2::internal::Project_Section_Data_Imp<T>::make_default(Tag<T>&&)
{
  // The default name for a new object.
  static QString const s_name{u8"New " + QString::fromStdString(T::type())};

  // Copy the name locally so we can edit it.
  auto l_name = s_name;

  // Uniqueify the name.
  uniqueify_name(l_name, get_all_names(Tag<T>()));

  // Make a new object.
  auto l_object = std::make_shared<T>(T{});

  // Set the name.
  l_object->member_at<0>() = s_name;

  // Make a handle out of the data.
  return m_factory.make_handle(std::move(l_object));
}




//---------------------------------------------------------------------------
// Project_Chained_Data<T,Args...>
//---------------------------------------------------------------------------
// Special 6
//============================================================
template <typename T, typename...Args>
sak::v2::Project_Chained_Data<T,Args...>::Project_Chained_Data(QString const& a_filepath):
  Inh1(a_filepath),
  Inh2(),
  Inh3()
{
}

template <typename T, typename...Args>
sak::v2::Project_Chained_Data<T,Args...>::~Project_Chained_Data() = default;


template class sak::v2::Project_Data;


namespace
{
  void test()
  {
    using namespace sak;
    using namespace sak::v2;


    using File_Tag = Tag<File_Data>;
    using Texture_Tag = Tag<Texture_Data>;

    QString l_filepath{u8"blah"};
    sak::v2::Project_Data l_project{l_filepath};
    l_project.name();
    l_project.location();
    l_project.filepath();

    l_project.add_signalbox(nullptr);
    l_project.remove_signalbox(nullptr);
    l_project.clear_signalboxes();

    File_Handle l_fh{};
    Texture_Handle l_th{};

    l_project.changed(l_fh);
    l_project.changed_at(l_fh, 0);
    l_project.added(l_fh);
    l_project.removed(l_fh);
    l_project.requests_editor(l_fh);
    l_project.requests_focus(l_fh);

    l_project.changed(l_th);
    l_project.changed_at(l_th, 0);
    l_project.added(l_th);
    l_project.removed(l_th);
    l_project.requests_editor(l_th);
    l_project.requests_focus(l_th);

    l_project.empty(File_Tag{});
    l_project.count(File_Tag{});
    l_project.has_handle(l_fh);
    l_project.get_handle_at(File_Tag{},0);
    l_project.get_all_handles(File_Tag{});
    l_project.get_all_names(File_Tag{});
    l_project.make_emplace(File_Data{});
    l_project.make_default(File_Tag{});

    l_project.empty(Texture_Tag{});
    l_project.count(Texture_Tag{});
    l_project.has_handle(l_th);
    l_project.get_handle_at(Texture_Tag{},0);
    l_project.get_all_handles(Texture_Tag{});
    l_project.get_all_names(Texture_Tag{});
    l_project.make_emplace(Texture_Data{});
    l_project.make_default(Texture_Tag{});


  }
}

