#include "signal_entity_name_changed.hpp"

//---------------------------------------------------------------------------
// Signal_Entity_Name_Changed
//---------------------------------------------------------------------------
// Signal that indicates an Entity with a given id has had its name changed.

// Special 6
//============================================================
sak::Signal_Entity_Name_Changed::Signal_Entity_Name_Changed(Signal_Source a_source, Entity_ID a_id, std::string const& a_old_name, std::string const& a_new_name) :
  Signal_Entity(a_source, Signal_Type::Entity_Name_Changed, a_id),
  m_old_name{a_old_name},
  m_new_name{a_new_name}
{}

sak::Signal_Entity_Name_Changed::~Signal_Entity_Name_Changed() = default;

// Interface
//============================================================
std::string const& sak::Signal_Entity_Name_Changed::old_name() const noexcept
{
  return m_old_name;
}

std::string const& sak::Signal_Entity_Name_Changed::new_name() const noexcept
{
  return m_new_name;
}
