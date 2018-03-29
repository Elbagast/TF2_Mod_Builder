#ifndef SAK_ENTITY_FACTORY_HPP
#define SAK_ENTITY_FACTORY_HPP

#ifndef SAK_ENTITY_FACTORY_FWD_HPP
#include "entity_factory_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_ENTITY_MAKER_FWD_HPP
#include "abstract_entity_maker_fwd.hpp"
#endif

#ifndef SAK_ENTITY_ID_FWD_HPP
#include "entity_id_fwd.hpp"
#endif

#ifndef SAK_ENTITY_HANDLE_FWD_HPP
#include "entity_handle_fwd.hpp"
#endif

#ifndef INCLUDE_STD_MAP
#define INCLUDE_STD_MAP
#include <map>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_QT_QSTRING
#define INCLUDE_QT_QSTRING
#include <QString>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Entity_Factory
  //---------------------------------------------------------------------------
  // Make an entity using the supplied id. If the id is null the handle is null
  // and no entity data was created.

  class Entity_Factory
  {
  private:
    // Data Members
    //============================================================
    mutable Entity_ID_Value_Type m_next_id;
    std::map<QString, std::unique_ptr<Abstract_Entity_Maker> > m_makers;

  public:
    // Special 6
    //============================================================
    // Create with a set of built in Entity makers.
    Entity_Factory();
    ~Entity_Factory();

    // Block copying because we hold lots of unique_ptrs.
    Entity_Factory(Entity_Factory const& a_other) = delete;
    Entity_Factory& operator=(Entity_Factory const& a_other) = delete;

    // Block moving because things will possibly hold a pointer to held data.
    Entity_Factory(Entity_Factory && a_other) = delete;
    Entity_Factory& operator=(Entity_Factory && a_other) = delete;

    // Interface
    //============================================================
    // Is this a type of Entity we can make?
    bool has_type(QString const& a_type) const;

    // Get all of the available Entity types.
    std::vector<QString> all_types() const;

    // Make this kind of Entity. It will have its name set to the type and the
    // data is default initialised to empty. If the returned handle is destroyed
    // before being copied or moved, the Entity data is also destroyed. If the
    // type supplied is not one that can be made, then the handle is a null
    // handle.
    Entity_Handle make_entity(QString const& a_type) const;

    // Attempt to add this maker to the collection. If it's type is not already
    // present it will be added and true is returned. If a maker with the same
    // type is already present nothing happens and false is returned.
    bool add_maker(std::unique_ptr<Abstract_Entity_Maker>&& a_maker);
  };
}

#endif // SAK_ENTITY_FACTORY_HPP
