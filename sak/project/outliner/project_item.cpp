#include "project_item.hpp"

#include <QDebug>
#include <QString>
#include <QVariant>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QAbstractItemView>

#include <qtlib/outliner/model.hpp>
#include <sak/project/object.hpp>
//#include <sak/project/signalbox.hpp>
#include <sak/shared/project_access.hpp>
#include <sak/shared/outliner/header_item.hpp>
#include "root_item.hpp"

namespace
{
  template <typename... Args>
  void shadup(Args&&...)
  {

  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------
// sak::outliner::Project_Item
//---------------------------------------------------------------------------
// Outliner item that represents a Project. It's data is the Project's name.

// Special 6
//============================================================
sak::project::outliner::project_item::project_item(parent_type* a_parent):
    inherited_type(a_parent)
{
  initialise_files(true);
  initialise_textures(true);
}
sak::project::outliner::project_item::~project_item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
QVariant sak::project::outliner::project_item::get_data(int a_role) const
{
  if (a_role == Qt::DisplayRole)
  {
    return QVariant(cget_project().name());
  }
  else
  {
    return QVariant();
  }
}

// Other
//----------------------------------------
// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing.  Position is the position in terms of
// the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
// to get the position relative to the window for a properly placed menu.
void sak::project::outliner::project_item::do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position)
{
  shadup(a_view, a_model,a_position);

  QMenu menu{};
  menu.addAction("Project context menu");
  menu.addAction(cget_project().name())->setEnabled(false);
  menu.addSeparator();
  // Create and add a new File
  auto l_action_add_file = menu.addAction("Add new File");
  QObject::connect(l_action_add_file, &QAction::triggered, [this]()
  {
    file::project_access::add_new(this->get_project());
  });
  auto l_action_add_texture = menu.addAction("Add new Texture");
  QObject::connect(l_action_add_texture, &QAction::triggered, [this]()
  {
    texture::project_access::add_new(this->get_project());
  });

  menu.exec(a_view->viewport()->mapToGlobal(a_position));
}

// Do whatever we want when an item has been double clicked on.
void sak::project::outliner::project_item::do_double_clicked(QAbstractItemView* a_view, model_type* a_model)
{
  return this->item_type::do_double_clicked(a_view, a_model);
}

// Additional Interface
//============================================================
sak::project::object& sak::project::outliner::project_item::get_project()
{
  return get_true_parent()->get_project();
}
sak::project::object const& sak::project::outliner::project_item::cget_project() const
{
  return get_true_parent()->cget_project();
}

sak::file::outliner::header_item* sak::project::outliner::project_item::file_header_item() const
{
  return this->get_true_child<0>();
}

void sak::project::outliner::project_item::initialise_files(bool a_read_files)
{
  this->set_child<0>(std::make_unique<child_type<0>>(this, a_read_files));
}

void sak::project::outliner::project_item::close_files()
{
  if (!cget_project().has_files())
  {
    this->remove_child<0>();
  }
}


sak::texture::outliner::header_item* sak::project::outliner::project_item::texture_header_item() const
{
  return this->get_true_child<1>();
}

void sak::project::outliner::project_item::initialise_textures(bool a_read)
{
  this->set_child<1>(std::make_unique<child_type<1>>(this, a_read));
}

void sak::project::outliner::project_item::close_textures()
{
  if (!cget_project().has_textures())
  {
    this->remove_child<1>();
  }
}
