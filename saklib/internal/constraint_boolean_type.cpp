#include "constraint_boolean_type.h"

#include <iostream>

// Initialise as if calling set_range(a_bound1, a_bound2, a_initial)
template <typename T>
saklib::internal::Constraint_Boolean_Type<T>::Constraint_Boolean_Type(boolean_type a_initial):
    m_initial_value{a_initial}
{
    set_initial_value(a_initial);
}

template <typename T>
bool saklib::internal::Constraint_Boolean_Type<T>::can_set_value_to(boolean_type /*a_value*/) const
{
    return true;
}

template <typename T>
typename saklib::internal::Constraint_Boolean_Type<T>::boolean_type
saklib::internal::Constraint_Boolean_Type<T>::get_initial_value() const
{
    return m_initial_value;
}

// Set the initial value.
template <typename T>
void saklib::internal::Constraint_Boolean_Type<T>::set_initial_value(boolean_type a_value)
{
    m_initial_value = a_value;
}

// Set the constraints to the defaults
template <typename T>
void saklib::internal::Constraint_Boolean_Type<T>::set_to_default()
{
    m_initial_value = default_initial_value();
}

template <typename T>
typename saklib::internal::Constraint_Boolean_Type<T>::boolean_type
saklib::internal::Constraint_Boolean_Type<T>::default_initial_value()
{
    return boolean_type{false};
}

template saklib::internal::Constraint_Boolean_Type<bool>;



template <typename T>
saklib::internal::Constrained_Boolean_Type<T>::Constrained_Boolean_Type(constraint_type const& ar_constraint):
    mr_constraint{ar_constraint},
    m_value{mr_constraint.get_initial_value()}
{
}

// Get the stored value
template <typename T>
typename saklib::internal::Constrained_Boolean_Type<T>::boolean_type saklib::internal::Constrained_Boolean_Type<T>::get_value() const
{
    return m_value;
}

// Can the value be set to this? Returns true if it can, but returns false if the
// value is already set to this since there would be no change.
template <typename T>
bool saklib::internal::Constrained_Boolean_Type<T>::can_set_value_to(boolean_type a_value) const
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
bool saklib::internal::Constrained_Boolean_Type<T>::try_set_value(boolean_type a_value)
{
    if (can_set_value_to(a_value))
    {
        m_value = a_value;
        return true;
    }
    else
    {
        return false;
    }
}

template saklib::internal::Constrained_Boolean_Type<bool>;


template <typename T>
std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Constraint_Boolean_Type<T> const& a_constraint)
{
    a_ostream << "Constraint_Bool { ";
    a_ostream << "initial=\"" << std::boolalpha << a_constraint.get_initial_value() << std::noboolalpha ;
    a_ostream << "\" } ";
    return a_ostream;
}

template std::ostream& saklib::internal::operator << <bool>(std::ostream& a_ostream, Constraint_Boolean_Type<bool> const& a_constraint);

template <typename T>
std::ostream& saklib::internal::operator << (std::ostream& a_ostream, Constrained_Boolean_Type<T> const& a_constrained)
{
    a_ostream << "Constrained_Bool { ";
    a_ostream << "value=\"" << std::boolalpha << a_constrained.get_value();
    a_ostream << "\" } ";
    return a_ostream;
}

template std::ostream& saklib::internal::operator << <bool>(std::ostream& a_ostream, Constrained_Boolean_Type<bool> const& a_constraint);

