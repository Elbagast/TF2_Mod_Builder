#include "element_widget.h"

#include "project_widget.h"
#include "../project_manager.h"

#include "attribute_editor.h"
#include "../element.h"
#include "../all_attributes.h"

#include "qstring_operations.h"

#include <QLabel>
//#include <QGridLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

//#include "editor_bool.h"

// Special 6
//============================================================
Saklib::Qtlib::Element_Widget::Element_Widget(Project_Widget* project_widget, ElementID elementid):
    QWidget(nullptr),
    mp_project_widget(project_widget),
    m_elementid(elementid),
    m_parentid(mp_project_widget->project_manager().element_parent(m_elementid)),

    m_self_header_layout(std::make_unique<QHBoxLayout>()),
    m_element_type_label(std::make_unique<QLabel>()),
    m_element_name_label(std::make_unique<QLabel>()),
    m_element_id_label(std::make_unique<QLabel>()),

    m_parent_id_label(std::make_unique<QLabel>()),

    //m_attribute_names(),
    //m_attribute_types(),
    m_attribute_layouts(),
    m_attribute_editors(),

    m_layout(std::make_unique<QVBoxLayout>()),

    m_parent_header_layout(std::make_unique<QHBoxLayout>()),
    m_attribute_layout(std::make_unique<QFormLayout>())

{
    // Really shouldn't have got here with an invalid ID
    assert(mp_project_widget->project_manager().is_valid(elementid));


    // Configure the labels

    // If the name is editable this type will get changed.
    m_element_name_label->setText(mp_project_widget->project_manager().element_name(m_elementid).c_str());

    m_element_type_label->setText(mp_project_widget->project_manager().element_type(m_elementid).c_str());

    m_element_id_label->setText(QString("ID: ").append(to_QString(m_elementid.value())));

    m_self_header_layout->addWidget(m_element_type_label.get());
    m_self_header_layout->addWidget(m_element_name_label.get());
    m_self_header_layout->addStretch();
    m_self_header_layout->addWidget(m_element_id_label.get());

    m_layout->addLayout(m_self_header_layout.get());

    //QString parent_label =
    m_parent_id_label = std::make_unique<QLabel>(to_QString(m_parentid.elementid().value()).append(" : ").append(to_QString(m_parentid.index())));

    // Add the widgets to the layout
    //int grid_row{0};

    //m_layout->addWidget(m_element_name_label.get());//, grid_row, 0);
    //m_layout->addWidget(m_element_type_label.get());//, ++grid_row, 0);
    //m_layout->addWidget(m_element_can_be_root_label.get());//, ++grid_row, 0);
    //m_layout->addWidget(m_element_id_label.get());//, ++grid_row, 0);
    //m_layout->addWidget(m_parent_id_label.get());//, ++grid_row, 0);
    //++grid_row;
    m_layout->addLayout(m_attribute_layout.get());
    {
        // scope to expire this reference
        Vector<Uptr<Attribute>> const& attributes = mp_project_widget->project_manager().element(m_elementid).attributes();
        for (size_type attribute_index = 0, end = attributes.size(); attribute_index != end; ++attribute_index)
        {
            // The Attribute we're working with
            Attribute const*const attribute{attributes.at(attribute_index).get()};
            // Make a AttributeID that refers to this Attribute
            AttributeID attributeid{m_elementid, attribute_index};

            // make and add editors
            QUptr<Attribute_Editor> editor{make_Attribute_Editor(mp_project_widget, attributeid)};
            QUptr<QHBoxLayout> layout{std::make_unique<QHBoxLayout>()};
            layout->addWidget(editor.get());
            //layout->addStretch();

            editor->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
            // Add it to the grid
            //m_layout->addWidget(editor.get(), grid_row, 2);

            m_attribute_layout->addRow(to_QString(attribute->name()), layout.get());

            // Store it
            m_attribute_editors.push_back(std::move(editor));
            m_attribute_layouts.push_back(std::move(layout));

            // Seperator Line?

            // next grid row and index
            //++grid_row;
        }
    }
    // This is the same as putting a vertical spacer at the bottom, the blank space
    // below the last row in the grid can be stretched down
    //m_layout->setRowStretch(++grid_row,1);
    m_attribute_layout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    m_attribute_layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    //m_attribute_layout->setSizeConstraint(QLayout::SetFixedSize); // resize whenever the size changes...
    m_layout->addStretch();
    //m_layout->setSizeConstraint(QLayout::SetFixedSize); // resize whenever the size changes...
    this->setLayout(m_layout.get());
    this->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
}

Saklib::Qtlib::Element_Widget::~Element_Widget() = default;

// Update the data displayed by this widget and its children
void Saklib::Qtlib::Element_Widget::refresh_data()
{
    m_element_name_label->setText(mp_project_widget->project_manager().element(m_elementid).name().c_str());
    m_parentid = mp_project_widget->project_manager().element_parent(m_elementid);
    m_parent_id_label->setText(to_QString(m_parentid.elementid().value()).append(" : ").append(to_QString(m_parentid.index())));
    for (auto& attribute_editor : m_attribute_editors)
    {
        attribute_editor->refresh_data();
    }
}

void Saklib::Qtlib::Element_Widget::refresh_data(size_type attribute_index)
{
    m_attribute_editors.at(attribute_index)->refresh_data();
}

