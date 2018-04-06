#include "entity_name.hpp"

//---------------------------------------------------------------------------
// Entity_Name
//---------------------------------------------------------------------------
// The component of an Entity that supplies the name interface.

  // Special 6
//============================================================
// Construct with this name as the initial name.
sak::Entity_Name::Entity_Name(std::string const& a_name) :
  Abstract_Entity_Name(),
  m_name{a_name}
{
}

sak::Entity_Name::~Entity_Name() = default;

// Interface
//============================================================
std::string const& sak::Entity_Name::get_name() const
{
  return m_name;
}

bool sak::Entity_Name::set_name(std::string const& a_name)
{
  if (a_name != m_name)
  {
    m_name = a_name;
    return true;
  }
  else
  {
    return false;
  }
}
