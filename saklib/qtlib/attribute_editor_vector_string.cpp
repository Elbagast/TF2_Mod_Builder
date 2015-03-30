#include "attribute_editor_vector_string.h"
#include "attribute_editor_string.h"

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Vector_String::Attribute_Editor_Vector_String(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor_Vector(project_widget, attributeid, parent)
{
}
Saklib::Qtlib::Attribute_Editor_Vector_String::~Attribute_Editor_Vector_String() = default;

// make an appropriately typed component widget
Saklib::Uptr<Saklib::Qtlib::Attribute_Editor> Saklib::Qtlib::Attribute_Editor_Vector_String::make_component_widget(size_type index) const
{
    return Uptr<Attribute_Editor>(new Attribute_Editor_String(project_widget(), attributeid(), index));
}

void Saklib::Qtlib::Attribute_Editor_Vector_String::slot_append()
{

}
