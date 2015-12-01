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

#include <cassert>

// Special 6
//============================================================
template <typename S>
saklib::internal::Smart_Handle<S>::Smart_Handle(storage_type& ar_storage, handle_type const& a_handle) :
    mp_storage{ &ar_storage },
    m_handle{ a_handle }
{
    mp_storage->increment_reference_count(m_handle);
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
    mp_storage{ nullptr },
    m_handle{ null_handle() }
{
}

template <typename S>
saklib::internal::Smart_Handle<S>::~Smart_Handle()
{
    if (mp_storage != nullptr)
    {
        mp_storage->decrement_reference_count(m_handle);
    }
}

template <typename S>
saklib::internal::Smart_Handle<S>::Smart_Handle(Smart_Handle const& other) :
    mp_storage{ other.mp_storage },
    m_handle{ (mp_storage != nullptr ? other.m_handle : handle_type(null_handle())) }
{
    if (mp_storage != nullptr)
    {
        mp_storage->increment_reference_count(m_handle);
    }
}

template <typename S>
saklib::internal::Smart_Handle<S>& saklib::internal::Smart_Handle<S>::operator=(Smart_Handle const& other)
{
    if (&other != this)
    {
        storage_type* old_manager{ mp_storage };
        handle_type old_handle{ m_handle };

        mp_storage = other.mp_storage;
        m_handle = other.m_handle;

        if (mp_storage)
        {
            mp_storage->increment_reference_count(m_handle); // this is a new holder of this value so increment
        }
        if (old_manager)
        {
            old_manager->decrement_reference_count(old_handle); // decrement after as this may trigger destruction
        }
    }
    return *this;
}

template <typename S>
saklib::internal::Smart_Handle<S>::Smart_Handle(Smart_Handle && other) :
    mp_storage{ std::move(other.mp_storage) },
    m_handle{ std::move(other.m_handle) }
{
    // no reference count change
    other.mp_storage = nullptr;
    other.m_handle = null_handle();
}

template <typename S>
saklib::internal::Smart_Handle<S>& saklib::internal::Smart_Handle<S>::operator=(Smart_Handle && other)
{
    storage_type* old_manager{ mp_storage };
    handle_type old_handle{ m_handle };

    mp_storage = std::move(other.mp_storage);
    m_handle = std::move(other.m_handle);

    other.mp_storage = nullptr;
    other.m_handle = null_handle();

    if (old_manager != nullptr)
    {
        old_manager->decrement_reference_count(old_handle); // decrement after as this may trigger destruction
    }
    return *this;
}

/*
Smart_Handle& operator=(Null_Handle_Type const&)
{
    return nullify();
}
Smart_Handle& operator=(Null_Handle_Type &&)
{
    return nullify();
}
*/
// Interface
//============================================================
template <typename S>
typename saklib::internal::Smart_Handle<S>::data_return_type saklib::internal::Smart_Handle<S>::get_data()
{
    return mp_storage->get_data(m_handle);
}

template <typename S>
typename saklib::internal::Smart_Handle<S>::data_const_return_type saklib::internal::Smart_Handle<S>::cget_data() const
{
    return mp_storage->cget_data(m_handle);
}

template <typename S>
bool saklib::internal::Smart_Handle<S>::is_null() const
{
    return mp_storage == nullptr || m_handle == null_handle();
}

template <typename S>
bool saklib::internal::Smart_Handle<S>::is_valid() const
{
    return !is_null() && mp_storage->is_valid(m_handle);
}

template <typename S>
typename saklib::internal::Smart_Handle<S>::handle_type saklib::internal::Smart_Handle<S>::get_handle() const
{
    return m_handle;
}

template <typename S>
saklib::internal::Handle_Value_Type saklib::internal::Smart_Handle<S>::get_handle_value() const
{
    return m_handle.get_value();
}

template <typename S>
typename saklib::internal::Smart_Handle<S>::reference_count_type saklib::internal::Smart_Handle<S>::get_reference_count() const
{
    if (mp_storage)
    {
        return mp_storage->get_reference_count(m_handle);
    }
    else
    {
        return storage_type::reference_count_zero();
    }
}

template <typename S>
template <std::size_t I>
typename std::tuple_element<I, typename saklib::internal::Smart_Handle<S>::storage_type::tuple_type >::type const&
saklib::internal::Smart_Handle<S>::get_extra_property() const
{
    return mp_storage->get_extra_property<I>(m_handle);
}

template <typename S>
template <std::size_t I>
void saklib::internal::Smart_Handle<S>::set_extra_property(typename std::tuple_element<I, typename saklib::internal::Smart_Handle<S>::storage_type::tuple_type >::type const& a_value)
{
    mp_storage->set_extra_property<I>(m_handle, a_value);
}

template <typename S>
typename saklib::internal::Smart_Handle<S>::storage_type* saklib::internal::Smart_Handle<S>::get_storage()
{
    return mp_storage;
}

template <typename S>
typename saklib::internal::Smart_Handle<S>::storage_type const* saklib::internal::Smart_Handle<S>::cget_storage() const
{
    return mp_storage;
}

template <typename S>
saklib::internal::Smart_Handle<S>& saklib::internal::Smart_Handle<S>::nullify()
{
    storage_type* old_manager{ mp_storage };
    handle_type old_handle{ m_handle };

    mp_storage = nullptr;
    m_handle = null_handle();

    if (old_manager)
    {
        old_manager->decrement_reference_count(old_handle); // decrement after as this may trigger destruction
    }
    return *this;
}

// Comparison Operators
//============================================================
template <typename S>
bool saklib::internal::operator==(Smart_Handle<S> const& lhs, Smart_Handle<S> const& rhs)
{
    return (lhs.cget_storage() == rhs.cget_storage()) && (lhs.get_handle() == rhs.get_handle());
}
template <typename S>
bool saklib::internal::operator!=(Smart_Handle<S> const& lhs, Smart_Handle<S> const& rhs)
{
    return !operator==(lhs, rhs);
}
template <typename S>
bool saklib::internal::operator<(Smart_Handle<S> const& lhs, Smart_Handle<S> const& rhs)
{
    return (lhs.cget_storage() < rhs.cget_storage()) && (lhs.get_handle() < rhs.get_handle());
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

