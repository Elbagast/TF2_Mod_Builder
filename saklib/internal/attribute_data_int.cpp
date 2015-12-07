#include "attribute_data_int.h"
#include "type_string.h"


#include <limits>
#include <iostream>

//---------------------------------------------------------------------------
// Attribute_Data_Definition_Integral_Type<T>
//---------------------------------------------------------------------------

// Special 6
//============================================================
// Initialise with the default lowest, highest and initial values.
template <typename T>
saklib::internal::Attribute_Data_Definition_Integral_Type<T>::Attribute_Data_Definition_Integral_Type(std::string const& a_name):
    m_name(a_name),
    m_initial_value(default_initial_value()),
    m_lowest_value(default_lowest_value()),
    m_highest_value(default_highest_value())
{}

// Initialise as if calling set_range(a_bound1, a_bound2, a_initial)
template <typename T>
saklib::internal::Attribute_Data_Definition_Integral_Type<T>::Attribute_Data_Definition_Integral_Type(std::string const& a_name, int_type a_bound1, int_type a_bound2, int_type a_initial):
    Attribute_Data_Definition_Integral_Type(a_name)
{
    set_range(a_bound1, a_bound2, a_initial);
}

template <typename T>
saklib::internal::Attribute_Data_Definition_Integral_Type<T>::Attribute_Data_Definition_Integral_Type(std::string const& a_name, int_type a_value):
    Attribute_Data_Definition_Integral_Type(a_name)
{
    set_to_only_value(a_value);
}

// Interface
//============================================================
template <typename T>
std::string const& saklib::internal::Attribute_Data_Definition_Integral_Type<T>::cget_name() const
{
    return m_name;
}

template <typename T>
void saklib::internal::Attribute_Data_Definition_Integral_Type<T>::set_name(std::string const& a_name)
{
    m_name = a_name;
}

template <typename T>
std::string const& saklib::internal::Attribute_Data_Definition_Integral_Type<T>::cget_type() const
{
    return Type_String<T>()();
}

template <typename T>
bool saklib::internal::Attribute_Data_Definition_Integral_Type<T>::can_set_value_to(int_type a_value) const
{
    return a_value >= m_lowest_value && a_value <= m_highest_value;
}

template <typename T>
typename saklib::internal::Attribute_Data_Definition_Integral_Type<T>::int_type
saklib::internal::Attribute_Data_Definition_Integral_Type<T>::get_initial_value() const
{
    return m_initial_value;
}

template <typename T>
typename saklib::internal::Attribute_Data_Definition_Integral_Type<T>::int_type
saklib::internal::Attribute_Data_Definition_Integral_Type<T>::get_lowest_value() const
{
    return m_lowest_value;
}

template <typename T>
typename saklib::internal::Attribute_Data_Definition_Integral_Type<T>::int_type
saklib::internal::Attribute_Data_Definition_Integral_Type<T>::get_highest_value() const
{
    return m_highest_value;
}

// Set the initial value. If the supplied value is outside [lowest, highest] it
// will instead be set to the boundary it is closest to.
// e.g. if lowest = 0, highest = 10, initial = 5
// set_initial_value(1) -> lowest = 0, highest = 10, initial = 1
// set_initial_value(-1) -> lowest = 0, highest = 10, initial = 0
// set_initial_value(11) -> lowest = 0, highest = 10, initial = 10
template <typename T>
void saklib::internal::Attribute_Data_Definition_Integral_Type<T>::set_initial_value(int_type a_value)
{
    if (a_value > m_highest_value)
    {
        m_initial_value = m_highest_value;
    }
    else if (a_value < m_lowest_value)
    {
        m_initial_value = m_lowest_value;
    }
    else
    {
        m_initial_value = a_value;
    }
}

// Set the lowest value. If the supplied value is greater than initial value it
// will instead be set to be the same as the initial value.
// e.g. if lowest = 0, highest = 10, initial = 5
// set_lowest_value(1) -> lowest = 1, highest = 10, initial = 5
// set_lowest_value(6) -> lowest = 5, highest = 10, initial = 5
// set_lowest_value(11) -> lowest = 5, highest = 10, initial = 5
template <typename T>
void saklib::internal::Attribute_Data_Definition_Integral_Type<T>::set_lowest_value(int_type a_value)
{
    if (a_value > m_initial_value)
    {
        m_lowest_value = m_initial_value;
    }
    else
    {
        m_lowest_value = a_value;
    }
}

// Set the highest value. If the supplied value is less than initial value it
// will instead be set to be the same as the initial value.
// e.g. if lowest = 0, highest = 10, initial = 5
// set_highest_value(-1) -> lowest = 1, highest = 5, initial = 5
// set_highest_value(4) -> lowest = 1, highest = 5, initial = 5
// set_highest_value(11) -> lowest = 1, highest = 11, initial = 5
template <typename T>
void saklib::internal::Attribute_Data_Definition_Integral_Type<T>::set_highest_value(int_type a_value)
{
    if (a_value < m_initial_value)
    {
        m_highest_value = m_initial_value;
    }
    else
    {
        m_highest_value = a_value;
    }
}

// Set the all the constraint values. You must supply at least the range bounds
// either way around. The lower of them will become the lowest and the higher
// the highest. If you supply an initial value, it will be set after the lowest
// and highest have been set, using the same rules as set_initial_value(). By
// default the initial value is 0, so it will be set to that or the closest
// boundary to 0.
// e.g.
// set_range(-5,10) -> lowest = -5, highest = 10, initial = 0
// set_range(-5,10,1) -> lowest = -5, highest = 10, initial = 1
// set_range(-5,10,-6) -> lowest = -5, highest = 10, initial = -5
// set_range(-5,10,123) -> lowest = -5, highest = 10, initial = 10
// set_range(120,0) -> lowest = 0, highest = 120, initial = 0
// set_range(120,0,20) -> lowest = 0, highest = 120, initial = 20
// set_range(120,0,-20) -> lowest = 0, highest = 120, initial = 0
// set_range(120,0,140) -> lowest = 0, highest = 120, initial = 120
template <typename T>
void saklib::internal::Attribute_Data_Definition_Integral_Type<T>::set_range(int_type a_bound1, int_type a_bound2, int_type a_initial)
{
    if (a_bound1 <= a_bound2)
    {
        m_lowest_value = a_bound1;
        m_highest_value = a_bound2;
    }
    else
    {
        m_lowest_value = a_bound2;
        m_highest_value = a_bound1;
    }
    set_initial_value(a_initial);
}

// Set the lowest, highest, and inital values all to the given value. This
// means the constraint is set to a single value.
// e.g.
// set_to_only_value(0) -> lowest = 0, highest = 0, initial = 0
// set_to_only_value(1234) -> lowest = 1234, highest = 1234, initial = 1234
// set_to_only_value(-5678) -> lowest = -5678, highest = -5678, initial = -5678
template <typename T>
void saklib::internal::Attribute_Data_Definition_Integral_Type<T>::set_to_only_value(int_type a_value)
{
    m_initial_value = a_value;
    m_lowest_value = a_value;
    m_highest_value = a_value;
}


// Set the constraints to the defaults
template <typename T>
void saklib::internal::Attribute_Data_Definition_Integral_Type<T>::set_to_default()
{
    m_initial_value = default_initial_value();
    m_lowest_value = default_lowest_value();
    m_highest_value = default_highest_value();
}


template <typename T>
typename saklib::internal::Attribute_Data_Definition_Integral_Type<T>::int_type
saklib::internal::Attribute_Data_Definition_Integral_Type<T>::default_initial_value()
{
    return int_type{0};
}

template <typename T>
typename saklib::internal::Attribute_Data_Definition_Integral_Type<T>::int_type
saklib::internal::Attribute_Data_Definition_Integral_Type<T>::default_lowest_value()
{
    return std::numeric_limits<int_type>::lowest();
}

template <typename T>
typename saklib::internal::Attribute_Data_Definition_Integral_Type<T>::int_type
saklib::internal::Attribute_Data_Definition_Integral_Type<T>::default_highest_value()
{
    return std::numeric_limits<int_type>::max();
}

// Non-Member Operators
//============================================================
template <typename T>
std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Attribute_Data_Definition_Integral_Type<T> const& ar_definition)
{
    a_ostream << "Attribute_Data_Definition_Int {";
    a_ostream << " name=\"" << ar_definition.cget_name();
    a_ostream << "\" initial=\"" << ar_definition.get_initial_value();
    a_ostream << "\" lowest=\"" << ar_definition.get_lowest_value();
    a_ostream << "\" highest=\"" << ar_definition.get_highest_value();
    a_ostream << "\" } ";
    return a_ostream;
}

// Forced Instantiation
//============================================================
// include char types?
template saklib::internal::Attribute_Data_Definition_Integral_Type<short>;
template saklib::internal::Attribute_Data_Definition_Integral_Type<unsigned short>;
template saklib::internal::Attribute_Data_Definition_Integral_Type<int>;
template saklib::internal::Attribute_Data_Definition_Integral_Type<unsigned int>;
template saklib::internal::Attribute_Data_Definition_Integral_Type<long>;
template saklib::internal::Attribute_Data_Definition_Integral_Type<unsigned long>;
template saklib::internal::Attribute_Data_Definition_Integral_Type<long long>;
template saklib::internal::Attribute_Data_Definition_Integral_Type<unsigned long long>;

template std::ostream& saklib::internal::operator << <short>(std::ostream& a_ostream, Attribute_Data_Definition_Integral_Type<short> const& a_constraint);
template std::ostream& saklib::internal::operator << <unsigned short>(std::ostream& a_ostream, Attribute_Data_Definition_Integral_Type<unsigned short> const& a_constraint);
template std::ostream& saklib::internal::operator << <int>(std::ostream& a_ostream, Attribute_Data_Definition_Integral_Type<int> const& a_constraint);
template std::ostream& saklib::internal::operator << <unsigned int>(std::ostream& a_ostream, Attribute_Data_Definition_Integral_Type<unsigned int> const& a_constraint);
template std::ostream& saklib::internal::operator << <long>(std::ostream& a_ostream, Attribute_Data_Definition_Integral_Type<long> const& a_constraint);
template std::ostream& saklib::internal::operator << <unsigned long>(std::ostream& a_ostream, Attribute_Data_Definition_Integral_Type<unsigned long> const& a_constraint);
template std::ostream& saklib::internal::operator << <long long>(std::ostream& a_ostream, Attribute_Data_Definition_Integral_Type<long long> const& a_constraint);
template std::ostream& saklib::internal::operator << <unsigned long long>(std::ostream& a_ostream, Attribute_Data_Definition_Integral_Type<unsigned long long> const& a_constraint);


//---------------------------------------------------------------------------
// Attribute_Data_Integral_Type<T>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T>
saklib::internal::Attribute_Data_Integral_Type<T>::Attribute_Data_Integral_Type(definition_type const& ar_definition):
    mr_definition(ar_definition),
    m_value(mr_definition.get_initial_value())
{
}

// Interface
//============================================================
template <typename T>
std::string const& saklib::internal::Attribute_Data_Integral_Type<T>::cget_name() const
{
    return mr_definition.cget_name();
}

template <typename T>
std::string const& saklib::internal::Attribute_Data_Integral_Type<T>::cget_type() const
{
    return mr_definition.cget_type();
}

template <typename T>
std::string saklib::internal::Attribute_Data_Integral_Type<T>::cget_value_string() const
{
    return std::to_string(m_value);
}

// Get the stored value
template <typename T>
typename saklib::internal::Attribute_Data_Integral_Type<T>::int_type saklib::internal::Attribute_Data_Integral_Type<T>::cget_value() const
{
    return m_value;
}

// Can the value be set to this? Returns true if it can, but returns false if the
// value is already set to this since there would be no change.
template <typename T>
bool saklib::internal::Attribute_Data_Integral_Type<T>::can_set_value_to(int_type a_value) const
{
    if (a_value != m_value && mr_definition.can_set_value_to(a_value))
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
bool saklib::internal::Attribute_Data_Integral_Type<T>::try_set_value(int_type a_value)
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
void saklib::internal::Attribute_Data_Integral_Type<T>::set_value(int_type a_value)
{
    m_value = a_value;
}

/*
template <typename T>
typename saklib::internal::Attribute_Data_Integral_Type<T>::integer_type
saklib::internal::Attribute_Data_Integral_Type<T>::get_initial_value() const
{
    return mr_constraint.get_initial_value();
}
*/
template <typename T>
typename saklib::internal::Attribute_Data_Integral_Type<T>::int_type
saklib::internal::Attribute_Data_Integral_Type<T>::cget_lowest_value() const
{
    return mr_definition.get_lowest_value();
}

template <typename T>
typename saklib::internal::Attribute_Data_Integral_Type<T>::int_type
saklib::internal::Attribute_Data_Integral_Type<T>::cget_highest_value() const
{
    return mr_definition.get_highest_value();
}

// Non-Member Operators
//============================================================
template <typename T>
std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Attribute_Data_Integral_Type<T> const& ar_attribute)
{
    a_ostream << "Attribute_Data_Int {";
    a_ostream << " name=\"" << ar_attribute.cget_name();
    a_ostream << " value=\""<< ar_attribute.cget_value();
    a_ostream << "\" lowest=\"" << ar_attribute.cget_lowest_value();
    a_ostream << "\" highest=\"" << ar_attribute.cget_highest_value();
    a_ostream << "\" } ";
    return a_ostream;
}

// Forced Instantiation
//============================================================
// include char types?
template saklib::internal::Attribute_Data_Integral_Type<short>;
template saklib::internal::Attribute_Data_Integral_Type<unsigned short>;
template saklib::internal::Attribute_Data_Integral_Type<int>;
template saklib::internal::Attribute_Data_Integral_Type<unsigned int>;
template saklib::internal::Attribute_Data_Integral_Type<long>;
template saklib::internal::Attribute_Data_Integral_Type<unsigned long>;
template saklib::internal::Attribute_Data_Integral_Type<long long>;
template saklib::internal::Attribute_Data_Integral_Type<unsigned long long>;

template std::ostream& saklib::internal::operator << <short>(std::ostream& a_ostream, Attribute_Data_Integral_Type<short> const& a_constrained);
template std::ostream& saklib::internal::operator << <unsigned short>(std::ostream& a_ostream, Attribute_Data_Integral_Type<unsigned short> const& a_constrained);
template std::ostream& saklib::internal::operator << <int>(std::ostream& a_ostream, Attribute_Data_Integral_Type<int> const& a_constrained);
template std::ostream& saklib::internal::operator << <unsigned int>(std::ostream& a_ostream, Attribute_Data_Integral_Type<unsigned int> const& a_constrained);
template std::ostream& saklib::internal::operator << <long>(std::ostream& a_ostream, Attribute_Data_Integral_Type<long> const& a_constrained);
template std::ostream& saklib::internal::operator << <unsigned long>(std::ostream& a_ostream, Attribute_Data_Integral_Type<unsigned long> const& a_constrained);
template std::ostream& saklib::internal::operator << <long long>(std::ostream& a_ostream, Attribute_Data_Integral_Type<long long> const& a_constrained);
template std::ostream& saklib::internal::operator << <unsigned long long>(std::ostream& a_ostream, Attribute_Data_Integral_Type<unsigned long long> const& a_constrained);

/*
template saklib::internal::Type_Integral_Type<short>;
template saklib::internal::Type_Integral_Type<unsigned short>;
template saklib::internal::Type_Integral_Type<int>;
template saklib::internal::Type_Integral_Type<unsigned int>;
template saklib::internal::Type_Integral_Type<long>;
template saklib::internal::Type_Integral_Type<unsigned long>;
template saklib::internal::Type_Integral_Type<long long>;
template saklib::internal::Type_Integral_Type<unsigned long long>;
*/
