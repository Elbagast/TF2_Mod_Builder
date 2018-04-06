#ifndef SAK_ENTITY_HPP
#define SAK_ENTITY_HPP

// This Header's Forward Header
//============================================================
#ifndef SAK_ENTITY_FWD_HPP
#include "entity_fwd.hpp"
#endif

// SAK Forwarding Headers
//============================================================
#ifndef SAK_ABSTRACT_ENTITY_NAME_FWD_HPP
#include "abstract_entity_name_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_ENTITY_TYPE_FWD_HPP
#include "abstract_entity_type_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_ENTITY_TOOLTIP_FWD_HPP
#include "abstract_entity_tooltip_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_ENTITY_ICON_FWD_HPP
#include "abstract_entity_icon_fwd.hpp"
#endif

// SAK Headers
//============================================================
#ifndef SAK_ENTITY_ID_HPP
#include "entity_id.hpp"
#endif

// Standard Headers
//============================================================
#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_STRING
#define INCLUDE_STD_STRING
#include <string>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Entity
  //---------------------------------------------------------------------------
  // A container of component parts. Entity does not check the supplied id
  // value for whether it is null or invalid. It has no way of knowing what
  // makes a valid id at any time anyway. It also doesn't care if the
  // supplied components are nullptr.

  class Entity
  {
  private:
    // Data Members
    //============================================================
    Entity_ID m_id;
    std::unique_ptr<Abstract_Entity_Type> m_type_component;
    std::unique_ptr<Abstract_Entity_Name> m_name_component;
    std::unique_ptr<Abstract_Entity_Tooltip> m_tooltip_component;
    std::unique_ptr<Abstract_Entity_Icon> m_icon_component;

  public:
    // Special 6
    //============================================================
    // Auto convert component pointer types to the abstract pointer types.
    template <typename T_Name, typename T_Type, typename T_Tooltip, typename T_Icon>
    Entity(Entity_ID a_id,
           std::unique_ptr<T_Type>&& a_type_component,
           std::unique_ptr<T_Name>&& a_name_component,
           std::unique_ptr<T_Tooltip>&& a_tooltip_component,
           std::unique_ptr<T_Icon>&& a_icon_component):
      Entity(a_id,
             std::unique_ptr<Abstract_Entity_Type>{a_type_component.release()},
             std::unique_ptr<Abstract_Entity_Name>{a_name_component.release()},
             std::unique_ptr<Abstract_Entity_Tooltip>{a_tooltip_component.release()},
             std::unique_ptr<Abstract_Entity_Icon>{a_icon_component.release()})
    {}

    Entity(Entity_ID a_id,
           std::unique_ptr<Abstract_Entity_Type>&& a_type_component,
           std::unique_ptr<Abstract_Entity_Name>&& a_name_component,
           std::unique_ptr<Abstract_Entity_Tooltip>&& a_tooltip_component,
           std::unique_ptr<Abstract_Entity_Icon>&& a_icon_component);
    ~Entity();

    // Block copying so we don't break components.
    Entity(Entity const& a_other) = delete;
    Entity& operator=(Entity const& a_other) = delete;

    // Can move mostly so we don't have to reveal the handle system in the factory.
    Entity(Entity && a_other);
    Entity& operator=(Entity && a_other);

    // Interface
    //============================================================
    Entity_ID id() const;

    Abstract_Entity_Type* type_component();
    Abstract_Entity_Name* name_component();
    Abstract_Entity_Tooltip* tooltip_component();
    Abstract_Entity_Icon* icon_component();

    Abstract_Entity_Type const* ctype_component() const;
    Abstract_Entity_Name const* cname_component() const;
    Abstract_Entity_Tooltip const* ctooltip_component() const;
    Abstract_Entity_Icon const* cicon_component() const;
  };
}

#endif // SAK_ENTITY_HPP
