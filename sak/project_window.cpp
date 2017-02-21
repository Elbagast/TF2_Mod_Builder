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
#include <QFileDialog>
#include <QDebug>

#include "project_widget.h"
#include "dialog/new_project_dialog.h"
#include "fixed_settings.h"
#include "project.h"
#include "exceptions/exception.h"

//---------------------------------------------------------------------------
// Project_Window
//---------------------------------------------------------------------------

// Internal constants and implementation
//============================================================
namespace
{
    QString const c_title_application{u8"TF2 Mod Builder"};

    QString const c_title_file{u8"File"};
    QString const c_title_file_new_project{u8"New Project"};
    QString const c_title_file_open_project{u8"Open Project"};
    QString const c_title_file_save_project{u8"Save Project"};
    QString const c_title_file_close_project{u8"Close Project"};
    QString const c_title_file_exit{u8"Exit"};

    QString const c_title_edit{u8"Edit"};
    QString const c_title_edit_undo{u8"Undo"};
    QString const c_title_edit_redo{u8"Redo"};
    QString const c_title_edit_view_history{u8"View History"};
    QString const c_title_edit_clear_history{u8"Clear History"};

    QString const c_title_component{u8"Component"};
    QString const c_title_component_create{u8"Create..."};
    QString const c_title_component_create_file{u8"File"};
    QString const c_title_component_create_texture{u8"Texture"};
    QString const c_title_component_create_material{u8"Material"};
    QString const c_title_component_create_model{u8"Model"};
    QString const c_title_component_create_package{u8"Package"};
    QString const c_title_component_create_release{u8"Release"};

    QString const c_title_build{u8"Build"};
    QString const c_title_build_build_project{u8"Build Project"};
    QString const c_title_build_rebuild_project{u8"Rebuild Project"};
    QString const c_title_build_clean_project{u8"Clean Project"};
    QString const c_title_build_build_component{u8"Build..."};
    QString const c_title_build_rebuild_component{u8"Rebuild..."};
    QString const c_title_build_clean_component{u8"Clean..."};

    QString const c_title_build_build_component_front{u8"Build "};
    QString const c_title_build_rebuild_component_front{u8"Rebuild "};
    QString const c_title_build_clean_component_front{u8"Clean "};

    QString const c_title_install{u8"Install"};
    QString const c_title_install_install_status{u8"Install Status"};
    QString const c_title_install_install_component{u8"Install..."};
    QString const c_title_install_uninstall_component{u8"Uninstall..."};
    QString const c_title_install_uninstall_all{u8"Uninstall all"};

    QString const c_title_install_install_component_front{u8"Install "};
    QString const c_title_install_uninstall_component_front{u8"Uninstall "};

    QString const c_title_settings{u8"Settings"};
    QString const c_title_settings_settings{u8"Settings"};
    QString const c_title_settings_tf2_settings{u8"TF2 Settings"};
    QString const c_title_settings_sfm_settings{u8"SFM Settings"};

    QString const c_title_help{u8"Help"};
    QString const c_title_help_help{u8"Help"};
    QString const c_title_help_about{u8"About"};

    QString const c_open_project_title{u8"Open Project"};
    QString const c_open_project_types{u8"Project file (*.sakpro)"};



    // Seperating out since we might want to change this to display information.
    class Background_Widget :
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
}

// Pimpl Data
//============================================================
class sak::Project_Window::Implementation
{
public:
    std::unique_ptr<QStackedWidget> m_central_stack;

    std::unique_ptr<Background_Widget> m_background_widget;

    // Going to need some kind of settings object or reference to one. Or singleton?

    std::unique_ptr<Project_Widget> m_project_widget;

    std::unique_ptr<QMenu> m_file;
    std::unique_ptr<QAction> m_file_new_project;
    std::unique_ptr<QAction> m_file_open_project;
    std::unique_ptr<QAction> m_file_save_project;
    std::unique_ptr<QAction> m_file_close_project;
    std::unique_ptr<QAction> m_file_exit;

    std::unique_ptr<QMenu> m_edit;
    std::unique_ptr<QAction> m_edit_undo;
    std::unique_ptr<QAction> m_edit_redo;
    std::unique_ptr<QAction> m_edit_view_history;
    std::unique_ptr<QAction> m_edit_clear_history;

    std::unique_ptr<QMenu> m_component;
    std::unique_ptr<QMenu> m_component_create;
    std::unique_ptr<QAction> m_component_create_file;
    std::unique_ptr<QAction> m_component_create_texture;
    std::unique_ptr<QAction> m_component_create_material;
    std::unique_ptr<QAction> m_component_create_model;
    std::unique_ptr<QAction> m_component_create_package;
    std::unique_ptr<QAction> m_component_create_release;

    std::unique_ptr<QMenu> m_build;
    std::unique_ptr<QAction> m_build_build_project;
    std::unique_ptr<QAction> m_build_rebuild_project;
    std::unique_ptr<QAction> m_build_clean_project;
    std::unique_ptr<QAction> m_build_build_component;
    std::unique_ptr<QAction> m_build_rebuild_component;
    std::unique_ptr<QAction> m_build_clean_component;

    std::unique_ptr<QMenu> m_install;
    std::unique_ptr<QAction> m_install_install_status;
    std::unique_ptr<QAction> m_install_install_component;
    std::unique_ptr<QAction> m_install_uninstall_component;
    std::unique_ptr<QAction> m_install_uninstall_all;

    std::unique_ptr<QMenu> m_settings;
    std::unique_ptr<QAction> m_settings_settings;
    std::unique_ptr<QAction> m_settings_tf2_settings;
    std::unique_ptr<QAction> m_settings_sfm_settings;

    std::unique_ptr<QMenu> m_help;
    std::unique_ptr<QAction> m_help_help;
    std::unique_ptr<QAction> m_help_about;

    Implementation():
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
    {}


};

// Special 6
//============================================================
sak::Project_Window::Project_Window(QWidget* a_parent):
    QMainWindow(a_parent),
    m_data{std::make_unique<Implementation>()}
{
    // Add the background widget to the stack.
    imp().m_central_stack->addWidget(imp().m_background_widget.get());

    // Set the central widget to be the stack. We modify the stack to change what the window is displaying.
    this->setCentralWidget(imp().m_central_stack.get());

    // Window Title
    //this->setWindowTitle(c_title_application);
    update_window_title();

    // Minimum Window Size (720p for now)
    this->setMinimumSize(1280,720);

    // Menu Bar -> File
    //============================================================
    // Configure the menu items
    QObject::connect(imp().m_file_new_project.get(), &QAction::triggered, this, &Project_Window::new_project);
    QObject::connect(imp().m_file_open_project.get(), &QAction::triggered, this, &Project_Window::open_project);
    QObject::connect(imp().m_file_save_project.get(), &QAction::triggered, this, &Project_Window::save_project);
    QObject::connect(imp().m_file_close_project.get(), &QAction::triggered, this, &Project_Window::close_project);
    QObject::connect(imp().m_file_exit.get(), &QAction::triggered, this, &Project_Window::exit);

    // Build the File menu. It does not take ownership of the QActions.
    imp().m_file->addAction(imp().m_file_new_project.get());
    imp().m_file->addAction(imp().m_file_open_project.get());
    imp().m_file->addSeparator();
    imp().m_file->addAction(imp().m_file_save_project.get());
    imp().m_file->addSeparator();
    imp().m_file->addAction(imp().m_file_close_project.get());
    imp().m_file->addSeparator();
    imp().m_file->addAction(imp().m_file_exit.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(imp().m_file.get());

    // Menu Bar -> Edit
    //============================================================
    // Configure the menu items
    QObject::connect(imp().m_edit_undo.get(), &QAction::triggered, this, &Project_Window::undo);
    QObject::connect(imp().m_edit_redo.get(), &QAction::triggered, this, &Project_Window::redo);
    QObject::connect(imp().m_edit_view_history.get(), &QAction::triggered, this, &Project_Window::view_history);
    QObject::connect(imp().m_edit_clear_history.get(), &QAction::triggered, this, &Project_Window::clear_history);

    // Build the File menu. It does not take ownership of the QActions.
    imp().m_edit->addAction(imp().m_edit_undo.get());
    imp().m_edit->addAction(imp().m_edit_redo.get());
    imp().m_edit->addSeparator();
    imp().m_edit->addAction(imp().m_edit_view_history.get());
    imp().m_edit->addAction(imp().m_edit_clear_history.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(imp().m_edit.get());

    // Menu Bar -> Create
    //============================================================
    // Configure the menu items
    QObject::connect(imp().m_component_create_file.get(), &QAction::triggered, this, &Project_Window::create_file);
    QObject::connect(imp().m_component_create_texture.get(), &QAction::triggered, this, &Project_Window::create_texture);
    QObject::connect(imp().m_component_create_material.get(), &QAction::triggered, this, &Project_Window::create_material);
    QObject::connect(imp().m_component_create_model.get(), &QAction::triggered, this, &Project_Window::create_model);
    QObject::connect(imp().m_component_create_package.get(), &QAction::triggered, this, &Project_Window::create_package);
    QObject::connect(imp().m_component_create_release.get(), &QAction::triggered, this, &Project_Window::create_release);

    // Build the File menu. It does not take ownership of the QActions.
    imp().m_component_create->addAction(imp().m_component_create_file.get());
    imp().m_component_create->addAction(imp().m_component_create_texture.get());
    imp().m_component_create->addAction(imp().m_component_create_material.get());
    imp().m_component_create->addAction(imp().m_component_create_model.get());
    imp().m_component_create->addAction(imp().m_component_create_package.get());
    imp().m_component_create->addAction(imp().m_component_create_release.get());

    imp().m_component->addMenu(imp().m_component_create.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(imp().m_component.get());

    // Menu Bar -> Build
    //============================================================
    // Configure the menu items
    QObject::connect(imp().m_build_build_project.get(), &QAction::triggered, this, &Project_Window::build_project);
    QObject::connect(imp().m_build_rebuild_project.get(), &QAction::triggered, this, &Project_Window::rebuild_project);
    QObject::connect(imp().m_build_clean_project.get(), &QAction::triggered, this, &Project_Window::clean_project);
    QObject::connect(imp().m_build_build_component.get(), &QAction::triggered, this, &Project_Window::build_component);
    QObject::connect(imp().m_build_rebuild_component.get(), &QAction::triggered, this, &Project_Window::rebuild_component);
    QObject::connect(imp().m_build_clean_component.get(), &QAction::triggered, this, &Project_Window::clean_component);

    // Build the File menu. It does not take ownership of the QActions.
    imp().m_build->addAction(imp().m_build_build_project.get());
    imp().m_build->addAction(imp().m_build_rebuild_project.get());
    imp().m_build->addAction(imp().m_build_clean_project.get());
    imp().m_build->addSeparator();
    imp().m_build->addAction(imp().m_build_build_component.get());
    imp().m_build->addAction(imp().m_build_rebuild_component.get());
    imp().m_build->addAction(imp().m_build_clean_component.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(imp().m_build.get());


    // Menu Bar -> Install
    //============================================================
    // Configure the menu items
    QObject::connect(imp().m_install_install_status.get(), &QAction::triggered, this, &Project_Window::install_status);
    QObject::connect(imp().m_install_install_component.get(), &QAction::triggered, this, &Project_Window::install_component);
    QObject::connect(imp().m_install_uninstall_component.get(), &QAction::triggered, this, &Project_Window::uninstall_component);
    QObject::connect(imp().m_install_uninstall_all.get(), &QAction::triggered, this, &Project_Window::uninstall_all);

    // Build the File menu. It does not take ownership of the QActions.
    imp().m_install->addAction(imp().m_install_install_status.get());
    imp().m_install->addSeparator();
    imp().m_install->addAction(imp().m_install_install_component.get());
    imp().m_install->addAction(imp().m_install_uninstall_component.get());
    imp().m_install->addSeparator();
    imp().m_install->addAction(imp().m_install_uninstall_all.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(imp().m_install.get());

    // Menu Bar -> Settings
    //============================================================
    // Configure the menu items
    QObject::connect(imp().m_settings_settings.get(), &QAction::triggered, this, &Project_Window::settings);
    QObject::connect(imp().m_settings_tf2_settings.get(), &QAction::triggered, this, &Project_Window::tf2_settings);
    QObject::connect(imp().m_settings_sfm_settings.get(), &QAction::triggered, this, &Project_Window::sfm_settings);

    // Build the File menu. It does not take ownership of the QActions.
    imp().m_settings->addAction(imp().m_settings_settings.get());
    imp().m_settings->addAction(imp().m_settings_tf2_settings.get());
    imp().m_settings->addAction(imp().m_settings_sfm_settings.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(imp().m_settings.get());

    // Menu Bar -> Help
    //============================================================
    // Configure the menu items
    QObject::connect(imp().m_help_help.get(), &QAction::triggered, this, &Project_Window::help);
    QObject::connect(imp().m_help_about.get(), &QAction::triggered, this, &Project_Window::about);

    // Build the File menu. It does not take ownership of the QActions.
    imp().m_help->addAction(imp().m_help_help.get());
    imp().m_help->addAction(imp().m_help_about.get());

    // Add the File menu to the menubar. It does not take ownership of the QMenu.
    this->menuBar()->addMenu(imp().m_help.get());


    // Update everything
    notify_project_changes();
}

sak::Project_Window::~Project_Window()
{
    // If this is owned by the stack it will be double-deleted.
    imp().m_background_widget->setParent(nullptr);
    if(imp().m_project_widget) imp().m_project_widget->setParent(nullptr);
}

// Menu Bar -> File
//============================================================
// Make a new empty Project based on what the user supplies via a dialog.
// If the user cancels out, nothing happens.
bool sak::Project_Window::new_project()
{
    // close the open project or do nothing if there isn't one.
    // if we didn't close it, stop
    if (!close_project())
    {
        return false;
    }

    // get initalisation parameters from the user...
    New_Project_Dialog l_dialog{};
    auto l_result = l_dialog.exec();

    // if ser cancels, stop
    if (l_result == QDialog::Rejected)
    {
        return false;
    }

    // Location project will be built in
    QDir l_dir{l_dialog.location()};

    // If the root dir for the project does not exist, and we fail to build it, error.
    if(!l_dir.exists(l_dialog.name()) && !l_dir.mkdir(l_dialog.name()))
    {
        // failed to make the project directory
        QMessageBox::warning(this, "New Project Failed","Could not create the project directory.");
        return false;
    }

    // Project root dir now exists, go to it
    l_dir.cd(l_dialog.name());

    // Compose the filepath for the project file
    QString l_filename{l_dialog.name() + Fixed_Settings::project_file_extension()};
    QString l_filepath{l_dir.filePath(l_filename)};

    qDebug() << "new project:";
    qDebug() << "dir: " << l_dir.absolutePath();
    qDebug() << "filename: " << l_filename;
    qDebug() << "filepath: " << l_filepath;

    // It might be worth seperating the initialisation of a project?
    // That way things like write permissions can be checked without making the data object?
    try
    {
        // Right now this constructor does the file stuff and emits exceptions if it can't
        auto l_project = std::make_unique<Project>(l_filepath);

        // Make the widget
        imp().m_project_widget = std::make_unique<Project_Widget>(std::move(l_project));
        QObject::connect(imp().m_project_widget.get(), &Project_Widget::signal_undo_change,
                         this, &Project_Window::notify_undo_changes);
    }
    catch(Filesystem_Error& e)
    {
        e.dialog(this);
        return false;
    }

    imp().m_central_stack->addWidget(imp().m_project_widget.get());
    imp().m_central_stack->setCurrentIndex(1);

    notify_project_changes();
    return true;
}

// Opens a project and loads the data found based on what the user supplies
// via a dialog. If the user cancels out, nothing happens.
bool sak::Project_Window::open_project()
{
    // close the open project or do nothing if there isn't one.
    // if we didn't close it, stop
    if (!close_project())
    {
        return false;
    }

    // Get a project file
    QString l_filepath = QFileDialog::getOpenFileName(this,
                                                      c_open_project_title,
                                                      Fixed_Settings::default_project_location(),
                                                      c_open_project_types);

    // If nothing then the user canceled the operation.
    if (l_filepath.isEmpty())
    {
        return false;
    }


    //qDebug() << "open project:";
    //qDebug() << "filepath: " << l_filename;

    try
    {
        // Right now this constructor does the file stuff and emits exceptions if it can't
        auto l_project = std::make_unique<Project>(l_filepath);

        // Make the widget
        auto l_widget = std::make_unique<Project_Widget>(std::move(l_project));

        // Install the widget
        std::swap(imp().m_project_widget,l_widget);
        QObject::connect(imp().m_project_widget.get(), &Project_Widget::signal_undo_change,
                         this, &Project_Window::notify_undo_changes);
    }
    catch(Filesystem_Error& e)
    {
        e.dialog(this);
        return false;
    }

    imp().m_central_stack->addWidget(imp().m_project_widget.get());
    imp().m_central_stack->setCurrentIndex(1);

    notify_project_changes();
    return true;
}

// Save the Project data.
void sak::Project_Window::save_project()
{
    if(is_project_open())
    {
        imp().m_project_widget->save_project();
    }
}

// Ask to save then close the Project if that is not cancelled.
bool sak::Project_Window::close_project()
{
    // if there's a project ask to save it and stop if the user cancels out
    if (is_project_open())
    {
        if (ask_to_save())
        {
            // user has not cancelled, do the close

            // Unhook the project widget.
            imp().m_central_stack->removeWidget(imp().m_project_widget.get());
            // Now destory it.
            imp().m_project_widget.reset();
            // Set the stack to point to the first widget again.
            imp().m_central_stack->setCurrentIndex(0);
            notify_project_changes();

            // closing success
            return true;
        }
        else
        {
            // we cancelled, no close
            return false;
        }
    }
    else
    {
        // no closing, so close is success, return true.
        return true;
    }
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
    if(is_project_open())
    {
        imp().m_project_widget->undo();
    }
}

// Redo the last undone command in the command history
void sak::Project_Window::redo()
{
    if(is_project_open())
    {
        imp().m_project_widget->redo();
    }
}

// View the entire command history of the project.
void sak::Project_Window::view_history()
{
    if(is_project_open())
    {
        imp().m_project_widget->view_history();
    }
}

// Cleat the undo/redo history of of the Project.
void sak::Project_Window::clear_history()
{
    if(is_project_open())
    {
        imp().m_project_widget->clear_history();
    }
}

// Menu Bar -> Create
//============================================================
// Create a new File in the active Project;
void sak::Project_Window::create_file()
{
    if(is_project_open())
    {
        imp().m_project_widget->create_file();
    }
}

// Create a new Texture in the active Project;
void sak::Project_Window::create_texture()
{
    if(is_project_open())
    {
        imp().m_project_widget->create_texture();
    }
}

// Create a new Material in the active Project;
void sak::Project_Window::create_material()
{
    if(is_project_open())
    {
        imp().m_project_widget->create_material();
    }
}

// Create a new Model in the active Project;
void sak::Project_Window::create_model()
{
    if(is_project_open())
    {
        imp().m_project_widget->create_model();
    }
}

// Create a new Package in the active Project;
void sak::Project_Window::create_package()
{
    if(is_project_open())
    {
        imp().m_project_widget->create_package();
    }
}

// Create a new Release in the active Project;
void sak::Project_Window::create_release()
{
    if(is_project_open())
    {
        imp().m_project_widget->create_release();
    }
}

// Menu Bar -> Build
//============================================================
// Build all the components of the Project.
void sak::Project_Window::build_project()
{
    if(is_project_open())
    {
        imp().m_project_widget->build_project();
    }
}

// Reuild all the components of the Project.
void sak::Project_Window::rebuild_project()
{
    if(is_project_open())
    {
        imp().m_project_widget->rebuild_project();
    }
}

// Delete all the temporary and resulting files from building the Project.
void sak::Project_Window::clean_project()
{
    if(is_project_open())
    {
        imp().m_project_widget->clean_project();
    }
}

// Build the currently selected Component of the Project.
void sak::Project_Window::build_component()
{
    if(is_project_open())
    {
        imp().m_project_widget->build_component();
    }
}

// Reuild the currently selected Component of the Project.
void sak::Project_Window::rebuild_component()
{
    if(is_project_open())
    {
        imp().m_project_widget->rebuild_component();
    }
}

// Delete all the temporary and resulting files from building the currently
// selected Component of the Project.
void sak::Project_Window::clean_component()
{
    if(is_project_open())
    {
        imp().m_project_widget->clean_component();
    }
}

// Menu Bar -> Install
//============================================================
// Review the current install status of all components.
void sak::Project_Window::install_status()
{
    if(is_project_open())
    {
        imp().m_project_widget->install_status();
    }
}

// Install the current component. Opens a dialog detailing required options
// and the status of the install.
void sak::Project_Window::install_component()
{
    if(is_project_open())
    {
        imp().m_project_widget->install_component();
    }
}

// Delete all the temporary and resulting files from building the Project.
void sak::Project_Window::uninstall_component()
{
    if(is_project_open())
    {
        imp().m_project_widget->uninstall_component();
    }
}

// Uninstalls all the components that are currently installed.
void sak::Project_Window::uninstall_all()
{
    if(is_project_open())
    {
        imp().m_project_widget->uninstall_all();
    }
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
    return cimp().m_project_widget != nullptr;
}

// Can we currently call undo?
bool sak::Project_Window::can_undo() const
{
    if(is_project_open())
    {
        return cimp().m_project_widget->can_undo();
    }
    else
    {
        return false;
    }
}

// Can we currently call redo?
bool sak::Project_Window::can_redo() const
{
    if(is_project_open())
    {
        return cimp().m_project_widget->can_redo();
    }
    else
    {
        return false;
    }
}

// Get the name of the currently selected component. Empty if none is selected.
QString sak::Project_Window::selected_component_name() const
{
    if(is_project_open())
    {
        return cimp().m_project_widget->selected_component_name();
    }
    else
    {
        return QString();
    }
}

// Is a component selected? If no project is open, this is always false.
bool sak::Project_Window::is_component_selected() const
{
    if(is_project_open())
    {
        return cimp().m_project_widget->is_component_selected();
    }
    else
    {
        return false;
    }
}

// Is the selected component buildable? If no component is open, this is always false.
bool sak::Project_Window::is_component_buildable() const
{
    if(is_project_open())
    {
        return cimp().m_project_widget->is_component_buildable();
    }
    else
    {
        return false;
    }
}

// Is the selected component installable? If no component is open, this is always false.
bool sak::Project_Window::is_component_installable() const
{
    if(is_project_open())
    {
        return cimp().m_project_widget->is_component_installable();
    }
    else
    {
        return false;
    }
}


// Spawn a message box asking if the user wants to save the current project,
// act on it and return true if the action was never cancelled.
bool sak::Project_Window::ask_to_save()
{
    if (is_project_open() && cimp().m_project_widget->has_unsaved_edits())
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
    else
    {
        return true;
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
    else
    {
        // Handle the event as normal
        QMainWindow::closeEvent(event);
    }
}

// Notifications
//============================================================
// Tell parts of the window that these states have changed so they should update.

// Change anything that needs to change if a Project is opended or closed.
void sak::Project_Window::notify_project_changes()
{
    bool l_project_open_state{is_project_open()};

    imp().m_file_save_project.get()->setEnabled(l_project_open_state);
    imp().m_file_close_project.get()->setEnabled(l_project_open_state);

    imp().m_edit.get()->setEnabled(l_project_open_state);

    imp().m_component.get()->setEnabled(l_project_open_state);

    imp().m_build.get()->setEnabled(l_project_open_state);

    imp().m_install.get()->setEnabled(l_project_open_state);

    // Since undo changes are dependent on the Project, check that too.
    notify_undo_changes();
    // And anything that depends on a component being selected.
    notify_component_changes();

    update_window_title();
}

// Change anything that needs to change if undo changes are made.
void sak::Project_Window::notify_undo_changes()
{
    // assuming the project status is already correct (this controls
    // the menu that these actions are in so they may already be inaccessable)
    // set the action statuses to what is needed.

    imp().m_edit_undo.get()->setEnabled(can_undo());
    imp().m_edit_redo.get()->setEnabled(can_redo());
}


// Change anything that needs to change if the selected componenent changes.
void sak::Project_Window::notify_component_changes()
{
    QString l_component_name{selected_component_name()};

    // Buildable?
    bool l_is_component_buildable{is_component_buildable()};
    imp().m_build_build_component->setEnabled(l_is_component_buildable);
    imp().m_build_rebuild_component->setEnabled(l_is_component_buildable);
    imp().m_build_clean_component->setEnabled(l_is_component_buildable);
    if (l_is_component_buildable)
    {
        imp().m_build_build_component->setText(c_title_build_build_component_front + l_component_name);
        imp().m_build_rebuild_component->setText(c_title_build_rebuild_component_front + l_component_name);
        imp().m_build_clean_component->setText(c_title_build_clean_component_front + l_component_name);
    }
    else
    {
        imp().m_build_build_component->setText(c_title_build_build_component);
        imp().m_build_rebuild_component->setText(c_title_build_rebuild_component);
        imp().m_build_clean_component->setText(c_title_build_clean_component);
    }

    // Installable?
    bool l_is_component_installable{is_component_buildable()};
    imp().m_install_install_component->setEnabled(l_is_component_installable);
    imp().m_install_uninstall_component->setEnabled(l_is_component_installable);
    if (l_is_component_installable)
    {
        imp().m_install_install_component->setText(c_title_install_install_component_front + l_component_name);
        imp().m_install_uninstall_component->setText(c_title_install_uninstall_component_front + l_component_name);
    }
    else
    {
        imp().m_install_install_component->setText(c_title_install_install_component);
        imp().m_install_uninstall_component->setText(c_title_install_uninstall_component);
    }
}



void sak::Project_Window::update_window_title()
{
    QString l_title{};
    if (is_project_open())
    {
        l_title += imp().m_project_widget->name() + " - ";
    }
    l_title += c_title_application;
    this->setWindowTitle(l_title);
}
