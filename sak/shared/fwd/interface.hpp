#ifndef SAK_SHARED_FWD_INTERFACE_HPP
#define SAK_SHARED_FWD_INTERFACE_HPP

#include "object.hpp"

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::interface<T>
    //---------------------------------------------------------------------------
    template <typename T>
    class interface;
  }

  namespace file
  {
    using interface = shared::interface<object>;
  }

  namespace texture
  {
    using interface = shared::interface<object>;
  }
}

#endif // SAK_SHARED_FWD_INTERFACE_HPP
