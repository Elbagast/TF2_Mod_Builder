#include "attribute_editor_int.h"

#include "project_widget.h"
#include "qstring_operations.h"

#include <numeric>

#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>


// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Int::Attribute_Editor_Int(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_spinbox(),
    m_label(),
    m_layout()
{
    shared_construction();
}
Saklib::Qtlib::Attribute_Editor_Int::Attribute_Editor_Int(Project_Widget*const project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, vector_index, parent),
    m_spinbox(),
    m_label(),
    m_layout()
{
    shared_construction();
}
Saklib::Qtlib::Attribute_Editor_Int::~Attribute_Editor_Int() = default;


void Saklib::Qtlib::Attribute_Editor_Int::v_refresh_data()
{
    m_spinbox->setValue(attribute_value<Int>());
}

// Slot used to capture the signal editingFinished() from the QSpinBox
void Saklib::Qtlib::Attribute_Editor_Int::slot_editingFinished()
{
    if (is_vector_component())
        project_widget()->undoable_attribute_vector_set_at<Int>(attributeid(), vector_index(), m_spinbox->value());
    else
        project_widget()->undoable_attribute_set_value<Int>(attributeid(), m_spinbox->value());
}

void Saklib::Qtlib::Attribute_Editor_Int::shared_construction()
{
    m_spinbox = std::make_unique<QSpinBox>();
    m_label = std::make_unique<QLabel>();
    m_layout = std::make_unique<QHBoxLayout>();

    m_spinbox->setValue(attribute_value<Int>());

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
