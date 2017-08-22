#include "item.hpp"

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
#include <sak/shared/outliner/header_item.hpp>

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
// sak::shared::outliner::item<T>
//---------------------------------------------------------------------------
// Outliner item that represents a File of a Project.

// Special 6
//============================================================
template <typename T>
sak::shared::outliner::item<T>::item(parent_type* a_parent, handle_type const& a_ehandle):
    inherited_type(a_parent),
    m_handle{a_ehandle}
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
    this->get_project().get_interface<T>().request_editor(this->m_handle);
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
    this->get_project().get_interface<T>().remove(this->m_handle);
  });

  // Execute the menu at the global posiiton.
  menu.exec(a_view->viewport()->mapToGlobal(a_position));
}

// Do whatever we want when an item has been double clicked on.
template <typename T>
void sak::shared::outliner::item<T>::do_double_clicked(QAbstractItemView*, model_type*)
{
  this->get_project().get_interface<T>().request_editor(this->m_handle);
}

// Additional Interface
//============================================================
template <typename T>
sak::project::object& sak::shared::outliner::item<T>::get_project()
{
  return get_true_parent()->get_project();
}

template <typename T>
sak::project::object const& sak::shared::outliner::item<T>::cget_project() const
{
  return get_true_parent()->cget_project();
}

template <typename T>
typename sak::shared::outliner::item<T>::handle_type const& sak::shared::outliner::item<T>::cget_handle() const
{
  return m_handle;
}

template <typename T>
QString sak::shared::outliner::item<T>::cget_name() const
{
  // Access the member for "Name" assumed to be at index 0
  return m_handle.cget().cmember_at<0>().cget();
}

template <typename T>
void sak::shared::outliner::item<T>::set_name(QString const& a_name)
{
  // Issue the command to change the name.
  this->get_project().get_interface<T>().change_at<0>(m_handle, a_name);
}

template <typename T>
QString sak::shared::outliner::item<T>::cget_description() const
{
  // Access the member for "Description" assumed to be at index 1
  return m_handle.cget().cmember_at<1>().cget();
}

// Forced Instantiations
//============================================================
template sak::file::outliner::item;
template sak::texture::outliner::item;
