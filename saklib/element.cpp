#include "element.h"
#include "all_attributes.h"
#include <algorithm>

Saklib::Element::Element_Definition_Manager Saklib::Element::s_element_definition_manager{};

// Internal Factory Access
//============================================================
// Is an Element_Defintion with this type registered?
bool Saklib::Element::definition_exists(String const& type)
{
    return s_element_definition_manager.definition_exists(type);
}
// Is an Element_Defintion with this exact configuration registered?
bool Saklib::Element::definition_exists(Element_Definition const& definition)
{
    return s_element_definition_manager.definition_exists(definition);
}
// Is an Element_Defintion with the same configuration as arg does not exist, add it do the definitions 
bool Saklib::Element::try_add_definition(Element_Definition&& definition)
{
    return s_element_definition_manager.try_add_definition(std::forward<Element_Definition>(definition));
}
// Add this Element_Definition, overriding any definitions that might match
void Saklib::Element::add_override_definition(Element_Definition&& definition)
{
    s_element_definition_manager.add_override_definition(std::forward<Element_Definition>(definition));
}
// Get a vector of the registered types
Saklib::Vector_String Saklib::Element::get_registered_types()
{
    return s_element_definition_manager.get_registered_types();
}

// Special 6
//============================================================
Saklib::Element::Element(String const& type) :
    m_type(initialise_type_from_definition_of(type)),
    m_name(initialise_name_from_definition_of(type)),
    m_can_be_root(initialise_can_be_root_from_definition_of(type)),
    m_attributes(initialise_attributes_from_definition_of(type))
{}
/*
Saklib::Element::Element(String const& type, String const& name):
    m_type(initialise_type_from_definition_of(type)),
    m_name(name),
    m_attributes(initialise_attributes_from_definition_of(type))
{}
*/
Saklib::Element::~Element() = default;


Saklib::Element::Element(Element && other) :
    m_type(std::move(other.m_type)),
    m_name(std::move(other.m_name)),
    m_can_be_root(std::move(other.m_can_be_root)),
    m_attributes(std::move(other.m_attributes))
{
}
Saklib::Element& Saklib::Element::operator=(Element && other)
{
    m_type = std::move(other.m_type);
    m_name = std::move(other.m_name);
    m_can_be_root = std::move(other.m_can_be_root);
    m_attributes = std::move(other.m_attributes);

    return *this;
}

// Basic Access
//============================================================
Saklib::String const& Saklib::Element::type() const
{
    return m_type;
}

bool Saklib::Element::can_be_root() const
{
    return m_can_be_root;
}

Saklib::String const& Saklib::Element::name() const
{
    return m_name;
}
void Saklib::Element::set_name(String const& name)
{
    m_name = name;
}

// Attributes Access
//============================================================
Saklib::size_type Saklib::Element::attribute_count() const
{
    return m_attributes.size();
}
bool Saklib::Element::has_attribute(String const& name) const
{
    // probably want an Attribute typematching functor here
    return std::find_if(m_attributes.cbegin(), m_attributes.cend(), [&name](Uptr<Attribute> const& a){ assert(a != nullptr); return a->name() == name; }) != m_attributes.cend();
}
Saklib::Attribute* Saklib::Element::attribute(String const& name) const
{
    auto found = std::find_if(m_attributes.begin(), m_attributes.end(), [&name](Uptr<Attribute> const& a){ assert(a != nullptr); return a->name() == name; });
    if (found != m_attributes.end())
    {
        // break if we got here and found an invalid attribute
        return found->get();
    }
    else
        return nullptr;
}
Saklib::Attribute* Saklib::Element::attribute(size_type index) const
{
    if (index < m_attributes.size())
    {
        return m_attributes.at(index).get();
    }
    else
        return nullptr;
}
/*
Saklib::Attribute* Saklib::Element::add_attribute(String const& name, Type_Enum type)
{
    if (!has_attribute(name))
    {
        m_attributes.push_back(Uptr<Attribute>(nullptr));
        return m_attributes.back().get();
    }
    else
        return nullptr;
}
Saklib::Attribute* Saklib::Element::add_attribute(Attribute* newAttribute)
{
    if (!has_attribute(newAttribute->name()))
    {
        m_attributes.push_back(Uptr<Attribute>(newAttribute));
        return m_attributes.back().get();
    }
    else
        return nullptr;
}
Saklib::Attribute* Saklib::Element::add_attribute(Uptr<Attribute>& newAttribute)
{
    if (!has_attribute(newAttribute->name()))
    {
        m_attributes.push_back(Uptr<Attribute>(newAttribute.release()));
        return m_attributes.back().get();
    }
    else
        return nullptr;
}
Saklib::Attribute* Saklib::Element::add_attribute(Uptr<Attribute> && newAttribute)
{
    if (!has_attribute(newAttribute->name()))
    {
        m_attributes.push_back(std::move(newAttribute));
        return m_attributes.back().get();
    }
    else
        return nullptr;
}
*/

Saklib::Vector_String Saklib::Element::attribute_names() const
{
    Vector_String result{};
    for (auto const& attribute : m_attributes)
        result.push_back(attribute->name());
    return result;
}

Saklib::Vector<Saklib::Uptr<Saklib::Attribute>>& Saklib::Element::attributes()
{
    return m_attributes;
}
Saklib::Vector<Saklib::Uptr<Saklib::Attribute>> const& Saklib::Element::attributes() const
{
    return m_attributes;
}


// Initialisation Helpers
//============================================================

// Initialiser helpers
Saklib::String Saklib::Element::initialise_type_from_definition_of(String const& type)
{
    return s_element_definition_manager.get_type_from_definition_of(type);
}
Saklib::String Saklib::Element::initialise_name_from_definition_of(String const& type)
{
    return s_element_definition_manager.get_type_from_definition_of(type);
}
bool Saklib::Element::initialise_can_be_root_from_definition_of(String const& type)
{
    return s_element_definition_manager.get_can_be_root_from_definition_of(type);
}

Saklib::Vector<Saklib::Uptr<Saklib::Attribute>> Saklib::Element::initialise_attributes_from_definition_of(String const& type)
{
    return s_element_definition_manager.get_attributes_from_definition_of(type);
}


// Internal Manager
//============================================================
Saklib::Element::Element_Definition_Manager::Element_Definition_Manager() :
    m_element_definitions{}
{}

// Interface
//============================================================
// Is an Element_Definition with this type registered?
bool Saklib::Element::Element_Definition_Manager::definition_exists(String const& type) const
{
    return find_definition(type) != m_element_definitions.cend();
}
// Is an Element_Definition with this exact configuration registered?
bool Saklib::Element::Element_Definition_Manager::definition_exists(Element_Definition const& definition) const
{
    return find_definition(definition) != m_element_definitions.cend();
}
// If an Element_Definition with the same configuration as arg does not exist, add it do the definitions 
bool Saklib::Element::Element_Definition_Manager::try_add_definition(Element_Definition&& definition)
{
    if (definition_exists(definition))
        return false;
    else
    {
        add_definition(std::forward<Element_Definition>(definition));
        return true;
    }
}
// Add this Element_Definition, overriding any definitions that might match
void Saklib::Element::Element_Definition_Manager::add_override_definition(Element_Definition&& definition)
{
    auto found_definition = find_definition(definition);
    if (found_definition != m_element_definitions.end())
        m_element_definitions.insert(found_definition, std::forward<Element_Definition>(definition));
    else
        add_definition(std::forward<Element_Definition>(definition));
}
// Get a vector of the registered types
Saklib::Vector_String Saklib::Element::Element_Definition_Manager::get_registered_types() const
{
    Vector<String> result{};
    for (auto const& definition : m_element_definitions)
        result.push_back(definition.type());
    return result;
}


Saklib::String Saklib::Element::Element_Definition_Manager::get_type_from_definition_of(String const& type) const
{
    assert(find_definition(type) != m_element_definitions.cend());
    return find_definition(type)->type();
}
Saklib::Vector<Saklib::Uptr<Saklib::Attribute>> Saklib::Element::Element_Definition_Manager::get_attributes_from_definition_of(String const& type) const
{
    Vector<Uptr<Attribute>> result{};
    for (auto const& definition : find_definition(type)->attribute_definitions())
        result.push_back(make_Attribute(definition));

    return result;
}
bool Saklib::Element::Element_Definition_Manager::get_can_be_root_from_definition_of(String const& type) const
{
    return find_definition(type)->can_be_root();
}

Saklib::Vector<Saklib::Element_Definition>::iterator Saklib::Element::Element_Definition_Manager::find_definition(String const& type)
{
    auto compare_definition_type = [&type](Element_Definition const& definition) { return definition.type() == type; };
    return std::find_if(m_element_definitions.begin(), m_element_definitions.end(), compare_definition_type);
}
Saklib::Vector<Saklib::Element_Definition>::const_iterator Saklib::Element::Element_Definition_Manager::find_definition(String const& type) const
{
    auto compare_definition_type = [&type](Element_Definition const& definition) { return definition.type() == type; };
    return std::find_if(m_element_definitions.cbegin(), m_element_definitions.cend(), compare_definition_type);
}
Saklib::Vector<Saklib::Element_Definition>::iterator Saklib::Element::Element_Definition_Manager::find_definition(Element_Definition const& definition)
{
    return std::find(m_element_definitions.begin(), m_element_definitions.end(), definition);
}
Saklib::Vector<Saklib::Element_Definition>::const_iterator Saklib::Element::Element_Definition_Manager::find_definition(Element_Definition const& definition) const
{
    return std::find(m_element_definitions.cbegin(), m_element_definitions.cend(), definition);
}


void Saklib::Element::Element_Definition_Manager::add_definition(Element_Definition&& definition)
{
    auto less_definition_type = [&definition](Element_Definition const& other) { return other.type() < definition.type(); };
    auto position = std::find_if(m_element_definitions.cbegin(), m_element_definitions.cend(), less_definition_type);
    m_element_definitions.insert(position, std::forward<Element_Definition>(definition));
}
