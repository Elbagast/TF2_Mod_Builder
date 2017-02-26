#ifndef SAK_FILE_FWD_MANAGER_HPP
#define SAK_FILE_FWD_MANAGER_HPP

#include "object.hpp"
#include <sak/shared/fwd/manager.hpp>

namespace sak
{
  namespace file
  {
    //---------------------------------------------------------------------------
    // file::manager
    //---------------------------------------------------------------------------
    using manager = shared::manager<object>;

    //---------------------------------------------------------------------------
    // file::handle
    //---------------------------------------------------------------------------
    using handle = shared::handle<object>;
  }
}

#endif // SAK_FILE_FWD_MANAGER_HPP
