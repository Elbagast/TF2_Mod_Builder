#include "entity_tooltip.hpp"

//---------------------------------------------------------------------------
// Local_Entity_Tooltip
//---------------------------------------------------------------------------
// The component of an Entity that holds the type interface. Stores the type
// as a variable.

// Special 6
//============================================================
sak::Local_Entity_Tooltip::Local_Entity_Tooltip(std::string const& a_tooltip) :
  Abstract_Entity_Tooltip(),
  m_tooltip{a_tooltip}
{}

sak::Local_Entity_Tooltip::~Local_Entity_Tooltip() = default;

// Interface
//============================================================
std::string const& sak::Local_Entity_Tooltip::tooltip() const
{
  return m_tooltip;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Remote_Entity_Tooltip
//---------------------------------------------------------------------------
// The component of an Entity that holds the type interface. Stores the type
// as a reference to a string held elsewhere.

// Special 6
//============================================================
sak::Remote_Entity_Tooltip::Remote_Entity_Tooltip(std::string const& a_tooltip) :
  Abstract_Entity_Tooltip(),
  m_tooltip{a_tooltip}
{}

sak::Remote_Entity_Tooltip::~Remote_Entity_Tooltip() = default;

// Interface
//============================================================
std::string const& sak::Remote_Entity_Tooltip::tooltip() const
{
  return m_tooltip;
}
