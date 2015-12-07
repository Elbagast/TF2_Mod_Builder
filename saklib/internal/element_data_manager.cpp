#include "element_data_manager.h"

#include "element_data_handle.h"
#include "all_attribute_data_handle.h"
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

saklib::internal::Element_Data_Handle<saklib::internal::Element_Data_Manager::this_type> saklib::internal::Element_Data_Manager::make_element_handle(handle_type const& a_handle)
{
    if (has_element(a_handle))
    {
        return Element_Data_Handle<this_type>(this, m_storage.make_handle(a_handle));
    }
    else
    {
        return Element_Data_Handle<this_type>();
    }
}

saklib::internal::Element_Data_Handle<saklib::internal::Element_Data_Manager::this_type> saklib::internal::Element_Data_Manager::make_element(Element_Data_Definition_Handle&& a_definition_handle)
{
    if (a_definition_handle.is_valid())
    {
        auto new_handle = m_handle_factory.make_new_handle();
        auto new_reference_counter = m_storage.emplace_data(new_handle, Element_Data(a_definition_handle.cget_definition()), std::move(a_definition_handle));
        assert(new_reference_counter.is_valid());
        return Element_Data_Handle<this_type>(this, std::move(new_reference_counter));
    }
    else
    {
        return Element_Data_Handle<this_type>();
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

std::vector<saklib::internal::Element_Data_Handle<saklib::internal::Element_Data_Manager::this_type>> saklib::internal::Element_Data_Manager::make_all_element_handles()
{
    auto all_handles = cget_all_handles();
    std::vector<Element_Data_Handle<this_type>> l_result{};
    l_result.reserve(all_handles.size());
    for (auto const& handle : all_handles)
    {
        l_result.push_back(Element_Data_Handle<this_type>(this, make_reference_counter(handle)));
    }
    return l_result;
}

// Element_Data Wrapper Interface
//============================================================
std::string const& saklib::internal::Element_Data_Manager::element_cget_type(handle_type const& a_handle) const
{
    return cget_element(a_handle).cget_type();
}

std::string const& saklib::internal::Element_Data_Manager::element_cget_name(handle_type const& a_handle) const
{
    return cget_element(a_handle).cget_name();
}

void saklib::internal::Element_Data_Manager::element_set_name(handle_type const& a_handle, std::string const& a_name)
{
    return get_element(a_handle).set_name(a_name);
}

std::size_t saklib::internal::Element_Data_Manager::element_cget_attribute_count(handle_type const& a_handle) const
{
    return cget_element(a_handle).cget_attribute_count();
}

bool saklib::internal::Element_Data_Manager::element_has_attribute(handle_type const& a_handle, std::size_t a_index) const
{
    return has_element(a_handle) && a_index < element_cget_attribute_count(a_handle);
}

saklib::internal::Attribute_Data_Handle<saklib::internal::Element_Data_Manager::this_type> saklib::internal::Element_Data_Manager::element_cget_attribute_at(handle_type const& a_handle, std::size_t a_index) const
{
    if (element_has_attribute(a_handle, a_index))
    {
        return Attribute_Data_Handle<this_type>(const_cast<this_type*>(this), make_reference_counter(a_handle), a_index);
    }
    else
    {
        return Attribute_Data_Handle<this_type>();
    }
}

std::vector<saklib::internal::Attribute_Data_Handle<saklib::internal::Element_Data_Manager::this_type>> saklib::internal::Element_Data_Manager::element_cget_attributes(handle_type const& a_handle) const
{
    std::vector<Attribute_Data_Handle<this_type>> l_result{};
    auto const l_attribute_count = element_cget_attribute_count(a_handle);
    l_result.reserve(l_attribute_count);
    for (std::size_t l_index = 0; l_index < l_attribute_count; ++l_index)
    {
        l_result.emplace_back(const_cast<this_type*>(this), make_reference_counter(a_handle), l_index);
    }
    return l_result;
}

// Attribute_Data Wrapper Interface
//============================================================
std::string const& saklib::internal::Element_Data_Manager::attribute_cget_name(handle_type const& a_handle, std::size_t a_index) const
{
    return cget_attribute(a_handle, a_index).cget_name();
}

std::string const& saklib::internal::Element_Data_Manager::attribute_cget_type(handle_type const& a_handle, std::size_t a_index) const
{
    return cget_attribute(a_handle, a_index).cget_type();
}

std::string saklib::internal::Element_Data_Manager::attribute_cget_value_string(handle_type const& a_handle, std::size_t a_index) const
{
    return cget_attribute(a_handle, a_index).cget_value_string();
}

bool saklib::internal::Element_Data_Manager::attribute_is_bool(handle_type const& a_handle, std::size_t a_index) const
{
    return attribute_is_bool_type<bool>(a_handle, a_index);
}

bool saklib::internal::Element_Data_Manager::attribute_is_int(handle_type const& a_handle, std::size_t a_index) const
{
    return attribute_is_int_type<int>(a_handle, a_index);
}

saklib::internal::Attribute_Data_Handle_Boolean_Type<bool, saklib::internal::Element_Data_Manager::this_type> saklib::internal::Element_Data_Manager::attribute_cget_bool(handle_type const& a_handle, std::size_t a_index) const
{
    return attribute_cget_bool_type<bool>(a_handle, a_index);
}

saklib::internal::Attribute_Data_Handle_Integral_Type<int, saklib::internal::Element_Data_Manager::this_type> saklib::internal::Element_Data_Manager::attribute_cget_int(handle_type const& a_handle, std::size_t a_index) const
{
    return attribute_cget_int_type<int>(a_handle, a_index);
}

template <typename T>
bool saklib::internal::Element_Data_Manager::attribute_is_bool_type(handle_type const& a_handle, std::size_t a_index) const
{
    return cget_attribute(a_handle, a_index).is_bool_type<T>();
}

template <typename T>
bool saklib::internal::Element_Data_Manager::attribute_is_int_type(handle_type const& a_handle, std::size_t a_index) const
{
    return cget_attribute(a_handle, a_index).is_int_type<T>();
}

template <typename T>
saklib::internal::Attribute_Data_Handle_Boolean_Type<T, saklib::internal::Element_Data_Manager::this_type> saklib::internal::Element_Data_Manager::attribute_cget_bool_type(handle_type const& a_handle, std::size_t a_index) const
{
    if (element_has_attribute(a_handle, a_index) && attribute_is_bool_type<T>(a_handle, a_index))
    {
        return Attribute_Data_Handle_Boolean_Type<T, this_type>(const_cast<this_type*>(this), make_reference_counter(a_handle), a_index);
    }
    else
    {
        return Attribute_Data_Handle_Boolean_Type<T, this_type>();
    }
}

template <typename T>
saklib::internal::Attribute_Data_Handle_Integral_Type<T, saklib::internal::Element_Data_Manager::this_type> saklib::internal::Element_Data_Manager::attribute_cget_int_type(handle_type const& a_handle, std::size_t a_index) const
{
    if (element_has_attribute(a_handle, a_index) && attribute_is_int_type<T>(a_handle, a_index))
    {
        return Attribute_Data_Handle_Integral_Type<T, this_type>(const_cast<this_type*>(this), make_reference_counter(a_handle), a_index);
    }
    else
    {
        return Attribute_Data_Handle_Integral_Type<T, this_type>();
    }
}

// Attribute_Data_Boolean_Type<T> Wrapper Interface
//============================================================
template <typename T>
T saklib::internal::Element_Data_Manager::attribute_bool_type_cget_value(handle_type const& a_handle, std::size_t a_index) const
{
    return cget_attribute_bool_type<T>(a_handle, a_index).cget_value();
}

template <typename T>
bool saklib::internal::Element_Data_Manager::attribute_bool_type_can_set_value_to(handle_type const& a_handle, std::size_t a_index, T a_value) const
{
    return cget_attribute_bool_type<T>(a_handle, a_index).can_set_value_to(a_value);
}

template <typename T>
bool saklib::internal::Element_Data_Manager::attribute_bool_type_try_set_value(handle_type const& a_handle, std::size_t a_index, T a_value)
{
    return cget_attribute_bool_type<T>(a_handle, a_index).try_set_value(a_value);
}

template <typename T>
void saklib::internal::Element_Data_Manager::attribute_bool_type_set_value(handle_type const& a_handle, std::size_t a_index, T a_value)
{
    cget_attribute_bool_type<T>(a_handle, a_index).set_value(a_value);
}

// Attribute_Data_Integral_Type<T> Wrapper Interface
//============================================================
template <typename T>
T saklib::internal::Element_Data_Manager::attribute_int_type_cget_value(handle_type const& a_handle, std::size_t a_index) const
{
    return cget_attribute_int_type<T>(a_handle, a_index).cget_value();
}

template <typename T>
bool saklib::internal::Element_Data_Manager::attribute_int_type_can_set_value_to(handle_type const& a_handle, std::size_t a_index, T a_value) const
{
    return cget_attribute_int_type<T>(a_handle, a_index).can_set_value_to(a_value);
}

template <typename T>
bool saklib::internal::Element_Data_Manager::attribute_int_type_try_set_value(handle_type const& a_handle, std::size_t a_index, T a_value)
{
    return cget_attribute_int_type<T>(a_handle, a_index).try_set_value(a_value);
}

template <typename T>
void saklib::internal::Element_Data_Manager::attribute_int_type_set_value(handle_type const& a_handle, std::size_t a_index, T a_value)
{
    cget_attribute_int_type<T>(a_handle, a_index).set_value(a_value);
}

template <typename T>
T saklib::internal::Element_Data_Manager::attribute_int_type_cget_lowest_value(handle_type const& a_handle, std::size_t a_index) const
{
    return cget_attribute_int_type<T>(a_handle, a_index).cget_lowest_value();
}

template <typename T>
T saklib::internal::Element_Data_Manager::attribute_int_type_cget_highest_value(handle_type const& a_handle, std::size_t a_index) const
{
    return cget_attribute_int_type<T>(a_handle, a_index).cget_highest_value();
}

// Private Helpers
//============================================================
saklib::internal::Element_Data_Manager::reference_counter_type saklib::internal::Element_Data_Manager::make_reference_counter(handle_type const& a_handle) const
{
    return m_storage.make_handle(a_handle);
}

saklib::internal::Element_Data& saklib::internal::Element_Data_Manager::get_element(handle_type const& a_handle)
{
    return m_storage.get_data(a_handle);
}

saklib::internal::Element_Data const& saklib::internal::Element_Data_Manager::cget_element(handle_type const& a_handle) const
{
    return m_storage.cget_data(a_handle);
}

saklib::internal::Attribute_Data& saklib::internal::Element_Data_Manager::get_attribute(handle_type const& a_handle, std::size_t a_index)
{
    return get_element(a_handle).get_attribute_at(a_index);
}

saklib::internal::Attribute_Data const& saklib::internal::Element_Data_Manager::cget_attribute(handle_type const& a_handle, std::size_t a_index) const
{
    return cget_element(a_handle).cget_attribute_at(a_index);
}

template <typename T>
saklib::internal::Attribute_Data_Boolean_Type<T>& saklib::internal::Element_Data_Manager::get_attribute_bool_type(handle_type const& a_handle, std::size_t a_index)
{
    return get_attribute(a_handle, a_index).get_bool_type<T>();
}

template <typename T>
saklib::internal::Attribute_Data_Boolean_Type<T> const& saklib::internal::Element_Data_Manager::cget_attribute_bool_type(handle_type const& a_handle, std::size_t a_index) const
{
    return cget_attribute(a_handle, a_index).cget_bool_type<T>();
}

template <typename T>
saklib::internal::Attribute_Data_Integral_Type<T>& saklib::internal::Element_Data_Manager::get_attribute_int_type(handle_type const& a_handle, std::size_t a_index)
{
    return get_attribute(a_handle, a_index).get_int_type<T>();
}

template <typename T>
saklib::internal::Attribute_Data_Integral_Type<T> const& saklib::internal::Element_Data_Manager::cget_attribute_int_type(handle_type const& a_handle, std::size_t a_index) const
{
    return cget_attribute(a_handle, a_index).cget_int_type<T>();
}
