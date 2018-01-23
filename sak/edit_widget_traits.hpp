#ifndef SAK_EDIT_WIDGET_TRAITS_HPP
#define SAK_EDIT_WIDGET_TRAITS_HPP

#ifndef SAK_EDIT_WIDGET_TRAITS_FWD_HPP
#include "edit_widget_traits_fwd.hpp"
#endif

#include <memory>
#include <cassert>
#include <string>

#include <sak/abstract_member_edit_widget_fwd.hpp>

class QWidget;
class QString;

namespace sak
{
  //---------------------------------------------------------------------------
  // Edit_Widget_Traits<T>
  //---------------------------------------------------------------------------
  // For a given type, what is it's edit widget? how do we get data into and
  // out of it? How do we connect to it?
/*
  template <typename T>
  class Edit_Widget_Traits :
      public Abstract_Edit_Widget_Traits_Base<T>
  {
  public:
    static std::unique_ptr<QWidget> make_empty_widget()
    {
      assert(false);
      return std::make_unique<QWidget>(nullptr);
    }

    static std::unique_ptr<QWidget> make_widget(T const& a_value)
    {
      assert(false);
      return std::make_unique<QWidget>(nullptr);
    }

    static void set_widget_value(QWidget* a_widget, T const& a_value)
    {
      assert(false);
    }

    static T get_widget_value(QWidget* a_widget)
    {
      assert(false);
    }

    static void connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor, Editor_Function_Type a_signal)
    {
      assert(false);
    }
  };
*/
  //---------------------------------------------------------------------------
  // Edit_Widget_Traits<QString>
  //---------------------------------------------------------------------------
  // Specialisation for QString
  template <>
  class Edit_Widget_Traits<QString>
  {
  public:
    static std::unique_ptr<QWidget> make_empty_widget();
    static std::unique_ptr<QWidget> make_widget(QString const& a_value);
    static void set_widget_value(QWidget* a_widget, QString const& a_value);
    static QString get_widget_value(QWidget* a_widget);
    static void connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor);
  };

  //---------------------------------------------------------------------------
  // Edit_Widget_Traits<std::string>
  //---------------------------------------------------------------------------
  // Specialisation for std::string assumed as utf8
  template <>
  class Edit_Widget_Traits<std::string>
  {
  public:
    static std::unique_ptr<QWidget> make_empty_widget();
    static std::unique_ptr<QWidget> make_widget(std::string const& a_value);
    static void set_widget_value(QWidget* a_widget, std::string const& a_value);
    static std::string get_widget_value(QWidget* a_widget);
    static void connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor);
  };

  //---------------------------------------------------------------------------
  // Edit_Widget_Traits<bool>
  //---------------------------------------------------------------------------
  // Specialisation for bool
  template <>
  class Edit_Widget_Traits<bool>
  {
  public:
    static std::unique_ptr<QWidget> make_empty_widget();
    static std::unique_ptr<QWidget> make_widget(bool a_value);
    static void set_widget_value(QWidget* a_widget, bool a_value);
    static bool get_widget_value(QWidget* a_widget);
    static void connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor);
  };
}

#endif // SAK_EDIT_WIDGET_TRAITS_HPP
