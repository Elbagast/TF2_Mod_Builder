#include "attribute_editor_string.h"

#include "project_widget.h"
#include "qstring_operations.h"

#include <QLineEdit>
#include <QHBoxLayout>


// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_String::Attribute_Editor_String(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_line_edit(),
    m_layout()
{
    shared_construction();
}
Saklib::Qtlib::Attribute_Editor_String::Attribute_Editor_String(Project_Widget*const project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, vector_index, parent),
    m_line_edit(),
    m_layout()
{
    shared_construction();
}
Saklib::Qtlib::Attribute_Editor_String::~Attribute_Editor_String() = default;


void Saklib::Qtlib::Attribute_Editor_String::v_refresh_data()
{
    m_line_edit->setText(to_QString(attribute_value<String>()));
}

// Slot used to capture the signal editingFinished() from the QLineEdit
void Saklib::Qtlib::Attribute_Editor_String::slot_editingFinished()
{
    if (is_vector_component())
        project_widget()->undoable_attribute_vector_set_at<String>(attributeid(), vector_index(), to_String(m_line_edit->text()));
    else
        project_widget()->undoable_attribute_set_value<String>(attributeid(), to_String(m_line_edit->text()));
}

void Saklib::Qtlib::Attribute_Editor_String::shared_construction()
{
    m_line_edit = std::make_unique<QLineEdit>();
    m_layout = std::make_unique<QHBoxLayout>();

    m_line_edit->setText(to_QString(attribute_value<String>()));

    QObject::connect(m_line_edit.get(), &QLineEdit::editingFinished,
                     this, &Attribute_Editor_String::slot_editingFinished);

    m_layout->addWidget(m_line_edit.get());
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
