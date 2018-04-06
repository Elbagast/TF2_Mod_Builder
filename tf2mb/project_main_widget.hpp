#ifndef SAK_PROJECT_MAIN_WIDGET_HPP
#define SAK_PROJECT_MAIN_WIDGET_HPP

#ifndef SAK_PROJECT_MAIN_WIDGET_FWD_HPP
#include "project_main_widget_fwd.hpp"
#endif

#ifndef SAK_PROJECT_FWD_HPP
#include "project_fwd.hpp"
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
    // Create a Project with the given filepath.
    explicit Project_Main_Widget(Project* a_project, QWidget* a_parent = nullptr);
    ~Project_Main_Widget() override;

    Project_Main_Widget(Project_Main_Widget const& a_other) = delete;
    Project_Main_Widget& operator=(Project_Main_Widget const& a_other) = delete;

    Project_Main_Widget(Project_Main_Widget && a_other);
    Project_Main_Widget& operator=(Project_Main_Widget && a_other);
  };
}

#endif // SAK_PROJECT_MAIN_WIDGET_HPP
