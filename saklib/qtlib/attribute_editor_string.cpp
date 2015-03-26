#include "attribute_editor_string.h"

#include "project_manager.h"
#include "qstring_operations.h"

#include <QLineEdit>
#include <QHBoxLayout>


// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_String::Attribute_Editor_String(Project_Manager& project_manager, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_manager, attributeid, parent),
    m_line_edit(new QLineEdit(this)),
    m_layout(new QHBoxLayout)
{
    m_line_edit->setText(to_QString(mr_project_manager.attribute_type_cast<String>(m_attributeid)->value()));

    QObject::connect(m_line_edit.get(), &QLineEdit::editingFinished,
                     this, &Attribute_Editor_String::slot_editingFinished);

    m_layout->addWidget(m_line_edit.get());
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
Saklib::Qtlib::Attribute_Editor_String::~Attribute_Editor_String() = default;


void Saklib::Qtlib::Attribute_Editor_String::v_refresh_data()
{
    QString const data_value = to_QString(mr_project_manager.attribute_type_cast<String>(m_attributeid)->value());
    if (m_line_edit->text() != data_value)
    {
        m_line_edit->setText(data_value);
    }
}

// Slot used to capture the signal editingFinished() from the QLineEdit
void Saklib::Qtlib::Attribute_Editor_String::slot_editingFinished()
{
    mr_project_manager.undoable_set_attribute_value_type<String>(m_attributeid, to_String(m_line_edit->text()));
}
