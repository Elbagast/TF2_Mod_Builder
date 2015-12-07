#include "element_data_handle.h"

#include "attribute_data_handle.h"

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

saklib::internal::Element_Data_Handle::Element_Data_Handle() = default;

saklib::internal::Element_Data_Handle::Element_Data_Handle(Element_Data_Manager* ap_manager, reference_counter_type const& a_reference_counter):
    mp_manager(ap_manager),
    m_reference_counter(a_reference_counter)
{
    assert(mp_manager != nullptr);
    assert(cget_manager().has_element(cget_handle()));
}

saklib::internal::Element_Data_Handle::Element_Data_Handle(Element_Data_Manager* ap_manager, reference_counter_type&& a_reference_counter):
    mp_manager(ap_manager),
    m_reference_counter(std::move(a_reference_counter))
{
    assert(mp_manager != nullptr);
    assert(cget_manager().has_element(cget_handle()));
}

saklib::internal::Element_Data_Handle::~Element_Data_Handle() = default;

saklib::internal::Element_Data_Handle::Element_Data_Handle(Element_Data_Handle const& other) = default;

saklib::internal::Element_Data_Handle& saklib::internal::Element_Data_Handle::operator=(Element_Data_Handle const& other) = default;

saklib::internal::Element_Data_Handle::Element_Data_Handle(Element_Data_Handle && other):
    mp_manager(std::move(other.mp_manager)),
    m_reference_counter(std::move(other.m_reference_counter))
{
    other.mp_manager = nullptr;
}

saklib::internal::Element_Data_Handle& saklib::internal::Element_Data_Handle::operator=(Element_Data_Handle && other)
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

bool saklib::internal::Element_Data_Handle::is_valid() const
{
    return m_reference_counter.is_valid();
}


bool saklib::internal::Element_Data_Handle::is_null() const
{
    return m_reference_counter.is_null();
}


saklib::internal::Element_Data_Handle::handle_type saklib::internal::Element_Data_Handle::cget_handle() const
{
    return m_reference_counter.cget_handle();
}

std::size_t saklib::internal::Element_Data_Handle::cget_reference_count() const
{
    return m_reference_counter.cget_storage()->cget_reference_count(cget_handle());
}

saklib::internal::Element_Data_Manager& saklib::internal::Element_Data_Handle::get_manager()
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

saklib::internal::Element_Data_Manager const& saklib::internal::Element_Data_Handle::cget_manager() const
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
std::string const& saklib::internal::Element_Data_Handle::cget_type() const
{
    return cget_element().cget_type();
}

std::string const& saklib::internal::Element_Data_Handle::cget_name() const
{
    return cget_element().cget_name();
}

void saklib::internal::Element_Data_Handle::set_name(std::string const& a_name)
{
    get_element().set_name(a_name);
}

std::size_t saklib::internal::Element_Data_Handle::cget_attribute_count() const
{
    return cget_element().cget_attribute_count();
}

bool saklib::internal::Element_Data_Handle::has_attribute(std::size_t a_index) const
{
    return cget_element().has_attribute(a_index);
}

saklib::internal::Attribute_Data_Handle saklib::internal::Element_Data_Handle::cget_attribute_at(std::size_t a_index) const
{
    if (has_attribute(a_index))
    {
        return Attribute_Data_Handle(*this, a_index);
    }
    else
    {
        return Attribute_Data_Handle();
    }
}

std::vector<saklib::internal::Attribute_Data_Handle> saklib::internal::Element_Data_Handle::cget_attributes() const
{
    std::vector<Attribute_Data_Handle> l_result{};
    auto const l_attribute_count = cget_attribute_count();
    l_result.reserve(l_attribute_count);
    for (std::size_t l_index = 0; l_index < l_attribute_count; ++l_index)
    {
        l_result.emplace_back(*this, l_index);
    }
    return l_result;
}

// Comparison Operators
//============================================================
bool saklib::internal::Element_Data_Handle::operator==(Element_Data_Handle const& rhs)
{
    return mp_manager == rhs.mp_manager && m_reference_counter == rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Handle::operator!=(Element_Data_Handle const& rhs)
{
    return mp_manager != rhs.mp_manager && m_reference_counter != rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Handle::operator<(Element_Data_Handle const& rhs)
{
    return mp_manager < rhs.mp_manager && m_reference_counter < rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Handle::operator>(Element_Data_Handle const& rhs)
{
    return mp_manager > rhs.mp_manager && m_reference_counter > rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Handle::operator<=(Element_Data_Handle const& rhs)
{
    return mp_manager <= rhs.mp_manager && m_reference_counter <= rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Handle::operator>=(Element_Data_Handle const& rhs)
{
    return mp_manager >= rhs.mp_manager && m_reference_counter >= rhs.m_reference_counter;
}

// Comparison Operators for compare to the null handle
//============================================================
bool saklib::internal::Element_Data_Handle::operator==(Null_Handle_Type const& )
{
    return is_null();
}

bool saklib::internal::Element_Data_Handle::operator!=(Null_Handle_Type const& )
{
    return is_valid();
}

// Protected Helpers
//============================================================
saklib::internal::Element_Data& saklib::internal::Element_Data_Handle::get_element()
{
    return m_reference_counter.get_storage()->get_data(m_reference_counter.cget_handle());
}

saklib::internal::Element_Data const& saklib::internal::Element_Data_Handle::cget_element() const
{
    return m_reference_counter.cget_storage()->cget_data(m_reference_counter.cget_handle());
}

