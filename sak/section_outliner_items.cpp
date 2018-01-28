#include "section_outliner_items.hpp"

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

//#include <qtlib/outliner/model.hpp>

#include "outliner_model.hpp"

#include "project_interface.hpp"
#include "project_outliner_items.hpp"
#include "section_interface.hpp"
#include "section_handle.hpp"
#include "section_data.hpp"

namespace
{
  template <typename... Args>
  void unused(Args&&...)
  {

  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Section_Outliner_Item<T>
//---------------------------------------------------------------------------

// Outliner item that represents a File of a Project.

// Special 6
//============================================================
template <typename T>
sak::Section_Outliner_Item<T>::Section_Outliner_Item(Parent_Item_Type* a_parent, Handle_Type const& a_handle):
    Inherited_Type(a_parent),
    m_handle{a_handle}
{
  assert(a_parent != nullptr);
  assert(flamingo::not_null(a_handle));
}

template <typename T>
sak::Section_Outliner_Item<T>::~Section_Outliner_Item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
template <typename T>
QVariant sak::Section_Outliner_Item<T>::get_data(int a_role) const
{
  if (a_role == Qt::DisplayRole)
  {
    return QVariant(cget_name());
  }
  else if (a_role == Qt::DecorationRole)
  {
    static QString const s_iconpath{ QString::fromStdString(T::iconpath()) };
    // Going to need an icon for each type
    return QVariant(QIcon(QPixmap(s_iconpath)));
  }
  else if (a_role == Qt::ToolTipRole)
  {
    // No tooltips for now.
    return QVariant();
    //return QVariant(cget_description());
  }
  else
  {
    return QVariant();
  }
}

// Set the data in item with the given value
template <typename T>
void sak::Section_Outliner_Item<T>::set_data(QVariant const& a_value)
{
  set_name(a_value.toString());
}

// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
template <typename T>
QWidget* sak::Section_Outliner_Item<T>::get_editor(QWidget* a_parent)
{
  using Member_Type = Section_Data_Member_Type<0,T>;
  auto l_widget = Member_Type::make_empty_widget();
  l_widget->setParent(a_parent);

  return l_widget.release();
}

// Set the data in the editor to the value in the item
template <typename T>
void sak::Section_Outliner_Item<T>::set_editor_data(QWidget* a_editor)
{
  using Member_Type = Section_Data_Member_Type<0,T>;
  Member_Type::set_widget_value(a_editor, cget_name());
}

// Get the data in the editor and return it
template <typename T>
QVariant sak::Section_Outliner_Item<T>::get_editor_data(QWidget* a_editor)
{
  using Member_Type = Section_Data_Member_Type<0,T>;
  return QVariant(Member_Type::get_widget_value(a_editor));
}

// Other
//----------------------------------------
// Get the flags for this item
template <typename T>
Qt::ItemFlags sak::Section_Outliner_Item<T>::get_flags() const
{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemNeverHasChildren;
}

// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing.  Position is the position in terms of
// the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
// to get the position relative to the window for a properly placed menu.
template <typename T>
void sak::Section_Outliner_Item<T>::do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position)
{
  unused(a_view, a_model,a_position);

  QMenu menu{};
  menu.addAction("File context menu");
  menu.addAction(cget_name())->setEnabled(false);
  menu.addSeparator();

  // Open the main editor or focus on it if already open
  auto l_action_open = menu.addAction("Open");
  QObject::connect(l_action_open, &QAction::triggered, [this]()
  {
    this->get_project()->get_interface<T>().request_editor(this->m_handle);
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
    this->get_project()->get_interface<T>().remove(this->m_handle);
  });

  // Execute the menu at the global posiiton.
  menu.exec(a_view->viewport()->mapToGlobal(a_position));
}

// Do whatever we want when an item has been double clicked on.
template <typename T>
void sak::Section_Outliner_Item<T>::do_double_clicked(QAbstractItemView*, Outliner_Model*)
{
  this->get_project()->get_interface<T>().request_editor(this->m_handle);
}

// Additional Interface
//============================================================
template <typename T>
sak::Project_Interface* sak::Section_Outliner_Item<T>::get_project()
{
  return get_true_parent()->get_project();
}

template <typename T>
sak::Project_Interface const* sak::Section_Outliner_Item<T>::cget_project() const
{
  return get_true_parent()->cget_project();
}

template <typename T>
typename sak::Section_Outliner_Item<T>::Handle_Type const& sak::Section_Outliner_Item<T>::cget_handle() const
{
  return m_handle;
}

template <typename T>
QString sak::Section_Outliner_Item<T>::cget_name() const
{
  // Access the member for "Name" assumed to be at index 0
  return m_handle->cmember_at<0>();
}

template <typename T>
void sak::Section_Outliner_Item<T>::set_name(QString const& a_name)
{
  // Issue the command to change the name.
  this->get_project()->get_interface<T>().change_at<0>(m_handle, a_name);
}

template <typename T>
QString sak::Section_Outliner_Item<T>::cget_description() const
{
  // Access the member for "Description" assumed to be at index 1
  return m_handle->cmember_at<1>();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Section_Outliner_Header_Item<T>
//---------------------------------------------------------------------------
// Outliner item that represents the File container of a Project. It's children
// are all the Files present in the Project.

// Special 6
//============================================================
template <typename T>
sak::Section_Outliner_Header_Item<T>::Section_Outliner_Header_Item(Parent_Item_Type* a_parent, bool a_read_files):
    Inherited_Type(a_parent)
{
  if (a_read_files)
  {
    auto l_handles = this->get_project()->get_interface<T>().get_all();

    // sort them into whatever order and make the items
    for (auto const& l_handle : l_handles)
    {
      this->append_child(std::make_unique<Section_Outliner_Item<T>>(this, l_handle));
    }
  }
}

template <typename T>
sak::Section_Outliner_Header_Item<T>::~Section_Outliner_Header_Item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
template <typename T>
QVariant sak::Section_Outliner_Header_Item<T>::get_data(int a_role) const
{
  if (a_role == Qt::DisplayRole)
  {
    return QVariant(QString::fromStdString(Data_Type::type_plural()));
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
void sak::Section_Outliner_Header_Item<T>::do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position)
{
  unused(a_view, a_model,a_position);

  QMenu menu{};
  menu.addAction(QString::fromStdString(Data_Type::type_plural()));

  // Create and add a new File
  auto l_action_add_new = menu.addAction("Add new " + QString::fromStdString(Data_Type::type()));
  QObject::connect(l_action_add_new, &QAction::triggered, [=]()
  {
    this->get_project()->get_interface<T>().add_default();
  });

  menu.addAction(QString::number(this->get_child_count()));

  // Execute the menu at the global posiiton.
  menu.exec(a_view->viewport()->mapToGlobal(a_position));
}

// Do whatever we want when an item has been double clicked on.
template <typename T>
void sak::Section_Outliner_Header_Item<T>::do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model)
{
  return this->Abstract_Outliner_Item::do_double_clicked(a_view, a_model);
}

// Additional Interface
//============================================================
// Get the flags for this item
template <typename T>
Qt::ItemFlags sak::Section_Outliner_Header_Item<T>::get_flags() const
{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

template <typename T>
sak::Project_Interface* sak::Section_Outliner_Header_Item<T>::get_project()
{
  return get_true_parent()->get_project();
}

template <typename T>
sak::Project_Interface const* sak::Section_Outliner_Header_Item<T>::cget_project() const
{
  return get_true_parent()->cget_project();
}

// What index is the item that holds this Handle_Type reside at?
// Returns get_child_count() if it is not found.
template <typename T>
std::size_t sak::Section_Outliner_Header_Item<T>::index_of(Handle_Type const& a_handle) const
{
  std::size_t l_index{0};
  for(auto l_end = static_cast<std::size_t>(Inherited_Type::get_child_count()); l_index != l_end; ++l_index)
  {
    if (get_true_child_at(static_cast<int>(l_index))->cget_handle() == a_handle)
    {
      break;
    }
  }
  return l_index;
}

// What item holds this Handle_Type? Returns nullptr if not found.
template <typename T>
typename sak::Section_Outliner_Header_Item<T>::Child_Item_Type* sak::Section_Outliner_Header_Item<T>::item_of(Handle_Type const& a_handle) const
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
void sak::Section_Outliner_Header_Item<T>::name_changed(Handle_Type const& a_handle)
{
  assert(flamingo::not_null(a_handle));
  // reorder the Files based on the sorting...
}

// When a File has been added, this is called.
template <typename T>
void sak::Section_Outliner_Header_Item<T>::added(Handle_Type const& a_handle)
{
  assert(flamingo::not_null(a_handle));
  // insert a child in a location that obeys the sorting...
  append_child(std::make_unique<Section_Outliner_Item<T>>(this, a_handle));
}

// When a File has been removed, this is called.
template <typename T>
void sak::Section_Outliner_Header_Item<T>::removed(Handle_Type const& a_handle)
{
  assert(flamingo::not_null(a_handle));
  // insert the child with this data...
  remove_child(index_of(a_handle));
}

// Forced Instantiations
//============================================================

template sak::File_Outliner_Item;
template sak::File_Outliner_Header_Item;

template sak::Texture_Outliner_Item;
template sak::Texture_Outliner_Header_Item;
