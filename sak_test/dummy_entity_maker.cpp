#include "dummy_entity_maker.hpp"

#include <sak/entity_id.hpp>
#include <sak/internal/entity.hpp>

#include <sak/internal/entity_name.hpp>
#include <sak/internal/entity_type.hpp>
#include <sak/internal/entity_icon.hpp>
#include <sak/internal/entity_tooltip.hpp>

#include <memory>
#include <cassert>

//---------------------------------------------------------------------------
// Dummy_Entity_Maker
//---------------------------------------------------------------------------
// Thing that makes dummy entities for testing.

// Special 6
//============================================================
sak::Dummy_Entity_Maker::Dummy_Entity_Maker() = default;
sak::Dummy_Entity_Maker::~Dummy_Entity_Maker() = default;


// Interface
//============================================================
// Get the typestring for this Entity type.
sak::String sak::Dummy_Entity_Maker::type() const
{
  static String const s_type{u8"Dummy Entity"};
  return s_type;
}

// Make a new Entity of this type with the supplied id. If the supplied id
// is invalid then the handle is a null handle and no entity data was
// created.
sak::Entity sak::Dummy_Entity_Maker::make_entity(Entity_ID a_id) const
{
  static String const s_tooltip{u8"dummy tooltip"};
  static String const s_icon{u8"dummy iconpath"};

  return Entity
  {
    a_id,
    std::make_unique<Local_Entity_Type>(this->Dummy_Entity_Maker::type()),
    std::make_unique<Local_Entity_Tooltip>(s_tooltip),
    std::make_unique<Local_Entity_Icon>(s_icon),
    std::make_unique<Entity_Name>(this->Dummy_Entity_Maker::type())
  };
}
