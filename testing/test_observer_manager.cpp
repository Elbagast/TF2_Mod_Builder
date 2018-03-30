#include "test_observer_manager.hpp"

#include <sak/observer_manager.hpp>
#include <sak/entity_id.hpp>
#include <sak/variant.hpp>
#include "dummy_observer.hpp"
#include "dummy_signal.hpp"

#include <memory>
#include <iostream>
#include <cassert>
#include <string>

namespace
{
  void do_test_signals(sak::Observer_Manager& a_pom)
  {
    using namespace sak;

    Dummy_Signal l_dps{ Signal_Source::System, Signal_Type::Entity_Added };

    std::cout << "-------------------------" << std::endl;
    std::cout << "Count = " << a_pom.count() << std::endl;
    a_pom.send(l_dps);
    std::cout << "-------------------------" << std::endl;
  }
}

void sak::testing::test_observer_manager()
{
  std::cout << "Testing sak::Observer_Manager" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  Observer_Manager l_pom{};


  std::cout << "test while empty:" << std::endl;
  do_test_signals(l_pom);

  // Make some observers
  auto l_dpo1 = std::make_unique<Dummy_Observer>();
  auto l_dpo2 = std::make_unique<Dummy_Observer>();
  auto l_dpo3 = std::make_unique<Dummy_Observer>();
  auto l_dpo4 = std::make_unique<Dummy_Observer>();

  // Add them
  l_pom.add(l_dpo1.get());
  l_pom.add(l_dpo2.get());
  l_pom.add(l_dpo3.get());

  std::cout << "test with 3 observers:" << std::endl;
  do_test_signals(l_pom);

  // Remove an observer
  l_pom.remove(l_dpo1.get());

  // This one wasn't added so it should do nothing
  l_pom.remove(l_dpo4.get());

  // Should do nothing with nullptr
  l_pom.remove(nullptr);

  std::cout << "test after removing "<< l_dpo1.get() <<":" << std::endl;
  do_test_signals(l_pom);

  // Remove all observers
  l_pom.clear();

  std::cout << "test after clearing:" << std::endl;
  do_test_signals(l_pom);


  std::cout << "==============================" << std::endl;
}
