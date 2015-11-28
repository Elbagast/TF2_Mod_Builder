#include "attribute.h"

#ifndef SAKLIB_INTERNAL_ALL_CONSTRAINT_H
#include "all_constraint.h"
#endif

#ifndef SAKLIB_INTERNAL_TYPE_STRING_H
#include "type_string.h"
#endif

#include "exceptions/bad_attribute_type.h"

#include <cassert>
#include <iostream>
#include <typeindex>

namespace saklib
{
    namespace internal
    {
        namespace
        {
            boost::any make_any_constrained_from_any_constraint(boost::any const& a_any)
            {
                auto l_type = std::type_index(a_any.type());

                if (l_type == typeid(Constraint_Bool))
                {
                    return boost::any(Constrained_Bool(boost::any_cast<Constraint_Bool const&>(a_any)));
                }
                else if (l_type == typeid(Constraint_Int))
                {
                    return boost::any(Constrained_Int(boost::any_cast<Constraint_Int const&>(a_any)));
                }
                else
                {
                    return boost::any();
                }
            }

            /*
            template <typename T>
            struct Get_String
            {
                static char const* c_string()       { return ""; }
                static wchar_t const* wc_string()   { return L""; }
            };

            template <typename T>
            struct Get_std_string
            {
                std::string operator()() const { return std::string(Get_String<T>::c_string()); }
            };

            template <typename T>
            struct Get_std_wstring
            {
                std::wstring operator()() const { return std::string(Get_String<T>::wc_string()); }
            };

            template<>
            struct Get_String<Constraint_Bool>
            {
                static char const* c_string()       { return "Bool"; }
                static wchar_t const* wc_string()   { return L"Bool"; }
            };
            template<>
            struct Get_String<Constraint_Int>
            {
                static char const* c_string()       { return "Int"; }
                static wchar_t const* wc_string()   { return L"Int"; }
            };
            */
        }
    }
}





saklib::internal::Attribute_Definition::Attribute_Definition(String const& a_name, String const& a_type):
    m_name(a_name),
    m_any_constraint()
{
    set_type(a_type);
}

saklib::internal::Attribute_Definition::Attribute_Definition(String const& a_name, TS_Bool&&):
    m_name(a_name),
    m_any_constraint(Constraint_Bool())
{
}

saklib::internal::Attribute_Definition::Attribute_Definition(String const& a_name, TS_Bool&&, bool a_initial):
    m_name(a_name),
    m_any_constraint(Constraint_Bool(a_initial))
{
}

saklib::internal::Attribute_Definition::Attribute_Definition(String const& a_name, TS_Int&&):
    m_name(a_name),
    m_any_constraint(Constraint_Int())
{
}

saklib::internal::Attribute_Definition::Attribute_Definition(String const& a_name, TS_Int&&, int a_bound1, int a_bound2, int a_intiial):
    m_name(a_name),
    m_any_constraint(Constraint_Int(a_bound1, a_bound2, a_intiial))
{
}


saklib::internal::String saklib::internal::Attribute_Definition::get_name() const
{
    return m_name;
}

void saklib::internal::Attribute_Definition::set_name(String const& a_name)
{
    m_name = a_name;
}

saklib::internal::String saklib::internal::Attribute_Definition::get_type() const
{
    if (is_bool())      return TS_Bool()();
    else if (is_int())  return TS_Int()();
    else
    {
        assert(0);
        return String();
    }
}

void saklib::internal::Attribute_Definition::set_type(String const& a_type)
{
    if (a_type == TS_Bool()())       set_to_bool();
    else if (a_type == TS_Int()())   set_to_int();
}

bool saklib::internal::Attribute_Definition::is_bool() const
{
    return m_any_constraint.type() == typeid(Constraint_Bool);
}

bool saklib::internal::Attribute_Definition::is_int() const
{
    return m_any_constraint.type() == typeid(Constraint_Int);
}

void saklib::internal::Attribute_Definition::set_to_bool()
{
    if(!is_bool())
    {
        m_any_constraint = boost::any(Constraint_Bool());
    }
}

void saklib::internal::Attribute_Definition::set_to_int()
{
    if(!is_int())
    {
        m_any_constraint = boost::any(Constraint_Int());
    }
}

saklib::internal::Constraint_Bool& saklib::internal::Attribute_Definition::get_constraint_bool()
{
    if(is_bool())
    {
        return boost::any_cast<Constraint_Bool&>(m_any_constraint);
    }
    else
    {
        throw Bad_Attribute_Type(TS_Bool()(), get_type());
    }
}

saklib::internal::Constraint_Int& saklib::internal::Attribute_Definition::get_constraint_int()
{
    if(is_int())
    {
        return boost::any_cast<Constraint_Int&>(m_any_constraint);
    }
    else
    {
        throw Bad_Attribute_Type(TS_Int()(), get_type());
    }
}

saklib::internal::Constraint_Bool const& saklib::internal::Attribute_Definition::cget_constraint_bool() const
{
    if(is_bool())
    {
        return boost::any_cast<Constraint_Bool const&>(m_any_constraint);
    }
    else
    {
        throw Bad_Attribute_Type(TS_Bool()(), get_type());
    }
}

saklib::internal::Constraint_Int const& saklib::internal::Attribute_Definition::cget_constraint_int() const
{
    if(is_int())
    {
        return boost::any_cast<Constraint_Int const&>(m_any_constraint);
    }
    else
    {
        throw Bad_Attribute_Type(TS_Int()(), get_type());
    }
}

boost::any const& saklib::internal::Attribute_Definition::cget_any_constraint() const
{
    return m_any_constraint;
}

saklib::internal::Attribute_Definition saklib::internal::make_attribute_definition_bool__default(String const& a_name)
{
    return Attribute_Definition(a_name, TS_Bool());
}

saklib::internal::Attribute_Definition saklib::internal::make_attribute_definition_bool(String const& a_name, bool a_initial)
{
    return Attribute_Definition(a_name, TS_Bool(), a_initial);
}

saklib::internal::Attribute_Definition saklib::internal::make_attribute_definition_int__default(String const& a_name)
{
    return Attribute_Definition(a_name, TS_Int());
}

saklib::internal::Attribute_Definition saklib::internal::make_attribute_definition_int(String const& a_name, int a_bound1, int a_bound2, int a_intiial)
{
    return Attribute_Definition(a_name, TS_Int(), a_bound1, a_bound2, a_intiial);
}







saklib::internal::Attribute::Attribute(Attribute_Definition const& a_definition):
    mr_definition{a_definition},
    m_any_constrained{make_any_constrained_from_any_constraint(mr_definition.cget_any_constraint())}
{
}

saklib::internal::String saklib::internal::Attribute::get_name() const
{
    return mr_definition.get_name();
}

saklib::internal::String saklib::internal::Attribute::get_type() const
{
    // no need to repeat everything here
    return mr_definition.get_type();
}

bool saklib::internal::Attribute::is_bool() const
{
    return m_any_constrained.type() == typeid(Constrained_Bool);
}

bool saklib::internal::Attribute::is_int() const
{
    return m_any_constrained.type() == typeid(Constrained_Int);
}

saklib::internal::Constrained_Bool& saklib::internal::Attribute::get_value_bool()
{
    if(is_bool())
    {
        return boost::any_cast<Constrained_Bool&>(m_any_constrained);
    }
    else
    {
        throw Bad_Attribute_Type(TS_Bool()(), get_type());
    }
}

saklib::internal::Constrained_Int& saklib::internal::Attribute::get_value_int()
{
    if(is_int())
    {
        return boost::any_cast<Constrained_Int&>(m_any_constrained);
    }
    else
    {
        throw Bad_Attribute_Type(TS_Int()(), get_type());
    }
}

saklib::internal::Constrained_Bool const& saklib::internal::Attribute::cget_value_bool() const
{
    if(is_bool())
    {
        return boost::any_cast<Constrained_Bool const&>(m_any_constrained);
    }
    else
    {
        throw Bad_Attribute_Type(TS_Bool()(), get_type());
    }
}

saklib::internal::Constrained_Int const& saklib::internal::Attribute::cget_value_int() const
{
    if(is_int())
    {
        return boost::any_cast<Constrained_Int const&>(m_any_constrained);
    }
    else
    {
        throw Bad_Attribute_Type(TS_Int()(), get_type());
    }
}



std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Attribute_Definition const& a_definitition)
{
    a_ostream << "Attribute_Definition {";
    a_ostream << " name=\"" << a_definitition.get_name();
    a_ostream << "\" type=\"" << a_definitition.get_type();
    a_ostream << "\" ";
    if (a_definitition.is_bool()) a_ostream << a_definitition.cget_constraint_bool();
    else if (a_definitition.is_int()) a_ostream << a_definitition.cget_constraint_int();

    a_ostream << " } ";
    return a_ostream;
}

std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Attribute const& a_attribute)
{
    a_ostream << "Attribute {";
    a_ostream << " name=\"" << a_attribute.get_name();
    a_ostream << "\" type=\"" << a_attribute.get_type();
    a_ostream << "\" ";
    if (a_attribute.is_bool())      a_ostream << a_attribute.cget_value_bool();
    else if (a_attribute.is_int())  a_ostream << a_attribute.cget_value_int();

    a_ostream << " } ";
    return a_ostream;
}
