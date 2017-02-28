#ifndef SAK_SHARED_FWD_EXTENDED_MANAGER_HPP
#define SAK_SHARED_FWD_EXTENDED_MANAGER_HPP

#include "object.hpp"
#include "interface_traits.hpp"
#include <generic/fwd/uintid.hpp>
#include <generic/fwd/uintid_manager.hpp>
#include <generic/fwd/extended_manager.hpp>

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::extended_manager
    //---------------------------------------------------------------------------
    template <typename T>
    using extended_manager = generic::Extended_Manager<generic::Uint32ID_Manager, T, interface_traits<T>>;

    //---------------------------------------------------------------------------
    // shared::extended_handle
    //---------------------------------------------------------------------------
    template <typename T>
    using extended_handle = generic::Extended_Handle<generic::Uint32ID_Manager, T, interface_traits<T>>;
  }

  namespace file
  {
    //---------------------------------------------------------------------------
    // file::extended_manager
    //---------------------------------------------------------------------------
    using extended_manager = shared::extended_manager<object>;

    //---------------------------------------------------------------------------
    // file::extended_handle
    //---------------------------------------------------------------------------
    using extended_handle = shared::extended_handle<object>;
  }
}


#endif // SAK_SHARED_FWD_EXTENDED_MANAGER_HPP
