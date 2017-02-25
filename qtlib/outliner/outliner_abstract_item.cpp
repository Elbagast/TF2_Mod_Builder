#include "outliner_abstract_item.hpp"

#include <QVariant>
#include <QModelIndex>

//---------------------------------------------------------------------------
// outliner::abstract::Item
//---------------------------------------------------------------------------
// Defines the interface used by outliner::Model, outliner::delegate and
// outliner::View_Widget. There is only ever one column.
// Subclass this and create a tree Item subclasses.

// Special 6
//============================================================
qtlib::outliner::abstract::Item::~Item() = default;

// Interface
//============================================================
// Does this item have a parent item?
bool qtlib::outliner::abstract::Item::has_parent() const
{
    return false;
}

// Get the item that is the parent of this
qtlib::outliner::abstract::Item::item_type* qtlib::outliner::abstract::Item::get_parent() const
{
    return nullptr;
}

// Get the item at the root of the structure
qtlib::outliner::abstract::Item::item_type* qtlib::outliner::abstract::Item::get_root() const
{
    return nullptr;
}


// Does this item have any child items?
bool qtlib::outliner::abstract::Item::has_children() const
{
    return false;
}

// The number of child items this item has
int qtlib::outliner::abstract::Item::get_child_count() const
{
    return 0;
}


// Does this item have a child item at this index?
bool qtlib::outliner::abstract::Item::has_child_at(int ) const
{
    return false;
}

// Get the child at a given row, return nullptr if there is no child at row
qtlib::outliner::abstract::Item::item_type* qtlib::outliner::abstract::Item::get_child_at(int ) const
{
    return nullptr;
}


// The row that this item is in relative to the parent e.g. if the parent has
// 5 children, and this is the third, then row is 2. If this has no parent
// then -1 is returned.
int qtlib::outliner::abstract::Item::index_in_parent() const
{
    return -1;
}


// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
QVariant qtlib::outliner::abstract::Item::get_data(int) const
{
    return QVariant();
}

// Set the data in item with the given value
void qtlib::outliner::abstract::Item::set_data(QVariant const& )
{

}


// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
QWidget* qtlib::outliner::abstract::Item::get_editor(QWidget* )
{
    return nullptr;
}

// Set the data in the editor to the value in the item
void qtlib::outliner::abstract::Item::set_editor_data(QWidget* )
{

}

// Get the data in the editor and return it
QVariant qtlib::outliner::abstract::Item::get_editor_data(QWidget* )
{
    return QVariant();
}


// Other
//----------------------------------------
// Get the flags for this item
Qt::ItemFlags qtlib::outliner::abstract::Item::get_flags() const
{
    return Qt::NoItemFlags;
}

// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing
void qtlib::outliner::abstract::Item::do_context_menu(QAbstractItemView* /*a_view*/, model_type* /*a_model*/, QPoint const& /*a_point*/)
{

}

// Do whatever we want when an item has been double clicked on.
void qtlib::outliner::abstract::Item::do_double_clicked(QAbstractItemView* /*a_view*/, model_type* /*a_model*/)
{

}


// Encapsulate the casting of the void* stored in index to Item*
qtlib::outliner::abstract::Item::item_type* qtlib::outliner::abstract::Item::from_index(QModelIndex const& a_index)
{
    // if the index is valid, cast the internal pointer and return it
    if (a_index.isValid())
    {
        return static_cast<Item*>(a_index.internalPointer());
    }
    else
    {
        return nullptr;
    }
}

