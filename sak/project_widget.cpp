#include "project_widget.h"

#include <QHBoxLayout>
#include <QTabWidget>
#include <QTreeView>
#include <QLabel>

#include "project.h"

//---------------------------------------------------------------------------
// Project_Widget
//---------------------------------------------------------------------------
// Internal constants and implementation
//============================================================
namespace
{


    class Project_Display :
            public QWidget
    {
    public:
        explicit Project_Display(sak::Project const& a_data):
            QWidget(),
            m_layout{std::make_unique<QVBoxLayout>()},
            m_name{std::make_unique<QLabel>(a_data.name())},
            m_location{std::make_unique<QLabel>(a_data.location())},
            m_filepath{std::make_unique<QLabel>(a_data.filepath())},
            m_message{std::make_unique<QLabel>(a_data.message())},
            m_content{std::make_unique<QLabel>(a_data.content())}
        {
            m_layout->addWidget(m_name.get());
            m_layout->addWidget(m_location.get());
            m_layout->addWidget(m_filepath.get());
            m_layout->addWidget(m_message.get());
            m_layout->addWidget(m_content.get());
            this->setLayout(m_layout.get());
        }



    private:
        std::unique_ptr<QVBoxLayout> m_layout;
        std::unique_ptr<QLabel> m_name;
        std::unique_ptr<QLabel> m_location;
        std::unique_ptr<QLabel> m_filepath;
        std::unique_ptr<QLabel> m_message;
        std::unique_ptr<QLabel> m_content;
    };

}

// Pimpl Data
//============================================================
class sak::Project_Widget::Data
{
public:
    sak::Project m_data;

    std::unique_ptr<QHBoxLayout> m_layout;
    std::unique_ptr<QTreeView> m_outliner;
    std::unique_ptr<QTabWidget> m_tabs;
    std::unique_ptr<Project_Display> m_display;


    explicit Data(sak::Project&& a_data):
        m_data{std::move(a_data)},
        m_layout{std::make_unique<QHBoxLayout>()},
        m_outliner{std::make_unique<QTreeView>()},
        m_tabs{std::make_unique<QTabWidget>()},
        m_display{std::make_unique<Project_Display>(m_data)}
    {}
};

// Special 6
//============================================================
/*
sak::Project_Widget::Project_Widget(QString const& a_name, QString const& a_location, QWidget* a_parent):
    QWidget(a_parent),
    m_data{std::make_unique<Data>(Project_Data{(a_name, a_location)})}
{
    data().m_layout->addWidget(data().m_outliner.get());
    data().m_layout->setStretchFactor(data().m_outliner.get(),1);
    data().m_layout->addWidget(data().m_tabs.get());
    data().m_layout->setStretchFactor(data().m_tabs.get(),2);
    data().m_layout->addWidget(data().m_display.get());

    this->setLayout(data().m_layout.get());
}
*/

// Create a Project with the given filepath.
sak::Project_Widget::Project_Widget(Project && a_project, QWidget* a_parent):
   // Project_Widget(QFileInfo(a_filepath).fileName(), QFileInfo(a_filepath).absoluteDir().absolutePath(), a_parent)
    QWidget(a_parent),
    m_data{std::make_unique<Data>(std::move(a_project))}
{
    data().m_layout->addWidget(data().m_outliner.get());
    data().m_layout->setStretchFactor(data().m_outliner.get(),1);
    data().m_layout->addWidget(data().m_tabs.get());
    data().m_layout->setStretchFactor(data().m_tabs.get(),2);
    data().m_layout->addWidget(data().m_display.get());

    this->setLayout(data().m_layout.get());
}


// Menu Actions
//============================================================
// Actions that can be done on a project that needs direct support in the widget.
// Some of these tasks will have come from the Project_Window.

// Menu Bar -> File
//============================================================
// Save the Project data.
void sak::Project_Widget::save_project()
{

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
    return cdata().m_data.name();
}

// Get the root directory of the project.
QString sak::Project_Widget::location() const
{
    return cdata().m_data.location();
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
