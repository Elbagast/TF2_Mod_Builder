#include "project_outliner_items.hpp"

#include <QDebug>
#include <QString>
#include <QVariant>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QAbstractItemView>

//#include <qtlib/outliner/model.hpp>
#include "outliner_model.hpp"

#include "project_interface.hpp"

#include "section_interface.hpp"
#include "section_outliner_items.hpp"

namespace
{
  template <typename... Args>
  void unused(Args&&...)
  {

  }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------
// sak::Project_Outliner_Root_Item
//---------------------------------------------------------------------------
// Outliner root item for a single project. This item is invisible and
// defines the default context menu.

// Special 6
//============================================================
sak::Project_Outliner_Root_Item::Project_Outliner_Root_Item(Project_Interface* a_project):
  internal::Project_Outliner_Root_Item_Base(),
  m_project{a_project}
{
  this->set_true_child(std::make_unique<Child_Item_Type>(this));
}
sak::Project_Outliner_Root_Item::~Project_Outliner_Root_Item() = default;

// Virtual Interface
//============================================================
// Other
//----------------------------------------
// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing.  Position is the position in terms of
// the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
// to get the position relative to the window for a properly placed menu.
void sak::Project_Outliner_Root_Item::do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position)
{
  // silence warnings for arguments we don't use in this implementation
  unused(a_view, a_model, a_position);

  QMenu menu{};
  menu.addAction("Root context menu");
  menu.addSeparator();
  menu.addAction("blah blah blah");
  menu.exec(a_view->viewport()->mapToGlobal(a_position));
}

// Do whatever we want when an item has been double clicked on.
void sak::Project_Outliner_Root_Item::do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model)
{
  return Abstract_Outliner_Item::do_double_clicked(a_view, a_model);
}

// Additional Interface
//============================================================
sak::Project_Interface* sak::Project_Outliner_Root_Item::get_project()
{
  return m_project;
}

sak::Project_Interface const* sak::Project_Outliner_Root_Item::cget_project() const
{
  return m_project;
}

sak::Project_Outliner_Project_Item* sak::Project_Outliner_Root_Item::get_project_item() const
{
  return this->get_true_child();
}

sak::File_Outliner_Header_Item* sak::Project_Outliner_Root_Item::file_header_item() const
{
  return this->get_true_child()->file_header_item();
}

sak::Texture_Outliner_Header_Item* sak::Project_Outliner_Root_Item::texture_header_item() const
{
  return this->get_true_child()->texture_header_item();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------
// sak::Project_Outliner_Project_Item
//---------------------------------------------------------------------------
// Outliner item that represents a Project. It's data is the Project's name.

// Special 6
//============================================================
sak::Project_Outliner_Project_Item::Project_Outliner_Project_Item(Parent_Item_Type* a_parent):
    internal::Project_Outliner_Project_Item_Base(a_parent)
{
  initialise_files(true);
  initialise_textures(true);
}
sak::Project_Outliner_Project_Item::~Project_Outliner_Project_Item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
QVariant sak::Project_Outliner_Project_Item::get_data(int a_role) const
{
  if (a_role == Qt::DisplayRole)
  {
    return QVariant(cget_project()->name());
  }
  else
  {
    return QVariant();
  }
}

// Other
//----------------------------------------
// Get the flags for this item
Qt::ItemFlags sak::Project_Outliner_Project_Item::get_flags() const
{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing.  Position is the position in terms of
// the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
// to get the position relative to the window for a properly placed menu.
void sak::Project_Outliner_Project_Item::do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position)
{
  // silence warnings for arguments we don't use in this implementation
  unused(a_view, a_model, a_position);

  QMenu menu{};
  menu.addAction("Project context menu");
  menu.addAction(cget_project()->name())->setEnabled(false);
  menu.addSeparator();
  // Create and add a new File
  auto l_action_add_file = menu.addAction("Add new File");
  QObject::connect(l_action_add_file, &QAction::triggered, [this]()
  {
    this->get_project()->get_file_interface().add_default();
  });
  auto l_action_add_texture = menu.addAction("Add new Texture");
  QObject::connect(l_action_add_texture, &QAction::triggered, [this]()
  {
    this->get_project()->get_texture_interface().add_default();
  });

  menu.exec(a_view->viewport()->mapToGlobal(a_position));
}

// Do whatever we want when an item has been double clicked on.
void sak::Project_Outliner_Project_Item::do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model)
{
  return this->Abstract_Outliner_Item::do_double_clicked(a_view, a_model);
}

// Additional Interface
//============================================================
sak::Project_Interface* sak::Project_Outliner_Project_Item::get_project()
{
  return get_true_parent()->get_project();
}
sak::Project_Interface const* sak::Project_Outliner_Project_Item::cget_project() const
{
  return get_true_parent()->cget_project();
}

sak::File_Outliner_Header_Item* sak::Project_Outliner_Project_Item::file_header_item() const
{
  return this->get_true_child<0>();
}

void sak::Project_Outliner_Project_Item::initialise_files(bool a_read_files)
{
  this->set_child<0>(std::make_unique<Child_Item_Type<0>>(this, a_read_files));
}

void sak::Project_Outliner_Project_Item::close_files()
{
  if (get_project()->get_file_interface().not_empty())
  {
    this->remove_child<0>();
  }
}

sak::Texture_Outliner_Header_Item* sak::Project_Outliner_Project_Item::texture_header_item() const
{
  return this->get_true_child<1>();
}

void sak::Project_Outliner_Project_Item::initialise_textures(bool a_read)
{
  this->set_child<1>(std::make_unique<Child_Item_Type<1>>(this, a_read));
}

void sak::Project_Outliner_Project_Item::close_textures()
{
  if (get_project()->get_texture_interface().not_empty())
  {
    this->remove_child<1>();
  }
}
