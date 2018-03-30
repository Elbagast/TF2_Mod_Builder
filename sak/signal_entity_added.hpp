#ifndef SAK_SIGNAL_ENTITY_ADDED_HPP
#define SAK_SIGNAL_ENTITY_ADDED_HPP

#ifndef SAK_ABSTRACT_ENTITY_SIGNAL_HPP
#include "abstract_entity_signal.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Signal_Entity_Added
  //---------------------------------------------------------------------------
  // Signal that indicates an Entity with a given id was added to the project.

  class Signal_Entity_Added :
      public Abstract_Entity_Signal
  {
  public:
    // Special 6
    //============================================================
    Signal_Entity_Added(Signal_Source a_source, Entity_ID a_id);
    ~Signal_Entity_Added() override final;

    // Interface
    //============================================================
    using Abstract_Entity_Signal::source;
    using Abstract_Entity_Signal::type;
    using Abstract_Entity_Signal::id;
  };
}

#endif // SAK_SIGNAL_ENTITY_ADDED_HPP
