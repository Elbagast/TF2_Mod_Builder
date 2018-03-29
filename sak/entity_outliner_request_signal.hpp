#ifndef SAK_ENTITY_OUTLINER_REQUEST_SIGNAL_HPP
#define SAK_ENTITY_OUTLINER_REQUEST_SIGNAL_HPP

#ifndef SAK_ABSTRACT_ENTITY_SIGNAL_HPP
#include "abstract_entity_signal.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Entity_Outliner_Request_Signal
  //---------------------------------------------------------------------------
  // Signal that indicates an Entity with a given id is requesting focus in the
  // Project outliner.

  class Entity_Outliner_Request_Signal :
      public Abstract_Entity_Signal
  {
  public:
    // Special 6
    //============================================================
    Entity_Outliner_Request_Signal(Signal_Source a_source, Entity_ID a_id);
    ~Entity_Outliner_Request_Signal() override final;

    // Interface
    //============================================================
    using Abstract_Entity_Signal::source;
    using Abstract_Entity_Signal::type;
    using Abstract_Entity_Signal::id;
  };
}

#endif // SAK_ENTITY_OUTLINER_REQUEST_SIGNAL_HPP
