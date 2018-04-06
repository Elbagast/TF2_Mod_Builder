#ifndef SAK_SIGNAL_HPP
#define SAK_SIGNAL_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_SIGNAL_FWD_HPP
#include "signal_fwd.hpp"
#endif

// SAK Forwarding Headers
//============================================================
#ifndef SAK_SIGNAL_SOURCE_FWD_HPP
#include "signal_source_fwd.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Signal
  //---------------------------------------------------------------------------
  // Base class for all signals. It has enough information to identify what the
  // event does and what derived class it is if that is necessary. Signal data
  // is guaranteed to be valid for at least the lifetime of the signal.

  class Signal
  {
  private:
    // Data Members
    //============================================================
    Signal_Source m_source;
    Signal_Type m_type;

  public:
    // Special 6
    //============================================================
    Signal(Signal_Source a_source, Signal_Type a_type);
    virtual ~Signal();

    // Interface
    //============================================================
    Signal_Source source() const noexcept;
    Signal_Type type() const noexcept;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Signal_Type
  //---------------------------------------------------------------------------
  // Enum for identifying a signal's type.

  enum class Signal_Type
  {
    Unknown = 0,

    Entity_Outliner_Request,  // Signal_Entity
    Entity_Editor_Request,    // Signal_Entity

    Entity_Added,             // Signal_Entity
    Entity_Removed,           // Signal_Entity

    Entity_Name_Changed       // Signal_Entity_Name_Changed
  };
}

#endif // SAK_SIGNAL_HPP
