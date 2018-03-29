#ifndef SAK_ABSTRACT_SIGNAL_HPP
#define SAK_ABSTRACT_SIGNAL_HPP

#ifndef SAK_ABSTRACT_SIGNAL_FWD_HPP
#include "abstract_signal_fwd.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Signal
  //---------------------------------------------------------------------------
  // Base class for all Project signals. It has enough information to identify
  // its true type, which holds enough data to process the signal.

  class Abstract_Signal
  {
  private:
    // Data Members
    //============================================================
    Signal_Source m_source;
    Signal_Type m_type;

  public:
    // Special 6
    //============================================================
    Abstract_Signal(Signal_Source a_source, Signal_Type a_type);
    virtual ~Abstract_Signal() = 0;

    // Interface
    //============================================================
    Signal_Source source() const noexcept;
    Signal_Type type() const noexcept;
  };

  //---------------------------------------------------------------------------
  // Signal_Source
  //---------------------------------------------------------------------------
  // Enum for identifying the origin of a signal.
  enum class Signal_Source
  {
    Unknown,

    System,
    User,
    Editor,
    Outliner,
    Redo,
    Undo
  };

  //---------------------------------------------------------------------------
  // Signal_Type
  //---------------------------------------------------------------------------
  // Enum for identifying a signal's true type.

  enum class Signal_Type
  {
    Unknown,

    Entity_Outliner_Request,
    Entity_Editor_Request,

    Entity_Added,
    Entity_Removed,

    Entity_Name_Changed
  };
}

#endif // SAK_ABSTRACT_SIGNAL_HPP
