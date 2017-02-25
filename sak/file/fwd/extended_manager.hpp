#ifndef SAK_FILE_FWD_EXTENDED_MANAGER_HPP
#define SAK_FILE_FWD_EXTENDED_MANAGER_HPP

#include "data.hpp"
#include "interface_traits.hpp"
#include <generic/fwd/uintid.hpp>
#include <generic/fwd/uintid_manager.hpp>
#include <generic/fwd/extended_manager.hpp>

namespace sak
{
  namespace file
  {
    //---------------------------------------------------------------------------
    // file::extended_manager
    //---------------------------------------------------------------------------
    using extended_manager = generic::Extended_Manager<generic::Uint32ID_Manager, data, interface_traits>;

    //---------------------------------------------------------------------------
    // file::extended_handle
    //---------------------------------------------------------------------------
    using extended_handle = generic::Extended_Handle<generic::Uint32ID_Manager, data, interface_traits>;
  }
}


#endif // SAK_FILE_FWD_EXTENDED_MANAGER_HPP
