#include "entity_definition.hpp"

#include "string.hpp"

//---------------------------------------------------------------------------
// Entity_Definition
//---------------------------------------------------------------------------
// Holds a basic set of information required to make an Entity with a
// configuration that matches that which is held by this. This detatches
// what a user needs to define an Entity type entirely from its
// implementation, which is itself split into components (doesn't have to
// be...).

// Special 6
//============================================================
sak::Entity_Definition::Entity_Definition(String const& a_type, String const& a_tooltip, String const& a_iconpath):
  m_type{a_type},
  m_tooltip{a_tooltip},
  m_iconpath{a_iconpath}
{
}
sak::Entity_Definition::~Entity_Definition() = default;

sak::Entity_Definition::Entity_Definition(Entity_Definition const&) = default;
sak::Entity_Definition& sak::Entity_Definition::operator=(Entity_Definition const&) = default;

sak::Entity_Definition::Entity_Definition(Entity_Definition &&) = default;
sak::Entity_Definition& sak::Entity_Definition::operator=(Entity_Definition &&) = default;

// Interface
//============================================================

// Type
//------------------------------------------------------------

// Get the type.
sak::String const& sak::Entity_Definition::type() const
{
  return m_type;
}

// Set the type. If the type is empty or the same as that in antoher
// definition that is used at the same time, Entity_Manager will have to
// deal with that somehow.
void sak::Entity_Definition::set_type(String const& a_value)
{
  m_type = a_value;
}

// Tooltip
//------------------------------------------------------------

// Is the tooltip set? Returns true if the tooltip is not empty.
bool sak::Entity_Definition::has_tooltip() const
{
  return !m_tooltip.is_empty();
}

// Get the tooltip.
sak::String const& sak::Entity_Definition::tooltip() const
{
  return m_tooltip;
}

// Set the tooltip.
void sak::Entity_Definition::set_tooltip(String const& a_value)
{
  m_tooltip = a_value;
}

// Icon
//------------------------------------------------------------

// Is the iconpath set? Returns true if the iconpath is not empty.
// Does not check if the iconpath exists.
bool sak::Entity_Definition::has_iconpath() const
{
  return !m_iconpath.is_empty();
}

// Get the iconpath.
sak::String const& sak::Entity_Definition::iconpath() const
{
  return m_iconpath;
}

// Set the iconpath.
void sak::Entity_Definition::set_iconpath(String const& a_value)
{
  m_iconpath = a_value;
}
