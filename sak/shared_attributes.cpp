#include "shared_attributes.hpp"

#include "abstract_member_edit_widget.hpp"

#include <cassert>

#include <QString>
#include <QLineEdit>
#include <QObject>
#include <QValidator>
#include <QCheckBox>
#include <QTextEdit>


//---------------------------------------------------------------------------
// Text_Line
//---------------------------------------------------------------------------
// A short string of unicode text containing any characters except control
// characters. Max length is 256 chars.

namespace sak
{
  namespace
  {
    enum class Category
    {
      Invalid,
      Low_Surrogate,
      High_Surrogate,
      Valid
    };

    Category text_line_char_category(QChar a_char)
    {
      if (a_char.isPrint())
      {
        return Category::Valid;
      }
      else if (a_char.isLowSurrogate())
      {
        return Category::Low_Surrogate;
      }
      else if (a_char.isHighSurrogate())
      {
        return Category::High_Surrogate;
      }
      else
      {
        return Category::Invalid;
      }
    }



    //---------------------------------------------------------------------------
    // Text_Line_Validator
    //---------------------------------------------------------------------------
    class Text_Line_Validator :
        public QValidator
    {
    private:
      // Special 6
      //============================================================
      Text_Line_Validator() = default;
    public:
      ~Text_Line_Validator() override = default;

      // QValidator overrides
      //============================================================
      //void fixup(QString& a_input) const override final;

      QValidator::State validate(QString& a_input, int& a_cursor_position) const override final
      {
        // Format [word]{Nx[directory seperator][word]} where N can be 0
        // word = combination of a...z,A...Z,_ chars
        // directory seperator = / or \\
        // If the last char is a seperator then the result is intermediate.

        // A name cannot be empty
        if (a_input.isEmpty())
        {
          return QValidator::Invalid;
        }
        // Initialise a last category marker.
        Category l_last_category{Category::Valid};

        for (auto l_iter = a_input.cbegin(), l_end = a_input.cend(); l_iter != l_end; ++l_iter)
        {
          // Determine the current category
          auto l_this_category = text_line_char_category(*l_iter);

          // If the char is invalid the whole thing is invalid.
          if (l_this_category == Category::Invalid)
          {
            return QValidator::Invalid;
          }

          // High surrogate must follow a lower surrogate
          if (l_last_category == Category::Low_Surrogate && l_this_category != Category::High_Surrogate)
          {
            return QValidator::Invalid;
          }

          // Since an invalid char will have already been detected, and Valid can be followed by
          // Valid or High_Surrogate, no more processing is needed.

          // Updated the last category and continue.
          l_last_category = l_this_category;
        }

        // if the last character was a Low_Surrogate then we are intermediate
        if (l_last_category == Category::Low_Surrogate)
        {
          return QValidator::Intermediate;
        }
        // otherwise everything validated
        else
        {
          return QValidator::Acceptable;
        }

      }

      static Text_Line_Validator* singleton()
      {
        // Since the validator has no individual state we use a static one.
        static Text_Line_Validator s_validator{};

        return std::addressof(s_validator);
      }
    };

    std::unique_ptr<QLineEdit> text_line_make_true_empty_widget()
    {
      // Build a true-type widget so we can manipulate it.
      auto l_widget = std::make_unique<QLineEdit>(nullptr);

      // Setup
      l_widget->setMaxLength(256);

      // Install it.
      l_widget->setValidator(Text_Line_Validator::singleton());

      // Return the setup widget.
      return std::move(l_widget);
    }

    void text_line_set_true_widget_value(QLineEdit* a_widget, Text_Line::Value_Type const& a_value)
    {
      // This widget better have a validator, and it better be the right one...
      assert(a_widget->validator() == Text_Line_Validator::singleton());
      // Value should already be validated.
      //assert(a_widget->validator()->validate(a_value, 0) == QValidator::Acceptable);

      // Set the value.
      a_widget->setText(a_value);

      // Value should set properly.
      assert(a_widget->text() == a_value);
    }
  }
}

std::unique_ptr<QWidget> sak::Text_Line::make_empty_widget()
{
  // Make an empty widget and repackage it.
  return std::unique_ptr<QWidget>(text_line_make_true_empty_widget().release());
}

std::unique_ptr<QWidget> sak::Text_Line::make_widget(Value_Type const& a_value)
{
  // Make an empty true widget.
  auto l_widget = text_line_make_true_empty_widget();

  // Set the value.
  text_line_set_true_widget_value(l_widget.get(), a_value);

  // Repackage the widget.
  return std::unique_ptr<QWidget>(l_widget.release());
}

void sak::Text_Line::set_widget_value(QWidget* a_widget, Value_Type const& a_value)
{
  // Cast and set the value.
  text_line_set_true_widget_value(static_cast<QLineEdit*>(a_widget), a_value);
}

typename sak::Text_Line::Value_Type sak::Text_Line::get_widget_value(QWidget* a_widget)
{
  // Cast and access the value.
  return static_cast<QLineEdit*>(a_widget)->text();
}

void sak::Text_Line::connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor)
{
  QObject::connect(static_cast<QLineEdit*>(a_widget), &QLineEdit::editingFinished, a_editor, &Abstract_Member_Edit_Widget::editing_finished);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Text_Long
//---------------------------------------------------------------------------
// A string of unicode text containing any characters that would make human
// readable text. Max length is 1024 chars.


namespace sak
{
  namespace
  {
    /*
    enum class Category
    {
      Invalid,
      Low_Surrogate,
      High_Surrogate,
      Valid
    };*/

    Category text_long_char_category(QChar a_char)
    {
      if (a_char.isPrint() || a_char.isSpace())
      {
        return Category::Valid;
      }
      else if (a_char.isLowSurrogate())
      {
        return Category::Low_Surrogate;
      }
      else if (a_char.isHighSurrogate())
      {
        return Category::High_Surrogate;
      }
      else
      {
        return Category::Invalid;
      }
    }



    //---------------------------------------------------------------------------
    // Text_Long_Validator
    //---------------------------------------------------------------------------
    class Text_Long_Validator :
        public QValidator
    {
    private:
      // Special 6
      //============================================================
      Text_Long_Validator() = default;
    public:
      ~Text_Long_Validator() override = default;

      // QValidator overrides
      //============================================================
      //void fixup(QString& a_input) const override final;

      QValidator::State validate(QString& a_input, int& a_cursor_position) const override final
      {
        // Format [word]{Nx[directory seperator][word]} where N can be 0
        // word = combination of a...z,A...Z,_ chars
        // directory seperator = / or \\
        // If the last char is a seperator then the result is intermediate.

        // A name cannot be empty
        if (a_input.isEmpty())
        {
          return QValidator::Invalid;
        }
        // Initialise a last category marker.
        Category l_last_category{Category::Valid};

        for (auto l_iter = a_input.cbegin(), l_end = a_input.cend(); l_iter != l_end; ++l_iter)
        {
          // Determine the current category
          auto l_this_category = text_line_char_category(*l_iter);

          // If the char is invalid the whole thing is invalid.
          if (l_this_category == Category::Invalid)
          {
            return QValidator::Invalid;
          }

          // High surrogate must follow a lower surrogate
          if (l_last_category == Category::Low_Surrogate && l_this_category != Category::High_Surrogate)
          {
            return QValidator::Invalid;
          }

          // Since an invalid char will have already been detected, and Valid can be followed by
          // Valid or High_Surrogate, no more processing is needed.

          // Updated the last category and continue.
          l_last_category = l_this_category;
        }

        // if the last character was a Low_Surrogate then we are intermediate
        if (l_last_category == Category::Low_Surrogate)
        {
          return QValidator::Intermediate;
        }
        // otherwise everything validated
        else
        {
          return QValidator::Acceptable;
        }

      }

      static Text_Long_Validator* singleton()
      {
        // Since the validator has no individual state we use a static one.
        static Text_Long_Validator s_validator{};

        return std::addressof(s_validator);
      }
    };

    std::unique_ptr<QTextEdit> text_long_make_true_empty_widget()
    {
      // Build a true-type widget so we can manipulate it.
      auto l_widget = std::make_unique<QTextEdit>(nullptr);

      // Setup
      //l_widget->setMaxLength(2048);
      l_widget->setAcceptRichText(false);

      // Install it.
      //l_widget->setValidator(Text_Long_Validator::singleton());

      // Return the setup widget.
      return std::move(l_widget);
    }

    void text_long_set_true_widget_value(QTextEdit* a_widget, Text_Long::Value_Type const& a_value)
    {
      // This widget better have a validator, and it better be the right one...
      //assert(a_widget->validator() == Text_Long_Validator::singleton());
      // Value should already be validated.
      //assert(a_widget->validator()->validate(a_value, 0) == QValidator::Acceptable);

      // Set the value.
      a_widget->setPlainText(a_value);

      // Value should set properly.
      assert(a_widget->toPlainText() == a_value);
    }
  }
}



std::unique_ptr<QWidget> sak::Text_Long::make_empty_widget()
{
  // Make an empty widget and repackage it.
  return std::unique_ptr<QWidget>(text_long_make_true_empty_widget().release());
}

std::unique_ptr<QWidget> sak::Text_Long::make_widget(Value_Type const& a_value)
{
  // Make an empty true widget.
  auto l_widget = text_long_make_true_empty_widget();

  // Set the value.
  text_long_set_true_widget_value(l_widget.get(), a_value);

  // Repackage the widget.
  return std::unique_ptr<QWidget>(l_widget.release());
}

void sak::Text_Long::set_widget_value(QWidget* a_widget, Value_Type const& a_value)
{
  // Cast and set the value.
  text_long_set_true_widget_value(static_cast<QTextEdit*>(a_widget), a_value);
}

typename sak::Text_Long::Value_Type sak::Text_Long::get_widget_value(QWidget* a_widget)
{
  // Cast and access the value.
  return static_cast<QTextEdit*>(a_widget)->toPlainText();
}

void sak::Text_Long::connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor)
{
  QObject::connect(static_cast<QTextEdit*>(a_widget), &QTextEdit::textChanged, a_editor, &Abstract_Member_Edit_Widget::editing_finished);
}
