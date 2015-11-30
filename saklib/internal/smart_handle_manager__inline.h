#ifndef SAKLIB_INTERNAL_SMART_HANDLE_MANAGER__INLINE_H
#define SAKLIB_INTERNAL_SMART_HANDLE_MANAGER__INLINE_H

#ifndef SAKLIB_INTERNAL_SMART_HANDLE_MANAGER_H
#include "smart_handle_manager.h"
#endif

#ifndef SAKLIB_INTERNAL_SMART_HANDLE_H
#include "smart_handle.h"
#endif

//---------------------------------------------------------------------------
// Smart_Handle_Manager<T, F_Pre_Destructor>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T, typename FPD>
saklib::internal::Smart_Handle_Manager<T, FPD>::Smart_Handle_Manager(pre_destructor_type const& a_pre_destructor):
    m_storage{a_pre_destructor}
{
}

// Interface
//============================================================
template <typename T, typename FPD>
typename saklib::internal::Smart_Handle_Manager<T, FPD>::smart_handle_type saklib::internal::Smart_Handle_Manager<T, FPD>::make_null_handle()
{
    return smart_handle_type();
}

template <typename T, typename FPD>
typename saklib::internal::Smart_Handle_Manager<T, FPD>::smart_handle_type saklib::internal::Smart_Handle_Manager<T, FPD>::emplace_data(data_stored_type&& a_data)
{
    handle_type new_handle = m_storage.emplace_data(std::forward<data_stored_type>(a_data));
    return smart_handle_type(m_storage, new_handle);
}

template <typename T, typename FPD>
std::vector<typename saklib::internal::Smart_Handle_Manager<T, FPD>::smart_handle_type>
saklib::internal::Smart_Handle_Manager<T, FPD>::get_all_handles()
{
    std::vector<handle_type> l_dumb_handles{ m_storage.get_all_handles() };

    std::vector<smart_handle_type> l_result{};
    l_result.reserve(l_dumb_handles.size());

    for (auto const& dumb_handle : l_dumb_handles)
    {
        l_result.push_back(smart_handle_type(m_storage, dumb_handle));
    }

    return l_result;
}


template <typename T, typename FPD>
typename saklib::internal::Smart_Handle_Manager<T, FPD>::pre_destructor_type const& saklib::internal::Smart_Handle_Manager<T, FPD>::get_pre_destructor() const
{
    return m_storage.get_pre_destructor();
}

template <typename T, typename FPD>
void saklib::internal::Smart_Handle_Manager<T, FPD>::set_pre_destructor(pre_destructor_type const& a_pre_destructor)
{
    m_storage.set_pre_destructor(a_pre_destructor);
}


#endif // SAKLIB_INTERNAL_SMART_HANDLE_MANAGER__INLINE_H

