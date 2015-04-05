#include "project_manager.h"

#include "element.h"
#include "attribute_type.h"

#include "qtlib/qstring_operations.h"

#include "project_observer.h"

#include "internal_element_definitions.h"

// Special 6
//============================================================
Saklib::Project_Manager::Project_Manager() :
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

Saklib::Project_Manager::Project_Manager(Path const& filepath) :
    Project_Manager()
{
    // Store the filename in this attribute
    open_project(filepath);
}
Saklib::Project_Manager::~Project_Manager()
{
    clear();
}

// Interface
//============================================================


// Overall Project
//------------------------------------------------------------


void Saklib::Project_Manager::new_project(Path const& filepath)
{
    clear();

    m_project_elementid = make_element("Project");
    m_project_filepath = m_element_manager.attributeid(m_project_elementid, "Filepath");

    set_project_filepath(filepath);

    observers_unsaved_edits_changed(false); // force this signal if m_unsaved_edits was false before
}

void Saklib::Project_Manager::open_project(Path const& filepath)
{
    clear();

    // this should load from the file...

    m_project_elementid = make_element("Project");
    m_project_filepath = m_element_manager.attributeid(m_project_elementid, "Filepath");

    set_project_filepath(filepath);

    observers_unsaved_edits_changed(false); // force this signal if m_unsaved_edits was false before
}


void Saklib::Project_Manager::save() const
{
    observers_unsaved_edits_changed(false);
}
void Saklib::Project_Manager::save_as(Path const& filepath)
{
    set_project_filepath(filepath);
    save();
}


void Saklib::Project_Manager::clear()
{
    m_element_manager.clear();
    m_command_history.clear();
    m_unsaved_edits = false;
}




Saklib::ElementID Saklib::Project_Manager::project_elementid() const
{
    return m_project_elementid;
}
Saklib::Path const& Saklib::Project_Manager::project_filepath() const
{
    return Saklib::attribute_type_cast<Path>(m_element_manager.attribute(m_project_filepath))->value();
}
void Saklib::Project_Manager::set_project_filepath(Path const& filepath)
{
    m_element_manager.element(m_project_elementid).set_name(Saklib::to_String(filepath.filename()));
    Saklib::attribute_type_cast<Path>(m_element_manager.attribute(m_project_filepath))->set_value(filepath);

    // tell observers the filepath changed?
}



void Saklib::Project_Manager::add_observer(Project_Observer*const observer)
{
    auto found = std::find(m_observers.cbegin(), m_observers.cend(), observer);
    if (found == m_observers.cend())
    {
        m_observers.push_back(observer);
    }
}

void Saklib::Project_Manager::remove_observer(Project_Observer*const observer)
{
    auto found = std::find(m_observers.cbegin(), m_observers.cend(), observer);
    if (found != m_observers.cend())
    {
        m_observers.erase(found);
    }
}

// Lifetime
//------------------------------------------------------------

void Saklib::Project_Manager::register_element_definition(Element_Definition&& definition)
{
    m_internal_element_definitions.add_override_definition(std::forward<Element_Definition>(definition));
}

bool Saklib::Project_Manager::has_element_definition(String const& type) const
{
    return m_internal_element_definitions.definition_exists(type);
}
Saklib::Element_Definition const& Saklib::Project_Manager::element_definition(String const& type) const
{
    return m_internal_element_definitions.definition(type);
}

Saklib::Vector_String Saklib::Project_Manager::all_registered_element_types() const
{
    return m_internal_element_definitions.definition_types();
}

// Make a new Element and return all info about it
Saklib::ElementID Saklib::Project_Manager::make_element(String const& type)
{
    assert(has_element_definition(type));
    ElementID newid = m_element_manager.make_element(element_definition(type));
    return newid;
}

// Destory an Element and everything associated with it
void Saklib::Project_Manager::destroy_element(ElementID elementid)
{
    m_element_manager.destroy_element(elementid);
    observers_element_destroyed(elementid);
}

// Does this refer to something in this? - rename these to has(blah) ?
bool Saklib::Project_Manager::is_valid(ElementID elementid) const
{
    return m_element_manager.is_valid(elementid);
}
bool Saklib::Project_Manager::is_valid(AttributeID attributeid) const
{
    return m_element_manager.is_valid(attributeid);
}

// Elements
//------------------------------------------------------------
Saklib::Element& Saklib::Project_Manager::element(ElementID elementid)
{
    assert_element(elementid);
    return m_element_manager.element(elementid);
}

Saklib::Element const& Saklib::Project_Manager::element(ElementID elementid) const
{
    assert_element(elementid);
    return m_element_manager.element(elementid);
}

Saklib::String const& Saklib::Project_Manager::element_type(ElementID elementid) const
{
    assert_element(elementid);
    return m_element_manager.element(elementid).type();
}

Saklib::String const& Saklib::Project_Manager::element_name(ElementID elementid) const
{
    assert_element(elementid);
    return m_element_manager.element(elementid).name();
}

void Saklib::Project_Manager::element_set_name(ElementID elementid, String const& value)
{
    assert_element(elementid);
    // maintaining unique names should have been done before getting here

    m_element_manager.element(elementid).set_name(value);
    observers_element_name_changed(elementid);
    set_unsaved_edits(true);
}

bool Saklib::Project_Manager::element_can_be_root(ElementID elementid) const
{
    assert_element(elementid);
    return m_element_manager.element(elementid).can_be_root();
}

Saklib::AttributeID Saklib::Project_Manager::element_parent(ElementID elementid) const
{
    assert_element(elementid);
    return m_element_manager.parent(elementid);
}

void Saklib::Project_Manager::element_set_parent(ElementID elementid, AttributeID attributeid)
{
    if (elementid.is_valid())
    {
        assert_element(elementid);
        m_element_manager.set_parent(elementid, attributeid);

        observers_element_parent_changed(elementid);
        set_unsaved_edits(true);
    }
}

// Attributes
//------------------------------------------------------------
Saklib::AttributeID Saklib::Project_Manager::attributeid(ElementID elementid, String const& attribute_name) const
{
    return m_element_manager.attributeid(elementid, attribute_name);
}

Saklib::Attribute *const Saklib::Project_Manager::attribute(AttributeID attributeid)
{
    return m_element_manager.attribute(attributeid);
}
Saklib::Attribute *const Saklib::Project_Manager::attribute(ElementID elementid, size_type attribute_index)
{
    return m_element_manager.attribute(elementid, attribute_index);
}
Saklib::Attribute *const Saklib::Project_Manager::attribute(ElementID elementid, String const& attribute_name)
{
    return m_element_manager.attribute(elementid, attribute_name);
}


Saklib::Attribute const*const Saklib::Project_Manager::attribute(AttributeID attributeid) const
{
    return m_element_manager.attribute(attributeid);
}
Saklib::Attribute const*const Saklib::Project_Manager::attribute(ElementID elementid, size_type attribute_index) const
{
    return m_element_manager.attribute(elementid, attribute_index);
}
Saklib::Attribute const*const Saklib::Project_Manager::attribute(ElementID elementid, String const& attribute_name) const
{
    return m_element_manager.attribute(elementid, attribute_name);
}

Saklib::String const& Saklib::Project_Manager::attribute_name(AttributeID attributeid) const
{
    return m_element_manager.attribute(attributeid)->name();
}
Saklib::Type_Enum Saklib::Project_Manager::attribute_type_enum(AttributeID attributeid) const
{
    return m_element_manager.attribute(attributeid)->type_enum();
}
Saklib::String Saklib::Project_Manager::attribute_type_string(AttributeID attributeid) const
{
    return m_element_manager.attribute(attributeid)->type_string();
}



// Attribute_Type<T>
//------------------------------------------------------------
// These functions set the data without question, and tell the model and widget to update.
template <>
void Saklib::Project_Manager::attribute_set_value<Saklib::ElementID>(AttributeID attributeid, ElementID const& value)
{
    assert_attribute<ElementID>(attributeid);
    observers_begin_model_reset();

    auto attribute = attribute_type_cast<ElementID>(attributeid);
    ElementID old_value = attribute->value();
    ElementID new_value = value;

    attribute->set_value(new_value);
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
Saklib::size_type Saklib::Project_Manager::any_attribute_vector_size(AttributeID attributeid) const
{
    auto attribute_type = attribute_type_enum(attributeid);
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return attribute_vector_size<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid);
    case Type_Enum::Vector_Int:         return attribute_vector_size<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid);
    case Type_Enum::Vector_Double:      return attribute_vector_size<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid);
    case Type_Enum::Vector_String:      return attribute_vector_size<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid);
    case Type_Enum::Vector_Path:        return attribute_vector_size<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid);
    case Type_Enum::Vector_ElementID:   return attribute_vector_size<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid);
    default: return 0;
    }
}

// if the attribute is a vector, return it's size, otherwise 0
bool Saklib::Project_Manager::any_attribute_vector_empty(AttributeID attributeid) const
{
    auto attribute_type = attribute_type_enum(attributeid);
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return attribute_vector_empty<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid);
    case Type_Enum::Vector_Int:         return attribute_vector_empty<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid);
    case Type_Enum::Vector_Double:      return attribute_vector_empty<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid);
    case Type_Enum::Vector_String:      return attribute_vector_empty<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid);
    case Type_Enum::Vector_Path:        return attribute_vector_empty<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid);
    case Type_Enum::Vector_ElementID:   return attribute_vector_empty<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid);
    default: return false;
    }
}


void Saklib::Project_Manager::any_attribute_vector_clear(AttributeID attributeid)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid); break;
    case Type_Enum::Vector_Int:         attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid); break;
    case Type_Enum::Vector_Double:      attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid); break;
    case Type_Enum::Vector_String:      attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid); break;
    case Type_Enum::Vector_Path:        attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid); break;
    case Type_Enum::Vector_ElementID:   attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid); break;
    default: assert(false); // called on the wrong type
    }
}

void Saklib::Project_Manager::any_attribute_vector_pop_back(AttributeID attributeid)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid); break;
    case Type_Enum::Vector_Int:         attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid); break;
    case Type_Enum::Vector_Double:      attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid); break;
    case Type_Enum::Vector_String:      attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid); break;
    case Type_Enum::Vector_Path:        attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid); break;
    case Type_Enum::Vector_ElementID:   attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid); break;
    default: assert(false); // called on the wrong type
    }
}
void Saklib::Project_Manager::any_attribute_vector_swap_at(AttributeID attributeid, size_type index, size_type other_index)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_Int:         attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_Double:      attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_String:      attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_Path:        attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid, index, other_index); break;
    case Type_Enum::Vector_ElementID:   attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid, index, other_index); break;
    default: assert(false); // called on the wrong type
    }
}

// Attribute_Type<Vector<T>> Forwarding Functions
//------------------------------------------------------------
// We must know the type to use these ones, and they should be called without specifying the
// explicitly so that the ElementID overload can be used (specialisation for it doesn't work).

template <>
void Saklib::Project_Manager::attribute_vector_set_vector<Saklib::ElementID>(AttributeID attributeid, Vector<ElementID> const& other_vector)
{
    assert_attribute<Vector_ElementID>(attributeid);
    observers_begin_model_reset();

    auto attribute = attribute_type_cast<Vector_ElementID>(attributeid);
    Vector_ElementID old_vector = attribute->vector();

    attribute->set_vector(other_vector);

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
void Saklib::Project_Manager::attribute_vector_clear<Saklib::ElementID>(AttributeID attributeid)
{
    assert_attribute<Vector_ElementID>(attributeid);
    observers_begin_model_reset();

    auto attribute = attribute_type_cast<Vector_ElementID>(attributeid);
    Vector_ElementID old_vector = attribute->vector();

    attribute->clear();

    for (auto elementid : old_vector)
    {
        element_set_parent(elementid, invalid_attributeid());
    }
    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);

    set_unsaved_edits(true);
}

template <>
void Saklib::Project_Manager::attribute_vector_set_at<Saklib::ElementID>(AttributeID attributeid, size_type index, ElementID const& value)
{
    assert_attribute<Vector_ElementID>(attributeid);
    observers_begin_model_reset();

    auto attribute = attribute_type_cast<Vector_ElementID>(attributeid);
    ElementID old_value = attribute->at(index);
    ElementID new_value = value;

    attribute->set_at(index, new_value);
    element_set_parent(new_value, attributeid);
    element_set_parent(old_value, invalid_attributeid());

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

template<>
void Saklib::Project_Manager::attribute_vector_set_front<Saklib::ElementID>(AttributeID attributeid, ElementID const& value)
{
    assert_attribute<Vector_ElementID>(attributeid);
    observers_begin_model_reset();

    auto attribute = attribute_type_cast<Vector_ElementID>(attributeid);
    ElementID old_value = attribute->front();
    ElementID new_value = value;

    attribute->set_front(new_value);
    element_set_parent(new_value, attributeid);
    element_set_parent(old_value, invalid_attributeid());

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

template<>
void Saklib::Project_Manager::attribute_vector_set_back<Saklib::ElementID>(AttributeID attributeid, ElementID const& value)
{
    assert_attribute<Vector_ElementID>(attributeid);
    observers_begin_model_reset();

    auto attribute = attribute_type_cast<Vector_ElementID>(attributeid);
    ElementID old_value = attribute->front();
    ElementID new_value = value;

    attribute->set_back(new_value);
    element_set_parent(new_value, attributeid);
    element_set_parent(old_value, invalid_attributeid());

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

template <>
void Saklib::Project_Manager::attribute_vector_swap_at<Saklib::ElementID>(AttributeID attributeid, size_type index, size_type other_index)
{
    assert_attribute<Vector_ElementID>(attributeid);
    observers_begin_model_reset();

    auto attribute = attribute_type_cast<Vector_ElementID>(attributeid);
    attribute->swap_at(index, other_index);

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

template<>
void Saklib::Project_Manager::attribute_vector_push_back<Saklib::ElementID>(AttributeID attributeid, ElementID const& value)
{
    assert_attribute<Vector_ElementID>(attributeid);
    observers_begin_model_reset();

    auto attribute = this->attribute_type_cast<Vector_ElementID>(attributeid);

    attribute->push_back(value);
    element_set_parent(value, attributeid);

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}
template<>
void Saklib::Project_Manager::attribute_vector_pop_back<Saklib::ElementID>(AttributeID attributeid)
{
    assert_attribute<Vector_ElementID>(attributeid);
    observers_begin_model_reset();

    auto attribute = this->attribute_type_cast<Vector_ElementID>(attributeid);

    ElementID back_value = attribute->back();
    attribute->pop_back();
    element_set_parent(back_value, invalid_attributeid());

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

template<>
void Saklib::Project_Manager::attribute_vector_insert_at<Saklib::ElementID>(AttributeID attributeid, size_type index, ElementID const& value)
{
    assert_attribute<Vector_ElementID>(attributeid);
    observers_begin_model_reset();

    auto attribute = this->attribute_type_cast<Vector_ElementID>(attributeid);

    attribute->insert_at(index, value);
    element_set_parent(value, invalid_attributeid());

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}

template<>
void Saklib::Project_Manager::attribute_vector_remove_at<Saklib::ElementID>(AttributeID attributeid, size_type index)
{
    assert_attribute<Vector_ElementID>(attributeid);

    auto attribute = this->attribute_type_cast<Vector_ElementID>(attributeid);
    ElementID removed_value = attribute->at(index);

    observers_begin_model_reset();

    attribute->remove_at(index);
    element_set_parent(removed_value, invalid_attributeid());

    observers_end_model_reset();
    observers_attribute_value_changed(attributeid);
    set_unsaved_edits(true);
}


// Commands - indirect write access
//------------------------------------------------------------
// To support undoing edits use these functions to edit data from the outliner/widgets.

bool Saklib::Project_Manager::undoable_element_set_name(ElementID elementid, String const& value)
{
    // if conditions are right to issue a command
    if(elementid.is_valid()
       && this->is_valid(elementid)
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

bool Saklib::Project_Manager::undoable_any_attribute_vector_clear(AttributeID attributeid)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return undoable_attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid);
    case Type_Enum::Vector_Int:         return undoable_attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid);
    case Type_Enum::Vector_Double:      return undoable_attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid);
    case Type_Enum::Vector_String:      return undoable_attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid);
    case Type_Enum::Vector_Path:        return undoable_attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid);
    case Type_Enum::Vector_ElementID:   return undoable_attribute_vector_clear<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid);
    default: assert(false); // called on the wrong type
    }
    return false;
}

bool Saklib::Project_Manager::undoable_any_attribute_vector_swap_at(AttributeID attributeid, size_type index, size_type other_index)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return undoable_attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid, index, other_index);
    case Type_Enum::Vector_Int:         return undoable_attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid, index, other_index);
    case Type_Enum::Vector_Double:      return undoable_attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid, index, other_index);
    case Type_Enum::Vector_String:      return undoable_attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid, index, other_index);
    case Type_Enum::Vector_Path:        return undoable_attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid, index, other_index);
    case Type_Enum::Vector_ElementID:   return undoable_attribute_vector_swap_at<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid, index, other_index);
    default: assert(false); // called on the wrong type
    }
    return false;
}

bool Saklib::Project_Manager::undoable_any_attribute_vector_pop_back(AttributeID attributeid)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return undoable_attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid);
    case Type_Enum::Vector_Int:         return undoable_attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid);
    case Type_Enum::Vector_Double:      return undoable_attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid);
    case Type_Enum::Vector_String:      return undoable_attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid);
    case Type_Enum::Vector_Path:        return undoable_attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid);
    case Type_Enum::Vector_ElementID:   return undoable_attribute_vector_pop_back<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid);
    default: assert(false); // called on the wrong type
    }
    return false;
}

bool Saklib::Project_Manager::undoable_any_attribute_vector_remove_at(AttributeID attributeid, size_type index)
{
    auto attribute_type = attribute(attributeid)->type_enum();
    switch(attribute_type)
    {
    case Type_Enum::Vector_Bool:        return undoable_attribute_vector_remove_at<TypeHolder_vt<Type_Enum::Vector_Bool>>(attributeid, index);
    case Type_Enum::Vector_Int:         return undoable_attribute_vector_remove_at<TypeHolder_vt<Type_Enum::Vector_Int>>(attributeid, index);
    case Type_Enum::Vector_Double:      return undoable_attribute_vector_remove_at<TypeHolder_vt<Type_Enum::Vector_Double>>(attributeid, index);
    case Type_Enum::Vector_String:      return undoable_attribute_vector_remove_at<TypeHolder_vt<Type_Enum::Vector_String>>(attributeid, index);
    case Type_Enum::Vector_Path:        return undoable_attribute_vector_remove_at<TypeHolder_vt<Type_Enum::Vector_Path>>(attributeid, index);
    case Type_Enum::Vector_ElementID:   return undoable_attribute_vector_remove_at<TypeHolder_vt<Type_Enum::Vector_ElementID>>(attributeid, index);
    default: assert(false); // called on the wrong type
    }
    return false;
}



// Flat Access
//------------------------------------------------------------
Saklib::Vector_ElementID Saklib::Project_Manager::all_elementids() const
{
    return m_element_manager.all_elementids();
}
Saklib::Vector_ElementID Saklib::Project_Manager::root_elementids() const
{
    return m_element_manager.root_elementids();
}

// Model Interface
//------------------------------------------------------------
// Functions that provide data to the outliner model

// What are this item's children?
Saklib::Vector_AttributeID Saklib::Project_Manager::outliner_children(ElementID elementid) const
{
    // Assuming a valid ElementID...
    Vector_AttributeID results{};

    // For each Attribute by index
    auto const& attributes = element(elementid).attributes();
    for(size_type index = 0, end = attributes.size(); index != end; ++index)
    {
        AttributeID attributeid{elementid, index};
        // If the type is of interest
        Type_Enum type{attributes.at(index)->type_enum()};

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
Saklib::Vector_ElementID Saklib::Project_Manager::outliner_children(AttributeID attributeid) const
{
    // Assuming a valid AttributeID...
    Vector_ElementID results{};

    // If invalid get the root children
    if (!attributeid.is_valid())
    {
        return root_elementids();
    }

    Type_Enum type{attribute_type_enum(attributeid)};
    if (type == Type_Enum::ElementID)
    {
        // Get the ElementID held
        ElementID held_elementid = attribute_type_cast<ElementID>(attributeid)->value();
        if (held_elementid.is_valid())
        {
            results.push_back(held_elementid);
        }
    }
    else if (type == Type_Enum::Vector_ElementID)
    {
        // For each stored ElementID
        auto const& elementid_vector = attribute_type_cast<Vector_ElementID>(attributeid)->vector();
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
Saklib::AttributeID Saklib::Project_Manager::outliner_child_at_row(ElementID elementid, int row) const
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
Saklib::ElementID Saklib::Project_Manager::outliner_child_at_row(AttributeID attributeid, int row) const
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
int Saklib::Project_Manager::outliner_row_count_root() const
{
    return root_elementids().size();
}
int Saklib::Project_Manager::outliner_row_count(ElementID elementid) const
{
    return outliner_children(elementid).size();
}
int Saklib::Project_Manager::outliner_row_count(AttributeID attributeid) const
{
    return outliner_children(attributeid).size();
}

// What is the parent of this item?
Saklib::AttributeID Saklib::Project_Manager::parent_of(ElementID elementid) const
{
    return m_element_manager.parent(elementid);
}
Saklib::ElementID Saklib::Project_Manager::parent_of(AttributeID attributeid) const
{
    return attributeid.elementid();
}

// What row is this in its parent as far as the model is concerned?
int Saklib::Project_Manager::outliner_row_in_parent(ElementID elementid) const
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
int Saklib::Project_Manager::outliner_row_in_parent(AttributeID attributeid) const
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
bool Saklib::Project_Manager::can_undo() const
{
    return m_command_history.can_undo();
}

// Will calling redo do anything?
bool Saklib::Project_Manager::can_redo() const
{
    return m_command_history.can_redo();
}

// How many times can undo() be called()?
Saklib::size_type Saklib::Project_Manager::undo_count() const
{
    return m_command_history.undo_count();
}

// How many times can redo() be called()?
Saklib::size_type Saklib::Project_Manager::redo_count() const
{
    return m_command_history.redo_count();
}

// Call unexecute() in the current command and step back one in the history.
void Saklib::Project_Manager::undo()
{
    m_command_history.undo();
    command_history_changed();
}

// Step forward one in the history and call execute() on that command.
void Saklib::Project_Manager::redo()
{
    m_command_history.redo();
    command_history_changed();
}

// Clear all stored commands.
void Saklib::Project_Manager::clear_history()
{
    m_command_history.clear();
    command_history_changed();
}

Saklib::size_type Saklib::Project_Manager::command_ref_count(ElementID elementid) const
{
    return m_element_manager.command_ref_count(elementid);
}

void Saklib::Project_Manager::increment_command_ref_count(ElementID elementid)
{
    if (elementid.is_valid() && is_valid(elementid))
    {
        m_element_manager.increment_command_ref_count(elementid);
    }
}
void Saklib::Project_Manager::increment_command_ref_count(AttributeID attributeid)
{
    increment_command_ref_count(attributeid.elementid());
}

void Saklib::Project_Manager::decrement_command_ref_count(ElementID elementid)
{
    if (elementid.is_valid() && is_valid(elementid))
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
void Saklib::Project_Manager::decrement_command_ref_count(AttributeID attributeid)
{
    decrement_command_ref_count(attributeid.elementid());
}


// Call whenever commands are issued or called
void Saklib::Project_Manager::command_history_changed()
{
    observers_undo_counts_changed(m_command_history.undo_count(), m_command_history.redo_count());
}




// Internal
//============================================================
void Saklib::Project_Manager::assert_element(ElementID elementid) const
{
    assert(elementid.is_valid());
    assert(this->is_valid(elementid));
}

void Saklib::Project_Manager::set_unsaved_edits(bool state)
{
    if (m_unsaved_edits != state)
    {
        m_unsaved_edits = state;
        observers_unsaved_edits_changed(state);
    }
}

// Observer Signals
//============================================================
void Saklib::Project_Manager::observers_begin_model_reset() const
{
    all_observers_function(&Project_Observer::begin_model_reset);
}
void Saklib::Project_Manager::observers_end_model_reset() const
{
    all_observers_function(&Project_Observer::end_model_reset);
}

void Saklib::Project_Manager::observers_element_name_changed(ElementID elementid) const
{
    all_observers_function(&Project_Observer::element_name_changed, elementid);
}
void Saklib::Project_Manager::observers_element_parent_changed(ElementID elementid) const
{
    all_observers_function(&Project_Observer::element_parent_changed, elementid);
}
void Saklib::Project_Manager::observers_element_destroyed(ElementID elementid) const
{
    all_observers_function(&Project_Observer::element_destroyed, elementid);
}


void Saklib::Project_Manager::observers_attribute_value_changed(AttributeID attributeid) const
{
    all_observers_function(&Project_Observer::attribute_value_changed, attributeid);
}

void Saklib::Project_Manager::observers_unsaved_edits_changed(bool state) const
{
    all_observers_function(&Project_Observer::unsaved_edits_changed, state);
}
void Saklib::Project_Manager::observers_undo_counts_changed(size_type undo_count, size_type redo_count) const
{
    all_observers_function(&Project_Observer::undo_counts_changed, undo_count, redo_count);
}


