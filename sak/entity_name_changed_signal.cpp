#include "entity_name_changed_signal.hpp"

//---------------------------------------------------------------------------
// Entity_Name_Changed_Signal
//---------------------------------------------------------------------------
// Signal that indicates an Entity with a given id has had its name changed.

// Special 6
//============================================================
sak::Entity_Name_Changed_Signal::Entity_Name_Changed_Signal(Signal_Source a_source, Entity_ID a_id, QString const& a_old_name, QString const& a_new_name) :
  Abstract_Entity_Signal(a_source, Signal_Type::Entity_Name_Changed, a_id),
  m_old_name{a_old_name},
  m_new_name{a_new_name}
{}

sak::Entity_Name_Changed_Signal::~Entity_Name_Changed_Signal() = default;

// Interface
//============================================================
QString const& sak::Entity_Name_Changed_Signal::old_name() const
{
  return m_old_name;
}

QString const& sak::Entity_Name_Changed_Signal::new_name() const
{
  return m_new_name;
}
