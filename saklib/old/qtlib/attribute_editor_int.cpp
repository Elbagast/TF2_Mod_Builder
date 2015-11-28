#include "attribute_editor_int.h"

#include "project_widget.h"
#include "../project_manager.h"
#include "qstring_traits.h"

#include <limits>

#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDoubleValidator>

#include <QDebug>



// Special 6
//============================================================
saklib::Qtlib::Attribute_Editor_Int_SB::Attribute_Editor_Int_SB(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_spinbox(),
    //m_label(),
    m_layout()
{
    shared_construction();
}
saklib::Qtlib::Attribute_Editor_Int_SB::Attribute_Editor_Int_SB(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, vector_index, parent),
    m_spinbox(),
    //m_label(),
    m_layout()
{
    shared_construction();
}
saklib::Qtlib::Attribute_Editor_Int_SB::~Attribute_Editor_Int_SB() = default;


void saklib::Qtlib::Attribute_Editor_Int_SB::v_refresh_data()
{
    m_spinbox->setValue(attribute_value<Int>());
}

// Slot used to capture the signal editingFinished() from the QSpinBox
void saklib::Qtlib::Attribute_Editor_Int_SB::v_editing_finished()
{
    bool command_issued{false};
    if (is_vector_component())
    {
        command_issued = project_widget()->project_manager().undoable_attribute_vector_set_at<Int>(attributeid(), vector_index(), m_spinbox->value());
    }
    else
    {
        command_issued = project_widget()->project_manager().undoable_attribute_set_value<Int>(attributeid(), m_spinbox->value());
    }
    if (command_issued == false)
    {
        v_refresh_data();
    }
}

void saklib::Qtlib::Attribute_Editor_Int_SB::shared_construction()
{
    m_spinbox = make_quptr<QSpinBox>();
    //m_label = make_quptr<QLabel>();
    m_layout = make_quptr<QHBoxLayout>();

    m_spinbox->setValue(attribute_value<Int>());


    // And this is why sharing construction of two unrelated types is baaaad

    Attribute_Type<Int>::stored_type_constraint const* lp_constraint = nullptr;

    if (is_vector_component())
    {
        lp_constraint = attribute_type_cast<std::vector<Int>>(project_widget()->project_manager().attribute(attributeid()))->value_constraint();
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
                     this, &Attribute_Editor_Int_SB::v_editing_finished);

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



// Special 6
//============================================================
saklib::Qtlib::Attribute_Editor_Int_LE::Attribute_Editor_Int_LE(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_layout(),
    m_line_edit(),
    m_validator()

{
    shared_construction();
}
saklib::Qtlib::Attribute_Editor_Int_LE::Attribute_Editor_Int_LE(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, vector_index, parent),
    m_layout(),
    m_line_edit(),
    m_validator()
{
    shared_construction();
}
saklib::Qtlib::Attribute_Editor_Int_LE::~Attribute_Editor_Int_LE() = default;


void saklib::Qtlib::Attribute_Editor_Int_LE::v_refresh_data()
{
    qDebug() << "v_refresh_data()";
    qDebug() << "int value = " << to_qstring(attribute_value<Int>());
    m_line_edit->setText(to_qstring(attribute_value<Int>()));
    qDebug() << "text value = " << m_line_edit->text();
}

void saklib::Qtlib::Attribute_Editor_Int_LE::v_editing_finished()
{
    qDebug() << "v_editing_finished()";
    QString l_text = m_line_edit->text();
    int l_pos{0};
    qDebug() << "text value = " << l_text;
    qDebug() << "validator result = " << m_validator->validate(l_text, l_pos);

    Int entry{from_qstring<Int>(m_line_edit->text())};
    Int current{this->attribute_value<Int>()};

    qDebug() << "entry == current value = " << ( entry == current);
    if (entry != current)
    {
        if (is_vector_component())
        {
            project_widget()->project_manager().undoable_attribute_vector_set_at<Int>(attributeid(), vector_index(), from_qstring<Int>(m_line_edit->text()));
        }
        else
        {
            project_widget()->project_manager().undoable_attribute_set_value<Int>(attributeid(), from_qstring<Int>(m_line_edit->text()));
        }
    }
    else
    {
        v_refresh_data(); // report change failure somehow?
    }
}

void saklib::Qtlib::Attribute_Editor_Int_LE::shared_construction()
{
    m_layout = make_quptr<QHBoxLayout>();

    m_line_edit = make_quptr<QLineEdit>();
    m_validator = make_quptr<QIntValidator>();

    m_validator->setBottom(std::numeric_limits<Int>::lowest());
    m_validator->setTop(std::numeric_limits<Int>::max());
    //m_validator->setDecimals();
    //m_validator->setNotation(QDoubleValidator::StandardNotation);
    //m_validator->setNotation(QDoubleValidator::ScientificNotation);

    Attribute_Type<Int>::stored_type_constraint const* lp_constraint = nullptr;

    if (is_vector_component())
    {
        lp_constraint = attribute_type_cast<std::vector<Int>>(project_widget()->project_manager().attribute(attributeid()))->value_constraint();
    }
    else
    {
        lp_constraint = attribute_type_cast<Int>(project_widget()->project_manager().attribute(attributeid()))->constraint();
    }

    if (lp_constraint && lp_constraint->has_min_value())
    {
        m_validator->setBottom(lp_constraint->min_value());
    }
    else
    {
        m_validator->setBottom(std::numeric_limits<Int>::lowest());
    }
    qDebug() << "validator bottom = " << to_qstring(m_validator->bottom());

    if (lp_constraint && lp_constraint->has_max_value())
    {
        m_validator->setTop(lp_constraint->max_value());
    }
    else
    {
        m_validator->setTop(std::numeric_limits<Int>::max());
    }
    qDebug() << "validator top = " << to_qstring(m_validator->top());

    m_line_edit->setValidator(m_validator.get());

    QObject::connect(m_line_edit.get(), &QLineEdit::editingFinished,
                     this, &Attribute_Editor_Int_LE::v_editing_finished);

    m_layout->addWidget(m_line_edit.get());



    v_refresh_data();

    m_layout->setStretch(0,1);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
