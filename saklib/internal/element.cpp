#include "element.h"

#include "attribute.h"

#include <iostream>

namespace saklib
{
    namespace internal
    {
        namespace
        {
            std::vector<Attribute> make_attributes(Element_Definition const& a_definition)
            {
                std::vector<Attribute> l_attributes{};
                l_attributes.reserve(a_definition.get_attribute_count());

                for (Size_Type index = 0, end = a_definition.get_attribute_count(); index != end; ++index)
                {
                    l_attributes.emplace_back(a_definition.cget_attribute_at(index));
                }

                return l_attributes;
            }
        }
    }
}

saklib::internal::Element_Definition::Element_Definition(String const& a_type):
    m_type(a_type),
    m_attribute_definitions()
{
}

saklib::internal::Element_Definition::Element_Definition(String const& a_type, storage_type const& a_attribute_definitions):
    m_type(a_type),
    m_attribute_definitions(a_attribute_definitions)
{
}

saklib::internal::Element_Definition::Element_Definition(String const& a_type, storage_type && a_attribute_definitions):
    m_type(a_type),
    m_attribute_definitions(std::move(a_attribute_definitions))
{
}

saklib::internal::String saklib::internal::Element_Definition::get_type() const
{
    return m_type;
}

void saklib::internal::Element_Definition::set_type(String const& a_type)
{
    m_type = a_type;
}

saklib::internal::Size_Type saklib::internal::Element_Definition::get_attribute_count() const
{
    return m_attribute_definitions.size();
}

saklib::internal::Attribute_Definition& saklib::internal::Element_Definition::get_attribute_at(Size_Type a_index)
{
    return m_attribute_definitions.at(a_index);
}

saklib::internal::Attribute_Definition const& saklib::internal::Element_Definition::cget_attribute_at(Size_Type a_index) const
{
    return m_attribute_definitions.at(a_index);
}


void saklib::internal::Element_Definition::push_back_attribute_definition(Attribute_Definition const& a_attribute_definition)
{
    m_attribute_definitions.push_back(a_attribute_definition);
}
void saklib::internal::Element_Definition::push_back_attribute_definition(Attribute_Definition && a_attribute_definition)
{
    m_attribute_definitions.push_back(std::move(a_attribute_definition));
}


void saklib::internal::Element_Definition::insert_attribute_definition(Size_Type a_index, Attribute_Definition const& a_attribute_definition)
{
    auto l_iterator = m_attribute_definitions.begin();
    std::advance(l_iterator, a_index);
    m_attribute_definitions.insert(l_iterator, a_attribute_definition);
}

void saklib::internal::Element_Definition::insert_attribute_definition(Size_Type a_index, Attribute_Definition && a_attribute_definition)
{
    auto l_iterator = m_attribute_definitions.begin();
    std::advance(l_iterator, a_index);
    m_attribute_definitions.insert(l_iterator, std::forward<Attribute_Definition>(a_attribute_definition));
}

void saklib::internal::Element_Definition::remove_attribute_definition(Size_Type a_index)
{
    auto l_iterator = m_attribute_definitions.begin();
    std::advance(l_iterator, a_index);
    m_attribute_definitions.erase(l_iterator);
}

void saklib::internal::Element_Definition::set_attribute_definitions(storage_type const& a_attribute_definitions)
{
    m_attribute_definitions = a_attribute_definitions;
}



saklib::internal::Element::Element(Element_Definition const& ar_definition):
    mr_definition(ar_definition),
    m_name(mr_definition.get_type()),
    m_attributes(make_attributes(mr_definition))
{
}

saklib::internal::Element::Element(Element_Definition const& ar_definition, String const& a_name):
    mr_definition(ar_definition),
    m_name(a_name),
    m_attributes(make_attributes(mr_definition))
{
}


saklib::internal::String saklib::internal::Element::get_type() const
{
    return mr_definition.get_type();
}

saklib::internal::String saklib::internal::Element::get_name() const
{
    return m_name;
}

void saklib::internal::Element::set_name(String const& a_name)
{
    m_name = a_name;
}

saklib::internal::Size_Type saklib::internal::Element::get_attribute_count() const
{
    return m_attributes.size();
}

saklib::internal::Attribute& saklib::internal::Element::get_attribute_at(Size_Type a_index)
{
    return m_attributes.at(a_index);
}

saklib::internal::Attribute const& saklib::internal::Element::cget_attribute_at(Size_Type a_index) const
{
    return m_attributes.at(a_index);
}



std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Element_Definition const& a_element_definition)
{
    a_ostream << "Element_Definition" << std::endl;
    a_ostream << "{" << std::endl;
    a_ostream << "  type=\"" << a_element_definition.get_type() << "\"" << std::endl;
    for (Size_Type index = 0, end = a_element_definition.get_attribute_count(); index != end; ++index)
    {
        a_ostream << "  " << a_element_definition.cget_attribute_at(index) << std::endl;
    }
    a_ostream << "}" << std::endl;
    return a_ostream;
}

std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Element const& a_element)
{
    a_ostream << "Element" << std::endl;
    a_ostream << "{" << std::endl;
    a_ostream << "  type=\"" << a_element.get_type() << "\"" << std::endl;
    a_ostream << "  name=\"" << a_element.get_name() << "\"" << std::endl;
    for (Size_Type index = 0, end = a_element.get_attribute_count(); index != end; ++index)
    {
        a_ostream << "  " << a_element.cget_attribute_at(index) << std::endl;
    }
    a_ostream << "}" << std::endl;
    return a_ostream;
}

