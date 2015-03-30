#include "attribute_editor_vector_int.h"
#include "attribute_editor_int.h"
#include "project_widget.h"

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Vector_Int::Attribute_Editor_Vector_Int(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor_Vector(project_widget, attributeid, parent)
{
}
Saklib::Qtlib::Attribute_Editor_Vector_Int::~Attribute_Editor_Vector_Int() = default;

// make an appropriately typed component widget
Saklib::Uptr<Saklib::Qtlib::Attribute_Editor> Saklib::Qtlib::Attribute_Editor_Vector_Int::make_component_widget(size_type index) const
{
    return Uptr<Attribute_Editor>(new Attribute_Editor_Int(project_widget(), attributeid(), index));
}

void Saklib::Qtlib::Attribute_Editor_Vector_Int::slot_append()
{
    project_widget()->undoable_attribute_vector_push_back(attributeid(), Int(0));
}
