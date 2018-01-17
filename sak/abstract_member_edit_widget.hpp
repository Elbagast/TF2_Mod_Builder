#ifndef SAK_ABSTRACT_MEMBER_EDIT_WIDGET_HPP
#define SAK_ABSTRACT_MEMBER_EDIT_WIDGET_HPP

#ifndef SAK_ABSTRACT_MEMBER_EDIT_WIDGET_FWD_HPP
#include "abstract_member_edit_widget_fwd.hpp"
#endif

#ifndef INCLUDE_QT_QWIDGET
#define INCLUDE_QT_QWIDGET
#include <QWidget>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Member_Edit_Widget
  //---------------------------------------------------------------------------
  // This is the base class for member value editor widgets. These are the
  // things that must be supplied. Inherit this class and compose the true
  // editor in it. Also for a signal to be generated it must not be part of a template.

  class Abstract_Member_Edit_Widget :
      public QWidget
  {
    Q_OBJECT
  public:
    // Special 6
    //============================================================
    explicit Abstract_Member_Edit_Widget(QWidget* a_parent = nullptr);
    ~Abstract_Member_Edit_Widget() override;

    virtual void update() = 0;
  public slots:
    virtual void editing_finished() = 0;
  };
}


#endif // SAK_ABSTRACT_MEMBER_EDIT_WIDGET_HPP
