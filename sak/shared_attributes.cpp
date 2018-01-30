#include "shared_attributes.hpp"

#include "abstract_member_edit_widget.hpp"

#include <cassert>

#include <QString>
#include <QLineEdit>
#include <QObject>
#include <QValidator>
#include <QCheckBox>
#include <QTextEdit>

#include <qtlib/line_edit.hpp>

namespace sak
{
  //---------------------------------------------------------------------------
  // Default_Line_Edit
  //---------------------------------------------------------------------------
  // Widget operations for qtlib::Line_Edit. That entire class could be hidden
  // in here...

  class Default_Line_Edit
  {
  public:
    static std::unique_ptr<qtlib::Line_Edit> make_empty_true_widget(QValidator* a_validator, int a_max_length, QString const& a_tooltip);

    static std::unique_ptr<qtlib::Line_Edit> make_true_widget(QValidator* a_validator, int a_max_length, QString const& a_tooltip, QString const& a_value);

    static void set_true_widget_value(qtlib::Line_Edit* a_widget, QString const& a_value);

    static QString get_true_widget_value(qtlib::Line_Edit* a_widget);

    static std::unique_ptr<QWidget> make_empty_widget(QValidator* a_validator, int a_max_length, QString const& a_tooltip);

    static std::unique_ptr<QWidget> make_widget(QValidator* a_validator, int a_max_length, QString const& a_tooltip, QString const& a_value);

    static void set_widget_value(QWidget* a_widget, QString const& a_value);

    static QString get_widget_value(QWidget* a_widget);

    static void connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor);
  };
} // namespace sak

//---------------------------------------------------------------------------
// Default_Line_Edit
//---------------------------------------------------------------------------

std::unique_ptr<qtlib::Line_Edit> sak::Default_Line_Edit::make_empty_true_widget(QValidator* a_validator, int a_max_length, QString const& a_tooltip)
{
  // Build a true-type widget so we can manipulate it.
  auto l_widget = std::make_unique<qtlib::Line_Edit>(nullptr);

  // Setup using supplied arguments.
  l_widget->setValidator(a_validator);
  l_widget->setMaxLength(a_max_length);
  l_widget->setToolTip(a_tooltip);

  // Return the setup widget.
  return std::move(l_widget);
}

std::unique_ptr<qtlib::Line_Edit> sak::Default_Line_Edit::make_true_widget(QValidator* a_validator, int a_max_length, QString const& a_tooltip, QString const& a_value)
{
  // Make an empty widget.
  auto l_widget = make_empty_true_widget(a_validator,a_max_length,a_tooltip);

  // SEt the value using the prescribed method.
  set_true_widget_value(l_widget.get(), a_value);

  // Return the setup widget.
  return std::move(l_widget);
}

void sak::Default_Line_Edit::set_true_widget_value(qtlib::Line_Edit* a_widget, QString const& a_value)
{
  a_widget->setText(a_value);
}


QString sak::Default_Line_Edit::get_true_widget_value(qtlib::Line_Edit* a_widget)
{
  return a_widget->text();
}

std::unique_ptr<QWidget> sak::Default_Line_Edit::make_empty_widget(QValidator* a_validator, int a_max_length, QString const& a_tooltip)
{
  auto l_true_widget = make_empty_true_widget(a_validator, a_max_length, a_tooltip);
  std::unique_ptr<QWidget> l_widget{ l_true_widget.release() };

  // Return the setup widget.
  return std::move(l_widget);
}

std::unique_ptr<QWidget> sak::Default_Line_Edit::make_widget(QValidator* a_validator, int a_max_length, QString const& a_tooltip, QString const& a_value)
{
  auto l_true_widget = make_true_widget(a_validator, a_max_length, a_tooltip, a_value);
  std::unique_ptr<QWidget> l_widget{ l_true_widget.release() };

  // Return the setup widget.
  return std::move(l_widget);
}

void sak::Default_Line_Edit::set_widget_value(QWidget* a_widget, QString const& a_value)
{
  auto l_true_widget = static_cast<qtlib::Line_Edit*>(a_widget);
  set_true_widget_value(l_true_widget, a_value);
}

QString sak::Default_Line_Edit::get_widget_value(QWidget* a_widget)
{
  auto l_true_widget = static_cast<qtlib::Line_Edit*>(a_widget);
  return get_true_widget_value(l_true_widget);
}

void sak::Default_Line_Edit::connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor)
{
  auto l_true_widget = static_cast<qtlib::Line_Edit*>(a_widget);

  QObject::connect(l_true_widget,
                   &qtlib::Line_Edit::editingFinished,
                   a_editor,
                   &Abstract_Member_Edit_Widget::editing_finished);

  QObject::connect(l_true_widget,
                   &qtlib::Line_Edit::editingFailed,
                   a_editor,
                   &Abstract_Member_Edit_Widget::editing_failed);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------


namespace sak
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
  // Text_Name_Validator
  //---------------------------------------------------------------------------
  class Text_Name_Validator :
      public QValidator
  {
  private:
    // Special 6
    //============================================================
    Text_Name_Validator() = default;
  public:
    ~Text_Name_Validator() override = default;

    // QValidator overrides
    //============================================================
    //void fixup(QString& a_input) const override final;

    QValidator::State validate(QString& a_input, int& /*a_cursor_position*/) const override final
    {
      // A name cannot be empty
      if (a_input.isEmpty())
      {
        return QValidator::Intermediate;
      }
      // Cannot start with a space character
      if (a_input.front().isSpace())
      {
        return QValidator::Intermediate;
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

    static Text_Name_Validator* singleton()
    {
      // Since the validator has no individual state we use a static one.
      static Text_Name_Validator s_validator{};

      return std::addressof(s_validator);
    }
  };

  std::unique_ptr<qtlib::Line_Edit> text_name_make_true_empty_widget()
  {
    // Build a true-type widget so we can manipulate it.
    auto l_widget = std::make_unique<qtlib::Line_Edit>(nullptr);

    // Setup
    l_widget->setMaxLength(256);

    // Install it.
    l_widget->setValidator(Text_Name_Validator::singleton());

    // Return the setup widget.
    return std::move(l_widget);
  }

  void text_name_set_true_widget_value(qtlib::Line_Edit* a_widget, Text_Name::Value_Type const& a_value)
  {
    // This widget better have a validator, and it better be the right one...
    assert(a_widget->validator() == Text_Name_Validator::singleton());
    // Value should already be validated.
    //assert(a_widget->validator()->validate(a_value, 0) == QValidator::Acceptable);

    // Set the value.
    a_widget->setText(a_value);

    // Value should set properly.
    assert(a_widget->text() == a_value);
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Text_Name
//---------------------------------------------------------------------------
// A short string of unicode text containing any characters except control
// characters. Max length is 256 chars. Must contain something.

std::unique_ptr<QWidget> sak::Text_Name::make_empty_widget()
{
  return Default_Line_Edit::make_empty_widget(Text_Name_Validator::singleton(), 256, tooltip());
}

std::unique_ptr<QWidget> sak::Text_Name::make_widget(Value_Type const& a_value)
{
  return Default_Line_Edit::make_widget(Text_Name_Validator::singleton(), 256, tooltip(), a_value);
}

void sak::Text_Name::set_widget_value(QWidget* a_widget, Value_Type const& a_value)
{
  Default_Line_Edit::set_widget_value(a_widget, a_value);
}

typename sak::Text_Name::Value_Type sak::Text_Name::get_widget_value(QWidget* a_widget)
{
  return Default_Line_Edit::get_widget_value(a_widget);
}

void sak::Text_Name::connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor)
{
  Default_Line_Edit::connect_to(a_widget, a_editor);
}

QString sak::Text_Name::tooltip()
{
  return QString::fromUtf8(u8"A short string containing printable characters, including spaces.\n"
                           "- Max length = 256 characters.\n"
                           "- Cannot start with a space.\n"
                           "- Must be at least 1 character long.\n"
                           "- The supplied name should be unique among the group.\n"
                           "- If it isn't it will be altered to fit."
                           );
}


//------------------------------------------------------------------------------------------------------------------------------------------------------



namespace sak
{
  namespace
  {
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

      QValidator::State validate(QString& a_input, int& /*a_cursor_position*/) const override final
      {
        // Format [word]{Nx[directory seperator][word]} where N can be 0
        // word = combination of a...z,A...Z,_ chars
        // directory seperator = / or \\
        // If the last char is a seperator then the result is intermediate.

        // Can be empty
        if (a_input.isEmpty())
        {
          return QValidator::Acceptable;
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

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Text_Line
//---------------------------------------------------------------------------
// A short string of unicode text containing any characters except control
// characters. Max length is 256 chars.

std::unique_ptr<QWidget> sak::Text_Line::make_empty_widget()
{
  return Default_Line_Edit::make_empty_widget(Text_Line_Validator::singleton(), 256, tooltip());
}

std::unique_ptr<QWidget> sak::Text_Line::make_widget(Value_Type const& a_value)
{
  return Default_Line_Edit::make_widget(Text_Line_Validator::singleton(), 256, tooltip(), a_value);
}

void sak::Text_Line::set_widget_value(QWidget* a_widget, Value_Type const& a_value)
{
  Default_Line_Edit::set_widget_value(a_widget, a_value);
}

typename sak::Text_Line::Value_Type sak::Text_Line::get_widget_value(QWidget* a_widget)
{
  return Default_Line_Edit::get_widget_value(a_widget);
}

void sak::Text_Line::connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor)
{
  Default_Line_Edit::connect_to(a_widget, a_editor);
}

QString sak::Text_Line::tooltip()
{
  return QString::fromUtf8(u8"A short string containing printable characters, including spaces.\n"
                           "- Max length = 256 characters."
                           );
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

      QValidator::State validate(QString& a_input, int& /*a_cursor_position*/) const override final
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
