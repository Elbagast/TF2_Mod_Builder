#ifndef SAK_SHARED_FWD_PROJECT_ACCESS_HPP
#define SAK_SHARED_FWD_PROJECT_ACCESS_HPP

#include "object.hpp"

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::project_access<T>
    //---------------------------------------------------------------------------
    // Supply an interface to send signals back to the Project. This allows us to
    // hide the signalling methods from the templates so we can have template
    // classes only expose things that need to be exposed.
    template <typename T>
    struct project_access;
  }

  namespace file
  {
    using project_access = shared::project_access<object>;
  }
}

#endif // SAK_SHARED_FWD_PROJECT_ACCESS_HPP
