#include "header_item.hpp"

#include <cassert>
#include <algorithm>
#include <limits>
#include <vector>

#include <QDebug>
#include <QString>
#include <QVariant>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QAbstractItemView>
#include <QPixmap>
#include <QIcon>

#include <qtlib/outliner/model.hpp>
#include <sak/project/object.hpp>
#include <sak/project/outliner/project_item.hpp>
#include <sak/project/outliner/root_item.hpp>

#include <sak/shared/interface.hpp>
#include <sak/shared/manager.hpp>

namespace
{
  template <typename... Args>
  void shadup(Args&&...)
  {

  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------
// sak::shared::outliner::header_item<T>
//---------------------------------------------------------------------------
// Outliner item that represents the File container of a Project. It's children
// are all the Files present in the Project.

// Special 6
//============================================================
template <typename T>
sak::shared::outliner::header_item<T>::header_item(parent_type* a_parent, bool a_read_files):
    inherited_type(a_parent)
{
  if (a_read_files)
  {
    auto l_handles = this->get_project().get_interface<T>().get_all();

    // sort them into whatever order and make the items
    for (auto const& l_handle : l_handles)
    {
      this->append_child(std::make_unique<item<T>>(this, l_handle));
    }
  }
}

template <typename T>
sak::shared::outliner::header_item<T>::~header_item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
template <typename T>
QVariant sak::shared::outliner::header_item<T>::get_data(int a_role) const
{
  if (a_role == Qt::DisplayRole)
  {
    return QVariant(QString::fromStdString(object_type::type()) + u8"s");
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
template <typename T>
void sak::shared::outliner::header_item<T>::do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position)
{
  shadup(a_view, a_model,a_position);

  QMenu menu{};
  menu.addAction(QString::fromStdString(object_type::type()) + "s context menu");

  // Create and add a new File
  auto l_action_add_file = menu.addAction("Add new " + QString::fromStdString(object_type::type()));
  QObject::connect(l_action_add_file, &QAction::triggered, [=]()
  {
    this->get_project().get_interface<T>().add_default();
  });

  menu.addAction(QString::number(this->get_child_count()));

  // Execute the menu at the global posiiton.
  menu.exec(a_view->viewport()->mapToGlobal(a_position));
}

// Do whatever we want when an item has been double clicked on.
template <typename T>
void sak::shared::outliner::header_item<T>::do_double_clicked(QAbstractItemView* a_view, model_type* a_model)
{
  return this->item_type::do_double_clicked(a_view, a_model);
}

// Additional Interface
//============================================================
template <typename T>
sak::project::object& sak::shared::outliner::header_item<T>::get_project()
{
  return get_true_parent()->get_project();
}

template <typename T>
sak::project::object const& sak::shared::outliner::header_item<T>::cget_project() const
{
  return get_true_parent()->cget_project();
}

// What index is the item that holds this handle_type reside at?
// Returns get_child_count() if it is not found.
template <typename T>
std::size_t sak::shared::outliner::header_item<T>::index_of(handle_type const& a_handle) const
{
  std::size_t l_index{0};
  for(auto l_end = static_cast<std::size_t>(inherited_type::get_child_count()); l_index != l_end; ++l_index)
  {
    if (get_true_child_at(static_cast<int>(l_index))->cget_handle() == a_handle)
    {
      break;
    }
  }
  return l_index;
}

// What item holds this handle_type? Returns nullptr if not found.
template <typename T>
typename sak::shared::outliner::header_item<T>::child_type* sak::shared::outliner::header_item<T>::item_of(handle_type const& a_handle) const
{
  auto l_index = static_cast<int>(index_of(a_handle));
  if (l_index != get_child_count())
  {
    return get_true_child_at(l_index);
  }
  else
  {
    return nullptr;
  }
}

// When a File has had its name changed, this is called.
template <typename T>
void sak::shared::outliner::header_item<T>::name_changed(handle_type const& a_handle)
{
  assert(a_handle.is_valid());
  // reorder the Files based on the sorting...
}

// When a File has been added, this is called.
template <typename T>
void sak::shared::outliner::header_item<T>::added(handle_type const& a_handle)
{
  assert(a_handle.is_valid());
  // insert a child in a location that obeys the sorting...
  append_child(std::make_unique<item<T>>(this, a_handle));
}

// When a File has been removed, this is called.
template <typename T>
void sak::shared::outliner::header_item<T>::removed(handle_type const& a_handle)
{
  assert(a_handle.is_valid());
  // insert the child with this data...
  remove_child(index_of(a_handle));
}

// Forced Instantiations
//============================================================
template sak::file::outliner::header_item;
template sak::texture::outliner::header_item;
