#ifndef PROJECT_EDITOR_WIDGET_HPP
#define PROJECT_EDITOR_WIDGET_HPP

#ifndef SAK_PROJECT_EDITOR_WIDGET_FWD_HPP
#include "project_editor_widget_fwd.hpp"
#endif

#ifndef SAK_PROJECT_INTERFACE_FWD_HPP
#include "project_interface_fwd.hpp"
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
  // Project_Editor_Widget
  //---------------------------------------------------------------------------
  class Project_Editor_Widget :
      public QWidget
  {
  public:
    // Special 6
    //============================================================
    explicit Project_Editor_Widget(Project_Interface* a_project, QWidget* a_parent = nullptr);
    ~Project_Editor_Widget() override;

    Project_Editor_Widget(Project_Editor_Widget const& a_other) = delete;
    Project_Editor_Widget& operator=(Project_Editor_Widget const& a_other) = delete;

    Project_Editor_Widget(Project_Editor_Widget && a_other) = delete;
    Project_Editor_Widget& operator=(Project_Editor_Widget && a_other) = delete;

  private:
    // Pimpl Data
    //============================================================
    class Implementation;
    std::unique_ptr<Implementation> m_data;

    Implementation& imp()                { return *m_data; }
    Implementation const& cimp() const   { return *m_data; }
  };
}

#endif // PROJECT_EDITOR_WIDGET_HPP
