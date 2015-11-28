#include "attribute_editor_vector_elementid.h"
#include "attribute_editor_elementid.h"
#include "project_widget.h"
#include "../project_manager.h"
#include "select_element_type_dialog.h"

// Special 6
//============================================================
//template<>
saklib::Qtlib::Attribute_Editor_Vector_Type<saklib::ElementID>::Attribute_Editor_Vector_Type(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent):
    Attribute_Editor_Vector(project_widget, attributeid, parent)
{
}
//template<>
saklib::Qtlib::Attribute_Editor_Vector_Type<saklib::ElementID>::~Attribute_Editor_Vector_Type() = default;

//template<>
void saklib::Qtlib::Attribute_Editor_Vector_Type<saklib::ElementID>::slot_append()
{
    // Make a dialog that asks the user to select one, floating above the project widget
    Select_Element_Type_Dialog dialog{project_widget()->project_manager().attribute_element_types(attributeid()), project_widget()};

    // if the user selects one, make an Element of that type and assign it to the attribute
    if (dialog.exec() == QDialog::Accepted && !dialog.selected_element_type().empty())
    {
        ElementID new_element = project_widget()->project_manager().make_element(dialog.selected_element_type());
        project_widget()->project_manager().undoable_attribute_vector_push_back<ElementID>(attributeid(), new_element);
    }
}

//template<>
void saklib::Qtlib::Attribute_Editor_Vector_Type<saklib::ElementID>::slot_insert_at(size_type index)
{
    // Make a dialog that asks the user to select one, floating above the project widget
    Select_Element_Type_Dialog dialog{project_widget()->project_manager().attribute_element_types(attributeid()), project_widget()};

    // if the user selects one, make an Element of that type and assign it to the attribute
    if (dialog.exec() == QDialog::Accepted && !dialog.selected_element_type().empty())
    {
        ElementID new_element = project_widget()->project_manager().make_element(dialog.selected_element_type());
        project_widget()->project_manager().undoable_attribute_vector_insert_at<ElementID>(attributeid(), index, new_element);
    }
}

void saklib::Qtlib::Attribute_Editor_Vector_Type<saklib::ElementID>::slot_remove_at(size_type index)
{
    project_widget()->project_manager().undoable_attribute_vector_remove_at<ElementID>(attributeid(), index);
}
void saklib::Qtlib::Attribute_Editor_Vector_Type<saklib::ElementID>::slot_remove_last()
{
    project_widget()->project_manager().undoable_attribute_vector_pop_back<ElementID>(attributeid());
}
void saklib::Qtlib::Attribute_Editor_Vector_Type<saklib::ElementID>::slot_swap(size_type index, size_type other_index)
{
    project_widget()->project_manager().undoable_attribute_vector_swap_at<ElementID>(attributeid(), index, other_index);
}
void saklib::Qtlib::Attribute_Editor_Vector_Type<saklib::ElementID>::slot_move_up(size_type index)
{
    auto size = attribute_vector_size();
    if (size > 1 && index < size && index > 0)
        project_widget()->project_manager().undoable_attribute_vector_swap_at<ElementID>(attributeid(), index, index - 1);
}
void saklib::Qtlib::Attribute_Editor_Vector_Type<saklib::ElementID>::slot_move_down(size_type index)
{
    auto size = attribute_vector_size();
    if (size > 1 && index < size && index + 1 < size)
        project_widget()->project_manager().undoable_attribute_vector_swap_at<ElementID>(attributeid(), index, index + 1);
}
void saklib::Qtlib::Attribute_Editor_Vector_Type<saklib::ElementID>::slot_clear()
{
    project_widget()->project_manager().undoable_attribute_vector_clear<ElementID>(attributeid());
}
