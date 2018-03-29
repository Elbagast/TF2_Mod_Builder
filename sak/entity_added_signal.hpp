#ifndef SAK_ENTITY_ADDED_SIGNAL_HPP
#define SAK_ENTITY_ADDED_SIGNAL_HPP

#ifndef SAK_ABSTRACT_ENTITY_SIGNAL_HPP
#include "abstract_entity_signal.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Entity_Added_Signal
  //---------------------------------------------------------------------------
  // Signal that indicates an Entity with a given id was added to the project.

  class Entity_Added_Signal :
      public Abstract_Entity_Signal
  {
  public:
    // Special 6
    //============================================================
    Entity_Added_Signal(Signal_Source a_source, Entity_ID a_id);
    ~Entity_Added_Signal() override final;

    // Interface
    //============================================================
    using Abstract_Entity_Signal::source;
    using Abstract_Entity_Signal::type;
    using Abstract_Entity_Signal::id;
  };
}

#endif // SAK_ENTITY_ADDED_SIGNAL_HPP
