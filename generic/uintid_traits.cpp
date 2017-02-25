#include "uintid_traits.hpp"

template <typename T>
typename generic::internal::UintID_Traits<T>::id_type generic::internal::UintID_Traits<T>::make_null_id() noexcept
{
    return id_type(0);
}
template <typename T>
void generic::internal::UintID_Traits<T>::assign(id_type& a_id, id_type const& a_other) noexcept
{
    a_id = a_other;
}
template <typename T>
bool generic::internal::UintID_Traits<T>::less_than(id_type const& a_id, id_type const& a_other) noexcept
{
    return a_id.get() < a_other.get();
}
template <typename T>
bool generic::internal::UintID_Traits<T>::equal(id_type const& a_id, id_type const& a_other) noexcept
{
    return a_id.get() == a_other.get();
}

template generic::internal::UintID_Traits<unsigned char>;
template generic::internal::UintID_Traits<unsigned short>;
template generic::internal::UintID_Traits<unsigned int>;
template generic::internal::UintID_Traits<unsigned long>;
template generic::internal::UintID_Traits<unsigned long long>;
