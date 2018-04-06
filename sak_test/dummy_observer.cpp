#include "dummy_observer.hpp"

#include <sak/signal.hpp>
#include <sak/signal_source.hpp>

#include "test_io.hpp"

#include <iostream>


//---------------------------------------------------------------------------
// Dummy_Project_Observer
//---------------------------------------------------------------------------
// Dump all the parameter to std::cout

// Special 6
//============================================================
sak::Dummy_Observer::Dummy_Observer() = default;
sak::Dummy_Observer::~Dummy_Observer() = default;

// Interface
//============================================================
// Recieve a project signal. It should contain everything needed to update
// and representation of the Project. Guaranteed to be valid for at least
// the duration of this call.
void sak::Dummy_Observer::recieve(Signal const& a_signal)
{
  std::cout << this << " : "
           << "sak::Dummy_Observer::recieve( "
           << std::addressof(a_signal)
           << " : " << a_signal
           << " )" << std::endl;
}

