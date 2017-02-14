#ifndef UINTID_H
#define UINTID_H

#include <cstdint>

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

    using Uint8ID = internal::UintID<std::uint8_t>;
    using Uint16ID = internal::UintID<std::uint16_t>;
    using Uint32ID = internal::UintID<std::uint32_t>;
    using Uint64ID = internal::UintID<std::uint64_t>;
    using UintPtrID = internal::UintID<std::uintptr_t>;
    using UintMaxID = internal::UintID<std::uintmax_t>;
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

#endif // UINTID_H
