#ifndef SAK_FILE_FWD_MANAGER_HPP
#define SAK_FILE_FWD_MANAGER_HPP

#include "data.hpp"
#include <generic/fwd/uintid.hpp>
#include <generic/fwd/uintid_manager.hpp>
#include <generic/fwd/manager.hpp>

namespace sak
{
  namespace file
  {
    //---------------------------------------------------------------------------
    // file::manager
    //---------------------------------------------------------------------------
    using manager = generic::Manager<generic::Uint32ID_Manager, data>;

    //---------------------------------------------------------------------------
    // file::handle
    //---------------------------------------------------------------------------
    using handle = generic::Handle<generic::Uint32ID_Manager, data>;
  }
}

#endif // SAK_FILE_FWD_MANAGER_HPP
