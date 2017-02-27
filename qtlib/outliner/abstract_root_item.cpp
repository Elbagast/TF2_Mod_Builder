#include "abstract_root_item.hpp"

#include <QVariant>

//---------------------------------------------------------------------------
// outliner::abstract::Root_Item
//---------------------------------------------------------------------------
// Abstract subclass of abstract::Item. Subclass from this for your root
// (invisible) object in an outliner item tree. Functions that are part of
// the abstract::Item interface that will not be called on the root item
// are finalised with do-nothing implemenations. Your implemenation of
// do_custom_context_menu is what will be carried out in the view if one is
// requested where no item is present.

// Special 6
//============================================================
qtlib::outliner::abstract::Root_Item::~Root_Item() = default;

// Interface
//============================================================
// Parent
//----------------------------------------
// Does this item have a parent item?
bool qtlib::outliner::abstract::Root_Item::has_parent() const
{
    return this->abstract::Item::has_parent();
}

// Get the item that is the parent of this
qtlib::outliner::abstract::Root_Item::item_type* qtlib::outliner::abstract::Root_Item::get_parent() const
{
    return this->abstract::Item::get_parent();
}

// Get the item at the root of the structure
qtlib::outliner::abstract::Root_Item::item_type* qtlib::outliner::abstract::Root_Item::get_root() const
{
    return this->abstract::Item::get_root();
}

// The row that this item is in relative to the parent e.g. if the parent has
// 5 children, and this is the third, then row is 2. If this has no parent
// then -1 is returned.
int qtlib::outliner::abstract::Root_Item::index_in_parent() const
{
    return this->abstract::Item::index_in_parent();
}

// Children
//----------------------------------------
// Does this item have any child items?
bool qtlib::outliner::abstract::Root_Item::has_children() const
{
    return this->abstract::Item::has_children();
}

// The number of child items this item has
int qtlib::outliner::abstract::Root_Item::get_child_count() const
{
    return this->abstract::Item::get_child_count();
}


// Does this item have a child item at this index?
bool qtlib::outliner::abstract::Root_Item::has_child_at(int a_index) const
{
    return this->abstract::Item::has_child_at(a_index);
}

// Get the child at a given row, return nullptr if there is no child at row
qtlib::outliner::abstract::Root_Item::item_type* qtlib::outliner::abstract::Root_Item::get_child_at(int a_index) const
{
    return this->abstract::Item::get_child_at(a_index);
}

// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
QVariant qtlib::outliner::abstract::Root_Item::get_data(int a_role) const
{
    return this->abstract::Item::get_data(a_role);
}

// Set the data in item with the given value
void qtlib::outliner::abstract::Root_Item::set_data(QVariant const& a_value)
{
    return this->abstract::Item::set_data(a_value);
}


// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
QWidget* qtlib::outliner::abstract::Root_Item::get_editor(QWidget* a_parent)
{
    return this->abstract::Item::get_editor(a_parent);
}

// Set the data in the editor to the value in the item
void qtlib::outliner::abstract::Root_Item::set_editor_data(QWidget* a_editor)
{
    return this->abstract::Item::set_editor_data(a_editor);
}

// Get the data in the editor and return it
QVariant qtlib::outliner::abstract::Root_Item::get_editor_data(QWidget* a_editor)
{
    return this->abstract::Item::get_editor_data(a_editor);
}


// Other
//----------------------------------------
// Get the flags for this item
Qt::ItemFlags qtlib::outliner::abstract::Root_Item::get_flags() const
{
    return this->abstract::Item::get_flags();
}

// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing
void qtlib::outliner::abstract::Root_Item::do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_point)
{
    return this->abstract::Item::do_context_menu(a_view, a_model, a_point);
}

// Do whatever we want when an item has been double clicked on.
void qtlib::outliner::abstract::Root_Item::do_double_clicked(QAbstractItemView* a_view, model_type* a_model)
{
    return this->abstract::Item::do_double_clicked(a_view, a_model);
}

