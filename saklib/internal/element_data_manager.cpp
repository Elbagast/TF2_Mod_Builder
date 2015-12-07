#include "element_data_manager.h"

//#include "element_data.h"
//#include "all_attribute_data_.h"

#include "element_data_handle.h"
//#include "all_attribute_data_handle.h"

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
        return Element_Data_Handle(this, m_storage.make_handle(a_handle));
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
        assert(new_reference_counter.is_valid());
        return Element_Data_Handle(this, std::move(new_reference_counter));
    }
    else
    {
        return Element_Data_Handle();
    }
}

std::size_t saklib::internal::Element_Data_Manager::cget_reference_count(handle_type const& a_handle) const
{
    return m_storage.cget_reference_count(a_handle);
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
    for (auto const& l_handle : all_handles)
    {
        l_result.emplace_back(this, m_storage.make_handle(l_handle));
    }
    return l_result;
}
