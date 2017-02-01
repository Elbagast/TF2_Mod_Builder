#ifndef PROJECT_WINDOW_H
#define PROJECT_WINDOW_H

#include <QMainWindow>
#include <memory>

class QCheckBox;
class QWidget;
class QVBoxLayout;
class QStackedWidget;

namespace sak
{
    //---------------------------------------------------------------------------
    // Project_Window
    //---------------------------------------------------------------------------
    // Main Window class for an open Project.
    class Project_Window :
            public QMainWindow
    {
        Q_OBJECT
    public:

        // Special 6
        //============================================================
        explicit Project_Window(QWidget* a_parent = nullptr);
        ~Project_Window() override;


        // Menu Bar -> File
        //============================================================
        // Make a new emtpy Project based on what the user supplies via a dialog.
        // If the user cancels out, nothing happens.
        void new_project();

        // Opens a project and loads the data found based on what the user supplies
        // via a dialog. If the user cancels out, nothing happens.
        void open_project();

        // Save the Project data.
        void save_project();

        // Ask to save then close the Project if that is not cancelled.
        void close_project();

        // Ask to save then quit if that is not cancelled.
        void exit();

        // Menu Bar -> Edit
        //============================================================
        // Undo the last command issued.
        void undo();

        // Redo the last undone command in the command history
        void redo();

        // View the entire command history of the project.
        void view_history();

        // Cleat the undo/redo history of of the Project.
        void clear_history();

        // Menu Bar -> Component
        //============================================================
        // Create a new File in the active Project;
        void create_file();

        // Create a new Texture in the active Project;
        void create_texture();

        // Create a new Material in the active Project;
        void create_material();

        // Create a new Model in the active Project;
        void create_model();

        // Create a new Package in the active Project;
        void create_package();

        // Create a new Release in the active Project;
        void create_release();

        // Menu Bar -> Build
        //============================================================
        // Build all the components of the Project.
        void build_project();

        // Reuild all the components of the Project.
        void rebuild_project();

        // Delete all the temporary and resulting files from building the Project.
        void clean_project();

        // Build the currently selected Component of the Project.
        void build_component();

        // Reuild the currently selected Component of the Project.
        void rebuild_component();

        // Delete all the temporary and resulting files from building the currently
        // selected Component of the Project.
        void clean_component();

        // Menu Bar -> Install
        //============================================================
        // Review the current install status of all components.
        void install_status();

        // Install the current component. Opens a dialog detailing required options
        // and the status of the install.
        void install_component();

        // Delete all the temporary and resulting files from building the Project.
        void uninstall_component();

        // Uninstalls all the components that are currently installed.
        void uninstall_all();

        // Menu Bar -> System
        //============================================================
        // Open the settings editor.
        void settings();

        // Open the settings editor on the tf2 page.
        void tf2_settings();

        // Open the settings editor on the sfm page.
        void sfm_settings();

        // Menu Bar -> Help
        //============================================================
        // Open help browser.
        void help();

        // Open the about dialog.
        void about();


        // Auxilliary
        //============================================================
        // Is a Project currently open?
        bool is_project_open() const;

        // Spawn a message box asking if the user wants to save the current project,
        // act on it and return true if the action was never cancelled.
        bool ask_to_save();

    private:

        // Internal Interface
        //============================================================
        // Change anything that needs to change if a Project is opended or closed.
        void notify_project_changes();

        // Change anything that needs to change if undo changes are made.
        void notify_undo_changes();

        // Change anything that needs to change if the selected componenent changes.
        void notify_component_changes();

        // Data Members
        //============================================================
        std::unique_ptr<QStackedWidget> m_central_stack;

        class Background_Widget;
        std::unique_ptr<Background_Widget> m_background_widget;

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
    };
}

#endif // PROJECT_WINDOW_H
