#include "test_entity_id.hpp"

#include <sak/entity_id.hpp>

#include <iostream>
#include <cassert>

namespace sak
{
  std::ostream& operator<<(std::ostream& a_ostream, Entity_ID a_id)
  {
    a_ostream << "EID[" << entity_id_value(a_id) << "]";
    return a_ostream;
  }
}


void sak::testing::test_entity_id()
{
  std::cout << "Testing sak::Entity_ID" << std::endl;
  std::cout << "==============================" << std::endl;

  using namespace sak;

  // Make a null id
  auto l_eid1 = make_null_entity_id();
  std::cout << l_eid1 << std::endl;

  assert(l_eid1 == Entity_ID::Null);
  assert(is_null(l_eid1));
  assert(!not_null(l_eid1));
  assert(entity_id_value(l_eid1) == 0);


  // Make a null id via the factory function
  auto l_eid2 = make_null_entity_id();
  std::cout << l_eid2 << std::endl;

  assert(l_eid2 == Entity_ID::Null);
  assert(is_null(l_eid2));
  assert(!not_null(l_eid2));
  assert(entity_id_value(l_eid2) == 0);

  assert(l_eid1 == l_eid2);


  // Make an id via the factory function
  Entity_ID_Value_Type l_idv1{1u};

  auto l_eid3 = make_entity_id(l_idv1);
  std::cout << l_eid3 << std::endl;

  assert(l_eid3 != Entity_ID::Null);
  assert(!is_null(l_eid3));
  assert(not_null(l_eid3));
  assert(entity_id_value(l_eid3) == l_idv1);

  assert(l_eid3 != l_eid1);
  assert(l_eid3 != l_eid2);


  // Test comparison
  assert(l_eid3 > l_eid1);
  assert(l_eid1 < l_eid3);

  assert(l_eid3 >= l_eid1);
  assert(l_eid1 <= l_eid3);


  // Test swapping
  assert(entity_id_value(l_eid1) == 0);
  assert(entity_id_value(l_eid3) == l_idv1);

  std::swap(l_eid1, l_eid3);

  assert(entity_id_value(l_eid1) == l_idv1);
  assert(entity_id_value(l_eid3) == 0);

  swap(l_eid1, l_eid3);

  assert(entity_id_value(l_eid1) == 0);
  assert(entity_id_value(l_eid3) == l_idv1);

  // Test reset
  reset(l_eid3);
  assert(is_null(l_eid3));
  assert(entity_id_value(l_eid3) == 0);



  std::cout << "==============================" << std::endl;
}
