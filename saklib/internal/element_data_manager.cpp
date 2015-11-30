#include "element_data_manager.h"

#include "exceptions/bad_element_data_type.h"
#include <limits>

//---------------------------------------------------------------------------
// Element_Definition_Data_Manager
//---------------------------------------------------------------------------

// Interface
//============================================================
// Attempt to add this definition. If a definition with a type the same as the
// new one already exists, this will not be added and returns false. If it is
// added, it returns true. Definitions can have the same configuration, so long
// as they have different types.
bool saklib::internal::Element_Definition_Data_Manager::add_definition(Element_Data_Definition const& a_definition)
{
    std::string l_type{a_definition.cget_type()};
    if (!has_definition(l_type))
    {
        m_map.emplace(l_type, tuple_type(a_definition, 0));
        return true;
    }
    else
    {
        return false;
    }
}

// Is there a definition with this type?
bool saklib::internal::Element_Definition_Data_Manager::has_definition(std::string const& a_type) const
{
    return m_map.find(a_type) != m_map.cend();
}

// Get a definition, throw an exception if there isn't one
saklib::internal::Element_Data_Definition const& saklib::internal::Element_Definition_Data_Manager::cget_definition(std::string const& a_type) const
{
    auto const found = m_map.find(a_type);
    if (found != m_map.end())
    {
        return cget_iterator_data(found);
    }
    else
    {
        throw Bad_Element_Data_Type(a_type);
    }
}

// The number of Elements that have been made using this definition.
std::size_t saklib::internal::Element_Definition_Data_Manager::get_definition_usage_count(std::string const& a_type) const
{
    auto const found = m_map.find(a_type);
    if (found != m_map.end())
    {
        return cget_iterator_usage_count(found);
    }
    else
    {
        return 0;
    }
}

// Can this definition corresponding to this type be removed? A definition can
// only be removed if it exists and it has a usage count of 0. If these are
// both true then true is returned. If there is no such definition or it has
// a usage count above 0 then false is returned.
bool saklib::internal::Element_Definition_Data_Manager::can_remove_definition(std::string const& a_type) const
{
    auto const found = m_map.find(a_type);
    return found != m_map.cend() && cget_iterator_usage_count(found) == 0;
}

// Try and remove the definition corresponding to this type. This function
// calls can_remove_definition() and only removes the definition if the result
// of that is true. If the remove cannot happen or fails then this function
// return false, otherwise the definition corresponding to this type is
// removed.
bool saklib::internal::Element_Definition_Data_Manager::remove_definition(std::string const& a_type)
{
    if (can_remove_definition(a_type))
    {
        m_map.erase(a_type);
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::string> saklib::internal::Element_Definition_Data_Manager::get_definition_types() const
{
    std::vector<std::string> l_result{};
    l_result.reserve(m_map.size());
    for (auto const& pair : m_map)
    {
        l_result.push_back(pair.first);
    }
    return l_result;
}

void saklib::internal::Element_Definition_Data_Manager::increment_usage_count(std::string const& a_type)
{
    auto found = m_map.find(a_type);
    if (found != m_map.end())
    {
        auto& found_usage = get_iterator_usage_count(found);
        if (found_usage != std::numeric_limits<std::size_t>::max())
        {
            found_usage += 1;
        }
    }
}

void saklib::internal::Element_Definition_Data_Manager::decrement_usage_count(std::string const& a_type)
{
    auto found = m_map.find(a_type);
    if (found != m_map.end())
    {
        auto& found_usage = get_iterator_usage_count(found);
        if (found_usage != 0)
        {
            found_usage -= 1;
        }
    }
}

saklib::internal::Element_Data_Definition& saklib::internal::Element_Definition_Data_Manager::get_iterator_data(map_type::iterator a_iterator)
{
    return std::get<0>(a_iterator->second);
}

saklib::internal::Element_Data_Definition const& saklib::internal::Element_Definition_Data_Manager::cget_iterator_data(map_type::const_iterator a_iterator) const
{
    return std::get<0>(a_iterator->second);
}

std::size_t& saklib::internal::Element_Definition_Data_Manager::get_iterator_usage_count(map_type::iterator a_iterator)
{
    return std::get<1>(a_iterator->second);
}

std::size_t const& saklib::internal::Element_Definition_Data_Manager::cget_iterator_usage_count(map_type::const_iterator a_iterator) const
{
    return std::get<1>(a_iterator->second);
}

//---------------------------------------------------------------------------
// Element_Definition_Data_Release
//---------------------------------------------------------------------------

saklib::internal::Element_Definition_Data_Release::Element_Definition_Data_Release(Element_Definition_Data_Manager& ar_element_definition_manager):
    mp_element_definition_manager{&ar_element_definition_manager}
{}

void saklib::internal::Element_Definition_Data_Release::operator()(Element_Data& a_about_to_destruct)
{
    mp_element_definition_manager->decrement_usage_count(a_about_to_destruct.cget_type());
}

//---------------------------------------------------------------------------
// Element_Data_Manager
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Element_Data_Manager::Element_Data_Manager():
    m_element_definition_manager(),
    m_manager(Element_Definition_Data_Release(m_element_definition_manager))
{}

// Interface
//============================================================
bool saklib::internal::Element_Data_Manager::add_definition(Element_Data_Definition const& a_definition)
{
    return m_element_definition_manager.add_definition(a_definition);
}

bool saklib::internal::Element_Data_Manager::has_definition(std::string const& a_type) const
{
    return m_element_definition_manager.has_definition(a_type);
}

saklib::internal::Element_Data_Definition const& saklib::internal::Element_Data_Manager::cget_definition(std::string const& a_type) const
{
    return m_element_definition_manager.cget_definition(a_type);
}

std::size_t saklib::internal::Element_Data_Manager::get_definition_usage_count(std::string const& a_type) const
{
    return m_element_definition_manager.get_definition_usage_count(a_type);
}

bool saklib::internal::Element_Data_Manager::can_remove_definition(std::string const& a_type) const
{
    return m_element_definition_manager.can_remove_definition(a_type);
}

bool saklib::internal::Element_Data_Manager::remove_definition(std::string const& a_type)
{
    return m_element_definition_manager.remove_definition(a_type);
}

std::vector<std::string> saklib::internal::Element_Data_Manager::get_definition_types() const
{
    return m_element_definition_manager.get_definition_types();
}

saklib::internal::Element_Data_Handle saklib::internal::Element_Data_Manager::make_null_handle() const
{
    return Element_Data_Handle();
}

saklib::internal::Element_Data_Handle saklib::internal::Element_Data_Manager::make_element_handle(std::string const& a_type)
{
    if (has_definition(a_type))
    {
        // should this be a make function?
        Element_Data l_result{m_element_definition_manager.cget_definition(a_type)};
        m_element_definition_manager.increment_usage_count(a_type);
        auto l_smart_handle = m_manager.emplace_data(std::move(l_result));
        return Element_Data_Handle(*this, std::move(l_smart_handle));
    }
    else
    {
        return make_null_handle();
    }
}

std::vector<saklib::internal::Element_Data_Handle> saklib::internal::Element_Data_Manager::make_all_element_handles()
{
    std::vector<Element_Data_Handle> l_result{};
    auto l_smart_handles = m_manager.get_all_handles();
    l_result.reserve(l_smart_handles.size());
    for (auto && smart_handle : l_smart_handles)
    {
        l_result.push_back(Element_Data_Handle(*this, std::move(smart_handle)));
    }
    return l_result;
}

//---------------------------------------------------------------------------
// Element_Handle
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Element_Data_Handle::Element_Data_Handle(Element_Data_Manager& ar_manager, smart_handle_type&& a_smart_handle):
    mp_manager(&ar_manager),
    m_smart_handle(std::forward<smart_handle_type>(a_smart_handle))
{
}

saklib::internal::Element_Data_Handle::Element_Data_Handle():
    mp_manager(nullptr),
    m_smart_handle()
{
}


saklib::internal::Element_Data_Handle::~Element_Data_Handle() = default;

saklib::internal::Element_Data_Handle::Element_Data_Handle(Element_Data_Handle const& other) = default;
saklib::internal::Element_Data_Handle& saklib::internal::Element_Data_Handle::operator=(Element_Data_Handle const& other) = default;

saklib::internal::Element_Data_Handle::Element_Data_Handle(Element_Data_Handle && other):
    mp_manager(std::move(other.mp_manager)),
    m_smart_handle(std::move(other.m_smart_handle))
{
    other.mp_manager = nullptr;
}

saklib::internal::Element_Data_Handle& saklib::internal::Element_Data_Handle::operator=(Element_Data_Handle && other)
{
    mp_manager = std::move(other.mp_manager);
    m_smart_handle = std::move(other.m_smart_handle);

    other.mp_manager = nullptr;

    return *this;
}


// Interface
//============================================================
bool saklib::internal::Element_Data_Handle::is_valid() const
{
    return mp_manager != nullptr && m_smart_handle.is_valid();
}

bool saklib::internal::Element_Data_Handle::is_null() const
{
    return mp_manager == nullptr && m_smart_handle.is_null();
}

saklib::internal::Element_Data_Handle::handle_type saklib::internal::Element_Data_Handle::get_handle() const
{
    return m_smart_handle.cget_handle();
}

saklib::internal::Handle_Value_Type saklib::internal::Element_Data_Handle::get_handle_value() const
{
    return m_smart_handle.cget_handle_value();
}

saklib::internal::Element_Data_Handle::reference_count_type saklib::internal::Element_Data_Handle::get_reference_count() const
{
    return m_smart_handle.cget_reference_count();
}

saklib::internal::Element_Data& saklib::internal::Element_Data_Handle::get_element()
{
    return m_smart_handle.get_data();
}

saklib::internal::Element_Data const& saklib::internal::Element_Data_Handle::cget_element() const
{
    return m_smart_handle.cget_data();
}

saklib::internal::Element_Data_Manager* saklib::internal::Element_Data_Handle::get_manager()
{
    return mp_manager;
}

saklib::internal::Element_Data_Manager const* saklib::internal::Element_Data_Handle::cget_manager() const
{
    return mp_manager;
}

