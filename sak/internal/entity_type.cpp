#include "entity_type.hpp"

//---------------------------------------------------------------------------
// Local_Entity_Type
//---------------------------------------------------------------------------
// The component of an Entity that holds the type interface. Stores the type
// as a variable.

// Special 6
//============================================================
// Construct with this type as the intial.
sak::Local_Entity_Type::Local_Entity_Type(std::string const& a_type) :
  Abstract_Entity_Type(),
  m_type{a_type}
{
}

sak::Local_Entity_Type::~Local_Entity_Type() = default;

// Interface
//============================================================
std::string const& sak::Local_Entity_Type::type() const
{
  return m_type;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Remote_Entity_Type
//---------------------------------------------------------------------------
// The component of an Entity that holds the type interface. Stores the type
// as a reference to a string held elsewhere.

// Special 6
//============================================================
// Construct with this type as the intial.
sak::Remote_Entity_Type::Remote_Entity_Type(std::string const& a_type) :
  Abstract_Entity_Type(),
  m_type{a_type}
{
}

sak::Remote_Entity_Type::~Remote_Entity_Type() = default;

// Interface
//============================================================
std::string const& sak::Remote_Entity_Type::type() const
{
  return m_type;
}
