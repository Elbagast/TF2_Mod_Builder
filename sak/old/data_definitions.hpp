#ifndef SAK_DATA_DEFINITIONS_HPP
#define SAK_DATA_DEFINITIONS_HPP

#ifndef SAK_DATA_DEFINITIONS_FWD_HPP
#include "data_definitions_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_MEMBER_EDIT_WIDGET_FWD_HPP
#include "abstract_member_edit_widget_fwd.hpp"
#endif

//#ifndef SAK_ABSTRACT_PROJECT_INTERFACE_FWD_HPP
//#include "abstract_project_interface_fwd.hpp"
//#endif

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
  // Example_Data_Definition
  //---------------------------------------------------------------------------
  // This is everything you must provide in a data definition class.
  class Example_Data_Definition
  {
  public:
    using Typestring_Type = FLAMINGO_LITYPE_STRING(u8"Example_Data");
    using Value_Type = int;

    //static std::unique_ptr<QWidget> make_widget(Abstract_Project_Interface* a_project); // hmmmmmmmm
    static std::unique_ptr<QWidget> make_widget();
    static void set_widget_value(QWidget* a_widget, Value_Type const& a_value);
    static Value_Type get_widget_value(QWidget* a_widget);
    static void connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor);
    static QString tooltip();

    // Does not include stream interface because we defer that to whatever
    // handles each type for that.
  };

  //---------------------------------------------------------------------------
  // Text_Name_Definition
  //---------------------------------------------------------------------------
  // A short string of unicode text containing any characters except control
  // characters. Max length is 256 chars. Must contain something.
  class Text_Name_Definition
  {
  public:
    using Typestring_Type = FLAMINGO_LITYPE_STRING(u8"Text_Name");
    using Value_Type = QString;

    static std::unique_ptr<QWidget> make_widget();
    static void set_widget_value(QWidget* a_widget, Value_Type const& a_value);
    static Value_Type get_widget_value(QWidget* a_widget);
    static void connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor);
    static QString tooltip();
  };

  //---------------------------------------------------------------------------
  // Text_Line_Definition
  //---------------------------------------------------------------------------
  // A short string of unicode text containing any characters except control
  // characters. Max length is 256 chars.

  class Text_Line_Definition
  {
  public:
    using Typestring_Type = FLAMINGO_LITYPE_STRING(u8"Text_Line");
    using Value_Type = QString;

    static std::unique_ptr<QWidget> make_widget();
    static void set_widget_value(QWidget* a_widget, Value_Type const& a_value);
    static Value_Type get_widget_value(QWidget* a_widget);
    static void connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor);
    static QString tooltip();
  };
} // namespace sak


#endif // SAK_DATA_DEFINITIONS_HPP
