#include "uintid.h"

template <typename T>
generic::internal::UintID<T>::UintID(uint_type a_value) noexcept:
    m_value{a_value}
{}

template <typename T>
typename generic::internal::UintID<T>::uint_type generic::internal::UintID<T>::get() const noexcept
{
    return m_value;
}


template generic::internal::UintID<unsigned char>;
template generic::internal::UintID<unsigned short>;
template generic::internal::UintID<unsigned int>;
template generic::internal::UintID<unsigned long>;
template generic::internal::UintID<unsigned long long>;

