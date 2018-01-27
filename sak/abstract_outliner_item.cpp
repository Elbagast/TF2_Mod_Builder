#include "abstract_outliner_item.hpp"

#include <QVariant>
#include <QModelIndex>

//---------------------------------------------------------------------------
// Abstract_Outliner_Item
//---------------------------------------------------------------------------

// Special 6
//============================================================
sak::Abstract_Outliner_Item::~Abstract_Outliner_Item() = default;

// Interface
//============================================================
// Does this item have a parent item?
bool sak::Abstract_Outliner_Item::has_parent() const
{
  return false;
}

// Get the item that is the parent of this
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Item::get_parent() const
{
  return nullptr;
}

// Get the item at the root of the structure
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Item::get_root() const
{
  return nullptr;
}


// Does this item have any child items?
bool sak::Abstract_Outliner_Item::has_children() const
{
  return false;
}

// The number of child items this item has
int sak::Abstract_Outliner_Item::get_child_count() const
{
  return 0;
}


// Does this item have a child item at this index?
bool sak::Abstract_Outliner_Item::has_child_at(int ) const
{
  return false;
}

// Get the child at a given row, return nullptr if there is no child at row
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Item::get_child_at(int ) const
{
  return nullptr;
}


// The row that this item is in relative to the parent e.g. if the parent has
// 5 children, and this is the third, then row is 2. If this has no parent
// then -1 is returned.
int sak::Abstract_Outliner_Item::index_in_parent() const
{
  return -1;
}


// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
QVariant sak::Abstract_Outliner_Item::get_data(int) const
{
  return QVariant();
}

// Set the data in item with the given value
void sak::Abstract_Outliner_Item::set_data(QVariant const& )
{

}


// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
QWidget* sak::Abstract_Outliner_Item::get_editor(QWidget* )
{
  return nullptr;
}

// Set the data in the editor to the value in the item
void sak::Abstract_Outliner_Item::set_editor_data(QWidget* )
{

}

// Get the data in the editor and return it
QVariant sak::Abstract_Outliner_Item::get_editor_data(QWidget* )
{
  return QVariant();
}


// Other
//----------------------------------------
// Get the flags for this item
Qt::ItemFlags sak::Abstract_Outliner_Item::get_flags() const
{
  return Qt::NoItemFlags;
}

// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing
void sak::Abstract_Outliner_Item::do_context_menu(QAbstractItemView*, Outliner_Model*, QPoint const&)
{

}

// Do whatever we want when an item has been double clicked on.
void sak::Abstract_Outliner_Item::do_double_clicked(QAbstractItemView*, Outliner_Model*)
{

}


// Encapsulate the casting of the void* stored in index to Item*
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Item::from_index(QModelIndex const& a_index)
{
  // if the index is valid, cast the internal pointer and return it
  if (a_index.isValid())
  {
    return static_cast<Abstract_Outliner_Item*>(a_index.internalPointer());
  }
  else
  {
    return nullptr;
  }
}



//---------------------------------------------------------------------------
// Abstract_Outliner_Readonly_Item
//---------------------------------------------------------------------------

// Special 6
//============================================================
sak::Abstract_Outliner_Readonly_Item::~Abstract_Outliner_Readonly_Item() = default;

// Interface
//============================================================
// Set the data in item with the given value
void sak::Abstract_Outliner_Readonly_Item::set_data(QVariant const& a_value)
{
  return this->Abstract_Outliner_Item::set_data(a_value);
}

// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
QWidget* sak::Abstract_Outliner_Readonly_Item::get_editor(QWidget* a_parent)
{
  return this->Abstract_Outliner_Item::get_editor(a_parent);
}

// Set the data in the editor to the value in the item
void sak::Abstract_Outliner_Readonly_Item::set_editor_data(QWidget* a_editor)
{
  return this->Abstract_Outliner_Item::set_editor_data(a_editor);
}

// Get the data in the editor and return it
QVariant sak::Abstract_Outliner_Readonly_Item::get_editor_data(QWidget* a_editor)
{
  return this->Abstract_Outliner_Item::get_editor_data(a_editor);
}

// Other
//----------------------------------------
// Get the flags for this item
Qt::ItemFlags sak::Abstract_Outliner_Readonly_Item::get_flags() const
{
  return this->Abstract_Outliner_Item::get_flags();
}


//---------------------------------------------------------------------------
// Abstract_Outliner_Root_Item
//---------------------------------------------------------------------------
// Abstract subclass of Abstract_Outliner_Item. Subclass from this for your root
// (invisible) object in an outliner item tree. Functions that are part of
// the Abstract_Outliner_Item interface that will not be called on the root item
// are finalised with do-nothing implemenations. Your implemenation of
// do_custom_context_menu is what will be carried out in the view if one is
// requested where no item is present.

// Special 6
//============================================================
sak::Abstract_Outliner_Root_Item::~Abstract_Outliner_Root_Item() = default;

// Interface
//============================================================
// Parent
//----------------------------------------
// Does this item have a parent item?
bool sak::Abstract_Outliner_Root_Item::has_parent() const
{
    return this->Abstract_Outliner_Item::has_parent();
}

// Get the item that is the parent of this
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Root_Item::get_parent() const
{
    return this->Abstract_Outliner_Item::get_parent();
}

// Get the item at the root of the structure
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Root_Item::get_root() const
{
    return this->Abstract_Outliner_Item::get_root();
}

// The row that this item is in relative to the parent e.g. if the parent has
// 5 children, and this is the third, then row is 2. If this has no parent
// then -1 is returned.
int sak::Abstract_Outliner_Root_Item::index_in_parent() const
{
    return this->Abstract_Outliner_Item::index_in_parent();
}

// Children
//----------------------------------------
// Does this item have any child items?
bool sak::Abstract_Outliner_Root_Item::has_children() const
{
    return this->Abstract_Outliner_Item::has_children();
}

// The number of child items this item has
int sak::Abstract_Outliner_Root_Item::get_child_count() const
{
    return this->Abstract_Outliner_Item::get_child_count();
}


// Does this item have a child item at this index?
bool sak::Abstract_Outliner_Root_Item::has_child_at(int a_index) const
{
    return this->Abstract_Outliner_Item::has_child_at(a_index);
}

// Get the child at a given row, return nullptr if there is no child at row
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Root_Item::get_child_at(int a_index) const
{
    return this->Abstract_Outliner_Item::get_child_at(a_index);
}

// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
QVariant sak::Abstract_Outliner_Root_Item::get_data(int a_role) const
{
    return this->Abstract_Outliner_Item::get_data(a_role);
}

// Set the data in item with the given value
void sak::Abstract_Outliner_Root_Item::set_data(QVariant const& a_value)
{
    return this->Abstract_Outliner_Item::set_data(a_value);
}


// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
QWidget* sak::Abstract_Outliner_Root_Item::get_editor(QWidget* a_parent)
{
    return this->Abstract_Outliner_Item::get_editor(a_parent);
}

// Set the data in the editor to the value in the item
void sak::Abstract_Outliner_Root_Item::set_editor_data(QWidget* a_editor)
{
    return this->Abstract_Outliner_Item::set_editor_data(a_editor);
}

// Get the data in the editor and return it
QVariant sak::Abstract_Outliner_Root_Item::get_editor_data(QWidget* a_editor)
{
    return this->Abstract_Outliner_Item::get_editor_data(a_editor);
}


// Other
//----------------------------------------
// Get the flags for this item
Qt::ItemFlags sak::Abstract_Outliner_Root_Item::get_flags() const
{
    return this->Abstract_Outliner_Item::get_flags();
}

// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing
void sak::Abstract_Outliner_Root_Item::do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_point)
{
    return this->Abstract_Outliner_Item::do_context_menu(a_view, a_model, a_point);
}

// Do whatever we want when an item has been double clicked on.
void sak::Abstract_Outliner_Root_Item::do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model)
{
    return this->Abstract_Outliner_Item::do_double_clicked(a_view, a_model);
}

