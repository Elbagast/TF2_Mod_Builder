#include "abstract_entity_signal.hpp"

#include <cassert>

//---------------------------------------------------------------------------
// Abstract_Entity_Signal
//---------------------------------------------------------------------------
// Base class for all Project signals that relate to a specific handle.

// Special 6
//============================================================
sak::Abstract_Entity_Signal::Abstract_Entity_Signal(Signal_Source a_source,
                                                    Signal_Type a_type,
                                                    Entity_ID a_id) :
  Abstract_Signal(a_source, a_type),
  m_id{a_id}
{
  assert(not_null(m_id));
}

sak::Abstract_Entity_Signal::~Abstract_Entity_Signal() = default;

// Interface
//============================================================
sak::Entity_ID sak::Abstract_Entity_Signal::id() const
{
  return m_id;
}
