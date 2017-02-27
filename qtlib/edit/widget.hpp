#ifndef QTLIB_EDIT_ABSTRACT_WIDGET_HPP
#define QTLIB_EDIT_ABSTRACT_WIDGET_HPP

#include <QWidget>

namespace qtlib
{
  namespace edit
  {
    namespace abstract
    {
      /*
      //---------------------------------------------------------------------------
      // edit::abstract::widget
      //---------------------------------------------------------------------------
      // This is the base class for editor widgets. These are the the things that
      // must be supplied. Inherit this class and compose the editor in it.
      class widget :
          public QWidget
      {
        Q_OBJECT
      public:
        explicit widget(QWidget* a_parent):
          QWidget(a_parent)
        {}
        virtual ~widget() = default;

        virtual void update() = 0;
      signals:
        void editing_finished();
      };

      //---------------------------------------------------------------------------
      // edit::abstract::widget<T>
      //---------------------------------------------------------------------------
      // The minimum interface for a widget for a given type.
      template <typename T>
      class widget_type :
          public widget
      {
      public:
        explicit widget(QWidget* a_parent):
          widget(a_parent)
        {}
        ~widget() override = default;

        virtual T get_value() const = 0;
      };
*/
    } // namespace abstract
  } // namespace edit
} // namespace qtlib

#endif // QTLIB_EDIT_ABSTRACT_WIDGET_HPP
