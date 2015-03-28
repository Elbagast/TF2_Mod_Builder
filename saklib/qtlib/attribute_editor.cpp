#include "attribute_editor.h"

#include "../types.h"
#include "project_widget.h"
#include "attribute_editor_bool.h"
#include "attribute_editor_int.h"
#include "attribute_editor_double.h"
#include "attribute_editor_string.h"
#include "attribute_editor_elementid.h"

#include "attribute_editor_vector_elementid.h"

#include <QLabel>
#include <QHBoxLayout>

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor::Attribute_Editor(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    QWidget(parent),
    mp_project_widget(project_widget),
    m_attributeid(attributeid)
{
    assert(mp_project_widget);
    assert(mp_project_widget->is_valid(attributeid));
}
Saklib::Qtlib::Attribute_Editor::~Attribute_Editor() = default;


// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Dummy::Attribute_Editor_Dummy(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_label(new QLabel("DUMMY EDITOR", this)),
    m_layout(new QHBoxLayout)
{
    m_layout->addWidget(m_label.get());
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
}
Saklib::Qtlib::Attribute_Editor_Dummy::~Attribute_Editor_Dummy() = default;


// Function with a typeswitch
Saklib::Uptr<Saklib::Qtlib::Attribute_Editor> Saklib::Qtlib::make_Attribute_Editor(Project_Widget*const project_widget, AttributeID attributeid)
{
    assert(project_widget);
    assert(project_widget->is_valid(attributeid));

    switch (project_widget->attribute_type_enum(attributeid))
    {
    case Type_Enum::Bool:            return Uptr<Attribute_Editor>(new Attribute_Editor_Bool(project_widget, attributeid));
    case Type_Enum::Int:             return Uptr<Attribute_Editor>(new Attribute_Editor_Int(project_widget, attributeid));
    case Type_Enum::Double:          return Uptr<Attribute_Editor>(new Attribute_Editor_Double(project_widget, attributeid));
    case Type_Enum::String:          return Uptr<Attribute_Editor>(new Attribute_Editor_String(project_widget, attributeid));
    //case Type_Enum::Path:            return Uptr<Attribute_Editor>(new Attribute_Editor_Path(project_widget, attributeid));
    case Type_Enum::ElementID:       return Uptr<Attribute_Editor>(new Attribute_Editor_ElementID(project_widget, attributeid));

    //case Type_Enum::Vector_Bool:      return Uptr<Attribute_Editor>(new Attribute_Editor_Vector_Bool(project_widget, attributeid));
    //case Type_Enum::Vector_Int:       return Uptr<Attribute_Editor>(new Attribute_Editor_Vector_Int(project_widget, attributeid));
    //case Type_Enum::Vector_Double:    return Uptr<Attribute_Editor>(new Attribute_Editor_Vector_Double(project_widget, attributeid));
    //case Type_Enum::Vector_String:    return Uptr<Attribute_Editor>(new Attribute_Editor_Vector_String(project_widget, attributeid));
    //case Type_Enum::Vector_Path:      return Uptr<Attribute_Editor>(new Attribute_Editor_Vector_Path(project_widget, attributeid));
    case Type_Enum::Vector_ElementID: return Uptr<Attribute_Editor>(new Attribute_Editor_Vector_ElementID(project_widget, attributeid));

    //default:                         assert(false); return Uptr<Attribute_Editor>(nullptr);
    default:                        return Uptr<Attribute_Editor>(new Attribute_Editor_Dummy(project_widget, attributeid));
    }
}
