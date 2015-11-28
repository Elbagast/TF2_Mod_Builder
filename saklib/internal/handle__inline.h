#ifndef SAKLIB_INTERNAL_HANDLE__INLINE_H
#define SAKLIB_INTERNAL_HANDLE__INLINE_H

#ifndef SAKLIB_INTERNAL_HANDLE_H
#include "handle.h"
#endif

// Special 6
//============================================================
template <typename T>
saklib::internal::Handle<T>::Handle():
    m_value{null_handle_value()}
{}

template <typename T>
saklib::internal::Handle<T>::Handle(Null_Handle_Type && /*a_handle*/):
    Handle()
{}

template <typename T>
saklib::internal::Handle<T>::Handle(Handle_Value_Type a_value):
    m_value{a_value}
{}

template <typename T>
saklib::internal::Handle<T>::~Handle() = default;

template <typename T>
saklib::internal::Handle<T>::Handle(Handle const& handle) = default;

template <typename T>
saklib::internal::Handle<T>& saklib::internal::Handle<T>::operator=(Handle const& a_handle) = default;


template <typename T>
saklib::internal::Handle<T>::Handle(Handle && a_handle):
    m_value{std::move(a_handle.m_value)}
{
    a_handle.m_value = null_handle_value();
}

template <typename T>
saklib::internal::Handle<T>& saklib::internal::Handle<T>::operator=(Handle && a_handle)
{
    m_value = std::move(a_handle.m_value);
    a_handle.m_value = null_handle_value();
    return *this;
}

// Interface
//============================================================
template <typename T>
saklib::internal::Handle_Value_Type saklib::internal::Handle<T>::get_value() const
{
    return m_value;
}

template <typename T>
saklib::internal::Handle<T>::operator bool() const
{
    return m_value != null_handle_value();
}


// Comparison Operators
//============================================================
template <typename T>
bool saklib::internal::operator==(Handle<T> const& lhs, Handle<T> const& rhs)
{
    return lhs.get_value() == rhs.get_value();
}
template <typename T>
bool saklib::internal::operator!=(Handle<T> const& lhs, Handle<T> const& rhs)
{
    return !operator==(lhs, rhs);
}
template <typename T>
bool saklib::internal::operator<(Handle<T> const& lhs, Handle<T> const& rhs)
{
    return lhs.get_value() < rhs.get_value();
}
template <typename T>
bool saklib::internal::operator>(Handle<T> const& lhs, Handle<T> const& rhs)
{
    return operator<(rhs, lhs);
}
template <typename T>
bool saklib::internal::operator<=(Handle<T> const& lhs, Handle<T> const& rhs)
{
    return !operator>(lhs, rhs);
}
template <typename T>
bool saklib::internal::operator>=(Handle<T> const& lhs, Handle<T> const& rhs)
{
    return !operator<(lhs, rhs);
}


// Comparison Operators for compare to the null handle
//============================================================
template <typename T>
bool saklib::internal::operator==(Handle<T> const& lhs, Null_Handle_Type const&/*rhs*/)
{
    return lhs.get_value() == Null_Handle_Type::value;
}
template <typename T>
bool saklib::internal::operator!=(Handle<T> const& lhs, Null_Handle_Type const& rhs)
{
    return !operator==(lhs, rhs);
}

template <typename T>
bool saklib::internal::operator==(Null_Handle_Type const& lhs, Handle<T> const& rhs)
{
    return operator==(rhs, lhs);
}
template <typename T>
bool saklib::internal::operator!=(Null_Handle_Type const& lhs, Handle<T> const& rhs)
{
    return !operator==(rhs, lhs);
}


#endif // HANDLE__INLINE_H

