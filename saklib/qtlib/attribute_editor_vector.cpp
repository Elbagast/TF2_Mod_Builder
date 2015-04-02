#include "attribute_editor_vector.h"

#include "attribute_editor_elementid.h"

#include "project_widget.h"
#include "../project_manager.h"
#include "qstring_operations.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Vector::Attribute_Editor_Vector(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    //mp_element_widget(parent),
    m_append_button(std::make_unique<QPushButton>("Append...")),
    m_layout(std::make_unique<QVBoxLayout>()),
    m_component_layout(std::make_unique<QVBoxLayout>()),
    m_vector_widgets()
{
    QObject::connect(m_append_button.get(), &QPushButton::clicked,
                     this, &Attribute_Editor_Vector::slot_append);

    m_append_button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_layout->addLayout(m_component_layout.get());

    m_layout->addWidget(m_append_button.get());
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSizeConstraint(QLayout::SetFixedSize); // resize whenever the size changes...
    this->setLayout(m_layout.get());

    this->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(this, &QWidget::customContextMenuRequested,
                     this, &Attribute_Editor_Vector::slot_custom_context_menu);

    v_refresh_data();
}

Saklib::Qtlib::Attribute_Editor_Vector::~Attribute_Editor_Vector()
{
    m_layout->removeWidget(m_append_button.get());
    m_append_button->setParent(nullptr);
    for (auto const& widget : m_vector_widgets)
    {
        m_component_layout->removeWidget(widget.get());
        widget->setParent(nullptr);
    }
    m_vector_widgets.clear();
}


Saklib::size_type Saklib::Qtlib::Attribute_Editor_Vector::attribute_vector_size() const
{
    return this->project_widget()->project_manager().any_attribute_vector_size(attributeid());
}

void Saklib::Qtlib::Attribute_Editor_Vector::v_refresh_data()
{
    // We have a vector of widgets as long as the vector in the attribute....
    // therefore
    // sometimes this will be called when there has been a change in size,
    // and other times there haven't been
    auto data_count = attribute_vector_size();
    auto widget_count = m_vector_widgets.size();

    if (data_count > widget_count)
    {
        // make more widgets for each vector item that needs one
        for (size_type index = widget_count; index != data_count; ++index)
        {
            m_vector_widgets.push_back(make_Attribute_Editor(project_widget(), attributeid(), index));
            m_component_layout->addWidget(m_vector_widgets.back().get());
        }
    }
    else if (data_count < widget_count)
    {
        // remove widgets from the end and delete them
        while (m_vector_widgets.size() != data_count)
        {
            m_component_layout->removeWidget(m_vector_widgets.back().get());
            m_vector_widgets.pop_back();
        }
    }

    for (auto& vector_widget : m_vector_widgets)
    {
        vector_widget->refresh_data();
    }
}

void Saklib::Qtlib::Attribute_Editor_Vector::slot_custom_context_menu(QPoint const& pos)
{
    auto menu_position = this->mapToGlobal(pos);
    QMenu context_menu{};
    context_menu.addAction("Attribute_Editor_Vector");
    context_menu.exec(menu_position);
}
