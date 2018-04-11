#ifndef SAK_ABSTRACT_ENTITY_TOOLTIP_HPP
#define SAK_ABSTRACT_ENTITY_TOOLTIP_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_ABSTRACT_ENTITY_TOOLTIP_FWD_HPP
#include "abstract_entity_tooltip_fwd.hpp"
#endif

#ifndef SAK_STRING_FWD_HPP
#include "string_fwd.hpp"
#endif


namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Entity_Tooltip
  //---------------------------------------------------------------------------
  // The component of an Entity that holds the tooltip interface.

  class Abstract_Entity_Tooltip
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Entity_Tooltip() = 0;

    // Interface
    //============================================================
    virtual String const& tooltip() const = 0;
  };
}

#endif // SAK_ABSTRACT_ENTITY_TOOLTIP_HPP
