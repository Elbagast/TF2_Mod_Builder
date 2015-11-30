#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTER__INLINE_H
#define SAKLIB_INTERNAL_REFERENCE_COUNTER__INLINE_H

#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTER_H
#include "reference_counter.h"
#endif

//---------------------------------------------------------------------------
// Member_Reference_Counter<T_Manager, T_Handle, F_Incrementor, F_Decrementor>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T_M, typename T_H, typename F_I, typename F_D>
saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::Reference_Counter() :
    mp_manager(nullptr),
    m_handle()
{
}

template <typename T_M, typename T_H, typename F_I, typename F_D>
saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::Reference_Counter(manager_type* ap_manager, handle_type const& a_handle) :
    mp_manager(ap_manager),
    m_handle(a_handle)
{
    if (is_valid())
    {
        incrementor_type()(mp_manager, m_handle);
    }
}

template <typename T_M, typename T_H, typename F_I, typename F_D>
saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::~Reference_Counter()
{
    if (is_valid())
    {
        decrementor_type()(mp_manager, m_handle);
    }
}

template <typename T_M, typename T_H, typename F_I, typename F_D>
saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::Reference_Counter(Reference_Counter const& other) :
    mp_manager(other.mp_manager),
    m_handle(other.m_handle)
{
    if (is_valid())
    {
        incrementor_type()(mp_manager, m_handle);
    }
}

template <typename T_M, typename T_H, typename F_I, typename F_D>
saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>& saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::operator=(Reference_Counter const& other)
{
    if (&other != this)
    {
        manager_type* old_mp_manager{mp_manager};
        handle_type old_m_handle{m_handle};

        mp_manager = other.mp_manager;
        m_handle = other.m_handle;

        if (is_valid())
        {
            incrementor_type()(mp_manager, m_handle);
        }
        if (old_mp_manager != nullptr)
        {
            decrementor_type()(old_mp_manager, old_m_handle);
        }
    }
    return *this;
}

template <typename T_M, typename T_H, typename F_I, typename F_D>
saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::Reference_Counter(Reference_Counter && other):
    mp_manager(other.mp_manager),
    m_handle(other.m_handle)
{
    other.mp_manager = nullptr;
    other.m_handle = handle_type();
}

template <typename T_M, typename T_H, typename F_I, typename F_D>
saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>& saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::operator=(Reference_Counter && other)
{
    if (&other != this)
    {
        manager_type* old_mp_manager{mp_manager};
        handle_type old_m_handle{m_handle};

        mp_manager = std::move(other.mp_manager);
        m_handle = std::move(other.m_handle);

        if (old_mp_manager != nullptr)
        {
            decrementor_type()(old_mp_manager, old_m_handle);
        }
    }
    return *this;
}

// Interface
//============================================================

template <typename T_M, typename T_H, typename F_I, typename F_D>
bool saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::is_valid() const
{
    return mp_manager != nullptr; // && mp_manager->is_valid(m_handle); //?
}

template <typename T_M, typename T_H, typename F_I, typename F_D>
bool saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::is_null() const
{
    return mp_manager == nullptr;
}

template <typename T_M, typename T_H, typename F_I, typename F_D>
typename saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::manager_type* saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::get_manager()
{
    return mp_manager;
}

template <typename T_M, typename T_H, typename F_I, typename F_D>
typename saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::manager_type const* saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::cget_manager() const
{
    return mp_manager;
}

template <typename T_M, typename T_H, typename F_I, typename F_D>
typename saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::handle_type const& saklib::internal::Reference_Counter<T_M, T_H, F_I, F_D>::cget_handle() const
{
    return m_handle;
}

//---------------------------------------------------------------------------
// Member_Reference_Counter<T_Manager, T_Handle, void(T_Manager::*F_Incrementor)(T_Handle const&), void(T_Manager::*F_Decrementor)(T_Handle const&)>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T_M, typename T_H, void(T_M::*F_I)(T_H const&), void(T_M::*F_D)(T_H const&) >
saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::Member_Reference_Counter() :
    m_reference_counter()
{
}

template <typename T_M, typename T_H, void(T_M::*F_I)(T_H const&), void(T_M::*F_D)(T_H const&) >
saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::Member_Reference_Counter(manager_type* ap_manager, handle_type const& a_handle) :
    m_reference_counter(ap_manager, (a_handle))
{
}

template <typename T_M, typename T_H, void(T_M::*F_I)(T_H const&), void(T_M::*F_D)(T_H const&) >
saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::~Member_Reference_Counter() = default;

template <typename T_M, typename T_H, void(T_M::*F_I)(T_H const&), void(T_M::*F_D)(T_H const&) >
saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::Member_Reference_Counter(Member_Reference_Counter const& other) = default;

template <typename T_M, typename T_H, void(T_M::*F_I)(T_H const&), void(T_M::*F_D)(T_H const&) >
saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >& saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::operator=(Member_Reference_Counter const& other) = default;

template <typename T_M, typename T_H, void(T_M::*F_I)(T_H const&), void(T_M::*F_D)(T_H const&) >
saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::Member_Reference_Counter(Member_Reference_Counter && other):
    m_reference_counter(std::move(other.m_reference_counter))
{
}

template <typename T_M, typename T_H, void(T_M::*F_I)(T_H const&), void(T_M::*F_D)(T_H const&) >
saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >& saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::operator=(Member_Reference_Counter && other)
{
    if (&other != this)
    {
        m_reference_counter = std::move(other.m_reference_counter);
    }
    return *this;
}

// Interface
//============================================================

template <typename T_M, typename T_H, void(T_M::*F_I)(T_H const&), void(T_M::*F_D)(T_H const&) >
bool saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::is_valid() const
{
    return m_reference_counter.is_valid();
}

template <typename T_M, typename T_H, void(T_M::*F_I)(T_H const&), void(T_M::*F_D)(T_H const&) >
bool saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::is_null() const
{
    return m_reference_counter.is_null();
}

template <typename T_M, typename T_H, void(T_M::*F_I)(T_H const&), void(T_M::*F_D)(T_H const&) >
typename saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::manager_type* saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::get_manager()
{
    return m_reference_counter.get_manager();
}

template <typename T_M, typename T_H, void(T_M::*F_I)(T_H const&), void(T_M::*F_D)(T_H const&) >
typename saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::manager_type const* saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::cget_manager() const
{
    return m_reference_counter.cget_manager();
}

template <typename T_M, typename T_H, void(T_M::*F_I)(T_H const&), void(T_M::*F_D)(T_H const&) >
typename saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::handle_type const& saklib::internal::Member_Reference_Counter<T_M, T_H, F_I, F_D >::cget_handle() const
{
    return m_reference_counter.cget_handle();
}



#endif // SAKLIB_INTERNAL_REFERENCE_COUNTER__INLINE_H

