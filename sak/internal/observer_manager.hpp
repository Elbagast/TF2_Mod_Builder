#ifndef SAK_OBSERVER_MANAGER_HPP
#define SAK_OBSERVER_MANAGER_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_OBSERVER_MANAGER_FWD_HPP
#include "observer_manager_fwd.hpp"
#endif

// SAK Forwarding Headers
//============================================================
#ifndef SAK_ABSTRACT_OBSERVER_FWD_HPP
#include "../abstract_observer_fwd.hpp"
#endif

#ifndef SAK_SIGNAL_FWD_HPP
#include "../signal_fwd.hpp"
#endif

#ifndef SAK_ENTITY_ID_FWD_HPP
#include "../entity_id_fwd.hpp"
#endif

#ifndef SAK_VARIANT_FWD_HPP
#include "../variant_fwd.hpp"
#endif

// Standard Headers
//============================================================
#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Observer_Manager
  //---------------------------------------------------------------------------
  // Manages a collection of observers for a project and allows calling
  // observer functions on all of them.

  class Observer_Manager
  {
  private:
    // Data Members
    //============================================================
    std::vector<Abstract_Observer*> m_observers;

  public:
    // Special 6
    //============================================================
    Observer_Manager();
    ~Observer_Manager();

    // There's not really anything stopping this from being copied or moved, but
    // it's only going to be used in one place by something that can't be moved
    // or copied, so we enforce this here too.
    Observer_Manager(Observer_Manager const&) = delete;
    Observer_Manager& operator=(Observer_Manager const&) = delete;

    Observer_Manager(Observer_Manager &&) = delete;
    Observer_Manager& operator=(Observer_Manager &&) = delete;

    // Interface
    //============================================================

    // Collection
    //------------------------------------------------------------
    // Just keep these names the same as for Project since that's all that's
    // going to use them.


    // Is this observer in the collection?
    bool has(Abstract_Observer* a_observer) const;

    // How many observers are currently held?
    std::size_t count() const;

    // Get all the currently held observers.
    std::vector<Abstract_Observer*> observers() const;

    // Add an object that will rely on the Project's signals. If
    // nullptr or already present, nothing happens.
    void add(Abstract_Observer* a_observer);

    // Remove an object that will rely on the Project's signals. If
    // nullptr or not present, nothing happens.
    void remove(Abstract_Observer* a_observer);

    // Clear all the observers so that nothing relies on changes to this.
    void clear();


    // Observer Functions
    //------------------------------------------------------------
    // Call recieve on all held observers with this signal object.
    void send(Signal const& a_signal);
  };
}

#endif // SAK_OBSERVER_MANAGER_HPP
