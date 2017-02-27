#ifndef QTLIB_DISPLAY_WIDGET_TRAITS_HPP
#define QTLIB_DISPLAY_WIDGET_TRAITS_HPP

#include <memory>
#include <QWidget>
#include <QLabel>
#include <qtlib/string_conversion.hpp>

namespace qtlib
{
  namespace display
  {
    // Template providing functions related to display widgets.
    // Default implementation assumes the intended type is a QLabel and the templated
    // type can be converted to a QString using To_QString.
    template <typename T>
    struct widget_traits
    {
      using value_type = T;
      using widget_type = QLabel;

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
        return ap_widget->setText(To_QString<value_type>()(a_value));
      }
    };
  } // namespace display
} // namespace qtlib

#endif // QTLIB_DISPLAY_WIDGET_TRAITS_HPP
