#include "attribute_editor_int.h"

#include "project_manager.h"
#include "qstring_operations.h"

#include <numeric>

#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>


// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Int::Attribute_Editor_Int(Project_Manager& project_manager, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_manager, attributeid, parent),
    m_spinbox(new QSpinBox(this)),
    m_label(new QLabel(this)),
    m_layout(new QHBoxLayout)
{
    m_spinbox->setValue(mr_project_manager.attribute_type_cast<Int>(m_attributeid)->value());

    m_spinbox->setMinimum(std::numeric_limits<Int>::min());
    m_spinbox->setMaximum(std::numeric_limits<Int>::max());

    QObject::connect(m_spinbox.get(), &QSpinBox::editingFinished,
                     this, &Attribute_Editor_Int::slot_editingFinished);

    QString label_text{"Min: "};
    label_text.append(to_QString(m_spinbox->minimum()));
    label_text.append(" Max: ");
    label_text.append(to_QString(m_spinbox->maximum()));
    m_label->setText(label_text);

    m_layout->addWidget(m_spinbox.get());
    m_layout->setStretch(0,1);
    m_layout->addWidget(m_label.get());
    //m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
Saklib::Qtlib::Attribute_Editor_Int::~Attribute_Editor_Int() = default;


void Saklib::Qtlib::Attribute_Editor_Int::v_refresh_data()
{
    auto const data_value = mr_project_manager.attribute_type_cast<Int>(m_attributeid)->value();
    if (m_spinbox->value() != data_value)
    {
        m_spinbox->setValue(data_value);
    }
}

// Slot used to capture the signal editingFinished() from the QSpinBox
void Saklib::Qtlib::Attribute_Editor_Int::slot_editingFinished()
{
    mr_project_manager.undoable_set_attribute_value_type<Int>(m_attributeid, m_spinbox->value());
}
