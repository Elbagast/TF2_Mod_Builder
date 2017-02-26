#ifndef SAK_FILE_FWD_SIGNALBOX_HPP
#define SAK_FILE_FWD_SIGNALBOX_HPP

#include <sak/shared/fwd/signalbox.hpp>
#include "object.hpp"

namespace sak
{
  namespace file
  {
    namespace abstract
    {
      //---------------------------------------------------------------------------
      // file::abstract::signalbox
      //---------------------------------------------------------------------------
      // All signals that are dispatched from Project for a given handle type.
      using signalbox = shared::abstract::signalbox<object>;
    }
  }
}

#endif // SAK_FILE_FWD_SIGNALBOX_HPP
