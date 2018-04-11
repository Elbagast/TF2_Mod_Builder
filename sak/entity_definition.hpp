#ifndef SAK_ENTITY_DEFINITION_HPP
#define SAK_ENTITY_DEFINITION_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_ENTITY_DEFINITION_FWD_HPP
#include "entity_definition_fwd.hpp"
#endif

// SAK Headers
//============================================================
#ifndef SAK_STRING_HPP
#include "string.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Entity_Definition
  //---------------------------------------------------------------------------
  // Holds a basic set of information required to make an Entity with a
  // configuration that matches that which is held by this. This detatches
  // what a user needs to define an Entity type entirely from its
  // implementation, which is itself split into components (doesn't have to
  // be...).

  // Could probably mimic the Entity component setup and have the definition
  // split into components?

  class Entity_Definition
  {
  private:
    // Data Members
    //============================================================
    String m_type;
    String m_tooltip;
    String m_iconpath;

  public:
    // Special 6
    //============================================================
    explicit Entity_Definition(String const& a_type,
                               String const& a_tooltip = String{},
                               String const& a_iconpath = String{});
    ~Entity_Definition();

    Entity_Definition(Entity_Definition const&);
    Entity_Definition& operator=(Entity_Definition const&);

    Entity_Definition(Entity_Definition &&);
    Entity_Definition& operator=(Entity_Definition &&);

    // Interface
    //============================================================

    // Type
    //------------------------------------------------------------

    // Get the type.
    String const& type() const;

    // Set the type. If the type is empty or the same as that in antoher
    // definition that is used at the same time, Entity_Manager will have to
    // deal with that somehow.
    void set_type(String const& a_value);

    // Tooltip
    //------------------------------------------------------------

    // Is the tooltip set? Returns true if the tooltip is not empty.
    bool has_tooltip() const;

    // Get the tooltip.
    String const& tooltip() const;

    // Set the tooltip.
    void set_tooltip(String const& a_value);

    // Icon
    //------------------------------------------------------------

    // Is the iconpath set? Returns true if the iconpath is not empty.
    // Does not check if the iconpath exists.
    bool has_iconpath() const;

    // Get the iconpath.
    String const& iconpath() const;

    // Set the iconpath.
    void set_iconpath(String const& a_value);
  };
}

#endif // SAK_ENTITY_DEFINITION_HPP
