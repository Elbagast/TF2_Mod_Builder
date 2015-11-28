#ifndef SAKLIB_INTERNAL_SMART_HANDLE_MANAGER__INLINE_H
#define SAKLIB_INTERNAL_SMART_HANDLE_MANAGER__INLINE_H

#ifndef SAKLIB_INTERNAL_SMART_HANDLE_MANAGER_H
#include "smart_handle_manager.h"
#endif

#ifndef SAKLIB_INTERNAL_SMART_HANDLE_H
#include "smart_handle.h"
#endif


// Interface
//============================================================
template <typename T, typename... Args>
typename saklib::internal::Smart_Handle_Manager<T, Args...>::smart_handle_type saklib::internal::Smart_Handle_Manager<T, Args...>::make_null_handle()
{
    return smart_handle_type();
}

template <typename T, typename... Args>
typename saklib::internal::Smart_Handle_Manager<T, Args...>::smart_handle_type saklib::internal::Smart_Handle_Manager<T, Args...>::emplace_data(data_stored_type&& a_data)
{
    handle_type new_handle = m_storage.emplace_data(std::forward<data_stored_type>(a_data));
    return smart_handle_type(m_storage, new_handle);
}

#endif // SAKLIB_INTERNAL_SMART_HANDLE_MANAGER__INLINE_H

