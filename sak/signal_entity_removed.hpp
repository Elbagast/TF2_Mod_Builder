#ifndef SAK_ENTITY_REMOVED_SIGNAL_HPP
#define SAK_ENTITY_REMOVED_SIGNAL_HPP

#ifndef SAK_ABSTRACT_ENTITY_SIGNAL_HPP
#include "abstract_entity_signal.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Signal_Entity_Removed
  //---------------------------------------------------------------------------
  // Signal that indicates an Entity with a given id was removed from the project.

  class Signal_Entity_Removed :
      public Abstract_Entity_Signal
  {
  public:
    // Special 6
    //============================================================
    Signal_Entity_Removed(Signal_Source a_source, Entity_ID a_id);
    ~Signal_Entity_Removed() override final;

    // Interface
    //============================================================
    using Abstract_Entity_Signal::source;
    using Abstract_Entity_Signal::type;
    using Abstract_Entity_Signal::id;
  };
}

#endif // SAK_ENTITY_REMOVED_SIGNAL_HPP
