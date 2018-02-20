#ifndef SAK_SIGNAL_SOURCE_HPP
#define SAK_SIGNAL_SOURCE_HPP

#ifndef SAK_SIGNAL_SOURCE_FWD_HPP
#include "signal_source_fwd.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Signal_Source
  //---------------------------------------------------------------------------
  // Enum for identifying the origin of a signal.
  enum class Signal_Source
  {
    System,
    User,
    Editor,
    Outliner,
    Redo,
    Undo
  };
}

#endif // SAK_SIGNAL_SOURCE_HPP
