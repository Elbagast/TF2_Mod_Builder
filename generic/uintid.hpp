#ifndef GENERIC_UINTID_HPP
#define GENERIC_UINTID_HPP

#include "fwd/uintid.hpp"

namespace generic
{
    //---------------------------------------------------------------------------
    // generic::UintID<uint type>
    //---------------------------------------------------------------------------
    // Basic class that serves as an ID that is based on unsigned integer types.

    namespace internal
    {
        template <typename T>
        class UintID
        {
        public:
            using uint_type = T;

            explicit UintID(uint_type a_value = 0) noexcept;

            uint_type get() const noexcept;

        private:
            uint_type m_value;
        };

        template <typename T>
        bool operator==(UintID<T> a_lhs, UintID<T> a_rhs) noexcept;
        template <typename T>
        bool operator!=(UintID<T> a_lhs, UintID<T> a_rhs) noexcept;
        template <typename T>
        bool operator<(UintID<T> a_lhs, UintID<T> a_rhs) noexcept;
        template <typename T>
        bool operator>(UintID<T> a_lhs, UintID<T> a_rhs) noexcept;
        template <typename T>
        bool operator<=(UintID<T> a_lhs, UintID<T> a_rhs) noexcept;
        template <typename T>
        bool operator>=(UintID<T> a_lhs, UintID<T> a_rhs) noexcept;
    }
}



template <typename T>
bool generic::internal::operator==(UintID<T> a_lhs, UintID<T> a_rhs) noexcept
{
    return a_lhs.get() == a_rhs.get();
}
template <typename T>
bool generic::internal::operator!=(UintID<T> a_lhs, UintID<T> a_rhs) noexcept
{
    return a_lhs.get() != a_rhs.get();
}
template <typename T>
bool generic::internal::operator<(UintID<T> a_lhs, UintID<T> a_rhs) noexcept
{
    return a_lhs.get() < a_rhs.get();
}
template <typename T>
bool generic::internal::operator>(UintID<T> a_lhs, UintID<T> a_rhs) noexcept
{
    return a_lhs.get() > a_rhs.get();
}
template <typename T>
bool generic::internal::operator<=(UintID<T> a_lhs, UintID<T> a_rhs) noexcept
{
    return a_lhs.get() <= a_rhs.get();
}
template <typename T>
bool generic::internal::operator>=(UintID<T> a_lhs, UintID<T> a_rhs) noexcept
{
    return a_lhs.get() >= a_rhs.get();
}

#endif // GENERIC_UINTID_HPP
