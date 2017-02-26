#ifndef SAK_FILE_FWD_INTERFACE_TRAITS_HPP
#define SAK_FILE_FWD_INTERFACE_TRAITS_HPP

#include <sak/shared/fwd/interface_traits.hpp>
#include "object.hpp"

namespace sak
{
  namespace file
  {
    //---------------------------------------------------------------------------
    // file::interface_traits
    //---------------------------------------------------------------------------
    using interface_traits = shared::interface_traits<object>;
  }
}

#endif // SAK_FILE_FWD_INTERFACE_TRAITS_HPP
