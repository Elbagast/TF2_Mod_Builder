#include "signal_entity.hpp"

//---------------------------------------------------------------------------
// Signal_Entity
//---------------------------------------------------------------------------
// Class for a signal that relates to a specific Entity. This class is also
// derived from so that more complicated signals can store an Entity_ID in
// addition to other data.

// Special 6
//============================================================
sak::Signal_Entity::Signal_Entity(Signal_Source a_source, Signal_Type a_type, Entity_ID a_id) :
  Signal(a_source, a_type),
  m_id{a_id}
{
}

sak::Signal_Entity::~Signal_Entity() = default;

// Interface
//============================================================
sak::Entity_ID sak::Signal_Entity::id() const noexcept
{
  return m_id;
}

sak::Signal_Entity sak::make_signal_entity_outliner_request(Signal_Source a_source, Entity_ID a_id)
{
  return Signal_Entity{a_source, Signal_Type::Entity_Outliner_Request, a_id};
}

sak::Signal_Entity sak::make_signal_entity_editor_request(Signal_Source a_source, Entity_ID a_id)
{
  return Signal_Entity{a_source, Signal_Type::Entity_Editor_Request, a_id};
}

sak::Signal_Entity sak::make_signal_entity_added(Signal_Source a_source, Entity_ID a_id)
{
  return Signal_Entity{a_source, Signal_Type::Entity_Added, a_id};
}

sak::Signal_Entity sak::make_signal_entity_removed(Signal_Source a_source, Entity_ID a_id)
{
  return Signal_Entity{a_source, Signal_Type::Entity_Removed, a_id};
}
