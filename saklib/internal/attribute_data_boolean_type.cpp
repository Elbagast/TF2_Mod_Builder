#include "attribute_data_boolean_type.h"
#include "type_string.h"

#include <iostream>

//---------------------------------------------------------------------------
// Attribute_Data_Definition_Boolean_Type<T>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T>
saklib::internal::Attribute_Data_Definition_Boolean_Type<T>::Attribute_Data_Definition_Boolean_Type(std::string const& a_name, boolean_type a_initial):
    m_name(a_name),
    m_initial_value(a_initial)
{
    set_initial_value(a_initial);
}

// Interface
//============================================================
template <typename T>
std::string const& saklib::internal::Attribute_Data_Definition_Boolean_Type<T>::cget_name() const
{
    return m_name;
}

template <typename T>
void saklib::internal::Attribute_Data_Definition_Boolean_Type<T>::set_name(std::string const& a_name)
{
    m_name = a_name;
}

template <typename T>
std::string const& saklib::internal::Attribute_Data_Definition_Boolean_Type<T>::cget_type() const
{
    return Type_String<T>()();
}

template <typename T>
bool saklib::internal::Attribute_Data_Definition_Boolean_Type<T>::can_set_value_to(boolean_type /*a_value*/) const
{
    return true;
}

template <typename T>
typename saklib::internal::Attribute_Data_Definition_Boolean_Type<T>::boolean_type
saklib::internal::Attribute_Data_Definition_Boolean_Type<T>::get_initial_value() const
{
    return m_initial_value;
}

// Set the initial value.
template <typename T>
void saklib::internal::Attribute_Data_Definition_Boolean_Type<T>::set_initial_value(boolean_type a_value)
{
    m_initial_value = a_value;
}

// Set the constraints to the defaults
template <typename T>
void saklib::internal::Attribute_Data_Definition_Boolean_Type<T>::set_to_default()
{
    m_initial_value = default_initial_value();
}

template <typename T>
typename saklib::internal::Attribute_Data_Definition_Boolean_Type<T>::boolean_type
saklib::internal::Attribute_Data_Definition_Boolean_Type<T>::default_initial_value()
{
    return boolean_type{false};
}

// Non-Member Operators
//============================================================
template <typename T>
std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Attribute_Data_Definition_Boolean_Type<T> const& a_constraint)
{
    a_ostream << "Attribute_Data_Definition_Bool { ";
    a_ostream << "initial=\"" << std::boolalpha << a_constraint.get_initial_value() << std::noboolalpha ;
    a_ostream << "\" } ";
    return a_ostream;
}

// Forced Instantiation
//============================================================
template saklib::internal::Attribute_Data_Definition_Boolean_Type<bool>;
template std::ostream& saklib::internal::operator << <bool>(std::ostream& a_ostream, Attribute_Data_Definition_Boolean_Type<bool> const& a_constraint);


//---------------------------------------------------------------------------
// Attribute_Data_Boolean_Type<T>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T>
saklib::internal::Attribute_Data_Boolean_Type<T>::Attribute_Data_Boolean_Type(definition_type const& ar_constraint):
    mr_definition{ar_constraint},
    m_value{mr_definition.get_initial_value()}
{
}

// Interface
//============================================================
template <typename T>
std::string const& saklib::internal::Attribute_Data_Boolean_Type<T>::cget_name() const
{
    return mr_definition.cget_name();
}

template <typename T>
std::string const& saklib::internal::Attribute_Data_Boolean_Type<T>::cget_type() const
{
    return mr_definition.cget_type();
}

template <typename T>
std::string saklib::internal::Attribute_Data_Boolean_Type<T>::cget_value_string() const
{
    if (m_value == true)
    {
        return "true";
    }
    else if (m_value == false)
    {
        return "false";
    }
    else
    {
        return "";
    }
}

// Get the stored value
template <typename T>
typename saklib::internal::Attribute_Data_Boolean_Type<T>::boolean_type saklib::internal::Attribute_Data_Boolean_Type<T>::cget_value() const
{
    return m_value;
}

// Can the value be set to this? Returns true if it can, but returns false if the
// value is already set to this since there would be no change.
template <typename T>
bool saklib::internal::Attribute_Data_Boolean_Type<T>::can_set_value_to(boolean_type a_value) const
{
    if (a_value != m_value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// If can_set_value_to() then set the value to this and return true, else false.
template <typename T>
bool saklib::internal::Attribute_Data_Boolean_Type<T>::try_set_value(boolean_type a_value)
{
    if (can_set_value_to(a_value))
    {
        set_value(a_value);
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
void saklib::internal::Attribute_Data_Boolean_Type<T>::set_value(boolean_type a_value)
{
    m_value = a_value;
}

// Non-Member Operators
//============================================================
template <typename T>
std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Attribute_Data_Boolean_Type<T> const& a_constrained)
{
    a_ostream << "Attribute_Data_Bool { ";
    a_ostream << "value=\"" << std::boolalpha << a_constrained.cget_value();
    a_ostream << "\" } ";
    return a_ostream;
}

// Forced Instantiation
//============================================================
template saklib::internal::Attribute_Data_Boolean_Type<bool>;
template std::ostream& saklib::internal::operator << <bool>(std::ostream& a_ostream, Attribute_Data_Boolean_Type<bool> const& a_constraint);

