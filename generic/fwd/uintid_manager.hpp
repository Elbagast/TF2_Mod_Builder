#ifndef GENERIC_FWD_UINTID_MANAGER_HPP
#define GENERIC_FWD_UINTID_MANAGER_HPP

#include <cstdint>

namespace generic
{
    //---------------------------------------------------------------------------
    // generic::UintID_Manager<uint type>
    //---------------------------------------------------------------------------
    // Class for encapsulating the issue and retiring of UintID types while
    // maintaining a pool. It tracks what ids are active and collects the ids
    // that are revoked so they can be reused.

    namespace internal
    {
        template <typename T>
        class UintID_Manager;
    }

    using Uint8ID_Manager = internal::UintID_Manager<std::uint8_t>;
    using Uint16ID_Manager = internal::UintID_Manager<std::uint16_t>;
    using Uint32ID_Manager = internal::UintID_Manager<std::uint32_t>;
    using Uint64ID_Manager = internal::UintID_Manager<std::uint64_t>;
    using UintPtrID_Manager = internal::UintID_Manager<std::uintptr_t>;
    using UintMaxID_Manager = internal::UintID_Manager<std::uintmax_t>;
}

#endif // GENERIC_FWD_UINTID_MANAGER_HPP
