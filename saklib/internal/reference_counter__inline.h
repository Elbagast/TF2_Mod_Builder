#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTER__INLINE_H
#define SAKLIB_INTERNAL_REFERENCE_COUNTER__INLINE_H

#ifndef SAKLIB_INTERNAL_REFERENCE_COUNTER_H
#include "reference_counter.h"
#endif

//---------------------------------------------------------------------------
// Member_Reference_Counter<T_Storage, T_Handle, F_Incrementor, F_Decrementor>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename S, typename H, typename I, typename D>
saklib::internal::Reference_Counter<S, H, I, D>::Reference_Counter() :
    mp_storage(nullptr),
    m_handle()
{
}

template <typename S, typename H, typename I, typename D>
saklib::internal::Reference_Counter<S, H, I, D>::Reference_Counter(storage_type& ar_storage, handle_type const& a_handle) :
    mp_storage(&ar_storage),
    m_handle(a_handle)
{
    if (is_valid())
    {
        incrementor_type()(mp_storage, m_handle);
    }
}

template <typename S, typename H, typename I, typename D>
saklib::internal::Reference_Counter<S, H, I, D>::~Reference_Counter()
{
    if (is_valid())
    {
        decrementor_type()(mp_storage, m_handle);
    }
}

template <typename S, typename H, typename I, typename D>
saklib::internal::Reference_Counter<S, H, I, D>::Reference_Counter(Reference_Counter const& other) :
    mp_storage(other.mp_storage),
    m_handle(other.m_handle)
{
    if (is_valid())
    {
        incrementor_type()(mp_storage, m_handle);
    }
}

template <typename S, typename H, typename I, typename D>
saklib::internal::Reference_Counter<S, H, I, D>& saklib::internal::Reference_Counter<S, H, I, D>::operator=(Reference_Counter const& other)
{
    if (&other != this)
    {
        storage_type* old_mp_manager{mp_storage};
        handle_type old_m_handle{m_handle};

        mp_storage = other.mp_storage;
        m_handle = other.m_handle;

        if (is_valid())
        {
            incrementor_type()(mp_storage, m_handle);
        }
        if (old_mp_manager != nullptr)
        {
            decrementor_type()(old_mp_manager, old_m_handle);
        }
    }
    return *this;
}

template <typename S, typename H, typename I, typename D>
saklib::internal::Reference_Counter<S, H, I, D>::Reference_Counter(Reference_Counter && other):
    mp_storage(other.mp_storage),
    m_handle(other.m_handle)
{
    other.mp_storage = nullptr;
    other.m_handle = handle_type();
}

template <typename S, typename H, typename I, typename D>
saklib::internal::Reference_Counter<S, H, I, D>& saklib::internal::Reference_Counter<S, H, I, D>::operator=(Reference_Counter && other)
{
    if (&other != this)
    {
        storage_type* old_mp_manager{mp_storage};
        handle_type old_m_handle{m_handle};

        mp_storage = std::move(other.mp_storage);
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

template <typename S, typename H, typename I, typename D>
bool saklib::internal::Reference_Counter<S, H, I, D>::is_valid() const
{
    return mp_storage != nullptr;// && mp_manager->is_valid(m_handle); //?
}

template <typename S, typename H, typename I, typename D>
bool saklib::internal::Reference_Counter<S, H, I, D>::is_null() const
{
    return mp_storage == nullptr;
}

template <typename S, typename H, typename I, typename D>
typename saklib::internal::Reference_Counter<S, H, I, D>::storage_type* saklib::internal::Reference_Counter<S, H, I, D>::get_storage()
{
    return mp_storage;
}

template <typename S, typename H, typename I, typename D>
typename saklib::internal::Reference_Counter<S, H, I, D>::storage_type const* saklib::internal::Reference_Counter<S, H, I, D>::cget_storage() const
{
    return mp_storage;
}

template <typename S, typename H, typename I, typename D>
typename saklib::internal::Reference_Counter<S, H, I, D>::handle_type const& saklib::internal::Reference_Counter<S, H, I, D>::cget_handle() const
{
    return m_handle;
}

// Comparison Operators
//============================================================
template <typename S, typename H, typename I, typename D>
bool saklib::internal::operator==(Reference_Counter<S, H, I, D> const& lhs, Reference_Counter<S, H, I, D> const& rhs)
{
    return (lhs.cget_storage() == rhs.cget_storage()) && (lhs.cget_handle() == rhs.cget_handle());
}

template <typename S, typename H, typename I, typename D>
bool saklib::internal::operator!=(Reference_Counter<S, H, I, D> const& lhs, Reference_Counter<S, H, I, D> const& rhs)
{
    return !operator==(lhs, rhs);
}

template <typename S, typename H, typename I, typename D>
bool saklib::internal::operator<(Reference_Counter<S, H, I, D> const& lhs, Reference_Counter<S, H, I, D> const& rhs)
{
    return lhs.cget_handle() < rhs.cget_handle();
    //return (lhs.cget_storage() < rhs.cget_storage()) && (lhs.cget_handle() < rhs.cget_handle());
}

template <typename S, typename H, typename I, typename D>
bool saklib::internal::operator>(Reference_Counter<S, H, I, D> const& lhs, Reference_Counter<S, H, I, D> const& rhs)
{
    return operator<(rhs, lhs);
}

template <typename S, typename H, typename I, typename D>
bool saklib::internal::operator<=(Reference_Counter<S, H, I, D> const& lhs, Reference_Counter<S, H, I, D> const& rhs)
{
    return !operator>(lhs, rhs);
}

template <typename S, typename H, typename I, typename D>
bool saklib::internal::operator>=(Reference_Counter<S, H, I, D> const& lhs, Reference_Counter<S, H, I, D> const& rhs)
{
    return !operator<(lhs, rhs);
}


// Comparison Operators for compare to the null handle
//============================================================
template <typename S, typename H, typename I, typename D>
bool saklib::internal::operator==(Reference_Counter<S, H, I, D> const& lhs, Null_Handle_Type const& rhs)
{
    return lhs.is_null();
}

template <typename S, typename H, typename I, typename D>
bool saklib::internal::operator!=(Reference_Counter<S, H, I, D> const& lhs, Null_Handle_Type const& rhs)
{
    return !operator==(lhs, rhs);
}

template <typename S, typename H, typename I, typename D>
bool saklib::internal::operator==(Null_Handle_Type const& lhs, Reference_Counter<S, H, I, D> const& rhs)
{
    return operator==(rhs, lhs);
}

template <typename S, typename H, typename I, typename D>
bool saklib::internal::operator!=(Null_Handle_Type const& lhs, Reference_Counter<S, H, I, D> const& rhs)
{
    return !operator==(rhs, lhs);
}




//---------------------------------------------------------------------------
// Member_Reference_Counter<T_Storage, T_Handle, void(T_Storage::*F_Incrementor)(T_Handle const&), void(T_Storage::*F_Decrementor)(T_Handle const&)>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&) >
saklib::internal::Member_Reference_Counter<S, H, I, D>::Member_Reference_Counter() :
    m_reference_counter()
{
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&) >
saklib::internal::Member_Reference_Counter<S, H, I, D>::Member_Reference_Counter(storage_type& ar_storage, handle_type const& a_handle) :
    m_reference_counter(ar_storage, a_handle)
{
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&) >
saklib::internal::Member_Reference_Counter<S, H, I, D>::~Member_Reference_Counter() = default;

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&) >
saklib::internal::Member_Reference_Counter<S, H, I, D>::Member_Reference_Counter(Member_Reference_Counter const& other) = default;

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&) >
saklib::internal::Member_Reference_Counter<S, H, I, D>& saklib::internal::Member_Reference_Counter<S, H, I, D>::operator=(Member_Reference_Counter const& other) = default;

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&) >
saklib::internal::Member_Reference_Counter<S, H, I, D>::Member_Reference_Counter(Member_Reference_Counter && other):
    m_reference_counter(std::move(other.m_reference_counter))
{
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&) >
saklib::internal::Member_Reference_Counter<S, H, I, D>& saklib::internal::Member_Reference_Counter<S, H, I, D>::operator=(Member_Reference_Counter && other)
{
    if (&other != this)
    {
        m_reference_counter = std::move(other.m_reference_counter);
    }
    return *this;
}

// Interface
//============================================================

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&) >
bool saklib::internal::Member_Reference_Counter<S, H, I, D>::is_valid() const
{
    return m_reference_counter.is_valid();
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&) >
bool saklib::internal::Member_Reference_Counter<S, H, I, D>::is_null() const
{
    return m_reference_counter.is_null();
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&) >
typename saklib::internal::Member_Reference_Counter<S, H, I, D>::storage_type* saklib::internal::Member_Reference_Counter<S, H, I, D>::get_storage()
{
    return m_reference_counter.get_storage();
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&) >
typename saklib::internal::Member_Reference_Counter<S, H, I, D>::storage_type const* saklib::internal::Member_Reference_Counter<S, H, I, D>::cget_storage() const
{
    return m_reference_counter.cget_storage();
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&) >
typename saklib::internal::Member_Reference_Counter<S, H, I, D>::handle_type const& saklib::internal::Member_Reference_Counter<S, H, I, D>::cget_handle() const
{
    return m_reference_counter.cget_handle();
}

// Comparison Operators
//============================================================
template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
bool saklib::internal::operator==(Member_Reference_Counter<S, H, I, D> const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs)
{
    return (lhs.cget_storage() == rhs.cget_storage()) && (lhs.cget_handle() == rhs.cget_handle());
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
bool saklib::internal::operator!=(Member_Reference_Counter<S, H, I, D> const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs)
{
    return !operator==(lhs, rhs);
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
bool saklib::internal::operator<(Member_Reference_Counter<S, H, I, D> const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs)
{
    return lhs.cget_handle() < rhs.cget_handle();
    //return (lhs.cget_storage() < rhs.cget_storage()) && (lhs.cget_handle() < rhs.cget_handle());
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
bool saklib::internal::operator>(Member_Reference_Counter<S, H, I, D> const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs)
{
    return operator<(rhs, lhs);
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
bool saklib::internal::operator<=(Member_Reference_Counter<S, H, I, D> const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs)
{
    return !operator>(lhs, rhs);
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
bool saklib::internal::operator>=(Member_Reference_Counter<S, H, I, D> const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs)
{
    return !operator<(lhs, rhs);
}

// Comparison Operators for compare to the null handle
//============================================================
template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
bool saklib::internal::operator==(Member_Reference_Counter<S, H, I, D> const& lhs, Null_Handle_Type const& )
{
    return lhs.is_null();
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
bool saklib::internal::operator!=(Member_Reference_Counter<S, H, I, D> const& lhs, Null_Handle_Type const& rhs)
{
    return !operator==(lhs, rhs);
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
bool saklib::internal::operator==(Null_Handle_Type const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs)
{
    return operator==(rhs, lhs);
}

template <typename S, typename H, void(S::*I)(H const&), void(S::*D)(H const&)>
bool saklib::internal::operator!=(Null_Handle_Type const& lhs, Member_Reference_Counter<S, H, I, D> const& rhs)
{
    return !operator==(rhs, lhs);
}


#endif // SAKLIB_INTERNAL_REFERENCE_COUNTER__INLINE_H

