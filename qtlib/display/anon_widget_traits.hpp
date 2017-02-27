#ifndef QTLIB_DISPLAY_ANON_WIDGET_TRAITS_HPP
#define QTLIB_DISPLAY_ANON_WIDGET_TRAITS_HPP

#include "widget_traits.hpp"

namespace qtlib
{
  namespace display
  {
    template <typename T>
    struct anon_widget_traits
    {
    private:
      using true_traits_type = widget_traits<T>;
      using true_widget_type = typename true_traits_type::widget_type;
    public:
      using value_type = T;
      using widget_type = QWidget;

      static std::unique_ptr<widget_type> make_empty_widget()
      {
        return std::unique_ptr<widget_type>(static_cast<widget_type*>(true_traits_type::make_empty_display_widget().release()));
      }

      static std::unique_ptr<widget_type> make_widget(value_type const& a_value)
      {
        return std::unique_ptr<widget_type>(static_cast<widget_type*>(true_traits_type::make_display_widget(a_value).release()));
      }

      static void set_widget_value(widget_type* ap_widget, value_type const& a_value)
      {
        true_traits_type::set_display_widget_value(static_cast<true_widget_type*>(ap_widget),a_value);
      }
    };
  } // namespace display
} // namespace qtlib

#endif // QTLIB_DISPLAY_ANON_WIDGET_TRAITS_HPP
