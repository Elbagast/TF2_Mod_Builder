#ifndef SAK_ABSTRACT_ENTITY_NAME_HPP
#define SAK_ABSTRACT_ENTITY_NAME_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_ABSTRACT_ENTITY_NAME_FWD_HPP
#include "abstract_entity_name_fwd.hpp"
#endif

#ifndef SAK_STRING_FWD_HPP
#include "string_fwd.hpp"
#endif


namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Entity_Name
  //---------------------------------------------------------------------------
  // The component of an Entity that supplies the name interface.

  class Abstract_Entity_Name
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Entity_Name() = 0;

    // Interface
    //============================================================
    virtual String const& get_name() const = 0;
    virtual bool set_name(String const&) = 0;
  };
}

#endif // SAK_ABSTRACT_ENTITY_NAME_HPP
