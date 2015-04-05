#include "attribute_editor_elementid.h"

#include "project_widget.h"
#include "../project_manager.h"

#include "qstring_operations.h"
#include "select_element_type_dialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_ElementID::Attribute_Editor_ElementID(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_elementid(),
    m_layout(),
    m_button(),
    m_name_label(),
    m_type_label()
{
    shared_construction();
}
Saklib::Qtlib::Attribute_Editor_ElementID::Attribute_Editor_ElementID(Project_Widget*const project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, vector_index, parent),
    m_elementid(),
    m_layout(),
    m_button(),
    m_name_label(),
    m_type_label()
{
    shared_construction();
}
Saklib::Qtlib::Attribute_Editor_ElementID::~Attribute_Editor_ElementID() = default;


void Saklib::Qtlib::Attribute_Editor_ElementID::v_refresh_data()
{
    auto const data_value = attribute_value<ElementID>();
    if (m_elementid != data_value)
    {
        //refresh the representation
        m_elementid = data_value;
        m_button->setText(button_text());
        m_name_label->setText(name_label_text());
        m_type_label->setText(type_label_text());
    }
}

void Saklib::Qtlib::Attribute_Editor_ElementID::slot_clicked()
{
    if (m_elementid.is_valid() && project_widget()->project_manager().is_valid(m_elementid))
    {
       project_widget()->open_editor(m_elementid);
    }
    else
    {
        // Get a list of types of Element that we can use
        auto element_types = project_widget()->project_manager().all_registered_element_types();

        // Make a dialog that asks the user to select one, floating above the project widget
        Select_Element_Type_Dialog dialog{element_types, project_widget()};

        // if the user selects one, make an Element of that type and assign it to the attribute
        if (dialog.exec() == QDialog::Accepted && !dialog.selected_element_type().empty())
        {
            ElementID new_element = project_widget()->project_manager().make_element(dialog.selected_element_type());
            if (is_vector_component())
                project_widget()->project_manager().undoable_attribute_vector_set_at<ElementID>(attributeid(), vector_index(), new_element);
            else
                project_widget()->project_manager().undoable_attribute_set_value<ElementID>(attributeid(), new_element);
        }
    }
}


// Internal
//============================================================
QString Saklib::Qtlib::Attribute_Editor_ElementID::button_text() const
{
    if (m_elementid.is_valid() && project_widget()->project_manager().is_valid(m_elementid))
    {
       return QString("Edit");
    }
    else
    {
        return QString("Make Element");
    }
}
QString Saklib::Qtlib::Attribute_Editor_ElementID::name_label_text() const
{
    static QString const label_front{"Name: "};
    if (m_elementid.is_valid() && project_widget()->project_manager().is_valid(m_elementid))
    {
        return label_front + to_QString(project_widget()->project_manager().element_name(m_elementid));
    }
    else
    {
        return QString();
    }
}
QString Saklib::Qtlib::Attribute_Editor_ElementID::type_label_text() const
{
    static QString const label_front{"Type: "};
    if (m_elementid.is_valid() && project_widget()->project_manager().is_valid(m_elementid))
    {
        return label_front + to_QString(project_widget()->project_manager().element_type(m_elementid));
    }
    else
    {
        return QString();
    }
}

void Saklib::Qtlib::Attribute_Editor_ElementID::shared_construction()
{
    m_elementid = attribute_value<ElementID>();

    m_layout = make_quptr<QHBoxLayout>();
    m_button = make_quptr<QPushButton>(button_text());
    m_name_label = make_quptr<QLabel>(name_label_text());
    m_type_label = make_quptr<QLabel>(type_label_text());

    // If the ElementID is a valid value, make sure it's valid in the project_widget
    if (m_elementid.is_valid())
        assert(this->project_widget()->project_manager().is_valid(m_elementid));

    QObject::connect(m_button.get(), &QPushButton::clicked,
                     this, &Attribute_Editor_ElementID::slot_clicked);

    m_layout->addWidget(m_button.get());
    m_layout->addWidget(m_name_label.get());
    m_layout->addWidget(m_type_label.get());

    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}


