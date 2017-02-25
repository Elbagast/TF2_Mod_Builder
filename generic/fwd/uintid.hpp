#ifndef GENERIC_FWD_UINTID_HPP
#define GENERIC_FWD_UINTID_HPP

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
        class UintID;
    }

    using Uint8ID = internal::UintID<std::uint8_t>;
    using Uint16ID = internal::UintID<std::uint16_t>;
    using Uint32ID = internal::UintID<std::uint32_t>;
    using Uint64ID = internal::UintID<std::uint64_t>;
    using UintPtrID = internal::UintID<std::uintptr_t>;
    using UintMaxID = internal::UintID<std::uintmax_t>;
}

#endif // GENERIC_FWD_UINTID_HPP
