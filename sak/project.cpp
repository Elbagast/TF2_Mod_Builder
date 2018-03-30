#include "project.hpp"

#include "entity_manager.hpp"
#include "entity_factory.hpp"

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
    void save() const;

    void load();

    // Data that is fixed on contruction.
    QString name() const;

    QString location() const;

    QString filepath() const;


    // Entity Interface
    //------------------------------------------------------------
    Entity_Manager& entity_manager();

    Entity_Manager const& centity_manager() const;
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

namespace
{
  sak::Entity_Factory do_make_factory()
  {
    using namespace sak;

    return Entity_Factory{};
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
  m_entity_manager{do_make_factory()}
{}

sak::Project::Implementation::~Implementation() = default;


// Interface
//============================================================


// Project Data
//------------------------------------------------------------
void sak::Project::Implementation::save() const
{
  //TODO
}

void sak::Project::Implementation::load()
{
  //TODO
}

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
sak::Entity_Manager& sak::Project::Implementation::entity_manager()
{
  return m_entity_manager;
}

sak::Entity_Manager const& sak::Project::Implementation::centity_manager() const
{
  return m_entity_manager;
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
void sak::Project::save() const
{
  cimp().save();
}

void sak::Project::load()
{
  imp().load();
}

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
sak::Entity_Manager& sak::Project::entity_manager()
{
  return imp().entity_manager();
}

sak::Entity_Manager const& sak::Project::centity_manager() const
{
  return cimp().centity_manager();
}

