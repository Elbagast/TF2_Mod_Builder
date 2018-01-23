#include "valve_attributes.hpp"

#include "abstract_member_edit_widget.hpp"

#include <cassert>

#include <QString>
#include <QLineEdit>
#include <QObject>
#include <QValidator>
#include <QCheckBox>

/*
//---------------------------------------------------------------------------
// Valve_Buildpath
//---------------------------------------------------------------------------
// Widget true type is a QLineEditor that has a QValidator set.


namespace sak
{
  namespace
  {
    enum class Category
    {
      Invalid,
      Valid,
      Seperator
    };

    Category char_category(QChar a_char)
    {
      // if not ascii
      if (a_char > QChar(127))
      {
        // it's invalid
        return Category::Invalid;
      }

      // if char is a digit, letter or underscore
      if (a_char.isDigit() || a_char.isLetter() || a_char == QChar(u8'_'))
      {
        // it's valid
        return Category::Seperator;
      }
      // if char is forward or backslash
      else if(a_char == QChar(u8'\\') || a_char == QChar(u8'/'))
      {
        // it's a seperator
        return Category::Seperator;
      }
      else
      {
        // everything else is invalid
        return Category::Invalid;
      }
    }



    //---------------------------------------------------------------------------
    // Valve_Buildpath_Validator
    //---------------------------------------------------------------------------
    class Valve_Buildpath_Validator :
        public QValidator
    {
    private:
      // Special 6
      //============================================================
      Valve_Buildpath_Validator() = default;
    public:
      ~Valve_Buildpath_Validator() override;

      // QValidator overrides
      //============================================================
      //void fixup(QString& a_input) const override final;

      QValidator::State validate(QString& a_input, int& a_cursor_position) const override final
      {
        // Format [word]{Nx[directory seperator][word]} where N can be 0
        // word = combination of a...z,A...Z,_ chars
        // directory seperator = / or \\
        // If the last char is a seperator then the result is intermediate.

        // It can be empty.
        if (a_input.isEmpty())
        {
          return QValidator::Acceptable;
        }
        // Initialise a last category marker.
        Category l_last_category{Category::Seperator};

        for (auto l_iter = a_input.cbegin(), l_end = a_input.cend(); l_iter != l_end; ++l_iter)
        {
          auto l_this_category = char_category(*l_iter);

          // If the char is invalid the whole thing is invalid.
          if (l_this_category == Category::Invalid)
          {
            return QValidator::Invalid;
          }

          // if the last category is seperator then this one must be valid for the string to be valid
          if (l_last_category == Category::Seperator && l_this_category != Category::Valid)
          {
            return QValidator::Invalid;
          }

          // Since an invalid char will have already been detected, and valid can be followed by
          // valid or seperator, no more processing is needed.

          // Updated the last category and continue.
          l_last_category = l_this_category;
        }

        // if the last character was a seperator then we are intermediate
        if (l_last_category == Category::Seperator)
        {
          return QValidator::Intermediate;
        }
        // otherwise everything validated
        else
        {
          return QValidator::Acceptable;
        }

      }

      static Valve_Buildpath_Validator* singleton()
      {
        // Since the validator has no individual state we use a static one.
        static Valve_Buildpath_Validator s_validator{};

        return std::addressof(s_validator);
      }
    };

    std::unique_ptr<QLineEdit> valve_buildpath_make_true_empty_widget()
    {
      // Build a true-type widget so we can manipulate it.
      auto l_widget = std::make_unique<QLineEdit>(nullptr);

      // Install it.
      l_widget->setValidator(Valve_Buildpath_Validator::singleton());

      // Return the setup widget.
      return std::move(l_widget);
    }

    void valve_buildpath_set_true_widget_value(QLineEdit* a_widget, Valve_Buildpath::Value_Type const& a_value)
    {
      // This widget better have a validator, and it better be the right one...
      assert(a_widget->validator() == Valve_Buildpath_Validator::singleton());
      // Value should already be validated.
      assert(a_widget->validator()->validate(a_value, 0) == QValidator::Acceptable);

      // Set the value.
      l_widget->setText(a_value);

      // Value should set properly.
      assert(l_widget->text() == a_value);
    }
  }
}

std::unique_ptr<QWidget> sak::Valve_Buildpath::make_empty_widget()
{
  // Make an empty widget and repackage it.
  return std::unique_ptr<QWidget>(valve_buildpath_make_true_empty_widget.release());
}

std::unique_ptr<QWidget> sak::Valve_Buildpath::make_widget(Value_Type const& a_value)
{
  // Make an empty true widget.
  auto l_widget = valve_buildpath_make_true_empty_widget();

  // Set the value.
  valve_buildpath_set_true_widget_value(l_widget.get(), a_value);

  // Repackage the widget.
  return std::unique_ptr<QWidget>(l_widget.release());
}

void sak::Valve_Buildpath::set_widget_value(QWidget* a_widget, Value_Type const& a_value)
{
  // Cast and set the value.
  valve_buildpath_set_true_widget_value(static_cast<QLineEdit*>(a_widget), a_value);
}

typename sak::Valve_Buildpath::Value_Type sak::Valve_Buildpath::get_widget_value(QWidget* a_widget)
{
  // Cast and access the value.
  return static_cast<QLineEdit*>(a_widget)->text();
}

void sak::Valve_Buildpath::connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor)
{
  QObject::connect(static_cast<QLineEdit*>(a_widget), &QLineEdit::editingFinished, a_editor, &Abstract_Member_Edit_Widget::editing_finished);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Valve_Bool
//---------------------------------------------------------------------------
// Widget true type is a QCheckbox


std::unique_ptr<QWidget> sak::Valve_Buildpath::make_empty_widget()
{
  // Make an empty widget and repackage it.
  return std::unique_ptr<QWidget>(std::make_unique<QCheckBox>(nullptr).release());
}

std::unique_ptr<QWidget> sak::Valve_Buildpath::make_widget(Value_Type const& a_value)
{
  // Make an empty true widget.
  auto l_widget = make_empty_widget();

  // Set the value.
  set_widget_value(l_widget.get(), a_value);

  // Repackage the widget.
  return std::move(l_widget);
}

void sak::Valve_Buildpath::set_widget_value(QWidget* a_widget, Value_Type const& a_value)
{
  // Cast and set the value.
  static_cast<QCheckBox*>(a_widget)->setChecked(a_value);
}

typename sak::Valve_Buildpath::Value_Type sak::Valve_Buildpath::get_widget_value(QWidget* a_widget)
{
  // Cast and access the value.
  return static_cast<QCheckBox*>(a_widget)->isChecked();
}

void sak::Valve_Buildpath::connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor)
{
  QObject::connect(static_cast<QCheckBox*>(a_widget), &QCheckBox::stateChanged, [a_editor](){ a_editor->editing_finished(); });
}
*/
