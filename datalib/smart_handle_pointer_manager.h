#ifndef SMART_HANDLE_POINTER_MANAGER_H
#define SMART_HANDLE_POINTER_MANAGER_H

#include "handle.h"
#include "handle_factory.h"
#include "smart_handle.h"
#include <cassert>
#include <map>
#include <memory>
#include <numeric>
#include <tuple>

namespace datalib
{
    template <typename T>
    class Smart_Handle_Pointer_Manager
    {
    public:
        // Typedefs
        //============================================================
        using data_type = T;
        using handle_type = Handle<data_type>;

        using data_stored_type = std::unique_ptr<data_type>;
        using data_return_type = data_type*;
        using data_const_return_type = data_type const*;

        using reference_count_type = std::size_t;

        using handle_factory_type = Handle_Factory<data_type>;

        using smart_handle_type = typename Smart_Handle < Smart_Handle_Pointer_Manager >;


        // Interface
        //============================================================
        smart_handle_type make_null_handle()
        {
            return smart_handle_type(this, m_id_factory.make_null_handle());
        }

        smart_handle_type emplace_data(data_stored_type&& data)
        {
            handle_type new_handle = m_id_factory.make_new_handle();
            m_map.emplace(new_handle, tuple_type(std::forward<data_stored_type>(data), 0));
            return smart_handle_type(this, new_handle);
        }

        bool is_null(handle_type const& handle) const
        {
            return handle == null_handle();
        }

        bool is_valid(handle_type const& handle) const
        {
            return has_data(handle);
        }

        bool has_data(handle_type const& handle) const
        {
            return (handle != null_handle()) && (m_map.find(handle) != m_map.cend());
        }

        data_return_type data(handle_type const& handle)
        {
            if (handle != null_handle())
            {
                auto found_iterator = m_map.find(handle);
                if (found_iterator != m_map.end())
                {
                    return iterator_data(found_iterator).get();
                }
            }
            return nullptr;
        }

        data_const_return_type cdata(handle_type const& handle) const
        {
            if (handle != null_handle())
            {
                auto found_iterator = m_map.find(handle);
                if (found_iterator != m_map.end())
                {
                    return citerator_data(found_iterator).get();
                }
            }
            return nullptr;
        }

        reference_count_type reference_count(handle_type const& handle) const
        {
            if (handle != null_handle())
            {
                auto found_iterator = m_map.find(handle);
                if (found_iterator != m_map.end())
                {
                    return citerator_reference_count(found_iterator);
                }
            }
            return std::numeric_limits<reference_count_type>::min();
        }

        void increment_reference_count(handle_type const& handle)
        {
            if (handle != null_handle())
            {
                auto found_iterator = m_map.find(handle);
                assert(found_iterator != m_map.end()); // must exist
                if (found_iterator != m_map.end())
                {
                    assert(iterator_reference_count(found_iterator) != std::numeric_limits<reference_count_type>::max()); // must not be max when we get here...
                    iterator_reference_count(found_iterator) += 1;
                }
            }
        }

        void decrement_reference_count(handle_type const& handle)
        {
            if (handle != null_handle())
            {
                auto found_iterator = m_map.find(handle);
                assert(found_iterator != m_map.end()); // must exist
                if (found_iterator != m_map.end())
                {
                    assert(iterator_reference_count(found_iterator) != std::numeric_limits<reference_count_type>::min()); // must not be zero when we get here...
                    iterator_reference_count(found_iterator) -= 1;
                    if (iterator_reference_count(found_iterator) == std::numeric_limits<reference_count_type>::min())
                    {
                        m_map.erase(handle);
                        m_id_factory.revoke_handle(handle);
                    }
                }
            }
        }

    private:
        // By using a tuple the manager can potentially be extended
        using tuple_type = std::tuple < data_stored_type, reference_count_type >;
        using map_type = std::map < handle_type, tuple_type >;


        data_stored_type& iterator_data(typename map_type::iterator iterator)
        {
            return std::get<0>(iterator->second);
        }

        data_stored_type const& citerator_data(typename map_type::const_iterator iterator) const
        {
            return std::get<0>(iterator->second);
        }

        reference_count_type& iterator_reference_count(typename map_type::iterator iterator)
        {
            return std::get<1>(iterator->second);
        }

        reference_count_type const& citerator_reference_count(typename map_type::const_iterator iterator) const
        {
            return std::get<1>(iterator->second);
        }

        map_type m_map;
        handle_factory_type m_id_factory;
    };

} // namespace datalib

#endif // SMART_HANDLE_POINTER_MANAGER_H

