#ifndef SAK_FILE_FWD_INTERFACE_HPP
#define SAK_FILE_FWD_INTERFACE_HPP

#include <sak/shared/fwd/interface.hpp>
#include "object.hpp"

namespace sak
{
  namespace file
  {
    //---------------------------------------------------------------------------
    // file::interface
    //---------------------------------------------------------------------------
    using interface = shared::interface<object>;

    //---------------------------------------------------------------------------
    // file::const_interface
    //---------------------------------------------------------------------------
    using const_interface = shared::interface<object>;
  }
}

#endif // SAK_FILE_FWD_INTERFACE_HPP
