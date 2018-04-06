#include "entity_definition_maker.hpp"

#include "entity.hpp"
#include "entity_name.hpp"
#include "entity_type.hpp"
#include "entity_icon.hpp"
#include "entity_tooltip.hpp"

//---------------------------------------------------------------------------
// Entity_Definition_Maker
//---------------------------------------------------------------------------
// Make entities using the supplied definition.

// Special 6
//============================================================
sak::Entity_Definition_Maker::Entity_Definition_Maker(Entity_Definition const& a_def) :
  Abstract_Entity_Maker(),
  m_def{a_def}
{}

sak::Entity_Definition_Maker::~Entity_Definition_Maker() = default;

// Interface
//============================================================
// Get the typestring for this Entity type.
std::string sak::Entity_Definition_Maker::type() const
{
  return m_def.type();
}

// Make a new Entity of this type with the supplied id. It is not the
// responsibility of this to determine whether the id is null or invalid,
// that should have been done before reaching here.
sak::Entity sak::Entity_Definition_Maker::make_entity(Entity_ID a_id) const
{
  return Entity
  {
    a_id,
    std::make_unique<Remote_Entity_Type>(m_def.type()),
    std::make_unique<Entity_Name>(m_def.type()),
    std::make_unique<Remote_Entity_Tooltip>(m_def.tooltip()),
    std::make_unique<Remote_Entity_Icon>(m_def.iconpath())
  };
}
