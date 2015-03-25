#include "attribute_editor_double.h"

#include "project_manager.h"
#include "temp_disconnect.h"
#include "qstring_operations.h"

#include <numeric>

#include <QLabel>
#include <QDoubleSpinBox>
#include <QHBoxLayout>


// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Double::Attribute_Editor_Double(Project_Manager& project_manager, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_manager, attributeid, parent),
    m_spinbox(new QDoubleSpinBox(this)),
    m_label(new QLabel(this)),
    m_layout(new QHBoxLayout)
{
    m_spinbox->setValue(mr_project_manager.attribute_type_cast<Double>(m_attributeid)->get());

    // ok this gets a bit weird with numeric limits, because they're mad
    m_spinbox->setMinimum(std::numeric_limits<Double>::min());
    m_spinbox->setMaximum(std::numeric_limits<Double>::max());

    m_spinbox->setMinimum(-1000000.00);
    m_spinbox->setMaximum(1000000.00);

    QString label_text{"Min: "};
    label_text.append(to_QString(m_spinbox->minimum()));
    label_text.append(" Max: ");
    label_text.append(to_QString(m_spinbox->maximum()));
    m_label->setText(label_text);

    // must specify template to disambiguate the overloaded valueChanged signal
    QObject::connect<void(QDoubleSpinBox::*)(double), void(Attribute_Editor_Double::*)(double)>(m_spinbox.get(), &QDoubleSpinBox::valueChanged,
                     this, &Attribute_Editor_Double::slot_valueChanged);

    m_layout->addWidget(m_spinbox.get());
    m_layout->setStretch(0,1);
    m_layout->addWidget(m_label.get());
    //m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
Saklib::Qtlib::Attribute_Editor_Double::~Attribute_Editor_Double() = default;


void Saklib::Qtlib::Attribute_Editor_Double::v_refresh_data()
{
    auto const data_value = mr_project_manager.attribute_type_cast<Double>(m_attributeid)->get();
    if (m_spinbox->value() != data_value)
    {
        auto td = make_Temp_Disconnect<void(QDoubleSpinBox::*)(double), void(Attribute_Editor_Double::*)(double)>(m_spinbox.get(), &QDoubleSpinBox::valueChanged,
                    this, &Attribute_Editor_Double::slot_valueChanged);
        m_spinbox->setValue(data_value);
    }
}

void Saklib::Qtlib::Attribute_Editor_Double::slot_valueChanged(double value)
{
    mr_project_manager.command_set_attribute_value_type<Double>(m_attributeid, value);
}

