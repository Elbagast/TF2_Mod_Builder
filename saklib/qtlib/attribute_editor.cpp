#include "attribute_editor.h"

#include "../types.h"
#include "project_manager.h"
#include "attribute_editor_bool.h"
#include "attribute_editor_int.h"
#include "attribute_editor_double.h"

#include <QLabel>

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor::Attribute_Editor(Project_Manager& project_manager, AttributeID attributeid, QWidget* parent):
    QWidget(parent),
    mr_project_manager(project_manager),
    m_attributeid(attributeid)
{
    assert(project_manager.is_valid(attributeid));
}
Saklib::Qtlib::Attribute_Editor::~Attribute_Editor() = default;


// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Dummy::Attribute_Editor_Dummy(Project_Manager& project_manager, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_manager, attributeid, parent),
    m_label(new QLabel("DUMMY EDITOR", this))
{
}
Saklib::Qtlib::Attribute_Editor_Dummy::~Attribute_Editor_Dummy() = default;


// Function with a typeswitch
Saklib::Uptr<Saklib::Qtlib::Attribute_Editor> Saklib::Qtlib::make_Attribute_Editor(Project_Manager& project_manager, AttributeID attributeid)
{
    assert(project_manager.is_valid(attributeid));

    switch (project_manager.attribute_type_enum(attributeid))
    {
    case Type_Enum::Bool:            return Uptr<Attribute_Editor>(new Attribute_Editor_Bool(project_manager, attributeid));
    case Type_Enum::Int:             return Uptr<Attribute_Editor>(new Attribute_Editor_Int(project_manager, attributeid));
    case Type_Enum::Double:          return Uptr<Attribute_Editor>(new Attribute_Editor_Double(project_manager, attributeid));
    //case Type_Enum::String:          return Uptr<Attribute_Editor>(new Attribute_Editor_Bool(project_manager, attributeid));
    //case Type_Enum::Path:            return Uptr<Attribute_Editor>(new Attribute_Editor_String(project_manager, attributeid));
    //case Type_Enum::ElementID:       return Uptr<Attribute_Editor>(new Attribute_Editor_ElementID(project_manager, attributeid));

    //case Type_Enum::Vector_Bool:      return Uptr<Attribute_Editor>(new Attribute_Editor_Vector_Bool(project_manager, attributeid));
    //case Type_Enum::Vector_Int:       return Uptr<Attribute_Editor>(new Attribute_Editor_Vector_Int(project_manager, attributeid));
    //case Type_Enum::Vector_Double:    return Uptr<Attribute_Editor>(new Attribute_Editor_Vector_Double(project_manager, attributeid));
    //case Type_Enum::Vector_String:    return Uptr<Attribute_Editor>(new Attribute_Editor_Vector_String(project_manager, attributeid));
    //case Type_Enum::Vector_Path:      return Uptr<Attribute_Editor>(new Attribute_Editor_Vector_Path(project_manager, attributeid));
    //case Type_Enum::Vector_ElementID: return Uptr<Attribute_Editor>(new Attribute_Editor_Vector_ElementID(project_manager, attributeid));

    //default:                         assert(false); return Uptr<Attribute_Editor>(nullptr);
    default:                        return Uptr<Attribute_Editor>(new Attribute_Editor_Dummy(project_manager, attributeid));
    }
}
