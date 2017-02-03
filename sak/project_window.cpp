#include "project_window.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QCloseEvent>

#include "dialog/new_project_dialog.h"

namespace
{
    QString const c_title_application{"TF2 Mod Builder"};

    QString const c_title_file{"File"};
    QString const c_title_file_new_project{"New Project"};
    QString const c_title_file_open_project{"Open Project"};
    QString const c_title_file_save_project{"Save Project"};
    QString const c_title_file_close_project{"Close Project"};
    QString const c_title_file_exit{"Exit"};

    QString const c_title_edit{"Edit"};
    QString const c_title_edit_undo{"Undo"};
    QString const c_title_edit_redo{"Redo"};
    QString const c_title_edit_view_history{"View History"};
    QString const c_title_edit_clear_history{"Clear History"};

    QString const c_title_component{"Component"};
    QString const c_title_component_create{"Create..."};
    QString const c_title_component_create_file{"File"};
    QString const c_title_component_create_texture{"Texture"};
    QString const c_title_component_create_material{"Material"};
    QString const c_title_component_create_model{"Model"};
    QString const c_title_component_create_package{"Package"};
    QString const c_title_component_create_release{"Release"};

    QString const c_title_build{"Build"};
    QString const c_title_build_build_project{"Build Project"};
    QString const c_title_build_rebuild_project{"Rebuild Project"};
    QString const c_title_build_clean_project{"Clean Project"};
    QString const c_title_build_build_component{"Build..."};
    QString const c_title_build_rebuild_component{"Rebuild..."};
    QString const c_title_build_clean_component{"Clean..."};

    QString const c_title_build_build_component_front{"Build "};
    QString const c_title_build_rebuild_component_front{"Rebuild "};
    QString const c_title_build_clean_component_front{"Clean "};

    QString const c_title_install{"Install"};
    QString const c_title_install_install_status{"Install Status"};
    QString const c_title_install_install_component{"Install..."};
    QString const c_title_install_uninstall_component{"Uninstall..."};
    QString const c_title_install_uninstall_all{"Uninstall all"};

    QString const c_title_install_install_component_front{"Install "};
    QString const c_title_install_uninstall_component_front{"Uninstall "};

    QString const c_title_settings{"Settings"};
    QString const c_title_settings_settings{"Settings"};
    QString const c_title_settings_tf2_settings{"TF2 Settings"};
    QString const c_title_settings_sfm_settings{"SFM Settings"};

    QString const c_title_help{"Help"};
    QString const c_title_help_help{"Help"};
    QString const c_title_help_about{"About"};


    QString const c_default_project_name{"untitled"};
    QString const c_default_project_location{"D:\\Temp"};
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
// Project_Widget
//---------------------------------------------------------------------------
// Temporary class to build functionality.
class sak::Project_Widget :
        public QWidget
{
public:
    explicit Project_Widget(QString const& a_name, QString const& a_location, QWidget* a_parent = nullptr):
        QWidget(a_parent)
    {
        //barebones as all hell for now.

        auto l_layout = std::make_unique<QVBoxLayout>();
        auto l_name = std::make_unique<QLabel>(a_name,nullptr);
        auto l_location = std::make_unique<QLabel>(a_location,nullptr);

        l_layout->addWidget(l_name.release());
        l_layout->addWidget(l_location.release());
        this->setLayout(l_layout.release());

    }
    ~Project_Widget() override = default;
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
    m_project_widget{},

    m_file{std::make_unique<QMenu>(c_title_file)},
    m_file_new_project{std::make_unique<QAction>(c_title_file_new_project)},
    m_file_open_project{std::make_unique<QAction>(c_title_file_open_project)},
    m_file_save_project{std::make_unique<QAction>(c_title_file_save_project)},
    m_file_close_project{std::make_unique<QAction>(c_title_file_close_project)},
    m_file_exit{std::make_unique<QAction>(c_title_file_exit)},

    m_edit{std::make_unique<QMenu>(c_title_edit)},
    m_edit_undo{std::make_unique<QAction>(c_title_edit_undo)},
    m_edit_redo{std::make_unique<QAction>(c_title_edit_redo)},
    m_edit_view_history{std::make_unique<QAction>(c_title_edit_view_history)},
    m_edit_clear_history{std::make_unique<QAction>(c_title_edit_clear_history)},

    m_component{std::make_unique<QMenu>(c_title_component)},
    m_component_create{std::make_unique<QMenu>(c_title_component_create)},
    m_component_create_file{std::make_unique<QAction>(c_title_component_create_file)},
    m_component_create_texture{std::make_unique<QAction>(c_title_component_create_texture)},
    m_component_create_material{std::make_unique<QAction>(c_title_component_create_material)},
    m_component_create_model{std::make_unique<QAction>(c_title_component_create_model)},
    m_component_create_package{std::make_unique<QAction>(c_title_component_create_package)},
    m_component_create_release{std::make_unique<QAction>(c_title_component_create_release)},

    m_build{std::make_unique<QMenu>(c_title_build)},
    m_build_build_project{std::make_unique<QAction>(c_title_build_build_project)},
    m_build_rebuild_project{std::make_unique<QAction>(c_title_build_rebuild_project)},
    m_build_clean_project{std::make_unique<QAction>(c_title_build_clean_project)},
    m_build_build_component{std::make_unique<QAction>(c_title_build_build_component)},
    m_build_rebuild_component{std::make_unique<QAction>(c_title_build_rebuild_component)},
    m_build_clean_component{std::make_unique<QAction>(c_title_build_clean_component)},

    m_install{std::make_unique<QMenu>(c_title_install)},
    m_install_install_status{std::make_unique<QAction>(c_title_install_install_status)},
    m_install_install_component{std::make_unique<QAction>(c_title_install_install_component)},
    m_install_uninstall_component{std::make_unique<QAction>(c_title_install_uninstall_component)},
    m_install_uninstall_all{std::make_unique<QAction>(c_title_install_uninstall_all)},

    m_settings{std::make_unique<QMenu>(c_title_settings)},
    m_settings_settings{std::make_unique<QAction>(c_title_settings_settings)},
    m_settings_tf2_settings{std::make_unique<QAction>(c_title_settings_tf2_settings)},
    m_settings_sfm_settings{std::make_unique<QAction>(c_title_settings_sfm_settings)},

    m_help{std::make_unique<QMenu>(c_title_help)},
    m_help_help{std::make_unique<QAction>(c_title_help_help)},
    m_help_about{std::make_unique<QAction>(c_title_help_about)}
{
    // Add the background widget to the stack.
    m_central_stack->addWidget(m_background_widget.get());

    // Set the central widget to be the stack. We modify the stack to change what the window is displaying.
    this->setCentralWidget(m_central_stack.get());

    // Window Title
    this->setWindowTitle(c_title_application);

    // Minimum Window Size (720p for now)
    this->setMinimumSize(1280,720);

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
    if(m_project_widget) m_project_widget->setParent(nullptr);
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

    // get initalisation parameters from the user...
    New_Project_Dialog l_dialog{c_default_project_name, c_default_project_location};
    auto l_result = l_dialog.exec();

    if (l_result == QDialog::Rejected)
    {
        return;
    }


    // Make the widget - could be a factory function instead?
    m_project_widget = std::make_unique<Project_Widget>(l_dialog.name(), l_dialog.location());

    m_central_stack->addWidget(m_project_widget.get());
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
{
    // if there's a project ask to save it and stop if the user cancels out
    if (is_project_open()
        //&& has_unsaved_edits()
        && !ask_to_save() )
    {
        return;
    }

    // Unhook the project widget.
    m_central_stack->removeWidget(m_project_widget.get());
    // Now destory it.
    m_project_widget.reset();
    // Set the stack to point to the first widget again.
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



// Internal Interface
//============================================================
// State query helpers for determining whether actions are
// currently active, and what they do.

// Is a project currently open?
bool sak::Project_Window::is_project_open() const
{
    // Whether or not the stack contains a second widget (the Project_Widget).
    return m_central_stack->count() == 2;
}

// Can we currently call undo?
bool sak::Project_Window::can_undo() const
{
    return false;
}

// Can we currently call redo?
bool sak::Project_Window::can_redo() const
{
    return false;
}

// Get the name of the currently selected component. Empty if none is selected.
QString sak::Project_Window::selected_component_name() const
{
    return QString();
}

// Is a component selected? If no project is open, this is always false.
bool sak::Project_Window::is_component_selected() const
{
    return false;
}

// Is the selected component buildable? If no component is open, this is always false.
bool sak::Project_Window::is_component_buildable() const
{
    return false;
}

// Is the selected component installable? If no component is open, this is always false.
bool sak::Project_Window::is_component_installable() const
{
    return false;
}


// Spawn a message box asking if the user wants to save the current project,
// act on it and return true if the action was never cancelled.
bool sak::Project_Window::ask_to_save()
{
    int msgBoxRet = QMessageBox::question(this,
                                              c_title_application,
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

// Virtuals
//============================================================
// Needed so that we can ask to save when we use the x button in the corner to close.
void sak::Project_Window::closeEvent(QCloseEvent *event)
{
    // if any of these are true then we can saftely exit and will
    if (is_project_open() // project is open
        //&& has_unsaved_data() // there is unsaved data
        && !ask_to_save() // and we cancel the save prompt
        )
    {
        // cancel the close attempt
        event->ignore();

    }

    // Handle the event as normal
    QMainWindow::closeEvent(event);
}

// Notifications
//============================================================
// Tell parts of the window that these states have changed so they should update.

// Change anything that needs to change if a Project is opended or closed.
void sak::Project_Window::notify_project_changes()
{
    bool l_project_open_state{is_project_open()};

    m_file_save_project.get()->setEnabled(l_project_open_state);
    m_file_close_project.get()->setEnabled(l_project_open_state);

    m_edit.get()->setEnabled(l_project_open_state);

    m_component.get()->setEnabled(l_project_open_state);

    m_build.get()->setEnabled(l_project_open_state);

    m_install.get()->setEnabled(l_project_open_state);

    // Since undo changes are dependent on the Project, check that too.
    notify_undo_changes();
    // And anything that depends on a component being selected.
    notify_component_changes();

}

// Change anything that needs to change if undo changes are made.
void sak::Project_Window::notify_undo_changes()
{
    // assuming the project status is already correct (this controls
    // the menu that these actions are in so they may already be inaccessable)
    // set the action statuses to what is needed.

    m_edit_undo.get()->setEnabled(can_undo());
    m_edit_redo.get()->setEnabled(can_redo());
}


// Change anything that needs to change if the selected componenent changes.
void sak::Project_Window::notify_component_changes()
{
    QString l_component_name{selected_component_name()};

    // Buildable?
    bool l_is_component_buildable{is_component_buildable()};
    m_build_build_component->setEnabled(l_is_component_buildable);
    m_build_rebuild_component->setEnabled(l_is_component_buildable);
    m_build_clean_component->setEnabled(l_is_component_buildable);
    if (l_is_component_buildable)
    {
        m_build_build_component->setText(c_title_build_build_component_front + l_component_name);
        m_build_rebuild_component->setText(c_title_build_rebuild_component_front + l_component_name);
        m_build_clean_component->setText(c_title_build_clean_component_front + l_component_name);
    }
    else
    {
        m_build_build_component->setText(c_title_build_build_component);
        m_build_rebuild_component->setText(c_title_build_rebuild_component);
        m_build_clean_component->setText(c_title_build_clean_component);
    }

    // Installable?
    bool l_is_component_installable{is_component_buildable()};
    m_install_install_component->setEnabled(l_is_component_installable);
    m_install_uninstall_component->setEnabled(l_is_component_installable);
    if (l_is_component_installable)
    {
        m_install_install_component->setText(c_title_install_install_component_front + l_component_name);
        m_install_uninstall_component->setText(c_title_install_uninstall_component_front + l_component_name);
    }
    else
    {
        m_install_install_component->setText(c_title_install_install_component);
        m_install_uninstall_component->setText(c_title_install_uninstall_component);
    }
}



