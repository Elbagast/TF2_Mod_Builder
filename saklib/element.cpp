#include "element.h"
#include "all_attributes.h"
#include "element_definition.h"
#include <algorithm>


// Special 6
//============================================================
Saklib::Element::Element(Element_Definition const& definition, String const& name) :
    m_type(definition.type()),
    m_name(name.empty() ? definition.type() : name),
    m_can_be_root(definition.can_be_root()),
    m_attributes()
{
    for (auto const& attribute_definition : definition.attribute_definitions())
    {
        m_attributes.push_back(make_Attribute(attribute_definition));
    }
}

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

Saklib::Attribute* Saklib::Element::attribute(String const& name)
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

Saklib::Attribute const* Saklib::Element::cattribute(String const& name) const
{
    auto found = std::find_if(m_attributes.cbegin(), m_attributes.cend(), [&name](Uptr<Attribute> const& a){ assert(a != nullptr); return a->name() == name; });
    if (found != m_attributes.cend())
    {
        // break if we got here and found an invalid attribute
        return found->get();
    }
    else
        return nullptr;
}

Saklib::Attribute* Saklib::Element::attribute(size_type index)
{
    if (index < m_attributes.size())
    {
        return m_attributes.at(index).get();
    }
    else
        return nullptr;
}

Saklib::Attribute const* Saklib::Element::cattribute(size_type index) const
{
    if (index < m_attributes.size())
    {
        return m_attributes.at(index).get();
    }
    else
        return nullptr;
}

Saklib::Vector_String Saklib::Element::attribute_names() const
{
    Vector_String result{};
    for (auto const& attribute : m_attributes)
        result.push_back(attribute->name());
    return result;
}
