#include "attribute_editor_double.h"

#include "project_widget.h"
#include "../project_manager.h"
#include "qstring_traits.h"

#include <numeric>

#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDoubleValidator>

#include <QDebug>


// Special 6
//============================================================
saklib::Qtlib::Attribute_Editor_Double_SB::Attribute_Editor_Double_SB(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_spinbox(),
    m_layout()

{
    shared_construction();
}
saklib::Qtlib::Attribute_Editor_Double_SB::Attribute_Editor_Double_SB(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, vector_index, parent),
    m_spinbox(),
    m_layout()
{
    shared_construction();
}
saklib::Qtlib::Attribute_Editor_Double_SB::~Attribute_Editor_Double_SB() = default;


void saklib::Qtlib::Attribute_Editor_Double_SB::v_refresh_data()
{
    m_spinbox->setValue(attribute_value<Double>());
}

void saklib::Qtlib::Attribute_Editor_Double_SB::v_editing_finished()
{
    if (is_vector_component())
    {
        project_widget()->project_manager().undoable_attribute_vector_set_at<Double>(attributeid(), vector_index(), m_spinbox->value());
    }
    else
    {
        project_widget()->project_manager().undoable_attribute_set_value<Double>(attributeid(), m_spinbox->value());
    }
}

void saklib::Qtlib::Attribute_Editor_Double_SB::shared_construction()
{
    m_layout = make_quptr<QHBoxLayout>();

    m_spinbox = make_quptr<QDoubleSpinBox>();
    //m_label = make_quptr<QLabel>();

    m_spinbox->setValue(attribute_value<Double>());

    // And this is why sharing construction of two unrelated types is baaaad

    Attribute_Type<Double>::stored_type_constraint const* lp_constraint = nullptr;

    if (is_vector_component())
    {
        lp_constraint = attribute_type_cast<std::vector<Double>>(project_widget()->project_manager().attribute(attributeid()))->value_constraint();
    }
    else
    {
        lp_constraint = attribute_type_cast<Double>(project_widget()->project_manager().attribute(attributeid()))->constraint();
    }

    if (lp_constraint && lp_constraint->has_min_value())
    {
        m_spinbox->setMinimum(lp_constraint->min_value());
    }
    else
    {
        //m_spinbox->setMinimum(-1000000.00);
        //m_spinbox->setMinimum(std::numeric_limits<Double>::min());
        m_spinbox->setMinimum(std::numeric_limits<Double>::lowest());
    }

    if (lp_constraint && lp_constraint->has_max_value())
    {
        m_spinbox->setMaximum(lp_constraint->max_value());
    }
    else
    {
        m_spinbox->setMaximum(1000000.00);
        //m_spinbox->setMaximum(std::numeric_limits<Double>::max());
    }

    if (lp_constraint && lp_constraint->has_step_size())
    {
        m_spinbox->setSingleStep(lp_constraint->step_size());
    }
    else
    {
        m_spinbox->setSingleStep(1);
    }

    if (lp_constraint && lp_constraint->has_decimal_places())
    {
        m_spinbox->setDecimals(lp_constraint->decimal_places());
    }
    else
    {
        m_spinbox->setDecimals(2);
    }



    // this works but is ass.
    // Probably going to want constraints as part of an Attribute by default?

    //QString label_text{"Min: "};
    //label_text.append(to_QString(m_spinbox->lowest()));
    //label_text.append(" Max: ");
    //label_text.append(to_QString(m_spinbox->maximum()));
    //m_label->setText(label_text);

    QObject::connect(m_spinbox.get(), &QSpinBox::editingFinished,
                     this, &Attribute_Editor_Double_SB::v_editing_finished);

    m_layout->addWidget(m_spinbox.get());


    v_refresh_data();

    m_layout->setStretch(0,1);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}






// Special 6
//============================================================
saklib::Qtlib::Attribute_Editor_Double_LE::Attribute_Editor_Double_LE(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_layout(),
    m_line_edit(),
    m_validator()

{
    shared_construction();
}
saklib::Qtlib::Attribute_Editor_Double_LE::Attribute_Editor_Double_LE(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, vector_index, parent),
    m_layout(),
    m_line_edit(),
    m_validator()
{
    shared_construction();
}
saklib::Qtlib::Attribute_Editor_Double_LE::~Attribute_Editor_Double_LE() = default;


void saklib::Qtlib::Attribute_Editor_Double_LE::v_refresh_data()
{
    qDebug() << "v_refresh_data()";
    qDebug() << "double value = " << to_qstring(attribute_value<Double>());
    m_line_edit->setText(to_qstring(attribute_value<Double>()));
    qDebug() << "text value = " << m_line_edit->text();
}

void saklib::Qtlib::Attribute_Editor_Double_LE::v_editing_finished()
{
    qDebug() << "v_editing_finished()";
    QString l_text = m_line_edit->text();
    int l_pos{0};
    qDebug() << "text value = " << l_text;
    qDebug() << "validator result = " << m_validator->validate(l_text, l_pos);

    Double entry{from_qstring<Double>(m_line_edit->text())};
    Double current{this->attribute_value<Double>()};

    qDebug() << "entry == current value = " << ( entry == current);
    if (entry != current)
    {
        if (is_vector_component())
        {
            project_widget()->project_manager().undoable_attribute_vector_set_at<Double>(attributeid(), vector_index(), from_qstring<Double>(m_line_edit->text()));
        }
        else
        {
            project_widget()->project_manager().undoable_attribute_set_value<Double>(attributeid(), from_qstring<Double>(m_line_edit->text()));
        }
    }
    else
    {
        v_refresh_data(); // report change failure somehow?
    }
}

void saklib::Qtlib::Attribute_Editor_Double_LE::shared_construction()
{
    m_layout = make_quptr<QHBoxLayout>();

    m_line_edit = make_quptr<QLineEdit>();
    m_validator = make_quptr<QDoubleValidator>();

    m_validator->setBottom(std::numeric_limits<Double>::lowest());
    m_validator->setTop(std::numeric_limits<Double>::max());
    //m_validator->setDecimals();
    //m_validator->setNotation(QDoubleValidator::StandardNotation);
    m_validator->setNotation(QDoubleValidator::ScientificNotation);

    Attribute_Type<Double>::stored_type_constraint const* lp_constraint = nullptr;

    if (is_vector_component())
    {
        lp_constraint = attribute_type_cast<std::vector<Double>>(project_widget()->project_manager().attribute(attributeid()))->value_constraint();
    }
    else
    {
        lp_constraint = attribute_type_cast<Double>(project_widget()->project_manager().attribute(attributeid()))->constraint();
    }

    if (lp_constraint && lp_constraint->has_min_value())
    {
        m_validator->setBottom(lp_constraint->min_value());
    }
    else
    {
        m_validator->setBottom(std::numeric_limits<Double>::lowest());
    }
    qDebug() << "validator bottom = " << to_qstring(m_validator->bottom());

    if (lp_constraint && lp_constraint->has_max_value())
    {
        m_validator->setTop(lp_constraint->max_value());
    }
    else
    {
        m_validator->setTop(std::numeric_limits<Double>::max());
    }
    qDebug() << "validator top = " << to_qstring(m_validator->top());

    if (lp_constraint && lp_constraint->has_decimal_places())
    {
        m_validator->setDecimals(lp_constraint->decimal_places());
    }
    else
    {
        //m_validator->setDecimals(std::numeric_limits<Double>::max_digits10);
        m_validator->setDecimals(1000);
    }
    qDebug() << "validator decimals = " << to_qstring(m_validator->decimals());

    m_line_edit->setValidator(m_validator.get());

    QObject::connect(m_line_edit.get(), &QLineEdit::editingFinished,
                     this, &Attribute_Editor_Double_LE::v_editing_finished);

    m_layout->addWidget(m_line_edit.get());



    v_refresh_data();

    m_layout->setStretch(0,1);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
