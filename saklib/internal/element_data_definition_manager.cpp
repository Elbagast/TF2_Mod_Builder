#include "element_data_definition_manager.h"
#include "exceptions/bad_element_data_type.h"

#include <cassert>

//---------------------------------------------------------------------------
// Element_Definition_Data_Manager
//---------------------------------------------------------------------------

// Interface
//============================================================
// Is there a definition with this type?
bool saklib::internal::Element_Data_Definition_Manager::has_definition(std::string const& a_type) const
{
    return m_storage.has_data(a_type);
}

saklib::internal::Element_Data_Definition_Handle saklib::internal::Element_Data_Definition_Manager::add_definition(Element_Data_Definition && a_definition)
{
    if (has_definition(a_definition.cget_type()))
    {
        return Element_Data_Definition_Handle();
    }
    else
    {
        // add the data
        auto r_counter = m_storage.emplace_data(a_definition.cget_type(), std::move(a_definition));
        assert(m_storage.cget_reference_count(a_definition.cget_type()) == 1); // should be for the counter just made
        // force increment the data so that it won't be destroyed by the decrements called only be handles
        m_storage.increment_reference_count(r_counter.cget_handle());
        // make and return the full handle
        assert(m_storage.cget_reference_count(a_definition.cget_type()) == 2); // should now be incremented
        assert(get_definition_usage_count(a_definition.cget_type()) == 1);
        return Element_Data_Definition_Handle(std::move(r_counter));
    }
}

// Get a definition, throw an exception if there isn't one
saklib::internal::Element_Data_Definition const& saklib::internal::Element_Data_Definition_Manager::cget_definition(std::string const& a_type) const
{
    if (has_definition(a_type))
    {
        return m_storage.cget_data<0>(a_type);
    }
    else
    {
        throw Bad_Element_Data_Type(a_type);
    }
}

// Get reference counted handle to a definition
saklib::internal::Element_Data_Definition_Handle saklib::internal::Element_Data_Definition_Manager::make_definition_handle(std::string const& a_type)
{
    if (has_definition(a_type))
    {
        // add the data
        auto r_counter = m_storage.make_handle(a_type);
        assert(r_counter.is_valid());
        assert(r_counter.cget_handle() == a_type);
        assert(r_counter.cget_storage() == &m_storage);
        return Element_Data_Definition_Handle(std::move(r_counter));
    }
    else
    {
        return Element_Data_Definition_Handle();
    }


    //return Element_Data_Definition_Handle(m_storage.make_handle(a_type));
}

// The number of Elements that have been made using this definition.
std::size_t saklib::internal::Element_Data_Definition_Manager::get_definition_usage_count(std::string const& a_type) const
{
    return m_storage.cget_reference_count(a_type) - 1;
}

// Can this definition corresponding to this type be removed? A definition can
// only be removed if it exists and it has a usage count of 0. If these are
// both true then true is returned. If there is no such definition or it has
// a usage count above 0 then false is returned.
bool saklib::internal::Element_Data_Definition_Manager::can_remove_definition(std::string const& a_type) const
{
    // this should mean only the forced increment has taken place
    return has_definition(a_type) && m_storage.cget_reference_count(a_type) == 1;
}

// Try and remove the definition corresponding to this type. This function
// calls can_remove_definition() and only removes the definition if the result
// of that is true. If the remove cannot happen or fails then this function
// return false, otherwise the definition corresponding to this type is
// removed.
bool saklib::internal::Element_Data_Definition_Manager::remove_definition(std::string const& a_type)
{
    if (can_remove_definition(a_type))
    {
        m_storage.decrement_reference_count(a_type);
        assert(!m_storage.has_data(a_type));
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::string> saklib::internal::Element_Data_Definition_Manager::cget_definition_types() const
{
    return m_storage.cget_all_handles();
}

std::vector<saklib::internal::Element_Data_Definition_Handle> saklib::internal::Element_Data_Definition_Manager::make_definition_handles()
{
    auto all_handles = m_storage.cget_all_handles();
    std::vector<Element_Data_Definition_Handle> smart_handles{};
    smart_handles.reserve(all_handles.size());
    for (auto const& handle : all_handles)
    {
        smart_handles.push_back(make_definition_handle(handle));
    }
    return smart_handles;
}

//---------------------------------------------------------------------------
// Element_Definition_Data_Handle
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Element_Data_Definition_Handle::Element_Data_Definition_Handle():
    m_reference_counter()
{
}

saklib::internal::Element_Data_Definition_Handle::Element_Data_Definition_Handle(reference_counter_type const& a_ref_counter):
    m_reference_counter(a_ref_counter)
{
}

saklib::internal::Element_Data_Definition_Handle::Element_Data_Definition_Handle(reference_counter_type&& a_ref_counter):
    m_reference_counter(std::move(a_ref_counter))
{
}

saklib::internal::Element_Data_Definition_Handle::~Element_Data_Definition_Handle() = default;

saklib::internal::Element_Data_Definition_Handle::Element_Data_Definition_Handle(Element_Data_Definition_Handle const& other) = default;
saklib::internal::Element_Data_Definition_Handle& saklib::internal::Element_Data_Definition_Handle::operator=(Element_Data_Definition_Handle const& other) = default;

saklib::internal::Element_Data_Definition_Handle::Element_Data_Definition_Handle(Element_Data_Definition_Handle && other) :
    m_reference_counter(std::move(other.m_reference_counter))
{
}

saklib::internal::Element_Data_Definition_Handle& saklib::internal::Element_Data_Definition_Handle::operator=(Element_Data_Definition_Handle && other)
{
    if (&other != this)
    {
        m_reference_counter = std::move(other.m_reference_counter);
    }
    return *this;
}

// Interface
//============================================================
bool saklib::internal::Element_Data_Definition_Handle::is_valid() const
{
    return m_reference_counter.is_valid();
}

bool saklib::internal::Element_Data_Definition_Handle::is_null() const
{
    return m_reference_counter.is_null();
}

std::size_t saklib::internal::Element_Data_Definition_Handle::cget_reference_count() const
{
    return m_reference_counter.cget_storage()->cget_reference_count(m_reference_counter.cget_handle());
}


//data interface
// what should it be?

saklib::internal::Element_Data_Definition const& saklib::internal::Element_Data_Definition_Handle::cget_definition() const
{
    if(is_null())
    {
        throw Bad_Data_Handle();
    }
    return m_reference_counter.cget_storage()->cget_data<0>(m_reference_counter.cget_handle());
}

// Comparison Operators
//============================================================
bool saklib::internal::Element_Data_Definition_Handle::operator==(Element_Data_Definition_Handle const& rhs)
{
    return m_reference_counter == rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Definition_Handle::operator!=(Element_Data_Definition_Handle const& rhs)
{
    return m_reference_counter != rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Definition_Handle::operator<(Element_Data_Definition_Handle const& rhs)
{
    return m_reference_counter < rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Definition_Handle::operator>(Element_Data_Definition_Handle const& rhs)
{
    return m_reference_counter > rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Definition_Handle::operator<=(Element_Data_Definition_Handle const& rhs)
{
    return m_reference_counter <= rhs.m_reference_counter;
}

bool saklib::internal::Element_Data_Definition_Handle::operator>=(Element_Data_Definition_Handle const& rhs)
{
    return m_reference_counter >= rhs.m_reference_counter;
}

// Comparison Operators for compare to the null handle
//============================================================
bool saklib::internal::Element_Data_Definition_Handle::operator==(Null_Integer_ID_Type const& rhs)
{
    return m_reference_counter == rhs;
}

bool saklib::internal::Element_Data_Definition_Handle::operator!=(Null_Integer_ID_Type const& rhs)
{
    return m_reference_counter != rhs;
}


