#include "member_widget.hpp"

//---------------------------------------------------------------------------
// shared::abstract::member_edit_widget
//---------------------------------------------------------------------------
// This is the base class for member value editor widgets. These are the
// things that must be supplied. Inherit this class and compose the true
// editor in it. Also for a signal to be generated it must not be part of a template.

// Special 6
//============================================================
sak::shared::abstract::member_edit_widget::member_edit_widget(QWidget* a_parent):
  QWidget(a_parent)
{}

sak::shared::abstract::member_edit_widget::~member_edit_widget() = default;
