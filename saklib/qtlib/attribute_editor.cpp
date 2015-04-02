#include "attribute_editor.h"

#include "../types.h"
#include "project_widget.h"
#include "../project_manager.h"

#include "attribute_editor_bool.h"
#include "attribute_editor_int.h"
#include "attribute_editor_double.h"
#include "attribute_editor_string.h"
#include "attribute_editor_elementid.h"

#include "attribute_editor_vector_type.h"
//#include "attribute_editor_vector_bool.h"
//#include "attribute_editor_vector_int.h"
//#include "attribute_editor_vector_double.h"
//#include "attribute_editor_vector_string.h"
#include "attribute_editor_vector_elementid.h"

#include <QLabel>
#include <QHBoxLayout>

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor::Attribute_Editor(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    QWidget(parent),
    mp_project_widget(project_widget),
    m_attributeid(attributeid),
    m_attribute_type(mp_project_widget->project_manager().attribute_type_enum(attributeid)),
    m_vector_index(0),
    m_is_vector_component(false)
{
    assert(mp_project_widget);
    assert(mp_project_widget->project_manager().is_valid(attributeid));
}

Saklib::Qtlib::Attribute_Editor::Attribute_Editor(Project_Widget*const project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent):
    QWidget(parent),
    mp_project_widget(project_widget),
    m_attributeid(attributeid),
    m_attribute_type(mp_project_widget->project_manager().attribute_type_enum(attributeid)),
    m_vector_index(vector_index),
    m_is_vector_component(true)
{
    assert(mp_project_widget);
    assert(mp_project_widget->project_manager().is_valid(attributeid));
}

Saklib::Qtlib::Attribute_Editor::~Attribute_Editor() = default;


// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Dummy::Attribute_Editor_Dummy(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor(project_widget, attributeid, parent),
    m_label(make_quptr<QLabel>("DUMMY EDITOR", this)),
    m_layout(make_quptr<QHBoxLayout>())
{
    m_layout->addWidget(m_label.get());
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout.get());
}
Saklib::Qtlib::Attribute_Editor_Dummy::~Attribute_Editor_Dummy() = default;




// Function with a typeswitch
Saklib::Qtlib::QUptr<Saklib::Qtlib::Attribute_Editor> Saklib::Qtlib::make_Attribute_Editor(Project_Widget*const project_widget, AttributeID attributeid)
{
    assert(project_widget);
    assert(project_widget->project_manager().is_valid(attributeid));

    switch (project_widget->project_manager().attribute_type_enum(attributeid))
    {
    case Type_Enum::Bool:            return QUptr<Attribute_Editor>(new Attribute_Editor_Bool(project_widget, attributeid));
    case Type_Enum::Int:             return QUptr<Attribute_Editor>(new Attribute_Editor_Int(project_widget, attributeid));
    case Type_Enum::Double:          return QUptr<Attribute_Editor>(new Attribute_Editor_Double(project_widget, attributeid));
    case Type_Enum::String:          return QUptr<Attribute_Editor>(new Attribute_Editor_String(project_widget, attributeid));
    //case Type_Enum::Path:            return QUptr<Attribute_Editor>(new Attribute_Editor_Path(project_widget, attributeid));
    case Type_Enum::ElementID:       return QUptr<Attribute_Editor>(new Attribute_Editor_ElementID(project_widget, attributeid));

    case Type_Enum::Vector_Bool:      return QUptr<Attribute_Editor>(new Attribute_Editor_Vector_Type<Bool>(project_widget, attributeid));
    case Type_Enum::Vector_Int:       return QUptr<Attribute_Editor>(new Attribute_Editor_Vector_Type<Int>(project_widget, attributeid));
    case Type_Enum::Vector_Double:    return QUptr<Attribute_Editor>(new Attribute_Editor_Vector_Type<Double>(project_widget, attributeid));
    case Type_Enum::Vector_String:    return QUptr<Attribute_Editor>(new Attribute_Editor_Vector_Type<String>(project_widget, attributeid));
    //case Type_Enum::Vector_Path:      return QUptr<Attribute_Editor>(new Attribute_Editor_Vector_Type<Path>(project_widget, attributeid));
    case Type_Enum::Vector_ElementID: return QUptr<Attribute_Editor>(new Attribute_Editor_Vector_Type<ElementID>(project_widget, attributeid));

    //default:                         assert(false); return QUptr<Attribute_Editor>(nullptr);
    default:                        return QUptr<Attribute_Editor>(new Attribute_Editor_Dummy(project_widget, attributeid));
    }
}

// Function with a typeswitch
Saklib::Qtlib::QUptr<Saklib::Qtlib::Attribute_Editor> Saklib::Qtlib::make_Attribute_Editor(Project_Widget*const project_widget, AttributeID attributeid, size_type vector_index)
{
    assert(project_widget);
    assert(project_widget->project_manager().is_valid(attributeid));

    switch (project_widget->project_manager().attribute_type_enum(attributeid))
    {
    case Type_Enum::Vector_Bool:            return QUptr<Attribute_Editor>(new Attribute_Editor_Bool(project_widget, attributeid, vector_index));
    case Type_Enum::Vector_Int:             return QUptr<Attribute_Editor>(new Attribute_Editor_Int(project_widget, attributeid, vector_index));
    case Type_Enum::Vector_Double:          return QUptr<Attribute_Editor>(new Attribute_Editor_Double(project_widget, attributeid, vector_index));
    case Type_Enum::Vector_String:          return QUptr<Attribute_Editor>(new Attribute_Editor_String(project_widget, attributeid, vector_index));
    //case Type_Enum::Vector_Path:            return QUptr<Attribute_Editor>(new Attribute_Editor_Path(project_widget, attributeid, vector_index));
    case Type_Enum::Vector_ElementID:       return QUptr<Attribute_Editor>(new Attribute_Editor_ElementID(project_widget, attributeid, vector_index));

    //default:                         assert(false); return QUptr<Attribute_Editor>(nullptr);
    default:                        return QUptr<Attribute_Editor>(new Attribute_Editor_Dummy(project_widget, attributeid));
    }
}
