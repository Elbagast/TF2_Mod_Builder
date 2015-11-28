#ifndef SAKLIB_INTERNAL_HANDLE_FACTORY__INLINE_H
#define SAKLIB_INTERNAL_HANDLE_FACTORY__INLINE_H

#ifndef SAKLIB_INTERNAL_HANDLE_FACTORY_H
#include "handle_factory.h"
#endif

#include <cassert>
#include <numeric>

//============================================================
//template <typename T>
//class Handle_Factory;
//============================================================

// Special 6
//============================================================
template <typename T>
saklib::internal::Handle_Factory<T>::Handle_Factory() :
    m_revoked_handles{},
    m_next_value{null_handle_value()}
{}

// Interface
//============================================================
template <typename T>
typename saklib::internal::Handle_Factory<T>::handle_type saklib::internal::Handle_Factory<T>::make_null_handle()
{
    return handle_type();
}

template <typename T>
typename saklib::internal::Handle_Factory<T>::handle_type saklib::internal::Handle_Factory<T>::make_new_handle()
{
    handle_type new_handle{};
    if (m_revoked_handles.empty())
    {
        assert(m_next_value != std::numeric_limits<Handle_Value_Type>::max());
        new_handle = handle_type{ ++m_next_value };
    }
    else
    {
        new_handle = m_revoked_handles.top();
        m_revoked_handles.pop();
    }
    return new_handle;
}

template <typename T>
void saklib::internal::Handle_Factory<T>::revoke_handle(handle_type const& handle)
{
    if (handle != null_handle())
    {
        m_revoked_handles.push(handle);
    }
}


//============================================================
//template <typename T>
//class Sequential_Handle_Factory;
//============================================================

//Special 6
//============================================================
template <typename T>
saklib::internal::Sequential_Handle_Factory<T>::Sequential_Handle_Factory() :
    m_next_value{null_handle_value()}
{}

// Interface
//============================================================
template <typename T>
typename saklib::internal::Sequential_Handle_Factory<T>::handle_type saklib::internal::Sequential_Handle_Factory<T>::make_null_handle()
{
    return handle_type();
}

template <typename T>
typename saklib::internal::Sequential_Handle_Factory<T>::handle_type saklib::internal::Sequential_Handle_Factory<T>::make_new_handle()
{
    assert(m_next_value != std::numeric_limits<Handle_Value_Type>::max());
    return handle_type{ ++m_next_value };
}

template <typename T>
// constexpr ?
void saklib::internal::Sequential_Handle_Factory<T>::revoke_handle(handle_type const& /*handle*/)
{
    // Hey look its nothing.
}

#endif // SAKLIB_INTERNAL_HANDLE_FACTORY__INLINE_H

