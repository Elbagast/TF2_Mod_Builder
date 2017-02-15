#ifndef UINTID_MANAGER_H
#define UINTID_MANAGER_H

#include "fwd_uintid_manager.h"
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
}

#endif // UINTID_MANAGER_H
