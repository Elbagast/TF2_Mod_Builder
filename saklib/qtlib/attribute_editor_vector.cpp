#include "attribute_editor_vector.h"

#include "attribute_editor_elementid.h"

#include "project_widget.h"
#include "qstring_operations.h"

#include <QVBoxLayout>
#include <QPushButton>

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Vector::Attribute_Editor_Vector(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_append_button(std::make_unique<QPushButton>("Append...")),
    m_layout(std::make_unique<QVBoxLayout>()),
    m_vector_widgets()
{
    QObject::connect(m_append_button.get(), &QPushButton::clicked,
                     this, &Attribute_Editor_Vector::slot_append);

    m_append_button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_layout->addWidget(m_append_button.get());
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    v_refresh_data();
}

Saklib::Qtlib::Attribute_Editor_Vector::~Attribute_Editor_Vector()
{
    for (auto& widget : m_vector_widgets)
    {
        m_layout->removeWidget(widget.get());
        widget->setParent(nullptr);
    }
    m_vector_widgets.clear();
}


Saklib::size_type Saklib::Qtlib::Attribute_Editor_Vector::attribute_vector_size() const
{
    return this->project_widget()->attribute_vector_size(attributeid());
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
            m_vector_widgets.push_back(make_component_widget(index));
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
