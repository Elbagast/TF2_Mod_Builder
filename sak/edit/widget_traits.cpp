#include "widget_traits.hpp"

#include <QString>
#include <QLineEdit>
#include <QObject>
#include <QCheckBox>

//---------------------------------------------------------------------------
// edit::widget_traits<QString>
//---------------------------------------------------------------------------
// Specialisation for QString

std::unique_ptr<QWidget> sak::edit::widget_traits<QString>::make_empty_widget()
{
  return std::unique_ptr<QWidget>(std::make_unique<QLineEdit>(nullptr).release());
}

std::unique_ptr<QWidget> sak::edit::widget_traits<QString>::make_widget(value_type const& a_value)
{
  return std::unique_ptr<QWidget>(std::make_unique<QLineEdit>(a_value, nullptr).release());
}

void sak::edit::widget_traits<QString>::set_widget_value(QWidget* a_widget, value_type const& a_value)
{
  static_cast<QLineEdit*>(a_widget)->setText(a_value);
}

typename sak::edit::widget_traits<QString>::value_type sak::edit::widget_traits<QString>::get_widget_value(QWidget* a_widget)
{
  return static_cast<QLineEdit*>(a_widget)->text();
}

void sak::edit::widget_traits<QString>::connect_to(QWidget* a_widget, editor_type* a_editor, editor_function_type a_func)
{
  QObject::connect(static_cast<QLineEdit*>(a_widget), &QLineEdit::editingFinished, a_editor, a_func);
}

//---------------------------------------------------------------------------
// edit::widget_traits<std::string>
//---------------------------------------------------------------------------
// Specialisation for std::string assumed as utf8

std::unique_ptr<QWidget> sak::edit::widget_traits<std::string>::make_empty_widget()
{
  return std::unique_ptr<QWidget>(std::make_unique<QLineEdit>(nullptr).release());
}

std::unique_ptr<QWidget> sak::edit::widget_traits<std::string>::make_widget(value_type const& a_value)
{
  return std::unique_ptr<QWidget>(std::make_unique<QLineEdit>(QString::fromStdString(a_value), nullptr).release());
}

void sak::edit::widget_traits<std::string>::set_widget_value(QWidget* a_widget, value_type const& a_value)
{
  static_cast<QLineEdit*>(a_widget)->setText(QString::fromStdString(a_value));
}

typename sak::edit::widget_traits<std::string>::value_type sak::edit::widget_traits<std::string>::get_widget_value(QWidget* a_widget)
{
  return static_cast<QLineEdit*>(a_widget)->text().toStdString();
}

void sak::edit::widget_traits<std::string>::connect_to(QWidget* a_widget, editor_type* a_editor, editor_function_type a_func)
{
  QObject::connect(static_cast<QLineEdit*>(a_widget), &QLineEdit::editingFinished, a_editor, a_func);
}

//---------------------------------------------------------------------------
// edit::widget_traits<bool>
//---------------------------------------------------------------------------
// Specialisation for bool

std::unique_ptr<QWidget> sak::edit::widget_traits<bool>::make_empty_widget()
{
  return std::unique_ptr<QWidget>(std::make_unique<QCheckBox>(nullptr).release());
}

std::unique_ptr<QWidget> sak::edit::widget_traits<bool>::make_widget(value_type const& a_value)
{
  auto l_widget = make_empty_widget();
  set_widget_value(l_widget.get(), a_value);
  return std::move(l_widget);
}

void sak::edit::widget_traits<bool>::set_widget_value(QWidget* a_widget, value_type const& a_value)
{
  static_cast<QCheckBox*>(a_widget)->setChecked(a_value);
}

typename sak::edit::widget_traits<bool>::value_type sak::edit::widget_traits<bool>::get_widget_value(QWidget* a_widget)
{
  return static_cast<QCheckBox*>(a_widget)->isChecked();
}

void sak::edit::widget_traits<bool>::connect_to(QWidget* a_widget, editor_type* a_editor, editor_function_type a_func)
{
  QObject::connect(static_cast<QCheckBox*>(a_widget), &QCheckBox::stateChanged, [a_editor, a_func](){ (a_editor->*a_func)(); });
}
