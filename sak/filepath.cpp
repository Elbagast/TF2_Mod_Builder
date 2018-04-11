#include "filepath.hpp"

//---------------------------------------------------------------------------
// Filepath
//---------------------------------------------------------------------------
// Stores a filepath, which may or may not be incomplete. Uses copy on write.

// Special 6
//============================================================
sak::Filepath::Filepath() :
  m_data{std::make_shared<std::experimental::filesystem::v1::path>()}
{}

sak::Filepath::Filepath(std::experimental::filesystem::v1::path const& a_data) :
  m_data{std::make_shared<std::experimental::filesystem::v1::path>(a_data)}
{}

sak::Filepath::Filepath(std::string const& a_data) :
  m_data{std::make_shared<std::experimental::filesystem::v1::path>(std::experimental::filesystem::v1::u8path(a_data))}
{}

sak::Filepath::Filepath(Filepath const& a_other) = default;
sak::Filepath& sak::Filepath::operator=(Filepath const& a_other) = default;

sak::Filepath::Filepath(Filepath && a_other) = default;
sak::Filepath& sak::Filepath::operator=(Filepath && a_other) = default;

// Interface
//============================================================
bool sak::Filepath::is_empty() const noexcept
{
  return m_data->empty();
}

bool sak::Filepath::is_absolute() const
{
  return m_data->is_absolute();
}

bool sak::Filepath::is_relative() const
{
  return m_data->is_relative();
}

std::string sak::Filepath::to_std_string() const
{
  return m_data->u8string();
}

// Swap the data.
void sak::Filepath::swap(Filepath& a_other) noexcept
{
  std::swap(m_data, a_other.m_data);
}

// Comparison Operators
//============================================================
bool sak::operator==(Filepath const& a_lhs, Filepath const& a_rhs) noexcept
{
  return *(a_lhs.m_data) < *(a_rhs.m_data);
}

bool sak::operator!=(Filepath const& a_lhs, Filepath const& a_rhs) noexcept
{
  return !operator<(a_lhs,a_rhs);
}

bool sak::operator<(Filepath const& a_lhs, Filepath const& a_rhs) noexcept
{
  return *(a_lhs.m_data) < *(a_rhs.m_data);
}

bool sak::operator>(Filepath const& a_lhs, Filepath const& a_rhs) noexcept
{
  return operator<(a_rhs,a_lhs);
}

bool sak::operator<=(Filepath const& a_lhs, Filepath const& a_rhs) noexcept
{
  return !operator>(a_lhs, a_rhs);
}

bool sak::operator>=(Filepath const& a_lhs, Filepath const& a_rhs) noexcept
{
  return !operator<(a_lhs,a_rhs);
}

// Non-member Interface
//============================================================
void sak::swap(Filepath& a_lhs, Filepath& a_rhs) noexcept
{
  a_lhs.swap(a_rhs);
}
