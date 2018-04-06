#ifndef SAK_ABSTRACT_OBSERVER_HPP
#define SAK_ABSTRACT_OBSERVER_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_ABSTRACT_OBSERVER_FWD_HPP
#include "abstract_observer_fwd.hpp"
#endif

// SAK Forwarding Headers
//============================================================
#ifndef SAK_SIGNAL_FWD_HPP
#include "signal_fwd.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Observer
  //---------------------------------------------------------------------------
  // Things that need to know about changes to the Project should inherit this
  // class and implement all the functions. Observers don't need to use
  // everything but they must at least provide a dummy implementation.

  class Abstract_Observer
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Observer() = 0;

    // Interface
    //============================================================
    // Recieve a project signal. It should contain everything needed to update
    // and representation of the Project. Guaranteed to be valid for at least
    // the duration of this call.
    virtual void recieve(Signal const& a_signal) = 0;
  };
}

#endif // SAK_ABSTRACT_OBSERVER_HPP
