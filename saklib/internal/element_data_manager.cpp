#include "element_data_manager.h"

#include "exceptions/bad_element_data_type.h"
#include <limits>

//---------------------------------------------------------------------------
// Element_Data_Manager
//---------------------------------------------------------------------------

// Special 6
//============================================================
//saklib::internal::Element_Data_Manager::Element_Data_Manager();

// Interface
//============================================================
bool saklib::internal::Element_Data_Manager::has_element(handle_type const& a_handle) const
{
    return m_storage.has_data(a_handle);
}

saklib::internal::Element_Data_Handle saklib::internal::Element_Data_Manager::make_element_handle(handle_type const& a_handle)
{
    if (has_element(a_handle))
    {
        return Element_Data_Handle(m_storage.make_handle(a_handle));
    }
    else
    {
        return Element_Data_Handle();
    }
}

saklib::internal::Element_Data_Handle saklib::internal::Element_Data_Manager::make_element(Element_Data_Definition_Handle&& a_definition_handle)
{
    if (a_definition_handle.is_valid())
    {
        auto new_handle = m_handle_factory.make_new_handle();
        auto new_reference_counter = m_storage.emplace_data(new_handle, Element_Data(a_definition_handle.cget_definition()), std::move(a_definition_handle));
        return Element_Data_Handle(std::move(new_reference_counter));
    }
    else
    {
        return Element_Data_Handle();
    }
}

std::vector<saklib::internal::Element_Data_Manager::handle_type> saklib::internal::Element_Data_Manager::cget_all_handles() const
{
    return m_storage.cget_all_handles();
}

std::vector<saklib::internal::Element_Data_Handle> saklib::internal::Element_Data_Manager::make_all_element_handles()
{
    auto all_handles = cget_all_handles();
    std::vector<Element_Data_Handle> l_result{};
    l_result.reserve(all_handles.size());
    for (auto const& handle : all_handles)
    {
        l_result.push_back(Element_Data_Handle(m_storage.make_handle(handle)));
    }
    return l_result;
}

//---------------------------------------------------------------------------
// Element_Data_Handle
//---------------------------------------------------------------------------
// Special 6
//============================================================
saklib::internal::Element_Data_Handle::Element_Data_Handle() = default;

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
    return m_reference_counter.cget_storage()->cget_reference_count(m_reference_counter.cget_handle());
}


// probably don't want to expose the Element here...
// need to supply wrapper handles for Attributes....
saklib::internal::Element_Data& saklib::internal::Element_Data_Handle::get_element()
{
    if(is_null())
    {
        throw Bad_Data_Handle();
    }
    return m_reference_counter.get_storage()->get_data(m_reference_counter.cget_handle());
}

saklib::internal::Element_Data const& saklib::internal::Element_Data_Handle::cget_element() const
{
    if(is_null())
    {
        throw Bad_Data_Handle();
    }
    return m_reference_counter.cget_storage()->cget_data(m_reference_counter.cget_handle());
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
bool saklib::internal::Element_Data_Handle::operator==(Null_Handle_Type const& rhs)
{
    return m_reference_counter == rhs;
}

bool saklib::internal::Element_Data_Handle::operator!=(Null_Handle_Type const& rhs)
{
    return m_reference_counter != rhs;
}
