#ifndef SAK_ENTITY_DEFINITION_MAKER_HPP
#define SAK_ENTITY_DEFINITION_MAKER_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_ENTITY_DEFINITION_MAKER_FWD_HPP
#include "entity_definition_maker_fwd.hpp"
#endif

// SAK Headers
//============================================================
#ifndef SAK_ABSTRACT_ENTITY_MAKER_HPP
#include "abstract_entity_maker.hpp"
#endif

#ifndef SAK_ENTITY_DEFINITION_HPP
#include "../entity_definition.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Entity_Definition_Maker
  //---------------------------------------------------------------------------
  // Make entities using the supplied definition.

  class Entity_Definition_Maker :
      public Abstract_Entity_Maker
  {
  private:
    // Data Members
    //============================================================
    Entity_Definition m_def;

  public:
    // Special 6
    //============================================================
    explicit Entity_Definition_Maker(Entity_Definition const& a_def);
    ~Entity_Definition_Maker() override final;

    // Interface
    //============================================================
    // Get the typestring for this Entity type.
    std::string type() const override final;

    // Make a new Entity of this type with the supplied id. It is not the
    // responsibility of this to determine whether the id is null or invalid,
    // that should have been done before reaching here.
    Entity make_entity(Entity_ID a_id) const override final;
  };
}

#endif // ENTITY_DEFINITION_MAKER_HPP
