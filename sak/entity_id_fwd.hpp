#ifndef SAK_ENTITY_ID_FWD_HPP
#define SAK_ENTITY_ID_FWD_HPP

#ifndef INCLUDE_STD_CSTDINT
#define INCLUDE_STD_CSTDINT
#include <cstdint>
#endif

namespace sak
{
  using Entity_ID_Value_Type = std::uintptr_t;

  enum class Entity_ID : Entity_ID_Value_Type;

}

#endif // SAK_ENTITY_ID_FWD_HPP
