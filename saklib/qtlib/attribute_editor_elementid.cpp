#include "attribute_editor_elementid.h"
#include "project_widget.h"
#include <QHBoxLayout>

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_ElementID::Attribute_Editor_ElementID(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_elementid(this->project_widget()->attribute_type_cast<ElementID>(this->attributeid())->value()),
    m_layout(new QHBoxLayout)
{

    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
Saklib::Qtlib::Attribute_Editor_ElementID::~Attribute_Editor_ElementID() = default;


void Saklib::Qtlib::Attribute_Editor_ElementID::v_refresh_data()
{
    auto const data_value = this->project_widget()->attribute_type_cast<ElementID>(this->attributeid())->value();
    if (m_elementid != data_value)
    {
        //refresh the representation
        m_elementid = data_value;
    }
}

void Saklib::Qtlib::Attribute_Editor_ElementID::slot_clicked()
{
    this->project_widget()->undoable_set_attribute_value_type<Bool>(this->attributeid(), m_checkbox->isChecked());
}
