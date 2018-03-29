#ifndef SAK_ENTITY_EDITOR_REQUEST_SIGNAL_HPP
#define SAK_ENTITY_EDITOR_REQUEST_SIGNAL_HPP

#ifndef SAK_ABSTRACT_ENTITY_SIGNAL_HPP
#include "abstract_entity_signal.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Entity_Editor_Request_Signal
  //---------------------------------------------------------------------------
  // Signal that indicates an Entity with a given id is requesting to have its
  // editor opened or brought into focus.

  class Entity_Editor_Request_Signal :
      public Abstract_Entity_Signal
  {
  public:
    // Special 6
    //============================================================
    Entity_Editor_Request_Signal(Signal_Source a_source, Entity_ID a_id);
    ~Entity_Editor_Request_Signal() override final;

    // Interface
    //============================================================
    using Abstract_Entity_Signal::source;
    using Abstract_Entity_Signal::type;
    using Abstract_Entity_Signal::id;
  };
}

#endif // SAK_ENTITY_EDITOR_REQUEST_SIGNAL_HPP
