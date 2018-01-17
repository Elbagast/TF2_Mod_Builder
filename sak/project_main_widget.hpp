#ifndef SAK_PROJECT_MAIN_WIDGET_HPP
#define SAK_PROJECT_MAIN_WIDGET_HPP

#ifndef SAK_PROJECT_MAIN_WIDGET_FWD_HPP
#include "project_main_widget_fwd.hpp"
#endif

#ifndef SAK_PROJECT_DATA_FWD_HPP
#include "project_data_fwd.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_QT_QWIDGET
#define INCLUDE_QT_QWIDGET
#include <QWidget>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Project_Main_Widget
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

  Tab Section:
  - A mixture of tabs that represent different componenent types.
  - Tabs are closed when the item is deleted or the tab is closed.

  Notes on the current implementation:
  - Outliner and tabs have display orders that are seperate.
  - Neither cares what the other order is.
  - Current design has the Project store things in the outliner order...
  - How would you change this so the Project holds them in any order (e.g. no order or ID order)
    and the outliner sorts into whatever order it wants as needed?
  - Doing this would simplify the Project signals to just use the handles rather than also their
    indexes.
  - Tabs already doesn't care...
  - Tabs caches the handles it needs...
  - Outliner should probably cache the handles and sort the cache instead.

  */
  class Project_Main_Widget :
          public QWidget
  {
    Q_OBJECT
  public:
    // Special 6
    //============================================================
    // Create a Project with the given filepath.
    explicit Project_Main_Widget(std::unique_ptr<Project_Data>&& a_project, QWidget* a_parent = nullptr);
    ~Project_Main_Widget() override;

    Project_Main_Widget(Project_Main_Widget const& a_other) = delete;
    Project_Main_Widget& operator=(Project_Main_Widget const& a_other) = delete;

    Project_Main_Widget(Project_Main_Widget && a_other);
    Project_Main_Widget& operator=(Project_Main_Widget && a_other);


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

    // Does the Project have unsaved changes?
    bool has_unsaved_edits() const;

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

  signals:
    void signal_unsaved_edits_change(bool a_state);
    void signal_undo_change();

  private:
    // Pimpl Data
    //============================================================
    class Implementation;
    std::unique_ptr<Implementation> m_data;

    Implementation& imp()                { return *m_data; }
    Implementation const& cimp() const   { return *m_data; }
  };
}

#endif // SAK_PROJECT_MAIN_WIDGET_HPP
