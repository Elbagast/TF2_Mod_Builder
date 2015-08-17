#include "element_name_editor.h"
#include "project_widget.h"
#include "../project_manager.h"
#include "qstring_operations.h"

#include <QLabel>
#include <QLineEdit>
#include <QStackedLayout>
#include <QMenu>
#include <QMouseEvent>
#include <QFocusEvent>

// Special 6
//============================================================
Saklib::Qtlib::Element_Name_Editor::Element_Name_Editor(Project_Widget* project_widget, ElementID elementid, QWidget* parent):
    QWidget(parent),
    mp_project_widget(project_widget),
    m_elementid(elementid),
    m_label(make_quptr<QLabel>(to_QString(mp_project_widget->project_manager().element_name(m_elementid)), this)),
    m_line_edit(make_quptr<QLineEdit>(to_QString(mp_project_widget->project_manager().element_name(m_elementid)), this)),
    m_layout(make_quptr<QStackedLayout>())
{
    m_layout->addWidget(m_label.get());
    m_layout->addWidget(m_line_edit.get());
    m_layout->setCurrentIndex(0);

    QObject::connect(m_line_edit.get(), &QLineEdit::editingFinished,
                     this, &Element_Name_Editor::slot_end_editing);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(this, &Element_Name_Editor::customContextMenuRequested,
                     this, &Element_Name_Editor::slot_customContextMenuRequested);

    m_label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    m_line_edit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
}

Saklib::Qtlib::Element_Name_Editor::~Element_Name_Editor() = default;

void Saklib::Qtlib::Element_Name_Editor::refresh_data()
{
    auto name = to_QString(mp_project_widget->project_manager().element_name(m_elementid));
    m_label->setText(name);
    m_line_edit->setText(name);
}

// Slots
//============================================================
// Connected to this->customContextMenuRequested
void Saklib::Qtlib::Element_Name_Editor::slot_customContextMenuRequested(QPoint const& pos)
{
    QMenu context_manu{};
    auto rename_action = context_manu.addAction("Rename");
    QObject::connect(rename_action, &QAction::triggered,
                     this, &Element_Name_Editor::slot_start_editing);

    context_manu.exec(this->mapToGlobal(pos));
}

void Saklib::Qtlib::Element_Name_Editor::slot_start_editing()
{
    m_layout->setCurrentIndex(1);
    m_line_edit->setFocus();
    m_line_edit->selectAll();
}

void Saklib::Qtlib::Element_Name_Editor::slot_end_editing()
{
    // if the line eidt contains text different from the label, apply an edit
    if (m_line_edit->text() != m_label->text())
    {
        // Set the Element name, this will loop back to tell this widget to update.
        mp_project_widget->project_manager().undoable_element_set_name(m_elementid, to_String(m_line_edit->text()));
    }
    m_layout->setCurrentIndex(0);
}

// Virtual Overrides
//============================================================
// To switching to the QLineEdit on double-click
void Saklib::Qtlib::Element_Name_Editor::mouseDoubleClickEvent(QMouseEvent* mouse_event)
{
    if (mouse_event->button() == Qt::LeftButton)
    {
        if (m_layout->currentIndex() == 0)
        {
            slot_start_editing();
        }
    }
}

// To switch to the QLabel when focus on this is lost
void Saklib::Qtlib::Element_Name_Editor::focusOutEvent(QFocusEvent* event)
{
    if (event->lostFocus())
    {
        slot_end_editing();
        QWidget::focusOutEvent(event);
    }
}
