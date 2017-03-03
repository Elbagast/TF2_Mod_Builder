#ifndef SAK_SHARED_FWD_INTERFACE_TRAITS_HPP
#define SAK_SHARED_FWD_INTERFACE_TRAITS_HPP

#include "object.hpp"

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::interface_traits<T>
    //---------------------------------------------------------------------------
    template <typename T>
    class interface_traits;
  }

  namespace file
  {
    using interface_traits = shared::interface_traits<object>;
  }

  namespace texture
  {
    using interface_traits = shared::interface_traits<object>;
  }
}

#endif // SAK_SHARED_FWD_INTERFACE_TRAITS_HPP
