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
bool saklib::internal::Element_Data_Manager::has_element(Element_ID a_id) const
{
    return m_storage.has_data(a_id);
}

saklib::internal::Element_Data_Handle saklib::internal::Element_Data_Manager::make_element_handle(Element_ID a_id)
{
    if (has_element(a_id))
    {
        return Element_Data_Handle(this, m_storage.make_handle(a_id));
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
        auto new_id = m_id_factory.issue_id();
        auto new_reference_counter = m_storage.emplace_data(new_id, Element_Data(a_definition_handle.cget_definition()), std::move(a_definition_handle));
        assert(new_reference_counter.is_valid());
        return Element_Data_Handle(this, std::move(new_reference_counter));
    }
    else
    {
        return Element_Data_Handle();
    }
}

std::size_t saklib::internal::Element_Data_Manager::cget_reference_count(Element_ID a_id) const
{
    return m_storage.cget_reference_count(a_id);
}

std::vector<saklib::internal::Element_ID> saklib::internal::Element_Data_Manager::cget_all_element_ids() const
{
    return m_storage.cget_all_handles();
}

std::vector<saklib::internal::Element_Data_Handle> saklib::internal::Element_Data_Manager::make_all_element_handles()
{
    auto all_ids = cget_all_element_ids();
    std::vector<Element_Data_Handle> l_result{};
    l_result.reserve(all_ids.size());
    for (auto l_id : all_ids)
    {
        l_result.emplace_back(this, m_storage.make_handle(l_id));
    }
    return l_result;
}
