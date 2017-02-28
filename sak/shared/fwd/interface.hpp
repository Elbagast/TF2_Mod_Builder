#ifndef SAK_SHARED_FWD_INTERFACE_HPP
#define SAK_SHARED_FWD_INTERFACE_HPP

#include "object.hpp"

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::interface
    //---------------------------------------------------------------------------
    template <typename T>
    class interface;

    //---------------------------------------------------------------------------
    // shared::const_interface
    //---------------------------------------------------------------------------
    template <typename T>
    class const_interface;
  }

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

#endif // SAK_SHARED_FWD_INTERFACE_HPP
