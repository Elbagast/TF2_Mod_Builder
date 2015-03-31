#include "element_widget.h"

#include "project_widget.h"
#include "attribute_editor.h"
#include "../element.h"
#include "../all_attributes.h"

#include "qstring_operations.h"

#include <QLabel>
//#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>

//#include "editor_bool.h"

// Special 6
//============================================================
Saklib::Qtlib::Element_Widget::Element_Widget(Project_Widget*const project_widget, ElementID elementid):
    QWidget(nullptr),
    mp_project_widget(project_widget),
    m_elementid(elementid),

    m_element_name_label(),
    m_element_type_label(),

    //m_attribute_names(),
    //m_attribute_types(),
    m_attribute_editors(),

    m_layout(std::make_unique<QVBoxLayout>()),
    m_attribute_layout(std::make_unique<QFormLayout>())

{
    // Really shouldn't have got here with an invalid ID
    assert(mp_project_widget->is_valid(elementid));

    // Configure the labels

    // If the name is editable this type will get changed.
    m_element_name_label.reset(new QLabel(mp_project_widget->element(m_elementid).name().c_str()));
    //m_element_name_label->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );

    m_element_type_label.reset(new QLabel(mp_project_widget->element(m_elementid).type().c_str()));
    //m_element_type_label->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );


    // Add the widgets to the layout
    //int grid_row{0};

    m_layout->addWidget(m_element_name_label.get());//, grid_row, 0);
    m_layout->addWidget(m_element_type_label.get());//, ++grid_row, 0);
    //++grid_row;
    m_layout->addLayout(m_attribute_layout.get());
    {
        // scope to expire this reference
        Vector<Uptr<Attribute>> const& attributes = mp_project_widget->element(m_elementid).attributes();
        for (size_type attribute_index = 0, end = attributes.size(); attribute_index != end; ++attribute_index)
        {
            // The Attribute we're working with
            Attribute const*const attribute{attributes.at(attribute_index).get()};
            // Make a AttributeID that refers to this Attribute
            AttributeID attributeid{m_elementid, attribute_index};

            // Make a label that is the Attribute name
            //auto name_label = std::make_unique<QLabel>(attribute->name().c_str());
            // Set sizing
            //name_label->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
            // Add it to the grid
           // m_layout->addWidget(name_label.get(), grid_row, 0);
            // Store the label
            //m_attribute_names.push_back(std::move(name_label));


            // Make a label that is the Attribute type
            //auto type_label = std::make_unique<QLabel>(attribute->type_string().c_str());
            // Set sizing
            //type_label->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
            // Add it to the grid
            //m_layout->addWidget(type_label.get(), grid_row, 1);
            // Store the label
            //m_attribute_types.push_back(std::move(type_label));


            // make and add editors
            Uptr<Attribute_Editor> editor{make_Attribute_Editor(mp_project_widget, attributeid)};

            editor->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
            // Add it to the grid
            //m_layout->addWidget(editor.get(), grid_row, 2);

            m_attribute_layout->addRow(to_QString(attribute->name()), editor.get());

            // Store it
            m_attribute_editors.push_back(std::move(editor));

            // Seperator Line?

            // next grid row and index
            //++grid_row;
        }
    }
    // This is the same as putting a vertical spacer at the bottom, the blank space
    // below the last row in the grid can be stretched down
    //m_layout->setRowStretch(++grid_row,1);
    m_attribute_layout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    m_attribute_layout->setSizeConstraint(QLayout::SetFixedSize); // resize whenever the size changes...
    m_layout->setSizeConstraint(QLayout::SetFixedSize); // resize whenever the size changes...
    setLayout(m_layout.get());
    this->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
}

Saklib::Qtlib::Element_Widget::~Element_Widget()
{
    // Clear these up first
    //m_attribute_names.clear();
    //m_attribute_types.clear();
    m_attribute_editors.clear();
}

// Update the data displayed by this widget and its children
void Saklib::Qtlib::Element_Widget::refresh_data()
{
    m_element_name_label->setText(mp_project_widget->element(m_elementid).name().c_str());
    for (auto& attribute_editor : m_attribute_editors)
        attribute_editor->refresh_data();

}

void Saklib::Qtlib::Element_Widget::refresh_data(size_type attribute_index)
{
    m_attribute_editors.at(attribute_index)->refresh_data();
}

