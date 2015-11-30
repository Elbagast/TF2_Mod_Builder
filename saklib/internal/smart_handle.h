#ifndef SAKLIB_INTERNAL_SMART_HANDLE_H
#define SAKLIB_INTERNAL_SMART_HANDLE_H

#ifndef SAKLIB_INTERNAL_SMART_HANDLE__FWD_H
#include "smart_handle__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_SMART_HANDLE_MANAGER__FWD_H
#include "smart_handle_manager__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_NULL_HANDLE_H
#include "null_handle.h"
#endif

#include "reference_counter.h"
#include <boost/bind.hpp>

namespace saklib
{
    namespace internal
    {

        //---------------------------------------------------------------------------
        // Smart_Handle<Storage>
        //---------------------------------------------------------------------------

        template <typename Storage>
        class Smart_Handle
        {
        public:
            // Typedefs
            //============================================================
            using storage_type = Storage;
            using handle_type = typename Storage::handle_type; // going to assume this is a Handle<T> for now....
            using data_return_type = typename Storage::data_return_type;
            using data_const_return_type = typename Storage::data_const_return_type;

            using reference_count_type = typename Storage::reference_count_type;

            // Special 6
            //============================================================
            // Only a manager can make these that have data.
            Smart_Handle(storage_type& a_storage, handle_type const& a_handle);

            explicit Smart_Handle(Null_Handle_Type const& null_handle);

            explicit Smart_Handle(Null_Handle_Type && null_handle);

            Smart_Handle();

            ~Smart_Handle();

            Smart_Handle(Smart_Handle const& other);
            Smart_Handle& operator=(Smart_Handle const& other);

            Smart_Handle(Smart_Handle && other);
            Smart_Handle& operator=(Smart_Handle && other);

            // Interface
            //============================================================
            data_return_type get_data();
            data_const_return_type cget_data() const;

            bool is_null() const;

            bool is_valid() const;

            handle_type cget_handle() const;

            Handle_Value_Type cget_handle_value() const;

            reference_count_type cget_reference_count() const;

            storage_type* get_manager();

            storage_type const* cget_manager() const;

        private:
            Smart_Handle& nullify();

            // Data Members
            //============================================================
            //storage_type* mp_storage; // must be pointer to enable assignment
            //handle_type m_handle;
            using reference_counter_type = Member_Reference_Counter<storage_type, handle_type, &storage_type::increment_reference_count, &storage_type::decrement_reference_count>;

            reference_counter_type m_reference_counter;
        };

        // Comparison Operators
        //============================================================
        template <typename M>
        inline bool operator==(Smart_Handle<M> const& lhs, Smart_Handle<M> const& rhs);
        template <typename M>
        inline bool operator!=(Smart_Handle<M> const& lhs, Smart_Handle<M> const& rhs);
        template <typename M>
        inline bool operator<(Smart_Handle<M> const& lhs, Smart_Handle<M> const& rhs);
        template <typename M>
        inline bool operator>(Smart_Handle<M> const& lhs, Smart_Handle<M> const& rhs);
        template <typename M>
        inline bool operator<=(Smart_Handle<M> const& lhs, Smart_Handle<M> const& rhs);
        template <typename M>
        inline bool operator>=(Smart_Handle<M> const& lhs, Smart_Handle<M> const& rhs);

        /*
        // Comparison Operators for compare to the dumb handle
        //============================================================
        template <typename M>
        inline bool operator==(Smart_Handle<M> const& lhs, typename Smart_Handle<M>::handle_type const& rhs);
        template <typename M>
        inline bool operator!=(Smart_Handle<M> const& lhs, typename Smart_Handle<M>::handle_type const& rhs);

        template <typename M>
        inline bool operator==(typename Smart_Handle<M>::handle_type const& lhs, Smart_Handle<M> const& rhs);
        template <typename M>
        inline bool operator!=(typename Smart_Handle<M>::handle_type const& lhs, Smart_Handle<M> const& rhs);
        */

        // Comparison Operators for compare to the null handle
        //============================================================
        template <typename M>
        inline bool operator==(Smart_Handle<M> const& lhs, Null_Handle_Type const& rhs);
        template <typename M>
        inline bool operator!=(Smart_Handle<M> const& lhs, Null_Handle_Type const& rhs);

        template <typename M>
        inline bool operator==(Null_Handle_Type const& lhs, Smart_Handle<M> const& rhs);
        template <typename M>
        inline bool operator!=(Null_Handle_Type const& lhs, Smart_Handle<M> const& rhs);
    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_SMART_HANDLE__INLINE_H
#include "smart_handle__inline.h"
#endif

#endif // SAKLIB_INTERNAL_SMART_HANDLE_H

