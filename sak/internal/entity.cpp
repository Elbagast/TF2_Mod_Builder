#include "entity.hpp"

#include "abstract_entity_name.hpp"
#include "abstract_entity_type.hpp"
#include "abstract_entity_tooltip.hpp"
#include "abstract_entity_icon.hpp"

#include <cassert>

//---------------------------------------------------------------------------
// Entity
//---------------------------------------------------------------------------
// A container of component parts. Entity does not check the supplied id
// value for whether it is null or invalid. It has no way of knowing what
// makes a valid id at any time anyway. It also doesn't care if the
// supplied components are nullptr.

// Special 6
//============================================================
sak::Entity::Entity(Entity_ID a_id,
                    std::unique_ptr<Abstract_Entity_Type>&& a_type_component,
                    std::unique_ptr<Abstract_Entity_Tooltip>&& a_tooltip_component,
                    std::unique_ptr<Abstract_Entity_Icon>&& a_icon_component,
                    std::unique_ptr<Abstract_Entity_Name>&& a_name_component) :
  m_id{a_id},
  m_type_component{std::move(a_type_component)},
  m_tooltip_component{std::move(a_tooltip_component)},
  m_icon_component{std::move(a_icon_component)},
  m_name_component{std::move(a_name_component)}
{
}

sak::Entity::~Entity() = default;

sak::Entity::Entity(Entity && ) = default;
sak::Entity& sak::Entity::operator=(Entity && ) = default;

// Interface
//============================================================
sak::Entity_ID sak::Entity::id() const
{
  return m_id;
}

sak::Abstract_Entity_Type* sak::Entity::type_component()
{
  return m_type_component.get();
}

sak::Abstract_Entity_Tooltip* sak::Entity::tooltip_component()
{
  return m_tooltip_component.get();
}

sak::Abstract_Entity_Icon* sak::Entity::icon_component()
{
  return m_icon_component.get();
}

sak::Abstract_Entity_Name* sak::Entity::name_component()
{
  return m_name_component.get();
}

sak::Abstract_Entity_Type const* sak::Entity::ctype_component() const
{
  return m_type_component.get();
}

sak::Abstract_Entity_Tooltip const* sak::Entity::ctooltip_component() const
{
  return m_tooltip_component.get();
}

sak::Abstract_Entity_Icon const* sak::Entity::cicon_component() const
{
  return m_icon_component.get();
}

sak::Abstract_Entity_Name const* sak::Entity::cname_component() const
{
  return m_name_component.get();
}
