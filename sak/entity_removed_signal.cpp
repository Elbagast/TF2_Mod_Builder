#include "entity_removed_signal.hpp"

//---------------------------------------------------------------------------
// Entity_Removed_Signal
//---------------------------------------------------------------------------
// Signal that indicates an Entity with a given id was removed from the project.

// Special 6
//============================================================
sak::Entity_Removed_Signal::Entity_Removed_Signal(Signal_Source a_source,
                                                  Entity_ID a_id) :
  Abstract_Entity_Signal(a_source, Signal_Type::Entity_Added, a_id)
{
}

sak::Entity_Removed_Signal::~Entity_Removed_Signal() = default;
