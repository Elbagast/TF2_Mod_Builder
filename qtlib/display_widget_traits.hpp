#ifndef QTLIB_DISPLAY_WIDGET_TRAITS_HPP
#define QTLIB_DISPLAY_WIDGET_TRAITS_HPP

#include <memory>
#include <QWidget>
#include <QLabel>
#include "string_conversion.hpp"

namespace qtlib
{
  // Template providing functions related to display widgets.
  // Default implementation assumes the intended type is a QLabel and the templated
  // type can be converted to a QString using To_QString.
  template <typename T>
  struct Display_Widget_Traits
  {
    using value_type = T;
    using widget_type = QLabel;

    static std::unique_ptr<widget_type> make_empty_display_widget()
    {
      return std::make_unique<widget_type>(nullptr);
    }

    static std::unique_ptr<widget_type> make_display_widget(value_type const& a_value)
    {
      return std::make_unique<widget_type>(To_QString<value_type>()(a_value), nullptr);
    }

    static void set_display_widget_value(widget_type* ap_widget, value_type const& a_value)
    {
      return ap_widget->setText(To_QString<value_type>()(a_value));
    }
  };

  template <typename T>
  struct Anonymous_Display_Widget_Traits
  {
  private:
      using true_traits_type = Display_Widget_Traits<T>;
      using true_widget_type = typename true_traits_type::widget_type;
  public:
    using value_type = T;
    using widget_type = QWidget;

    static std::unique_ptr<widget_type> make_empty_display_widget()
    {
      return std::unique_ptr<widget_type>(static_cast<widget_type*>(true_traits_type::make_empty_display_widget().release()));
    }

    static std::unique_ptr<widget_type> make_display_widget(value_type const& a_value)
    {
      return std::unique_ptr<widget_type>(static_cast<widget_type*>(true_traits_type::make_display_widget(a_value).release()));
    }

    static void set_display_widget_value(widget_type* ap_widget, value_type const& a_value)
    {
      true_traits_type::set_display_widget_value(static_cast<true_widget_type*>(ap_widget),a_value);
    }
  };
} // namespace qtlib

#endif // QTLIB_DISPLAY_WIDGET_TRAITS_HPP
