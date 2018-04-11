#ifndef SAK_ABSTRACT_ENTITY_TYPE_HPP
#define SAK_ABSTRACT_ENTITY_TYPE_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_ABSTRACT_ENTITY_TYPE_FWD_HPP
#include "abstract_entity_type_fwd.hpp"
#endif

#ifndef SAK_STRING_FWD_HPP
#include "string_fwd.hpp"
#endif


namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Entity_Type
  //---------------------------------------------------------------------------
  // The component of an Entity that holds the type interface.

  class Abstract_Entity_Type
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Entity_Type() = 0;

    // Interface
    //============================================================
    virtual String const& type() const = 0;
  };
}

#endif // SAK_ABSTRACT_ENTITY_TYPE_HPP
