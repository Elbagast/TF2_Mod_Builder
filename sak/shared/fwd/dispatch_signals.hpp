#ifndef SAK_SHARED_FWD_DISPATCH_SIGNALS_HPP
#define SAK_SHARED_FWD_DISPATCH_SIGNALS_HPP

#include "object.hpp"

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::dispatch_signals<T>
    //---------------------------------------------------------------------------
    // Supply an interface to send signals back to the Project. This allows us to
    // hide the signalling methods from the templates so we can have template
    // classes only expose things that need to be exposed.
    template <typename T>
    struct dispatch_signals;
  }

  namespace file
  {
    using dispatch_signals = shared::dispatch_signals<object>;
  }
}

#endif // SAK_SHARED_FWD_DISPATCH_SIGNALS_HPP
