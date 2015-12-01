#ifndef SAKLIB_INTERNAL_SMART_HANDLE_MANAGER_H
#define SAKLIB_INTERNAL_SMART_HANDLE_MANAGER_H


#ifndef SAKLIB_INTERNAL_SMART_HANDLE_MANAGER__FWD_H
#include "smart_handle_manager__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_SMART_HANDLE__FWD_H
#include "smart_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_HANDLE__FWD_H
#include "handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE_H
#include "reference_counted_storage.h"
#endif

namespace saklib
{
    namespace internal
    {
        template <typename T, typename... Args>
        class Smart_Handle_Manager
        {
        public:
            // Typedefs
            //============================================================
            using storage_type = Reference_Counted_Storage<T>;

            using data_type = typename storage_type::data_type;
            using handle_type = typename storage_type::handle_type;

            using data_stored_type = typename storage_type::data_stored_type;
            using data_return_type = typename storage_type::data_return_type;
            using data_const_return_type = typename storage_type::data_const_return_type;
            using reference_count_type = typename storage_type::reference_count_type;

            using smart_handle_type = typename Smart_Handle < storage_type >;

            // Interface
            //============================================================
            smart_handle_type make_null_handle();

            smart_handle_type emplace_data(data_stored_type&& a_data);

        private:
            storage_type m_storage;
        };
    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_SMART_HANDLE_MANAGER__INLINE_H
#include "smart_handle_manager__inline.h"
#endif

#endif // SAKLIB_INTERNAL_SMART_HANDLE_MANAGER_H

