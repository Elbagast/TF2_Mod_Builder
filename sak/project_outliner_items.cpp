#include "project_outliner_items.h"

#include <cassert>

#include <QString>
#include <QVariant>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QAbstractItemView>
#include <QPixmap>
#include <QIcon>
#include "../qtlib/outliner/outliner_model.h"
#include <algorithm>
#include <limits>
#include <vector>

#include "project.h"
#include "project_widget.h"


#include "file.h"
#include "file_interface_traits.h"
#include "../generic/uintid.h"
#include "../generic/uintid_manager.h"
#include "../generic/extended_manager.h"

#include <QDebug>

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
sak::outliner::Root_Item::Root_Item(Project& a_project, Project_Widget& a_project_widget):
    inherited_type(),
    m_project{a_project},
    m_project_widget{a_project_widget}
{
    this->set_child(std::make_unique<Project_Item>(this));
}
sak::outliner::Root_Item::~Root_Item() = default;

// Virtual Interface
//============================================================
// Other
//----------------------------------------
// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing.  Position is the position in terms of
// the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
// to get the position relative to the window for a properly placed menu.
void sak::outliner::Root_Item::do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position)
{
    shadup(a_view, a_model,a_position);

    QMenu menu{};
    menu.addAction("Root context menu");
    menu.addSeparator();
    menu.addAction("blah blah blah");
    menu.exec(a_view->viewport()->mapToGlobal(a_position));
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
sak::Project_Widget& sak::outliner::Root_Item::get_project_widget()
{
    return m_project_widget;
}

sak::Project_Widget const& sak::outliner::Root_Item::cget_project_widget() const
{
    return m_project_widget;
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
    set_child<0>(std::make_unique<child_type<0>>(this));
    /*
    if (cget_project().has_files())
    {
        set_child<0>(std::make_unique<child_type<0>>(this));
    }
    //etc

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
// actions can call functions in it for editing.  Position is the position in terms of
// the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
// to get the position relative to the window for a properly placed menu.
void sak::outliner::Project_Item::do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position)
{
    shadup(a_view, a_model,a_position);

    QMenu menu{};
    menu.addAction("Project context menu");
    menu.addAction(cget_project().name())->setEnabled(false);
    menu.addSeparator();
    menu.addAction("mooooo");
    menu.addAction("buhi.");
    menu.exec(a_view->viewport()->mapToGlobal(a_position));
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

sak::Project_Widget& sak::outliner::Project_Item::get_project_widget()
{
    return get_true_parent()->get_project_widget();
}

sak::Project_Widget const& sak::outliner::Project_Item::cget_project_widget() const
{
    return get_true_parent()->cget_project_widget();
}
//---------------------------------------------------------------------------
// sak::outliner::File_Header_Item
//---------------------------------------------------------------------------
// Outliner item that represents the File container of a Project. It's children
// are all the Files present in the Project.

// Special 6
//============================================================
sak::outliner::File_Header_Item::File_Header_Item(parent_type* a_parent):
    inherited_type(a_parent)
{
    /*
    for(std::size_t l_index = 0, l_end = cget_project().file_count(); l_index != l_end; ++l_index)
    {
        this->append_child(std::make_unique<File_Item>(this));
    }*/
    update();
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
// actions can call functions in it for editing.  Position is the position in terms of
// the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
// to get the position relative to the window for a properly placed menu.
void sak::outliner::File_Header_Item::do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position)
{
    shadup(a_view, a_model,a_position);

    QMenu menu{};
    menu.addAction("Files context menu");

    // Create and add a new File
    auto l_action_add_file = menu.addAction("Add new File");
    QObject::connect(l_action_add_file, &QAction::triggered, [=]()
    {
        // Either this call triggers the data change in model, or we have to make that call here.
        this->get_project().add_new_file();
    });

    auto l_action_debug = menu.addAction("debug");
    QObject::connect(l_action_debug, &QAction::triggered, [=]()
    {
        qDebug() << "file list:";
        for (auto const& l_file : cget_project().get_all_file_names())
        {
            qDebug() << l_file;
        }
    });

    menu.addAction(QString::number(this->get_child_count()));

    // Execute the menu at the global posiiton.
    menu.exec(a_view->viewport()->mapToGlobal(a_position));
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

sak::Project_Widget& sak::outliner::File_Header_Item::get_project_widget()
{
    return get_true_parent()->get_project_widget();
}

sak::Project_Widget const& sak::outliner::File_Header_Item::cget_project_widget() const
{
    return get_true_parent()->cget_project_widget();
}

// update the file count
void sak::outliner::File_Header_Item::update()
{
    auto l_file_count = static_cast<int>(cget_project().file_count());
    auto l_child_count = this->get_child_count();
    //qDebug() << "file count =  " << l_file_count;
    //qDebug() << "child count = " << l_child_count;
    if (l_child_count < l_file_count)
    {
        for (;l_child_count != l_file_count; ++l_child_count)
        {
            this->append_child(std::make_unique<File_Item>(this));
        }
    }
    else if (l_child_count > l_file_count)
    {
        for (;l_child_count != l_file_count; ++l_file_count)
        {
            this->remove_last_child();
        }
    }
    assert(static_cast<int>(cget_project().file_count()) == this->get_child_count());
}

//---------------------------------------------------------------------------
// sak::outliner::File_Item
//---------------------------------------------------------------------------
// Outliner item that represents a File of a Project.

// Special 6
//============================================================
sak::outliner::File_Item::File_Item(parent_type* a_parent):
    inherited_type(a_parent)
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
        return QVariant(cget_file_name());
    }
    else if (a_role == Qt::DecorationRole)
    {
        return QVariant(QIcon(QPixmap("D:\\Temp\\sak\\file_icon.png")));
    }
    else
    {
        return QVariant();
    }
}

// Set the data in item with the given value
void sak::outliner::File_Item::set_data(QVariant const& a_value)
{
    set_file_name(a_value.toString());
}

// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
QWidget* sak::outliner::File_Item::get_editor(QWidget* a_parent)
{
    return new QLineEdit(a_parent);
}

// Set the data in the editor to the value in the item
void sak::outliner::File_Item::set_editor_data(QWidget* a_editor)
{
    static_cast<QLineEdit*>(a_editor)->setText(cget_file_name());
}

// Get the data in the editor and return it
QVariant sak::outliner::File_Item::get_editor_data(QWidget* a_editor)
{
    return QVariant(static_cast<QLineEdit*>(a_editor)->text());
}

// Other
//----------------------------------------
// Get the flags for this item
Qt::ItemFlags sak::outliner::File_Item::get_flags() const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

// Other
//----------------------------------------
// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing.  Position is the position in terms of
// the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
// to get the position relative to the window for a properly placed menu.
void sak::outliner::File_Item::do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position)
{
    shadup(a_view, a_model,a_position);

    QMenu menu{};
    menu.addAction("File context menu");
    menu.addAction(cget_file_name())->setEnabled(false);
    menu.addSeparator();

    // Open the main editor or focus on it if already open
    auto l_action_open = menu.addAction("Open");
    QObject::connect(l_action_open, &QAction::triggered, [=]()
    {
        // We need access to a means to open an editor.
        // We probably need to talk to the Project_Widget then.
        this->get_project_widget().open_file_editor(static_cast<std::size_t>(this->index_in_parent()));
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
        // get rid of the data
        this->get_project().remove_file_at(this->index_in_parent());
    });

    // Execute the menu at the global posiiton.
    menu.exec(a_view->viewport()->mapToGlobal(a_position));
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

sak::Project_Widget& sak::outliner::File_Item::get_project_widget()
{
    return get_true_parent()->get_project_widget();
}

sak::Project_Widget const& sak::outliner::File_Item::cget_project_widget() const
{
    return get_true_parent()->cget_project_widget();
}

QString sak::outliner::File_Item::cget_file_name() const
{
    return cget_project().get_file_at(this->index_in_parent()).get().cget_name();
}

void sak::outliner::File_Item::set_file_name(QString const& a_name)
{
    get_project().get_file_at(this->index_in_parent()).get().set_name(a_name);
}

/*
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
void sak::outliner::Texture_Header_Item::do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position)
{
    shadup(a_view, a_model,a_position);

    QMenu menu{};
    menu.addAction("Textures context menu");
    menu.exec(a_view->viewport()->mapToGlobal(a_position));
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
*/
