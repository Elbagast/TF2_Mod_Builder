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
Saklib::Qtlib::Attribute_Editor_Vector::Attribute_Editor_Vector(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    //mp_element_widget(parent),

    m_layout(make_quptr<QVBoxLayout>()),
    m_component_layout(make_quptr<QVBoxLayout>()),
    m_button_layout(make_quptr<QHBoxLayout>()),
    m_append_button(make_quptr<QPushButton>("Append...")),
    m_clear_button(make_quptr<QPushButton>("Clear")),
    m_vector_widgets()
{
    m_append_button->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    QObject::connect(m_append_button.get(), &QPushButton::clicked,
                     this, &Attribute_Editor_Vector::slot_append);

    m_clear_button->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    QObject::connect(m_clear_button.get(), &QPushButton::clicked,
                     this, &Attribute_Editor_Vector::slot_clear);


    //m_append_button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_button_layout->addWidget(m_append_button.get());
    m_button_layout->addWidget(m_clear_button.get());
    m_button_layout->addStretch();
    m_button_layout->setSpacing(0);
    m_button_layout->setContentsMargins(0,0,0,0);

    m_layout->addLayout(m_component_layout.get());
    m_layout->addLayout(m_button_layout.get());
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    //m_layout->setSizeConstraint(QLayout::SetFixedSize); // resize whenever the size changes...
    this->setLayout(m_layout.get());

    this->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(this, &QWidget::customContextMenuRequested,
                     this, &Attribute_Editor_Vector::slot_custom_context_menu);

    v_refresh_data();
}

Saklib::Qtlib::Attribute_Editor_Vector::~Attribute_Editor_Vector() = default;


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
            m_vector_widgets.push_back(make_quptr<Attribute_Editor_Vector_Component>(project_widget(), attributeid(), index, this));
            m_vector_widgets.back().get()->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );
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


// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Vector_Component::Attribute_Editor_Vector_Component(Project_Widget* project_widget, AttributeID attributeid, size_type index, Attribute_Editor_Vector* parent):
    QWidget(parent),
    mp_parent(parent),
    m_layout(make_quptr<QHBoxLayout>()),

    m_move_button_layout(make_quptr<QVBoxLayout>()),
    m_move_up_button(make_quptr<QPushButton>()),
    m_move_down_button(make_quptr<QPushButton>()),

    m_other_button_layout(make_quptr<QVBoxLayout>()),
    m_insert_button(make_quptr<QPushButton>()),
    m_remove_button(make_quptr<QPushButton>()),

    m_editor(make_Attribute_Editor(project_widget, attributeid, index))
{
    m_move_up_button->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    m_move_up_button->setText("Move Up");
    //m_move_up_button->setText(QString::fromUtf8("\ucb84"));
    //m_move_up_button->setText(QString::fromUtf8("∧"));
    //m_move_up_button->setText(QString::fromStdWString(L"∧"));
    QObject::connect(m_move_up_button.get(), &QPushButton::clicked,
                     this, &Attribute_Editor_Vector_Component::slot_move_up);

    m_move_down_button->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    m_move_down_button->setText("Move Down");
    //m_move_down_button->setText(QString::fromUtf8("\ucb85"));
    //m_move_up_button->setText(QString::fromStdWString(L"\ucb85"));
    QObject::connect(m_move_down_button.get(), &QPushButton::clicked,
                     this, &Attribute_Editor_Vector_Component::slot_move_down);

    m_move_button_layout->addWidget(m_move_up_button.get());
    m_move_button_layout->addWidget(m_move_down_button.get());
    m_move_button_layout->setSpacing(0);
    m_move_button_layout->setContentsMargins(0,0,0,0);

    m_insert_button->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    m_insert_button->setText("Insert Before");
    QObject::connect(m_insert_button.get(), &QPushButton::clicked,
                     this, &Attribute_Editor_Vector_Component::slot_insert_before);

    m_remove_button->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
    m_remove_button->setText("Remove");
    QObject::connect(m_remove_button.get(), &QPushButton::clicked,
                     this, &Attribute_Editor_Vector_Component::slot_remove);

    m_other_button_layout->addWidget(m_insert_button.get());
    m_other_button_layout->addWidget(m_remove_button.get());
    m_other_button_layout->setSpacing(0);
    m_other_button_layout->setContentsMargins(0,0,0,0);

    m_editor->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum );

    m_layout->addLayout(m_move_button_layout.get());
    m_layout->addWidget(m_editor.get());
    m_layout->addLayout(m_other_button_layout.get());

    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
}

Saklib::Qtlib::Attribute_Editor_Vector_Component::~Attribute_Editor_Vector_Component() = default;


void Saklib::Qtlib::Attribute_Editor_Vector_Component::slot_insert_before()
{
    mp_parent->slot_insert_at(vector_index());
}


void Saklib::Qtlib::Attribute_Editor_Vector_Component::slot_remove()
{
    mp_parent->slot_remove_at(vector_index());
}

void Saklib::Qtlib::Attribute_Editor_Vector_Component::slot_move_up()
{
    mp_parent->slot_move_up(vector_index());
}

void Saklib::Qtlib::Attribute_Editor_Vector_Component::slot_move_down()
{
    mp_parent->slot_move_down(vector_index());
}
