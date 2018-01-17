#include "project_data.hpp"

#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <cassert>
#include <algorithm>
#include <iterator>

#include "abstract_project_signalbox.hpp"

#include "command_history.hpp"

#include <sak/exceptions/exception.hpp>

#include "section_data.hpp"
#include "section_handle.hpp"
#include "section_data_manager.hpp"
#include "abstract_section_signalbox.hpp"
#include "section_interface.hpp"
#include "section_command.hpp"
#include "section_xml_traits.hpp"

#include <sak/name_utilities.hpp>


/*
Looking at the is again there's a lot of repeat code arodun the signalling for
different types. This could be reduced by keeping the shared::abstract::signalbox
separate and inside the shared::data_manager template instead of having a single
one that merges them all together. This would mean a number of essentially
duplicated references as each project::object dependent is referenced once for
each type managed, unless some kind of switching class is built.

Is it worth thinking of project::object as a template class instead? It is
essentially being built as a shared front-end for a number of types that share
implementations. Although it only shows up once so that's probably a hassle.

Currently:
project::object
  signal_dispatcher
    signalbox<T>
      signal<T>
  data_manager<T>
    manager<T>
      handle<T>
        <T>
  command_history
    command
      command<T>

There is an issue:
- currently inbound signals must consult a data_manager before propegating
  - this allows things to actually change before everything updates
- however data_manager should probably be doing the outbound signals itself rather
  than the messy enforcement of this currently done
  - this would allow some implementation details to be simpler
- but this is what would casue the multiple referencing since there would now be a
  seperate dispatcher for each type
  - do we care?
    - thinking about it more there are data types we haven't considered that may have
      more complicated signalling, so sepatating the implementation into sections would
      allow more signals to be added without the need for adding more linking code.

*/


//---------------------------------------------------------------------------
// Project_Data::Implementation
//---------------------------------------------------------------------------

namespace sak
{
  class Project_Data::Implementation
  {
  public:
    QFileInfo m_filepath;
    QString m_message;
    QString m_data;

    File_Data_Manager m_file_manager;
    Texture_Data_Manager m_texture_manager;

    Command_History m_command_history;

    explicit Implementation(QString const& a_filepath):
      m_filepath{a_filepath},
      m_file_manager{},
      m_texture_manager{},
      m_command_history{}
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
  // If the directory does not exist it will fail.
  if(!imp().m_filepath.dir().exists())
  {
    // Failure exception for directory not existing.
    throw Directory_Missing_Error(imp().m_filepath.absoluteDir().absolutePath());
    //data().m_message = u8"Failure exception for directory not existing.";
  }
  // if the file exists, load it
  if(cimp().m_filepath.exists())
  {
    load();
  }
  // else make a new file using the empty initialsed data.
  else
  {
    save();
  }
}
sak::Project_Data::~Project_Data() = default;

sak::Project_Data::Project_Data(Project_Data &&) = default;
sak::Project_Data& sak::Project_Data::operator=(Project_Data &&) = default;

// Interface
//============================================================
// Save the current data to the file.
void sak::Project_Data::save() const
{
 QFile l_file{(cimp().m_filepath.absoluteFilePath())};
 if (l_file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
 {
   //qDebug() << "File opened";

   //QTextStream out_stream(&file);

   //qDebug() << static_cast<QFile*>(out_stream.device())->fileName();
   QXmlStreamWriter l_stream{&l_file};
   l_stream.setAutoFormatting(true);
   l_stream.writeStartDocument();

   // start the element that contains all the data
   l_stream.writeStartElement("Project");

   cimp().m_file_manager.to_xmlstream(l_stream);
   cimp().m_texture_manager.to_xmlstream(l_stream);

   // end the element that contains all the data
   l_stream.writeEndElement();

   l_stream.writeEndDocument();

   l_file.close();
 }
 else
 {
   throw File_Write_Error(cimp().m_filepath.absoluteFilePath());
 }
}

// Get the data from the file and discard the current data.
void sak::Project_Data::load()
{
  // Initialise new data
  auto l_data{std::make_unique<Implementation>(cimp().m_filepath.absoluteFilePath())};

  // Create a file object
  QFile l_file{cimp().m_filepath.absoluteFilePath()};

  // Attempt to open the file to read it
  if (l_file.exists() && l_file.open(QFile::ReadOnly | QFile::Text))
  {
    // make an xml stream
    QXmlStreamReader l_stream{&l_file};

    // <Project>
    if (l_stream.readNextStartElement()
        && l_stream.name().toString() == "Project")
    {
      l_data->m_file_manager.from_xmlstream(l_stream);
      l_data->m_texture_manager.from_xmlstream(l_stream);

      // </Project>
      qDebug() << "tokenstring = " << l_stream.tokenString() << l_stream.name().toString();
      if (l_stream.readNext() != QXmlStreamReader::Characters)
      {
        // Bad file structure
        qDebug() << "Didn't find Project Characters";
      }
      qDebug() << "tokenstring = " << l_stream.tokenString() << l_stream.name().toString();
      if (l_stream.readNext() != QXmlStreamReader::EndElement)
      {
        // Bad file structure
        qDebug() << "Didn't find Project EndElement";
      }
      qDebug() << "tokenstring = " << l_stream.tokenString() << l_stream.name().toString();

    }
    else
    {
      // Bad file structure
      qDebug() << "Didn't find Project";
    }

    l_file.close();

    // Replace the current data and consign it to oblivion. The data
    // is now that which has been loaded.
    std::swap(m_data, l_data);
  }
  else
  {
    // Failure exception for file loading.
    throw File_Read_Error(imp().m_filepath.absoluteFilePath());
  }
}

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
  imp().m_file_manager.add_signalbox(a_signalbox);
  imp().m_texture_manager.add_signalbox(a_signalbox);
}

// Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::Project_Data::remove_signalbox(Abstract_Project_Signalbox* a_signalbox)
{
  imp().m_file_manager.remove_signalbox(a_signalbox);
  imp().m_texture_manager.remove_signalbox(a_signalbox);
}

// Can we currently call undo?
bool sak::Project_Data::can_undo() const
{
  return cimp().m_command_history.can_undo();
}

// Can we currently call redo?
bool sak::Project_Data::can_redo() const
{
  return cimp().m_command_history.can_redo();
}

// How many times can undo() be called?
std::size_t sak::Project_Data::undo_count() const
{
  return cimp().m_command_history.undo_count();
}

// How many times can redo() be called?
std::size_t sak::Project_Data::redo_count() const
{
  return cimp().m_command_history.redo_count();
}

// Undo the last command issued.
void sak::Project_Data::undo()
{
  imp().m_command_history.undo();
}

// Redo the last undone command in the command history
void sak::Project_Data::redo()
{
  imp().m_command_history.redo();
}

// Clear the undo/redo history.
void sak::Project_Data::clear_history()
{
  imp().m_command_history.clear();
}

template <>
sak::Section_Interface<sak::File_Data> sak::Project_Data::get_interface<sak::File_Data>()
{
  return get_file_interface();
}

template <>
sak::Section_Interface<sak::Texture_Data> sak::Project_Data::get_interface<sak::Texture_Data>()
{
  return get_texture_interface();
}

sak::File_Interface sak::Project_Data::get_file_interface()
{
  return Section_Interface<File_Data>(std::addressof(imp().m_file_manager), std::addressof(imp().m_command_history));
}

sak::Texture_Interface sak::Project_Data::get_texture_interface()
{
  return Section_Interface<Texture_Data>(std::addressof(imp().m_texture_manager), std::addressof(imp().m_command_history));
}

