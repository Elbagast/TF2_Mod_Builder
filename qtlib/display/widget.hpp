#ifndef QTLIB_DISPLAY_ABSTRACT_WIDGET_HPP
#define QTLIB_DISPLAY_ABSTRACT_WIDGET_HPP

#include <QWidget>

namespace qtlib
{
  namespace display
  {
    namespace abstract
    {
      //---------------------------------------------------------------------------
      // display::abstract::widget
      //---------------------------------------------------------------------------
      // This is the base class for display widgets. These are the the things that
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
      };

      //---------------------------------------------------------------------------
      // display::abstract::widget<T>
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
        virtual void set_value(T const& a_value) const = 0;
      };

    } // namespace abstract
  } // namespace edit
} // namespace qtlib
#endif // QTLIB_DISPLAY_ABSTRACT_WIDGET_HPP
