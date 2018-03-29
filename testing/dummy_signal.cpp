#include "dummy_signal.hpp"

//---------------------------------------------------------------------------
// Dummy_Signal
//---------------------------------------------------------------------------

sak::Dummy_Signal::Dummy_Signal(Signal_Source a_source, Signal_Type a_type) :
  Abstract_Signal(a_source, a_type)
{}

sak::Dummy_Signal::~Dummy_Signal() = default;
