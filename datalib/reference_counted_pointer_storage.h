#ifndef REFERENCE_COUNTED_POINTER_STORAGE_H
#define REFERENCE_COUNTED_POINTER_STORAGE_H

#include "handle.h"
#include <map>
#include <memory>
#include <numeric>
#include <cassert>
#include <iostream>

namespace datalib
{
    template <typename T>
    class Reference_Counted_Pointer_Storage
    {
    public:
        // Typedefs
        //============================================================
        using data_type = T;
        using handle_type = Handle<T>;

        using data_stored_type = std::unique_ptr<data_type>;
        using data_return_type = data_type*;
        using data_const_return_type = data_type const*;
        using reference_count_type = std::size_t;

        // Special 6
        //============================================================

        // Interface
        //============================================================

        void emplace_data(handle_type const& handle, data_stored_type&& data)
        {
            if (handle != null_handle())
            {
                m_map.emplace(handle, tuple_type(std::forward<data_stored_type>(data), 0));
            }
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
            return handle != null_handle() && m_map.find(handle) != m_map.cend();
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
            auto found_iterator = m_map.find(handle);
            if (found_iterator != m_map.end())
            {
                return citerator_reference_count(found_iterator);
            }
            return 0;
        }

        void increment_reference_count(handle_type const& handle)
        {
            if (handle != null_handle())
            {
                auto found_iterator = m_map.find(handle);
                assert(found_iterator != m_map.end()); // must exist
                if (found_iterator != m_map.end())
                {
                    assert(iterator_reference_count(found_iterator) != reference_count_max()); // must not be max when we get here...
                    iterator_reference_count(found_iterator) += 1;
                }
            }
        }

        bool decrement_reference_count(handle_type const& handle)
        {
            if (handle != null_handle())
            {
                auto found_iterator = m_map.find(handle);
                assert(found_iterator != m_map.end()); // must exist
                if (found_iterator != m_map.end())
                {
                    std::cout << "handle found: " << handle.underlying_value() << std::endl;
                    assert(iterator_reference_count(found_iterator) != reference_count_zero()); // must not be zero when we get here...
                    iterator_reference_count(found_iterator) -= 1;

                    std::cout << "handle decremented: " << handle.underlying_value() << std::endl;
                    if (iterator_reference_count(found_iterator) == reference_count_zero())
                    {
                        std::cout << "handle erase: " << handle.underlying_value() << std::endl;
                        m_map.erase(handle);
                        std::cout << "handle erased: " << handle.underlying_value() << std::endl;
                        return true;
                    }
                }
            }
            return false;
        }

        static reference_count_type reference_count_max()
        {
            return std::numeric_limits<reference_count_type>::max();
        }

        static reference_count_type reference_count_zero()
        {
            return 0;
        }

    private:
        // By using a tuple the manager can potentially be extended
        using tuple_type = std::tuple < data_stored_type, reference_count_type >;
        using map_type = std::map < handle_type, tuple_type >;

        data_stored_type& iterator_data(typename map_type::iterator iterator)
        {
            assert(iterator != m_map.end());
            return std::get<0>(iterator->second);
        }

        data_stored_type const& citerator_data(typename map_type::const_iterator iterator) const
        {
            assert(iterator != m_map.end());
            return std::get<0>(iterator->second);
        }

        reference_count_type& iterator_reference_count(typename map_type::iterator iterator)
        {
            assert(iterator != m_map.end());
            return std::get<1>(iterator->second);
        }

        reference_count_type const& citerator_reference_count(typename map_type::const_iterator iterator) const
        {
            assert(iterator != m_map.end());
            return std::get<1>(iterator->second);
        }



        map_type m_map;
    };

} // namespace datalib

#endif // REFERENCE_COUNTED_POINTER_STORAGE_H

