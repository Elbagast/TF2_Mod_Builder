#include "element_data_handle.h"

#include "attribute_data_handle.h"
#include "element_data.h"

//---------------------------------------------------------------------------
// Element_Data_Handle
//---------------------------------------------------------------------------
// Special 6
//============================================================
saklib::internal::Element_Data_Handle::Element_Data_Handle() = default;

saklib::internal::Element_Data_Handle::Element_Data_Handle(reference_counter_type const& a_reference_counter):
    m_reference_counter(a_reference_counter)
{
}

saklib::internal::Element_Data_Handle::Element_Data_Handle(reference_counter_type&& a_reference_counter):
    m_reference_counter(std::move(a_reference_counter))
{
}
saklib::internal::Element_Data_Handle::~Element_Data_Handle() = default;

saklib::internal::Element_Data_Handle::Element_Data_Handle(Element_Data_Handle const& other) = default;
saklib::internal::Element_Data_Handle& saklib::internal::Element_Data_Handle::operator=(Element_Data_Handle const& other) = default;

saklib::internal::Element_Data_Handle::Element_Data_Handle(Element_Data_Handle && other):
    m_reference_counter(std::move(other.m_reference_counter))
{
}

saklib::internal::Element_Data_Handle& saklib::internal::Element_Data_Handle::operator=(Element_Data_Handle && other)
{
    if (&other != this)
    {
        m_reference_counter = std::move(other.m_reference_counter);
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
    return cget_storage().cget_reference_count(cget_handle());
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
    get_element().set_name(a_name); // no unique checking...
}

std::size_t saklib::internal::Element_Data_Handle::cget_attribute_count() const
{
    return cget_element().cget_attribute_count();
}

saklib::internal::Attribute_Data_Handle saklib::internal::Element_Data_Handle::cget_attribute_at(std::size_t a_index) const
{
    if (is_valid() && a_index < cget_attribute_count())
    {
        return Attribute_Data_Handle(m_reference_counter, a_index);
    }
    else
    {
        return Attribute_Data_Handle();
    }
}

std::vector<saklib::internal::Attribute_Data_Handle> saklib::internal::Element_Data_Handle::cget_attributes() const
{
    std::size_t l_attribute_count = cget_attribute_count();
    std::vector<Attribute_Data_Handle> l_result{};
    for (std::size_t index = 0; index != l_attribute_count; ++index)
    {
        l_result.push_back(Attribute_Data_Handle(m_reference_counter, index));
    }
    return l_result;
}

// Comparison Operators
//============================================================
bool saklib::internal::Element_Data_Handle::operator==(Element_Data_Handle const& rhs)
{
    return m_reference_counter == rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Handle::operator!=(Element_Data_Handle const& rhs)
{
    return m_reference_counter != rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Handle::operator<(Element_Data_Handle const& rhs)
{
    return m_reference_counter < rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Handle::operator>(Element_Data_Handle const& rhs)
{
    return m_reference_counter > rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Handle::operator<=(Element_Data_Handle const& rhs)
{
    return m_reference_counter <= rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Handle::operator>=(Element_Data_Handle const& rhs)
{
    return m_reference_counter >= rhs.m_reference_counter;
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
saklib::internal::Element_Data_Handle::storage_type& saklib::internal::Element_Data_Handle::get_storage()
{
    if (is_valid())
    {
        return *(m_reference_counter.get_storage());
    }
    else
    {
        throw Bad_Data_Handle();
    }
}

saklib::internal::Element_Data_Handle::storage_type const& saklib::internal::Element_Data_Handle::cget_storage() const
{
    if (is_valid())
    {
        return *(m_reference_counter.cget_storage());
    }
    else
    {
        throw Bad_Data_Handle();
    }
}

saklib::internal::Element_Data& saklib::internal::Element_Data_Handle::get_element()
{
    return get_storage().get_data(m_reference_counter.cget_handle());
}

saklib::internal::Element_Data const& saklib::internal::Element_Data_Handle::cget_element() const
{
    return cget_storage().cget_data(m_reference_counter.cget_handle());
}
