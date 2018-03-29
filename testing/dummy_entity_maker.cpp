#include "dummy_entity_maker.hpp"

#include <sak/entity_id.hpp>
#include <sak/entity.hpp>
#include <sak/entity_handle.hpp>

#include "dummy_entity.hpp"

#include <memory>
#include <cassert>
#include <QString>

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
QString sak::Dummy_Entity_Maker::type() const
{
  return QString{"Dummy Entity"};
}

// Make a new Entity of this type with the supplied id. If the supplied id
// is invalid then the handle is a null handle and no entity data was
// created.
sak::Entity_Handle sak::Dummy_Entity_Maker::make_entity(Entity_ID a_id) const
{
  assert(not_null(a_id));

  return Entity_Handle{std::make_shared<Entity>
          (
            a_id,
            std::unique_ptr<Abstract_Entity_Name>(std::make_unique<Dummy_Entity_Name>(this->type()).release()),
            std::unique_ptr<Abstract_Entity_Type>(std::make_unique<Dummy_Entity_Type>(this->type()).release()),
            std::unique_ptr<Abstract_Entity_Tooltip>(std::make_unique<Dummy_Entity_Tooltip>(QString{"dummy tooltip"}).release()),
            std::unique_ptr<Abstract_Entity_Icon>(std::make_unique<Dummy_Entity_Icon>(QString{"dummy iconpath"}).release())
          ) };
}

// Make a Dummy_Entity_Maker so that it can be installed.
std::unique_ptr<sak::Abstract_Entity_Maker> sak::Dummy_Entity_Maker::make_self()
{
  return std::unique_ptr<Abstract_Entity_Maker>{std::make_unique<Dummy_Entity_Maker>().release()};
}
