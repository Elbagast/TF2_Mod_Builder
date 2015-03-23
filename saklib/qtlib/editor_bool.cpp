#include "editor_bool.h"
#include "../command_history.h"
#include "../attribute_type.h"
#include <QCheckBox>

// Special 6
//============================================================
Saklib::Qtlib::Editor_Bool::Editor_Bool(Attribute_Type<Bool>* attribute_type, Command_History& command_history, QWidget* parent):
    Attribute_Editor(parent),
    mp_attribute_type(attribute_type),
    m_command_history(command_history),
    m_checkbox(new QCheckBox(this))
{
    m_checkbox->setChecked(mp_attribute_type->get());

    QObject::connect(m_checkbox.get(), &QCheckBox::clicked,
                     this, &Editor_Bool::slot_clicked);
}
Saklib::Qtlib::Editor_Bool::~Editor_Bool() = default;


void Saklib::Qtlib::Editor_Bool::v_refresh_data()
{
    if (m_checkbox->isChecked() != mp_attribute_type->get())
    {
        // block signals?
        m_checkbox->setChecked(mp_attribute_type->get());
    }
}

void Saklib::Qtlib::Editor_Bool::slot_clicked()
{
    m_command_history.emplace_execute<Command_Editor_Set_Attribute_Bool>(m_checkbox.get(), mp_attribute_type);
}


Saklib::Qtlib::Command_Editor_Set_Attribute_Bool::Command_Editor_Set_Attribute_Bool(QCheckBox* editor, Attribute_Type<Bool>* attribute_type):
    mp_editor(editor),
    mp_attribute_type(attribute_type),
    m_old_value(attribute_type->get()),
    m_new_value(editor->isChecked())
{}
Saklib::Qtlib::Command_Editor_Set_Attribute_Bool::~Command_Editor_Set_Attribute_Bool() = default;

void Saklib::Qtlib::Command_Editor_Set_Attribute_Bool::v_execute()
{
    mp_attribute_type->set(m_new_value);
    mp_editor->setChecked(m_new_value);
}

void Saklib::Qtlib::Command_Editor_Set_Attribute_Bool::v_unexecute()
{
    mp_attribute_type->set(m_old_value);
    mp_editor->setChecked(m_old_value);
}
