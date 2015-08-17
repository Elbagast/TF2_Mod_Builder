#ifndef SMART_HANDLE_H
#define SMART_HANDLE_H

#include "null_handle.h"
#include <cassert>
//#include <iostream>


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
        using handle_type = typename Manager::handle_type; // going to assume this is a Handle<T> for now....
        using data_return_type = typename Manager::data_return_type;
        using data_const_return_type = typename Manager::data_const_return_type;

        using reference_count_type = typename Manager::reference_count_type;

        // Special 6
        //============================================================

        Smart_Handle() :
            mp_manager{ nullptr },
            m_handle{ null_handle() }
        {
        }

        Smart_Handle(manager_type* manager, handle_type const& handle) :
            Smart_Handle()
        {
            if (manager != nullptr)
            {
                mp_manager = manager;
                m_handle = handle;
                mp_manager->increment_reference_count(m_handle);
            }
        }

        explicit Smart_Handle(Null_Handle_Type const& /*null_handle*/) :
            Smart_Handle()
        {
        }

        explicit Smart_Handle(Null_Handle_Type && /*null_handle*/) :
            Smart_Handle()
        {
        }

        ~Smart_Handle()
        {
            //std::cout << "destructor: M=" << mp_manager << " H=" << m_handle.underlying_value() << " RC=" << reference_count() << std::endl;
            if (mp_manager != nullptr)
            {
                mp_manager->decrement_reference_count(m_handle);
            }
            //std::cout << "destructor end" << std::endl;
        }

        Smart_Handle(Smart_Handle const& other) :
            mp_manager{ other.mp_manager },
            m_handle{ (mp_manager != nullptr ? other.m_handle : handle_type(null_handle())) }
        {
            if (mp_manager != nullptr)
            {
                mp_manager->increment_reference_count(m_handle);
            }
        }
        Smart_Handle& operator=(Smart_Handle const& other)
        {
            if (&other != this)
            {
                manager_type* old_manager{ mp_manager };
                handle_type old_handle{ m_handle };

                mp_manager = other.mp_manager;
                m_handle = other.m_handle;

                if (mp_manager)
                {
                    mp_manager->increment_reference_count(m_handle); // this is a new holder of this value so increment
                }
                if (old_manager)
                {
                    old_manager->decrement_reference_count(old_handle); // decrement after as this may trigger destruction
                }
            }
            return *this;
        }


        Smart_Handle(Smart_Handle && other) :
            mp_manager{ std::move(other.mp_manager) },
            m_handle{ std::move(other.m_handle) }
        {
            // no reference count change
            other.mp_manager = nullptr;
            other.m_handle = null_handle();
        }
        Smart_Handle& operator=(Smart_Handle && other)
        {
            handle_type old_handle{ m_handle };
            m_handle = std::move(other.m_handle);
            if (mp_manager != nullptr)
            {
                mp_manager->decrement_reference_count(old_handle); // decrement after as this may trigger destruction
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
        data_return_type data()                             { return mp_manager->data(m_handle); } //hmm
        data_const_return_type cdata() const                { return mp_manager->cdata(m_handle); } //hmm

        bool is_null() const
        {
            return mp_manager == nullptr || m_handle == null_handle();
        }

        bool is_valid() const
        {
            return !is_null() && mp_manager->is_valid(m_handle);
        }

        handle_type const& handle() const
        {
            return m_handle;
        }

        reference_count_type reference_count() const
        {
            if (mp_manager)
            {
                return mp_manager->reference_count(m_handle);
            }
            else
            {
                return manager_type::reference_count_zero();
            }
        }

        manager_type* manager()
        {
            return mp_manager;
        }

        manager_type const* cmanager() const
        {
            return mp_manager;
        }

    private:
        Smart_Handle& nullify()
        {
            manager_type* old_manager{ mp_manager };
            handle_type old_handle{ m_handle };

            mp_manager = nullptr;
            m_handle = null_handle();

            if (old_manager)
            {
                old_manager->decrement_reference_count(old_handle); // decrement after as this may trigger destruction
            }
            return *this;
        }

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

