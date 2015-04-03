#ifndef PROJECT_MANAGER_TEMPLATES_H
#define PROJECT_MANAGER_TEMPLATES_H

#include "project_manager_declaration.h"
#include "project_manager_commands.h"

/*
Template function implementation for Project_Widget
====================================================================================================
*/

// Attributes
//------------------------------------------------------------

template <typename T>
Saklib::Attribute_Type<T> const*const Saklib::Project_Manager::attribute_type_cast(AttributeID attributeid) const
{
    return Saklib::attribute_type_cast<T>(attribute(attributeid));
}
template <typename T>
Saklib::Attribute_Type<T> const*const Saklib::Project_Manager::attribute_type_cast(ElementID elementid, size_type attribute_index) const
{
    return Saklib::attribute_type_cast<T>(attribute(elementid, attribute_index));
}
template <typename T>
Saklib::Attribute_Type<T> const*const Saklib::Project_Manager::attribute_type_cast(ElementID elementid, String const& attribute_name) const
{
    return Saklib::attribute_type_cast<T>(attribute(elementid, attribute_name));
}


template <typename T>
Saklib::Attribute_Type<T> *const Saklib::Project_Manager::attribute_type_cast(AttributeID attributeid)
{
    return Saklib::attribute_type_cast<T>(attribute(attributeid));
}
template <typename T>
Saklib::Attribute_Type<T> *const Saklib::Project_Manager::attribute_type_cast(ElementID elementid, size_type attribute_index)
{
    return Saklib::attribute_type_cast<T>(attribute(elementid, attribute_index));
}
template <typename T>
Saklib::Attribute_Type<T> *const Saklib::Project_Manager::attribute_type_cast(ElementID elementid, String const& attribute_name)
{
    return Saklib::attribute_type_cast<T>(attribute(elementid, attribute_name));
}



// Attribute_Type<T>
//------------------------------------------------------------
// These functions set the data without question, and tell the model and widget to update.

template <typename T>
T const& Saklib::Project_Manager::attribute_value(AttributeID attributeid) const
{
    assert_attribute<T>(attributeid);
    return attribute_type_cast<T>(attributeid)->value();
}

template <typename T>
void Saklib::Project_Manager::attribute_set_value(AttributeID attributeid, T const& value)
{
    // god dammit have to specificy the template right now, but it works
    attribute_function<T, decltype(&Attribute_Type<T>::set_value), T>(attributeid, &Attribute_Type<T>::set_value, value);
}

// vector functions....all of them.........



// Attribute_Type<Vector<T>> forwarding functions
//------------------------------------------------------------
// We must know the type to use these ones, and they should be called without specifying the
// explicitly so that the ElementID overload can be used (specialisation for it doesn't work).

template <typename T>
void Saklib::Project_Manager::attribute_vector_set_vector(AttributeID attributeid, Vector<T> const& other_vector)
{
    attribute_function<Vector<T>, decltype(&Attribute_Type<Vector<T>>::set_vector), Vector<T> const&>(attributeid, &Attribute_Type<Vector<T>>::set_vector, other_vector);
}

template <typename T>
bool Saklib::Project_Manager::attribute_vector_empty(AttributeID attributeid) const
{
    assert_attribute<Vector<T>>(attributeid);
    return attribute_type_cast<Vector<T>>(attributeid)->empty();
}

template <typename T>
Saklib::size_type Saklib::Project_Manager::attribute_vector_size(AttributeID attributeid) const
{
    assert_attribute<Vector<T>>(attributeid);
    return attribute_type_cast<Vector<T>>(attributeid)->size();
}

template <typename T>
void Saklib::Project_Manager::attribute_vector_clear(AttributeID attributeid)
{
    attribute_function<Vector<T>, decltype(&Attribute_Type<Vector<T>>::clear)>(attributeid, &Attribute_Type<Vector<T>>::clear);
}

template <typename T>
T const& Saklib::Project_Manager::attribute_vector_at(AttributeID attributeid, size_type index) const
{
    assert_attribute<Vector<T>>(attributeid);
    return attribute_type_cast<Vector<T>>(attributeid)->at(index);
}

template <typename T>
T const& Saklib::Project_Manager::attribute_vector_front(AttributeID attributeid) const
{
    assert_attribute<Vector<T>>(attributeid);
    return attribute_type_cast<Vector<T>>(attributeid)->front();
}

template <typename T>
T const& Saklib::Project_Manager::attribute_vector_back(AttributeID attributeid) const
{
    assert_attribute<Vector<T>>(attributeid);
    return attribute_type_cast<Vector<T>>(attributeid)->back();
}

template <typename T>
void Saklib::Project_Manager::attribute_vector_set_at(AttributeID attributeid, size_type index, T const& value)
{
    attribute_function<Vector<T>, decltype(&Attribute_Type<Vector<T>>::set_at), size_type, T>(attributeid, &Attribute_Type<Vector<T>>::set_at, index, value);
}

template <typename T>
void Saklib::Project_Manager::attribute_vector_set_front(AttributeID attributeid, T const& value)
{
    attribute_function<Vector<T>, decltype(&Attribute_Type<Vector<T>>::set_front), T>(attributeid, &Attribute_Type<Vector<T>>::set_front);
}

template <typename T>
void Saklib::Project_Manager::attribute_vector_set_back(AttributeID attributeid, T const& value)
{
    attribute_function<Vector<T>, decltype(&Attribute_Type<Vector<T>>::set_back), T>(attributeid, &Attribute_Type<Vector<T>>::set_back, value);
}

template <typename T>
void Saklib::Project_Manager::attribute_vector_swap_at(AttributeID attributeid, size_type index, size_type other_index)

{
    attribute_function<Vector<T>, decltype(&Attribute_Type<Vector<T>>::swap_at), size_type, size_type>(attributeid, &Attribute_Type<Vector<T>>::swap_at, index, other_index);
}

template <typename T>
void Saklib::Project_Manager::attribute_vector_push_back(AttributeID attributeid, T const& value)
{
    attribute_function<Vector<T>, decltype(&Attribute_Type<Vector<T>>::push_back), T>(attributeid, &Attribute_Type<Vector<T>>::push_back, value);
}

template <typename T>
void Saklib::Project_Manager::attribute_vector_pop_back(AttributeID attributeid)
{
    attribute_function<Vector<T>, decltype(&Attribute_Type<Vector<T>>::pop_back)>(attributeid, &Attribute_Type<Vector<T>>::pop_back);
}

template <typename T>
void Saklib::Project_Manager::attribute_vector_insert_at(AttributeID attributeid, size_type index, T const& value)
{
    attribute_function<Vector<T>, decltype(&Attribute_Type<Vector<T>>::insert_at), size_type, T>(attributeid, &Attribute_Type<Vector<T>>::insert_at, index, value);
}

template <typename T>
void Saklib::Project_Manager::attribute_vector_remove_at(AttributeID attributeid, size_type index)
{
    attribute_function<Vector<T>, decltype(&Attribute_Type<Vector<T>>::remove_at), size_type>(attributeid, &Attribute_Type<Vector<T>>::remove_at, index);
}



// Commands - indirect write access
//------------------------------------------------------------
// To support undoing edits use these functions to edit data from the outliner/widgets.

template <typename T>
bool Saklib::Project_Manager::undoable_attribute_set_value(AttributeID attributeid, T const& value)
{
    // if conditions are right to issue a command
    if(attributeid.is_valid()
       && this->is_valid(attributeid)
       && this->attribute_type_enum(attributeid) == Type_Traits<T>::type_enum()
       && this->attribute_type_cast<T>(attributeid)->value() != value)
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
bool Saklib::Project_Manager::undoable_attribute_vector_clear(AttributeID attributeid)
{
    if(attributeid.is_valid()
       && this->is_valid(attributeid)
       && this->attribute_type_enum(attributeid) == Type_Traits<Vector<T>>::type_enum()
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
bool Saklib::Project_Manager::undoable_attribute_vector_set_at(AttributeID attributeid, size_type index, T const& value)
{
    if(attributeid.is_valid()
       && this->is_valid(attributeid)
       && this->attribute_type_enum(attributeid) == Type_Traits<Vector<T>>::type_enum()
       && this->attribute_type_cast<Vector<T>>(attributeid)->at(index) != value)
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
bool Saklib::Project_Manager::undoable_attribute_vector_set_front(AttributeID attributeid, T const& value)
{
    if(attributeid.is_valid()
       && this->is_valid(attributeid)
       && this->attribute_type_enum(attributeid) == Type_Traits<Vector<T>>::type_enum()
       && this->attribute_type_cast<Vector<T>>(attributeid)->at(index) != value)
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
bool Saklib::Project_Manager::undoable_attribute_vector_set_back(AttributeID attributeid, T const& value)
{
    if(attributeid.is_valid()
       && this->is_valid(attributeid)
       && this->attribute_type_enum(attributeid) == Type_Traits<Vector<T>>::type_enum()
       && this->attribute_type_cast<Vector<T>>(attributeid)->at(index) != value)
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
bool Saklib::Project_Manager::undoable_attribute_vector_swap_at(AttributeID attributeid, size_type index, size_type other_index)
{
    if(attributeid.is_valid()
       && this->is_valid(attributeid)
       && this->attribute_type_enum(attributeid) == Type_Traits<Vector<T>>::type_enum()
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
bool Saklib::Project_Manager::undoable_attribute_vector_push_back(AttributeID attributeid, T const& value)
{
    if(attributeid.is_valid()
       && this->is_valid(attributeid)
       && this->attribute_type_enum(attributeid) == Type_Traits<Vector<T>>::type_enum() )
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
bool Saklib::Project_Manager::undoable_attribute_vector_pop_back(AttributeID attributeid)
{
    if(attributeid.is_valid()
       && this->is_valid(attributeid)
       && this->attribute_type_enum(attributeid) == Type_Traits<Vector<T>>::type_enum()
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
bool Saklib::Project_Manager::undoable_attribute_vector_insert_at(AttributeID attributeid, size_type index, T const& value)
{
    if(attributeid.is_valid()
       && this->is_valid(attributeid)
       && this->attribute_type_enum(attributeid) == Type_Traits<Vector<T>>::type_enum()
       && this->attribute_vector_size<T>(attributeid) > index
       && this->attribute_type_cast<Vector<T>>(attributeid)->at(index) != value) // hmm
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
bool Saklib::Project_Manager::undoable_attribute_vector_remove_at(AttributeID attributeid, size_type index)
{
    if(attributeid.is_valid()
       && this->is_valid(attributeid)
       && this->attribute_type_enum(attributeid) == Type_Traits<Vector<T>>::type_enum()
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
void Saklib::Project_Manager::assert_attribute(AttributeID attributeid) const
{
    assert(attributeid.is_valid());
    assert(this->is_valid(attributeid));
    assert(this->attribute_type_enum(attributeid) == Type_Traits<T>::type_enum());
    //assert(this->attribute_type_cast<T>(attributeid)->value() != value);
}


template <typename T, typename Func, typename... Args>
void Saklib::Project_Manager::attribute_function(AttributeID attributeid, Func member_function, Args... args)
{
    assert_attribute<T>(attributeid);
    (m_element_manager.element(attributeid.elementid()).attribute_type_cast<T>(attributeid.index())->*member_function)(std::forward<Args>(args)...);
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

template <typename MemFunc>
void Saklib::Project_Manager::all_observers_function(MemFunc func) const
{
    for (auto p_observer : m_observers)
    {
        (p_observer->*func)();
    }
}

template <typename MemFunc, typename... Args>
void Saklib::Project_Manager::all_observers_function(MemFunc func, Args&&... args) const
{
    for (auto p_observer : m_observers)
    {
        (p_observer->*func)(std::forward<Args>(args)...);
    }
}


#endif // PROJECT_MANAGER_TEMPLATES_H

