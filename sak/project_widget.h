#ifndef PROJECT_WIDGET_H
#define PROJECT_WIDGET_H

#include <memory>
#include <QWidget>
class QHBoxLayout;
class QTabWidget;
class QTreeView;
class QString;


namespace sak
{
    class Project_Window;

    //---------------------------------------------------------------------------
    // Project_Widget
    //---------------------------------------------------------------------------
    // Class that does the display work for managing a Project.
    /*
    Display layout:

    --------------------------------------
    |          | C-name\C-name\\\\\\\\\\\|
    |          |        -----------------|
    |          |                         |
    | Outliner |   Tab widget            |
    |  widget  |                         |
    |          |                         |
    |          |                         |
    --------------------------------------

    - Opening a component from the outliner opens/switches to the open component
    widget in the tab widget.
    - When a compoenent is destroyed its tab is removed.
    - If data is changed then its tab is updated.
    */
    class Project_Widget :
            public QWidget
    {
    public:
        // Special 6
        //============================================================
        // Create a Project_Widget that will load the data at the given filepath.
        explicit Project_Widget(QString const& a_filepath, QWidget* a_parent = nullptr);

        // Create a Project_Widget in the directory location with the given name.
        // After data creation the file is saved there even though the Project
        // will be empty.
        Project_Widget(QString const& a_location, QString const& a_name, QWidget* a_parent = nullptr);

        // Menu Actions
        //============================================================
        // Actions that can be done on a project that needs direct support in the widget.
        // Some of these tasks will have come from the Project_Window.

        // Menu Bar -> File
        //============================================================
        // Save the Project data.
        void save_project();

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

    private:
        std::unique_ptr<QHBoxLayout> m_layout;
        std::unique_ptr<QTreeView> m_outliner;
        std::unique_ptr<QTabWidget> m_tabs;

        // hiding data implementation for now since it will eventually be the Project class.
        class Data;
        std::unique_ptr<Data> m_data;
    };
}

#endif // PROJECT_WIDGET_H
