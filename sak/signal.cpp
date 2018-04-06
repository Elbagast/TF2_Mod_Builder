#include "signal.hpp"
//---------------------------------------------------------------------------
// Signal
//---------------------------------------------------------------------------
// Base class for all signals. It has enough information to identify what the
// event does and what derived class it is if that is necessary.

// Special 6
//============================================================
sak::Signal::Signal(Signal_Source a_source, Signal_Type a_type) :
  m_source{a_source},
  m_type{a_type}
{
}

sak::Signal::~Signal() = default;

// Interface
//============================================================
sak::Signal_Source sak::Signal::source() const noexcept
{
  return m_source;
}

sak::Signal_Type sak::Signal::type() const noexcept
{
  return m_type;
}
