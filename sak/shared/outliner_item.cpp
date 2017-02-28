#include "outliner_item.hpp"

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
#include <sak/project.hpp>
#include <sak/outliner/project_item.hpp>
#include <sak/outliner/root_item.hpp>
#include <sak/shared/dispatch_signals.hpp> // does the signal stuff.

#include "object.hpp"
#include "manager.hpp"
#include "extended_manager.hpp"
#include "interface_traits.hpp"
#include "interface.hpp"

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
    auto l_files = cget_project().get_all_files();
    // sort them into whatever order and make the items
    for (auto const& l_file : l_files)
    {
      this->append_child(std::make_unique<item<T>>(this, l_file));
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
    return QVariant(QString::fromUtf8(u8"Files"));
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
  menu.addAction("Files context menu");

  // Create and add a new File
  auto l_action_add_file = menu.addAction("Add new File");
  QObject::connect(l_action_add_file, &QAction::triggered, [=]()
  {
    dispatch_signals<object_type>::command_make_new(&(this->get_project())); // outbound signal.
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
sak::Project& sak::shared::outliner::header_item<T>::get_project()
{
  return get_true_parent()->get_project();
}

template <typename T>
sak::Project const& sak::shared::outliner::header_item<T>::cget_project() const
{
  return get_true_parent()->cget_project();
}

// What index is the item that holds this extended_handle_type reside at?
// Returns get_child_count() if it is not found.
template <typename T>
std::size_t sak::shared::outliner::header_item<T>::index_of(extended_handle_type const& a_ehandle) const
{
  std::size_t l_index{0};
  for(auto l_end = static_cast<std::size_t>(inherited_type::get_child_count()); l_index != l_end; ++l_index)
  {
    if (get_true_child_at(static_cast<int>(l_index))->cget_ehandle() == a_ehandle)
    {
      break;
    }
  }
  return l_index;
}

// What item holds this extended_handle_type? Returns nullptr if not found.
template <typename T>
typename sak::shared::outliner::header_item<T>::child_type* sak::shared::outliner::header_item<T>::item_of(extended_handle_type const& a_ehandle) const
{
  auto l_index = static_cast<int>(index_of(a_ehandle));
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
void sak::shared::outliner::header_item<T>::name_changed(extended_handle_type const& a_ehandle)
{
  assert(a_ehandle.is_valid());
  // reorder the Files based on the sorting...
}

// When a File has been added, this is called.
template <typename T>
void sak::shared::outliner::header_item<T>::added(extended_handle_type const& a_ehandle)
{
  assert(a_ehandle.is_valid());
  // insert a child in a location that obeys the sorting...
  append_child(std::make_unique<item<T>>(this, a_ehandle));
}

// When a File has been removed, this is called.
template <typename T>
void sak::shared::outliner::header_item<T>::removed(extended_handle_type const& a_ehandle)
{
  assert(a_ehandle.is_valid());
  // insert the child with this data...
  remove_child(index_of(a_ehandle));
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------
// sak::shared::outliner::item<T>
//---------------------------------------------------------------------------
// Outliner item that represents a File of a Project.

// Special 6
//============================================================
template <typename T>
sak::shared::outliner::item<T>::item(parent_type* a_parent, extended_handle_type const& a_ehandle):
    inherited_type(a_parent),
    m_ehandle{a_ehandle}
{
  assert(a_parent != nullptr);
  assert(a_ehandle.is_valid());
}

template <typename T>
sak::shared::outliner::item<T>::~item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
template <typename T>
QVariant sak::shared::outliner::item<T>::get_data(int a_role) const
{
  if (a_role == Qt::DisplayRole)
  {
    return QVariant(cget_name());
  }
  else if (a_role == Qt::DecorationRole)
  {
    return QVariant(QIcon(QPixmap("D:\\Temp\\sak\\file_icon.png")));
  }
  else if (a_role == Qt::ToolTipRole)
  {
    return QVariant(cget_description());
  }
  else
  {
    return QVariant();
  }
}

// Set the data in item with the given value
template <typename T>
void sak::shared::outliner::item<T>::set_data(QVariant const& a_value)
{
  set_name(a_value.toString());
}

// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
template <typename T>
QWidget* sak::shared::outliner::item<T>::get_editor(QWidget* a_parent)
{
  return new QLineEdit(a_parent);
}

// Set the data in the editor to the value in the item
template <typename T>
void sak::shared::outliner::item<T>::set_editor_data(QWidget* a_editor)
{
  static_cast<QLineEdit*>(a_editor)->setText(cget_name());
}

// Get the data in the editor and return it
template <typename T>
QVariant sak::shared::outliner::item<T>::get_editor_data(QWidget* a_editor)
{
  return QVariant(static_cast<QLineEdit*>(a_editor)->text());
}

// Other
//----------------------------------------
// Get the flags for this item
template <typename T>
Qt::ItemFlags sak::shared::outliner::item<T>::get_flags() const
{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemNeverHasChildren;
}

// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing.  Position is the position in terms of
// the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
// to get the position relative to the window for a properly placed menu.
template <typename T>
void sak::shared::outliner::item<T>::do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position)
{
  shadup(a_view, a_model,a_position);

  QMenu menu{};
  menu.addAction("File context menu");
  menu.addAction(cget_name())->setEnabled(false);
  menu.addSeparator();

  // Open the main editor or focus on it if already open
  auto l_action_open = menu.addAction("Open");
  QObject::connect(l_action_open, &QAction::triggered, [this]()
  {
    dispatch_signals<object_type>::requests_editor(&(this->get_project()), this->m_ehandle);
  });

  // Commence an edit operation in the outliner
  auto l_action_rename = menu.addAction("Rename");
  QObject::connect(l_action_rename, &QAction::triggered, [=]()
  {
    a_view->edit(a_view->indexAt(a_position));
  });

  // Destroy this one
  auto l_action_delete = menu.addAction("Delete");
  QObject::connect(l_action_delete, &QAction::triggered, [=]()
  {
    dispatch_signals<object_type>::requests_editor(&(this->get_project()), this->m_ehandle); // outbound signal.
  });

  // Execute the menu at the global posiiton.
  menu.exec(a_view->viewport()->mapToGlobal(a_position));
}

// Do whatever we want when an item has been double clicked on.
template <typename T>
void sak::shared::outliner::item<T>::do_double_clicked(QAbstractItemView*, model_type*)
{
  dispatch_signals<object_type>::requests_editor(&(get_project()), m_ehandle); // outbound signal.
}

// Additional Interface
//============================================================
template <typename T>
sak::Project& sak::shared::outliner::item<T>::get_project()
{
  return get_true_parent()->get_project();
}

template <typename T>
sak::Project const& sak::shared::outliner::item<T>::cget_project() const
{
  return get_true_parent()->cget_project();
}

template <typename T>
typename sak::shared::outliner::item<T>::extended_handle_type const& sak::shared::outliner::item<T>::cget_ehandle() const
{
  return m_ehandle;
}

template <typename T>
QString sak::shared::outliner::item<T>::cget_name() const
{
  // Access the member for "Description" assumed to be at index 0
  return m_ehandle.cget().cat<0>().cget();
}

template <typename T>
void sak::shared::outliner::item<T>::set_name(QString const& a_name)
{
  m_ehandle.get().at<0>().set(a_name);
}

template <typename T>
QString sak::shared::outliner::item<T>::cget_description() const
{
  // Access the member for "Description" assumed to be at index 1
  return m_ehandle.cget().cat<1>().cget();
}




// Forced Instantiations
//============================================================
template sak::file::outliner::header_item;
template sak::file::outliner::item;
