#include "attribute_editor_double.h"

#include "project_widget.h"
#include "qstring_operations.h"

#include <numeric>

#include <QLabel>
#include <QDoubleSpinBox>
#include <QHBoxLayout>


// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Double::Attribute_Editor_Double(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_spinbox(new QDoubleSpinBox(this)),
    m_label(new QLabel(this)),
    m_layout(new QHBoxLayout)
{
    m_spinbox->setValue(this->project_widget()->attribute_type_cast<Double>(this->attributeid())->value());

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

    QObject::connect(m_spinbox.get(), &QSpinBox::editingFinished,
                     this, &Attribute_Editor_Double::slot_editingFinished);

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
    auto const data_value = this->project_widget()->attribute_type_cast<Double>(this->attributeid())->value();
    if (m_spinbox->value() != data_value)
    {
        m_spinbox->setValue(data_value);
    }
}

// Slot used to capture the signal editingFinished() from the QSpinBox
void Saklib::Qtlib::Attribute_Editor_Double::slot_editingFinished()
{
    this->project_widget()->undoable_attribute_set_value<Double>(this->attributeid(), m_spinbox->value());
}
