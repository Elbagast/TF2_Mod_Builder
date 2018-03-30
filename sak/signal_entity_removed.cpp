#include "signal_entity_removed.hpp"

//---------------------------------------------------------------------------
// Signal_Entity_Removed
//---------------------------------------------------------------------------
// Signal that indicates an Entity with a given id was removed from the project.

// Special 6
//============================================================
sak::Signal_Entity_Removed::Signal_Entity_Removed(Signal_Source a_source,
                                                  Entity_ID a_id) :
  Abstract_Entity_Signal(a_source, Signal_Type::Entity_Added, a_id)
{
}

sak::Signal_Entity_Removed::~Signal_Entity_Removed() = default;
