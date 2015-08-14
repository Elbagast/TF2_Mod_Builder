#ifndef SMART_HANDLE_H
#define SMART_HANDLE_H

#include "null_handle.h"
#include <cassert>

namespace datalib
{
    class Example_Manager
    {
    public:

    };

    /*
    Smart_Handle < Manager >
    ====================================================================================================
    */

    template <typename Manager>
    class Smart_Handle
    {
        friend typename Manager;
    public:
        // Typedefs
        //============================================================
        using manager_type = Manager;
        using handle_type = typename Manager::handle_type;
    private:
        using data_return_type = typename Manager::data_return_type;
        using data_const_return_type = typename Manager::data_const_return_type;

        using reference_count_type = typename Manager::reference_count_type;

        // Special 6
        //============================================================

        Smart_Handle(manager_type* manager, handle_type const& handle) :
            mp_manager{ manager },
            m_handle{ handle }
        {
            assert(mp_manager != nullptr);
            mp_manager->increment_reference_count(m_handle);
        }
    public:
        ~Smart_Handle()
        {
            mp_manager->decrement_reference_count(m_handle);
        }

        Smart_Handle(Smart_Handle const& other) :
            mp_manager{ other.mp_manager },
            m_handle{ other.m_handle }
        {
            mp_manager->increment_reference_count(m_handle);
        }
        Smart_Handle& operator=(Smart_Handle const& other)
        {
            // check for equivalence rather than self assignment
            if (m_handle != other.m_handle)
            {
                handle_type old_handle{ m_handle };
                m_handle = other.m_handle;
                mp_manager->increment_reference_count(m_handle); // this is a new holder of this value so increment
                mp_manager->decrement_reference_count(old_handle); // decrement after as this may trigger destruction
            }
            return *this;
        }

        Smart_Handle(Smart_Handle && other) :
            mp_manager{ std::move(other.mp_manager) },
            m_handle{ std::move(other.m_handle) }
        {
            // no reference count change
        }
        Smart_Handle& operator=(Smart_Handle && other)
        {
            handle_type old_handle{ m_handle };
            m_handle = std::move(other.m_handle);
            mp_manager->decrement_reference_count(old_handle); // decrement after as this may trigger destruction
            return *this;
        }
        // Interface
        //============================================================
        data_return_type data()                             { return mp_manager->data(m_handle); }
        data_const_return_type cdata() const                { return mp_manager->cdata(m_handle); }

        bool is_null() const                                { return !mp_manager || mp_manager->is_null(m_handle); }
        bool is_valid() const                               { return mp_manager && mp_manager->is_valid(m_handle); }
        handle_type const& handle() const                   { return m_handle; }
        reference_count_type reference_count() const        { return mp_manager->reference_count(m_handle); }

        manager_type* manager()                             { return mp_manager; }
        manager_type const* cmanager() const                { return mp_manager; }

    private:
        // Data Members
        //============================================================
        manager_type* mp_manager; // must be pointer to enable assignment
        handle_type m_handle;
    };

    // Comparison Operators
    //============================================================
    template <typename M>
    inline bool operator==(Smart_Handle<M> const& lhs, Smart_Handle<M> const& rhs)
    {
        return (lhs.cmanager() == rhs.cmanager()) && (lhs.handle() == rhs.handle());
    }
    template <typename M>
    inline bool operator!=(Smart_Handle<M> const& lhs, Smart_Handle<M> const& rhs)
    {
        return !operator==(lhs, rhs);
    }
    template <typename M>
    inline bool operator<(Smart_Handle<M> const& lhs, Smart_Handle<M> const& rhs)
    {
        return (lhs.cmanager() < rhs.cmanager()) && (lhs.handle() < rhs.handle());
    }
    template <typename M>
    inline bool operator>(Smart_Handle<M> const& lhs, Smart_Handle<M> const& rhs)
    {
        return operator==(rhs, lhs);
    }
    template <typename M>
    inline bool operator<=(Smart_Handle<M> const& lhs, Smart_Handle<M> const& rhs)
    {
        return !operator>(lhs, rhs);
    }
    template <typename M>
    inline bool operator>=(Smart_Handle<M> const& lhs, Smart_Handle<M> const& rhs)
    {
        return !operator<(lhs, rhs);
    }


    // Comparison Operators for compare to the null handle
    //============================================================
    template <typename M>
    inline bool operator==(Smart_Handle<M> const& lhs, Null_Handle_Type const&/*rhs*/)
    {
        // Can't directly compare to Null_Handle_Type as the Smart_Handle<M>handle_type might not be
        // a Handle<T> class, so we defer this operation to back to the manager.
        return lhs.is_null();
    }
    template <typename M>
    inline bool operator!=(Smart_Handle<M> const& lhs, Null_Handle_Type const& rhs)
    {
        return !operator==(lhs, rhs);
    }

    template <typename M>
    inline bool operator==(Null_Handle_Type const& lhs, Smart_Handle<M> const& rhs)
    {
        return operator==(rhs, lhs);
    }
    template <typename M>
    inline bool operator!=(Null_Handle_Type const& lhs, Smart_Handle<M> const& rhs)
    {
        return !operator==(rhs, lhs);
    }

} // namespace datalib

#endif // SMART_HANDLE_H

