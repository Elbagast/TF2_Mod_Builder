#include "edit_widget_traits.hpp"

#include "abstract_member_edit_widget.hpp"

#include <QString>
#include <QLineEdit>
#include <QObject>
#include <QCheckBox>

//---------------------------------------------------------------------------
// Edit_Widget_Traits<QString>
//---------------------------------------------------------------------------
// Specialisation for QString

std::unique_ptr<QWidget> sak::Edit_Widget_Traits<QString>::make_empty_widget()
{
  return std::unique_ptr<QWidget>(std::make_unique<QLineEdit>(nullptr).release());
}

std::unique_ptr<QWidget> sak::Edit_Widget_Traits<QString>::make_widget(QString const& a_value)
{
  return std::unique_ptr<QWidget>(std::make_unique<QLineEdit>(a_value, nullptr).release());
}

void sak::Edit_Widget_Traits<QString>::set_widget_value(QWidget* a_widget, QString const& a_value)
{
  static_cast<QLineEdit*>(a_widget)->setText(a_value);
}

QString sak::Edit_Widget_Traits<QString>::get_widget_value(QWidget* a_widget)
{
  return static_cast<QLineEdit*>(a_widget)->text();
}

void sak::Edit_Widget_Traits<QString>::connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor)
{
  QObject::connect(static_cast<QLineEdit*>(a_widget), &QLineEdit::editingFinished, a_editor, &Abstract_Member_Edit_Widget::editing_finished);
}

//---------------------------------------------------------------------------
// Edit_Widget_Traits<std::string>
//---------------------------------------------------------------------------
// Specialisation for std::string assumed as utf8

std::unique_ptr<QWidget> sak::Edit_Widget_Traits<std::string>::make_empty_widget()
{
  return std::unique_ptr<QWidget>(std::make_unique<QLineEdit>(nullptr).release());
}

std::unique_ptr<QWidget> sak::Edit_Widget_Traits<std::string>::make_widget(std::string const& a_value)
{
  return std::unique_ptr<QWidget>(std::make_unique<QLineEdit>(QString::fromStdString(a_value), nullptr).release());
}

void sak::Edit_Widget_Traits<std::string>::set_widget_value(QWidget* a_widget, std::string const& a_value)
{
  static_cast<QLineEdit*>(a_widget)->setText(QString::fromStdString(a_value));
}

std::string sak::Edit_Widget_Traits<std::string>::get_widget_value(QWidget* a_widget)
{
  return static_cast<QLineEdit*>(a_widget)->text().toStdString();
}

void sak::Edit_Widget_Traits<std::string>::connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor)
{
  QObject::connect(static_cast<QLineEdit*>(a_widget), &QLineEdit::editingFinished, a_editor, &Abstract_Member_Edit_Widget::editing_finished);
}

//---------------------------------------------------------------------------
// Edit_Widget_Traits<bool>
//---------------------------------------------------------------------------
// Specialisation for bool

std::unique_ptr<QWidget> sak::Edit_Widget_Traits<bool>::make_empty_widget()
{
  return std::unique_ptr<QWidget>(std::make_unique<QCheckBox>(nullptr).release());
}

std::unique_ptr<QWidget> sak::Edit_Widget_Traits<bool>::make_widget(bool a_value)
{
  auto l_widget = make_empty_widget();
  set_widget_value(l_widget.get(), a_value);
  return std::move(l_widget);
}

void sak::Edit_Widget_Traits<bool>::set_widget_value(QWidget* a_widget, bool a_value)
{
  static_cast<QCheckBox*>(a_widget)->setChecked(a_value);
}

bool sak::Edit_Widget_Traits<bool>::get_widget_value(QWidget* a_widget)
{
  return static_cast<QCheckBox*>(a_widget)->isChecked();
}

void sak::Edit_Widget_Traits<bool>::connect_to(QWidget* a_widget, Abstract_Member_Edit_Widget* a_editor)
{
  QObject::connect(static_cast<QCheckBox*>(a_widget), &QCheckBox::stateChanged, [a_editor](){ a_editor->editing_finished(); });
}
