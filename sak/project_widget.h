#ifndef PROJECT_WIDGET_H
#define PROJECT_WIDGET_H

#include <memory>
#include <QWidget>

namespace sak
{
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
        // Create a Project with the given name in the directory location.
        // After data creation the file is saved there even though the Project
        // will be empty.
        //Project_Widget(QString const& a_name, QString const& a_location, QWidget* a_parent = nullptr);

        // Create a Project with the given filepath.
        explicit Project_Widget(QString const& a_filepath, QWidget* a_parent = nullptr);

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

        // Interface
        //============================================================
        // State query helpers for determining whether actions are
        // currently active, and what they do.

        // Get the name of the project.
        QString name() const;

        // Get the root directory of the project.
        QString location() const;

        // Can we currently call undo?
        bool can_undo() const;

        // Can we currently call redo?
        bool can_redo() const;

        // Get the name of the currently selected component. Empty if none is selected.
        QString selected_component_name() const;

        // Is a component selected? If no project is open, this is always false.
        bool is_component_selected() const;

        // Is the selected component buildable? If no component is open, this is always false.
        bool is_component_buildable() const;

        // Is the selected component installable? If no component is open, this is always false.
        bool is_component_installable() const;

    private:
        // Pimpl Data
        //============================================================
        class Data;
        std::unique_ptr<Data> m_data;

        Data& data()                { return *m_data; }
        Data const& cdata() const   { return *m_data; }
    };
}

#endif // PROJECT_WIDGET_H
