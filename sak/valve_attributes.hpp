#ifndef SAK_VALVE_ATTRIBUTES_HPP
#define SAK_VALVE_ATTRIBUTES_HPP

#ifndef SAK_VALVE_ATTRIBUTES_FWD_HPP
#include "valve_attributes_fwd.hpp"
#endif

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
  // Valve_Buildpath
  //---------------------------------------------------------------------------
  // A valid Valve filename (without extension) in a valid Valve directory.

  class Valve_Buildpath
  {
  public:
    using Typestring = FLAMINGO_LITYPE_STRING(u8"Valve_Buildpath");
    using Value_Type = QString;

    static std::unique_ptr<QWidget> make_widget();
    static void set_widget_value(QWidget* a_widget, Value_Type const& a_value);
    static Value_Type get_widget_value(QWidget* a_widget);
    static void connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor);
    static QString tooltip();
  };

  //---------------------------------------------------------------------------
  // Valve_Bool
  //---------------------------------------------------------------------------
  // A valid Valve filename (without extension) in a valid Valve directory.

  class Valve_Bool
  {
  public:
    using Typestring = FLAMINGO_LITYPE_STRING(u8"Valve_Bool");
    using Value_Type = bool;

    static std::unique_ptr<QWidget> make_widget();
    static void set_widget_value(QWidget* a_widget, Value_Type const& a_value);
    static Value_Type get_widget_value(QWidget* a_widget);
    static void connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor);
    static QString tooltip();
  };

}


#endif // SAK_VALVE_ATTRIBUTES_HPP
