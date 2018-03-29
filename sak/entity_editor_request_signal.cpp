#include "entity_editor_request_signal.hpp"

//---------------------------------------------------------------------------
// Entity_Editor_Request_Signal
//---------------------------------------------------------------------------
// Signal that indicates an Entity with a given id is requesting to have its
// editor opened or brought into focus.

// Special 6
//============================================================
sak::Entity_Editor_Request_Signal::Entity_Editor_Request_Signal(Signal_Source a_source, Entity_ID a_id) :
  Abstract_Entity_Signal(a_source, Signal_Type::Entity_Outliner_Request, a_id)
{}

sak::Entity_Editor_Request_Signal::~Entity_Editor_Request_Signal() = default;
