#ifndef SAK_ENTITY_NAME_HPP
#define SAK_ENTITY_NAME_HPP

#ifndef SAK_ENTITY_NAME_FWD_HPP
#include "entity_name_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_ENTITY_NAME_HPP
#include "abstract_entity_name.hpp"
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
    std::string m_name;

  public:
    // Special 6
    //============================================================
    // Construct with this name as the initial name.
    explicit Entity_Name(std::string const& a_name);
    ~Entity_Name() override final;

    // Block copying components.
    Entity_Name(Entity_Name const&) = delete;
    Entity_Name& operator=(Entity_Name const&) = delete;

    // Block moving components.
    Entity_Name(Entity_Name &&) = delete;
    Entity_Name& operator=(Entity_Name &&) = delete;

    // Interface
    //============================================================
    std::string const& get_name() const override final;
    bool set_name(std::string const& a_name) override final;
  };
}

#endif // SAK_ENTITY_NAME_HPP
