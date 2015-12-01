#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE__INLINE_H
#define SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE__INLINE_H

#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE_H
#include "reference_counted_storage.h"
#endif

#ifndef INCLUDE_STD_CASSERT
#define INCLUDE_STD_CASSERT
#include <cassert>
#endif


//---------------------------------------------------------------------------
// Reference_Counted_Storage<Args...>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename H, typename... Args>
saklib::internal::Reference_Counted_Storage<H, Args...>::Reference_Counted_Storage():
    m_map{},
    m_currently_erasing{false},
    m_erase_queue{}
{
}


// Interface
//============================================================
template <typename H, typename... Args>
bool saklib::internal::Reference_Counted_Storage<H, Args...>::has_data(handle_type const& a_handle) const
{
    return m_map.find(a_handle) != m_map.cend();
}

template <typename H, typename... Args>
std::size_t saklib::internal::Reference_Counted_Storage<H, Args...>::data_types_count()
{
    return std::tuple_size<data_tuple_type>::tuple_size;
}

template <typename H, typename... Args>
template <std::size_t N>
typename saklib::internal::Reference_Counted_Storage<H, Args...>::Data<N>::return_type
saklib::internal::Reference_Counted_Storage<H, Args...>::get_data(handle_type const& a_handle)
{
    auto found_iterator = m_map.find(a_handle);
    if (found_iterator != m_map.end())
    {
        return get_iterator_data<N>(found_iterator);
    }
    else
    {
        return Data<N>::storage_traits_type::get_data_fail();
    }
}

template <typename H, typename... Args>
template <std::size_t N>
typename saklib::internal::Reference_Counted_Storage<H, Args...>::Data<N>::const_return_type
saklib::internal::Reference_Counted_Storage<H, Args...>::cget_data(handle_type const& a_handle) const
{
    auto found_iterator = m_map.find(a_handle);
    if (found_iterator != m_map.cend())
    {
        return cget_iterator_data<N>(found_iterator);
    }
    else
    {
        return Data<N>::storage_traits_type::cget_data_fail();
    }
}

template <typename H, typename... Args>
std::size_t saklib::internal::Reference_Counted_Storage<H, Args...>::cget_reference_count(handle_type const& a_handle) const
{
    auto found_iterator = m_map.find(a_handle);
    if (found_iterator != m_map.end())
    {
        return cget_iterator_reference_count(found_iterator);
    }
    else
    {
        return 0;
    }
}

template <typename H, typename... Args>
void saklib::internal::Reference_Counted_Storage<H, Args...>::increment_reference_count(handle_type const& a_handle)
{
    auto found_iterator = m_map.find(a_handle);
    if (found_iterator != m_map.end())
    {
        get_iterator_reference_count(found_iterator) += 1;
    }
}

template <typename H, typename... Args>
void saklib::internal::Reference_Counted_Storage<H, Args...>::decrement_reference_count(handle_type const& a_handle)
{
    auto found_iterator = m_map.find(a_handle);
    if (found_iterator != m_map.end())
    {
        if (cget_iterator_reference_count(found_iterator) != reference_count_zero())
        {
            get_iterator_reference_count(found_iterator) -= 1;
        }
        if (cget_iterator_reference_count(found_iterator) == reference_count_zero())
        {
            // We will now destroy this handle, but we might be calling this function again when we do
            // which needs care because we cannot call std::map::erase from inside an incomplete erase
            // call. That means we use a a queue and lock access to it.

            // Add the handle to the erase queue. The data wil be destroyed before this function returns.
            m_erase_queue.push(a_handle);

            // while
            // a std::map::erase is currently not in progress
            // and the erase queue has items (it may grow during this loop)
            while(!m_currently_erasing && !m_erase_queue.empty())
            {
                // lock erasing - subsequent decrement_reference_count calls that result in the
                // destruction of handles will not enter this block.
                m_currently_erasing = true;

                // call the pre_destructor on this value
                //m_pre_destructor(get_iterator_data(m_map.find(m_erase_queue.top())));
                signal_destruction_start(a_handle);
                // Destroy the data for this handle.
                m_map.erase(m_erase_queue.top());
                // Then revoke the handle
                signal_destruction_end(a_handle);
                // and remove that handle from the queue
                m_erase_queue.pop();
                // unlock erasing
                m_currently_erasing = false;
            }
        }
    }
}

template <typename H, typename... Args>
std::size_t saklib::internal::Reference_Counted_Storage<H, Args...>::reference_count_max()
{
    return std::numeric_limits<std::size_t>::max();
}

template <typename H, typename... Args>
std::size_t saklib::internal::Reference_Counted_Storage<H, Args...>::reference_count_zero()
{
    return 0;
}



// Emplace the given data using the given handle, return true if succeeded. The handle
// supplied must not already be in use (i.e. has_data(a_handle) == false) and it is not
// this object's responsibility to ensure that.
template <typename H, typename... Args>
typename saklib::internal::Reference_Counted_Storage<H, Args...>::reference_counter_type
saklib::internal::Reference_Counted_Storage<H, Args...>::emplace_data(handle_type const& a_handle, typename Storage_Traits<Args>::stored_type&&... a_data)
{
    if (has_data(a_handle))
    {
        return reference_counter_type();
    }
    else
    {
        m_map.emplace(a_handle, std::make_pair(0, std::make_tuple(std::forward<Args>(a_data)...)));
        signal_new_data(a_handle);
        return reference_counter_type(*this, a_handle);
    }
}

template <typename H, typename... Args>
typename saklib::internal::Reference_Counted_Storage<H, Args...>::reference_counter_type
saklib::internal::Reference_Counted_Storage<H, Args...>::emplace_data_tuple(handle_type const& a_handle, stored_tuple_type&& a_tuple)
{
    if (has_data(a_handle))
    {
        return reference_counter_type();
    }
    else
    {
        m_map.emplace(a_handle, std::make_pair(0, std::move(a_tuple)));
        signal_new_data(a_handle);
        return reference_counter_type(*this, a_handle);
    }
}

template <typename H, typename... Args>
typename saklib::internal::Reference_Counted_Storage<H, Args...>::reference_counter_type
saklib::internal::Reference_Counted_Storage<H, Args...>::make_handle(handle_type const& a_handle)
{
    if (has_data(a_handle))
    {
        return reference_counter_type(*this, a_handle);
    }
    else
    {
        return reference_counter_type();
    }
}

template <typename H, typename... Args>
std::vector<typename saklib::internal::Reference_Counted_Storage<H, Args...>::handle_type>
saklib::internal::Reference_Counted_Storage<H, Args...>::cget_all_handles() const
{
    std::vector<handle_type> l_result{};
    l_result.reserve(m_map.size());
    for (auto const& pair : m_map)
    {
        l_result.push_back(pair.first);
    }
    return l_result;
}



template <typename H, typename... Args>
void saklib::internal::Reference_Counted_Storage<H, Args...>::signal_new_data(handle_type const& /*a_handle*/)
{
    // dummy right now
}

template <typename H, typename... Args>
void saklib::internal::Reference_Counted_Storage<H, Args...>::signal_destruction_start(handle_type const& /*a_handle*/)
{
    // dummy right now
}

template <typename H, typename... Args>
void saklib::internal::Reference_Counted_Storage<H, Args...>::signal_destruction_end(handle_type const& /*a_handle*/)
{
    // dummy right now
}

template <typename H, typename... Args>
std::size_t& saklib::internal::Reference_Counted_Storage<H, Args...>::get_iterator_reference_count(typename map_type::iterator a_iterator)
{
    // iterator to pair<handle, pair<size_t, tuple>>
    // want size_t
    return a_iterator->second.first;
}

template <typename H, typename... Args>
std::size_t saklib::internal::Reference_Counted_Storage<H, Args...>::cget_iterator_reference_count(typename map_type::const_iterator a_iterator) const
{
    return a_iterator->second.first;
}

template <typename H, typename... Args>
template <std::size_t N>
typename saklib::internal::Reference_Counted_Storage<H, Args...>::Data<N>::return_type
saklib::internal::Reference_Counted_Storage<H, Args...>::get_iterator_data(typename map_type::iterator a_iterator)
{
    // iterator to pair<handle, pair<size_t, tuple>>
    // want tuple.N
    return std::get<N>(a_iterator->second.second);
}

template <typename H, typename... Args>
template <std::size_t N>
typename saklib::internal::Reference_Counted_Storage<H, Args...>::Data<N>::const_return_type
saklib::internal::Reference_Counted_Storage<H, Args...>::cget_iterator_data(typename map_type::const_iterator a_iterator) const
{
    return std::get<N>(a_iterator->second.second);
}


#endif // SAKLIB_INTERNAL_REFERENCE_COUNTED_STORAGE__INLINE_H

