#ifndef SAK_PROJECT_OUTLINER_WIDGET_HPP
#define SAK_PROJECT_OUTLINER_WIDGET_HPP

#ifndef SAK_PROJECT_OUTLINER_WIDGET_FWD_HPP
#include "project_outliner_widget_fwd.hpp"
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
  // Project_Outliner_Widget
  //---------------------------------------------------------------------------
  class Project_Outliner_Widget :
          public QWidget
  {
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
    explicit Project_Outliner_Widget(Project* a_project, QWidget* a_parent = nullptr);
    ~Project_Outliner_Widget() override;

    Project_Outliner_Widget(Project_Outliner_Widget const& a_other) = delete;
    Project_Outliner_Widget& operator=(Project_Outliner_Widget const& a_other) = delete;

    Project_Outliner_Widget(Project_Outliner_Widget && a_other) = delete;
    Project_Outliner_Widget& operator=(Project_Outliner_Widget && a_other) = delete;

  };
}


#endif // SAK_PROJECT_OUTLINER_WIDGET_HPP
