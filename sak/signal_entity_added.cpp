#include "signal_entity_added.hpp"

//---------------------------------------------------------------------------
// Signal_Entity_Added
//---------------------------------------------------------------------------
// Signal that indicates an Entity with a given id was added to the project.

// Special 6
//============================================================
sak::Signal_Entity_Added::Signal_Entity_Added(Signal_Source a_source,
                                                  Entity_ID a_id) :
  Abstract_Entity_Signal(a_source, Signal_Type::Entity_Added, a_id)
{
}

sak::Signal_Entity_Added::~Signal_Entity_Added() = default;
