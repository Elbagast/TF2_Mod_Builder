#include "attribute_editor_bool.h"
#include "project_widget.h"
#include "../project_manager.h"
#include <QCheckBox>
#include <QHBoxLayout>

// Special 6
//============================================================
saklib::Qtlib::Attribute_Editor_Bool::Attribute_Editor_Bool(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_checkbox(nullptr),
    m_layout(nullptr)
{
    shared_construction();
}
saklib::Qtlib::Attribute_Editor_Bool::Attribute_Editor_Bool(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, vector_index, parent),
    m_checkbox(nullptr),
    m_layout(nullptr)
{
    shared_construction();
}

saklib::Qtlib::Attribute_Editor_Bool::~Attribute_Editor_Bool() = default;


void saklib::Qtlib::Attribute_Editor_Bool::v_refresh_data()
{
    Bool data = attribute_value<Bool>();
    m_checkbox->setChecked(data);
    m_checkbox->setText(data ? "True" : "False");
}

void saklib::Qtlib::Attribute_Editor_Bool::v_editing_finished()
{
    if (is_vector_component())
        project_widget()->project_manager().undoable_attribute_vector_set_at<Bool>(attributeid(), vector_index(), m_checkbox->isChecked());
    else
        project_widget()->project_manager().undoable_attribute_set_value<Bool>(attributeid(), m_checkbox->isChecked());
}

void saklib::Qtlib::Attribute_Editor_Bool::shared_construction()
{
    m_checkbox = make_quptr<QCheckBox>();
    m_layout = make_quptr<QHBoxLayout>();

    v_refresh_data();

    QObject::connect(m_checkbox.get(), &QCheckBox::clicked,
                     this, &Attribute_Editor_Bool::editing_finished);

    m_layout->addWidget(m_checkbox.get());
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}
