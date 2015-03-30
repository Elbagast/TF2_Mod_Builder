#include "attribute_editor_vector_double.h"
#include "attribute_editor_double.h"

// Special 6
//============================================================
Saklib::Qtlib::Attribute_Editor_Vector_Double::Attribute_Editor_Vector_Double(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor_Vector(project_widget, attributeid, parent)
{
}
Saklib::Qtlib::Attribute_Editor_Vector_Double::~Attribute_Editor_Vector_Double() = default;

// make an appropriately typed component widget
Saklib::Uptr<Saklib::Qtlib::Attribute_Editor> Saklib::Qtlib::Attribute_Editor_Vector_Double::make_component_widget(size_type index) const
{
    return Uptr<Attribute_Editor>(new Attribute_Editor_Double(project_widget(), attributeid(), index));
}

void Saklib::Qtlib::Attribute_Editor_Vector_Double::slot_append()
{

}
