#ifndef HANDLE_H
#define HANDLE_H

#include "null_handle.h"

namespace datalib
{
    template <typename T>
    class Handle
    {
    public:
        using underlying_type = Null_Handle_Type::underlying_type;
        using data_type = T;

        // Special 6
        //============================================================
        Handle():
            m_value{null_handle_value()}
        {}
        explicit Handle(Null_Handle_Type && /*handle*/):
            Handle()
        {}
        explicit Handle(underlying_type const& value):
            m_value{value}
        {}
        ~Handle() = default;

        Handle(Handle const& handle) = default;
        Handle& operator=(Handle const& handle) = default;
        Handle& operator=(Null_Handle_Type const& /*handle*/)
        {
            m_value = null_handle_value();
            return *this;
        }

        Handle(Handle && handle):
            m_value{std::move(handle.m_value)}
        {
            handle.m_value = null_handle_value();
        }
        Handle& operator=(Handle && handle)
        {
            m_value = std::move(handle.m_value);
            handle.m_value = null_handle_value();
            return *this;
        }

        // Interface
        //============================================================
        underlying_type const& underlying_value() const
        {
            return m_value;
        }

        explicit operator bool()
        {
            return m_value != null_handle_value();
        }

    private:
        // Data Members
        //============================================================
        underlying_type m_value;
    };

    // Comparison Operators
    //============================================================
    template <typename T>
    inline bool operator==(Handle<T> const& lhs, Handle<T> const& rhs)
    {
        return lhs.underlying_value() == rhs.underlying_value();
    }
    template <typename T>
    inline bool operator!=(Handle<T> const& lhs, Handle<T> const& rhs)
    {
        return !operator==(lhs, rhs);
    }
    template <typename T>
    inline bool operator<(Handle<T> const& lhs, Handle<T> const& rhs)
    {
        return lhs.underlying_value() < rhs.underlying_value();
    }
    template <typename T>
    inline bool operator>(Handle<T> const& lhs, Handle<T> const& rhs)
    {
        return operator==(rhs, lhs);
    }
    template <typename T>
    inline bool operator<=(Handle<T> const& lhs, Handle<T> const& rhs)
    {
        return !operator>(lhs, rhs);
    }
    template <typename T>
    inline bool operator>=(Handle<T> const& lhs, Handle<T> const& rhs)
    {
        return !operator<(lhs, rhs);
    }


    // Comparison Operators for compare to the null handle
    //============================================================
    template <typename T>
    inline bool operator==(Handle<T> const& lhs, Null_Handle_Type const&/*rhs*/)
    {
        return lhs.underlying_value() == Null_Handle_Type::value;
    }
    template <typename T>
    inline bool operator!=(Handle<T> const& lhs, Null_Handle_Type const& rhs)
    {
        return !operator==(lhs, rhs);
    }

    template <typename T>
    inline bool operator==(Null_Handle_Type const& lhs, Handle<T> const& rhs)
    {
        return operator==(rhs, lhs);
    }
    template <typename T>
    inline bool operator!=(Null_Handle_Type const& lhs, Handle<T> const& rhs)
    {
        return !operator==(rhs, lhs);
    }


} // namespace datalib


#endif // HANDLE_H

