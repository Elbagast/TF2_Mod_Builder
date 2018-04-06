#include "abstract_project_outliner_root_item.hpp"

#include <cassert>

//---------------------------------------------------------------------------
// Abstract_Outliner_Project_Root_Item
//---------------------------------------------------------------------------
// In order to allow the outliner to show the data in different ways that
// allow it to not care about the specific item types. This means the outliner
// widget sends changes to this which then handles how things update.

// Special 6
//============================================================
sak::Abstract_Outliner_Project_Root_Item::Abstract_Outliner_Project_Root_Item(Project* a_project):
  m_project{a_project}
{
  assert(m_project != nullptr);
}

sak::Abstract_Outliner_Project_Root_Item::~Abstract_Outliner_Project_Root_Item() = default;

// Project Stuff
//----------------------------------------
sak::Project* sak::Abstract_Outliner_Project_Root_Item::project()
{
  return m_project;
}

sak::Project const* sak::Abstract_Outliner_Project_Root_Item::cproject() const
{
  return m_project;
}





sak::Dummy_Outliner_Project_Root_Item::Dummy_Outliner_Project_Root_Item(Project* a_project):
  Abstract_Outliner_Project_Root_Item(a_project)
{}

sak::Dummy_Outliner_Project_Root_Item::~Dummy_Outliner_Project_Root_Item() = default;

