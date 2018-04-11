#include "string.hpp"
//---------------------------------------------------------------------------
// String
//---------------------------------------------------------------------------
// Unicode string class. Uses copy on write. Mostly just so we can enforce
// specific encoding when we need to.

// For now we just implement it so that the pointer is always valid.

// Special 6
//============================================================
sak::String::String() :
  m_data{std::make_shared<std::string>()}
{}
sak::String::String(std::string const& a_data):
  m_data{std::make_shared<std::string>(a_data)}
{}

sak::String::String(String const& a_other) = default;
sak::String& sak::String::operator=(String const& a_other) = default;

sak::String::String(String && a_other) = default;
sak::String& sak::String::operator=(String && a_other) = default;

// Interface
//============================================================
bool sak::String::is_empty() const noexcept
{
  return m_data->empty();
}

std::string sak::String::to_std_string() const
{
  return *m_data;
}

// Swap the data.
void sak::String::swap(String& a_other) noexcept
{
  std::swap(m_data, a_other.m_data);
}

// Member Operators
//============================================================
/*
bool sak::String::operator ==(String const& a_other) const noexcept
{
  return *m_data == *(a_other.m_data);
}

bool sak::String::operator <(String const& a_other) const noexcept
{
  return *m_data < *(a_other.m_data);
}
*/
// Comparison Operators
//============================================================
bool sak::operator==(String const& a_lhs, String const& a_rhs) noexcept
{
  return *(a_lhs.m_data) == *(a_rhs.m_data);
}

bool sak::operator!=(String const& a_lhs, String const& a_rhs) noexcept
{
  return !operator==(a_lhs,a_rhs);
}

bool sak::operator<(String const& a_lhs, String const& a_rhs) noexcept
{
  return *(a_lhs.m_data) < *(a_rhs.m_data);
}

bool sak::operator>(String const& a_lhs, String const& a_rhs) noexcept
{
  return operator<(a_rhs,a_lhs);
}

bool sak::operator<=(String const& a_lhs, String const& a_rhs) noexcept
{
  return !operator>(a_lhs, a_rhs);
}

bool sak::operator>=(String const& a_lhs, String const& a_rhs) noexcept
{
  return !operator<(a_lhs,a_rhs);
}

bool sak::operator==(String const& a_lhs, std::string const& a_rhs) noexcept
{
  return *(a_lhs.m_data) == a_rhs;
}

bool sak::operator==(std::string const& a_lhs, String const& a_rhs) noexcept
{
  return operator==(a_rhs,a_lhs);
}

bool sak::operator!=(String const& a_lhs, std::string const& a_rhs) noexcept
{
  return !operator==(a_lhs,a_rhs);
}

bool sak::operator!=(std::string const& a_lhs, String const& a_rhs) noexcept
{
  return !operator==(a_lhs,a_rhs);
}

// Non-member Interface
//============================================================
void sak::swap(String& a_lhs, String& a_rhs) noexcept
{
  a_lhs.swap(a_rhs);
}
