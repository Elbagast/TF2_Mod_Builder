#include "project_outliner_items.h"

#include <cassert>

#include <QString>
#include <QVariant>
#include <QMenu>
#include <QAction>

#include "project.h"

namespace
{
    template <typename... Args>
    void shadup(Args&&...)
    {

    }
}

//---------------------------------------------------------------------------
// sak::outliner::Root_Item
//---------------------------------------------------------------------------
// Outliner root item for a single project. This item is invisible and
// defines the default context menu.

// Special 6
//============================================================
sak::outliner::Root_Item::Root_Item(Project& a_project):
    qtlib::outliner::Root_Trunk_Item<Project_Item>(),
    m_project{a_project}
{
    this->set_child(std::make_unique<Project_Item>(this));
}
sak::outliner::Root_Item::~Root_Item() = default;

// Virtual Interface
//============================================================
// Other
//----------------------------------------
// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing
void sak::outliner::Root_Item::do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_point)
{
    shadup(a_view, a_model,a_point);

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
sak::outliner::Project_Item::Project_Item(parent_type* a_parent):
    inherited_type(a_parent)
{
    if (cget_project().has_files())
    {
        set_child<0>(std::make_unique<child_type<0>>(this));
    }
    //etc
    /*
    if (cget_project().has_textures())
    {
        set_child<0>(std::make_unique<child_type<0>>(this));
    }
    */

}
sak::outliner::Project_Item::~Project_Item() = default;

// Virtual Interface
//============================================================
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
    shadup(a_view, a_model,a_point);

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

//---------------------------------------------------------------------------
// sak::outliner::File_Header_Item
//---------------------------------------------------------------------------
// Outliner item that represents the File container of a Project. It's children
// are all the Files present in the Project.

// Special 6
//============================================================
sak::outliner::File_Header_Item::File_Header_Item(parent_type* a_parent):
    qtlib::outliner::Readonly_Branch_Item<Project_Item, File_Item>(a_parent)
{
    for(std::size_t l_index = 0, l_end = cget_project().file_count(); l_index != l_end; ++l_index)
    {
        this->append_child(std::make_unique<File_Item>(this));
    }
}

sak::outliner::File_Header_Item::~File_Header_Item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
QVariant sak::outliner::File_Header_Item::get_data(int a_role) const
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
// actions can call functions in it for editing
void sak::outliner::File_Header_Item::do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_point)
{
    shadup(a_view, a_model,a_point);

    QMenu menu{};
    menu.addAction("Files context menu");
    menu.exec(a_point);
}

// Additional Interface
//============================================================
sak::Project& sak::outliner::File_Header_Item::get_project()
{
    return get_true_parent()->get_project();
}

sak::Project const& sak::outliner::File_Header_Item::cget_project() const
{
    return get_true_parent()->cget_project();
}


//---------------------------------------------------------------------------
// sak::outliner::File_Item
//---------------------------------------------------------------------------
// Outliner item that represents a File of a Project.

// Special 6
//============================================================
sak::outliner::File_Item::File_Item(parent_type* a_parent):
    qtlib::outliner::Readonly_Leaf_Item<File_Header_Item>(a_parent)
{}

sak::outliner::File_Item::~File_Item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
QVariant sak::outliner::File_Item::get_data(int a_role) const
{
    if (a_role == Qt::DisplayRole)
    {
        return QVariant(cget_project().get_file_at(this->index_in_parent()).get().cget_name());
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
void sak::outliner::File_Item::do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_point)
{
    shadup(a_view, a_model,a_point);

    QMenu menu{};
    menu.addAction("File context menu");
    menu.addAction(cget_project().get_file_at(this->index_in_parent()).get().cget_name())->setEnabled(false);
    menu.addSeparator();
    menu.exec(a_point);
}

// Additional Interface
//============================================================
sak::Project& sak::outliner::File_Item::get_project()
{
    return get_true_parent()->get_project();
}

sak::Project const& sak::outliner::File_Item::cget_project() const
{
    return get_true_parent()->cget_project();
}

//---------------------------------------------------------------------------
// sak::outliner::Texture_Header_Item
//---------------------------------------------------------------------------
// Outliner item that represents the Texture container of a Project. It's children
// are all the Textures present in the Project.

// Special 6
//============================================================
sak::outliner::Texture_Header_Item::Texture_Header_Item(parent_type* a_parent):
    qtlib::outliner::Readonly_Branch_Item<Project_Item, Texture_Item>(a_parent)
{}

sak::outliner::Texture_Header_Item::~Texture_Header_Item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
QVariant sak::outliner::Texture_Header_Item::get_data(int a_role) const
{
    if (a_role == Qt::DisplayRole)
    {
        return QVariant(QString::fromUtf8(u8"Textures"));
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
void sak::outliner::Texture_Header_Item::do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_point)
{
    shadup(a_view, a_model,a_point);

    QMenu menu{};
    menu.addAction("Textures context menu");
    menu.exec(a_point);
}

// Additional Interface
//============================================================
sak::Project& sak::outliner::Texture_Header_Item::get_project()
{
    return get_true_parent()->get_project();
}

sak::Project const& sak::outliner::Texture_Header_Item::cget_project() const
{
    return get_true_parent()->cget_project();
}
