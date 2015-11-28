#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE__INLINE_H
#define SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE__INLINE_H

#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE_H
#include "reference_counted_storage.h"
#endif

#include <cassert>

template <typename T, typename FPD>
template <typename T_Again>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again>::data_return_type saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again>::get_data_fail()
{
    throw std::range_error("Invalid handle.");
}

template <typename T, typename FPD>
template <typename T_Again>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again>::data_const_return_type saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again>::cget_data_fail()
{
    throw std::range_error("Invalid handle.");
}

template <typename T, typename FPD>
template <typename T_Again>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again>::data_return_type saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again>::get_data_return_from_stored(data_stored_type& a_stored)
{
    return a_stored;
}

template <typename T, typename FPD>
template <typename T_Again>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again>::data_const_return_type saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again>::cget_data_return_from_stored(data_stored_type const& a_stored)
{
     return a_stored;
}


template <typename T, typename FPD>
template <typename T_Again>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again*>::data_return_type saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again*>::get_data_fail()
{
    return nullptr;
}

template <typename T, typename FPD>
template <typename T_Again>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again*>::data_const_return_type saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again*>::cget_data_fail()
{
    return nullptr;
}

template <typename T, typename FPD>
template <typename T_Again>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again*>::data_return_type saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again*>::get_data_return_from_stored(data_stored_type& a_stored)
{
    return a_stored.get();
}

template <typename T, typename FPD>
template <typename T_Again>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again*>::data_const_return_type saklib::internal::Reference_Counted_Storage<T, FPD>::Internal<T_Again*>::cget_data_return_from_stored(data_stored_type const& a_stored)
{
     return a_stored.get();
}


// Special 6
//============================================================
template <typename T, typename FPD>
saklib::internal::Reference_Counted_Storage<T, FPD>::Reference_Counted_Storage(pre_destructor_type const& a_pre_destructor):
    m_map(),
    m_handle_factory(),
    m_currently_erasing(false),
    m_erase_queue(),
    m_pre_destructor(a_pre_destructor)
{}

template <typename T, typename FPD>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::handle_type
saklib::internal::Reference_Counted_Storage<T, FPD>::make_null_handle() const
{
    return m_handle_factory.make_null_handle();
}

template <typename T, typename FPD>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::handle_type
saklib::internal::Reference_Counted_Storage<T, FPD>::emplace_data(data_stored_type&& a_data)
{
    auto l_handle = m_handle_factory.make_new_handle();
    assert(!has_data(l_handle));
    m_map.emplace(l_handle, tuple_type(std::forward<data_stored_type>(a_data), 0));
    return l_handle;
}

template <typename T, typename FPD>
bool saklib::internal::Reference_Counted_Storage<T, FPD>::is_null(handle_type const& a_handle) const
{
    return a_handle == null_handle();
}

template <typename T, typename FPD>
bool saklib::internal::Reference_Counted_Storage<T, FPD>::is_valid(handle_type const& a_handle) const
{
    return has_data(a_handle);
}

template <typename T, typename FPD>
bool saklib::internal::Reference_Counted_Storage<T, FPD>::has_data(handle_type const& a_handle) const
{
    return a_handle != null_handle() && m_map.find(a_handle) != m_map.cend();
}

template <typename T, typename FPD>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::data_return_type saklib::internal::Reference_Counted_Storage<T, FPD>::get_data(handle_type const& a_handle)
{
    auto found_iterator = m_map.find(a_handle);
    if (found_iterator != m_map.end())
    {
        return get_iterator_data(found_iterator);
    }
    return internal_type::get_data_fail();
}

template <typename T, typename FPD>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::data_const_return_type saklib::internal::Reference_Counted_Storage<T, FPD>::cget_data(handle_type const& a_handle) const
{
    auto found_iterator = m_map.find(a_handle);
    if (found_iterator != m_map.end())
    {
        return cget_iterator_data(found_iterator);
    }
    return internal_type::cget_data_fail();
}

template <typename T, typename FPD>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::reference_count_type saklib::internal::Reference_Counted_Storage<T, FPD>::get_reference_count(handle_type const& a_handle) const
{
    auto found_iterator = m_map.find(a_handle);
    if (found_iterator != m_map.end())
    {
        return cget_iterator_reference_count(found_iterator);
    }
    return 0;
}

template <typename T, typename FPD>
void saklib::internal::Reference_Counted_Storage<T, FPD>::increment_reference_count(handle_type const& a_handle)
{
    if (a_handle != null_handle())
    {
        auto found_iterator = m_map.find(a_handle);
        assert(found_iterator != m_map.end()); // must exist
        if (found_iterator != m_map.end())
        {
            assert(get_iterator_reference_count(found_iterator) != reference_count_max()); // must not be max when we get here...
            get_iterator_reference_count(found_iterator) += 1;
        }
    }
}

template <typename T, typename FPD>
void saklib::internal::Reference_Counted_Storage<T, FPD>::decrement_reference_count(handle_type const& a_handle)
{
    if (a_handle != null_handle())
    {
        auto found_iterator = m_map.find(a_handle);
        assert(found_iterator != m_map.end()); // must exist
        if (found_iterator != m_map.end())
        {
            assert(get_iterator_reference_count(found_iterator) != reference_count_zero()); // must not be zero when we get here...
            get_iterator_reference_count(found_iterator) -= 1;
            if (get_iterator_reference_count(found_iterator) == reference_count_zero())
            {
                // We will now destroy this handle, but we might be calling this function again when we do
                // which needs care because we cannot call std::map::erase from inside an incomplete erase
                // call. That means we use a a queue and lock access to it.

                // Add the handle to the erase queue. The data wil be destiyed before this function returns.
                m_erase_queue.push(a_handle);

                // while
                // a std::map::erase is currently not in progress
                // and the erase queue has items (it may grow during this loop)
                while(!m_currently_erasing && !m_erase_queue.empty())
                {
                    // lock erasing - subsequent decrement_reference_count calls that result in the
                    // destruction of handles will not entre this block.
                    m_currently_erasing = true;

                    // call the pre_destructor on this value
                    m_pre_destructor(get_iterator_data(m_map.find(m_erase_queue.top())));
                    // Destroy the data for this handle.
                    m_map.erase(m_erase_queue.top());
                    // Then revoke the handle
                    m_handle_factory.revoke_handle(m_erase_queue.top());
                    // and remove that handle from the queue
                    m_erase_queue.pop();
                    // unlock erasing
                    m_currently_erasing = false;
                }
            }
        }
    }
}

template <typename T, typename FPD>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::reference_count_type saklib::internal::Reference_Counted_Storage<T, FPD>::reference_count_max()
{
    return std::numeric_limits<reference_count_type>::max();
}

template <typename T, typename FPD>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::reference_count_type saklib::internal::Reference_Counted_Storage<T, FPD>::reference_count_zero()
{
    return 0;
}

template <typename T, typename FPD>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::pre_destructor_type const& saklib::internal::Reference_Counted_Storage<T, FPD>::get_pre_destructor() const
{
    return m_pre_destructor;
}

template <typename T, typename FPD>
void saklib::internal::Reference_Counted_Storage<T, FPD>::set_pre_destructor(pre_destructor_type const& a_pre_destructor)
{
    m_pre_destructor = a_pre_destructor;
}

template <typename T, typename FPD>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::data_return_type saklib::internal::Reference_Counted_Storage<T, FPD>::get_iterator_data(typename map_type::iterator a_iterator)
{
    return internal_type::get_data_return_from_stored(std::get<0>(a_iterator->second));
}

template <typename T, typename FPD>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::data_const_return_type saklib::internal::Reference_Counted_Storage<T, FPD>::cget_iterator_data(typename map_type::const_iterator a_iterator) const
{
    return internal_type::cget_data_return_from_stored(std::get<0>(a_iterator->second));
}

template <typename T, typename FPD>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::reference_count_type& saklib::internal::Reference_Counted_Storage<T, FPD>::get_iterator_reference_count(typename map_type::iterator a_iterator)
{
    return std::get<1>(a_iterator->second);
}

template <typename T, typename FPD>
typename saklib::internal::Reference_Counted_Storage<T, FPD>::reference_count_type const& saklib::internal::Reference_Counted_Storage<T, FPD>::cget_iterator_reference_count(typename map_type::const_iterator a_iterator) const
{
    return std::get<1>(a_iterator->second);
}




#endif // SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE__INLINE_H

