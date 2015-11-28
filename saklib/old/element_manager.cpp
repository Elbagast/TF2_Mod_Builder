#include "element_manager.h"
#include "element_definition.h"
#include "attribute.h"
#include <cassert>
#include <algorithm>

// Special 6
//============================================================

saklib::Element_Manager::Element_Manager() :
    m_map{},
    m_next_id{ 0 }
{
}
//saklib::Element_Manager::~Element_Manager() = default;
// Interface
//============================================================
// Build a new Map_Entry containing a new Element from type and return the id number
saklib::ElementID saklib::Element_Manager::make_element(Element_Definition const& definition, String const& name)
{
    ElementID newid{++m_next_id};

    String final_name{};
    if (name.empty())
    {
        final_name = definition.type();
    }
    final_name = make_name_unique(final_name);

    m_map.emplace(newid, Element_Cache(definition, final_name));
    return newid;
}

// Destory the Element associated with this id
void saklib::Element_Manager::destroy_element(ElementID const& elementid)
{
    m_map.erase(elementid);
}


// Is this AttributeID valid for this?
bool saklib::Element_Manager::has_elementid(ElementID const& elementid) const
{
    return elementid.is_valid() && m_map.find(elementid) != m_map.end();
}

// Access the parent of this ID
bool saklib::Element_Manager::has_parent(ElementID const& elementid) const
{
    auto found = m_map.find(elementid);
    return found != m_map.end() && found->second.m_parent.is_valid();
}
saklib::AttributeID saklib::Element_Manager::element_parent(ElementID const& elementid) const
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
        return found->second.m_parent;
    else
        return AttributeID();
}
void saklib::Element_Manager::set_element_parent(ElementID const& elementid, AttributeID owner)
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
        found->second.m_parent = owner;
}

// The name of a given Element
saklib::String const& saklib::Element_Manager::element_name(ElementID const& elementid) const
{
    auto found = m_map.find(elementid);
    assert(found != m_map.end());
    return found->second.m_element.name();
}

// Set an Element name, return true if the given name was unique
bool saklib::Element_Manager::set_element_name(ElementID const& elementid, String const& name)
{
    auto found = m_map.find(elementid);
    assert(found != m_map.end());
    auto& found_element = found->second.m_element;
    found_element.set_name(make_name_unique(name));
    return name == found_element.name();
}

// Access the Element associated with this id
saklib::Element* saklib::Element_Manager::element(ElementID const& elementid)
{
    auto found = m_map.find(elementid);
    if(found != m_map.end())
    {
        return &(found->second.m_element);
    }
    return nullptr;
}

saklib::Element const* saklib::Element_Manager::celement(ElementID const& elementid) const
{
    auto found = m_map.find(elementid);
    if(found != m_map.end())
    {
        return &(found->second.m_element);
    }
    return nullptr;
}


// Is this AttributeID valid for this?
bool saklib::Element_Manager::has_attributeid(AttributeID const& attributeid) const
{
    auto found = m_map.find(attributeid.elementid());
    return found != m_map.end() && attributeid.index() < found->second.m_element.attribute_count();
}


// Make an AttributeID from the given data
saklib::AttributeID saklib::Element_Manager::attributeid(ElementID const& elementid, size_type attribute_index) const
{
    auto found = m_map.find(elementid);
    if (found != m_map.end()
        && attribute_index < found->second.m_element.attribute_count())
        return AttributeID(elementid, attribute_index);
    else
        return AttributeID();
}
saklib::AttributeID saklib::Element_Manager::attributeid(ElementID const& elementid, String const& attribute_name) const
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
    {
        auto const& found_element = found->second.m_element;
        for (size_type attribute_index = 0, end = found_element.attribute_count(); attribute_index != end; ++attribute_index)
        {
            auto lp_attribute = found_element.cattribute(attribute_index);
            if (lp_attribute->name() == attribute_name)
            {
                return AttributeID(elementid, attribute_index);
            }
        }
    }

    return AttributeID();
}

// Access the Attribute associated with this id
saklib::Attribute* saklib::Element_Manager::attribute(AttributeID const& attributeid)
{
    auto found = m_map.find(attributeid.elementid());
    if (found != m_map.end()
        && attributeid.index() < found->second.m_element.attribute_count())
        return found->second.m_element.attribute(attributeid.index());
    else
        return nullptr;
}

saklib::Attribute* saklib::Element_Manager::attribute(ElementID const& elementid, size_type attribute_index)
{
    auto found = m_map.find(elementid);
    if (found != m_map.end()
        && attribute_index < found->second.m_element.attribute_count())
        return found->second.m_element.attribute(attribute_index);
    else
        return nullptr;
}

saklib::Attribute* saklib::Element_Manager::attribute(ElementID const& elementid, String const& attribute_name)
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
        return found->second.m_element.attribute(attribute_name);
    else
        return nullptr;
}


saklib::Attribute const* saklib::Element_Manager::cattribute(AttributeID const& attributeid) const
{
    const_iterator found = m_map.find(attributeid.elementid());
    if (found != m_map.end()
        && attributeid.index() < found->second.m_element.attribute_count())
        return found->second.m_element.cattribute(attributeid.index());
    else
        return nullptr;
}

saklib::Attribute const* saklib::Element_Manager::cattribute(ElementID const& elementid, size_type attribute_index) const
{
    auto found = m_map.find(elementid);
    if (found != m_map.end()
        && attribute_index < found->second.m_element.attribute_count())
        return found->second.m_element.cattribute(attribute_index);
    else
        return nullptr;
}

saklib::Attribute const* saklib::Element_Manager::cattribute(ElementID const& elementid, String const& attribute_name) const
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
        return found->second.m_element.cattribute(attribute_name);
    else
        return nullptr;
}


// Typed Access to Attributes

// Auxillary access
std::vector<saklib::ElementID> saklib::Element_Manager::all_elementids() const
{
    std::vector<ElementID> result{};
    for (auto const& value : m_map)
    {
        assert(value.first.is_valid());
        result.push_back(value.first);
        assert(result.back().is_valid());
    }
    return result;
}
// ElementIDs that have no parent
std::vector<saklib::ElementID> saklib::Element_Manager::root_elementids() const
{
    std::vector<ElementID> result{};
    for (auto const& value : m_map)
    {
        if (!value.second.m_parent.is_valid() && value.second.m_element.can_be_root() )
        {
            assert(value.first.is_valid());
            result.push_back(value.first);
            assert(result.back().is_valid());
        }
    }
    return result;
}

// Names of all Elements
std::vector<saklib::String> saklib::Element_Manager::all_element_names() const
{
    std::vector<String> result{};
    for (auto const& value : m_map)
    {
        result.push_back(value.second.m_element.name());
    }
    return result;
}

// Destory everything
void saklib::Element_Manager::clear()
{
    m_map.clear();
    m_next_id = 0;
}

// Command Interface
//============================================================
// Bits that only Command objects will end up using

saklib::size_type saklib::Element_Manager::command_ref_count(ElementID const& elementid) const
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
    {
        return found->second.m_command_ref_count;
    }
    else
    {
        return 0;
    }
}

// Adjust ref counts
void saklib::Element_Manager::increment_command_ref_count(ElementID const& elementid)
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
    {
        found->second.m_command_ref_count += 1;
    }
}

void saklib::Element_Manager::decrement_command_ref_count(ElementID const& elementid)
{

    auto found = m_map.find(elementid);
    if (found != m_map.end())
    {
        assert(found->second.m_command_ref_count != 0); // for now...
        found->second.m_command_ref_count -= 1;

        // delete the Element if appropriate? - check against owner count
    }
}

saklib::String saklib::Element_Manager::make_name_unique(String const& name)
{
    // get all the names of Elements that currently exist
    auto all_names = all_element_names();
    // if name is not among those that already exist, stop
    //if (std::find(all_names.cbegin(), all_names.cend(), name) == all_names.cend())
    //{
    //    return;
    //}
    // make an adjusted name
    std::size_t count{0};
    String adjusted_name{name};
    while(std::find(all_names.cbegin(), all_names.cend(), adjusted_name) != all_names.cend())
    {
        ++count;
        adjusted_name = name + std::to_string(count);
    }

    return adjusted_name;
}


/*
// Adjust Element ownership tracking
void saklib::Element_Manager::add_owner(ElementID const& elementid, AttributeID owner)
{
    // if the elementid exists and it doesn't already have this owner
    auto found = m_map.find(elementid);
    if (found != m_map.end())
    {
        // if this owner does not already exist here
        auto found_owner = std::find(found->second.m_owners.cbegin(), found->second.m_owners.cend(), owner);
        if (found_owner != found->second.m_owners.cend())
        {
            // Add the new owner and sort the vector.
            found->second.m_owners.push_back(owner);
            std::sort(found->second.m_owners.begin(), found->second.m_owners.end());
        }
    }
}
void saklib::Element_Manager::remove_owner(ElementID const& elementid, AttributeID owner)
{
    // if the elementid exists
    auto found = m_map.find(elementid);
    if (found != m_map.end())
    {
        // Remove this owner if it exists
        found->second.m_owners.erase(std::find(found->second.m_owners.begin(), found->second.m_owners.end(), owner));

        // delete the Element if appropriate? - check against command ref count
    }
}
*/

