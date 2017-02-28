#ifndef SAK_SHARED_FWD_MANAGER_HPP
#define SAK_SHARED_FWD_MANAGER_HPP

#include "object.hpp"
#include <generic/fwd/uintid.hpp>
#include <generic/fwd/uintid_manager.hpp>
#include <generic/fwd/manager.hpp>

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::manager<T>
    //---------------------------------------------------------------------------
    template <typename T>
    using manager = generic::Manager<generic::Uint32ID_Manager, T>;

    //---------------------------------------------------------------------------
    // shared::handle<T>
    //---------------------------------------------------------------------------
    template <typename T>
    using handle = generic::Handle<generic::Uint32ID_Manager, T>;
  }

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

#endif // SAK_SHARED_FWD_MANAGER_HPP
