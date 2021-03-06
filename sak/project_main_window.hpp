﻿#ifndef SAK_PROJECT_MAIN_WINDOW_HPP
#define SAK_PROJECT_MAIN_WINDOW_HPP

#ifndef SAK_PROJECT_MAIN_WINDOW_FWD_HPP
#include "project_main_window_fwd.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_QT_QMAINWINDOW
#define INCLUDE_QT_QMAINWINDOW
#include <QMainWindow>
#endif


namespace sak
{
  //---------------------------------------------------------------------------
  // Project_Main_Window
  //---------------------------------------------------------------------------
  // Main Window class for an open Project.
  /*
   State Tracked:
   - project open?
        - yes:
          - enable actions
              - file::save
              - file::close
          - enable menus
              - edit
              - Component
              - build
              - install
          - component selected?
              - yes
                  - enable actions, displaying component name
                      - build::build component
                      - build::rebuild component
                      - build::clean component
                      - install::install component
                      - install::uninstall component
              - no
                  - disable actions, displaying no component name
                      - build::build component
                      - build::rebuild component
                      - build::clean component
                      - install::install component
                      - install::uninstall component
          - undo properties?
              - can undo?
                  - yes
                      - enable action edit::undo
                  - no
                      - disable action edit::undo
              - can redo?
                  - yes
                      - enable action edit::redo
                  - no
                      - disable action edit::redo
              - history
          - unsaved data?
              - yes
                  - prompt to save on close or exit
                  - display marker
              - no
      - no:
          - disable actions
              - file::save
              - file::close
          - disable menus
              - edit
              - create
              - build
              - install
  */
  class Project_Main_Window :
      public QMainWindow
  {
    Q_OBJECT
  public:

    // Special 6
    //============================================================
    explicit Project_Main_Window(QWidget* a_parent = nullptr);
    ~Project_Main_Window() override;

    Project_Main_Window(Project_Main_Window const& a_other) = delete;
    Project_Main_Window& operator=(Project_Main_Window const& a_other) = delete;

    Project_Main_Window(Project_Main_Window && a_other) = delete;
    Project_Main_Window& operator=(Project_Main_Window && a_other) = delete;

  private:
    // Menu Action Slots
    //============================================================
    // The menu actions are connected to these corresponding slots.
    // These are the things the user can do though the main window.

    // Menu Bar -> File
    //============================================================
    // Make a new empty Project based on what the user supplies via a dialog.
    // If the user cancels out, nothing happens.
    bool new_project();

    // Opens a project and loads the data found based on what the user supplies
    // via a dialog. If the user cancels out, nothing happens.
    bool open_project();

    // Save the Project data.
    void save_project();

    // Ask to save then close the Project if that is not cancelled.
    bool close_project();

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


    // Internal Interface
    //============================================================
    // State query helpers for determining whether actions are
    // currently active, and what they do.

    // Get the name of the current project. Empty if not open.
    QString project_name() const;

    // Is a project currently open?
    bool is_project_open() const;

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

    // Spawn a message box asking if the user wants to save the current project,
    // act on it and return true if the action was never cancelled.
    bool ask_to_save();

    // Virtuals
    //============================================================
    // Needed so that we can ask to save when we use the x button in the corner to close.
    void closeEvent(QCloseEvent *event) override;

    // Notifications
    //============================================================
    // Tell parts of the window that these states have changed so they should update.

    // Change anything that needs to change if a Project is opended or closed.
    void notify_project_changes();

    // Change anything that needs to change if undo changes are made.
    void notify_undo_changes();

    // Change anything that needs to change if the selected componenent changes.
    void notify_component_changes();

    void update_window_title();

    // Pimpl Data
    //============================================================
    class Implementation;
    std::unique_ptr<Implementation> m_data;

    Implementation& imp()                { return *m_data; }
    Implementation const& cimp() const   { return *m_data; }
  };
}

#endif // SAK_PROJECT_MAIN_WINDOW_HPP
