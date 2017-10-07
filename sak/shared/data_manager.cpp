#include "data_manager.hpp"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

#include <sak/shared/object.hpp>
#include <sak/shared/manager.hpp>
#include <sak/shared/xml_traits.hpp>
#include <sak/shared/signalbox.hpp>

#include <sak/name_utilities.hpp>

#include <cassert>


//---------------------------------------------------------------------------
// sak::shared::data_manager<T>
//---------------------------------------------------------------------------
// Splitting out the repeated backend management system for project.

// Constants
//============================================================
namespace
{
  template <typename T>
  struct section_title
  {
    //static QString const s_value;
    static QString value()
    {
      static QString const s_value{QString::fromStdString(T::type()) + u8"s" };
      return s_value;
    }
  };

  QString const c_count_title{ u8"Count" };
}

//template <typename T>
//QString const section_title<T>::s_value{ QString::fromStdString(T::type()) + u8"s"  };

// Special 6
//============================================================
template <typename T>
sak::shared::data_manager<T>::data_manager():
  m_manager{},
  m_handles{},
  m_signalboxes{}
{}

template <typename T>
sak::shared::data_manager<T>::~data_manager() = default;

// Virtuals
//============================================================
template <typename T>
void sak::shared::data_manager<T>::changed(handle_type const& a_handle)
{
  qDebug() << "sak::shared::data_manager<T>::changed "<< a_handle.id().value();
  // This thing must exist
  assert(flamingo::not_null(a_handle));
  assert(std::find(m_handles.cbegin(), m_handles.cend(), a_handle) != m_handles.cend());

  for (signalbox_type* l_item : m_signalboxes) l_item->changed(a_handle);
}

// When a File has its data changed in a specific place, this is called.
template <typename T>
void sak::shared::data_manager<T>::changed_at(handle_type const& a_handle, std::size_t a_section)
{
  qDebug() << "sak::shared::data_manager<T>::changed_at "<< a_handle.id().value() << ", " << a_section;
  // This thing must exist
  assert(flamingo::not_null(a_handle));
  assert(std::find(m_handles.cbegin(), m_handles.cend(), a_handle) != m_handles.cend());

  for (signalbox_type* l_item : m_signalboxes) l_item->changed_at(a_handle, a_section);
}

// When a File has been added, this is called.
template <typename T>
void sak::shared::data_manager<T>::added(handle_type const& a_handle)
{
  qDebug() << "sak::shared::data_manager<T>::added "<< a_handle.id().value();
  // This thing must exist
  assert(flamingo::not_null(a_handle));
  assert(std::addressof(m_manager) == a_handle.manager());
  assert(m_manager.is_valid(a_handle.id()));
  // but not yet be part of the Project
  assert(std::find(m_handles.cbegin(), m_handles.cend(), a_handle) == m_handles.cend());
  m_handles.push_back(a_handle);

  for (signalbox_type* l_item : m_signalboxes) l_item->added(a_handle);
}
// When a File has been removed, this is called.
template <typename T>
void sak::shared::data_manager<T>::removed(handle_type const& a_handle)
{
  qDebug() << "sak::shared::data_manager<T>::removed "<< a_handle.id().value();
  assert(flamingo::not_null(a_handle));
  auto l_found = std::find(m_handles.begin(), m_handles.end(), a_handle);
  assert(l_found != m_handles.cend());
  assert(std::addressof(a_handle) != std::addressof(*l_found));

  // Copy the file::extended_handle locally. We don't know where it came from and have to propagate
  // the signal from here rather than who knows where to insure the signal reference stays
  // valid for all that need it.
  handle_type l_handle = a_handle;

  // Now kill it, because if it's still in the project the signal will call back to find it
  // is still present.
  m_handles.erase(l_found);

  for (signalbox_type* l_item : m_signalboxes) l_item->removed(l_handle);
}
// When a File requests an editor, this is called.
template <typename T>
void sak::shared::data_manager<T>::requests_editor(handle_type const& a_handle)
{
  qDebug() << "sak::shared::data_manager<T>::requests_editor "<< a_handle.id().value();
  // This thing must exist
  assert(flamingo::not_null(a_handle));
  assert(std::find(m_handles.cbegin(), m_handles.cend(), a_handle) != m_handles.cend());

  for (signalbox_type* l_item : m_signalboxes) l_item->requests_editor(a_handle);
}

// When a File requests an editor, this is called.
template <typename T>
void sak::shared::data_manager<T>::requests_focus(handle_type const& a_handle)
{
  qDebug() << "sak::shared::data_manager<T>::requests_focus "<< a_handle.id().value();
  // This thing must exist
  assert(flamingo::not_null(a_handle));
  assert(std::find(m_handles.cbegin(), m_handles.cend(), a_handle) != m_handles.cend());

  for (signalbox_type* l_item : m_signalboxes) l_item->requests_focus(a_handle);
}

// Public Interface
//============================================================
// Are there any Files in this Project?
template <typename T>
bool sak::shared::data_manager<T>::empty() const
{
  return m_handles.empty();
}

// How many any Files are in this Project?
template <typename T>
std::size_t sak::shared::data_manager<T>::count() const
{
  return m_handles.size();
}

template <typename T>
bool sak::shared::data_manager<T>::has_handle(handle_type const& a_handle) const
{
  return std::find(m_handles.cbegin(), m_handles.cend(), a_handle) != m_handles.cend();
}

// Get the file at this index, asssuming the Files are alphabetically sorted by name
template <typename T>
typename sak::shared::data_manager<T>::handle_type sak::shared::data_manager<T>::get_at(std::size_t a_index) const
{
  return m_handles.at(a_index);
}

// Get all the Files alphabetically sorted by name
template <typename T>
std::vector<typename sak::shared::data_manager<T>::handle_type> sak::shared::data_manager<T>::get_all() const
{
  return m_handles;
}


// Get all the Files alphabetically sorted names
template <typename T>
std::vector<QString> sak::shared::data_manager<T>::get_all_names() const
{
  std::vector<QString> l_result{};
  l_result.reserve(m_handles.size());
  for (auto const& l_handle : m_handles)
  {
    l_result.push_back(l_handle->cmember_at<0>());
  }
  return l_result;
}

// You may create new Files using these two functions. Files created in this way
// are part of the Project's data management system but have not yet been added to the
// Project properly. That will only happen when the Project recieves a signal via its
// Project_Signalbox that it should be addeed.

// Make a new file using the supplied data. Project's data management system owns it but
// it is not part of the Project.
template <typename T>
typename sak::shared::data_manager<T>::handle_type sak::shared::data_manager<T>::make_emplace(object_type&& a_object)
{
  return m_manager.make_handle(std::move(a_object));
}

// Make a new file using the default parameters. Project's data management system owns it
// but it is not part of the Project.
template <typename T>
typename sak::shared::data_manager<T>::handle_type sak::shared::data_manager<T>::make()
{
  // uniqueify the name.
  QString l_name{u8"New " + QString::fromStdString(object_type::type())};
  uniqueify_name(l_name, get_all_names());
  object_type l_object{};
  l_object.member_at<0>() = l_name;
  return make_emplace(std::move(l_object));
}

template <typename T>
void sak::shared::data_manager<T>::to_xmlstream(QXmlStreamWriter& a_stream) const
{
  // Start the Files block
  a_stream.writeStartElement(section_title<T>::value());
  a_stream.writeTextElement(c_count_title, QString::number(count()));

  for (auto const& l_handle : m_handles)
  {
    sak::shared::xml_traits<object_type>::to_stream(a_stream, *l_handle);
  }

  // End the Files block
  a_stream.writeEndElement();
}

template <typename T>
void sak::shared::data_manager<T>::from_xmlstream(QXmlStreamReader& a_stream)
{
  // Read the Files
  if (a_stream.readNextStartElement() && a_stream.name().toString() == section_title<T>::value())
  {
    qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
    //qDebug() << "Files:";
    int l_count {0};

    // <Count>
    if (a_stream.readNextStartElement() && a_stream.name().toString() == c_count_title)
    {
      qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();

      l_count = a_stream.readElementText().toInt();
      //qDebug() << "Count = " << l_count;

      qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
    }
    else
    {
      qDebug() << "Didn't find " << section_title<T>::value() << " " << c_count_title;
      qDebug() << "Last element: " << a_stream.qualifiedName().toString();
      // file format error
    }

    m_handles.reserve(l_count);
    // read the files
    for (int l_index = 0; l_index != l_count; ++l_index)
    {
      object_type l_object{};
      sak::shared::xml_traits<object_type>::from_stream(a_stream, l_object);

      auto l_handle = make_emplace(std::move(l_object));
      m_handles.push_back(std::move(l_handle));
    }
    // </Files>

    qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
    if (a_stream.readNext() != QXmlStreamReader::Characters)
    {
      // Bad file structure
      qDebug() << "Didn't find Characters";
    }
    qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
    if (a_stream.readNext() != QXmlStreamReader::EndElement)
    {
      // Bad file structure
      qDebug() << "Didn't find EndElement";
    }
    qDebug() << "tokenstring = " << a_stream.tokenString() << a_stream.name().toString();
  }
  else
  {
    // Bad file structure
    qDebug() << "Didn't find " << section_title<T>::value() << "...";
    qDebug() << "Last element: " << a_stream.qualifiedName().toString();
  }
}


// Add an object that will rely on the outbound data signals. If nulltpr, nothing happens.
template <typename T>
void sak::shared::data_manager<T>::add_signalbox(signalbox_type* a_signalbox)
{
  if (a_signalbox != nullptr
      && std::find(m_signalboxes.cbegin(), m_signalboxes.cend(), a_signalbox) == m_signalboxes.cend())
  {
    m_signalboxes.push_back(a_signalbox);
  }
}

// Remove an object that will rely on the outbound data signals. If nulltpr, nothing happens.
template <typename T>
void sak::shared::data_manager<T>::remove_signalbox(signalbox_type* a_signalbox)
{
  auto l_found = std::find(m_signalboxes.cbegin(), m_signalboxes.cend(), a_signalbox);
  if (l_found != m_signalboxes.cend())
  {
    m_signalboxes.erase(l_found);
  }
}


// Remove all signalboxes
template <typename T>
void sak::shared::data_manager<T>::clear_signalboxes()
{
  m_signalboxes.clear();
}

// Forced Instantiations
//============================================================
template sak::file::data_manager;
template sak::texture::data_manager;
