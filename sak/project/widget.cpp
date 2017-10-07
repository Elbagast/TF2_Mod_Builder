#include "widget.hpp"


#include <cassert>
#include <iterator>
#include <algorithm>

#include <QDebug>
#include <QHBoxLayout>
#include <QSplitter>

#include <sak/exceptions/exception.hpp>

#include <sak/shared/object.hpp>
#include <sak/shared/manager.hpp>
#include <sak/shared/widget.hpp>
#include <sak/shared/interface.hpp>
#include <sak/project/editor.hpp>

#include <sak/project/editor.hpp>
#include <sak/project/outliner/widget.hpp>

#include "object.hpp"
#include "signalbox.hpp"

//---------------------------------------------------------------------------
// project::widget
//---------------------------------------------------------------------------
// Internal constants and impl
//============================================================
namespace
{

}

// Pimpl Data
//============================================================
namespace sak
{
  namespace project
  {
    class widget::impl :
            public abstract::signalbox
    {
    public:
        widget* m_owner;
        bool m_unsaved_edits;
        std::unique_ptr<object> m_project;

        std::unique_ptr<QHBoxLayout> m_layout;

        // Because QSplitter takes ownership it must be before the widgets it holds.
        // This means the unique_ptr destructor is called after it knows its children are dead.
        std::unique_ptr<QSplitter> m_splitter;
        std::unique_ptr<outliner::widget> m_outliner;
        std::unique_ptr<editor> m_editor;

        ~impl() override;

        impl(widget* a_owner, std::unique_ptr<object>&& a_data);

        // When a File has its data changed(anything but the name), this is called.
        void changed(file::handle const& a_file) override final;
        // When a File has its data changed in a specific place, this is called.
        void changed_at(file::handle const& a_file, std::size_t a_section) override final;
        // When a File has been added, this is called.
        void added(file::handle const& a_file) override final;
        // When a File has been removed, this is called.
        void removed(file::handle const& a_file) override final;
        // When a File editor is to be opened, this is called.
        void requests_editor(file::handle const& a_file) override final;
        // When focus is changed to be on a File, call this
        void requests_focus(file::handle const& a_file) override final;

        // When a texture has its data changed(anything but the name), this is called.
        void changed(texture::handle const& a_texture) override final;
        // When a texture has its data changed in a specific place, this is called.
        void changed_at(texture::handle const& a_texture, std::size_t a_section) override final;
        // When a texture has been added, this is called.
        void added(texture::handle const& a_texture) override final;
        // When a texture has been removed, this is called.
        void removed(texture::handle const& a_texture) override final;
        // When a texture editor is to be opened, this is called.
        void requests_editor(texture::handle const& a_texture) override final;
        // When focus is changed to be on a texture, call this
        void requests_focus(texture::handle const& a_texture) override final;

        void signal_unsaved_edits_change(bool a_state);
        void signal_undo_change();
    };
  }
}

sak::project::widget::impl::~impl() = default;

sak::project::widget::impl::impl(project::widget* a_owner, std::unique_ptr<object>&& a_data):
    m_owner{a_owner},
    m_unsaved_edits{false},
    m_project{std::move(a_data)},
    m_layout{std::make_unique<QHBoxLayout>()},
    m_splitter{std::make_unique<QSplitter>(Qt::Horizontal, nullptr)},
    m_outliner{std::make_unique<outliner::widget>(*m_project, nullptr)},
    m_editor{std::make_unique<editor>(*m_project, nullptr)}
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

// When a File has its data changed(anything but the name), this is called.
void sak::project::widget::impl::changed(file::handle const& )
{
    qDebug() << "project::widget::impl::data_changed " << QString::fromStdString(file::object::type());
    signal_unsaved_edits_change(true);
    signal_undo_change();
}
// When a File has its data changed in a specific place, this is called.
void sak::project::widget::impl::changed_at(file::handle const&, std::size_t )
{
    qDebug() << "project::widget::impl::data_changed_at " << QString::fromStdString(file::object::type());
    signal_unsaved_edits_change(true);
    signal_undo_change();
}
// When a File has been added, this is called.
void sak::project::widget::impl::added(file::handle const& )
{
    qDebug() << "project::widget::impl::added " << QString::fromStdString(file::object::type());
    signal_unsaved_edits_change(true);
    signal_undo_change();
}
// When a File has been removed, this is called.
void sak::project::widget::impl::removed(file::handle const& )
{
    qDebug() << "project::widget::impl::removed " << QString::fromStdString(file::object::type());
    signal_unsaved_edits_change(true);
    signal_undo_change();
}
// When a File editor is to be opened, this is called.
void sak::project::widget::impl::requests_editor(file::handle const& )
{
    qDebug() << "project::widget::impl::requests_editor " << QString::fromStdString(file::object::type());
}
// When focus is changed to be on a File, call this
void sak::project::widget::impl::requests_focus(file::handle const& )
{
    qDebug() << "project::widget::impl::requests_focus " << QString::fromStdString(file::object::type());
}


// When a texture has its data changed(anything but the name), this is called.
void sak::project::widget::impl::changed(texture::handle const& )
{
    qDebug() << "project::widget::impl::data_changed " << QString::fromStdString(texture::object::type());
    signal_unsaved_edits_change(true);
    signal_undo_change();
}
// When a texture has its data changed in a specific place, this is called.
void sak::project::widget::impl::changed_at(texture::handle const&, std::size_t )
{
    qDebug() << "project::widget::impl::data_changed_at " << QString::fromStdString(texture::object::type());
    signal_unsaved_edits_change(true);
    signal_undo_change();
}
// When a texture has been added, this is called.
void sak::project::widget::impl::added(texture::handle const& )
{
    qDebug() << "project::widget::impl::added " << QString::fromStdString(texture::object::type());
    signal_unsaved_edits_change(true);
    signal_undo_change();
}
// When a texture has been removed, this is called.
void sak::project::widget::impl::removed(texture::handle const& )
{
    qDebug() << "project::widget::impl::removed " << QString::fromStdString(texture::object::type());
    signal_unsaved_edits_change(true);
    signal_undo_change();
}
// When a texture editor is to be opened, this is called.
void sak::project::widget::impl::requests_editor(texture::handle const& )
{
    qDebug() << "project::widget::impl::requests_editor " << QString::fromStdString(texture::object::type());
}
// When focus is changed to be on a texture, call this
void sak::project::widget::impl::requests_focus(texture::handle const& )
{
    qDebug() << "project::widget::impl::requests_focus " << QString::fromStdString(texture::object::type());
}




void sak::project::widget::impl::signal_unsaved_edits_change(bool a_state)
{
    qDebug() << "project::widget::impl::signal_unsaved_edits_change";
    if (m_unsaved_edits != a_state)
    {
        m_unsaved_edits = a_state;
        m_owner->emit signal_unsaved_edits_change(m_unsaved_edits);
    }
}

void sak::project::widget::impl::signal_undo_change()
{
    qDebug() << "project::widget::impl::signal_undo_change";
    qDebug() << "Undo = " << m_project->undo_count() << " Redo = " << m_project->redo_count();
    m_owner->emit signal_undo_change();
}

// Special 6
//============================================================
// Create a Project with the given filepath.
sak::project::widget::widget(std::unique_ptr<object>&& a_project, QWidget* a_parent):
    QWidget(a_parent),
    m_data{std::make_unique<impl>(this, std::move(a_project))}
{
    this->setLayout(imp().m_layout.get());
}
sak::project::widget::~widget() = default;

// Menu Actions
//============================================================
// Actions that can be done on a project that needs direct support in the widget.
// Some of these tasks will have come from the Project_Window.

// Menu Bar -> File
//============================================================
// Save the Project data.
void sak::project::widget::save_project()
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
void sak::project::widget::undo()
{
  imp().m_project->undo();
  //imp().signal_undo_change(); // Gets called if data changes and those changes make it back here.
}

// Redo the last undone command in the command history
void sak::project::widget::redo()
{
  imp().m_project->redo();
  //imp().signal_undo_change(); // Gets called if data changes and those changes make it back here.
}

// View the entire command history of the project.
void sak::project::widget::view_history()
{

}

// Cleat the undo/redo history of of the Project.
void sak::project::widget::clear_history()
{
  imp().m_project->clear_history();
  imp().signal_undo_change();
}

// Menu Bar -> Component
//============================================================
// Create a new File in the active Project;
void sak::project::widget::create_file()
{
  imp().m_project->get_file_interface().add_default();
}

// Create a new Texture in the active Project;
void sak::project::widget::create_texture()
{
  imp().m_project->get_texture_interface().add_default();
}

// Create a new Material in the active Project;
void sak::project::widget::create_material()
{

}

// Create a new Model in the active Project;
void sak::project::widget::create_model()
{

}

// Create a new Package in the active Project;
void sak::project::widget::create_package()
{

}

// Create a new Release in the active Project;
void sak::project::widget::create_release()
{

}

// Menu Bar -> Build
//============================================================
// Build all the components of the Project.
void sak::project::widget::build_project()
{

}

// Reuild all the components of the Project.
void sak::project::widget::rebuild_project()
{

}

// Delete all the temporary and resulting files from building the Project.
void sak::project::widget::clean_project()
{

}

// Build the currently selected Component of the Project.
void sak::project::widget::build_component()
{

}

// Reuild the currently selected Component of the Project.
void sak::project::widget::rebuild_component()
{

}

// Delete all the temporary and resulting files from building the currently
// selected Component of the Project.
void sak::project::widget::clean_component()
{

}

// Menu Bar -> Install
//============================================================
// Review the current install status of all components.
void sak::project::widget::install_status()
{

}

// Install the current component. Opens a dialog detailing required options
// and the status of the install.
void sak::project::widget::install_component()
{

}

// Delete all the temporary and resulting files from building the Project.
void sak::project::widget::uninstall_component()
{

}

// Uninstalls all the components that are currently installed.
void sak::project::widget::uninstall_all()
{

}

// Interface
//============================================================
// State query helpers for determining whether actions are
// currently active, and what they do.


// Get the name of the project.
QString sak::project::widget::name() const
{
    return cimp().m_project->name();
}

// Get the root directory of the project.
QString sak::project::widget::location() const
{
    return cimp().m_project->location();
}

// Does the Project have unsaved changes?
bool sak::project::widget::has_unsaved_edits() const
{
    return cimp().m_unsaved_edits;
}

// Can we currently call undo?
bool sak::project::widget::can_undo() const
{
    return cimp().m_project->can_undo();
}

// Can we currently call redo?
bool sak::project::widget::can_redo() const
{
    return cimp().m_project->can_redo();
}

// Get the name of the currently selected component. Empty if none is selected.
QString sak::project::widget::selected_component_name() const
{
    return QString();
}

// Is a component selected? If no project is open, this is always false.
bool sak::project::widget::is_component_selected() const
{
    return false;
}

// Is the selected component buildable? If no component is open, this is always false.
bool sak::project::widget::is_component_buildable() const
{
    return false;
}

// Is the selected component installable? If no component is open, this is always false.
bool sak::project::widget::is_component_installable() const
{
    return false;
}

