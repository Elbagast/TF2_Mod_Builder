#ifndef SAK_SHARED_FWD_SIGNALBOX_HPP
#define SAK_SHARED_FWD_SIGNALBOX_HPP

#include "object.hpp"

namespace sak
{
  namespace shared
  {
    namespace abstract
    {
      //---------------------------------------------------------------------------
      // shared::abstract::signalbox<T>
      //---------------------------------------------------------------------------
      // All signals that are dispatched from Project for a given object type.
      template <typename T>
      class signalbox;
    }
  }

  namespace file
  {
    namespace abstract
    {
      //---------------------------------------------------------------------------
      // file::abstract::signalbox
      //---------------------------------------------------------------------------
      // All signals that are dispatched from Project for a given object type.
      using signalbox = shared::abstract::signalbox<object>;
    }
  }
}

#endif // SAK_SHARED_FWD_SIGNALBOX_HPP
