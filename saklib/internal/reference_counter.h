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

        template <typename T_Manager, typename T_Handle, typename F_Incrementor, typename F_Decrementor>
        class Reference_Counter
        {
            // static_assert( F_Incrementor is void operator()(manager_type*, handle_type const&));
            // static_assert( F_Decrementor is void operator()(manager_type*, handle_type const&));

            template <typename F>
            struct Function_Caller
            {
                void operator()(T_Manager* ap_manager, T_Handle const& ar_handle)
                {
                    F()(ap_manager, ar_handle);
                }
            };

            using incrementor_type = typename Function_Caller<F_Incrementor>;
            using decrementor_type = typename Function_Caller<F_Decrementor>;

        public:
            // Typedefs
            //============================================================
            using manager_type = T_Manager;
            using handle_type = T_Handle;

            // Special 6
            //============================================================
            Reference_Counter();
            Reference_Counter(manager_type* ap_manager, handle_type const& a_handle);

            ~Reference_Counter();

            Reference_Counter(Reference_Counter const& other);
            Reference_Counter& operator=(Reference_Counter const& other);

            Reference_Counter(Reference_Counter && other);
            Reference_Counter& operator=(Reference_Counter && other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            manager_type* get_manager();
            manager_type const* cget_manager() const;
            handle_type const& cget_handle() const;

        private:
            manager_type* mp_manager;
            handle_type m_handle;
        };

        //---------------------------------------------------------------------------
        // Reference_Counter<T_Manager, T_Handle, F_Incrementor, F_Decrementor>
        //---------------------------------------------------------------------------

        template <typename T_Manager, typename T_Handle, void(T_Manager::*F_Incrementor)(T_Handle const&), void(T_Manager::*F_Decrementor)(T_Handle const&)>
        class Member_Reference_Counter
        {
            // static_assert( F_Incrementor is void operator()(manager_type*, handle_type const&));
            // static_assert( F_Decrementor is void operator()(manager_type*, handle_type const&));

            template <void(T_Manager::*F)(T_Handle const&)>
            struct Function_Caller
            {
                void operator()(T_Manager* ap_manager, T_Handle const& ar_handle)
                {
                    (ap_manager->*F)(ar_handle);
                }
            };

            using incrementor = Function_Caller<F_Incrementor>;
            using decrementor = Function_Caller<F_Decrementor>;
        public:
            // Typedefs
            //============================================================
            using manager_type = T_Manager;
            using handle_type = T_Handle;

            // Special 6
            //============================================================
            Member_Reference_Counter();
            Member_Reference_Counter(manager_type* ap_manager, handle_type const& a_handle);

            ~Member_Reference_Counter();

            Member_Reference_Counter(Member_Reference_Counter const& other);
            Member_Reference_Counter& operator=(Member_Reference_Counter const& other);

            Member_Reference_Counter(Member_Reference_Counter && other);
            Member_Reference_Counter& operator=(Member_Reference_Counter && other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            manager_type* get_manager();
            manager_type const* cget_manager() const;
            handle_type const& cget_handle() const;

        private:
            Reference_Counter<manager_type, handle_type, incrementor, decrementor> m_reference_counter;
        };

    } // namespace internal
} // namespace saklib

#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTER__INLINE_H
#include "reference_counter__inline.h"
#endif

#endif // REFERENCE_COUNTER_H
