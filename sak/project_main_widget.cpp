﻿#include "project_main_widget.hpp"


#include <cassert>
#include <iterator>
#include <algorithm>

#include <QDebug>
#include <QHBoxLayout>
#include <QSplitter>

#include <sak/exceptions/exception.hpp>

#include "section_data.hpp"
#include "section_handle.hpp"
#include "section_widget.hpp"
#include "section_interface.hpp"

#include "project_data.hpp"
#include "abstract_project_signalbox.hpp"
#include "project_editor_widget.hpp"
#include "project_outliner_widget.hpp"


//---------------------------------------------------------------------------
// Project_Main_Widget::Implementation
//---------------------------------------------------------------------------

// Pimpl Data
//============================================================
namespace sak
{
  class Project_Main_Widget::Implementation :
      public Abstract_Project_Signalbox
  {
  public:
    Project_Main_Widget* m_owner;
    bool m_unsaved_edits;
    std::unique_ptr<Project_Data> m_project;

    std::unique_ptr<QHBoxLayout> m_layout;

    // Because QSplitter takes ownership it must be before the widgets it holds.
    // This means the unique_ptr destructor is called after it knows its children are dead.
    std::unique_ptr<QSplitter> m_splitter;
    std::unique_ptr<Project_Outliner_Widget> m_outliner;
    std::unique_ptr<Project_Editor_Widget> m_editor;

    Implementation(Project_Main_Widget* a_owner, std::unique_ptr<Project_Data>&& a_data);
    ~Implementation() override;

    // When a File has its data changed(anything but the name), this is called.
    void changed(File_Handle const& a_file) override final;
    // When a File has its data changed in a specific place, this is called.
    void changed_at(File_Handle const& a_file, std::size_t a_section) override final;
    // When a File has been added, this is called.
    void added(File_Handle const& a_file) override final;
    // When a File has been removed, this is called.
    void removed(File_Handle const& a_file) override final;
    // When a File editor is to be opened, this is called.
    void requests_editor(File_Handle const& a_file) override final;
    // When focus is changed to be on a File, call this
    void requests_focus(File_Handle const& a_file) override final;

    // When a texture has its data changed(anything but the name), this is called.
    void changed(Texture_Handle const& a_texture) override final;
    // When a texture has its data changed in a specific place, this is called.
    void changed_at(Texture_Handle const& a_texture, std::size_t a_section) override final;
    // When a texture has been added, this is called.
    void added(Texture_Handle const& a_texture) override final;
    // When a texture has been removed, this is called.
    void removed(Texture_Handle const& a_texture) override final;
    // When a texture editor is to be opened, this is called.
    void requests_editor(Texture_Handle const& a_texture) override final;
    // When focus is changed to be on a texture, call this
    void requests_focus(Texture_Handle const& a_texture) override final;

    void signal_unsaved_edits_change(bool a_state);
    void signal_undo_change();
  };
}


sak::Project_Main_Widget::Implementation::Implementation(Project_Main_Widget* a_owner, std::unique_ptr<Project_Data>&& a_data):
    m_owner{a_owner},
    m_unsaved_edits{false},
    m_project{std::move(a_data)},
    m_layout{std::make_unique<QHBoxLayout>()},
    m_splitter{std::make_unique<QSplitter>(Qt::Horizontal, nullptr)},
    m_outliner{std::make_unique<Project_Outliner_Widget>(*m_project, nullptr)},
    m_editor{std::make_unique<Project_Editor_Widget>(*m_project, nullptr)}
{
  m_project->add_signalbox(this);

  m_splitter->addWidget(m_outliner.get());
  m_splitter->addWidget(m_editor.get());
  m_splitter->setStretchFactor(0,1);
  m_splitter->setStretchFactor(1,3);
  m_splitter->setChildrenCollapsible(false);

  m_layout->addWidget(m_splitter.get());
  m_layout->setSpacing(0);
}

sak::Project_Main_Widget::Implementation::~Implementation() = default;


// When a File has its data changed(anything but the name), this is called.
void sak::Project_Main_Widget::Implementation::changed(File_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::data_changed " << QString::fromStdString(File_Data::type());
  signal_unsaved_edits_change(true);
  signal_undo_change();
}
// When a File has its data changed in a specific place, this is called.
void sak::Project_Main_Widget::Implementation::changed_at(File_Handle const&, std::size_t )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::data_changed_at " << QString::fromStdString(File_Data::type());
  signal_unsaved_edits_change(true);
  signal_undo_change();
}
// When a File has been added, this is called.
void sak::Project_Main_Widget::Implementation::added(File_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::added " << QString::fromStdString(File_Data::type());
  signal_unsaved_edits_change(true);
  signal_undo_change();
}
// When a File has been removed, this is called.
void sak::Project_Main_Widget::Implementation::removed(File_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::removed " << QString::fromStdString(File_Data::type());
  signal_unsaved_edits_change(true);
  signal_undo_change();
}
// When a File editor is to be opened, this is called.
void sak::Project_Main_Widget::Implementation::requests_editor(File_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::requests_editor " << QString::fromStdString(File_Data::type());
}
// When focus is changed to be on a File, call this
void sak::Project_Main_Widget::Implementation::requests_focus(File_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::requests_focus " << QString::fromStdString(File_Data::type());
}


// When a texture has its data changed(anything but the name), this is called.
void sak::Project_Main_Widget::Implementation::changed(Texture_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::data_changed " << QString::fromStdString(Texture_Data::type());
  signal_unsaved_edits_change(true);
  signal_undo_change();
}
// When a texture has its data changed in a specific place, this is called.
void sak::Project_Main_Widget::Implementation::changed_at(Texture_Handle const&, std::size_t )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::data_changed_at " << QString::fromStdString(Texture_Data::type());
  signal_unsaved_edits_change(true);
  signal_undo_change();
}
// When a texture has been added, this is called.
void sak::Project_Main_Widget::Implementation::added(Texture_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::added " << QString::fromStdString(Texture_Data::type());
  signal_unsaved_edits_change(true);
  signal_undo_change();
}
// When a texture has been removed, this is called.
void sak::Project_Main_Widget::Implementation::removed(Texture_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::removed " << QString::fromStdString(Texture_Data::type());
  signal_unsaved_edits_change(true);
  signal_undo_change();
}
// When a texture editor is to be opened, this is called.
void sak::Project_Main_Widget::Implementation::requests_editor(Texture_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::requests_editor " << QString::fromStdString(Texture_Data::type());
}
// When focus is changed to be on a texture, call this
void sak::Project_Main_Widget::Implementation::requests_focus(Texture_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::requests_focus " << QString::fromStdString(Texture_Data::type());
}




void sak::Project_Main_Widget::Implementation::signal_unsaved_edits_change(bool a_state)
{
  qDebug() << "sak::Project_Main_Widget::Implementation::signal_unsaved_edits_change";
  if (m_unsaved_edits != a_state)
  {
    m_unsaved_edits = a_state;
    m_owner->emit signal_unsaved_edits_change(m_unsaved_edits);
  }
}

void sak::Project_Main_Widget::Implementation::signal_undo_change()
{
  qDebug() << "sak::Project_Main_Widget::Implementation::signal_undo_change";
  qDebug() << "Undo = " << m_project->undo_count() << " Redo = " << m_project->redo_count();
  m_owner->emit signal_undo_change();
}


//---------------------------------------------------------------------------
// Project_Main_Widget
//---------------------------------------------------------------------------

// Special 6
//============================================================
// Create a Project with the given filepath.
sak::Project_Main_Widget::Project_Main_Widget(std::unique_ptr<Project_Data>&& a_project, QWidget* a_parent):
  QWidget(a_parent),
  m_data{std::make_unique<Implementation>(this, std::move(a_project))}
{
  this->setLayout(imp().m_layout.get());
}

sak::Project_Main_Widget::~Project_Main_Widget() = default;

// Menu Actions
//============================================================
// Actions that can be done on a project that needs direct support in the widget.
// Some of these tasks will have come from the Project_Window.

// Menu Bar -> File
//============================================================
// Save the Project data.
void sak::Project_Main_Widget::save_project()
{
  try
  {
    cimp().m_project->save();
    imp().signal_unsaved_edits_change(false);
  }
  catch(File_Write_Error& l_exception)
  {
     l_exception.dialog(this);
  }
}

// Menu Bar -> Edit
//============================================================
// Undo the last command issued.
void sak::Project_Main_Widget::undo()
{
  imp().m_project->undo();
  //imp().signal_undo_change(); // Gets called if data changes and those changes make it back here.
}

// Redo the last undone command in the command history
void sak::Project_Main_Widget::redo()
{
  imp().m_project->redo();
  //imp().signal_undo_change(); // Gets called if data changes and those changes make it back here.
}

// View the entire command history of the project.
void sak::Project_Main_Widget::view_history()
{

}

// Cleat the undo/redo history of of the Project.
void sak::Project_Main_Widget::clear_history()
{
  imp().m_project->clear_history();
  imp().signal_undo_change();
}

// Menu Bar -> Component
//============================================================
// Create a new File in the active Project;
void sak::Project_Main_Widget::create_file()
{
  imp().m_project->get_file_interface().add_default();
}

// Create a new Texture in the active Project;
void sak::Project_Main_Widget::create_texture()
{
  imp().m_project->get_texture_interface().add_default();
}

// Create a new Material in the active Project;
void sak::Project_Main_Widget::create_material()
{

}

// Create a new Model in the active Project;
void sak::Project_Main_Widget::create_model()
{

}

// Create a new Package in the active Project;
void sak::Project_Main_Widget::create_package()
{

}

// Create a new Release in the active Project;
void sak::Project_Main_Widget::create_release()
{

}

// Menu Bar -> Build
//============================================================
// Build all the components of the Project.
void sak::Project_Main_Widget::build_project()
{

}

// Reuild all the components of the Project.
void sak::Project_Main_Widget::rebuild_project()
{

}

// Delete all the temporary and resulting files from building the Project.
void sak::Project_Main_Widget::clean_project()
{

}

// Build the currently selected Component of the Project.
void sak::Project_Main_Widget::build_component()
{

}

// Reuild the currently selected Component of the Project.
void sak::Project_Main_Widget::rebuild_component()
{

}

// Delete all the temporary and resulting files from building the currently
// selected Component of the Project.
void sak::Project_Main_Widget::clean_component()
{

}

// Menu Bar -> Install
//============================================================
// Review the current install status of all components.
void sak::Project_Main_Widget::install_status()
{

}

// Install the current component. Opens a dialog detailing required options
// and the status of the install.
void sak::Project_Main_Widget::install_component()
{

}

// Delete all the temporary and resulting files from building the Project.
void sak::Project_Main_Widget::uninstall_component()
{

}

// Uninstalls all the components that are currently installed.
void sak::Project_Main_Widget::uninstall_all()
{

}

// Interface
//============================================================
// State query helpers for determining whether actions are
// currently active, and what they do.


// Get the name of the project.
QString sak::Project_Main_Widget::name() const
{
  return cimp().m_project->name();
}

// Get the root directory of the project.
QString sak::Project_Main_Widget::location() const
{
  return cimp().m_project->location();
}

// Does the Project have unsaved changes?
bool sak::Project_Main_Widget::has_unsaved_edits() const
{
  return cimp().m_unsaved_edits;
}

// Can we currently call undo?
bool sak::Project_Main_Widget::can_undo() const
{
  return cimp().m_project->can_undo();
}

// Can we currently call redo?
bool sak::Project_Main_Widget::can_redo() const
{
  return cimp().m_project->can_redo();
}

// Get the name of the currently selected component. Empty if none is selected.
QString sak::Project_Main_Widget::selected_component_name() const
{
  return QString();
}

// Is a component selected? If no project is open, this is always false.
bool sak::Project_Main_Widget::is_component_selected() const
{
  return false;
}

// Is the selected component buildable? If no component is open, this is always false.
bool sak::Project_Main_Widget::is_component_buildable() const
{
  return false;
}

// Is the selected component installable? If no component is open, this is always false.
bool sak::Project_Main_Widget::is_component_installable() const
{
  return false;
}