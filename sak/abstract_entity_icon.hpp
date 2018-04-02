#ifndef SAK_ABSTRACT_ENTITY_ICON_HPP
#define SAK_ABSTRACT_ENTITY_ICON_HPP

#ifndef SAK_ABSTRACT_ENTITY_ICON_FWD_HPP
#include "abstract_entity_icon_fwd.hpp"
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Entity_Icon
  //---------------------------------------------------------------------------
  // The component of an Entity that holds the icon interface.

  class Abstract_Entity_Icon
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Entity_Icon() = 0;

    // Interface
    //============================================================
    virtual std::string const& iconpath() const = 0;
  };
}

#endif // SAK_ABSTRACT_ENTITY_ICON_HPP
