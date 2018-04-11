#include "entity_icon.hpp"

//---------------------------------------------------------------------------
// Local_Entity_Icon
//---------------------------------------------------------------------------
// The component of an Entity that holds the icon interface. Stores the icon
// path as a variable.

// Special 6
//============================================================
sak::Local_Entity_Icon::Local_Entity_Icon(String const& a_iconpath):
  Abstract_Entity_Icon(),
  m_iconpath{a_iconpath}
{}

sak::Local_Entity_Icon::~Local_Entity_Icon() = default;

// Interface
//============================================================
sak::String const& sak::Local_Entity_Icon::iconpath() const
{
  return m_iconpath;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Remote_Entity_Icon
//---------------------------------------------------------------------------
// The component of an Entity that holds the icon interface. Stores the icon
// path as a reference to a string held elsewhere.

// Special 6
//============================================================
sak::Remote_Entity_Icon::Remote_Entity_Icon(String const& a_iconpath):
  Abstract_Entity_Icon(),
  m_iconpath{a_iconpath}
{}

sak::Remote_Entity_Icon::~Remote_Entity_Icon() = default;

// Interface
//============================================================
sak::String const& sak::Remote_Entity_Icon::iconpath() const
{
  return m_iconpath;
}
