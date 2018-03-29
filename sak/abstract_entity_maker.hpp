#ifndef SAK_ABSTRACT_ENTITY_MAKER_HPP
#define SAK_ABSTRACT_ENTITY_MAKER_HPP

#ifndef SAK_ABSTRACT_ENTITY_MAKER_FWD_HPP
#include "abstract_entity_maker_fwd.hpp"
#endif

#ifndef SAK_ENTITY_HANDLE_FWD_HPP
#include "entity_handle_fwd.hpp"
#endif

#ifndef SAK_ENTITY_ID_FWD_HPP
#include "entity_id_fwd.hpp"
#endif

class QString;

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Entity_Maker
  //---------------------------------------------------------------------------
  // Make an entity using the supplied id. If the id is null the handle is null
  // and no entity data was created.

  class Abstract_Entity_Maker
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Entity_Maker() = 0;

    // Interface
    //============================================================
    // Get the typestring for this Entity type.
    virtual QString type() const = 0;

    // Make a new Entity of this type with the supplied id. If the supplied id
    // is invalid then the handle is a null handle and no entity data was
    // created.
    virtual Entity_Handle make_entity(Entity_ID a_id) const = 0;

    // If the Entity becomes made of distributed parts, this thing will make the
    // parts and whatever uses this will put them into storage.
  };
}

#endif // SAK_ABSTRACT_ENTITY_MAKER_HPP
