#include "outliner_item.h"

#include <algorithm>
#include <iterator>
#include <QVariant>
#include <QModelIndex>

//---------------------------------------------------------------------------
// Outliner_Item
//---------------------------------------------------------------------------
// Defines the interface used by Outliner_Model for actions specific to the
// model. There is only ever one column. Subclass this and create a Outliner_Item
// hierarchy that the model will use in order to do all the crap it needs to do.
//
// Basically you are creating an adapter for your data.

// Special 6
//============================================================
qtlib::Outliner_Item::Outliner_Item(Outliner_Item* a_parent):
    m_parent{a_parent},
    m_children{}
{
}
qtlib::Outliner_Item::~Outliner_Item() = default;

// Interface
//============================================================
// Reparent this
void qtlib::Outliner_Item::set_parent(Outliner_Item* a_parent)
{
    m_parent = a_parent;
}
// Get the item that is the parent of this
qtlib::Outliner_Item* qtlib::Outliner_Item::get_parent() const
{
    return m_parent;
}
// Get the item at the root of the structure
qtlib::Outliner_Item* qtlib::Outliner_Item::get_root() const
{
    // Make an editable pointer copy of this
    Outliner_Item* l_root = const_cast<Outliner_Item*>(this);
    // while m_parent is not nullptr, march down the parent chain and return the result
    while(l_root->m_parent)
    {
        l_root = l_root->m_parent;
    }
    return m_parent;
}
// Get the child at a given row, return nullptr if there is no child at row
qtlib::Outliner_Item* qtlib::Outliner_Item::get_child(int a_row) const
{
    // if the row is not nonsense and would be a valid index for m_children, return the child at that index
    if (a_row >= 0 && a_row < static_cast<int>(m_children.size()))
    {
        return m_children.at(a_row).get();
    }
    // else return nullptr to signify this is not a valid child
    else
    {
        return nullptr;
    }
}
// Add a new child, setting its parent to this
void qtlib::Outliner_Item::append_child(std::unique_ptr<Outliner_Item>&& a_child)
{
    // Reparent the child
    a_child->set_parent(this);
    // Take ownership of the pointer
    m_children.push_back(std::move(a_child));
}
void qtlib::Outliner_Item::clear_children()
{
    // Delete all children
    m_children.clear();
}
// The number of children this item has
int qtlib::Outliner_Item::child_count() const
{
    // cast to kill the compiler warning...
    // Qt likes to use ints for size/count
    return static_cast<int>(m_children.size());
}
// The row that this item is in relative to the parent e.g. if the parent has
// 5 children, and this is the third, then row is 2
int qtlib::Outliner_Item::row() const
{
    // if there is a parent
    if(m_parent != nullptr)
    {
        // Get the index of an item inside a vector

        // Find the child in m_parent's child list that is equal to this
        auto l_location = std::find_if(m_parent->m_children.cbegin(),
                                      m_parent->m_children.cend(),
                                      [this](decltype(m_children)::value_type const& value){ return value.get() == this; } );

        // sanity check for something that should never happen...
        if (l_location == m_parent->m_children.end())
        {
            throw std::range_error("Outliner_Item was not found in its parent's child list.");
        }

        // return the distance between the location and the starting iterator
        return static_cast<int>(std::distance(m_parent->m_children.cbegin(),l_location));
    }
    // else return -1, which means this item will create invalid indexes.
    else
    {
        return 0;
    }
}

// Encapsulate the casting of the void* stored in index to Outliner_Item*
qtlib::Outliner_Item* qtlib::Outliner_Item::from_index(QModelIndex const& a_index)
{
    // if the index is valid, cast the internal pointer and return it
    if (a_index.isValid())
    {
        return static_cast<Outliner_Item*>(a_index.internalPointer());
    }
    else
    {
        return nullptr;
    }
}

// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
QVariant qtlib::Outliner_Item::get_data(int a_role) const
{
    return v_get_data(a_role);
}

// Set the data in item with the given value
void qtlib::Outliner_Item::set_data(QVariant const& a_value)
{
    v_set_data(a_value);
}

// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
QWidget* qtlib::Outliner_Item::get_editor(QWidget* a_parent)
{
    return v_get_editor(a_parent);
}

// Set the data in the editor to the value in the item
void qtlib::Outliner_Item::set_editor_data(QWidget* a_editor)
{
    v_set_editor_data(a_editor);
}

QVariant qtlib::Outliner_Item::get_editor_data(QWidget* a_editor)
{
    return v_get_editor_data(a_editor);
}

// Other
//----------------------------------------
// Get the flags for this item in a given column
Qt::ItemFlags qtlib::Outliner_Item::flags() const
{
    return v_flags();
}
// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing
void qtlib::Outliner_Item::custom_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_point)
{
    return v_custom_context_menu(a_view, a_model, a_point);
}


// Virtuals
//============================================================
// While these functions are pure virtual, implementations that can serve
// as dummies (i.e. do nothing) are provided. Thus explicitly calling them
// means you won't have to re-provide a dummy implementation.

// Underlying data access
//----------------------------------------
QVariant qtlib::Outliner_Item::v_get_data(int) const
{
    return QVariant();
}

void qtlib::Outliner_Item::v_set_data(QVariant const& )
{

}

// Editors
//----------------------------------------
QWidget* qtlib::Outliner_Item::v_get_editor(QWidget* )
{
    return nullptr;
}

void qtlib::Outliner_Item::v_set_editor_data(QWidget* )
{

}

QVariant qtlib::Outliner_Item::v_get_editor_data(QWidget* )
{
    return QVariant();
}

// Other
//----------------------------------------
Qt::ItemFlags qtlib::Outliner_Item::v_flags() const
{
    return Qt::NoItemFlags;
}

void qtlib::Outliner_Item::v_custom_context_menu(QAbstractItemView*, Outliner_Model*, QPoint const& )
{

}
