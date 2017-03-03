#include "data_manager.hpp"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

#include <sak/shared/object.hpp>
#include <sak/shared/manager.hpp>
#include <sak/shared/extended_manager.hpp>
#include <sak/shared/xml_traits.hpp>
#include <sak/shared/project_access.hpp>

#include <sak/name_utilities.hpp>


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
sak::shared::data_manager<T>::data_manager(project::object& a_project):
  inherited_type(),
  m_project{a_project},
  m_emanager{interface_traits_type(&m_project)},
  m_ehandles{}
{}

template <typename T>
sak::shared::data_manager<T>::~data_manager() = default;

// Virtuals
//============================================================
template <typename T>
void sak::shared::data_manager<T>::changed(extended_handle_type const& a_ehandle)
{
  qDebug() << "sak::shared::data_manager<T>::changed "<< a_ehandle.id().get();
  // This thing must exist
  assert(a_ehandle.is_valid());
  assert(std::find(m_ehandles.cbegin(), m_ehandles.cend(), a_ehandle) != m_ehandles.cend());
}

// When a File has its data changed in a specific place, this is called.
template <typename T>
void sak::shared::data_manager<T>::changed_at(extended_handle_type const& a_ehandle, std::size_t a_section)
{
  qDebug() << "sak::shared::data_manager<T>::changed_at "<< a_ehandle.id().get() << ", " << a_section;
  // This thing must exist
  assert(a_ehandle.is_valid());
  assert(std::find(m_ehandles.cbegin(), m_ehandles.cend(), a_ehandle) != m_ehandles.cend());
}

// When a File has been added, this is called.
template <typename T>
void sak::shared::data_manager<T>::added(extended_handle_type const& a_ehandle)
{
  qDebug() << "sak::shared::data_manager<T>::added "<< a_ehandle.id().get();
  // This thing must exist
  assert(a_ehandle.is_valid());
  // but not yet be part of the Project
  assert(std::find(m_ehandles.cbegin(), m_ehandles.cend(), a_ehandle) == m_ehandles.cend());
  m_ehandles.push_back(a_ehandle);
}
// When a File has been removed, this is called.
template <typename T>
void sak::shared::data_manager<T>::removed(extended_handle_type const& a_ehandle)
{
  qDebug() << "sak::shared::data_manager<T>::removed "<< a_ehandle.id().get();
  assert(a_ehandle.is_valid());
  auto l_found = std::find(m_ehandles.begin(), m_ehandles.end(), a_ehandle);
  assert(l_found != m_ehandles.cend());
  assert(std::addressof(a_ehandle) != std::addressof(*l_found));

  // Copy the file::extended_handle locally. We don't know where it came from and have to propagate
  // the signal from here rather than who knows where to insure the signal reference stays
  // valid for all that need it.
  file::extended_handle l_ehandle = a_ehandle;

  // Now kill it, because if it's still in the project the signal will call back to find it
  // is still present.
  m_ehandles.erase(l_found);
}
// When a File requests an editor, this is called.
template <typename T>
void sak::shared::data_manager<T>::requests_editor(extended_handle_type const& a_ehandle)
{
  qDebug() << "sak::shared::data_manager<T>::requests_editor "<< a_ehandle.id().get();
  // This thing must exist
  assert(a_ehandle.is_valid());
  assert(std::find(m_ehandles.cbegin(), m_ehandles.cend(), a_ehandle) != m_ehandles.cend());
}

// When a File requests an editor, this is called.
template <typename T>
void sak::shared::data_manager<T>::requests_focus(extended_handle_type const& a_ehandle)
{
  qDebug() << "sak::shared::data_manager<T>::requests_focus "<< a_ehandle.id().get();
  // This thing must exist
  assert(a_ehandle.is_valid());
  assert(std::find(m_ehandles.cbegin(), m_ehandles.cend(), a_ehandle) != m_ehandles.cend());
}

// Public Interface
//============================================================
// Are there any Files in this Project?
template <typename T>
bool sak::shared::data_manager<T>::empty() const
{
  return m_ehandles.empty();
}

// How many any Files are in this Project?
template <typename T>
std::size_t sak::shared::data_manager<T>::count() const
{
  return m_ehandles.size();
}

template <typename T>
bool sak::shared::data_manager<T>::has_handle(extended_handle_type const& a_ehandle) const
{
  return std::find(m_ehandles.cbegin(), m_ehandles.cend(), a_ehandle) != m_ehandles.cend();
}

// Get the file at this index, asssuming the Files are alphabetically sorted by name
template <typename T>
typename sak::shared::data_manager<T>::extended_handle_type sak::shared::data_manager<T>::get_at(std::size_t a_index) const
{
  return m_ehandles.at(a_index);
}

// Get all the Files alphabetically sorted by name
template <typename T>
std::vector<typename sak::shared::data_manager<T>::extended_handle_type> sak::shared::data_manager<T>::get_all() const
{
  return m_ehandles;
}


// Get all the Files alphabetically sorted names
template <typename T>
std::vector<QString> sak::shared::data_manager<T>::get_all_names() const
{
  std::vector<QString> l_result{};
  l_result.reserve(m_ehandles.size());
  for (auto const& l_ehandle : m_ehandles)
  {
    l_result.push_back(l_ehandle.cget().cat<0>().cget());
  }
  return l_result;
}

// You may create new Files using these two functions. Files created in this way
// are part of the Project's data management system but have not yet been added to the
// Project properly. That will only happen when the Project recieves a signal via its
// Project_Signalbox that it should be addeed.

// Make a new file using the supplied data. Project's data management system owns it but
// it is not part of the Proeject.
template <typename T>
typename sak::shared::data_manager<T>::extended_handle_type sak::shared::data_manager<T>::make_emplace(object_type&& a_object)
{
  return m_emanager.emplace_data(std::move(a_object));
}

// Make a new file using the default parameters. Project's data management system owns it
// but it is not part of the Project.
template <typename T>
typename sak::shared::data_manager<T>::extended_handle_type sak::shared::data_manager<T>::make()
{
  // uniqueify the name.
  QString l_name{u8"New " + QString::fromStdString(object_type::type())};
  uniqueify_name(l_name, project_access<object_type>::get_all_names(m_project));
  file::object l_object{};
  l_object.at<0>().get() = l_name;
  return make_emplace(std::move(l_object));
}

template <typename T>
void sak::shared::data_manager<T>::to_xmlstream(QXmlStreamWriter& a_stream) const
{
  // Start the Files block
  a_stream.writeStartElement(section_title<T>::value());
  a_stream.writeTextElement(c_count_title, QString::number(count()));

  for (auto const& l_ehandle : m_ehandles)
  {
    sak::shared::xml_traits<object_type>::to_stream(a_stream, l_ehandle.cget());
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
    //qDebug() << "Files:";
    int l_count {0};

    // <Count>
    if (a_stream.readNextStartElement() && a_stream.name().toString() == c_count_title)
    {
      l_count = a_stream.readElementText().toInt();
      //qDebug() << "Count = " << l_count;

      // </Count>
      a_stream.readNext();
    }
    else
    {
      qDebug() << "Didn't find " << section_title<T>::value() << " " << c_count_title;
      // file format error
    }

    m_ehandles.reserve(l_count);
    // read the files
    for (int l_index = 0; l_index != l_count; ++l_index)
    {
      object_type l_object{};
      sak::shared::xml_traits<object_type>::from_stream(a_stream, l_object);

      auto l_handle = make_emplace(std::move(l_object));
      m_ehandles.push_back(std::move(l_handle));
    }
    // </Files>
    a_stream.readNext();

  }
  else
  {
    // Bad file structure
    qDebug() << "Didn't find <" << section_title<T>::value() << ">";
  }
}

// Forced Instantiations
//============================================================
template sak::file::data_manager;
