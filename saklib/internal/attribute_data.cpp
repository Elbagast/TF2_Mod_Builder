#include "attribute_data.h"

#ifndef SAKLIB_INTERNAL_ALL_ATTRIBUTE_DATA_H
#include "all_attribute_data_.h"
#endif

#ifndef SAKLIB_INTERNAL_TYPE_STRING_H
#include "type_string.h"
#endif

#include "exceptions/bad_attribute_data_type.h"

#include <cassert>
#include <iostream>
#include <typeindex>

namespace saklib
{
    namespace internal
    {
        namespace
        {
            boost::any make_any_data_from_any_definition(boost::any const& a_any)
            {
                auto l_type = std::type_index(a_any.type());

                if (l_type == typeid(Attribute_Data_Definition_Bool))
                {
                    return boost::any(Attribute_Data_Bool(boost::any_cast<Attribute_Data_Definition_Bool const&>(a_any)));
                }
                else if (l_type == typeid(Attribute_Data_Definition_Int))
                {
                    return boost::any(Attribute_Data_Int(boost::any_cast<Attribute_Data_Definition_Int const&>(a_any)));
                }
                else
                {
                    return boost::any();
                }
            }

            template <typename T>
            std::string const& get_name_from_any(boost::any const& a_any)
            {
                return boost::any_cast<T const&>(a_any).cget_name();
            }

            template <typename T>
            void set_name_from_any(boost::any& a_any, std::string const& a_name)
            {
                return boost::any_cast<T &>(a_any).set_name(a_name);
            }

            template <typename T>
            std::string const& get_type_from_any(boost::any const& a_any)
            {
                return boost::any_cast<T const&>(a_any).cget_type();
            }

            template <typename T>
            std::string get_value_string_from_any(boost::any const& a_any)
            {
                return boost::any_cast<T const&>(a_any).cget_value_string();
            }

        }
    }
}



//---------------------------------------------------------------------------
// Attribute_Data_Definition
//---------------------------------------------------------------------------

// Special 6
//============================================================

// Construct based on the given type string. If the type string is invalid then the type
// will be bool.
saklib::internal::Attribute_Data_Definition::Attribute_Data_Definition(std::string const& a_name, std::string const& a_type):
    Attribute_Data_Definition(a_name, TS_Bool())
{
    // If the type is invalid set_type() won't change the type.
    // This means an invalid type will reult in a type of bool.
    set_type(a_type);
}

saklib::internal::Attribute_Data_Definition::Attribute_Data_Definition(std::string const& a_name, TS_Bool&&):
    m_any_definition(Attribute_Data_Definition_Bool(a_name)),
    mf_name_getter( get_name_from_any<Attribute_Data_Definition_Bool> ),
    mf_name_setter( set_name_from_any<Attribute_Data_Definition_Bool> ),
    mf_type_getter( get_type_from_any<Attribute_Data_Definition_Bool> ),
    mf_value_getter( get_value_string_from_any<Attribute_Data_Bool> )
{
}

saklib::internal::Attribute_Data_Definition::Attribute_Data_Definition(std::string const& a_name, TS_Bool&&, bool a_initial):
    m_any_definition(Attribute_Data_Definition_Bool(a_name, a_initial)),
    mf_name_getter( get_name_from_any<Attribute_Data_Definition_Bool> ),
    mf_name_setter( set_name_from_any<Attribute_Data_Definition_Bool> ),
    mf_type_getter( get_type_from_any<Attribute_Data_Definition_Bool> ),
    mf_value_getter( get_value_string_from_any<Attribute_Data_Bool> )
{
}

saklib::internal::Attribute_Data_Definition::Attribute_Data_Definition(std::string const& a_name, TS_Int&&):
    m_any_definition(Attribute_Data_Definition_Int(a_name)),
    mf_name_getter( get_name_from_any<Attribute_Data_Definition_Int> ),
    mf_name_setter( set_name_from_any<Attribute_Data_Definition_Int> ),
    mf_type_getter( get_type_from_any<Attribute_Data_Definition_Int> ),
    mf_value_getter( get_value_string_from_any<Attribute_Data_Int> )
{
}

saklib::internal::Attribute_Data_Definition::Attribute_Data_Definition(std::string const& a_name, TS_Int&&, int a_bound1, int a_bound2, int a_intiial):
    m_any_definition(Attribute_Data_Definition_Int(a_name, a_bound1, a_bound2, a_intiial)),
    mf_name_getter( get_name_from_any<Attribute_Data_Definition_Int> ),
    mf_name_setter( set_name_from_any<Attribute_Data_Definition_Int> ),
    mf_type_getter( get_type_from_any<Attribute_Data_Definition_Int> ),
    mf_value_getter( get_value_string_from_any<Attribute_Data_Int> )
{
}

// Interface
//============================================================
std::string const& saklib::internal::Attribute_Data_Definition::cget_name() const
{
    return mf_name_getter(m_any_definition);
}

void saklib::internal::Attribute_Data_Definition::set_name(std::string const& a_name)
{
    mf_name_setter(m_any_definition, a_name);
}

std::string const& saklib::internal::Attribute_Data_Definition::cget_type() const
{
    return mf_type_getter(m_any_definition);
}

void saklib::internal::Attribute_Data_Definition::set_type(std::string const& a_type)
{
    if (a_type == TS_Bool()())       set_to_bool();
    else if (a_type == TS_Int()())   set_to_int();
}

bool saklib::internal::Attribute_Data_Definition::is_bool() const
{
    return m_any_definition.type() == typeid(Attribute_Data_Definition_Bool);
}

bool saklib::internal::Attribute_Data_Definition::is_int() const
{
    return m_any_definition.type() == typeid(Attribute_Data_Definition_Int);
}

void saklib::internal::Attribute_Data_Definition::set_to_bool()
{
    if(!is_bool())
    {
        *this = Attribute_Data_Definition(mf_name_getter(m_any_definition), TS_Bool());
    }
}

void saklib::internal::Attribute_Data_Definition::set_to_int()
{
    if(!is_int())
    {
        *this = Attribute_Data_Definition(mf_name_getter(m_any_definition), TS_Int());
    }
}

saklib::internal::Attribute_Data_Definition_Bool& saklib::internal::Attribute_Data_Definition::get_bool()
{
    if(is_bool())
    {
        return boost::any_cast<Attribute_Data_Definition_Bool&>(m_any_definition);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Bool()(), cget_type());
    }
}

saklib::internal::Attribute_Data_Definition_Int& saklib::internal::Attribute_Data_Definition::get_int()
{
    if(is_int())
    {
        return boost::any_cast<Attribute_Data_Definition_Int&>(m_any_definition);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Int()(), cget_type());
    }
}

saklib::internal::Attribute_Data_Definition_Bool const& saklib::internal::Attribute_Data_Definition::cget_bool() const
{
    if(is_bool())
    {
        return boost::any_cast<Attribute_Data_Definition_Bool const&>(m_any_definition);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Bool()(), cget_type());
    }
}

saklib::internal::Attribute_Data_Definition_Int const& saklib::internal::Attribute_Data_Definition::cget_int() const
{
    if(is_int())
    {
        return boost::any_cast<Attribute_Data_Definition_Int const&>(m_any_definition);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Int()(), cget_type());
    }
}

// Factory Functions
//============================================================

saklib::internal::Attribute_Data_Definition saklib::internal::make_attribute_definition_bool__default(std::string const& a_name)
{
    return Attribute_Data_Definition(a_name, TS_Bool());
}

saklib::internal::Attribute_Data_Definition saklib::internal::make_attribute_definition_bool(std::string const& a_name, bool a_initial)
{
    return Attribute_Data_Definition(a_name, TS_Bool(), a_initial);
}

saklib::internal::Attribute_Data_Definition saklib::internal::make_attribute_definition_int__default(std::string const& a_name)
{
    return Attribute_Data_Definition(a_name, TS_Int());
}

saklib::internal::Attribute_Data_Definition saklib::internal::make_attribute_definition_int(std::string const& a_name, int a_bound1, int a_bound2, int a_intiial)
{
    return Attribute_Data_Definition(a_name, TS_Int(), a_bound1, a_bound2, a_intiial);
}

// Non-Member Operators
//============================================================
std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Attribute_Data_Definition const& a_definitition)
{
    a_ostream << "Attribute_Definition {";
    a_ostream << " name=\"" << a_definitition.cget_name();
    a_ostream << "\" type=\"" << a_definitition.cget_type();
    a_ostream << "\" ";
    if (a_definitition.is_bool()) a_ostream << a_definitition.cget_bool();
    else if (a_definitition.is_int()) a_ostream << a_definitition.cget_int();

    a_ostream << " } ";
    return a_ostream;
}


//---------------------------------------------------------------------------
// Attribute_Data
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Attribute_Data::Attribute_Data(Attribute_Data_Definition const& a_definition):
    mr_definition(a_definition),
    m_any_attribute(make_any_data_from_any_definition(mr_definition.m_any_definition)),
    mf_value_string_getter(mr_definition.mf_value_getter)
{
}

// Interface
//============================================================
std::string const& saklib::internal::Attribute_Data::cget_name() const
{
    return mr_definition.cget_name();
}

std::string const& saklib::internal::Attribute_Data::cget_type() const
{
    // no need to repeat everything here
    return mr_definition.cget_type();
}

std::string saklib::internal::Attribute_Data::cget_value_string() const
{
    return mf_value_string_getter(m_any_attribute);
}

bool saklib::internal::Attribute_Data::is_bool() const
{
    return m_any_attribute.type() == typeid(Attribute_Data_Bool);
}

bool saklib::internal::Attribute_Data::is_int() const
{
    return m_any_attribute.type() == typeid(Attribute_Data_Int);
}

saklib::internal::Attribute_Data_Bool& saklib::internal::Attribute_Data::get_bool()
{
    if(is_bool())
    {
        return boost::any_cast<Attribute_Data_Bool&>(m_any_attribute);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Bool()(), cget_type());
    }
}

saklib::internal::Attribute_Data_Int& saklib::internal::Attribute_Data::get_int()
{
    if(is_int())
    {
        return boost::any_cast<Attribute_Data_Int&>(m_any_attribute);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Int()(), cget_type());
    }
}

saklib::internal::Attribute_Data_Bool const& saklib::internal::Attribute_Data::cget_bool() const
{
    if(is_bool())
    {
        return boost::any_cast<Attribute_Data_Bool const&>(m_any_attribute);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Bool()(), cget_type());
    }
}

saklib::internal::Attribute_Data_Int const& saklib::internal::Attribute_Data::cget_int() const
{
    if(is_int())
    {
        return boost::any_cast<Attribute_Data_Int const&>(m_any_attribute);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Int()(), cget_type());
    }
}

// Non-Member Operators
//============================================================
std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Attribute_Data const& a_attribute)
{
    a_ostream << "Attribute {";
    a_ostream << " name=\"" << a_attribute.cget_name();
    a_ostream << "\" type=\"" << a_attribute.cget_type();
    a_ostream << "\" value=\"" << a_attribute.cget_value_string();
    a_ostream << "\" } ";
    return a_ostream;
}
