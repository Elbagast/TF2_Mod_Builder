#ifndef SAK_ABSTRACT_ENTITY_NAME_HPP
#define SAK_ABSTRACT_ENTITY_NAME_HPP

#ifndef SAK_ABSTRACT_ENTITY_NAME_FWD_HPP
#include "abstract_entity_name_fwd.hpp"
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
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
    virtual std::string const& get_name() const = 0;
    virtual bool set_name(std::string const&) = 0;
  };
}

#endif // SAK_ABSTRACT_ENTITY_NAME_HPP
