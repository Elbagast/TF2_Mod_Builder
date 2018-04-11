#ifndef SAK_ENTITY_NAME_HPP
#define SAK_ENTITY_NAME_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_ENTITY_NAME_FWD_HPP
#include "entity_name_fwd.hpp"
#endif

// SAK Headers
//============================================================
#ifndef SAK_ABSTRACT_ENTITY_NAME_HPP
#include "abstract_entity_name.hpp"
#endif

#ifndef SAK_STRING_HPP
#include "../string.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Entity_Name
  //---------------------------------------------------------------------------
  // The component of an Entity that supplies the name interface.

  class Entity_Name :
      public Abstract_Entity_Name
  {
  private:
    // Data Members
    //============================================================
    String m_name;

  public:
    // Special 6
    //============================================================
    // Construct with this name as the initial name.
    explicit Entity_Name(String const& a_name);
    ~Entity_Name() override final;

    // Block copying components.
    Entity_Name(Entity_Name const&) = delete;
    Entity_Name& operator=(Entity_Name const&) = delete;

    // Block moving components.
    Entity_Name(Entity_Name &&) = delete;
    Entity_Name& operator=(Entity_Name &&) = delete;

    // Interface
    //============================================================
    String const& get_name() const override final;
    bool set_name(String const& a_name) override final;
  };
}

#endif // SAK_ENTITY_NAME_HPP
