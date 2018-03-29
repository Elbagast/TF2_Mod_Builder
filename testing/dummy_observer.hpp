#ifndef SAK_DUMMY_OBSERVER_HPP
#define SAK_DUMMY_OBSERVER_HPP

#ifndef SAK_ABSTRACT_OBSERVER_HPP
#include <sak/abstract_observer.hpp>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Dummy_Project_Observer
  //---------------------------------------------------------------------------
  // Dump all the parameter to std::cout

  class Dummy_Observer :
      public Abstract_Observer
  {
  public:
    // Special 6
    //============================================================
    Dummy_Observer();
    ~Dummy_Observer() override final;

    // Interface
    //============================================================
    // Recieve a project signal. It should contain everything needed to update
    // and representation of the Project. Guaranteed to be valid for at least
    // the duration of this call.
    void recieve(Abstract_Signal const& a_signal) override final;
  };
}

#endif // SAK_DUMMY_PROJECT_OBSERVER_HPP
