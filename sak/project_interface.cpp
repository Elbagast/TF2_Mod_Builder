#include "project_interface.hpp"

#include "section_interface.hpp"
#include "command_history.hpp"
#include "project_data.hpp"

#include "abstract_project_signalbox.hpp"

#include <QString>

//---------------------------------------------------------------------------
// Project_Interface
//---------------------------------------------------------------------------

// Special 6
//============================================================
sak::Project_Interface::Project_Interface(Project_Data* a_data, Command_History* a_command_history):
    m_project_data{a_data},
    m_command_history{a_command_history}
{
}
sak::Project_Interface::~Project_Interface() = default;

sak::Project_Interface::Project_Interface(Project_Interface const&) = default;
sak::Project_Interface& sak::Project_Interface::operator=(Project_Interface const&) = default;

sak::Project_Interface::Project_Interface(Project_Interface &&) = default;
sak::Project_Interface& sak::Project_Interface::operator=(Project_Interface &&) = default;

// Interface
//============================================================
/*
void sak::Project_Interface::save() const
{
  return m_project_data->save();
}

void sak::Project_Interface::load()
{
  return m_project_data->load();
}*/

QString sak::Project_Interface::name() const
{
  return m_project_data->name();
}

QString sak::Project_Interface::location() const
{
  return m_project_data->location();
}

QString sak::Project_Interface::filepath() const
{
  return m_project_data->filepath();
}


// Add an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::Project_Interface::add_signalbox(Abstract_Project_Signalbox* a_signalbox)
{
  m_project_data->add_signalbox(a_signalbox);
}

// Remove an object that will rely on the Project's signals. If nulltpr, nothing happens.
void sak::Project_Interface::remove_signalbox(Abstract_Project_Signalbox* a_signalbox)
{
  m_project_data->remove_signalbox(a_signalbox);
}

// Clear all the signalboxes so that nothing relies on changes to this.
void sak::Project_Interface::clear_signalboxes()
{
  m_project_data->clear_signalboxes();
}

// Can we currently call undo?
bool sak::Project_Interface::can_undo() const
{
  return m_command_history->can_undo();
}

// Can we currently call redo?
bool sak::Project_Interface::can_redo() const
{
  return m_command_history->can_redo();
}

// How many times can undo() be called?
std::size_t sak::Project_Interface::undo_count() const
{
  return m_command_history->undo_count();
}

// How many times can redo() be called?
std::size_t sak::Project_Interface::redo_count() const
{
  return m_command_history->redo_count();
}

// Undo the last command issued.
void sak::Project_Interface::undo()
{
  m_command_history->undo();
}

// Redo the last undone command in the command history
void sak::Project_Interface::redo()
{
  m_command_history->redo();
}

// Clear the undo/redo history.
void sak::Project_Interface::clear_history()
{
  m_command_history->clear();
}

template <>
sak::Section_Interface<sak::File_Data> sak::Project_Interface::get_interface<sak::File_Data>()
{
  return this->get_file_interface();
}

template <>
sak::Section_Interface<sak::Texture_Data> sak::Project_Interface::get_interface<sak::Texture_Data>()
{
  return this->get_texture_interface();
}

sak::File_Interface sak::Project_Interface::get_file_interface()
{
  return Section_Interface<File_Data>(m_project_data->get_file_manager(), m_command_history);
}

sak::Texture_Interface sak::Project_Interface::get_texture_interface()
{
  return Section_Interface<Texture_Data>(m_project_data->get_texture_manager(), m_command_history);
}
