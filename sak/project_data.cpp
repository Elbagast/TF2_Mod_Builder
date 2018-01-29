#include "project_data.hpp"

#include "abstract_project_signalbox.hpp"
#include "section_data.hpp"
#include "section_handle.hpp"
#include "section_data_manager.hpp"
#include "abstract_section_signalbox.hpp"
#include "xml_traits.hpp"
#include "name_utilities.hpp"

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
