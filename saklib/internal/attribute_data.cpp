#include "attribute_data.h"

#ifndef SAKLIB_INTERNAL_ALL_CONSTRAINT_H
#include "all_constraint.h"
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
    m_name(a_name),
    m_any_constraint(Constraint_Bool())
{
    // If the type is invalid set_type() won't change the type.
    // This means an invalid type will reult in a type of bool.
    set_type(a_type);
}

saklib::internal::Attribute_Data_Definition::Attribute_Data_Definition(std::string const& a_name, TS_Bool&&):
    m_name(a_name),
    m_any_constraint(Constraint_Bool())
{
}

saklib::internal::Attribute_Data_Definition::Attribute_Data_Definition(std::string const& a_name, TS_Bool&&, bool a_initial):
    m_name(a_name),
    m_any_constraint(Constraint_Bool(a_initial))
{
}

saklib::internal::Attribute_Data_Definition::Attribute_Data_Definition(std::string const& a_name, TS_Int&&):
    m_name(a_name),
    m_any_constraint(Constraint_Int())
{
}

saklib::internal::Attribute_Data_Definition::Attribute_Data_Definition(std::string const& a_name, TS_Int&&, int a_bound1, int a_bound2, int a_intiial):
    m_name(a_name),
    m_any_constraint(Constraint_Int(a_bound1, a_bound2, a_intiial))
{
}

// Interface
//============================================================
std::string const& saklib::internal::Attribute_Data_Definition::cget_name() const
{
    return m_name;
}

void saklib::internal::Attribute_Data_Definition::set_name(std::string const& a_name)
{
    m_name = a_name;
}

std::string const& saklib::internal::Attribute_Data_Definition::cget_type() const
{
    if (is_bool())      return TS_Bool()();
    else if (is_int())  return TS_Int()();
    else
    {
        // Shouldn't get here...
        assert(false);
        static std::string const type_fail{};
        return type_fail;
    }
}

void saklib::internal::Attribute_Data_Definition::set_type(std::string const& a_type)
{
    if (a_type == TS_Bool()())       set_to_bool();
    else if (a_type == TS_Int()())   set_to_int();
}

bool saklib::internal::Attribute_Data_Definition::is_bool() const
{
    return m_any_constraint.type() == typeid(Constraint_Bool);
}

bool saklib::internal::Attribute_Data_Definition::is_int() const
{
    return m_any_constraint.type() == typeid(Constraint_Int);
}

void saklib::internal::Attribute_Data_Definition::set_to_bool()
{
    if(!is_bool())
    {
        m_any_constraint = boost::any(Constraint_Bool());
    }
}

void saklib::internal::Attribute_Data_Definition::set_to_int()
{
    if(!is_int())
    {
        m_any_constraint = boost::any(Constraint_Int());
    }
}

saklib::internal::Constraint_Bool& saklib::internal::Attribute_Data_Definition::get_constraint_bool()
{
    if(is_bool())
    {
        return boost::any_cast<Constraint_Bool&>(m_any_constraint);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Bool()(), cget_type());
    }
}

saklib::internal::Constraint_Int& saklib::internal::Attribute_Data_Definition::get_constraint_int()
{
    if(is_int())
    {
        return boost::any_cast<Constraint_Int&>(m_any_constraint);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Int()(), cget_type());
    }
}

saklib::internal::Constraint_Bool const& saklib::internal::Attribute_Data_Definition::cget_constraint_bool() const
{
    if(is_bool())
    {
        return boost::any_cast<Constraint_Bool const&>(m_any_constraint);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Bool()(), cget_type());
    }
}

saklib::internal::Constraint_Int const& saklib::internal::Attribute_Data_Definition::cget_constraint_int() const
{
    if(is_int())
    {
        return boost::any_cast<Constraint_Int const&>(m_any_constraint);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Int()(), cget_type());
    }
}

boost::any const& saklib::internal::Attribute_Data_Definition::cget_any_constraint() const
{
    return m_any_constraint;
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
    if (a_definitition.is_bool()) a_ostream << a_definitition.cget_constraint_bool();
    else if (a_definitition.is_int()) a_ostream << a_definitition.cget_constraint_int();

    a_ostream << " } ";
    return a_ostream;
}


//---------------------------------------------------------------------------
// Attribute_Data
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Attribute_Data::Attribute_Data(Attribute_Data_Definition const& a_definition):
    mr_definition{a_definition},
    m_any_constrained{make_any_constrained_from_any_constraint(mr_definition.cget_any_constraint())}
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

bool saklib::internal::Attribute_Data::is_bool() const
{
    return m_any_constrained.type() == typeid(Constrained_Bool);
}

bool saklib::internal::Attribute_Data::is_int() const
{
    return m_any_constrained.type() == typeid(Constrained_Int);
}

saklib::internal::Constrained_Bool& saklib::internal::Attribute_Data::get_value_bool()
{
    if(is_bool())
    {
        return boost::any_cast<Constrained_Bool&>(m_any_constrained);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Bool()(), cget_type());
    }
}

saklib::internal::Constrained_Int& saklib::internal::Attribute_Data::get_value_int()
{
    if(is_int())
    {
        return boost::any_cast<Constrained_Int&>(m_any_constrained);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Int()(), cget_type());
    }
}

saklib::internal::Constrained_Bool const& saklib::internal::Attribute_Data::cget_value_bool() const
{
    if(is_bool())
    {
        return boost::any_cast<Constrained_Bool const&>(m_any_constrained);
    }
    else
    {
        throw Bad_Attribute_Data_Type(TS_Bool()(), cget_type());
    }
}

saklib::internal::Constrained_Int const& saklib::internal::Attribute_Data::cget_value_int() const
{
    if(is_int())
    {
        return boost::any_cast<Constrained_Int const&>(m_any_constrained);
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
    a_ostream << "\" ";
    if (a_attribute.is_bool())      a_ostream << a_attribute.cget_value_bool();
    else if (a_attribute.is_int())  a_ostream << a_attribute.cget_value_int();

    a_ostream << " } ";
    return a_ostream;
}
