﻿#ifndef SAK_TESTING_DUMMY_ENTITY_MAKER_HPP
#define SAK_TESTING_DUMMY_ENTITY_MAKER_HPP

#ifndef SAK_ENTITY_ID_FWD_HPP
#include <sak/entity_id_fwd.hpp>
#endif

#ifndef SAK_ENTITY_HANDLE_FWD_HPP
#include <sak/entity_handle_fwd.hpp>
#endif

#ifndef SAK_ABSTRACT_ENTITY_MAKER_HPP
#include <sak/abstract_entity_maker.hpp>
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif


namespace sak
{
  //---------------------------------------------------------------------------
  // Dummy_Entity_Maker
  //---------------------------------------------------------------------------
  // Thing that makes dummy entities for testing.

  class Dummy_Entity_Maker :
      public Abstract_Entity_Maker
  {
  public:
    // Special 6
    //============================================================
    Dummy_Entity_Maker();
    ~Dummy_Entity_Maker() override final;

    // Interface
    //============================================================
    // Get the typestring for this Entity type.
    QString type() const override final;

    // Make a new Entity of this type with the supplied id. If the supplied id
    // is invalid then the handle is a null handle and no entity data was
    // created.
    Entity_Handle make_entity(Entity_ID a_id) const override final;

    // Make a Dummy_Entity_Maker so that it can be installed.
    static std::unique_ptr<Abstract_Entity_Maker> make_self();
  };
}

#endif // SAK_TESTING_DUMMY_ENTITY_MAKER_HPP
