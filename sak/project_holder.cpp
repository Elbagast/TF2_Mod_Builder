#include "project_holder.hpp"

#include "project_data.hpp"
#include "command_history.hpp"
#include "project_interface.hpp"
#include "project_main_widget.hpp"
#include "xml_traits.hpp"
#include "exception.hpp"

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


//---------------------------------------------------------------------------
// Project_Holder
//---------------------------------------------------------------------------
// Special 6
//============================================================
// Project_Holder cannot exist without a valid project filepath.
sak::Project_Holder::Project_Holder(QString const& a_filepath):
  m_project_data{std::make_unique<Project_Data>(a_filepath)},
  m_command_history{std::make_unique<Command_History>()},
  m_project_interface{std::make_unique<Project_Interface>(m_project_data.get(), m_command_history.get())},
  m_project_widget{}
  //m_project_widget{std::make_unique<Project_Main_Widget>(m_project_interface.get())}//,
  //m_unsaved_edits{false}
{
  qDebug() << "sak::Project_Holder::Project_Holder";
  QFileInfo l_filepath{a_filepath};

  // If the directory does not exist it will fail.
  if(!l_filepath.dir().exists())
  {
    // Failure exception for directory not existing.
    throw Directory_Missing_Error{};
  }
  // if the file exists, load it
  if(l_filepath.exists())
  {
    load();
  }
  // else make a new file using the empty initialsed data.
  else
  {
    save();
  }
  // Delay the construction and linking of the widget until the data is loaded.
  // For some reason not delaying this means the widget never updates properly...
  // It's like the signalboxes don't get called
  m_project_widget = std::make_unique<Project_Main_Widget>(m_project_interface.get());
}

sak::Project_Holder::~Project_Holder() = default;

sak::Project_Holder::Project_Holder(Project_Holder &&) = default;
sak::Project_Holder& sak::Project_Holder::operator=(Project_Holder &&) = default;

// Interface
//============================================================
// Save the current data to the file.
void sak::Project_Holder::save() const
{
  qDebug() << "sak::Project_Holder::save";
  // Needs to spit out a detailed error if it fails.
  // What is it and where does it go?

  QFile l_file{(this->filepath())};

  if (l_file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
  {
    // Make an xml stream
    QXmlStreamWriter l_stream{&l_file};

    // Read to it
    Xml_Traits<Project_Data>::to_stream(l_stream, *m_project_data);

    l_file.close();
  }
  else
  {
    throw File_Write_Error{};
  }
}

// Get the data from the file and discard the current data.
void sak::Project_Holder::load()
{
  qDebug() << "sak::Project_Holder::load";
  // Needs to spit out a detailed error if it fails.
  // What is it and where does it go?

  // Create a file object
  QFile l_file{this->filepath()};

  if (!l_file.exists())
  {
    throw File_Missing_Error{};
  }

  // Attempt to open the file to read it
  if (l_file.open(QFile::ReadOnly | QFile::Text))
  {
    // make an xml stream
    QXmlStreamReader l_stream{&l_file};

    // Read directly into this
    Xml_Traits<Project_Data>::from_stream(l_stream, *m_project_data);

    l_file.close();
  }
  else
  {
    // Failure exception for file loading.
    throw File_Read_Error{};
  }
}

QString sak::Project_Holder::name() const
{
  return m_project_data->name();
}

QString sak::Project_Holder::location() const
{
  return m_project_data->location();
}

QString sak::Project_Holder::filepath() const
{
  return m_project_data->filepath();
}

sak::Project_Interface* sak::Project_Holder::interface()
{
  return m_project_interface.get();
}

sak::Project_Main_Widget* sak::Project_Holder::widget()
{
  return m_project_widget.get();
}

