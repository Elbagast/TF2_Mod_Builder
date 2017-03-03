#ifndef SAK_SHARED_OUTLINER_FWD_HEADER_ITEM_HPP
#define SAK_SHARED_OUTLINER_FWD_HEADER_ITEM_HPP

#include <sak/shared/fwd/object.hpp>

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
    }
  }
}
#endif // SAK_SHARED_OUTLINER_FWD_HEADER_ITEM_HPP
