#include "elementid.h"

/*
#include "element.h"
#include "element_manager.h"
#include <cassert>

// Special 6
//============================================================
Saklib::ElementID::ElementID(Element_Manager* manager) :
	mp_manager(manager),
    m_value(invalid_id())
{}
Saklib::ElementID::ElementID(Element_Manager* manager, String const& type) :
	mp_manager(manager),
	m_value(manager ? manager->make_new_id(type) : invalid_id())
{
    // Increment the ref count of the new value
	increment_value(mp_manager, m_value);
}
Saklib::ElementID::~ElementID()
{
    // Decrement the ref count of the value and data flag
	decrement_value(mp_manager, m_value);
}

Saklib::ElementID::ElementID(ElementID const& other) :
	mp_manager{ other.mp_manager },
    m_value{ other.m_value }
{
    // Increment the ref count of the copied value
	increment_value(mp_manager, m_value);
}
Saklib::ElementID& Saklib::ElementID::operator=(ElementID const& other)
{
    // check for equivalence rather than self assignment
    if (m_value != other.m_value)
    {
        // Local copy the old values
		Element_Manager* old_manager = mp_manager;
        id_type old_value = m_value;

        // Set member values to that of other
        m_value = other.m_value;

        // Increment the ref count of the copied value
		increment_value(mp_manager, m_value);

        // Decrement the ref count of the old value
		decrement_value(old_manager, old_value);
    }
    return *this;
}
Saklib::ElementID::ElementID(ElementID && other) :
	mp_manager{ std::move(other.mp_manager) },
    m_value{ std::move(other.m_value) }
{
	other.mp_manager = nullptr;
	other.m_value = invalid_id();
    // no ref count change
}
Saklib::ElementID& Saklib::ElementID::operator=(ElementID && other)
{
    // Local copy the old values
	Element_Manager* old_manager = mp_manager;
    id_type old_value = m_value;

    // Set member values to that of other
	mp_manager = std::move(other.mp_manager);
    m_value = std::move(other.m_value);

    // Invalidate member values of other
	other.mp_manager = nullptr;
	other.m_value = invalid_id();

    // Decrement the ref count of the old value
	decrement_value(old_manager, old_value);

    return *this;
}

// Interface
//============================================================
// The underlying id number
Saklib::id_type Saklib::ElementID::value() const
{
    return m_value;
}
// How many ElementIDs have the same value as this?
Saklib::size_type Saklib::ElementID::ref_count() const
{
	if (is_valid())
		return mp_manager->ref_count(m_value);
	else
		return invalid_id();
}
// Is the stored id number valid? 
bool Saklib::ElementID::is_valid() const
{
	return mp_manager != nullptr && m_value != invalid_id();
}


Saklib::Element& Saklib::ElementID::element()
{
	if (is_valid())
		return mp_manager->element(m_value);
	else
		assert(false);
}
Saklib::Element const& Saklib::ElementID::element() const
{
	if (is_valid())
		return mp_manager->element(m_value);
	else
		assert(false);
}
std::size_t Saklib::ElementID::attribute_count() const
{
    if (is_valid())
        return element().attribute_count();
    else
        return 0;
}
Saklib::Vector_String Saklib::ElementID::attribute_names() const
{
    Vector<String> result{};
    if (is_valid())
        return element().attribute_names();
    return result;
}

Saklib::Attribute* Saklib::ElementID::attribute(std::string const& attributeName) const
{
    return mp_manager->element(m_value).attribute(attributeName);
}

// Initialisation Helpers
//============================================================
void Saklib::ElementID::increment_value(Element_Manager* manager, id_type value)
{
    // Increment the ref count of the copied value
	if (manager != nullptr && value != invalid_id())
    {
		manager->increment_ref_count(value);
    }
}
void Saklib::ElementID::decrement_value(Element_Manager* manager, id_type value)
{
    // Decrement the ref count of the value and data flag
	if (manager != nullptr && value != invalid_id())
    {
		manager->decrement_ref_count(value);
    }
}
*/
