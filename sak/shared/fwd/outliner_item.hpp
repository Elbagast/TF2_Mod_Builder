#ifndef SAK_SHARED_FWD_OUTLINER_ITEM_HPP
#define SAK_SHARED_FWD_OUTLINER_ITEM_HPP

#include "object.hpp"

namespace sak
{
  namespace shared
  {
    namespace outliner
    {
      //---------------------------------------------------------------------------
      // shared::outliner::header_item<T>
      //---------------------------------------------------------------------------
      template <typename T>
      class header_item;

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
      //---------------------------------------------------------------------------
      // file::outliner::header_item
      //---------------------------------------------------------------------------
      using header_item = shared::outliner::header_item<object>;

      //---------------------------------------------------------------------------
      // file::outliner::item
      //---------------------------------------------------------------------------
      using item = shared::outliner::item<object>;
    }
  }
}

#endif // SAK_SHARED_FWD_OUTLINER_ITEM_HPP
