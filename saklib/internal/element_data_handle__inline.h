#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE__INLINE_H
#define SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE__INLINE_H

#ifndef SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE_H
#include "Element_Data_Handle.h"
#endif

#ifndef SAKLIB_INTERNAL_BAD_DATA_HANDLE_H
#include "exceptions/bad_data_handle.h"
#endif

#ifndef INCLUDE_STD_CASSERT
#define INCLUDE_STD_CASSERT
#include <cassert>
#endif


//---------------------------------------------------------------------------
// Element_Data_Handle<Manager>
//---------------------------------------------------------------------------
// Special 6
//============================================================
template <typename M>
saklib::internal::Element_Data_Handle<M>::Element_Data_Handle() = default;

template <typename M>
saklib::internal::Element_Data_Handle<M>::Element_Data_Handle(manager_type* ap_manager, reference_counter_type const& a_reference_counter):
    mp_manager(ap_manager),
    m_reference_counter(a_reference_counter)
{
    assert(mp_manager != nullptr);
    assert(cget_manager().has_element(cget_handle()));
}

template <typename M>
saklib::internal::Element_Data_Handle<M>::Element_Data_Handle(manager_type* ap_manager, reference_counter_type&& a_reference_counter):
    mp_manager(ap_manager),
    m_reference_counter(std::move(a_reference_counter))
{
    assert(mp_manager != nullptr);
    assert(cget_manager().has_element(cget_handle()));
}

template <typename M>
saklib::internal::Element_Data_Handle<M>::~Element_Data_Handle() = default;

template <typename M>
saklib::internal::Element_Data_Handle<M>::Element_Data_Handle(Element_Data_Handle const& other) = default;

template <typename M>
saklib::internal::Element_Data_Handle<M>& saklib::internal::Element_Data_Handle<M>::operator=(Element_Data_Handle const& other) = default;

template <typename M>
saklib::internal::Element_Data_Handle<M>::Element_Data_Handle(Element_Data_Handle && other):
    mp_manager(std::move(other.mp_manager)),
    m_reference_counter(std::move(other.m_reference_counter))
{
    other.mp_manager = nullptr;
}

template <typename M>
saklib::internal::Element_Data_Handle<M>& saklib::internal::Element_Data_Handle<M>::operator=(Element_Data_Handle && other)
{
    if (&other != this)
    {
        mp_manager = std::move(other.mp_manager);
        m_reference_counter = std::move(other.m_reference_counter);

        other.mp_manager = nullptr;
    }
    return *this;
}

// Interface
//============================================================
template <typename M>
bool saklib::internal::Element_Data_Handle<M>::is_valid() const
{
    return m_reference_counter.is_valid();
}

template <typename M>
bool saklib::internal::Element_Data_Handle<M>::is_null() const
{
    return m_reference_counter.is_null();
}

template <typename M>
typename saklib::internal::Element_Data_Handle<M>::handle_type saklib::internal::Element_Data_Handle<M>::cget_handle() const
{
    return m_reference_counter.cget_handle();
}

template <typename M>
std::size_t saklib::internal::Element_Data_Handle<M>::cget_reference_count() const
{
    return cget_manager().cget_reference_count(cget_handle());
}

template <typename M>
typename saklib::internal::Element_Data_Handle<M>::manager_type& saklib::internal::Element_Data_Handle<M>::get_manager()
{
    if (is_valid())
    {
        return *mp_manager;
    }
    else
    {
        throw Bad_Data_Handle();
    }
}

template <typename M>
typename saklib::internal::Element_Data_Handle<M>::manager_type const& saklib::internal::Element_Data_Handle<M>::cget_manager() const
{
    if (is_valid())
    {
        return *mp_manager;
    }
    else
    {
        throw Bad_Data_Handle();
    }
}


// Element_Data Wrapper Interface
//============================================================
template <typename M>
std::string const& saklib::internal::Element_Data_Handle<M>::cget_type() const
{
    return cget_manager().element_cget_type(cget_handle());
}

template <typename M>
std::string const& saklib::internal::Element_Data_Handle<M>::cget_name() const
{
    return cget_manager().element_cget_name(cget_handle());
}

template <typename M>
void saklib::internal::Element_Data_Handle<M>::set_name(std::string const& a_name)
{
    get_manager().element_set_name(cget_handle(), a_name);
}

template <typename M>
std::size_t saklib::internal::Element_Data_Handle<M>::cget_attribute_count() const
{
    return cget_manager().element_cget_attribute_count(cget_handle());
}

template <typename M>
typename saklib::internal::Element_Data_Handle<M>::attribute_handle_type saklib::internal::Element_Data_Handle<M>::cget_attribute_at(std::size_t a_index) const
{
    return cget_manager().element_cget_attribute_at(cget_handle(), a_index);
}

template <typename M>
std::vector<typename saklib::internal::Element_Data_Handle<M>::attribute_handle_type> saklib::internal::Element_Data_Handle<M>::cget_attributes() const
{
     return cget_manager().element_cget_attributes(cget_handle());
}

// Comparison Operators
//============================================================
template <typename M>
bool saklib::internal::Element_Data_Handle<M>::operator==(Element_Data_Handle<M> const& rhs)
{
    return m_reference_counter == rhs.m_reference_counter && mp_manager == rhs.mp_manager;
}

template <typename M>
bool saklib::internal::Element_Data_Handle<M>::operator!=(Element_Data_Handle<M> const& rhs)
{
    return m_reference_counter != rhs.m_reference_counter && mp_manager != rhs.mp_manager;
}

template <typename M>
bool saklib::internal::Element_Data_Handle<M>::operator<(Element_Data_Handle<M> const& rhs)
{
    return m_reference_counter < rhs.m_reference_counter && mp_manager < rhs.mp_manager;
}

template <typename M>
bool saklib::internal::Element_Data_Handle<M>::operator>(Element_Data_Handle<M> const& rhs)
{
    return m_reference_counter > rhs.m_reference_counter && mp_manager > rhs.mp_manager;
}

template <typename M>
bool saklib::internal::Element_Data_Handle<M>::operator<=(Element_Data_Handle<M> const& rhs)
{
    return m_reference_counter <= rhs.m_reference_counter && mp_manager <= rhs.mp_manager;
}

template <typename M>
bool saklib::internal::Element_Data_Handle<M>::operator>=(Element_Data_Handle<M> const& rhs)
{
    return m_reference_counter >= rhs.m_reference_counter && mp_manager >= rhs.mp_manager;
}

// Comparison Operators for compare to the null handle
//============================================================
template <typename M>
bool saklib::internal::Element_Data_Handle<M>::operator==(Null_Handle_Type const& )
{
    return is_null();
}

template <typename M>
bool saklib::internal::Element_Data_Handle<M>::operator!=(Null_Handle_Type const& )
{
    return is_valid();
}

#endif // SAKLIB_INTERNAL_ELEMENT_DATA_HANDLE__INLINE_H

