#include "attribute_editor_bool.h"
#include "project_manager.h"
#include <QCheckBox>
#include <QHBoxLayout>

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Bool::Attribute_Editor_Bool(Project_Manager& project_manager, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_manager, attributeid, parent),
    m_checkbox(new QCheckBox(this)),
    m_layout(new QHBoxLayout)
{
    m_checkbox->setChecked(mr_project_manager.attribute_type_cast<Bool>(m_attributeid)->get());

    QObject::connect(m_checkbox.get(), &QCheckBox::clicked,
                     this, &Attribute_Editor_Bool::slot_clicked);

    m_layout->addWidget(m_checkbox.get());
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
Saklib::Qtlib::Attribute_Editor_Bool::~Attribute_Editor_Bool() = default;


void Saklib::Qtlib::Attribute_Editor_Bool::v_refresh_data()
{
    auto const data_value = mr_project_manager.attribute_type_cast<Bool>(m_attributeid)->get();
    if (m_checkbox->isChecked() != data_value)
    {
        // block signals?
        m_checkbox->setChecked(data_value);
    }
}

void Saklib::Qtlib::Attribute_Editor_Bool::slot_clicked()
{
    mr_project_manager.command_set_attribute_value_type<Bool>(m_attributeid, m_checkbox->isChecked());
}
