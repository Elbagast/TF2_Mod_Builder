#include "attribute_editor_int.h"

#include "project_widget.h"
#include "../project_manager.h"
#include "qstring_operations.h"

#include <numeric>

#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>


// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Int::Attribute_Editor_Int(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_spinbox(),
    //m_label(),
    m_layout()
{
    shared_construction();
}
Saklib::Qtlib::Attribute_Editor_Int::Attribute_Editor_Int(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, vector_index, parent),
    m_spinbox(),
    //m_label(),
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
void Saklib::Qtlib::Attribute_Editor_Int::v_editing_finished()
{
    if (is_vector_component())
        project_widget()->project_manager().undoable_attribute_vector_set_at<Int>(attributeid(), vector_index(), m_spinbox->value());
    else
        project_widget()->project_manager().undoable_attribute_set_value<Int>(attributeid(), m_spinbox->value());
}

void Saklib::Qtlib::Attribute_Editor_Int::shared_construction()
{
    m_spinbox = make_quptr<QSpinBox>();
    //m_label = make_quptr<QLabel>();
    m_layout = make_quptr<QHBoxLayout>();

    m_spinbox->setValue(attribute_value<Int>());


    // And this is why sharing construction of two unrelated types is baaaad

    Attribute_Type<Int>::stored_type_constraint const* lp_constraint = nullptr;

    if (is_vector_component())
    {
        lp_constraint = attribute_type_cast<Vector_Int>(project_widget()->project_manager().attribute(attributeid()))->value_constraint();
    }
    else
    {
        lp_constraint = attribute_type_cast<Int>(project_widget()->project_manager().attribute(attributeid()))->constraint();
    }

    if (lp_constraint && lp_constraint->has_min_value())
        m_spinbox->setMinimum(lp_constraint->min_value());
    else
        m_spinbox->setMinimum(std::numeric_limits<Int>::min());

    if (lp_constraint && lp_constraint->has_max_value())
        m_spinbox->setMaximum(lp_constraint->max_value());
    else
        m_spinbox->setMaximum(std::numeric_limits<Int>::max());

    if (lp_constraint && lp_constraint->has_step_size())
        m_spinbox->setSingleStep(lp_constraint->step_size());
    else
        m_spinbox->setSingleStep(1);

    QObject::connect(m_spinbox.get(), &QSpinBox::editingFinished,
                     this, &Attribute_Editor_Int::v_editing_finished);

    //QString label_text{"Min: "};
    //label_text.append(to_QString(m_spinbox->minimum()));
    //label_text.append(" Max: ");
    //label_text.append(to_QString(m_spinbox->maximum()));
    //m_label->setText(label_text);

    m_layout->addWidget(m_spinbox.get());
    m_layout->setStretch(0,1);
    //m_layout->addWidget(m_label.get());
    //m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
