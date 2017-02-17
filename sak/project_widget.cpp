#include "project_widget.h"

#include <QHBoxLayout>
#include <QDebug>
#include <cassert>
#include <iterator>
#include <algorithm>

#include "file_manager.h"
#include "file_widget.h"
#include "project.h"
#include "project_outliner.h"
#include "project_editor.h"


//---------------------------------------------------------------------------
// Project_Widget
//---------------------------------------------------------------------------
// Internal constants and implementation
//============================================================
namespace
{

}

// Pimpl Data
//============================================================
namespace sak
{
    class Project_Widget::Implementation
    {
    public:
        std::unique_ptr<Project> m_project;
        std::unique_ptr<Project_Outliner> m_outliner;
        std::unique_ptr<Project_Editor> m_editor;

        std::unique_ptr<QHBoxLayout> m_layout;

        explicit Implementation(std::unique_ptr<Project>&& a_data):
            m_project{std::move(a_data)},
            m_outliner{std::make_unique<Project_Outliner>(*m_project, nullptr)},
            m_editor{std::make_unique<Project_Editor>(*m_project, nullptr)},
            m_layout{std::make_unique<QHBoxLayout>()}
        {
            m_layout->addWidget(m_outliner.get());
            m_layout->setStretchFactor(m_outliner.get(),1);
            m_layout->addWidget(m_editor.get());
            m_layout->setStretchFactor(m_editor.get(),3);
        }

        ~Implementation() = default;
    };
}

// Special 6
//============================================================
// Create a Project with the given filepath.
sak::Project_Widget::Project_Widget(std::unique_ptr<Project>&& a_project, QWidget* a_parent):
    QWidget(a_parent),
    m_data{std::make_unique<Implementation>(std::move(a_project))}
{
    this->setLayout(imp().m_layout.get());
}
sak::Project_Widget::~Project_Widget() = default;

// Menu Actions
//============================================================
// Actions that can be done on a project that needs direct support in the widget.
// Some of these tasks will have come from the Project_Window.

// Menu Bar -> File
//============================================================
// Save the Project data.
void sak::Project_Widget::save_project()
{
    cimp().m_project->save();
}

// Menu Bar -> Edit
//============================================================
// Undo the last command issued.
void sak::Project_Widget::undo()
{

}

// Redo the last undone command in the command history
void sak::Project_Widget::redo()
{

}

// View the entire command history of the project.
void sak::Project_Widget::view_history()
{

}

// Cleat the undo/redo history of of the Project.
void sak::Project_Widget::clear_history()
{

}

// Menu Bar -> Component
//============================================================
// Create a new File in the active Project;
void sak::Project_Widget::create_file()
{
    imp().m_project->add_new_file();
}

// Create a new Texture in the active Project;
void sak::Project_Widget::create_texture()
{

}

// Create a new Material in the active Project;
void sak::Project_Widget::create_material()
{

}

// Create a new Model in the active Project;
void sak::Project_Widget::create_model()
{

}

// Create a new Package in the active Project;
void sak::Project_Widget::create_package()
{

}

// Create a new Release in the active Project;
void sak::Project_Widget::create_release()
{

}

// Menu Bar -> Build
//============================================================
// Build all the components of the Project.
void sak::Project_Widget::build_project()
{

}

// Reuild all the components of the Project.
void sak::Project_Widget::rebuild_project()
{

}

// Delete all the temporary and resulting files from building the Project.
void sak::Project_Widget::clean_project()
{

}

// Build the currently selected Component of the Project.
void sak::Project_Widget::build_component()
{

}

// Reuild the currently selected Component of the Project.
void sak::Project_Widget::rebuild_component()
{

}

// Delete all the temporary and resulting files from building the currently
// selected Component of the Project.
void sak::Project_Widget::clean_component()
{

}

// Menu Bar -> Install
//============================================================
// Review the current install status of all components.
void sak::Project_Widget::install_status()
{

}

// Install the current component. Opens a dialog detailing required options
// and the status of the install.
void sak::Project_Widget::install_component()
{

}

// Delete all the temporary and resulting files from building the Project.
void sak::Project_Widget::uninstall_component()
{

}

// Uninstalls all the components that are currently installed.
void sak::Project_Widget::uninstall_all()
{

}

// Interface
//============================================================
// State query helpers for determining whether actions are
// currently active, and what they do.


// Get the name of the project.
QString sak::Project_Widget::name() const
{
    return cimp().m_project->name();
}

// Get the root directory of the project.
QString sak::Project_Widget::location() const
{
    return cimp().m_project->location();
}

// Can we currently call undo?
bool sak::Project_Widget::can_undo() const
{
    return false;
}

// Can we currently call redo?
bool sak::Project_Widget::can_redo() const
{
    return false;
}

// Get the name of the currently selected component. Empty if none is selected.
QString sak::Project_Widget::selected_component_name() const
{
    return QString();
}

// Is a component selected? If no project is open, this is always false.
bool sak::Project_Widget::is_component_selected() const
{
    return false;
}

// Is the selected component buildable? If no component is open, this is always false.
bool sak::Project_Widget::is_component_buildable() const
{
    return false;
}

// Is the selected component installable? If no component is open, this is always false.
bool sak::Project_Widget::is_component_installable() const
{
    return false;
}

