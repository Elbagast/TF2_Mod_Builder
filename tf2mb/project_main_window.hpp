#ifndef SAK_PROJECT_MAIN_WINDOW_HPP
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

  private:
    // Pimpl Data
    //============================================================
    class Implementation;
    std::unique_ptr<Implementation> m_data;

    Implementation& imp()                { return *m_data; }
    Implementation const& cimp() const   { return *m_data; }

  public:
    // Special 6
    //============================================================
    explicit Project_Main_Window(QWidget* a_parent = nullptr);
    ~Project_Main_Window() override;

    Project_Main_Window(Project_Main_Window const& a_other) = delete;
    Project_Main_Window& operator=(Project_Main_Window const& a_other) = delete;

    Project_Main_Window(Project_Main_Window && a_other) = delete;
    Project_Main_Window& operator=(Project_Main_Window && a_other) = delete;

    // Virtuals
    //============================================================
    // Needed so that we can ask to save when we use the x button in the corner to close.
    void closeEvent(QCloseEvent* a_event) override;
  };
}

#endif // SAK_PROJECT_MAIN_WINDOW_HPP
