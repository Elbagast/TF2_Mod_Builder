#include "object.hpp"

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

#include "signalbox.hpp"
#include <sak/exceptions/exception.hpp>
#include <sak/shared/manager.hpp>
#include <sak/shared/data_manager.hpp>
#include <sak/shared/signalbox.hpp>
#include <sak/shared/interface.hpp>
#include <generic/command_history.hpp>
#include <sak/shared/command.hpp>
#include <sak/name_utilities.hpp>

#include <sak/shared/xml_traits.hpp>

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
// project::object
//---------------------------------------------------------------------------
// Pimpl Data
//============================================================
namespace sak
{
  namespace project
  {
    class object::impl
    {
    public:
      QFileInfo m_filepath;
      QString m_message;
      QString m_data;

      file::data_manager m_file_manager;
      texture::data_manager m_texture_manager;

      generic::Command_History m_command_history;

      explicit impl(QString const& a_filepath):
        m_filepath{a_filepath},
        m_file_manager{},
        m_texture_manager{},
        m_command_history{}
      {
      }
      ~impl() = default;

    }; // project::object::impl
  } // namespace project
} // namespace sak

// Special 6
//============================================================
// Construct the project using the supplied filename. If the directory
// does not exist or is inaccessible it will fail. If the file does
// not exist it will attempt to create it and save the initial data
// to it. If the file exists it will attempt to load the data from it.
sak::project::object::object(QString const& a_filepath):
    m_data{std::make_unique<impl>(a_filepath)}
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
sak::project::object::~object() = default;

sak::project::object::object(object &&) = default;
sak::project::object& sak::project::object::operator=(object &&) = default;

// Interface
//============================================================
// Save the current data to the file.
void sak::project::object::save() const
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
void sak::project::object::load()
{
  // Initialise new data
  auto l_data{std::make_unique<impl>(cimp().m_filepath.absoluteFilePath())};

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

QString sak::project::object::name() const
{
  return cimp().m_filepath.baseName();
}

QString sak::project::object::location() const
{
  return cimp().m_filepath.absolutePath();
}

QString sak::project::object::filepath() const
{
  return cimp().m_filepath.absoluteFilePath();
}


// Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::project::object::add_signalbox(abstract::signalbox* a_signalbox)
{
  imp().m_file_manager.add_signalbox(a_signalbox);
  imp().m_texture_manager.add_signalbox(a_signalbox);
}

// Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::project::object::remove_signalbox(abstract::signalbox* a_signalbox)
{
  imp().m_file_manager.remove_signalbox(a_signalbox);
  imp().m_texture_manager.remove_signalbox(a_signalbox);
}

// Can we currently call undo?
bool sak::project::object::can_undo() const
{
  return cimp().m_command_history.can_undo();
}

// Can we currently call redo?
bool sak::project::object::can_redo() const
{
  return cimp().m_command_history.can_redo();
}

// How many times can undo() be called?
std::size_t sak::project::object::undo_count() const
{
  return cimp().m_command_history.undo_count();
}

// How many times can redo() be called?
std::size_t sak::project::object::redo_count() const
{
  return cimp().m_command_history.redo_count();
}

// Undo the last command issued.
void sak::project::object::undo()
{
  imp().m_command_history.undo();
}

// Redo the last undone command in the command history
void sak::project::object::redo()
{
  imp().m_command_history.redo();
}

// Clear the undo/redo history.
void sak::project::object::clear_history()
{
  imp().m_command_history.clear();
}

template <>
sak::shared::interface<sak::file::object> sak::project::object::get_interface<sak::file::object>()
{
  return get_file_interface();
}

template <>
sak::shared::interface<sak::texture::object> sak::project::object::get_interface<sak::texture::object>()
{
  return get_texture_interface();
}

sak::file::interface sak::project::object::get_file_interface()
{
  return shared::interface<file::object>(imp().m_file_manager, imp().m_command_history);
}

sak::texture::interface sak::project::object::get_texture_interface()
{
  return shared::interface<texture::object>(imp().m_texture_manager, imp().m_command_history);
}

