#include "attribute_editor_vector_elementid.h"
#include "attribute_editor_elementid.h"

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Vector_ElementID::Attribute_Editor_Vector_ElementID(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor_Vector(project_widget, attributeid, parent)
{
}
Saklib::Qtlib::Attribute_Editor_Vector_ElementID::~Attribute_Editor_Vector_ElementID() = default;

// make an appropriately typed component widget
Saklib::Uptr<Saklib::Qtlib::Attribute_Editor> Saklib::Qtlib::Attribute_Editor_Vector_ElementID::make_component_widget(size_type index) const
{
    return Uptr<Attribute_Editor>(new Attribute_Editor_ElementID(project_widget(), attributeid(), index));
}

void Saklib::Qtlib::Attribute_Editor_Vector_ElementID::slot_append()
{

}
