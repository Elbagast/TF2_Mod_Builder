#ifndef QTLIB_EDIT_WIDGET_TRAITS_HPP
#define QTLIB_EDIT_WIDGET_TRAITS_HPP

#include <memory>
#include <QWidget>
#include <QLineEdit>
#include <qtlib/string_conversion.hpp>

namespace qtlib
{
  namespace edit
  {
    //---------------------------------------------------------------------------
    // edit::widget_traits<T>
    //---------------------------------------------------------------------------
    // For a given type, what is it's edit widget? how do we get data into and
    // out of it? How do we connect to it?

    template <typename T>
    struct widget_traits
    {
      using value_type = T;
      using widget_type = QLineEdit;

      static std::unique_ptr<widget_type> make_empty_widget()
      {
        return std::make_unique<widget_type>(nullptr);
      }

      static std::unique_ptr<widget_type> make_widget(value_type const& a_value)
      {
        return std::make_unique<widget_type>(To_QString<value_type>()(a_value), nullptr);
      }

      static void set_widget_value(widget_type* ap_widget, value_type const& a_value)
      {
        return ap_widget->setText(a_value);
      }

      static value_type get_widget_value(widget_type* ap_widget)
      {
        return ap_widget->text();
      }
    };
  } // namespace display
} // namespace qtlib

#endif // QTLIB_EDIT_WIDGET_TRAITS_HPP
