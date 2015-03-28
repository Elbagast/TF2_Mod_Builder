#include "attribute_editor_vector_elementid.h"

#include "project_widget.h"
#include "qstring_operations.h"
#include "select_element_type_dialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>


// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Vector_ElementID::Attribute_Editor_Vector_ElementID(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor_Vector(project_widget, attributeid, parent)
{
}
Saklib::Qtlib::Attribute_Editor_Vector_ElementID::~Attribute_Editor_Vector_ElementID() = default;

// make an appropriately typed component widget
Saklib::Uptr<Saklib::Qtlib::Attribute_Editor_Vector_Component> Saklib::Qtlib::Attribute_Editor_Vector_ElementID::make_component_widget(size_type index) const
{
    return Uptr<Attribute_Editor_Vector_Component>{new Attribute_Editor_Vector_Component_ElementID(project_widget(), attributeid(), index)};
}





// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Vector_Component_ElementID::Attribute_Editor_Vector_Component_ElementID(Project_Widget*const project_widget,
                                                                                                        AttributeID attributeid,
                                                                                                        size_type index,
                                                                                                        QWidget* parent):
    Attribute_Editor_Vector_Component(project_widget, attributeid, index, parent),
    m_elementid(this->project_widget()->attribute_type_cast<Vector_ElementID>(this->attributeid())->at(index)),
    m_layout(std::make_unique<QHBoxLayout>()),
    m_button(std::make_unique<QPushButton>(button_text())),
    m_name_label(std::make_unique<QLabel>(name_label_text())),
    m_type_label(std::make_unique<QLabel>(type_label_text()))
{
    // If the ElementID is a valid value, make sure it's valid in the project_widget
    if (m_elementid.is_valid())
        assert(this->project_widget()->is_valid(m_elementid));

    QObject::connect(m_button.get(), &QPushButton::clicked,
                     this, &Attribute_Editor_Vector_Component_ElementID::slot_clicked);

    m_layout->addWidget(m_button.get());
    m_layout->addWidget(m_name_label.get());
    m_layout->addWidget(m_type_label.get());

    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
Saklib::Qtlib::Attribute_Editor_Vector_Component_ElementID::~Attribute_Editor_Vector_Component_ElementID() = default;

void Saklib::Qtlib::Attribute_Editor_Vector_Component_ElementID::v_refresh_data()
{
    auto const data_value = this->project_widget()->attribute_type_cast<Vector_ElementID>(this->attributeid())->at(this->index());
    if (m_elementid != data_value)
    {
        //refresh the representation
        m_elementid = data_value;
        m_button->setText(button_text());
        m_name_label->setText(name_label_text());
        m_type_label->setText(type_label_text());
    }
}

void Saklib::Qtlib::Attribute_Editor_Vector_Component_ElementID::slot_clicked()
{
    if (this->elementid().is_valid() && this->project_widget()->is_valid(this->elementid()))
    {
       this->project_widget()->open_editor(this->elementid());
    }
    else
    {
        // Get a list of types of Element that we can use
        auto element_types = Element::get_registered_types();

        // Make a dialog that asks the user to select one, floating above the project widget
        Select_Element_Type_Dialog dialog{element_types, this->project_widget()};

        // if the user selects one, make an Element of that type and assign it to the attribute
        if (dialog.exec() == QDialog::Accepted && !dialog.selected_element_type().empty())
        {
            ElementID new_element = project_widget()->make_element(dialog.selected_element_type());
            this->project_widget()->undoable_attribute_vector_set_value_at<ElementID>(this->attributeid(), this->index(), new_element);
        }
    }
}

// Internal
//============================================================
QString Saklib::Qtlib::Attribute_Editor_Vector_Component_ElementID::button_text() const
{
    if (m_elementid.is_valid() && project_widget()->is_valid(m_elementid))
    {
       return QString("Edit");
    }
    else
    {
        return QString("Make Element");
    }
}
QString Saklib::Qtlib::Attribute_Editor_Vector_Component_ElementID::name_label_text() const
{
    static QString const label_front{"Name: "};
    if (m_elementid.is_valid() && project_widget()->is_valid(m_elementid))
    {
        return label_front + to_QString(project_widget()->element_name(m_elementid));
    }
    else
    {
        return QString();
    }
}
QString Saklib::Qtlib::Attribute_Editor_Vector_Component_ElementID::type_label_text() const
{
    static QString const label_front{"Type: "};
    if (m_elementid.is_valid() && project_widget()->is_valid(m_elementid))
    {
        return label_front + to_QString(project_widget()->element_type(m_elementid));
    }
    else
    {
        return QString();
    }
}

/*
// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Vector_ElementID::Attribute_Editor_Vector_ElementID(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_append_button(std::make_unique<QPushButton>("Append Element...")),
    m_layout(std::make_unique<QVBoxLayout>()),
    m_vector_widgets()
{
    QObject::connect(m_append_button.get(), &QPushButton::clicked,
                     this, &Attribute_Editor_Vector_ElementID::slot_append);

    m_layout->addWidget(m_append_button.get());
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    v_refresh_data();
}

Saklib::Qtlib::Attribute_Editor_Vector_ElementID::~Attribute_Editor_Vector_ElementID() = default;

void Saklib::Qtlib::Attribute_Editor_Vector_ElementID::v_refresh_data()
{
    // We have a vector of widgets as long as the vector in the attribute....
    // therefore
    // sometimes this will be called when there has been a change in size,
    // and other times there haven't been
    auto data_count = project_widget()->attribute_type_cast<Vector_ElementID>(attributeid())->size();
    auto widget_count = m_vector_widgets.size();

    if (data_count > widget_count)
    {
        // make more widgets for each vector item that needs one
        for (size_type index = widget_count; index != data_count; ++index)
        {
            m_vector_widgets.push_back(std::make_unique<Attribute_Editor_Vector_Component_ElementID>(project_widget(), attributeid(), index));
            m_layout->insertWidget(static_cast<int>(index), m_vector_widgets.back().get());
        }
    }
    else if (data_count < widget_count)
    {
        // remove widgets from the end and delete them
        while (m_vector_widgets.size() != data_count)
        {
            m_layout->removeWidget(m_vector_widgets.back().get());
            m_vector_widgets.pop_back();
        }
    }

    for (auto& vector_widget : m_vector_widgets)
    {
        vector_widget->refresh_data();
    }
}

void Saklib::Qtlib::Attribute_Editor_Vector_ElementID::slot_append()
{

}
*/
