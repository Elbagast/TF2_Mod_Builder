#include "element.h"
#include "all_attributes.h"
#include "element_definition.h"
#include <algorithm>


// Special 6
//============================================================
saklib::Element::Element(Element_Definition const& definition, String const& name) :
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

saklib::Element::~Element() = default;


saklib::Element::Element(Element && other) :
    m_type(std::move(other.m_type)),
    m_name(std::move(other.m_name)),
    m_can_be_root(std::move(other.m_can_be_root)),
    m_attributes(std::move(other.m_attributes))
{
}
saklib::Element& saklib::Element::operator=(Element && other)
{
    m_type = std::move(other.m_type);
    m_name = std::move(other.m_name);
    m_can_be_root = std::move(other.m_can_be_root);
    m_attributes = std::move(other.m_attributes);

    return *this;
}

// Basic Access
//============================================================
saklib::String const& saklib::Element::type() const
{
    return m_type;
}

bool saklib::Element::can_be_root() const
{
    return m_can_be_root;
}

saklib::String const& saklib::Element::name() const
{
    return m_name;
}
void saklib::Element::set_name(String const& name)
{
    m_name = name;
}

// Attributes Access
//============================================================
saklib::size_type saklib::Element::attribute_count() const
{
    return m_attributes.size();
}

saklib::size_type saklib::Element::attribute_count_type(Type_Enum type) const
{
    size_type count{0};
    for (auto const& attribute : m_attributes)
    {
        if (attribute->type_enum() == type)
        {
            ++count;
        }
    }
    return count;
}

bool saklib::Element::has_attribute(String const& name) const
{
    // probably want an Attribute typematching functor here
    return cfind_attribute(name) != m_attributes.cend();
}

bool saklib::Element::has_attribute(size_type index) const
{
    return index < attribute_count();
}

saklib::Attribute* saklib::Element::attribute(String const& name)
{
    auto found = find_attribute(name);
    if (found != m_attributes.end())
    {
        return found->get();
    }
    else
        return nullptr;
}

saklib::Attribute const* saklib::Element::cattribute(String const& name) const
{
    auto found = cfind_attribute(name);
    if (found != m_attributes.cend())
    {
        return found->get();
    }
    else
        return nullptr;
}

saklib::Attribute* saklib::Element::attribute(size_type index)
{
    if (index < m_attributes.size())
    {
        return m_attributes.at(index).get();
    }
    else
        return nullptr;
}

saklib::Attribute const* saklib::Element::cattribute(size_type index) const
{
    if (index < m_attributes.size())
    {
        return m_attributes.at(index).get();
    }
    else
        return nullptr;
}

std::vector<saklib::String> saklib::Element::attribute_names() const
{
    std::vector<String> result{};
    for (auto const& attribute : m_attributes)
    {
        result.push_back(attribute->name());
    }
    return result;
}

saklib::Element::iterator saklib::Element::find_attribute(String const& name)
{
    return std::find_if(m_attributes.begin(), m_attributes.end(), [&name](std::unique_ptr<Attribute> const& a){ assert(a != nullptr); return a->name() == name; });
}

saklib::Element::const_iterator saklib::Element::cfind_attribute(String const& name) const
{
    return std::find_if(m_attributes.cbegin(), m_attributes.cend(), [&name](std::unique_ptr<Attribute> const& a){ assert(a != nullptr); return a->name() == name; });
}
