﻿#ifndef SAK_PROJECT_HPP
#define SAK_PROJECT_HPP

#ifndef SAK_PROJECT_FWD_HPP
#include "project_fwd.hpp"
#endif

#ifndef SAK_ENTITY_MANAGER_FWD_HPP
#include <sak/entity_manager_fwd.hpp>
#endif

#ifndef SAK_ENTITY_ID_FWD_HPP
#include <sak/entity_id_fwd.hpp>
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

class QString;
class QWidget;

namespace sak
{
  class Entity_Editor_Wdiget;

  //---------------------------------------------------------------------------
  // Project
  //---------------------------------------------------------------------------
  // A Project contains a number of entities and is stored in a file. It uses
  // the pimpl idiom so that the classes that need to access a project don't
  // have to know about how its implemented.

  class Project
  {
  private:
    // Data Members
    //============================================================
    class Implementation;
    std::unique_ptr<Implementation> m_imp;

    Implementation& imp()               { return *m_imp; }
    Implementation const& cimp() const  { return *m_imp; }

  public:
    // Special 6
    //============================================================
    explicit Project(QString const& a_filepath);
    ~Project();

    Project(Project const&) = delete;
    Project& operator=(Project const&) = delete;

    Project(Project &&) = delete;
    Project& operator=(Project &&) = delete;

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


#endif // SAK_PROJECT_HPP