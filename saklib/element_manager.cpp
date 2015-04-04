#include "element_manager.h"
#include "attribute.h"
#include <cassert>
#include <algorithm>

// Special 6
//============================================================

Saklib::Element_Manager::Element_Manager() :
    m_map{},
    m_next_id{ 0 }
{
}
//Saklib::Element_Manager::~Element_Manager() = default;
// Interface
//============================================================
// Build a new Map_Entry containing a new Element from type and return the id number
Saklib::ElementID Saklib::Element_Manager::make_element(String const& type)
{
    assert(Element::definition_exists(type));
    ElementID newid{++m_next_id};
    m_map.emplace(newid, Element_Cache(type));
    return newid;
}

// Destory the Element associated with this id
void Saklib::Element_Manager::destroy_element(ElementID elementid)
{
    m_map.erase(elementid);
}


// Is this AttributeID valid for this?
bool Saklib::Element_Manager::is_valid(ElementID elementid) const
{
    return elementid.is_valid() && m_map.find(elementid) != m_map.end();
}

// Access the parent of this ID
bool Saklib::Element_Manager::has_parent(ElementID elementid) const
{
    auto found = m_map.find(elementid);
    return found != m_map.end() && found->second.m_parent.is_valid();
}
Saklib::AttributeID Saklib::Element_Manager::parent(ElementID elementid) const
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
        return found->second.m_parent;
    else
        return AttributeID();
}
void Saklib::Element_Manager::set_parent(ElementID elementid, AttributeID owner)
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
        found->second.m_parent = owner;
}

// Access the Element associated with this id
Saklib::Element& Saklib::Element_Manager::element(ElementID elementid)
{
    auto found = m_map.find(elementid);
    assert(found != m_map.end());
    return found->second.m_element;
}

Saklib::Element const& Saklib::Element_Manager::element(ElementID elementid) const
{
    auto found = m_map.find(elementid);
    assert(found != m_map.end());
    return found->second.m_element;
}


// Is this AttributeID valid for this?
bool Saklib::Element_Manager::is_valid(AttributeID attributeid) const
{
    auto found = m_map.find(attributeid.elementid());
    return found != m_map.end() && attributeid.index() < found->second.m_element.attribute_count();
}


// Make an AttributeID from the given data
Saklib::AttributeID Saklib::Element_Manager::attributeid(ElementID elementid, size_type attribute_index) const
{
    auto found = m_map.find(elementid);
    if (found != m_map.end()
        && attribute_index < found->second.m_element.attribute_count())
        return AttributeID(elementid, attribute_index);
    else
        return AttributeID();
}
Saklib::AttributeID Saklib::Element_Manager::attributeid(ElementID elementid, String const& attribute_name) const
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
    {
        auto const& attributes = found->second.m_element.attributes();
        size_type index{0};
        for (auto const& attribute : attributes)
        {
            if (attribute->name() == attribute_name)
            {
                return AttributeID(elementid, index);
            }
            ++index;
        }
    }

    return AttributeID();
}

// Access the Attribute associated with this id
Saklib::Attribute*const Saklib::Element_Manager::attribute(AttributeID attributeid)
{
    auto found = m_map.find(attributeid.elementid());
    if (found != m_map.end()
        && attributeid.index() < found->second.m_element.attribute_count())
        return found->second.m_element.attribute(attributeid.index());
    else
        return nullptr;
}

Saklib::Attribute*const Saklib::Element_Manager::attribute(ElementID elementid, size_type attribute_index)
{
    auto found = m_map.find(elementid);
    if (found != m_map.end()
        && attribute_index < found->second.m_element.attribute_count())
        return found->second.m_element.attribute(attribute_index);
    else
        return nullptr;
}

Saklib::Attribute*const Saklib::Element_Manager::attribute(ElementID elementid, String const& attribute_name)
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
        return found->second.m_element.attribute(attribute_name);
    else
        return nullptr;
}


Saklib::Attribute const*const Saklib::Element_Manager::attribute(AttributeID attributeid) const
{
    const_iterator found = m_map.find(attributeid.elementid());
    if (found != m_map.end()
        && attributeid.index() < found->second.m_element.attribute_count())
        return found->second.m_element.attribute(attributeid.index());
    else
        return nullptr;
}

Saklib::Attribute const*const Saklib::Element_Manager::attribute(ElementID elementid, size_type attribute_index) const
{
    auto found = m_map.find(elementid);
    if (found != m_map.end()
        && attribute_index < found->second.m_element.attribute_count())
        return found->second.m_element.attribute(attribute_index);
    else
        return nullptr;
}

Saklib::Attribute const*const Saklib::Element_Manager::attribute(ElementID elementid, String const& attribute_name) const
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
        return found->second.m_element.attribute(attribute_name);
    else
        return nullptr;
}


// Typed Access to Attributes

// Auxillary access
Saklib::Vector_ElementID Saklib::Element_Manager::all_elementids() const
{
    Vector_ElementID result{};
    for (auto const& value : m_map)
    {
        assert(value.first.is_valid());
        result.push_back(value.first);
        assert(result.back().is_valid());
    }
    return result;
}
// ElementIDs that have no parent
Saklib::Vector_ElementID Saklib::Element_Manager::root_elementids() const
{
    Vector_ElementID result{};
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

// Destory everything
void Saklib::Element_Manager::clear()
{
    m_map.clear();
    m_next_id = 0;
}

// Command Interface
//============================================================
// Bits that only Command objects will end up using

Saklib::size_type Saklib::Element_Manager::command_ref_count(ElementID elementid) const
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
void Saklib::Element_Manager::increment_command_ref_count(ElementID elementid)
{
    auto found = m_map.find(elementid);
    if (found != m_map.end())
    {
        found->second.m_command_ref_count += 1;
    }
}

void Saklib::Element_Manager::decrement_command_ref_count(ElementID elementid)
{

    auto found = m_map.find(elementid);
    if (found != m_map.end())
    {
        assert(found->second.m_command_ref_count != 0); // for now...
        found->second.m_command_ref_count -= 1;

        // delete the Element if appropriate? - check against owner count
    }
}
/*
// Adjust Element ownership tracking
void Saklib::Element_Manager::add_owner(ElementID elementid, AttributeID owner)
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
void Saklib::Element_Manager::remove_owner(ElementID elementid, AttributeID owner)
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

