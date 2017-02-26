#ifndef SAK_SHARED_FWD_EXTENDED_MANAGER_HPP
#define SAK_SHARED_FWD_EXTENDED_MANAGER_HPP

#include "interface_traits.hpp"
#include <generic/fwd/uintid.hpp>
#include <generic/fwd/uintid_manager.hpp>
#include <generic/fwd/extended_manager.hpp>

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // file::extended_manager
    //---------------------------------------------------------------------------
    template <typename T>
    using extended_manager = generic::Extended_Manager<generic::Uint32ID_Manager, T, interface_traits<T>>;

    //---------------------------------------------------------------------------
    // file::extended_handle
    //---------------------------------------------------------------------------
    template <typename T>
    using extended_handle = generic::Extended_Handle<generic::Uint32ID_Manager, T, interface_traits<T>>;
  }
}


#endif // SAK_SHARED_FWD_EXTENDED_MANAGER_HPP
