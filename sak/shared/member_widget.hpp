#ifndef SAK_SHARED_ABSTRACT_MEMBER_WIDGET_HPP
#define SAK_SHARED_ABSTRACT_MEMBER_WIDGET_HPP

#include "fwd/member_widget.hpp"
#include <QWidget>

namespace sak
{
  namespace shared
  {
    namespace abstract
    {
      //---------------------------------------------------------------------------
      // shared::abstract::member_edit_widget
      //---------------------------------------------------------------------------
      // This is the base class for member value editor widgets. These are the
      // things that must be supplied. Inherit this class and compose the true
      // editor in it. Also for a signal to be generated it must not be part of a template.

      class member_edit_widget :
          public QWidget
      {
        Q_OBJECT
      public:
        // Special 6
        //============================================================
        explicit member_edit_widget(QWidget* a_parent = nullptr);
        ~member_edit_widget() override;

        virtual void update() = 0;
      public slots:
        virtual void editing_finished() = 0;
      };
    }
  }
}

#endif // SAK_SHARED_ABSTRACT_MEMBER_WIDGET_HPP
