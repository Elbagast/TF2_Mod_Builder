#ifndef SAK_TESTING_DUMMY_SIGNAL_HPP
#define SAK_TESTING_DUMMY_SIGNAL_HPP

#ifndef SAK_ABSTRACT_SIGNAL_HPP
#include <sak/abstract_signal.hpp>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Dummy_Signal
  //---------------------------------------------------------------------------
  // Simple signal that does nothing but implement the virtual functions.

  class Dummy_Signal :
      public Abstract_Signal
  {
  public:
    // Special 6
    //============================================================
    Dummy_Signal(Signal_Source a_source, Signal_Type a_type);
    ~Dummy_Signal() override final;
  };
}

#endif // SAK_TESTING_DUMMY_SIGNAL_HPP
