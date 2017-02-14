#ifndef UINTID_MANAGER_H
#define UINTID_MANAGER_H

#include "uintid.h"
#include <deque>

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
        class UintID_Manager
        {
        public:
            using uint_type = T;
            using id_type = UintID<T>;

            UintID_Manager();

            static id_type make_null_id();
            id_type make_id();
            bool retire_id(id_type a_id);
            bool is_active(id_type a_id) const;

        private:
            uint_type m_next_id;
            std::deque<uint_type> m_retired_ids;
        };
    }

    using Uint8ID_Manager = internal::UintID_Manager<std::uint8_t>;
    using Uint16ID_Manager = internal::UintID_Manager<std::uint16_t>;
    using Uint32ID_Manager = internal::UintID_Manager<std::uint32_t>;
    using Uint64ID_Manager = internal::UintID_Manager<std::uint64_t>;
    using UintPtrID_Manager = internal::UintID_Manager<std::uintptr_t>;
    using UintMaxID_Manager = internal::UintID_Manager<std::uintmax_t>;
}

#endif // UINTID_MANAGER_H
