#ifndef PROJECT_MANAGER_TEMPLATES_H
#define PROJECT_MANAGER_TEMPLATES_H

#include "project_manager_declaration.h"
#include "project_manager_commands.h"

/*
Template function implementation for Project_Widget
====================================================================================================
*/

// Attribute_Type<T>
//------------------------------------------------------------
// These functions set the data without question, and tell the model and widget to update.

template <typename T>
T const& saklib::Project_Manager::attribute_value(AttributeID const& attributeid) const
{
    assert_attribute<T>(attributeid);
    return attribute_type_cast<T>(attribute(attributeid))->value();
}

template <typename T>
void saklib::Project_Manager::attribute_set_value(AttributeID const& attributeid, T const& value)
{
    assert_attribute<T>(attributeid);
    attribute_type_cast<T>(attribute(attributeid))->set_value(value);
    attribute_changed(attributeid);
}

// Attribute_Type<Vector<T>> forwarding functions
//------------------------------------------------------------
// We must know the type to use these ones, and they should be called without specifying the
// explicitly so that the ElementID overload can be used (specialisation for it doesn't work).


template <typename T>
std::vector<T> const& saklib::Project_Manager::attribute_vector_vector(AttributeID const& attributeid)
{
    assert_attribute<std::vector<T>>(attributeid);
    return attribute_type_cast<std::vector<T>>(attribute(attributeid))->vector();
}

template <typename T>
void saklib::Project_Manager::attribute_vector_set_vector(AttributeID const& attributeid, std::vector<T> const& other_vector)
{
    assert_attribute<std::vector<T>>(attributeid);
    attribute_type_cast<std::vector<T>>(attribute(attributeid))->set_vector(other_vector);
    attribute_changed(attributeid);
}

template <typename T>
bool saklib::Project_Manager::attribute_vector_empty(AttributeID const& attributeid) const
{
    assert_attribute<std::vector<T>>(attributeid);
    return attribute_type_cast<std::vector<T>>(attribute(attributeid))->empty();
}

template <typename T>
saklib::size_type saklib::Project_Manager::attribute_vector_size(AttributeID const& attributeid) const
{
    assert_attribute<std::vector<T>>(attributeid);
    return attribute_type_cast<std::vector<T>>(attribute(attributeid))->size();
}

template <typename T>
void saklib::Project_Manager::attribute_vector_clear(AttributeID const& attributeid)
{
    assert_attribute<std::vector<T>>(attributeid);
    attribute_type_cast<std::vector<T>>(attribute(attributeid))->clear();
    attribute_changed(attributeid);
}

template <typename T>
T const& saklib::Project_Manager::attribute_vector_at(AttributeID const& attributeid, size_type index) const
{
    assert_attribute<std::vector<T>>(attributeid);
    return attribute_type_cast<std::vector<T>>(attribute(attributeid))->at(index);
}

template <typename T>
T const& saklib::Project_Manager::attribute_vector_front(AttributeID const& attributeid) const
{
    assert_attribute<std::vector<T>>(attributeid);
    return attribute_type_cast<std::vector<T>>(attribute(attributeid))->front();
}

template <typename T>
T const& saklib::Project_Manager::attribute_vector_back(AttributeID const& attributeid) const
{
    assert_attribute<std::vector<T>>(attributeid);
    return attribute_type_cast<std::vector<T>>(attribute(attributeid))->back();
}

template <typename T>
void saklib::Project_Manager::attribute_vector_set_at(AttributeID const& attributeid, size_type index, T const& value)
{
    assert_attribute<std::vector<T>>(attributeid);
    attribute_type_cast<std::vector<T>>(attribute(attributeid))->set_at(index, value);
    attribute_changed(attributeid);
}

template <typename T>
void saklib::Project_Manager::attribute_vector_set_front(AttributeID const& attributeid, T const& value)
{
    assert_attribute<std::vector<T>>(attributeid);
    attribute_type_cast<std::vector<T>>(attribute(attributeid))->set_front(value);
    attribute_changed(attributeid);
}

template <typename T>
void saklib::Project_Manager::attribute_vector_set_back(AttributeID const& attributeid, T const& value)
{
    assert_attribute<std::vector<T>>(attributeid);
    attribute_type_cast<std::vector<T>>(attribute(attributeid))->set_back(value);
    attribute_changed(attributeid);
}

template <typename T>
void saklib::Project_Manager::attribute_vector_swap_at(AttributeID const& attributeid, size_type index, size_type other_index)

{
    assert_attribute<std::vector<T>>(attributeid);
    attribute_type_cast<std::vector<T>>(attribute(attributeid))->swap_at(index, other_index);
    attribute_changed(attributeid);
}

template <typename T>
void saklib::Project_Manager::attribute_vector_push_back(AttributeID const& attributeid, T const& value)
{
    assert_attribute<std::vector<T>>(attributeid);
    attribute_type_cast<std::vector<T>>(attribute(attributeid))->push_back(value);
    attribute_changed(attributeid);
}

template <typename T>
void saklib::Project_Manager::attribute_vector_pop_back(AttributeID const& attributeid)
{
    assert_attribute<std::vector<T>>(attributeid);
    attribute_type_cast<std::vector<T>>(attribute(attributeid))->pop_back();
    attribute_changed(attributeid);
}

template <typename T>
void saklib::Project_Manager::attribute_vector_insert_at(AttributeID const& attributeid, size_type index, T const& value)
{
    assert_attribute<std::vector<T>>(attributeid);
    attribute_type_cast<std::vector<T>>(attribute(attributeid))->insert_at(index, value);
    attribute_changed(attributeid);
}

template <typename T>
void saklib::Project_Manager::attribute_vector_remove_at(AttributeID const& attributeid, size_type index)
{
    assert_attribute<std::vector<T>>(attributeid);
    attribute_type_cast<std::vector<T>>(attribute(attributeid))->remove_at(index);
    attribute_changed(attributeid);
}



// Commands - indirect write access
//------------------------------------------------------------
// To support undoing edits use these functions to edit data from the outliner/widgets.

template <typename T>
bool saklib::Project_Manager::undoable_attribute_set_value(AttributeID const& attributeid, T const& value)
{
    // if conditions are right to issue a command
    if(attributeid.is_valid()
       && this->has_attributeid(attributeid)
       && this->attribute_type_enum(attributeid) == Common_Traits<T>::type_enum()
       && this->attribute_value<T>(attributeid) != value)
    {
        m_command_history.emplace_execute<PMC_Attribute_Set_Value<T>>(this, attributeid, value);
        command_history_changed();
        return true;
    }
    else
    {
        return false;
    }
}



// Attribute_Type<Vector<T>>
//------------------------------------------------------------
template <typename T>
bool saklib::Project_Manager::undoable_attribute_vector_clear(AttributeID const& attributeid)
{
    if(attributeid.is_valid()
       && this->has_attributeid(attributeid)
       && this->attribute_type_enum(attributeid) == Common_Traits<std::vector<T>>::type_enum()
       && this->attribute_vector_empty<T>(attributeid) == false )
    {
        m_command_history.emplace_execute<PMC_Attribute_Vector_Clear<T>>(this, attributeid);
        command_history_changed();
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool saklib::Project_Manager::undoable_attribute_vector_set_at(AttributeID const& attributeid, size_type index, T const& value)
{
    if(attributeid.is_valid()
       && this->has_attributeid(attributeid)
       && this->attribute_type_enum(attributeid) == Common_Traits<std::vector<T>>::type_enum()
       && this->attribute_vector_at<T>(attributeid, index) != value)
    {
        m_command_history.emplace_execute<PMC_Attribute_Vector_Set_At<T>>(this, attributeid, index, value);
        command_history_changed();
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool saklib::Project_Manager::undoable_attribute_vector_set_front(AttributeID const& attributeid, T const& value)
{
    if(attributeid.is_valid()
       && this->has_attributeid(attributeid)
       && this->attribute_type_enum(attributeid) == Common_Traits<std::vector<T>>::type_enum()
       && this->attribute_vector_front<T>(attributeid) != value)
    {
        m_command_history.emplace_execute<PMC_Attribute_Vector_Set_Front<T>>(this, attributeid, value);
        command_history_changed();
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool saklib::Project_Manager::undoable_attribute_vector_set_back(AttributeID const& attributeid, T const& value)
{
    if(attributeid.is_valid()
       && this->has_attributeid(attributeid)
       && this->attribute_type_enum(attributeid) == Common_Traits<std::vector<T>>::type_enum()
       && this->attribute_vector_back<T>(attributeid) != value)
    {
        m_command_history.emplace_execute<PMC_Attribute_Vector_Set_Back<T>>(this, attributeid, value);
        command_history_changed();
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool saklib::Project_Manager::undoable_attribute_vector_swap_at(AttributeID const& attributeid, size_type index, size_type other_index)
{
    if(attributeid.is_valid()
       && this->has_attributeid(attributeid)
       && this->attribute_type_enum(attributeid) == Common_Traits<std::vector<T>>::type_enum()
       && this->attribute_vector_size<T>(attributeid) > index
       && this->attribute_vector_size<T>(attributeid) > other_index
       && this->attribute_vector_at<T>(attributeid, index) != this->attribute_vector_at<T>(attributeid, other_index) )
    {
        m_command_history.emplace_execute<PMC_Attribute_Vector_Swap_At<T>>(this, attributeid, index, other_index);
        command_history_changed();
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool saklib::Project_Manager::undoable_attribute_vector_push_back(AttributeID const& attributeid, T const& value)
{
    if(attributeid.is_valid()
       && this->has_attributeid(attributeid)
       && this->attribute_type_enum(attributeid) == Common_Traits<std::vector<T>>::type_enum() )
    {
        m_command_history.emplace_execute<PMC_Attribute_Vector_Push_Back<T>>(this, attributeid, value);
        command_history_changed();
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool saklib::Project_Manager::undoable_attribute_vector_pop_back(AttributeID const& attributeid)
{
    if(attributeid.is_valid()
       && this->has_attributeid(attributeid)
       && this->attribute_type_enum(attributeid) == Common_Traits<std::vector<T>>::type_enum()
       && this->attribute_vector_empty<T>(attributeid) == false )
    {
        m_command_history.emplace_execute<PMC_Attribute_Vector_Pop_Back<T>>(this, attributeid);
        command_history_changed();
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool saklib::Project_Manager::undoable_attribute_vector_insert_at(AttributeID const& attributeid, size_type index, T const& value)
{
    if(attributeid.is_valid()
       && this->has_attributeid(attributeid)
       && this->attribute_type_enum(attributeid) == Common_Traits<std::vector<T>>::type_enum()
       && this->attribute_vector_size<T>(attributeid) > index )
    {
        m_command_history.emplace_execute<PMC_Attribute_Vector_Insert_At<T>>(this, attributeid, index, value);
        command_history_changed();
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool saklib::Project_Manager::undoable_attribute_vector_remove_at(AttributeID const& attributeid, size_type index)
{
    if(attributeid.is_valid()
       && this->has_attributeid(attributeid)
       && this->attribute_type_enum(attributeid) == Common_Traits<std::vector<T>>::type_enum()
       && this->attribute_vector_size<T>(attributeid) > index)
    {
        m_command_history.emplace_execute<PMC_Attribute_Vector_Remove_At<T>>(this, attributeid, index);
        command_history_changed();
        return true;
    }
    else
    {
        return false;
    }
}


// Internal
//============================================================

// make sure an operation will work

template <typename T>
void saklib::Project_Manager::assert_attribute(AttributeID const& attributeid) const
{
    assert(attributeid.is_valid());
    assert(this->has_attributeid(attributeid));
    assert(this->attribute_type_enum(attributeid) == Common_Traits<T>::type_enum());
    //assert(this->attribute_type_cast<T>(attributeid)->value() != value);
}

template <typename MemFunc>
void saklib::Project_Manager::all_observers_function(MemFunc func) const
{
    for (auto p_observer : m_observers)
    {
        (p_observer->*func)();
    }
}


template <typename MemFunc, typename... Args>
void saklib::Project_Manager::all_observers_function(MemFunc func, Args&&... args) const
{
    for (auto p_observer : m_observers)
    {
        (p_observer->*func)(std::forward<Args>(args)...);
    }
}


#endif // PROJECT_MANAGER_TEMPLATES_H

