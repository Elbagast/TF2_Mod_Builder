#ifndef HANDLE_FACTORY_H
#define HANDLE_FACTORY_H

#include <cassert>
#include <numeric>
#include <queue>
#include <algorithm>

#include "handle.h"

namespace datalib
{
    template <typename T>
    class Handle_Factory
    {
    public:
        // Typedefs
        //============================================================
        using handle_type = Handle<T>;
        using data_type = typename handle_type::data_type;
        using underlying_type = typename handle_type::underlying_type;

        // Special 6
        //============================================================
        Handle_Factory() :
            m_revoked_handles{},
            m_next_value{null_handle_value()}
        {}

        // Interface
        //============================================================
        static handle_type make_null_handle()
        {
            return handle_type();
        }

        handle_type make_new_handle()
        {
            handle_type new_handle{};
            if (m_revoked_handles.empty())
            {
                assert(m_next_value != std::numeric_limits<underlying_type>::max());
                new_handle = handle_type{ ++m_next_value };
            }
            else
            {
                new_handle = m_revoked_handles.front();
                m_revoked_handles.pop();
            }
            return new_handle;
        }

        void revoke_handle(handle_type const& handle)
        {
            if (handle != null_handle())
            {
                m_revoked_handles.push(handle);
            }
        }

    private:
        // Data Members
        //============================================================
        std::queue<handle_type> m_revoked_handles;
        underlying_type m_next_value;
    };

    template <typename T>
    class Sequential_Handle_Factory
    {
    public:
        // Typedefs
        //============================================================
        using handle_type = Handle<T>;
        using data_type = typename handle_type::data_type;
        using underlying_type = typename handle_type::underlying_type;

        // Special 6
        //============================================================
        Sequential_Handle_Factory() :
            m_next_value{null_handle_value()}
        {}

        // Interface
        //============================================================
        static handle_type make_null_handle()
        {
            return handle_type();
        }

        handle_type make_new_handle()
        {
            assert(m_next_value != std::numeric_limits<underlying_type>::max());
            return handle_type{ ++m_next_value };
        }

        // constexpr ?
        static void revoke_handle(handle_type const& /*handle*/)
        {
            // Hey look its nothing.
        }

    private:
        // Data Members
        //============================================================
        underlying_type m_next_value;
    };
} // namespace datalib


#endif // HANDLE_FACTORY_H

