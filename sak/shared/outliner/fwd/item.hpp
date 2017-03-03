#ifndef SAK_SHARED_OUTLINER_FWD_ITEM_HPP
#define SAK_SHARED_OUTLINER_FWD_ITEM_HPP

#include <sak/shared/fwd/object.hpp>

namespace sak
{
  namespace shared
  {
    namespace outliner
    {
      //---------------------------------------------------------------------------
      // shared::outliner::item<T>
      //---------------------------------------------------------------------------
      template <typename T>
      class item;
    }
  }

  namespace file
  {
    namespace outliner
    {
      using item = shared::outliner::item<object>;
    }
  }

  namespace texture
  {
    namespace outliner
    {
      using item = shared::outliner::item<object>;
    }
  }
}

#endif // SAK_SHARED_OUTLINER_FWD_ITEM_HPP
