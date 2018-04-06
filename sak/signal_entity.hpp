#ifndef SAK_SIGNAL_ENTITY_HPP
#define SAK_SIGNAL_ENTITY_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_SIGNAL_ENTITY_FWD_HPP
#include "signal_entity_fwd.hpp"
#endif

// SAK Headers
//============================================================
#ifndef SAK_SIGNAL_HPP
#include "signal.hpp"
#endif

#ifndef SAK_ENTITY_ID_HPP
#include "entity_id.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Signal_Entity
  //---------------------------------------------------------------------------
  // Class for a signal that relates to a specific Entity. This class is also
  // derived from so that more complicated signals can store an Entity_ID in
  // addition to other data.

  class Signal_Entity :
      public Signal
  {
  private:
    // Data Members
    //============================================================
    Entity_ID m_id;

  public:
    // Special 6
    //============================================================
    Signal_Entity(Signal_Source a_source, Signal_Type a_type, Entity_ID a_id);
    ~Signal_Entity() override;

    // Interface
    //============================================================
    using Signal::source;
    using Signal::type;

    Entity_ID id() const noexcept;
  };

  Signal_Entity make_signal_entity_outliner_request(Signal_Source a_source, Entity_ID a_id);
  Signal_Entity make_signal_entity_editor_request(Signal_Source a_source, Entity_ID a_id);

  Signal_Entity make_signal_entity_added(Signal_Source a_source, Entity_ID a_id);
  Signal_Entity make_signal_entity_removed(Signal_Source a_source, Entity_ID a_id);
}

#endif // SAK_SIGNAL_ENTITY_HPP
