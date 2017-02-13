#include "project_outliner_items.h"

#include <cassert>

#include <QString>
#include <QVariant>
#include <QMenu>
#include <QAction>

#include "project.h"


//---------------------------------------------------------------------------
// sak::outliner::Root_Item
//---------------------------------------------------------------------------
// Outliner root item for a single project. This item is invisible and
// defines the default context menu.

// Special 6
//============================================================
sak::outliner::Root_Item::Root_Item(Project& a_project):
    m_project{a_project},
    m_child{std::make_unique<Project_Item>(this)}
{}
sak::outliner::Root_Item::~Root_Item() = default;

// Virtual Interface
//============================================================
// Does this item have any child items?
bool sak::outliner::Root_Item::has_children() const
{
    return m_child != nullptr;
}
// The number of children this item has
int sak::outliner::Root_Item::get_child_count() const
{
    return 1;
}

// Does this item have a child item at this index?
bool sak::outliner::Root_Item::has_child_at(int a_index) const
{
    return a_index == 0;
}
// Get the child at a given row, return nullptr if there is no child at row
sak::outliner::Root_Item::item_type* sak::outliner::Root_Item::get_child_at(int a_index) const
{
    if (a_index == 0)
    {
        return m_child.get();
    }
    else
    {
        return nullptr;
    }
}
// Other
//----------------------------------------
// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing
void sak::outliner::Root_Item::do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_point)
{
    QMenu menu{};
    menu.addAction("Root context menu");
    menu.addSeparator();
    menu.addAction("blah blah blah");
    menu.exec(a_point);
}

// Additional Interface
//============================================================
sak::Project& sak::outliner::Root_Item::get_project()
{
    return m_project;
}

sak::Project const& sak::outliner::Root_Item::cget_project() const
{
    return m_project;
}


//---------------------------------------------------------------------------
// sak::outliner::Project_Item
//---------------------------------------------------------------------------
// Outliner item that represents a Project. It's data is the Project's name.

// Special 6
//============================================================
sak::outliner::Project_Item::Project_Item(Root_Item* a_parent):
    qtlib::outliner::Readonly_Branch_Item<Root_Item, Header_Item>(a_parent)
    //m_parent{a_parent}//,
    //m_files{},
    //m_textures{}
{
}
sak::outliner::Project_Item::~Project_Item() = default;

// Virtual Interface
//============================================================
/*
// Does this item have a parent item?
bool sak::outliner::Project_Item::has_parent() const
{
    return true;
}
// Get the item that is the parent of this
sak::outliner::Project_Item::item_type* sak::outliner::Project_Item::get_parent() const
{
    return m_parent;
}
// Get the item at the root of the structure
sak::outliner::Project_Item::item_type* sak::outliner::Project_Item::get_root() const
{
    return m_parent;
}

// Does this item have any child items?
bool sak::outliner::Project_Item::has_children() const
{
    return false;
}
// The number of children this item has
int sak::outliner::Project_Item::get_child_count() const
{
    return 0;
}

// Does this item have a child item at this index?
bool sak::outliner::Project_Item::has_child_at(int a_index) const
{
    return false;
}
// Get the child at a given row, return nullptr if there is no child at row
sak::outliner::Project_Item::item_type* sak::outliner::Project_Item::get_child_at(int a_index) const
{
    return nullptr;
}

// The row that this item is in relative to the parent e.g. if the parent has
// 5 children, and this is the third, then row is 2. If this has no parent
// then -1 is returned.
int sak::outliner::Project_Item::index_in_parent() const
{
    return 0;
}
*/
// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
QVariant sak::outliner::Project_Item::get_data(int a_role) const
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
// actions can call functions in it for editing
void sak::outliner::Project_Item::do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_point)
{
    QMenu menu{};
    menu.addAction("Project context menu");
    menu.addAction(cget_project().name())->setEnabled(false);
    menu.addSeparator();
    menu.addAction("mooooo");
    menu.addAction("buhi.");
    menu.exec(a_point);
}

// Additional Interface
//============================================================
sak::Project& sak::outliner::Project_Item::get_project()
{
    return get_true_parent()->get_project();
}
sak::Project const& sak::outliner::Project_Item::cget_project() const
{
    return get_true_parent()->cget_project();
}


