#include "attribute_editor_vector_elementid.h"
#include "attribute_editor_elementid.h"
#include "project_widget.h"
#include "select_element_type_dialog.h"

// Special 6
//============================================================
//template<>
Saklib::Qtlib::Attribute_Editor_Vector_Type<Saklib::ElementID>::Attribute_Editor_Vector_Type(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor_Vector(project_widget, attributeid, parent)
{
}
//template<>
Saklib::Qtlib::Attribute_Editor_Vector_Type<Saklib::ElementID>::~Attribute_Editor_Vector_Type() = default;

//template<>
void Saklib::Qtlib::Attribute_Editor_Vector_Type<Saklib::ElementID>::slot_append()
{
    // Get a list of types of Element that we can use
    auto element_types = Element::get_registered_types();

    // Make a dialog that asks the user to select one, floating above the project widget
    Select_Element_Type_Dialog dialog{element_types, project_widget()};

    // if the user selects one, make an Element of that type and assign it to the attribute
    if (dialog.exec() == QDialog::Accepted && !dialog.selected_element_type().empty())
    {
        ElementID new_element = project_widget()->make_element(dialog.selected_element_type());
        project_widget()->undoable_attribute_vector_push_back(attributeid(), new_element);
    }
}

//template<>
void Saklib::Qtlib::Attribute_Editor_Vector_Type<Saklib::ElementID>::slot_insert(size_type index)
{
    // Get a list of types of Element that we can use
    auto element_types = Element::get_registered_types();

    // Make a dialog that asks the user to select one, floating above the project widget
    Select_Element_Type_Dialog dialog{element_types, project_widget()};

    // if the user selects one, make an Element of that type and assign it to the attribute
    if (dialog.exec() == QDialog::Accepted && !dialog.selected_element_type().empty())
    {
        ElementID new_element = project_widget()->make_element(dialog.selected_element_type());
        //project_widget()->undoable_attribute_vector_insert_at(attributeid(), index, new_element);
    }
}
