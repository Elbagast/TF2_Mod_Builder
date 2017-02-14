#ifndef UINTID_TRAITS_H
#define UINTID_TRAITS_H

#include "uintid.h"

namespace generic
{
    //---------------------------------------------------------------------------
    // generic::UintID_Traits<uint type>
    //---------------------------------------------------------------------------
    // Traits class to wrap a number of operations on UintID types and have them
    // in one place.

    namespace internal
    {
        template <typename T>
        class UintID_Traits
        {
        public:
            using uint_type = T;
            using id_type = UintID<T>;

            static id_type make_null_id() noexcept;
            static void assign(id_type& a_id, id_type const& a_other) noexcept;
            static bool less_than(id_type const& a_id, id_type const& a_other) noexcept;
            static bool equal(id_type const& a_id, id_type const& a_other) noexcept;
        };
    }
    using Uint8ID_Traits = internal::UintID_Traits<std::uint8_t>;
    using Uint16ID_Traits = internal::UintID_Traits<std::uint16_t>;
    using Uint32ID_Traits = internal::UintID_Traits<std::uint32_t>;
    using Uint64ID_Traits = internal::UintID_Traits<std::uint64_t>;
    using UintPtrID_Traits = internal::UintID_Traits<std::uintptr_t>;
    using UintMaxID_Traits = internal::UintID_Traits<std::uintmax_t>;
}

#endif // UINTID_TRAITS_H
