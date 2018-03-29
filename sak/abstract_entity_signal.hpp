#ifndef SAK_ABSTRACT_ENTITY_SIGNAL_HPP
#define SAK_ABSTRACT_ENTITY_SIGNAL_HPP

#ifndef SAK_ABSTRACT_ENTITY_SIGNAL_FWD_HPP
#include "abstract_entity_signal_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_SIGNAL_HPP
#include "abstract_signal.hpp"
#endif

#ifndef SAK_ENTITY_ID_HPP
#include "entity_id.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Entity_Signal
  //---------------------------------------------------------------------------
  // Base class for all Project signals that relate to a Entity.

  class Abstract_Entity_Signal :
      public Abstract_Signal
  {
  private:
    // Data Members
    //============================================================
    Entity_ID m_id;

  public:
    // Special 6
    //============================================================
    Abstract_Entity_Signal(Signal_Source a_source,
                           Signal_Type a_type,
                           Entity_ID a_id);
    ~Abstract_Entity_Signal() override = 0;

    // Interface
    //============================================================
    using Abstract_Signal::source;
    using Abstract_Signal::type;

    Entity_ID id() const;
  };
}

#endif // SAK_ABSTRACT_ENTITY_SIGNAL_HPP
