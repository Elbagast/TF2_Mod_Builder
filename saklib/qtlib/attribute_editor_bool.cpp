#include "attribute_editor_bool.h"
#include "project_widget.h"
#include <QCheckBox>
#include <QHBoxLayout>

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Bool::Attribute_Editor_Bool(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_checkbox(nullptr),
    m_layout(nullptr)
{
    shared_construction();
}
Saklib::Qtlib::Attribute_Editor_Bool::Attribute_Editor_Bool(Project_Widget*const project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, vector_index, parent),
    m_checkbox(nullptr),
    m_layout(nullptr)
{
    shared_construction();
}

Saklib::Qtlib::Attribute_Editor_Bool::~Attribute_Editor_Bool() = default;


void Saklib::Qtlib::Attribute_Editor_Bool::v_refresh_data()
{
    Bool data = attribute_value<Bool>();
    m_checkbox->setChecked(data);
    m_checkbox->setText(data ? "True" : "False");
}

void Saklib::Qtlib::Attribute_Editor_Bool::slot_clicked()
{
    if (is_vector_component())
        project_widget()->undoable_attribute_vector_set_at<Bool>(attributeid(), vector_index(), m_checkbox->isChecked());
    else
        project_widget()->undoable_attribute_set_value<Bool>(attributeid(), m_checkbox->isChecked());
}

void Saklib::Qtlib::Attribute_Editor_Bool::shared_construction()
{
    m_checkbox = std::make_unique<QCheckBox>();
    m_layout = std::make_unique<QHBoxLayout>();

    v_refresh_data();

    QObject::connect(m_checkbox.get(), &QCheckBox::clicked,
                     this, &Attribute_Editor_Bool::slot_clicked);

    m_layout->addWidget(m_checkbox.get());
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
