#ifndef SAK_ABSTRACT_ENTITY_MAKER_HPP
#define SAK_ABSTRACT_ENTITY_MAKER_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_ABSTRACT_ENTITY_MAKER_FWD_HPP
#include "abstract_entity_maker_fwd.hpp"
#endif

// SAK Forwarding Headers
//============================================================
#ifndef SAK_ENTITY_FWD_HPP
#include "entity_fwd.hpp"
#endif

#ifndef SAK_ENTITY_ID_FWD_HPP
#include "entity_id_fwd.hpp"
#endif

#ifndef SAK_ENTITY_DEFINITION_FWD_HPP
#include "../entity_definition_fwd.hpp"
#endif

#ifndef SAK_STRING_FWD_HPP
#include "../string_fwd.hpp"
#endif

// Standard Headers
//============================================================
#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif


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
    virtual String type() const = 0;

    // Make a new Entity of this type with the supplied id. It is not the
    // responsibility of this to determine whether the id is null or invalid,
    // that should have been done before reaching here.
    virtual Entity make_entity(Entity_ID a_id) const = 0;

    // Make a maker from an Entity_Definition. The maker holds copies of any
    // data it needs from the definition.
    static std::unique_ptr<Abstract_Entity_Maker> from_definition(Entity_Definition const& a_definition);
  };
}

#endif // SAK_ABSTRACT_ENTITY_MAKER_HPP
