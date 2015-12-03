#include "element_data.h"

#include "attribute_data.h"

#include <iostream>

namespace saklib
{
    namespace internal
    {
        namespace
        {
            std::vector<Attribute_Data> make_attributes(Element_Data_Definition const& a_definition)
            {
                std::vector<Attribute_Data> l_attributes{};
                l_attributes.reserve(a_definition.get_attribute_count());

                for (std::size_t index = 0, end = a_definition.get_attribute_count(); index != end; ++index)
                {
                    l_attributes.emplace_back(a_definition.cget_attribute_at(index));
                }

                return l_attributes;
            }
        }
    }
}

//---------------------------------------------------------------------------
// Element_Data_Definition
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Element_Data_Definition::Element_Data_Definition(std::string const& a_type):
    m_type(a_type),
    m_attribute_definitions()
{
}

saklib::internal::Element_Data_Definition::Element_Data_Definition(std::string const& a_type, storage_type const& a_attribute_definitions):
    m_type(a_type),
    m_attribute_definitions(a_attribute_definitions)
{
}

saklib::internal::Element_Data_Definition::Element_Data_Definition(std::string const& a_type, storage_type && a_attribute_definitions):
    m_type(a_type),
    m_attribute_definitions(std::move(a_attribute_definitions))
{
}

// Interface
//============================================================
std::string const& saklib::internal::Element_Data_Definition::cget_type() const
{
    return m_type;
}

void saklib::internal::Element_Data_Definition::set_type(std::string const& a_type)
{
    m_type = a_type;
}

std::size_t saklib::internal::Element_Data_Definition::get_attribute_count() const
{
    return m_attribute_definitions.size();
}

saklib::internal::Attribute_Data_Definition& saklib::internal::Element_Data_Definition::get_attribute_at(std::size_t a_index)
{
    return m_attribute_definitions.at(a_index);
}

saklib::internal::Attribute_Data_Definition const& saklib::internal::Element_Data_Definition::cget_attribute_at(std::size_t a_index) const
{
    return m_attribute_definitions.at(a_index);
}

saklib::internal::Element_Data_Definition::storage_type const& saklib::internal::Element_Data_Definition::cget_attributes() const
{
    return m_attribute_definitions;
}

void saklib::internal::Element_Data_Definition::push_back_attribute_definition(Attribute_Data_Definition const& a_attribute_definition)
{
    m_attribute_definitions.push_back(a_attribute_definition);
}
void saklib::internal::Element_Data_Definition::push_back_attribute_definition(Attribute_Data_Definition && a_attribute_definition)
{
    m_attribute_definitions.push_back(std::move(a_attribute_definition));
}


void saklib::internal::Element_Data_Definition::insert_attribute_definition(std::size_t a_index, Attribute_Data_Definition const& a_attribute_definition)
{
    auto l_iterator = m_attribute_definitions.begin();
    std::advance(l_iterator, a_index);
    m_attribute_definitions.insert(l_iterator, a_attribute_definition);
}

void saklib::internal::Element_Data_Definition::insert_attribute_definition(std::size_t a_index, Attribute_Data_Definition && a_attribute_definition)
{
    auto l_iterator = m_attribute_definitions.begin();
    std::advance(l_iterator, a_index);
    m_attribute_definitions.insert(l_iterator, std::forward<Attribute_Data_Definition>(a_attribute_definition));
}

void saklib::internal::Element_Data_Definition::remove_attribute_definition(std::size_t a_index)
{
    auto l_iterator = m_attribute_definitions.begin();
    std::advance(l_iterator, a_index);
    m_attribute_definitions.erase(l_iterator);
}

void saklib::internal::Element_Data_Definition::set_attribute_definitions(storage_type const& a_attribute_definitions)
{
    m_attribute_definitions = a_attribute_definitions;
}

// Non-Member Operators
//============================================================
std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Element_Data_Definition const& a_element_definition)
{
    a_ostream << "Element_Definition" << std::endl;
    a_ostream << "{" << std::endl;
    a_ostream << "  type=\"" << a_element_definition.cget_type() << "\"" << std::endl;
    for (auto const& attribute_definition : a_element_definition.cget_attributes())
    {
        a_ostream << "  " << attribute_definition << std::endl;
    }
    a_ostream << "}" << std::endl;
    return a_ostream;
}

//---------------------------------------------------------------------------
// Element_Data
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Element_Data::Element_Data(Element_Data_Definition const& ar_definition):
    mr_definition(ar_definition),
    m_name(mr_definition.cget_type()),
    m_attributes(make_attributes(mr_definition))
{
}

saklib::internal::Element_Data::Element_Data(Element_Data_Definition const& ar_definition, std::string const& a_name):
    mr_definition(ar_definition),
    m_name(a_name),
    m_attributes(make_attributes(mr_definition))
{
}

// Interface
//============================================================
std::string const& saklib::internal::Element_Data::cget_type() const
{
    return mr_definition.cget_type();
}

std::string const& saklib::internal::Element_Data::cget_name() const
{
    return m_name;
}

void saklib::internal::Element_Data::set_name(std::string const& a_name)
{
    m_name = a_name;
}

std::size_t saklib::internal::Element_Data::cget_attribute_count() const
{
    return m_attributes.size();
}

saklib::internal::Attribute_Data& saklib::internal::Element_Data::get_attribute_at(std::size_t a_index)
{
    return m_attributes.at(a_index);
}

saklib::internal::Attribute_Data const& saklib::internal::Element_Data::cget_attribute_at(std::size_t a_index) const
{
    return m_attributes.at(a_index);
}

saklib::internal::Element_Data::storage_type const& saklib::internal::Element_Data::cget_attributes() const
{
    return m_attributes;
}

// Non-Member Operators
//============================================================
std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Element_Data const& a_element)
{
    a_ostream << "Element" << std::endl;
    a_ostream << "{" << std::endl;
    a_ostream << "  type=\"" << a_element.cget_type() << "\"" << std::endl;
    a_ostream << "  name=\"" << a_element.cget_name() << "\"" << std::endl;
    for (auto const& attribute : a_element.cget_attributes())
    {
        a_ostream << "  " << attribute << std::endl;
    }
    a_ostream << "}" << std::endl;
    return a_ostream;
}

