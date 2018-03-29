#include "observer_manager.hpp"

#include "abstract_observer.hpp"

#include <algorithm>

//---------------------------------------------------------------------------
// Observer_Manager
//---------------------------------------------------------------------------
// Manages a collection of observers for a project and allows calling
// observer functions on all of them.

// Special 6
//============================================================
sak::Observer_Manager::Observer_Manager() :
  m_observers{}
{}

sak::Observer_Manager::~Observer_Manager() = default;

// Interface
//============================================================

namespace
{
  decltype(auto) do_find_observer(std::vector<sak::Abstract_Observer*> const& a_vector, sak::Abstract_Observer* a_observer)
  {
    return std::find(a_vector.cbegin(), a_vector.cend(), a_observer);
  }

  bool do_has_observer(std::vector<sak::Abstract_Observer*> const& a_vector, sak::Abstract_Observer* a_observer)
  {
    return do_find_observer(a_vector,a_observer) != a_vector.cend();
  }
}

// Collection
//------------------------------------------------------------

// Is this observer in the collection?
bool sak::Observer_Manager::has(Abstract_Observer* a_observer) const
{
  return do_has_observer(m_observers, a_observer);
}

// How many observers are currently held?
std::size_t sak::Observer_Manager::count() const
{
  return m_observers.size();
}

// Get all the currently held observers.
std::vector<sak::Abstract_Observer*> sak::Observer_Manager::observers() const
{
  return m_observers;
}

// Add an object that will rely on the Project's signals. If
// nullptr or already present, nothing happens.
void sak::Observer_Manager::add(Abstract_Observer* a_observer)
{
  if (a_observer != nullptr
     && !do_has_observer(m_observers, a_observer))
 {
   m_observers.push_back(a_observer);
 }
}

// Remove an object that will rely on the Project's signals. If
// nullptr or not present, nothing happens.
void sak::Observer_Manager::remove(Abstract_Observer* a_observer)
{
  if (a_observer == nullptr)
  {
    return;
  }
  auto l_found = do_find_observer(m_observers, a_observer);
  if (l_found != m_observers.cend())
  {
    m_observers.erase(l_found);
  }
}

// Clear all the observers so that nothing relies on changes to this.
void sak::Observer_Manager::clear()
{
  m_observers.clear();
}


// Observer Functions
//------------------------------------------------------------
// Call recieve on all held observers with this signal object.
void sak::Observer_Manager::send(Abstract_Signal const& a_signal)
{for (auto l_item : m_observers)
  {
    l_item->recieve(a_signal);
  }
}
