#include "abstract_entity_maker.hpp"

#include "entity_definition_maker.hpp"

//---------------------------------------------------------------------------
// Abstract_Entity_Maker
//---------------------------------------------------------------------------
// Make an entity using the supplied id. If the id is null the handle is null
// and no entity data was created.

// Special 6
//============================================================
sak::Abstract_Entity_Maker::~Abstract_Entity_Maker() = default;

// Make a maker from an Entity_Definition. The maker holds copies of any
// data it needs from the definition.
std::unique_ptr<sak::Abstract_Entity_Maker> sak::Abstract_Entity_Maker::from_definition(Entity_Definition const& a_definition)
{
  return std::unique_ptr<sak::Abstract_Entity_Maker>{std::make_unique<Entity_Definition_Maker>(a_definition).release()};
}
