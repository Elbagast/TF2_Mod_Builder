#ifndef SAK_FILE_FWD_EXTENDED_MANAGER_HPP
#define SAK_FILE_FWD_EXTENDED_MANAGER_HPP

#include "object.hpp"
#include "interface_traits.hpp"
#include <sak/shared/fwd/extended_manager.hpp>

namespace sak
{
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


#endif // SAK_FILE_FWD_EXTENDED_MANAGER_HPP
