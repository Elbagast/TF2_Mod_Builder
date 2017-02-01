#include "project_window.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedWidget>

namespace
{
    QString const c_application_title{"TF2 Mod Builder"};
}


//---------------------------------------------------------------------------
// Project_Window::Background_Widget
//---------------------------------------------------------------------------
// Seperating out since we might want to change this to display information.
class sak::Project_Window::Background_Widget :
        public QLabel
{
public:
    Background_Widget():
        QLabel("No Projects are open.\nFile->New Project to create a new Project.\n"
               "File->Load Project to open an existing Project.", nullptr)
    {
        this->setAlignment(Qt::AlignCenter);
    }
    ~Background_Widget() override = default;
};


//---------------------------------------------------------------------------
// Project_Window
//---------------------------------------------------------------------------
// Special 6
//============================================================
sak::Project_Window::Project_Window(QWidget* a_parent):
    QMainWindow(a_parent),
    m_central_stack{std::make_unique<QStackedWidget>()},
    m_background_widget{std::make_unique<Background_Widget>()},

    m_file{std::make_unique<QMenu>("File")},
    m_file_new_project{std::make_unique<QAction>("New Project")},
    m_file_open_project{std::make_unique<QAction>("Open Project")},
    m_file_save_project{std::make_unique<QAction>("Save Project")},
    m_file_close_project{std::make_unique<QAction>("Close Project")},
    m_file_exit{std::make_unique<QAction>("Exit")},

    m_edit{std::make_unique<QMenu>("Edit")},
    m_edit_undo{std::make_unique<QAction>("Undo")},
    m_edit_redo{std::make_unique<QAction>("Redo")},
    m_edit_view_history{std::make_unique<QAction>("View History")},
    m_edit_clear_history{std::make_unique<QAction>("Clear History")},

    m_component{std::make_unique<QMenu>("Component")},
    m_component_create{std::make_unique<QMenu>("Create...")},
    m_component_create_file{std::make_unique<QAction>("File")},
    m_component_create_texture{std::make_unique<QAction>("Texture")},
    m_component_create_material{std::make_unique<QAction>("Material")},
    m_component_create_model{std::make_unique<QAction>("Model")},
    m_component_create_package{std::make_unique<QAction>("Package")},
    m_component_create_release{std::make_unique<QAction>("Release")},

    m_build{std::make_unique<QMenu>("Build")},
    m_build_build_project{std::make_unique<QAction>("Build Project")},
    m_build_rebuild_project{std::make_unique<QAction>("Rebuild Project")},
    m_build_clean_project{std::make_unique<QAction>("Clean Project")},
    m_build_build_component{std::make_unique<QAction>("Build Component")},
    m_build_rebuild_component{std::make_unique<QAction>("Rebuild Component")},
    m_build_clean_component{std::make_unique<QAction>("Clean Component")},

    m_install{std::make_unique<QMenu>("Install")},
    m_install_install_status{std::make_unique<QAction>("Install Status")},
    m_install_install_component{std::make_unique<QAction>("Install Component")},
    m_install_uninstall_component{std::make_unique<QAction>("Uninstall Component")},
    m_install_uninstall_all{std::make_unique<QAction>("Uninstall all")},

    m_settings{std::make_unique<QMenu>("Settings")},
    m_settings_settings{std::make_unique<QAction>("Settings")},
    m_settings_tf2_settings{std::make_unique<QAction>("TF2 Settings")},
    m_settings_sfm_settings{std::make_unique<QAction>("SFM Settings")},

    m_help{std::make_unique<QMenu>("Help")},
    m_help_help{std::make_unique<QAction>("Help")},
    m_help_about{std::make_unique<QAction>("about")}
{
    // Add the background widget to the stack.
    m_central_stack->addWidget(m_background_widget.get());

    // Set the central widget to be the stack. We modify the stack to change what the window is displaying.
    this->setCentralWidget(m_central_stack.get());

    // Window Title
    this->setWindowTitle(c_application_title);

    // Menu Bar -> File
    //============================================================
    // Configure the menu items
    QObject::connect(m_file_new_project.get(), &QAction::triggered, this, &Project_Window::new_project);
    QObject::connect(m_file_open_project.get(), &QAction::triggered, this, &Project_Window::open_project);
    QObject::connect(m_file_save_project.get(), &QAction::triggered, this, &Project_Window::save_project);
    QObject::connect(m_file_close_project.get(), &QAction::triggered, this, &Project_Window::close_project);
    QObject::connect(m_file_exit.get(), &QAction::triggered, this, &Project_Window::exit);

    // Build the File menu. It does not take ownership of the QActions.
    m_file->addAction(m_file_new_project.get());
    m_file->addAction(m_file_open_project.get());
    m_file->addSeparator();
    m_file->addAction(m_file_save_project.get());
    m_file->addSeparator();
    m_file->addAction(m_file_close_project.get());
    m_file->addSeparator();
    m_file->addAction(m_file_exit.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(m_file.get());

    // Menu Bar -> Edit
    //============================================================
    // Configure the menu items
    QObject::connect(m_edit_undo.get(), &QAction::triggered, this, &Project_Window::undo);
    QObject::connect(m_edit_redo.get(), &QAction::triggered, this, &Project_Window::redo);
    QObject::connect(m_edit_view_history.get(), &QAction::triggered, this, &Project_Window::view_history);
    QObject::connect(m_edit_clear_history.get(), &QAction::triggered, this, &Project_Window::clear_history);

    // Build the File menu. It does not take ownership of the QActions.
    m_edit->addAction(m_edit_undo.get());
    m_edit->addAction(m_edit_redo.get());
    m_edit->addSeparator();
    m_edit->addAction(m_edit_view_history.get());
    m_edit->addAction(m_edit_clear_history.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(m_edit.get());

    // Menu Bar -> Create
    //============================================================
    // Configure the menu items
    QObject::connect(m_component_create_file.get(), &QAction::triggered, this, &Project_Window::create_file);
    QObject::connect(m_component_create_texture.get(), &QAction::triggered, this, &Project_Window::create_texture);
    QObject::connect(m_component_create_material.get(), &QAction::triggered, this, &Project_Window::create_material);
    QObject::connect(m_component_create_model.get(), &QAction::triggered, this, &Project_Window::create_model);
    QObject::connect(m_component_create_package.get(), &QAction::triggered, this, &Project_Window::create_package);
    QObject::connect(m_component_create_release.get(), &QAction::triggered, this, &Project_Window::create_release);

    // Build the File menu. It does not take ownership of the QActions.
    m_component_create->addAction(m_component_create_file.get());
    m_component_create->addAction(m_component_create_texture.get());
    m_component_create->addAction(m_component_create_material.get());
    m_component_create->addAction(m_component_create_model.get());
    m_component_create->addAction(m_component_create_package.get());
    m_component_create->addAction(m_component_create_release.get());

    m_component->addMenu(m_component_create.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(m_component.get());

    // Menu Bar -> Build
    //============================================================
    // Configure the menu items
    QObject::connect(m_build_build_project.get(), &QAction::triggered, this, &Project_Window::build_project);
    QObject::connect(m_build_rebuild_project.get(), &QAction::triggered, this, &Project_Window::rebuild_project);
    QObject::connect(m_build_clean_project.get(), &QAction::triggered, this, &Project_Window::clean_project);
    QObject::connect(m_build_build_component.get(), &QAction::triggered, this, &Project_Window::build_component);
    QObject::connect(m_build_rebuild_component.get(), &QAction::triggered, this, &Project_Window::rebuild_component);
    QObject::connect(m_build_clean_component.get(), &QAction::triggered, this, &Project_Window::clean_component);

    // Build the File menu. It does not take ownership of the QActions.
    m_build->addAction(m_build_build_project.get());
    m_build->addAction(m_build_rebuild_project.get());
    m_build->addAction(m_build_clean_project.get());
    m_build->addSeparator();
    m_build->addAction(m_build_build_component.get());
    m_build->addAction(m_build_rebuild_component.get());
    m_build->addAction(m_build_clean_component.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(m_build.get());


    // Menu Bar -> Install
    //============================================================
    // Configure the menu items
    QObject::connect(m_install_install_status.get(), &QAction::triggered, this, &Project_Window::install_status);
    QObject::connect(m_install_install_component.get(), &QAction::triggered, this, &Project_Window::install_component);
    QObject::connect(m_install_uninstall_component.get(), &QAction::triggered, this, &Project_Window::uninstall_component);
    QObject::connect(m_install_uninstall_all.get(), &QAction::triggered, this, &Project_Window::uninstall_all);

    // Build the File menu. It does not take ownership of the QActions.
    m_install->addAction(m_install_install_status.get());
    m_install->addSeparator();
    m_install->addAction(m_install_install_component.get());
    m_install->addAction(m_install_uninstall_component.get());
    m_install->addSeparator();
    m_install->addAction(m_install_uninstall_all.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(m_install.get());

    // Menu Bar -> Settings
    //============================================================
    // Configure the menu items
    QObject::connect(m_settings_settings.get(), &QAction::triggered, this, &Project_Window::settings);
    QObject::connect(m_settings_tf2_settings.get(), &QAction::triggered, this, &Project_Window::tf2_settings);
    QObject::connect(m_settings_sfm_settings.get(), &QAction::triggered, this, &Project_Window::sfm_settings);

    // Build the File menu. It does not take ownership of the QActions.
    m_settings->addAction(m_settings_settings.get());
    m_settings->addAction(m_settings_tf2_settings.get());
    m_settings->addAction(m_settings_sfm_settings.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(m_settings.get());

    // Menu Bar -> Help
    //============================================================
    // Configure the menu items
    QObject::connect(m_help_help.get(), &QAction::triggered, this, &Project_Window::help);
    QObject::connect(m_help_about.get(), &QAction::triggered, this, &Project_Window::about);

    // Build the File menu. It does not take ownership of the QActions.
    m_help->addAction(m_help_help.get());
    m_help->addAction(m_help_about.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(m_help.get());


    // Update everything
    notify_project_changes();
}

sak::Project_Window::~Project_Window()
{
    // If this is owned by the stack it will be double-deleted.
    m_background_widget->setParent(nullptr);
}

// Menu Bar -> File
//============================================================
// Make a new emtpy Project based on what the user supplies via a dialog.
// If the user cancels out, nothing happens.
void sak::Project_Window::new_project()
{
    // if there's a project ask to save it and stop if the user cancels out
    if (is_project_open()
        //&& has_unsaved_edits()
        && !ask_to_save() )
    {
        return;
    }

    auto l_new = std::make_unique<QWidget>();
    auto l_layout = std::make_unique<QVBoxLayout>(); //Central widget MUST HAVE A LAYOUT
    auto l_content = std::make_unique<QLabel>("new project",nullptr);

    l_layout->addWidget(l_content.release());
    l_new->setLayout(l_layout.release());

    m_central_stack->addWidget(l_new.release());
    m_central_stack->setCurrentIndex(1);

    notify_project_changes();
}

// Opens a project and loads the data found based on what the user supplies
// via a dialog. If the user cancels out, nothing happens.
void sak::Project_Window::open_project()
{
}

// Save the Project data.
void sak::Project_Window::save_project()
{
}

// Ask to save then close the Project if that is not cancelled.
void sak::Project_Window::close_project()
{// if there's a project ask to save it and stop if the user cancels out
    if (is_project_open()
        //&& has_unsaved_edits()
        && !ask_to_save() )
    {
        return;
    }

    // capture the removed widget
    std::unique_ptr<QWidget> l_removed{m_central_stack->widget(1)};
    m_central_stack->removeWidget(l_removed.get());
    // De-parent it so that it will be destroyed when this function ends.
    l_removed->setParent(nullptr);

    m_central_stack->setCurrentIndex(0);
    notify_project_changes();
}

// Ask to save then quit if that is not cancelled.
void sak::Project_Window::exit()
{
    this->close();
}

// Menu Bar -> Edit
//============================================================
// Undo the last command issued.
void sak::Project_Window::undo()
{

}

// Redo the last undone command in the command history
void sak::Project_Window::redo()
{

}

// View the entire command history of the project.
void sak::Project_Window::view_history()
{

}

// Cleat the undo/redo history of of the Project.
void sak::Project_Window::clear_history()
{

}

// Menu Bar -> Create
//============================================================
// Create a new File in the active Project;
void sak::Project_Window::create_file()
{

}

// Create a new Texture in the active Project;
void sak::Project_Window::create_texture()
{

}

// Create a new Material in the active Project;
void sak::Project_Window::create_material()
{

}

// Create a new Model in the active Project;
void sak::Project_Window::create_model()
{

}

// Create a new Package in the active Project;
void sak::Project_Window::create_package()
{

}

// Create a new Release in the active Project;
void sak::Project_Window::create_release()
{

}

// Menu Bar -> Build
//============================================================
// Build all the components of the Project.
void sak::Project_Window::build_project()
{

}

// Reuild all the components of the Project.
void sak::Project_Window::rebuild_project()
{

}

// Delete all the temporary and resulting files from building the Project.
void sak::Project_Window::clean_project()
{

}

// Build the currently selected Component of the Project.
void sak::Project_Window::build_component()
{

}

// Reuild the currently selected Component of the Project.
void sak::Project_Window::rebuild_component()
{

}

// Delete all the temporary and resulting files from building the currently
// selected Component of the Project.
void sak::Project_Window::clean_component()
{

}

// Menu Bar -> Install
//============================================================
// Review the current install status of all components.
void sak::Project_Window::install_status()
{

}

// Install the current component. Opens a dialog detailing required options
// and the status of the install.
void sak::Project_Window::install_component()
{

}

// Delete all the temporary and resulting files from building the Project.
void sak::Project_Window::uninstall_component()
{

}

// Uninstalls all the components that are currently installed.
void sak::Project_Window::uninstall_all()
{

}

// Menu Bar -> System
//============================================================
// Open the settings editor.
void sak::Project_Window::settings()
{

}

// Open the settings editor on the tf2 page.
void sak::Project_Window::tf2_settings()
{

}

// Open the settings editor on the sfm page.
void sak::Project_Window::sfm_settings()
{

}

// Menu Bar -> Help
//============================================================
// Open help browser.
void sak::Project_Window::help()
{

}

// Open the about dialog.
void sak::Project_Window::about()
{

}



// Auxilliary
//============================================================
// Is a Project currently open?
bool sak::Project_Window::is_project_open() const
{
    // Whether or not the stack contains any widgets.
    return m_central_stack->count() == 2;
}

// Spawn a message box asking if the user wants to save the current project,
// act on it and return true if the action was never cancelled.
bool sak::Project_Window::ask_to_save()
{
    int msgBoxRet = QMessageBox::question(this,
                                              c_application_title,
                                              tr("The project has been modified.\n"
                                                 "Do you want to save your changes?"),
                                              QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                              QMessageBox::Save);

    switch (msgBoxRet)
    {
    case QMessageBox::Save:
        // Save was clicked
        {
        save_project();
        return true;
        }
    case QMessageBox::Discard:
        // Discard was clicked
        return true;
    case QMessageBox::Cancel:
        // Cancel was clicked
        return false;
    default:
        // should never be reached
        return false;
    }
}

// Internal Interface
//============================================================
// Change anything that needs to change if a Project is opended or closed.
void sak::Project_Window::notify_project_changes()
{
    if(is_project_open())
    {
        m_file_new_project.get()->setEnabled(true);
        m_file_open_project.get()->setEnabled(true);
        m_file_save_project.get()->setEnabled(true);
        m_file_close_project.get()->setEnabled(true);
        m_file_exit.get()->setEnabled(true);

        m_component.get()->setEnabled(true);

        m_build.get()->setEnabled(true);

        m_install.get()->setEnabled(true);
    }
    else
    {
        m_file_new_project.get()->setEnabled(true);
        m_file_open_project.get()->setEnabled(true);
        m_file_save_project.get()->setEnabled(false);
        m_file_close_project.get()->setEnabled(false);
        m_file_exit.get()->setEnabled(true);

        m_component.get()->setEnabled(false);

        m_build.get()->setEnabled(false);

        m_install.get()->setEnabled(false);
    }
    // Since undo changes are dependent on the Project, check that too.
    notify_undo_changes();
    // And anything that depends on a component being selected.
    notify_component_changes();
}

// Change anything that needs to change if undo changes are made.
void sak::Project_Window::notify_undo_changes()
{
    if(is_project_open())
    {
        m_edit.get()->setEnabled(true);

        // Enable or disable undo/redo depending on whether there are
        // commands to undo.
    }
    else
    {
        m_edit.get()->setEnabled(false);
    }
}


// Change anything that needs to change if the selected componenent changes.
void sak::Project_Window::notify_component_changes()
{
    // need to ask stuff about the selected component
}



