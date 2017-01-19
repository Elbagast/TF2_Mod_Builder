#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTER_H
#define SAKLIB_INTERNAL_REFERENCE_COUNTER_H

#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTER__FWD_H
#include "reference_counter__fwd.h"
#endif

namespace saklib
{
    namespace internal
    {

        //---------------------------------------------------------------------------
        // Reference_Counter<T_Manager, T_Handle, F_Incrementor, F_Decrementor>
        //---------------------------------------------------------------------------

        template
                <
                typename T_Storage,
                typename T_Handle,
                typename F_Incrementor,
                typename F_Decrementor
                >
        class Reference_Counter
        {
            // static_assert( F_Incrementor is void operator()(manager_type*, handle_type const&));
            // static_assert( F_Decrementor is void operator()(manager_type*, handle_type const&));

            using incrementor_type = F_Incrementor;
            using decrementor_type = F_Decrementor;

        public:
            // Typedefs
            //============================================================
            using storage_type = T_Storage;
            using handle_type = T_Handle;

            // Special 6
            //============================================================
            Reference_Counter();
            Reference_Counter(storage_type& ar_storage, handle_type const& a_handle);

            ~Reference_Counter();

            Reference_Counter(Reference_Counter const& other);
            Reference_Counter& operator=(Reference_Counter const& other);

            Reference_Counter(Reference_Counter && other);
            Reference_Counter& operator=(Reference_Counter && other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            storage_type* get_storage();
            storage_type const* cget_storage() const;
            handle_type const& cget_handle() const;

        private:
            storage_type* mp_storage;
            handle_type m_handle;
        };

        // Comparison Operators
        //============================================================
        template <typename S, typename H, typename I, typename D>
        bool operator==(Reference_Counter<S, H, I, D> const& lhs, Reference_Counter<S, H, I, D> const& rhs);
        template <typename S, typename H, typename I, typename D>
        bool operator!=(Reference_Counter<S, H, I, D> const& lhs, Reference_Counter<S, H, I, D> const& rhs);
        template <typename S, typename H, typename I, typename D>
        bool operator<(Reference_Counter<S, H, I, D> const& lhs, Reference_Counter<S, H, I, D> const& rhs);
        template <typename S, typename H, typename I, typename D>
        bool operator>(Reference_Counter<S, H, I, D> const& lhs, Reference_Counter<S, H, I, D> const& rhs);
        template <typename S, typename H, typename I, typename D>
        bool operator<=(Reference_Counter<S, H, I, D> const& lhs, Reference_Counter<S, H, I, D> const& rhs);
        template <typename S, typename H, typename I, typename D>
        bool operator>=(Reference_Counter<S, H, I, D> const& lhs, Reference_Counter<S, H, I, D> const& rhs);

        // Comparison Operators for compare to the null handle
        //============================================================
        template <typename S, typename H, typename I, typename D>
        bool operator==(Reference_Counter<S, H, I, D> const& lhs, Null_Integer_ID_Type const& rhs);
        template <typename S, typename H, typename I, typename D>
        bool operator!=(Reference_Counter<S, H, I, D> const& lhs, Null_Integer_ID_Type const& rhs);

        template <typename S, typename H, typename I, typename D>
        bool operator==(Null_Integer_ID_Type const& lhs, Reference_Counter<S, H, I, D> const& rhs);
        template <typename S, typename H, typename I, typename D>
        bool operator!=(Null_Integer_ID_Type const& lhs, Reference_Counter<S, H, I, D> const& rhs);

        //---------------------------------------------------------------------------
        // Reference_Counter<T_Storage, T_Handle, F_Incrementor, F_Decrementor>
        //---------------------------------------------------------------------------

        template
                <
                typename T_Storage,
                typename T_Handle,
                void(T_Storage::*F_Incrementor)(T_Handle const&),
                void(T_Storage::*F_Decrementor)(T_Handle const&)
                >
        class Member_Reference_Counter
        {
            template <void(T_Storage::*F)(T_Handle const&)>
            struct Function_Caller
            {
                void operator()(T_Storage* ap_manager, T_Handle const& ar_handle)
                {
                    (ap_manager->*F)(ar_handle);
                }
            };

            using incrementor = Function_Caller<F_Incrementor>;
            using decrementor = Function_Caller<F_Decrementor>;
            using reference_counter_type = Reference_Counter<T_Storage, T_Handle, incrementor, decrementor>;
        public:
            // Typedefs
            //============================================================
            using storage_type = T_Storage;
            using handle_type = T_Handle;

            // Special 6
            //============================================================
            Member_Reference_Counter();
            Member_Reference_Counter(storage_type& ar_storage, handle_type const& a_handle);

            ~Member_Reference_Counter();

            Member_Reference_Counter(Member_Reference_Counter const& other);
            Member_Reference_Counter& operator=(Member_Reference_Counter const& other);

            Member_Reference_Counter(Member_Reference_Counter && other);
            Member_Reference_Counter& operator=(Member_Reference_Counter && other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            storage_type* get_storage();
            storage_type const* cget_storage() const;
            handle_type const& cget_handle() const;

        private:
            reference_counter_type m_reference_counter;
        };


        // Comparison Operators
        //============================================================
        template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
        bool operator==(Member_Reference_Counter<S, H, I, D> const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs);
        template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
        bool operator!=(Member_Reference_Counter<S, H, I, D> const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs);
        template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
        bool operator<(Member_Reference_Counter<S, H, I, D> const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs);
        template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
        bool operator>(Member_Reference_Counter<S, H, I, D> const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs);
        template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
        bool operator<=(Member_Reference_Counter<S, H, I, D> const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs);
        template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
        bool operator>=(Member_Reference_Counter<S, H, I, D> const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs);


        // Comparison Operators for compare to the null handle
        //============================================================
        template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
        bool operator==(Member_Reference_Counter<S, H, I, D> const& lhs, Null_Integer_ID_Type const& rhs);
        template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
        bool operator!=(Member_Reference_Counter<S, H, I, D> const& lhs, Null_Integer_ID_Type const& rhs);

        template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
        bool operator==(Null_Integer_ID_Type const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs);
        template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
        bool operator!=(Null_Integer_ID_Type const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs);

    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTER__INLINE_H
#include "reference_counter__inline.h"
#endif

#endif // REFERENCE_COUNTER_H
