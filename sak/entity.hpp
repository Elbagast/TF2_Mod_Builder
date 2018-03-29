#ifndef SAK_ENTITY_HPP
#define SAK_ENTITY_HPP

#ifndef SAK_ENTITY_FWD_HPP
#include "entity_fwd.hpp"
#endif

#ifndef SAK_ENTITY_ID_HPP
#include "entity_id.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

class QString;

namespace sak
{

  class Abstract_Entity_Name
  {
  public:
    virtual ~Abstract_Entity_Name() = default;
    virtual QString const& get_name() const = 0;
    virtual bool set_name(QString const&) = 0;

    // Do we just put the command and widget bit in here...?
  };

  class Abstract_Entity_Type
  {
  public:
    virtual ~Abstract_Entity_Type() = default;
    virtual QString const& get_type() const = 0;

    // Do we just put the command and widget bit in here...?
  };

  class Abstract_Entity_Tooltip
  {
  public:
    virtual ~Abstract_Entity_Tooltip() = default;
    virtual QString const& get_tooltip() const = 0;
  };

  class Abstract_Entity_Icon
  {
  public:
    virtual ~Abstract_Entity_Icon() = default;
    virtual QString const& get_iconpath() const = 0;
  };


  //---------------------------------------------------------------------------
  // Entity
  //---------------------------------------------------------------------------
  // A container of component parts.

  class Entity
  {
  private:
    // Data Members
    //============================================================
    Entity_ID m_id;
    std::unique_ptr<Abstract_Entity_Name> m_name_component;
    std::unique_ptr<Abstract_Entity_Type> m_type_component;
    std::unique_ptr<Abstract_Entity_Tooltip> m_tooltip_component;
    std::unique_ptr<Abstract_Entity_Icon> m_icon_component;

  public:
    // Special 6
    //============================================================
    Entity(Entity_ID a_id,
           std::unique_ptr<Abstract_Entity_Name>&& a_name_component,
           std::unique_ptr<Abstract_Entity_Type>&& a_type_component,
           std::unique_ptr<Abstract_Entity_Tooltip>&& a_tooltip_component,
           std::unique_ptr<Abstract_Entity_Icon>&& a_icon_component);
    ~Entity();

    // Block copying and moving so we don't end up duplicating the destruction
    // calls later.
    Entity(Entity const& a_other) = delete;
    Entity& operator=(Entity const& a_other) = delete;

    Entity(Entity && a_other) = delete;
    Entity& operator=(Entity && a_other) = delete;

    // Interface
    //============================================================
    Entity_ID id() const;

    Abstract_Entity_Name* name_component();
    Abstract_Entity_Type* type_component();
    Abstract_Entity_Tooltip* tooltip_component();
    Abstract_Entity_Icon* icon_component();

    Abstract_Entity_Name const* cname_component() const;
    Abstract_Entity_Type const* ctype_component() const;
    Abstract_Entity_Tooltip const* ctooltip_component() const;
    Abstract_Entity_Icon const* cicon_component() const;
  };
}

#endif // SAK_ENTITY_HPP
