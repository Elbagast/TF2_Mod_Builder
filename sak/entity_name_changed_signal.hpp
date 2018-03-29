#ifndef SAK_ENTITY_NAME_CHANGED_SIGNAL_HPP
#define SAK_ENTITY_NAME_CHANGED_SIGNAL_HPP

#ifndef SAK_ABSTRACT_ENTITY_SIGNAL_HPP
#include "abstract_entity_signal.hpp"
#endif

class QString;

namespace sak
{
  //---------------------------------------------------------------------------
  // Entity_Name_Changed_Signal
  //---------------------------------------------------------------------------
  // Signal that indicates an Entity with a given id has had its name changed.

  class Entity_Name_Changed_Signal :
      public Abstract_Entity_Signal
  {
  private:
    QString const& m_old_name;
    QString const& m_new_name;
  public:
    // Special 6
    //============================================================
    Entity_Name_Changed_Signal(Signal_Source a_source, Entity_ID a_id, QString const& a_old_name, QString const& a_new_name);
    ~Entity_Name_Changed_Signal() override final;

    // Interface
    //============================================================
    using Abstract_Entity_Signal::source;
    using Abstract_Entity_Signal::type;
    using Abstract_Entity_Signal::id;

    QString const& old_name() const;
    QString const& new_name() const;
  };
}

#endif // SAK_ENTITY_NAME_CHANGED_SIGNAL_HPP
