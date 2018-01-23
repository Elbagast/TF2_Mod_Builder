#ifndef SAK_SHARED_ATTRIBUTES_HPP
#define SAK_SHARED_ATTRIBUTES_HPP

#ifndef SAK_ABSTRACT_MEMBER_EDIT_WIDGET_FWD_HPP
#include "abstract_member_edit_widget_fwd.hpp"
#endif

#ifndef FLAMINGO_LITYPE_STRING_HPP
#include <flamingo/litype/string.hpp>
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

class QString;
class QWidget;

namespace sak
{
  //---------------------------------------------------------------------------
  // Text_Line
  //---------------------------------------------------------------------------
  // A short string of unicode text containing any characters except control
  // characters. Max length is 256 chars.

  class Text_Line
  {
  public:
    using Typestring = FLAMINGO_LITYPE_STRING(u8"Text_Line");
    using Value_Type = QString;

    static std::unique_ptr<QWidget> make_empty_widget();
    static std::unique_ptr<QWidget> make_widget(Value_Type const& a_value);
    static void set_widget_value(QWidget* a_widget, Value_Type const& a_value);
    static Value_Type get_widget_value(QWidget* a_widget);
    static void connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor);
  };

  //---------------------------------------------------------------------------
  // Text_Long
  //---------------------------------------------------------------------------
  // A string of unicode text containing any characters that would make human
  // readable text. Max length is 1024 chars.

  class Text_Long
  {
  public:
    using Typestring = FLAMINGO_LITYPE_STRING(u8"Text_Long");
    using Value_Type = QString;

    static std::unique_ptr<QWidget> make_empty_widget();
    static std::unique_ptr<QWidget> make_widget(Value_Type const& a_value);
    static void set_widget_value(QWidget* a_widget, Value_Type const& a_value);
    static Value_Type get_widget_value(QWidget* a_widget);
    static void connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor);
  };
}

#endif // SAK_SHARED_ATTRIBUTES_HPP
