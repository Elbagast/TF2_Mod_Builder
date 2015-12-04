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

                // How the hell can we expand this...
                // Might need a custom holder rather than boost::any

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
    Attribute_Data_Definition(a_name, Type_Bool())
{
    // If the type is invalid set_type() won't change the type.
    // This means an invalid type will reult in a type of bool.
    set_type(a_type);
}

template <typename T>
saklib::internal::Attribute_Data_Definition::Attribute_Data_Definition(std::string const& a_name, Type_Boolean_Type<T>&& ):
    m_any_definition(Attribute_Data_Definition_Boolean_Type<T>(a_name)),
    mf_name_getter( get_name_from_any<Attribute_Data_Definition_Boolean_Type<T>> ),
    mf_name_setter( set_name_from_any<Attribute_Data_Definition_Boolean_Type<T>> ),
    mf_type_getter( get_type_from_any<Attribute_Data_Definition_Boolean_Type<T>> ),
    mf_value_getter( get_value_string_from_any<Attribute_Data_Boolean_Type<T>> )
{
}

template <typename T>
saklib::internal::Attribute_Data_Definition::Attribute_Data_Definition(std::string const& a_name, Type_Boolean_Type<T>&& ,
                          typename Type_Boolean_Type<T>::bool_type a_initial):
    m_any_definition(Attribute_Data_Definition_Bool(a_name, a_initial)),
    mf_name_getter( get_name_from_any<Attribute_Data_Definition_Bool> ),
    mf_name_setter( set_name_from_any<Attribute_Data_Definition_Bool> ),
    mf_type_getter( get_type_from_any<Attribute_Data_Definition_Bool> ),
    mf_value_getter( get_value_string_from_any<Attribute_Data_Bool> )
{
}


template <typename T>
saklib::internal::Attribute_Data_Definition::Attribute_Data_Definition(std::string const& a_name, Type_Integral_Type<T>&& ):
    m_any_definition(Attribute_Data_Definition_Integral_Type<T>(a_name)),
    mf_name_getter( get_name_from_any<Attribute_Data_Definition_Integral_Type<T>> ),
    mf_name_setter( set_name_from_any<Attribute_Data_Definition_Integral_Type<T>> ),
    mf_type_getter( get_type_from_any<Attribute_Data_Definition_Integral_Type<T>> ),
    mf_value_getter( get_value_string_from_any<Attribute_Data_Integral_Type<T>> )
{
}

template <typename T>
saklib::internal::Attribute_Data_Definition::Attribute_Data_Definition(std::string const& a_name, Type_Integral_Type<T>&& ,
                          typename Type_Integral_Type<T>::int_type a_bound1,
                          typename Type_Integral_Type<T>::int_type a_bound2,
                          typename Type_Integral_Type<T>::int_type a_intiial):
    m_any_definition(Attribute_Data_Definition_Integral_Type<T>(a_name, a_bound1, a_bound2, a_intiial)),
    mf_name_getter( get_name_from_any<Attribute_Data_Definition_Integral_Type<T>> ),
    mf_name_setter( set_name_from_any<Attribute_Data_Definition_Integral_Type<T>> ),
    mf_type_getter( get_type_from_any<Attribute_Data_Definition_Integral_Type<T>> ),
    mf_value_getter( get_value_string_from_any<Attribute_Data_Integral_Type<T>> )
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
    return is_bool_type<bool>();
}

bool saklib::internal::Attribute_Data_Definition::is_int() const
{
    return is_int_type<int>();
}

void saklib::internal::Attribute_Data_Definition::set_to_bool()
{
    set_to_bool_type<bool>();
}

void saklib::internal::Attribute_Data_Definition::set_to_int()
{
    set_to_int_type<int>();
}

saklib::internal::Attribute_Data_Definition_Bool& saklib::internal::Attribute_Data_Definition::get_bool()
{
    return get_bool_type<bool>();
}

saklib::internal::Attribute_Data_Definition_Int& saklib::internal::Attribute_Data_Definition::get_int()
{
    return get_int_type<int>();
}

saklib::internal::Attribute_Data_Definition_Bool const& saklib::internal::Attribute_Data_Definition::cget_bool() const
{
    return cget_bool_type<bool>();
}

saklib::internal::Attribute_Data_Definition_Int const& saklib::internal::Attribute_Data_Definition::cget_int() const
{
    return cget_int_type<int>();
}


template <typename T>
bool saklib::internal::Attribute_Data_Definition::is_bool_type() const
{
    return m_any_definition.type() == typeid(Attribute_Data_Definition_Boolean_Type<T>);
}

template <typename T>
bool saklib::internal::Attribute_Data_Definition::is_int_type() const
{
    return m_any_definition.type() == typeid(Attribute_Data_Definition_Integral_Type<T>);
}

template <typename T>
void saklib::internal::Attribute_Data_Definition::set_to_bool_type()
{
    if(!is_bool())
    {
        *this = Attribute_Data_Definition(cget_name(), Type_Boolean_Type<T>());
    }
}

template <typename T>
void saklib::internal::Attribute_Data_Definition::set_to_int_type()
{
    if(!is_int())
    {
        *this = Attribute_Data_Definition(cget_name(), Type_Integral_Type<T>());
    }
}

template <typename T>
saklib::internal::Attribute_Data_Definition_Boolean_Type<T>& saklib::internal::Attribute_Data_Definition::get_bool_type()
{
    if(is_bool_type<T>())
    {
        return boost::any_cast<Attribute_Data_Definition_Boolean_Type<T>&>(m_any_definition);
    }
    else
    {
        throw Bad_Attribute_Data_Type();
        //throw Bad_Attribute_Data_Type(TS_Bool()(), cget_type());
    }
}

template <typename T>
saklib::internal::Attribute_Data_Definition_Integral_Type<T>& saklib::internal::Attribute_Data_Definition::get_int_type()
{
    if(is_int_type<T>())
    {
        return boost::any_cast<Attribute_Data_Definition_Integral_Type<T>&>(m_any_definition);
    }
    else
    {
        throw Bad_Attribute_Data_Type();
        //throw Bad_Attribute_Data_Type(TS_Int()(), cget_type());
    }
}

template <typename T>
saklib::internal::Attribute_Data_Definition_Boolean_Type<T> const& saklib::internal::Attribute_Data_Definition::cget_bool_type() const
{
    if(is_bool_type<T>())
    {
        return boost::any_cast<Attribute_Data_Definition_Boolean_Type<T> const&>(m_any_definition);
    }
    else
    {
        throw Bad_Attribute_Data_Type();
        //throw Bad_Attribute_Data_Type(TS_Bool()(), cget_type());
    }
}

template <typename T>
saklib::internal::Attribute_Data_Definition_Integral_Type<T> const& saklib::internal::Attribute_Data_Definition::cget_int_type() const
{
    if(is_int_type<T>())
    {
        return boost::any_cast<Attribute_Data_Definition_Integral_Type<T> const&>(m_any_definition);
    }
    else
    {
        throw Bad_Attribute_Data_Type();
        //throw Bad_Attribute_Data_Type(TS_Int()(), cget_type());
    }
}

// Factory Functions
//============================================================

saklib::internal::Attribute_Data_Definition saklib::internal::make_attribute_definition_bool__default(std::string const& a_name)
{
    return Attribute_Data_Definition(a_name, Type_Bool());
}

saklib::internal::Attribute_Data_Definition saklib::internal::make_attribute_definition_bool(std::string const& a_name, bool a_initial)
{
    return Attribute_Data_Definition(a_name, Type_Bool(), a_initial);
}

saklib::internal::Attribute_Data_Definition saklib::internal::make_attribute_definition_int__default(std::string const& a_name)
{
    return Attribute_Data_Definition(a_name, Type_Int());
}

saklib::internal::Attribute_Data_Definition saklib::internal::make_attribute_definition_int(std::string const& a_name, int a_bound1, int a_bound2, int a_intiial)
{
    return Attribute_Data_Definition(a_name, Type_Int(), a_bound1, a_bound2, a_intiial);
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

// Forced Instantiation
//============================================================

template bool saklib::internal::Attribute_Data_Definition::is_bool_type<bool>() const;
template void saklib::internal::Attribute_Data_Definition::set_to_bool_type<bool>();
template saklib::internal::Attribute_Data_Definition_Boolean_Type<bool>& saklib::internal::Attribute_Data_Definition::get_bool_type<bool>();
template saklib::internal::Attribute_Data_Definition_Boolean_Type<bool> const& saklib::internal::Attribute_Data_Definition::cget_bool_type<bool>() const;


template bool saklib::internal::Attribute_Data_Definition::is_int_type<short>() const;
template void saklib::internal::Attribute_Data_Definition::set_to_int_type<short>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<short>& saklib::internal::Attribute_Data_Definition::get_int_type<short>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<short> const& saklib::internal::Attribute_Data_Definition::cget_int_type<short>() const;

template bool saklib::internal::Attribute_Data_Definition::is_int_type<unsigned short>() const;
template void saklib::internal::Attribute_Data_Definition::set_to_int_type<unsigned short>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<unsigned short>& saklib::internal::Attribute_Data_Definition::get_int_type<unsigned short>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<unsigned short> const& saklib::internal::Attribute_Data_Definition::cget_int_type<unsigned short>() const;

template bool saklib::internal::Attribute_Data_Definition::is_int_type<int>() const;
template void saklib::internal::Attribute_Data_Definition::set_to_int_type<int>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<int>& saklib::internal::Attribute_Data_Definition::get_int_type<int>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<int> const& saklib::internal::Attribute_Data_Definition::cget_int_type<int>() const;

template bool saklib::internal::Attribute_Data_Definition::is_int_type<unsigned int>() const;
template void saklib::internal::Attribute_Data_Definition::set_to_int_type<unsigned int>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<unsigned int>& saklib::internal::Attribute_Data_Definition::get_int_type<unsigned int>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<unsigned int> const& saklib::internal::Attribute_Data_Definition::cget_int_type<unsigned int>() const;

template bool saklib::internal::Attribute_Data_Definition::is_int_type<long>() const;
template void saklib::internal::Attribute_Data_Definition::set_to_int_type<long>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<long>& saklib::internal::Attribute_Data_Definition::get_int_type<long>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<long> const& saklib::internal::Attribute_Data_Definition::cget_int_type<long>() const;

template bool saklib::internal::Attribute_Data_Definition::is_int_type<unsigned long>() const;
template void saklib::internal::Attribute_Data_Definition::set_to_int_type<unsigned long>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<unsigned long>& saklib::internal::Attribute_Data_Definition::get_int_type<unsigned long>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<unsigned long> const& saklib::internal::Attribute_Data_Definition::cget_int_type<unsigned long>() const;

template bool saklib::internal::Attribute_Data_Definition::is_int_type<long long>() const;
template void saklib::internal::Attribute_Data_Definition::set_to_int_type<long long>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<long long>& saklib::internal::Attribute_Data_Definition::get_int_type<long long>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<long long> const& saklib::internal::Attribute_Data_Definition::cget_int_type<long long>() const;

template bool saklib::internal::Attribute_Data_Definition::is_int_type<unsigned long long>() const;
template void saklib::internal::Attribute_Data_Definition::set_to_int_type<unsigned long long>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<unsigned long long>& saklib::internal::Attribute_Data_Definition::get_int_type<unsigned long long>();
template saklib::internal::Attribute_Data_Definition_Integral_Type<unsigned long long> const& saklib::internal::Attribute_Data_Definition::cget_int_type<unsigned long long>() const;


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
    return is_bool_type<bool>();
}

bool saklib::internal::Attribute_Data::is_int() const
{
    return is_int_type<int>();
}

saklib::internal::Attribute_Data_Bool& saklib::internal::Attribute_Data::get_bool()
{
    return get_bool_type<bool>();
}

saklib::internal::Attribute_Data_Int& saklib::internal::Attribute_Data::get_int()
{
    return get_int_type<int>();
}

saklib::internal::Attribute_Data_Bool const& saklib::internal::Attribute_Data::cget_bool() const
{
    return cget_bool_type<bool>();
}

saklib::internal::Attribute_Data_Int const& saklib::internal::Attribute_Data::cget_int() const
{
    return cget_int_type<int>();
}

template <typename T>
bool saklib::internal::Attribute_Data::is_bool_type() const
{
    return m_any_attribute.type() == typeid(Attribute_Data_Boolean_Type<T>);
}

template <typename T>
bool saklib::internal::Attribute_Data::is_int_type() const
{
    return m_any_attribute.type() == typeid(Attribute_Data_Integral_Type<T>);
}

template <typename T>
saklib::internal::Attribute_Data_Boolean_Type<T>& saklib::internal::Attribute_Data::get_bool_type()
{
    if(is_bool_type<T>())
    {
        return boost::any_cast<Attribute_Data_Boolean_Type<T>&>(m_any_attribute);
    }
    else
    {
        throw Bad_Attribute_Data_Type();
        //throw Bad_Attribute_Data_Type(TS_Bool()(), cget_type());
    }
}

template <typename T>
saklib::internal::Attribute_Data_Integral_Type<T>& saklib::internal::Attribute_Data::get_int_type()
{
    if(is_int_type<T>())
    {
        return boost::any_cast<Attribute_Data_Integral_Type<T>&>(m_any_attribute);
    }
    else
    {
        throw Bad_Attribute_Data_Type();
        //throw Bad_Attribute_Data_Type(TS_Int()(), cget_type());
    }
}

template <typename T>
saklib::internal::Attribute_Data_Boolean_Type<T> const& saklib::internal::Attribute_Data::cget_bool_type() const
{
    if(is_bool_type<T>())
    {
        return boost::any_cast<Attribute_Data_Boolean_Type<T> const&>(m_any_attribute);
    }
    else
    {
        throw Bad_Attribute_Data_Type();
        //throw Bad_Attribute_Data_Type(TS_Bool()(), cget_type());
    }
}

template <typename T>
saklib::internal::Attribute_Data_Integral_Type<T> const& saklib::internal::Attribute_Data::cget_int_type() const
{
    if(is_int_type<T>())
    {
        return boost::any_cast<Attribute_Data_Integral_Type<T> const&>(m_any_attribute);
    }
    else
    {
        throw Bad_Attribute_Data_Type();
        //throw Bad_Attribute_Data_Type(TS_Int()(), cget_type());
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

// Forced Instantiation
//============================================================
// Boolean Type
template bool saklib::internal::Attribute_Data::is_bool_type<bool>() const;
template saklib::internal::Attribute_Data_Boolean_Type<bool>& saklib::internal::Attribute_Data::get_bool_type<bool>();
template saklib::internal::Attribute_Data_Boolean_Type<bool> const& saklib::internal::Attribute_Data::cget_bool_type<bool>() const;

// Integral Type
template bool saklib::internal::Attribute_Data::is_int_type<short>() const;
template saklib::internal::Attribute_Data_Integral_Type<short>& saklib::internal::Attribute_Data::get_int_type<short>();
template saklib::internal::Attribute_Data_Integral_Type<short> const& saklib::internal::Attribute_Data::cget_int_type<short>() const;

template bool saklib::internal::Attribute_Data::is_int_type<unsigned short>() const;
template saklib::internal::Attribute_Data_Integral_Type<unsigned short>& saklib::internal::Attribute_Data::get_int_type<unsigned short>();
template saklib::internal::Attribute_Data_Integral_Type<unsigned short> const& saklib::internal::Attribute_Data::cget_int_type<unsigned short>() const;

template bool saklib::internal::Attribute_Data::is_int_type<int>() const;
template saklib::internal::Attribute_Data_Integral_Type<int>& saklib::internal::Attribute_Data::get_int_type<int>();
template saklib::internal::Attribute_Data_Integral_Type<int> const& saklib::internal::Attribute_Data::cget_int_type<int>() const;

template bool saklib::internal::Attribute_Data::is_int_type<unsigned int>() const;
template saklib::internal::Attribute_Data_Integral_Type<unsigned int>& saklib::internal::Attribute_Data::get_int_type<unsigned int>();
template saklib::internal::Attribute_Data_Integral_Type<unsigned int> const& saklib::internal::Attribute_Data::cget_int_type<unsigned int>() const;

template bool saklib::internal::Attribute_Data::is_int_type<long>() const;
template saklib::internal::Attribute_Data_Integral_Type<long>& saklib::internal::Attribute_Data::get_int_type<long>();
template saklib::internal::Attribute_Data_Integral_Type<long> const& saklib::internal::Attribute_Data::cget_int_type<long>() const;

template bool saklib::internal::Attribute_Data::is_int_type<unsigned long>() const;
template saklib::internal::Attribute_Data_Integral_Type<unsigned long>& saklib::internal::Attribute_Data::get_int_type<unsigned long>();
template saklib::internal::Attribute_Data_Integral_Type<unsigned long> const& saklib::internal::Attribute_Data::cget_int_type<unsigned long>() const;

template bool saklib::internal::Attribute_Data::is_int_type<long long>() const;
template saklib::internal::Attribute_Data_Integral_Type<long long>& saklib::internal::Attribute_Data::get_int_type<long long>();
template saklib::internal::Attribute_Data_Integral_Type<long long> const& saklib::internal::Attribute_Data::cget_int_type<long long>() const;

template bool saklib::internal::Attribute_Data::is_int_type<unsigned long long>() const;
template saklib::internal::Attribute_Data_Integral_Type<unsigned long long>& saklib::internal::Attribute_Data::get_int_type<unsigned long long>();
template saklib::internal::Attribute_Data_Integral_Type<unsigned long long> const& saklib::internal::Attribute_Data::cget_int_type<unsigned long long>() const;
