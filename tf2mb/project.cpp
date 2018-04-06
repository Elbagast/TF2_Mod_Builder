#include "project.hpp"

#include <sak/entity_manager.hpp>
#include <sak/entity_id.hpp>
#include <sak/entity_definition.hpp>
/*
#include <sak/internal/abstract_entity_maker.hpp>
#include <sak/internal/entity.hpp>
#include <sak/internal/entity_name.hpp>
#include <sak/internal/entity_type.hpp>
#include <sak/internal/entity_tooltip.hpp>
#include <sak/internal/entity_icon.hpp>

*/
#include <cassert>
#include <iostream>

#include <QFileInfo>
#include <QDir>
#include <QString>

namespace sak
{
  //---------------------------------------------------------------------------
  // sak::Project::Implementation
  //---------------------------------------------------------------------------
  // Basically we build everything here so we can hide the details and call all
  // these functions as forwarding functions.

  class Project::Implementation
  {
  private:
    // Data Members
    //============================================================
    QFileInfo m_filepath;
    Entity_Manager m_entity_manager;

  public:
    // Special 6
    //============================================================
    explicit Implementation(QString const& a_filepath);
    ~Implementation();

    Implementation(Implementation const&) = delete;
    Implementation& operator=(Implementation const&) = delete;

    Implementation(Implementation &&) = delete;
    Implementation& operator=(Implementation &&) = delete;

    // Interface
    //============================================================

    // Project Data
    //------------------------------------------------------------

    // Data that is fixed on contruction.
    QString name() const;

    QString location() const;

    QString filepath() const;


    // Entity Interface
    //------------------------------------------------------------
    Entity_Manager* entity_manager();
    Entity_Manager const* centity_manager() const;
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
/*
namespace sak
{
  //---------------------------------------------------------------------------
  // Empty_Entity_Maker
  //---------------------------------------------------------------------------
  // Make Entities that have a specific type and that's it.

  class Empty_Entity_Maker :
      public Abstract_Entity_Maker
  {
  private:
    // Data Members
    //============================================================
    std::string const m_type;
    std::string const m_tooltip;
    std::string const m_iconpath;

  public:
    // Special 6
    //============================================================
    Empty_Entity_Maker(std::string const& a_type, std::string const& a_tooltip, std::string const& a_iconpath);
    ~Empty_Entity_Maker() override final;

    // Interface
    //============================================================
    // Get the typestring for this Entity type.
    std::string type() const override final;

    // Make a new Entity of this type with the supplied id. If the supplied id
    // is invalid then the handle is a null handle and no entity data was
    // created.
    Entity make_entity(Entity_ID a_id) const override final;
  };
}
//---------------------------------------------------------------------------
// Empty_Entity_Maker
//---------------------------------------------------------------------------
// Make Entities that have a specific type and that's it.

// Special 6
//============================================================
sak::Empty_Entity_Maker::Empty_Entity_Maker(std::string const& a_type, std::string const& a_tooltip, std::string const& a_iconpath) :
  Abstract_Entity_Maker(),
  m_type{a_type},
  m_tooltip{a_tooltip},
  m_iconpath{a_iconpath}
{
  assert(!m_type.empty());
}
sak::Empty_Entity_Maker::~Empty_Entity_Maker() = default;

// Interface
//============================================================
// Get the typestring for this Entity type.
std::string sak::Empty_Entity_Maker::type() const
{
  return m_type;
}

// Make a new Entity of this type with the supplied id. If the supplied id
// is invalid then the handle is a null handle and no entity data was
// created.
sak::Entity sak::Empty_Entity_Maker::make_entity(Entity_ID a_id) const
{
  return Entity
  {
    a_id,
    std::make_unique<Entity_Name>(m_type),
    std::make_unique<Remote_Entity_Type>(m_type),
    std::make_unique<Remote_Entity_Tooltip>(m_tooltip),
    std::make_unique<Remote_Entity_Icon>(m_iconpath)
  };
}
*/
namespace
{
  /*
  std::vector<std::unique_ptr<sak::Abstract_Entity_Maker>> do_make_entity_makers()
  {
    using namespace sak;

    std::vector<std::unique_ptr<sak::Abstract_Entity_Maker>> l_result{};

    l_result.push_back(std::make_unique<sak::Empty_Entity_Maker>(u8"Texture",u8"This is a Texture.",u8""));
    l_result.push_back(std::make_unique<sak::Empty_Entity_Maker>(u8"Material",u8"This is a Material.",u8""));

    return l_result;
  }*/

  std::vector<sak::Entity_Definition> do_make_entity_defs()
  {
    using namespace sak;

    std::vector<sak::Entity_Definition> l_result{};

    l_result.push_back(Entity_Definition{u8"Texture",u8"This is a Texture.",u8""});
    l_result.push_back(Entity_Definition{u8"Material",u8"This is a Material.",u8""});

    return l_result;
  }

}


//---------------------------------------------------------------------------
// sak::Project::Implementation
//---------------------------------------------------------------------------
// A Project contains a number of entities.

// Special 6
//============================================================
sak::Project::Implementation::Implementation(QString const& a_filepath) :
  m_filepath{a_filepath},
  m_entity_manager{do_make_entity_defs()}
{
  std::cout << "Entity Types:" << std::endl;
  for (auto const& l_type : this->centity_manager()->get_all_types())
  {
    std::cout << l_type << std::endl;
  }

}

sak::Project::Implementation::~Implementation() = default;


// Interface
//============================================================


// Project Data
//------------------------------------------------------------

// Data that is fixed on contruction.
QString sak::Project::Implementation::name() const
{
  return m_filepath.baseName();
}

QString sak::Project::Implementation::location() const
{
  return m_filepath.absoluteDir().absolutePath();
}

QString sak::Project::Implementation::filepath() const
{
  return m_filepath.absoluteFilePath();
}

// Entity Interface
//------------------------------------------------------------
sak::Entity_Manager* sak::Project::Implementation::entity_manager()
{
  return std::addressof(m_entity_manager);
}

sak::Entity_Manager const* sak::Project::Implementation::centity_manager() const
{
  return std::addressof(m_entity_manager);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------
// sak::Project
//---------------------------------------------------------------------------
// A Project contains a number of entities.

// Special 6
//============================================================
sak::Project::Project(QString const& a_filepath) :
  m_imp{std::make_unique<Implementation>(a_filepath)}
{
}

sak::Project::~Project() = default;


// Interface
//============================================================

// Project Data
//------------------------------------------------------------

// Data that is fixed on contruction.
QString sak::Project::name() const
{
  return cimp().name();
}

QString sak::Project::location() const
{
  return cimp().location();
}

QString sak::Project::filepath() const
{
  return cimp().filepath();
}


// Entity Interface
//------------------------------------------------------------
sak::Entity_Manager* sak::Project::entity_manager()
{
  return imp().entity_manager();
}

sak::Entity_Manager const* sak::Project::centity_manager() const
{
  return cimp().centity_manager();
}
