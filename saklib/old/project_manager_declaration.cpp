#include "project_manager.h"

#include "element.h"
#include "all_constraints.h"
#include "string_traits.h"

//#include "qtlib/qstring_operations.h"

#include "project_observer.h"

#include "internal_element_definitions.h"

// Special 6
//============================================================
saklib::Project_Manager::Project_Manager() :
    m_internal_element_definitions{},
    m_element_manager{},
    m_command_history{},

    m_project_elementid{},
    m_project_filepath{},

    m_unsaved_edits(false),
    m_observers()
{
    // Store the filename in this attribute
}

saklib::Project_Manager::Project_Manager(Path const& filepath) :
    Project_Manager()
{
    // Store the filename in this attribute
    open_project(filepath);
}
saklib::Project_Manager::~Project_Manager()
{
    clear();
}

// Interface
//============================================================


// Overall Project
//------------------------------------------------------------


void saklib::Project_Manager::new_project(Path const& filepath)
{
    clear();

    m_project_elementid = make_element("Project");
    m_project_filepath = m_element_manager.attributeid(m_project_elementid, "Filepath");

    set_project_filepath(filepath);

    observers_unsaved_edits_changed(false); // force this signal if m_unsaved_edits was false before
}

void saklib::Project_Manager::open_project(Path const& filepath)
{
    clear();

    // this should load from the file...

    m_project_elementid = make_element("Project");
    m_project_filepath = m_element_manager.attributeid(m_project_elementid, "Filepath");

    set_project_filepath(filepath);

    observers_unsaved_edits_changed(false); // force this signal if m_unsaved_edits was false before
}


void saklib::Project_Manager::save() const
{
    observers_unsaved_edits_changed(false);
}
void saklib::Project_Manager::save_as(Path const& filepath)
{
    set_project_filepath(filepath);
    save();
}


void saklib::Project_Manager::clear()
{
    m_element_manager.clear();
    m_command_history.clear();
    m_unsaved_edits = false;
}




saklib::ElementID saklib::Project_Manager::project_elementid() const
{
    return m_project_elementid;
}
saklib::Path const& saklib::Project_Manager::project_filepath() const
{
    return saklib::attribute_type_cast<Path>(m_element_manager.cattribute(m_project_filepath))->value();
}
void saklib::Project_Manager::set_project_filepath(Path const& filepath)
{
    m_element_manager.element(m_project_elementid)->set_name(String_Traits<Path>::to_string(filepath.filename()));
    saklib::attribute_type_cast<Path>(m_element_manager.attribute(m_project_filepath))->set_value(filepath);

    // tell observers the filepath changed?
}



void saklib::Project_Manager::add_observer(Project_Observer* observer)
{
    auto found = std::find(m_observers.cbegin(), m_observers.cend(), observer);
    if (found == m_observers.cend())
    {
        m_observers.push_back(observer);
    }
}

void saklib::Project_Manager::remove_observer(Project_Observer* observer)
{
    auto found = std::find(m_observers.cbegin(), m_observers.cend(), observer);
    if (found != m_observers.cend())
    {
        m_observers.erase(found);
    }
}

// Lifetime
//------------------------------------------------------------

void saklib::Project_Manager::register_element_definition(Element_Definition&& definition)
{
    m_internal_element_definitions.add_override_definition(std::forward<Element_Definition>(definition));
}

bool saklib::Project_Manager::has_element_definition(String const& type) const
{
    return m_internal_element_definitions.definition_exists(type);
}
saklib::Element_Definition const& saklib::Project_Manager::element_definition(String const& type) const
{
    return m_internal_element_definitions.definition(type);
}

std::vector<saklib::String> saklib::Project_Manager::all_registered_element_types() const
{
    return m_internal_element_definitions.definition_types();
}

// Make a new Element and return all info about it
saklib::ElementID saklib::Project_Manager::make_element(String const& type)
{
    assert(has_element_definition(type));
    ElementID newid = m_element_manager.make_element(element_definition(type));
    return newid;
}

// Destory an Element and everything associated with it
void saklib::Project_Manager::destroy_element(ElementID const& elementid)
{
    m_element_manager.destroy_element(elementid);
    observers_element_destroyed(elementid);
}

// Does this refer to something in this? - rename these to has(blah) ?
bool saklib::Project_Manager::has_elementid(ElementID const& elementid) const
{
    return m_element_manager.has_elementid(elementid);
}
bool saklib::Project_Manager::has_attributeid(AttributeID const& attributeid) const
{
    return m_element_manager.has_attributeid(attributeid);
}

// Elements
//------------------------------------------------------------
saklib::Element* saklib::Project_Manager::element(ElementID const& elementid)
{
    assert_element(elementid);
    return m_element_manager.element(elementid);
}

saklib::Element const* saklib::Project_Manager::celement(ElementID const& elementid) const
{
    assert_element(elementid);
    return m_element_manager.celement(elementid);
}

saklib::String const& saklib::Project_Manager::element_type(ElementID const& elementid) const
{
    assert_element(elementid);
    return m_element_manager.celement(elementid)->type();
}

saklib::String const& saklib::Project_Manager::element_name(ElementID const& elementid) const
{
    assert_element(elementid);
    return m_element_manager.celement(elementid)->name();
}

void saklib::Project_Manager::element_set_name(ElementID const& elementid, String const& value)
{
    assert_element(elementid);
    // Element_Manager will adjust the name by adding a number to the end if it isn't unique.
    m_element_manager.set_element_name(elementid, value);
    //m_element_manager.element(elementid).set_name(value);
    observers_element_name_changed(elementid);
    set_unsaved_edits(true);
}

bool saklib::Project_Manager::element_can_be_root(ElementID const& elementid) const
{
    assert_element(elementid);
    return m_element_manager.celement(elementid)->can_be_root();
}

saklib::AttributeID saklib::Project_Manager::element_parent(ElementID const& elementid) const
{
    assert_element(elementid);
    return m_element_manager.element_parent(elementid);
}

void saklib::Project_Manager::element_set_parent(ElementID const& elementid, AttributeID attributeid)
{
    if (elementid.is_valid())
    {
        assert_element(elementid);
        m_element_manager.set_element_parent(elementid, attributeid);

        observers_element_parent_changed(elementid);
        set_unsaved_edits(true);
    }
}

// Attributes
//------------------------------------------------------------
saklib::AttributeID saklib::Project_Manager::attributeid(ElementID const& elementid, String const& attribute_name) const
{
    return m_element_manager.attributeid(elementid, attribute_name);
}

saklib::Attribute* saklib::Project_Manager::attribute(AttributeID const& attributeid)
{
    return m_element_manager.attribute(attributeid);
}
saklib::Attribute* saklib::Project_Manager::attribute(ElementID const& elementid, size_type attribute_index)
{
    return m_element_manager.attribute(elementid, attribute_index);
}
saklib::Attribute* saklib::Project_Manager::attribute(ElementID const& elementid, String const& attribute_name)
{
    return m_element_manager.attribute(elementid, attribute_name);
}


saklib::Attribute const* saklib::Project_Manager::attribute(AttributeID const& attributeid) const
{
    return m_element_manager.cattribute(attributeid);
}
saklib::Attribute const* saklib::Project_Manager::attribute(ElementID const& elementid, size_type attribute_index) const
{
    return m_element_manager.cattribute(elementid, attribute_index);
}
saklib::Attribute const* saklib::Project_Manager::attribute(ElementID const& elementid, String const& attribute_name) const
{
    return m_element_manager.cattribute(elementid, attribute_name);
}

saklib::String const& saklib::Project_Manager::attribute_name(AttributeID const& attributeid) const
{
    return m_element_manager.cattribute(attributeid)->name();
}
saklib::Type_Enum saklib::Project_Manager::attribute_type_enum(AttributeID const& attributeid) const
{
    return m_element_manager.cattribute(attributeid)->type_enum();
}
saklib::String saklib::Project_Manager::attribute_type_string(AttributeID const& attributeid) const
{
    return m_element_manager.cattribute(attributeid)->type_string();
}
bool saklib::Project_Manager::attribute_is_constrained(AttributeID const& attributeid) const
{
    return m_element_manager.cattribute(attributeid)->is_constrained();
}


// Attribute_Type<T>
//------------------------------------------------------------
// These functions set the data without question, and tell the model and widget to update.
template <>
void saklib::Project_Manager::attribute_set_value<saklib::ElementID>(AttributeID const& attributeid, ElementID const& value)
{
    assert_attribute<ElementID>(attributeid);
    observers_begin_model_reset();

    auto lp_attribute = attribute_type_cast<ElementID>(attribute(attributeid));
    ElementID old_value = lp_attribute->value();
    ElementID new_value = value;

    lp_attribute->set_value(new_value);
    element_set_parent(new_value, attributeid);
    element_set_parent(old_value, invalid_attributeid());

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);

    set_unsaved_edits(true);
}


// Attribute_Type<Vector<T>> Type-Anonymous Functions
//------------------------------------------------------------
// We do not need to know the underlying type to call these functions, but this must figure
// it out and act appropriately.


// if the attribute is a vector, return it's size, otherwise 0
saklib::size_type saklib::Project_Manager::any_attribute_vector_size(AttributeID const& attributeid) const
{
    auto attribute_type = attribute_type_enum(attributeid);
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return attribute_vector_size<Type_Holder_vt<Type_Enum::Vector_Bool>>(attributeid);
    case Type_Enum::Vector_Int:         return attribute_vector_size<Type_Holder_vt<Type_Enum::Vector_Int>>(attributeid);
    case Type_Enum::Vector_Double:      return attribute_vector_size<Type_Holder_vt<Type_Enum::Vector_Double>>(attributeid);
    case Type_Enum::Vector_String:      return attribute_vector_size<Type_Holder_vt<Type_Enum::Vector_String>>(attributeid);
    case Type_Enum::Vector_Path:        return attribute_vector_size<Type_Holder_vt<Type_Enum::Vector_Path>>(attributeid);
    case Type_Enum::Vector_ElementID:   return attribute_vector_size<Type_Holder_vt<Type_Enum::Vector_ElementID>>(attributeid);
    default: return 0;
    }
}

// if the attribute is a vector, return it's size, otherwise 0
bool saklib::Project_Manager::any_attribute_vector_empty(AttributeID const& attributeid) const
{
    auto attribute_type = attribute_type_enum(attributeid);
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return attribute_vector_empty<Type_Holder_vt<Type_Enum::Vector_Bool>>(attributeid);
    case Type_Enum::Vector_Int:         return attribute_vector_empty<Type_Holder_vt<Type_Enum::Vector_Int>>(attributeid);
    case Type_Enum::Vector_Double:      return attribute_vector_empty<Type_Holder_vt<Type_Enum::Vector_Double>>(attributeid);
    case Type_Enum::Vector_String:      return attribute_vector_empty<Type_Holder_vt<Type_Enum::Vector_String>>(attributeid);
    case Type_Enum::Vector_Path:        return attribute_vector_empty<Type_Holder_vt<Type_Enum::Vector_Path>>(attributeid);
    case Type_Enum::Vector_ElementID:   return attribute_vector_empty<Type_Holder_vt<Type_Enum::Vector_ElementID>>(attributeid);
    default: return false;
    }
}


void saklib::Project_Manager::any_attribute_vector_clear(AttributeID const& attributeid)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        attribute_vector_clear<Type_Holder_vt<Type_Enum::Vector_Bool>>(attributeid); break;
    case Type_Enum::Vector_Int:         attribute_vector_clear<Type_Holder_vt<Type_Enum::Vector_Int>>(attributeid); break;
    case Type_Enum::Vector_Double:      attribute_vector_clear<Type_Holder_vt<Type_Enum::Vector_Double>>(attributeid); break;
    case Type_Enum::Vector_String:      attribute_vector_clear<Type_Holder_vt<Type_Enum::Vector_String>>(attributeid); break;
    case Type_Enum::Vector_Path:        attribute_vector_clear<Type_Holder_vt<Type_Enum::Vector_Path>>(attributeid); break;
    case Type_Enum::Vector_ElementID:   attribute_vector_clear<Type_Holder_vt<Type_Enum::Vector_ElementID>>(attributeid); break;
    default: assert(false); // called on the wrong type
    }
}

void saklib::Project_Manager::any_attribute_vector_pop_back(AttributeID const& attributeid)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        attribute_vector_pop_back<Type_Holder_vt<Type_Enum::Vector_Bool>>(attributeid); break;
    case Type_Enum::Vector_Int:         attribute_vector_pop_back<Type_Holder_vt<Type_Enum::Vector_Int>>(attributeid); break;
    case Type_Enum::Vector_Double:      attribute_vector_pop_back<Type_Holder_vt<Type_Enum::Vector_Double>>(attributeid); break;
    case Type_Enum::Vector_String:      attribute_vector_pop_back<Type_Holder_vt<Type_Enum::Vector_String>>(attributeid); break;
    case Type_Enum::Vector_Path:        attribute_vector_pop_back<Type_Holder_vt<Type_Enum::Vector_Path>>(attributeid); break;
    case Type_Enum::Vector_ElementID:   attribute_vector_pop_back<Type_Holder_vt<Type_Enum::Vector_ElementID>>(attributeid); break;
    default: assert(false); // called on the wrong type
    }
}
void saklib::Project_Manager::any_attribute_vector_swap_at(AttributeID const& attributeid, size_type index, size_type other_index)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        attribute_vector_swap_at<Type_Holder_vt<Type_Enum::Vector_Bool>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_Int:         attribute_vector_swap_at<Type_Holder_vt<Type_Enum::Vector_Int>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_Double:      attribute_vector_swap_at<Type_Holder_vt<Type_Enum::Vector_Double>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_String:      attribute_vector_swap_at<Type_Holder_vt<Type_Enum::Vector_String>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_Path:        attribute_vector_swap_at<Type_Holder_vt<Type_Enum::Vector_Path>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_ElementID:   attribute_vector_swap_at<Type_Holder_vt<Type_Enum::Vector_ElementID>>(attributeid, index, other_index); break;
    default: assert(false); // called on the wrong type
    }
}

// Attribute_Type<Vector<T>> Forwarding Functions
//------------------------------------------------------------
// We must know the type to use these ones, and they should be called without specifying the
// explicitly so that the ElementID overload can be used (specialisation for it doesn't work).

template <>
void saklib::Project_Manager::attribute_vector_set_vector<saklib::ElementID>(AttributeID const& attributeid, std::vector<ElementID> const& other_vector)
{
    assert_attribute<std::vector<ElementID>>(attributeid);
    observers_begin_model_reset();

    auto lp_attribute = attribute_type_cast<std::vector<ElementID>>(attribute(attributeid));
    std::vector<ElementID> old_vector = lp_attribute->vector();

    lp_attribute->set_vector(other_vector);

    for (auto elementid : old_vector)
    {
        element_set_parent(elementid, invalid_attributeid());
    }
    for (auto elementid : other_vector)
    {
        element_set_parent(elementid, attributeid);
    }
    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);

    set_unsaved_edits(true);
}

template <>
void saklib::Project_Manager::attribute_vector_clear<saklib::ElementID>(AttributeID const& attributeid)
{
    assert_attribute<std::vector<ElementID>>(attributeid);
    observers_begin_model_reset();

    auto lp_attribute = attribute_type_cast<std::vector<ElementID>>(attribute(attributeid));
    std::vector<ElementID> old_vector = lp_attribute->vector();

    lp_attribute->clear();

    for (auto elementid : old_vector)
    {
        element_set_parent(elementid, invalid_attributeid());
    }
    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);

    set_unsaved_edits(true);
}

template <>
void saklib::Project_Manager::attribute_vector_set_at<saklib::ElementID>(AttributeID const& attributeid, size_type index, ElementID const& value)
{
    assert_attribute<std::vector<ElementID>>(attributeid);
    observers_begin_model_reset();

    auto lp_attribute = attribute_type_cast<std::vector<ElementID>>(attribute(attributeid));
    ElementID old_value = lp_attribute->at(index);
    ElementID new_value = value;

    lp_attribute->set_at(index, new_value);
    element_set_parent(new_value, attributeid);
    element_set_parent(old_value, invalid_attributeid());

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

template<>
void saklib::Project_Manager::attribute_vector_set_front<saklib::ElementID>(AttributeID const& attributeid, ElementID const& value)
{
    assert_attribute<std::vector<ElementID>>(attributeid);
    observers_begin_model_reset();

    auto lp_attribute = attribute_type_cast<std::vector<ElementID>>(attribute(attributeid));
    ElementID old_value = lp_attribute->front();
    ElementID new_value = value;

    lp_attribute->set_front(new_value);
    element_set_parent(new_value, attributeid);
    element_set_parent(old_value, invalid_attributeid());

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

template<>
void saklib::Project_Manager::attribute_vector_set_back<saklib::ElementID>(AttributeID const& attributeid, ElementID const& value)
{
    assert_attribute<std::vector<ElementID>>(attributeid);
    observers_begin_model_reset();

    auto lp_attribute = attribute_type_cast<std::vector<ElementID>>(attribute(attributeid));
    ElementID old_value = lp_attribute->front();
    ElementID new_value = value;

    lp_attribute->set_back(new_value);
    element_set_parent(new_value, attributeid);
    element_set_parent(old_value, invalid_attributeid());

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

template <>
void saklib::Project_Manager::attribute_vector_swap_at<saklib::ElementID>(AttributeID const& attributeid, size_type index, size_type other_index)
{
    assert_attribute<std::vector<ElementID>>(attributeid);
    observers_begin_model_reset();

    auto lp_attribute = attribute_type_cast<std::vector<ElementID>>(attribute(attributeid));
    lp_attribute->swap_at(index, other_index);

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

template<>
void saklib::Project_Manager::attribute_vector_push_back<saklib::ElementID>(AttributeID const& attributeid, ElementID const& value)
{
    assert_attribute<std::vector<ElementID>>(attributeid);
    observers_begin_model_reset();

    auto lp_attribute = attribute_type_cast<std::vector<ElementID>>(attribute(attributeid));

    lp_attribute->push_back(value);
    element_set_parent(value, attributeid);

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}
template<>
void saklib::Project_Manager::attribute_vector_pop_back<saklib::ElementID>(AttributeID const& attributeid)
{
    assert_attribute<std::vector<ElementID>>(attributeid);
    observers_begin_model_reset();

    auto lp_attribute = attribute_type_cast<std::vector<ElementID>>(attribute(attributeid));

    ElementID back_value = lp_attribute->back();
    lp_attribute->pop_back();
    element_set_parent(back_value, invalid_attributeid());

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

template<>
void saklib::Project_Manager::attribute_vector_insert_at<saklib::ElementID>(AttributeID const& attributeid, size_type index, ElementID const& value)
{
    assert_attribute<std::vector<ElementID>>(attributeid);
    observers_begin_model_reset();

    auto lp_attribute = attribute_type_cast<std::vector<ElementID>>(attribute(attributeid));

    lp_attribute->insert_at(index, value);
    element_set_parent(value, invalid_attributeid());

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

template<>
void saklib::Project_Manager::attribute_vector_remove_at<saklib::ElementID>(AttributeID const& attributeid, size_type index)
{
    assert_attribute<std::vector<ElementID>>(attributeid);

    auto lp_attribute = attribute_type_cast<std::vector<ElementID>>(attribute(attributeid));
    ElementID removed_value = lp_attribute->at(index);

    observers_begin_model_reset();

    lp_attribute->remove_at(index);
    element_set_parent(removed_value, invalid_attributeid());

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

// Attribute_Type<T> Constraint Stuff
//------------------------------------------------------------
// Get a vector of possible Element types for this attributeid
std::vector<saklib::String> saklib::Project_Manager::attribute_element_types(AttributeID const& attributeid) const
{
    std::vector<String> result{};
    auto type = attribute_type_enum(attributeid);
    bool is_constrained = attribute_is_constrained(attributeid);

    if (is_constrained && type == Type_Enum::ElementID)
    {
        result = attribute_type_cast<ElementID>(attribute(attributeid))->constraint()->element_types();
    }
    else if (is_constrained && type == Type_Enum::Vector_ElementID)
    {
        result = attribute_type_cast<std::vector<ElementID>>(attribute(attributeid))->value_constraint()->element_types();
    }
    else
    {
        result = all_registered_element_types();
    }

    return result;
}


// Commands - indirect write access
//------------------------------------------------------------
// To support undoing edits use these functions to edit data from the outliner/widgets.

bool saklib::Project_Manager::undoable_element_set_name(ElementID const& elementid, String const& value)
{
    // if conditions are right to issue a command
    if(elementid.is_valid()
       && this->has_elementid(elementid)
       && this->element_name(elementid) != value)
    {
        // do it. The command should call the update_... function(s) when it is executed/unexecuted
        m_command_history.emplace_execute<PMC_Element_Set_Name>(this, elementid, value);
        command_history_changed();
        return true;
    }
    else
    {
        return false;
    }
}

bool saklib::Project_Manager::undoable_any_attribute_vector_clear(AttributeID const& attributeid)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return undoable_attribute_vector_clear<Type_Holder_vt<Type_Enum::Vector_Bool>>(attributeid);
    case Type_Enum::Vector_Int:         return undoable_attribute_vector_clear<Type_Holder_vt<Type_Enum::Vector_Int>>(attributeid);
    case Type_Enum::Vector_Double:      return undoable_attribute_vector_clear<Type_Holder_vt<Type_Enum::Vector_Double>>(attributeid);
    case Type_Enum::Vector_String:      return undoable_attribute_vector_clear<Type_Holder_vt<Type_Enum::Vector_String>>(attributeid);
    case Type_Enum::Vector_Path:        return undoable_attribute_vector_clear<Type_Holder_vt<Type_Enum::Vector_Path>>(attributeid);
    case Type_Enum::Vector_ElementID:   return undoable_attribute_vector_clear<Type_Holder_vt<Type_Enum::Vector_ElementID>>(attributeid);
    default: assert(false); // called on the wrong type
    }
    return false;
}

bool saklib::Project_Manager::undoable_any_attribute_vector_swap_at(AttributeID const& attributeid, size_type index, size_type other_index)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return undoable_attribute_vector_swap_at<Type_Holder_vt<Type_Enum::Vector_Bool>>(attributeid, index, other_index);
    case Type_Enum::Vector_Int:         return undoable_attribute_vector_swap_at<Type_Holder_vt<Type_Enum::Vector_Int>>(attributeid, index, other_index);
    case Type_Enum::Vector_Double:      return undoable_attribute_vector_swap_at<Type_Holder_vt<Type_Enum::Vector_Double>>(attributeid, index, other_index);
    case Type_Enum::Vector_String:      return undoable_attribute_vector_swap_at<Type_Holder_vt<Type_Enum::Vector_String>>(attributeid, index, other_index);
    case Type_Enum::Vector_Path:        return undoable_attribute_vector_swap_at<Type_Holder_vt<Type_Enum::Vector_Path>>(attributeid, index, other_index);
    case Type_Enum::Vector_ElementID:   return undoable_attribute_vector_swap_at<Type_Holder_vt<Type_Enum::Vector_ElementID>>(attributeid, index, other_index);
    default: assert(false); // called on the wrong type
    }
    return false;
}

bool saklib::Project_Manager::undoable_any_attribute_vector_pop_back(AttributeID const& attributeid)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return undoable_attribute_vector_pop_back<Type_Holder_vt<Type_Enum::Vector_Bool>>(attributeid);
    case Type_Enum::Vector_Int:         return undoable_attribute_vector_pop_back<Type_Holder_vt<Type_Enum::Vector_Int>>(attributeid);
    case Type_Enum::Vector_Double:      return undoable_attribute_vector_pop_back<Type_Holder_vt<Type_Enum::Vector_Double>>(attributeid);
    case Type_Enum::Vector_String:      return undoable_attribute_vector_pop_back<Type_Holder_vt<Type_Enum::Vector_String>>(attributeid);
    case Type_Enum::Vector_Path:        return undoable_attribute_vector_pop_back<Type_Holder_vt<Type_Enum::Vector_Path>>(attributeid);
    case Type_Enum::Vector_ElementID:   return undoable_attribute_vector_pop_back<Type_Holder_vt<Type_Enum::Vector_ElementID>>(attributeid);
    default: assert(false); // called on the wrong type
    }
    return false;
}

bool saklib::Project_Manager::undoable_any_attribute_vector_remove_at(AttributeID const& attributeid, size_type index)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return undoable_attribute_vector_remove_at<Type_Holder_vt<Type_Enum::Vector_Bool>>(attributeid, index);
    case Type_Enum::Vector_Int:         return undoable_attribute_vector_remove_at<Type_Holder_vt<Type_Enum::Vector_Int>>(attributeid, index);
    case Type_Enum::Vector_Double:      return undoable_attribute_vector_remove_at<Type_Holder_vt<Type_Enum::Vector_Double>>(attributeid, index);
    case Type_Enum::Vector_String:      return undoable_attribute_vector_remove_at<Type_Holder_vt<Type_Enum::Vector_String>>(attributeid, index);
    case Type_Enum::Vector_Path:        return undoable_attribute_vector_remove_at<Type_Holder_vt<Type_Enum::Vector_Path>>(attributeid, index);
    case Type_Enum::Vector_ElementID:   return undoable_attribute_vector_remove_at<Type_Holder_vt<Type_Enum::Vector_ElementID>>(attributeid, index);
    default: assert(false); // called on the wrong type
    }
    return false;
}



// Flat Access
//------------------------------------------------------------
std::vector<saklib::ElementID> saklib::Project_Manager::all_elementids() const
{
    return m_element_manager.all_elementids();
}
std::vector<saklib::ElementID> saklib::Project_Manager::root_elementids() const
{
    return m_element_manager.root_elementids();
}

// Model Interface
//------------------------------------------------------------
// Functions that provide data to the outliner model

// What are this item's children?
std::vector<saklib::AttributeID> saklib::Project_Manager::outliner_children(ElementID const& elementid) const
{
    // Assuming a valid ElementID...
    std::vector<AttributeID> results{};

    // For each Attribute by index
    auto const* lp_element = celement(elementid);
    for (size_type attribute_index = 0, end = lp_element->attribute_count(); attribute_index != end; ++attribute_index)
    {
        AttributeID attributeid{elementid, attribute_index};
        // If the type is of interest
        Type_Enum type{lp_element->cattribute(attribute_index)->type_enum()};

        if (type == Type_Enum::ElementID || type == Type_Enum::Vector_ElementID)
        {
            results.push_back(attributeid);
        }


        // this version adds Attributes only if they have valid ElementIDs
        /*
        if (type == Type_Enum::ElementID
            && attribute_value<ElementID>(attributeid).is_valid())
        {
            results.push_back(attributeid);
        }
        else if (type == Type_Enum::Vector_ElementID
                 && !attribute_vector_empty<ElementID>(attributeid))
        {
            results.push_back(attributeid);
        }
        */
    }

    return results;
}
std::vector<saklib::ElementID> saklib::Project_Manager::outliner_children(AttributeID const& attributeid) const
{
    // Assuming a valid AttributeID...
    std::vector<ElementID> results{};

    // If invalid get the root children
    if (!attributeid.is_valid())
    {
        return root_elementids();
    }

    Type_Enum type{attribute_type_enum(attributeid)};
    if (type == Type_Enum::ElementID)
    {
        // Get the ElementID held
        ElementID held_elementid = attribute_type_cast<ElementID>(attribute(attributeid))->value();
        if (held_elementid.is_valid())
        {
            results.push_back(held_elementid);
        }
    }
    else if (type == Type_Enum::Vector_ElementID)
    {
        // For each stored ElementID
        auto const& elementid_vector = attribute_type_cast<std::vector<ElementID>>(attribute(attributeid))->vector();
        for(auto elementid : elementid_vector)
        {
            if (elementid.is_valid())
            {
                results.push_back(elementid);
            }
        }
    }
    else
    {
        // ignore other Attribute types
    }

    return results;
}

// What item is the child at row?
saklib::AttributeID saklib::Project_Manager::outliner_child_at_row(ElementID const& elementid, int row) const
{
    auto children = outliner_children(elementid);
    auto unsigned_row = static_cast<size_type>(row);
    if (row >=0 && unsigned_row < children.size())
    {
        return children.at(unsigned_row);
    }
    else
    {
        return invalid_attributeid();
    }
}
saklib::ElementID saklib::Project_Manager::outliner_child_at_row(AttributeID const& attributeid, int row) const
{
    auto children = outliner_children(attributeid);
    auto unsigned_row = static_cast<size_type>(row);
    if (row >=0 && unsigned_row < children.size())
    {
        return children.at(unsigned_row);
    }
    else
    {
        return invalid_elementid();
    }
}

// How many rows does this item have?
int saklib::Project_Manager::outliner_row_count_root() const
{
    return root_elementids().size();
}
int saklib::Project_Manager::outliner_row_count(ElementID const& elementid) const
{
    return outliner_children(elementid).size();
}
int saklib::Project_Manager::outliner_row_count(AttributeID const& attributeid) const
{
    return outliner_children(attributeid).size();
}

// What is the parent of this item?
saklib::AttributeID saklib::Project_Manager::parent_of(ElementID const& elementid) const
{
    return m_element_manager.element_parent(elementid);
}
saklib::ElementID saklib::Project_Manager::parent_of(AttributeID const& attributeid) const
{
    return attributeid.elementid();
}

// What row is this in its parent as far as the model is concerned?
int saklib::Project_Manager::outliner_row_in_parent(ElementID const& elementid) const
{
    auto parent = parent_of(elementid);
    auto siblings = outliner_children(parent);
    int row = 0;
    for (auto sibling : siblings)
    {
        if (sibling == elementid)
        {
            return row;
        }
        ++row;
    }
    return 0;
}
int saklib::Project_Manager::outliner_row_in_parent(AttributeID const& attributeid) const
{
    auto parent = parent_of(attributeid);
    auto siblings = outliner_children(parent);
    int row = 0;
    for (auto sibling : siblings)
    {
        if (sibling == attributeid)
        {
            return row;
        }
        ++row;
    }
    return 0;
}



// Command History
//------------------------------------------------------------
// Provide limited access to the underlying history
//Command_History const& command_history() const;

// Will calling undo do anything?
bool saklib::Project_Manager::can_undo() const
{
    return m_command_history.can_undo();
}

// Will calling redo do anything?
bool saklib::Project_Manager::can_redo() const
{
    return m_command_history.can_redo();
}

// How many times can undo() be called()?
saklib::size_type saklib::Project_Manager::undo_count() const
{
    return m_command_history.undo_count();
}

// How many times can redo() be called()?
saklib::size_type saklib::Project_Manager::redo_count() const
{
    return m_command_history.redo_count();
}

// Call unexecute() in the current command and step back one in the history.
void saklib::Project_Manager::undo()
{
    m_command_history.undo();
    command_history_changed();
}

// Step forward one in the history and call execute() on that command.
void saklib::Project_Manager::redo()
{
    m_command_history.redo();
    command_history_changed();
}

// Clear all stored commands.
void saklib::Project_Manager::clear_history()
{
    m_command_history.clear();
    command_history_changed();
}

saklib::size_type saklib::Project_Manager::command_ref_count(ElementID const& elementid) const
{
    return m_element_manager.command_ref_count(elementid);
}

void saklib::Project_Manager::increment_command_ref_count(ElementID const& elementid)
{
    if (elementid.is_valid() && has_elementid(elementid))
    {
        m_element_manager.increment_command_ref_count(elementid);
    }
}
void saklib::Project_Manager::increment_command_ref_count(AttributeID const& attributeid)
{
    increment_command_ref_count(attributeid.elementid());
}

void saklib::Project_Manager::decrement_command_ref_count(ElementID const& elementid)
{
    if (elementid.is_valid() && has_elementid(elementid))
    {
        m_element_manager.decrement_command_ref_count(elementid);
        if (m_element_manager.command_ref_count(elementid) == 0 // no commands use it now
            && !element_parent(elementid).is_valid()            // it has no parent
            && !element_can_be_root(elementid) )                // it cannot be parentless
        {
            destroy_element(elementid);
        }
    }
}
void saklib::Project_Manager::decrement_command_ref_count(AttributeID const& attributeid)
{
    decrement_command_ref_count(attributeid.elementid());
}


// Call whenever commands are issued or called
void saklib::Project_Manager::command_history_changed()
{
    observers_undo_counts_changed(m_command_history.undo_count(), m_command_history.redo_count());
}




// Internal
//============================================================
void saklib::Project_Manager::assert_element(ElementID const& elementid) const
{
    assert(elementid.is_valid());
    assert(this->has_elementid(elementid));
}

void saklib::Project_Manager::attribute_changed(AttributeID const& attributeid)
{
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

void saklib::Project_Manager::set_unsaved_edits(bool state)
{
    if (m_unsaved_edits != state)
    {
        m_unsaved_edits = state;
        observers_unsaved_edits_changed(state);
    }
}

// Observer Signals
//============================================================
void saklib::Project_Manager::observers_begin_model_reset() const
{
    all_observers_function(&Project_Observer::begin_model_reset);
}
void saklib::Project_Manager::observers_end_model_reset() const
{
    all_observers_function(&Project_Observer::end_model_reset);
}

void saklib::Project_Manager::observers_element_name_changed(ElementID const& elementid) const
{
    all_observers_function(&Project_Observer::element_name_changed, elementid);
}
void saklib::Project_Manager::observers_element_parent_changed(ElementID const& elementid) const
{
    all_observers_function(&Project_Observer::element_parent_changed, elementid);
}
void saklib::Project_Manager::observers_element_destroyed(ElementID const& elementid) const
{
    all_observers_function(&Project_Observer::element_destroyed, elementid);
}


void saklib::Project_Manager::observers_attribute_value_changed(AttributeID const& attributeid) const
{
    all_observers_function(&Project_Observer::attribute_value_changed, attributeid);
}

void saklib::Project_Manager::observers_unsaved_edits_changed(bool state) const
{
    all_observers_function(&Project_Observer::unsaved_edits_changed, state);
}
void saklib::Project_Manager::observers_undo_counts_changed(size_type undo_count, size_type redo_count) const
{
    all_observers_function(&Project_Observer::undo_counts_changed, undo_count, redo_count);
}


