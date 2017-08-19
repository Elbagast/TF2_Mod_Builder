#ifndef SAK_SHARED_FWD_MANAGER_HPP
#define SAK_SHARED_FWD_MANAGER_HPP

#include "object.hpp"
#include <flamingo/fwd/handle.hpp>
//#include <generic/fwd/uintid_manager.hpp>
//#include <generic/fwd/manager.hpp>

namespace sak
{
  namespace shared
  {
    //---------------------------------------------------------------------------
    // shared::manager<T>
    //---------------------------------------------------------------------------
    template <typename T>
    using manager = flamingo::manager32<T>;

    //---------------------------------------------------------------------------
    // shared::handle<T>
    //---------------------------------------------------------------------------
    template <typename T>
    using handle = flamingo::handle32<T>;
  }

  namespace file
  {
    using manager = shared::manager<object>;

    using handle = shared::handle<object>;
  }

  namespace texture
  {
    using manager = shared::manager<object>;

    using handle = shared::handle<object>;
  }
}

#endif // SAK_SHARED_FWD_MANAGER_HPP
