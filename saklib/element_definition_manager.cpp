#include "element_definition_manager.h"


// Internal Manager
//============================================================
Saklib::Element_Definition_Manager::Element_Definition_Manager() :
    m_definitions{}
{}

Saklib::Element_Definition_Manager::~Element_Definition_Manager() = default;

// Interface
//============================================================
// Is an Element_Definition with this type registered?
bool Saklib::Element_Definition_Manager::definition_exists(String const& type) const
{
    return find_definition(type) != m_definitions.cend();
}
// Is an Element_Definition with this exact configuration registered?
bool Saklib::Element_Definition_Manager::definition_exists(Element_Definition const& definition) const
{
    return find_definition(definition) != m_definitions.cend();
}
// If an Element_Definition with the same configuration as arg does not exist, add it do the definitions
bool Saklib::Element_Definition_Manager::try_add_definition(Element_Definition&& definition)
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
void Saklib::Element_Definition_Manager::add_override_definition(Element_Definition&& definition)
{
    auto found_definition = find_definition(definition);
    if (found_definition != m_definitions.end())
        m_definitions.insert(found_definition, std::forward<Element_Definition>(definition));
    else
        add_definition(std::forward<Element_Definition>(definition));
}
// Get a vector of the registered types
Saklib::Vector_String Saklib::Element_Definition_Manager::definition_types() const
{
    Vector<String> result{};
    for (auto const& definition : m_definitions)
        result.push_back(definition.type());
    return result;
}


// Get the definition
Saklib::Element_Definition const& Saklib::Element_Definition_Manager::definition(String const& type) const
{
    auto found_definition = find_definition(type);
    assert(found_definition != m_definitions.cend());
    return *found_definition;
}

Saklib::Vector<Saklib::Element_Definition>::iterator Saklib::Element_Definition_Manager::find_definition(String const& type)
{
    auto compare_definition_type = [&type](Element_Definition const& definition) { return definition.type() == type; };
    return std::find_if(m_definitions.begin(), m_definitions.end(), compare_definition_type);
}
Saklib::Vector<Saklib::Element_Definition>::const_iterator Saklib::Element_Definition_Manager::find_definition(String const& type) const
{
    auto compare_definition_type = [&type](Element_Definition const& definition) { return definition.type() == type; };
    return std::find_if(m_definitions.cbegin(), m_definitions.cend(), compare_definition_type);
}
Saklib::Vector<Saklib::Element_Definition>::iterator Saklib::Element_Definition_Manager::find_definition(Element_Definition const& definition)
{
    return std::find(m_definitions.begin(), m_definitions.end(), definition);
}
Saklib::Vector<Saklib::Element_Definition>::const_iterator Saklib::Element_Definition_Manager::find_definition(Element_Definition const& definition) const
{
    return std::find(m_definitions.cbegin(), m_definitions.cend(), definition);
}

void Saklib::Element_Definition_Manager::add_definition(Element_Definition&& definition)
{
    auto less_definition_type = [&definition](Element_Definition const& other) { return other.type() < definition.type(); };
    auto position = std::find_if(m_definitions.cbegin(), m_definitions.cend(), less_definition_type);
    m_definitions.insert(position, std::forward<Element_Definition>(definition));
}
