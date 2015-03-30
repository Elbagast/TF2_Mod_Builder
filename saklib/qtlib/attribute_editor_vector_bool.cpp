#include "attribute_editor_vector_bool.h"
#include "attribute_editor_bool.h"

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Vector_Bool::Attribute_Editor_Vector_Bool(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor_Vector(project_widget, attributeid, parent)
{
}
Saklib::Qtlib::Attribute_Editor_Vector_Bool::~Attribute_Editor_Vector_Bool() = default;

// make an appropriately typed component widget
Saklib::Uptr<Saklib::Qtlib::Attribute_Editor> Saklib::Qtlib::Attribute_Editor_Vector_Bool::make_component_widget(size_type index) const
{
    return Uptr<Attribute_Editor>(new Attribute_Editor_Bool(project_widget(), attributeid(), index));
}

void Saklib::Qtlib::Attribute_Editor_Vector_Bool::slot_append()
{

}
