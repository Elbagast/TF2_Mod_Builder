#ifndef SAK_ENTITY_NAME_CHANGED_SIGNAL_HPP
#define SAK_ENTITY_NAME_CHANGED_SIGNAL_HPP

#ifndef SAK_ABSTRACT_ENTITY_SIGNAL_HPP
#include "abstract_entity_signal.hpp"
#endif

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
      public Abstract_Entity_Signal
  {
  private:
    std::string const& m_old_name;
    std::string const& m_new_name;
  public:
    // Special 6
    //============================================================
    Signal_Entity_Name_Changed(Signal_Source a_source, Entity_ID a_id, std::string const& a_old_name, std::string const& a_new_name);
    ~Signal_Entity_Name_Changed() override final;

    // Interface
    //============================================================
    using Abstract_Entity_Signal::source;
    using Abstract_Entity_Signal::type;
    using Abstract_Entity_Signal::id;

    std::string const& old_name() const;
    std::string const& new_name() const;
  };
}

#endif // SAK_ENTITY_NAME_CHANGED_SIGNAL_HPP
