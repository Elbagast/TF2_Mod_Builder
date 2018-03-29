#include "abstract_signal.hpp"

//---------------------------------------------------------------------------
// Abstract_Signal
//---------------------------------------------------------------------------
// Base class for all Project signals. It has enough information to identify
// its true type, which holds enough data to process the signal.

// Special 6
//============================================================
sak::Abstract_Signal::Abstract_Signal(Signal_Source a_source, Signal_Type a_type) :
  m_source{a_source},
  m_type{a_type}
{}

sak::Abstract_Signal::~Abstract_Signal() = default;

// Interface
//============================================================
sak::Signal_Source sak::Abstract_Signal::source() const noexcept
{
  return m_source;
}

sak::Signal_Type sak::Abstract_Signal::type() const noexcept
{
  return m_type;
}
