#include "attribute_editor_double.h"

#include "project_widget.h"
#include "../project_manager.h"
#include "qstring_operations.h"

#include <numeric>

//#include <QLabel>
#include <QDoubleSpinBox>
#include <QHBoxLayout>


// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Double::Attribute_Editor_Double(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_spinbox(),
    //m_label(),
    m_layout()
{
    shared_construction();
}
Saklib::Qtlib::Attribute_Editor_Double::Attribute_Editor_Double(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, vector_index, parent),
    m_spinbox(),
    //m_label(),
    m_layout()
{
    shared_construction();
}
Saklib::Qtlib::Attribute_Editor_Double::~Attribute_Editor_Double() = default;


void Saklib::Qtlib::Attribute_Editor_Double::v_refresh_data()
{
    m_spinbox->setValue(attribute_value<Double>());
}

void Saklib::Qtlib::Attribute_Editor_Double::v_editing_finished()
{
    if (is_vector_component())
        project_widget()->project_manager().undoable_attribute_vector_set_at<Double>(attributeid(), vector_index(), m_spinbox->value());
    else
        project_widget()->project_manager().undoable_attribute_set_value<Double>(attributeid(), m_spinbox->value());
}

void Saklib::Qtlib::Attribute_Editor_Double::shared_construction()
{
    m_spinbox = make_quptr<QDoubleSpinBox>();
    //m_label = make_quptr<QLabel>();
    m_layout = make_quptr<QHBoxLayout>();
    m_spinbox->setValue(attribute_value<Double>());

    auto constraint = project_widget()->project_manager().attribute_type_cast<Double>(attributeid())->constraint();

    if (constraint && constraint->has_min_value())
        m_spinbox->setMinimum(constraint->min_value());
    else
        m_spinbox->setMinimum(-1000000.00);
        //m_spinbox->setMinimum(std::numeric_limits<Double>::min());

    if (constraint && constraint->has_max_value())
        m_spinbox->setMaximum(constraint->max_value());
    else
        m_spinbox->setMaximum(1000000.00);
        //m_spinbox->setMaximum(std::numeric_limits<Double>::max());

    if (constraint && constraint->has_step_size())
        m_spinbox->setSingleStep(constraint->step_size());
    else
        m_spinbox->setSingleStep(1);

    if (constraint && constraint->has_decimal_places())
        m_spinbox->setDecimals(constraint->decimal_places());
    else
        m_spinbox->setDecimals(2);

    // this works but is ass.
    // Probably going to want constraints as part of an Attribute by default?

    //QString label_text{"Min: "};
    //label_text.append(to_QString(m_spinbox->minimum()));
    //label_text.append(" Max: ");
    //label_text.append(to_QString(m_spinbox->maximum()));
    //m_label->setText(label_text);

    QObject::connect(m_spinbox.get(), &QSpinBox::editingFinished,
                     this, &Attribute_Editor_Double::v_editing_finished);

    m_layout->addWidget(m_spinbox.get());
    m_layout->setStretch(0,1);
    //m_layout->addWidget(m_label.get());
    //m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
