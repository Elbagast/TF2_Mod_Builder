#ifndef SAK_SIGNAL_ENTITY_NAME_CHANGED_HPP
#define SAK_SIGNAL_ENTITY_NAME_CHANGED_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_SIGNAL_ENTITY_NAME_CHANGED_FWD_HPP
#include "signal_entity_name_changed_fwd.hpp"
#endif

// SAK Headers
//============================================================
#ifndef SAK_SIGNAL_ENTITY_HPP
#include "signal_entity.hpp"
#endif

// Standard Headers
//============================================================
#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Signal_Entity_Name_Changed
  //---------------------------------------------------------------------------
  // Signal that indicates an Entity with a given id has had its name changed.

  class Signal_Entity_Name_Changed :
      public Signal_Entity
  {
  private:
    // Data Members
    //============================================================
    std::string const& m_old_name;
    std::string const& m_new_name;

  public:
    // Special 6
    //============================================================
    Signal_Entity_Name_Changed(Signal_Source a_source, Entity_ID a_id, std::string const& a_old_name, std::string const& a_new_name);
    ~Signal_Entity_Name_Changed() override;

    // Interface
    //============================================================
    using Signal_Entity::source;
    using Signal_Entity::type;
    using Signal_Entity::id;

    std::string const& old_name() const noexcept;
    std::string const& new_name() const noexcept;
  };
}

#endif // SAK_SIGNAL_ENTITY_NAME_CHANGED_HPP
