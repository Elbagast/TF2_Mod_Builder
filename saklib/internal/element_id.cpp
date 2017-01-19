#include "element_id.h"

//---------------------------------------------------------------------------
// Element_ID
//---------------------------------------------------------------------------

// Special 6
//============================================================
saklib::internal::Element_ID::Element_ID():
    m_id{}
{}

saklib::internal::Element_ID::Element_ID(value_type a_value):
    m_id{a_value}
{}

saklib::internal::Element_ID::Element_ID(id_type a_id):
    m_id{a_id}
{}

saklib::internal::Element_ID::~Element_ID() = default;

saklib::internal::Element_ID::Element_ID(Element_ID const& a_other) = default;

saklib::internal::Element_ID& saklib::internal::Element_ID::operator=(Element_ID const& a_other) = default;


saklib::internal::Element_ID::Element_ID(Element_ID && a_other):
    m_id{std::move(a_other.m_id)}
{
}

saklib::internal::Element_ID& saklib::internal::Element_ID::operator=(Element_ID && a_other)
{
    m_id = std::move(a_other.m_id);
    return *this;
}

// Interface
//============================================================
bool saklib::internal::Element_ID::is_valid() const
{
    return m_id.is_valid();
}

bool saklib::internal::Element_ID::is_null() const
{
    return m_id.is_null();
}

saklib::internal::Element_ID::value_type saklib::internal::Element_ID::get_value() const
{
    return m_id.get_value();
}

saklib::internal::Element_ID::operator bool() const
{
    return is_valid();
}

saklib::internal::Element_ID::value_type saklib::internal::Element_ID::get_null_value()
{
    return id_type::get_null_value();
}

// Comparison Operators
//============================================================
bool saklib::internal::operator==(Element_ID lhs, Element_ID rhs)
{
    return lhs.get_value() == rhs.get_value();
}

bool saklib::internal::operator!=(Element_ID lhs, Element_ID rhs)
{
    return !operator==(lhs, rhs);
}

bool saklib::internal::operator<(Element_ID lhs, Element_ID rhs)
{
    return lhs.get_value() < rhs.get_value();
}

bool saklib::internal::operator>(Element_ID lhs, Element_ID rhs)
{
    return operator<(rhs, lhs);
}

bool saklib::internal::operator<=(Element_ID lhs, Element_ID rhs)
{
    return !operator>(lhs, rhs);
}

bool saklib::internal::operator>=(Element_ID lhs, Element_ID rhs)
{
    return !operator<(lhs, rhs);
}


//---------------------------------------------------------------------------
// Element_ID_Factory<T>
//---------------------------------------------------------------------------

// Special 6
//============================================================

saklib::internal::Element_ID_Factory::Element_ID_Factory() :
    m_factory{}
{}

// Interface
//============================================================
saklib::internal::Element_ID saklib::internal::Element_ID_Factory::make_null_id()
{
    return Element_ID();
}

saklib::internal::Element_ID saklib::internal::Element_ID_Factory::issue_id()
{
    return Element_ID(m_factory.issue_id());
}

void saklib::internal::Element_ID_Factory::revoke_id(Element_ID a_id)
{
    m_factory.revoke_id(a_id.m_id);
}
