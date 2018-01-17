#ifndef SAK_EDIT_WIDGET_TRAITS_HPP
#define SAK_EDIT_WIDGET_TRAITS_HPP

#include <memory>
#include <cassert>
#include <string>

#include <sak/abstract_member_edit_widget.hpp>


class QWidget;
class QString;

namespace sak
{
  namespace edit
  {
    namespace abstract
    {
      template <typename T>
      struct widget_traits_typedefs
      {
        using value_type = T;
        using editor_type = sak::Abstract_Member_Edit_Widget;
        using editor_function_type = decltype(&sak::Abstract_Member_Edit_Widget::editing_finished);//void (sak::shared::abstract::member_edit_widget::*)();
      };
    }

    //---------------------------------------------------------------------------
    // edit::widget_traits<T>
    //---------------------------------------------------------------------------
    // For a given type, what is it's edit widget? how do we get data into and
    // out of it? How do we connect to it?

    template <typename T>
    struct widget_traits :
        public abstract::widget_traits_typedefs<T>
    {
      static std::unique_ptr<QWidget> make_empty_widget()
      {
        assert(false);
        return std::make_unique<QWidget>(nullptr);
      }

      static std::unique_ptr<QWidget> make_widget(value_type const& a_value)
      {
        assert(false);
        return std::make_unique<QWidget>(nullptr);
      }

      static void set_widget_value(QWidget* a_widget, value_type const& a_value)
      {
        assert(false);
      }

      static value_type get_widget_value(QWidget* a_widget)
      {
        assert(false);
      }

      static void connect_to(QWidget* a_widget, editor_type* a_editor, editor_function_type a_signal)
      {
        assert(false);
      }
    };

    //---------------------------------------------------------------------------
    // edit::widget_traits<QString>
    //---------------------------------------------------------------------------
    // Specialisation for QString
    template <>
    struct widget_traits<QString> :
        public abstract::widget_traits_typedefs<QString>
    {
      static std::unique_ptr<QWidget> make_empty_widget();
      static std::unique_ptr<QWidget> make_widget(value_type const& a_value);
      static void set_widget_value(QWidget* a_widget, value_type const& a_value);
      static value_type get_widget_value(QWidget* a_widget);
      static void connect_to(QWidget* a_widget, editor_type* a_editor, editor_function_type a_func);
    };

    //---------------------------------------------------------------------------
    // edit::widget_traits<std::string>
    //---------------------------------------------------------------------------
    // Specialisation for std::string assumed as utf8
    template <>
    struct widget_traits<std::string> :
        public abstract::widget_traits_typedefs<std::string>
    {
      static std::unique_ptr<QWidget> make_empty_widget();
      static std::unique_ptr<QWidget> make_widget(value_type const& a_value);
      static void set_widget_value(QWidget* a_widget, value_type const& a_value);
      static value_type get_widget_value(QWidget* a_widget);
      static void connect_to(QWidget* a_widget, editor_type* a_editor, editor_function_type a_func);
    };

    //---------------------------------------------------------------------------
    // edit::widget_traits<bool>
    //---------------------------------------------------------------------------
    // Specialisation for bool
    template <>
    struct widget_traits<bool> :
        public abstract::widget_traits_typedefs<bool>
    {
      static std::unique_ptr<QWidget> make_empty_widget();
      static std::unique_ptr<QWidget> make_widget(value_type const& a_value);
      static void set_widget_value(QWidget* a_widget, value_type const& a_value);
      static value_type get_widget_value(QWidget* a_widget);
      static void connect_to(QWidget* a_widget, editor_type* a_editor, editor_function_type a_func);
    };
  }
}

#endif // SAK_EDIT_WIDGET_TRAITS_HPP
