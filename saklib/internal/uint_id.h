#ifndef SAKLIB_INTERNAL_UINT_ID_H
#define SAKLIB_INTERNAL_UINT_ID_H

#ifndef SAKLIB_INTERNAL_UINT_ID__FWD_H
#include "uint_id__fwd.h"
#endif

#ifndef INCLUDE_STD_QUEUE
#define INCLUDE_STD_QUEUE
#include <queue>
#endif

#ifndef INCLUDE_STD_FUNCTIONAL
#define INCLUDE_STD_FUNCTIONAL
#include <functional>
#endif


namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Unsigned_Integer_ID<T>
        //---------------------------------------------------------------------------

        template <typename T>
        class Unsigned_Integer_ID
        {
            // static_assert T is unsinged int?
        public:
            // Typedefs
            //============================================================
            using uint_type = T;

            // Special 6
            //============================================================
            Unsigned_Integer_ID();
            explicit Unsigned_Integer_ID(uint_type a_value);
            ~Unsigned_Integer_ID();

            Unsigned_Integer_ID(Unsigned_Integer_ID const& a_other);
            Unsigned_Integer_ID& operator=(Unsigned_Integer_ID const& a_other);

            Unsigned_Integer_ID(Unsigned_Integer_ID && a_other);
            Unsigned_Integer_ID& operator=(Unsigned_Integer_ID && a_other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            uint_type get_value() const;

            explicit operator bool() const;

            static uint_type get_null_value();

        private:
            // Data Members
            //============================================================
            uint_type m_value;
        };

        // Comparison Operators
        //============================================================
        template <typename T>
        bool operator==(Unsigned_Integer_ID<T> lhs, Unsigned_Integer_ID<T> rhs);
        template <typename T>
        bool operator!=(Unsigned_Integer_ID<T> lhs, Unsigned_Integer_ID<T> rhs);
        template <typename T>
        bool operator<(Unsigned_Integer_ID<T> lhs, Unsigned_Integer_ID<T> rhs);
        template <typename T>
        bool operator>(Unsigned_Integer_ID<T> lhs, Unsigned_Integer_ID<T> rhs);
        template <typename T>
        bool operator<=(Unsigned_Integer_ID<T> lhs, Unsigned_Integer_ID<T> rhs);
        template <typename T>
        bool operator>=(Unsigned_Integer_ID<T> lhs, Unsigned_Integer_ID<T> rhs);


        //---------------------------------------------------------------------------
        // Unsigned_Integer_ID_Factory<T>
        //---------------------------------------------------------------------------

        template <typename T>
        class Unsigned_Integer_ID_Factory
        {
        public:
            // Typedefs
            //============================================================
            using uint_type = T;
            using id_type = Unsigned_Integer_ID<T>;

            // Special 6
            //============================================================
            Unsigned_Integer_ID_Factory();

            // Interface
            //============================================================
            static id_type make_null_id();

            id_type issue_id();

            void revoke_id(id_type a_id);

        private:
            // Data Members
            //============================================================
            // The queue will store the handle with the lowest value at the top
            using queue_type = std::priority_queue<id_type, std::vector<id_type>, std::greater<id_type>>;

            queue_type m_revoked_handles;
            uint_type m_next_value;
        };

    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_UINT_ID__INLINE_H
#include "uint_id__inline.h"
#endif

#endif // SAKLIB_INTERNAL_UINT_ID_H

