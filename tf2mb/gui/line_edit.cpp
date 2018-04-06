#include "line_edit.hpp"

#include <QFocusEvent>

//---------------------------------------------------------------------------
// Line_Edit
//---------------------------------------------------------------------------

// Special 6
//============================================================
// Construct without a validator or a state changer.
sak::gui::Line_Edit::Line_Edit(QWidget* a_parent):
  QLineEdit(a_parent)
{
}
sak::gui::Line_Edit::Line_Edit(QString const& a_contents, QWidget* a_parent):
  QLineEdit(a_contents, a_parent)
{
}

sak::gui::Line_Edit::~Line_Edit() = default;

// Virtuals
//============================================================
void sak::gui::Line_Edit::focusOutEvent(QFocusEvent* a_event)
{
  if (a_event->lostFocus())
  {
    emit this->lostFocus();
    if (!this->hasAcceptableInput())
    {
      emit this->editingFailed();
    }
  }
  // continue as normal
  this->QLineEdit::focusOutEvent(a_event);
}
