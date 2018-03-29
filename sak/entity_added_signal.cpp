#include "entity_added_signal.hpp"

//---------------------------------------------------------------------------
// Entity_Added_Signal
//---------------------------------------------------------------------------
// Signal that indicates an Entity with a given id was added to the project.

// Special 6
//============================================================
sak::Entity_Added_Signal::Entity_Added_Signal(Signal_Source a_source,
                                                  Entity_ID a_id) :
  Abstract_Entity_Signal(a_source, Signal_Type::Entity_Added, a_id)
{
}

sak::Entity_Added_Signal::~Entity_Added_Signal() = default;
