#ifndef SAKLIB_INTERNAL_HANDLE_H
#define SAKLIB_INTERNAL_HANDLE_H

#ifndef SAKLIB_INTERNAL_HANDLE__FWD_H
#include "handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_NULL_HANDLE_H
#include "null_handle.h"
#endif

namespace saklib
{
    namespace internal
    {
        template <typename T>
        class Handle
        {
        public:
            using data_type = T;

            // Special 6
            //============================================================
            Handle();
            Handle(Null_Handle_Type && /*handle*/);
            explicit Handle(Handle_Value_Type a_value);
            ~Handle();

            Handle(Handle const& handle);
            Handle& operator=(Handle const& a_handle);

            Handle(Handle && handle);
            Handle& operator=(Handle && a_handle);

            // Interface
            //============================================================
            Handle_Value_Type get_value() const;

            explicit operator bool() const;

        private:
            // Data Members
            //============================================================
            Handle_Value_Type m_value;
        };

        // Comparison Operators
        //============================================================
        template <typename T>
        bool operator==(Handle<T> const& lhs, Handle<T> const& rhs);
        template <typename T>
        bool operator!=(Handle<T> const& lhs, Handle<T> const& rhs);
        template <typename T>
        bool operator<(Handle<T> const& lhs, Handle<T> const& rhs);
        template <typename T>
        bool operator>(Handle<T> const& lhs, Handle<T> const& rhs);
        template <typename T>
        bool operator<=(Handle<T> const& lhs, Handle<T> const& rhs);
        template <typename T>
        bool operator>=(Handle<T> const& lhs, Handle<T> const& rhs);


        // Comparison Operators for compare to the null handle
        //============================================================
        template <typename T>
        bool operator==(Handle<T> const& lhs, Null_Handle_Type const& rhs);
        template <typename T>
        bool operator!=(Handle<T> const& lhs, Null_Handle_Type const& rhs);
        template <typename T>
        bool operator==(Null_Handle_Type const& lhs, Handle<T> const& rhs);
        template <typename T>
        bool operator!=(Null_Handle_Type const& lhs, Handle<T> const& rhs);
    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_HANDLE__INLINE_H
#include "handle__inline.h"
#endif

#endif // SAKLIB_INTERNAL_HANDLE_H

