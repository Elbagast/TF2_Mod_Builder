#include "uint_id.h"

#include <cassert>
#include <numeric>

//---------------------------------------------------------------------------
// Unsigned_Integer_ID<T>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T>
saklib::internal::Unsigned_Integer_ID<T>::Unsigned_Integer_ID():
    m_value{get_null_value()}
{}

template <typename T>
saklib::internal::Unsigned_Integer_ID<T>::Unsigned_Integer_ID(uint_type a_value):
    m_value{a_value}
{}

template <typename T>
saklib::internal::Unsigned_Integer_ID<T>::~Unsigned_Integer_ID() = default;

template <typename T>
saklib::internal::Unsigned_Integer_ID<T>::Unsigned_Integer_ID(Unsigned_Integer_ID const& a_other) = default;

template <typename T>
saklib::internal::Unsigned_Integer_ID<T>& saklib::internal::Unsigned_Integer_ID<T>::operator=(Unsigned_Integer_ID const& a_other) = default;


template <typename T>
saklib::internal::Unsigned_Integer_ID<T>::Unsigned_Integer_ID(Unsigned_Integer_ID && a_other):
    m_value{std::move(a_other.m_value)}
{
    a_other.m_value = get_null_value();
}

template <typename T>
saklib::internal::Unsigned_Integer_ID<T>& saklib::internal::Unsigned_Integer_ID<T>::operator=(Unsigned_Integer_ID && a_other)
{
    m_value = std::move(a_other.m_value);
    a_other.m_value = get_null_value();
    return *this;
}

// Interface
//============================================================

template <typename T>
bool saklib::internal::Unsigned_Integer_ID<T>::is_valid() const
{
    return m_value != get_null_value();
}

template <typename T>
bool saklib::internal::Unsigned_Integer_ID<T>::is_null() const
{
    return m_value == get_null_value();
}

template <typename T>
typename saklib::internal::Unsigned_Integer_ID<T>::uint_type saklib::internal::Unsigned_Integer_ID<T>::get_value() const
{
    return m_value;
}

template <typename T>
saklib::internal::Unsigned_Integer_ID<T>::operator bool() const
{
    return is_valid();
}

template <typename T>
typename saklib::internal::Unsigned_Integer_ID<T>::uint_type saklib::internal::Unsigned_Integer_ID<T>::get_null_value()
{
    return uint_type(0);
}

// Comparison Operators
//============================================================
template <typename T>
bool saklib::internal::operator==(Unsigned_Integer_ID<T> lhs, Unsigned_Integer_ID<T> rhs)
{
    return lhs.get_value() == rhs.get_value();
}
template <typename T>
bool saklib::internal::operator!=(Unsigned_Integer_ID<T> lhs, Unsigned_Integer_ID<T> rhs)
{
    return !operator==(lhs, rhs);
}
template <typename T>
bool saklib::internal::operator<(Unsigned_Integer_ID<T> lhs, Unsigned_Integer_ID<T> rhs)
{
    return lhs.get_value() < rhs.get_value();
}
template <typename T>
bool saklib::internal::operator>(Unsigned_Integer_ID<T> lhs, Unsigned_Integer_ID<T> rhs)
{
    return operator<(rhs, lhs);
}
template <typename T>
bool saklib::internal::operator<=(Unsigned_Integer_ID<T> lhs, Unsigned_Integer_ID<T> rhs)
{
    return !operator>(lhs, rhs);
}
template <typename T>
bool saklib::internal::operator>=(Unsigned_Integer_ID<T> lhs, Unsigned_Integer_ID<T> rhs)
{
    return !operator<(lhs, rhs);
}


//---------------------------------------------------------------------------
// Unsigned_Integer_ID_Factory<T>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T>
saklib::internal::Unsigned_Integer_ID_Factory<T>::Unsigned_Integer_ID_Factory() :
    m_revoked_handles{},
    m_next_value{id_type::get_null_value()}
{}

// Interface
//============================================================
template <typename T>
typename saklib::internal::Unsigned_Integer_ID_Factory<T>::id_type saklib::internal::Unsigned_Integer_ID_Factory<T>::make_null_id()
{
    return id_type();
}

template <typename T>
typename saklib::internal::Unsigned_Integer_ID_Factory<T>::id_type saklib::internal::Unsigned_Integer_ID_Factory<T>::issue_id()
{
    id_type new_id{};
    if (m_revoked_handles.empty())
    {
        assert(m_next_value != std::numeric_limits<uint_type>::max());
        new_id = id_type{ ++m_next_value };
    }
    else
    {
        new_id = m_revoked_handles.top();
        m_revoked_handles.pop();
    }
    return new_id;
}

template <typename T>
void saklib::internal::Unsigned_Integer_ID_Factory<T>::revoke_id(id_type a_id)
{
    if (a_id)
    {
        m_revoked_handles.push(a_id);
    }
}




template saklib::internal::Unsigned_Integer_ID<unsigned char>;
template saklib::internal::Unsigned_Integer_ID_Factory<unsigned char>;

template bool saklib::internal::operator==(Unsigned_Integer_ID<unsigned char> lhs, Unsigned_Integer_ID<unsigned char> rhs);
template bool saklib::internal::operator!=(Unsigned_Integer_ID<unsigned char> lhs, Unsigned_Integer_ID<unsigned char> rhs);
template bool saklib::internal::operator<(Unsigned_Integer_ID<unsigned char> lhs, Unsigned_Integer_ID<unsigned char> rhs);
template bool saklib::internal::operator>(Unsigned_Integer_ID<unsigned char> lhs, Unsigned_Integer_ID<unsigned char> rhs);
template bool saklib::internal::operator<=(Unsigned_Integer_ID<unsigned char> lhs, Unsigned_Integer_ID<unsigned char> rhs);
template bool saklib::internal::operator>=(Unsigned_Integer_ID<unsigned char> lhs, Unsigned_Integer_ID<unsigned char> rhs);


template saklib::internal::Unsigned_Integer_ID<unsigned short>;
template saklib::internal::Unsigned_Integer_ID_Factory<unsigned short>;

template bool saklib::internal::operator==(Unsigned_Integer_ID<unsigned short> lhs, Unsigned_Integer_ID<unsigned short> rhs);
template bool saklib::internal::operator!=(Unsigned_Integer_ID<unsigned short> lhs, Unsigned_Integer_ID<unsigned short> rhs);
template bool saklib::internal::operator<(Unsigned_Integer_ID<unsigned short> lhs, Unsigned_Integer_ID<unsigned short> rhs);
template bool saklib::internal::operator>(Unsigned_Integer_ID<unsigned short> lhs, Unsigned_Integer_ID<unsigned short> rhs);
template bool saklib::internal::operator<=(Unsigned_Integer_ID<unsigned short> lhs, Unsigned_Integer_ID<unsigned short> rhs);
template bool saklib::internal::operator>=(Unsigned_Integer_ID<unsigned short> lhs, Unsigned_Integer_ID<unsigned short> rhs);


template saklib::internal::Unsigned_Integer_ID<unsigned int>;
template saklib::internal::Unsigned_Integer_ID_Factory<unsigned int>;

template bool saklib::internal::operator==(Unsigned_Integer_ID<unsigned int> lhs, Unsigned_Integer_ID<unsigned int> rhs);
template bool saklib::internal::operator!=(Unsigned_Integer_ID<unsigned int> lhs, Unsigned_Integer_ID<unsigned int> rhs);
template bool saklib::internal::operator<(Unsigned_Integer_ID<unsigned int> lhs, Unsigned_Integer_ID<unsigned int> rhs);
template bool saklib::internal::operator>(Unsigned_Integer_ID<unsigned int> lhs, Unsigned_Integer_ID<unsigned int> rhs);
template bool saklib::internal::operator<=(Unsigned_Integer_ID<unsigned int> lhs, Unsigned_Integer_ID<unsigned int> rhs);
template bool saklib::internal::operator>=(Unsigned_Integer_ID<unsigned int> lhs, Unsigned_Integer_ID<unsigned int> rhs);


template saklib::internal::Unsigned_Integer_ID<unsigned long>;
template saklib::internal::Unsigned_Integer_ID_Factory<unsigned long>;

template bool saklib::internal::operator==(Unsigned_Integer_ID<unsigned long> lhs, Unsigned_Integer_ID<unsigned long> rhs);
template bool saklib::internal::operator!=(Unsigned_Integer_ID<unsigned long> lhs, Unsigned_Integer_ID<unsigned long> rhs);
template bool saklib::internal::operator<(Unsigned_Integer_ID<unsigned long> lhs, Unsigned_Integer_ID<unsigned long> rhs);
template bool saklib::internal::operator>(Unsigned_Integer_ID<unsigned long> lhs, Unsigned_Integer_ID<unsigned long> rhs);
template bool saklib::internal::operator<=(Unsigned_Integer_ID<unsigned long> lhs, Unsigned_Integer_ID<unsigned long> rhs);
template bool saklib::internal::operator>=(Unsigned_Integer_ID<unsigned long> lhs, Unsigned_Integer_ID<unsigned long> rhs);


template saklib::internal::Unsigned_Integer_ID<unsigned long long>;
template saklib::internal::Unsigned_Integer_ID_Factory<unsigned long long>;

template bool saklib::internal::operator==(Unsigned_Integer_ID<unsigned long long> lhs, Unsigned_Integer_ID<unsigned long long> rhs);
template bool saklib::internal::operator!=(Unsigned_Integer_ID<unsigned long long> lhs, Unsigned_Integer_ID<unsigned long long> rhs);
template bool saklib::internal::operator<(Unsigned_Integer_ID<unsigned long long> lhs, Unsigned_Integer_ID<unsigned long long> rhs);
template bool saklib::internal::operator>(Unsigned_Integer_ID<unsigned long long> lhs, Unsigned_Integer_ID<unsigned long long> rhs);
template bool saklib::internal::operator<=(Unsigned_Integer_ID<unsigned long long> lhs, Unsigned_Integer_ID<unsigned long long> rhs);
template bool saklib::internal::operator>=(Unsigned_Integer_ID<unsigned long long> lhs, Unsigned_Integer_ID<unsigned long long> rhs);

