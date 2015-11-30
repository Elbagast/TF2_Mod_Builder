#ifndef SAKLIB_INTERNAL_SMART_HANDLE__INLINE_H
#define SAKLIB_INTERNAL_SMART_HANDLE__INLINE_H

#ifndef SAKLIB_INTERNAL_SMART_HANDLE_H
#include "smart_handle.h"
#endif

#ifndef SAKLIB_INTERNAL_SMART_HANDLE_MANAGER_H
#include "smart_handle_manager.h"
#endif

#ifndef SAKLIB_INTERNAL_HANDLE_H
#include "handle.h"
#endif

#ifndef INCLUDE_STD_CASSERT
#define INCLUDE_STD_CASSERT
#include <cassert>
#endif

// Special 6
//============================================================
template <typename S>
saklib::internal::Smart_Handle<S>::Smart_Handle(storage_type& ar_storage, handle_type const& a_handle) :
    m_reference_counter{&ar_storage, a_handle}
{
}

template <typename S>
saklib::internal::Smart_Handle<S>::Smart_Handle(Null_Handle_Type const& /*null_handle*/) :
    Smart_Handle()
{
}

template <typename S>
saklib::internal::Smart_Handle<S>::Smart_Handle(Null_Handle_Type && /*null_handle*/) :
    Smart_Handle()
{
}

template <typename S>
saklib::internal::Smart_Handle<S>::Smart_Handle() :
    m_reference_counter{}
{
}

template <typename S>
saklib::internal::Smart_Handle<S>::~Smart_Handle() = default;

template <typename S>
saklib::internal::Smart_Handle<S>::Smart_Handle(Smart_Handle const& other) = default;

template <typename S>
saklib::internal::Smart_Handle<S>& saklib::internal::Smart_Handle<S>::operator=(Smart_Handle const& other) = default;

template <typename S>
saklib::internal::Smart_Handle<S>::Smart_Handle(Smart_Handle && other) :
    m_reference_counter{ std::move(other.m_reference_counter) }
{
}

template <typename S>
saklib::internal::Smart_Handle<S>& saklib::internal::Smart_Handle<S>::operator=(Smart_Handle && other)
{
    if (&other != this)
    {
        m_reference_counter = std::move(other.m_reference_counter);
    }
    return *this;
}

// Interface
//============================================================
template <typename S>
typename saklib::internal::Smart_Handle<S>::data_return_type saklib::internal::Smart_Handle<S>::get_data()
{
    return get_manager()->get_data(cget_handle());
    //return mp_storage->get_data(m_handle);
}

template <typename S>
typename saklib::internal::Smart_Handle<S>::data_const_return_type saklib::internal::Smart_Handle<S>::cget_data() const
{
    return cget_manager()->cget_data(cget_handle());
    //return mp_storage->cget_data(m_handle);
}

template <typename S>
bool saklib::internal::Smart_Handle<S>::is_null() const
{
    return m_reference_counter.is_null();
    //return mp_storage == nullptr || m_handle == null_handle();
}

template <typename S>
bool saklib::internal::Smart_Handle<S>::is_valid() const
{
    return m_reference_counter.is_valid();
    //return !is_null() && mp_storage->is_valid(m_handle);
}

template <typename S>
typename saklib::internal::Smart_Handle<S>::handle_type saklib::internal::Smart_Handle<S>::cget_handle() const
{
    return m_reference_counter.cget_handle();
}

template <typename S>
saklib::internal::Handle_Value_Type saklib::internal::Smart_Handle<S>::cget_handle_value() const
{
    return cget_handle().get_value();
}

template <typename S>
typename saklib::internal::Smart_Handle<S>::reference_count_type saklib::internal::Smart_Handle<S>::cget_reference_count() const
{
    if (cget_manager())
    {
        return cget_manager()->get_reference_count(cget_handle());
    }
    else
    {
        return storage_type::reference_count_zero();
    }
}

template <typename S>
typename saklib::internal::Smart_Handle<S>::storage_type* saklib::internal::Smart_Handle<S>::get_manager()
{
    return m_reference_counter.get_manager();
}

template <typename S>
typename saklib::internal::Smart_Handle<S>::storage_type const* saklib::internal::Smart_Handle<S>::cget_manager() const
{
    return m_reference_counter.cget_manager();
}

template <typename S>
saklib::internal::Smart_Handle<S>& saklib::internal::Smart_Handle<S>::nullify()
{
    m_reference_counter = reference_counter_type();
    /*
    storage_type* old_manager{ mp_storage };
    handle_type old_handle{ m_handle };

    mp_storage = nullptr;
    m_handle = null_handle();

    if (old_manager)
    {
        old_manager->decrement_reference_count(old_handle); // decrement after as this may trigger destruction
    }*/
    return *this;
}

// Comparison Operators
//============================================================
template <typename S>
bool saklib::internal::operator==(Smart_Handle<S> const& lhs, Smart_Handle<S> const& rhs)
{
    return (lhs.cget_manager() == rhs.cget_manager()) && (lhs.cget_handle() == rhs.cget_handle());
}
template <typename S>
bool saklib::internal::operator!=(Smart_Handle<S> const& lhs, Smart_Handle<S> const& rhs)
{
    return !operator==(lhs, rhs);
}
template <typename S>
bool saklib::internal::operator<(Smart_Handle<S> const& lhs, Smart_Handle<S> const& rhs)
{
    return (lhs.cget_manager() < rhs.cget_manager()) && (lhs.cget_handle() < rhs.cget_handle());
}
template <typename S>
bool saklib::internal::operator>(Smart_Handle<S> const& lhs, Smart_Handle<S> const& rhs)
{
    return operator==(rhs, lhs);
}
template <typename S>
bool saklib::internal::operator<=(Smart_Handle<S> const& lhs, Smart_Handle<S> const& rhs)
{
    return !operator>(lhs, rhs);
}
template <typename S>
bool saklib::internal::operator>=(Smart_Handle<S> const& lhs, Smart_Handle<S> const& rhs)
{
    return !operator<(lhs, rhs);
}

/*
// Comparison Operators for compare to the dumb handle
//============================================================
template <typename S>
bool saklib::internal::operator==(Smart_Handle<S> const& lhs, typename Smart_Handle<S>::handle_type const& rhs)
{
    return lhs.handle() == rhs;
}
template <typename S>
bool saklib::internal::operator!=(Smart_Handle<S> const& lhs, typename Smart_Handle<S>::handle_type const& rhs)
{
    return !operator==(lhs, rhs);
}

template <typename S>
bool saklib::internal::operator==(typename Smart_Handle<S>::handle_type const& lhs, Smart_Handle<S> const& rhs)
{
    return operator==(rhs, lhs);
}
template <typename S>
bool saklib::internal::operator!=(typename Smart_Handle<S>::handle_type const& lhs, Smart_Handle<S> const& rhs)
{
    return !operator==(rhs, lhs);
}
*/

// Comparison Operators for compare to the null handle
//============================================================
template <typename S>
bool saklib::internal::operator==(Smart_Handle<S> const& lhs, Null_Handle_Type const&/*rhs*/)
{
    return lhs.is_null();
}
template <typename S>
bool saklib::internal::operator!=(Smart_Handle<S> const& lhs, Null_Handle_Type const& rhs)
{
    return !operator==(lhs, rhs);
}

template <typename S>
bool saklib::internal::operator==(Null_Handle_Type const& lhs, Smart_Handle<S> const& rhs)
{
    return operator==(rhs, lhs);
}
template <typename S>
bool saklib::internal::operator!=(Null_Handle_Type const& lhs, Smart_Handle<S> const& rhs)
{
    return !operator==(rhs, lhs);
}


#endif // SAKLIB_INTERNAL_SMART_HANDLE__INLINE_H

