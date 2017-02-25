#include "project_outliner_items.hpp"

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

#include "../qtlib/outliner/outliner_model.hpp"
#include "project.hpp"
#include "project_signalbox.hpp"
#include "file_interface.hpp"

namespace
{
    template <typename... Args>
    void shadup(Args&&...)
    {

    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------
// sak::outliner::Root_Item
//---------------------------------------------------------------------------
// Outliner root item for a single project. This item is invisible and
// defines the default context menu.

// Special 6
//============================================================
sak::outliner::Root_Item::Root_Item(Project& a_project):
    inherited_type(),
    m_project{a_project}
{
    this->set_child(std::make_unique<child_type>(this));
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
void sak::outliner::Root_Item::do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position)
{
    shadup(a_view, a_model,a_position);

    QMenu menu{};
    menu.addAction("Root context menu");
    menu.addSeparator();
    menu.addAction("blah blah blah");
    menu.exec(a_view->viewport()->mapToGlobal(a_position));
}

// Do whatever we want when an item has been double clicked on.
void sak::outliner::Root_Item::do_double_clicked(QAbstractItemView* a_view, model_type* a_model)
{
    return item_type::do_double_clicked(a_view, a_model);
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

sak::outliner::Project_Item* sak::outliner::Root_Item::project_item() const
{
    return this->get_true_child();
}
sak::outliner::File_HPPeader_Item* sak::outliner::Root_Item::file_header_item() const
{
    return this->get_true_child()->file_header_item();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
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
        initialise_files(true);
    }
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
void sak::outliner::Project_Item::do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position)
{
    shadup(a_view, a_model,a_position);

    QMenu menu{};
    menu.addAction("Project context menu");
    menu.addAction(cget_project().name())->setEnabled(false);
    menu.addSeparator();
    // Create and add a new File
    auto l_action_add_file = menu.addAction("Add new File");
    QObject::connect(l_action_add_file, &QAction::triggered, [this]()
    {
        // Either this call triggers the data change in model, or we have to make that call here.
        auto l_file = this->get_project().make_file();
        this->get_project().get_signalbox()->added(l_file); // outbound signal to project
    });

    menu.exec(a_view->viewport()->mapToGlobal(a_position));
}

// Do whatever we want when an item has been double clicked on.
void sak::outliner::Project_Item::do_double_clicked(QAbstractItemView* a_view, model_type* a_model)
{
    return this->item_type::do_double_clicked(a_view, a_model);
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

sak::outliner::File_HPPeader_Item* sak::outliner::Project_Item::file_header_item() const
{
    return this->get_true_child<0>();
}

void sak::outliner::Project_Item::initialise_files(bool a_read_files)
{
    this->set_child<0>(std::make_unique<child_type<0>>(this, a_read_files));
}

void sak::outliner::Project_Item::close_files()
{
    if (!cget_project().has_files())
    {
        this->remove_child<0>();
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------
// sak::outliner::File_HPPeader_Item
//---------------------------------------------------------------------------
// Outliner item that represents the File container of a Project. It's children
// are all the Files present in the Project.

// Special 6
//============================================================
sak::outliner::File_HPPeader_Item::File_HPPeader_Item(parent_type* a_parent, bool a_read_files):
    inherited_type(a_parent)
{
    if (a_read_files)
    {
        auto l_files = cget_project().get_all_files();
        // sort them into whatever order and make the File_Items
        for (auto const& l_file : l_files)
        {
            this->append_child(std::make_unique<File_Item>(this, l_file));
        }
    }
}

sak::outliner::File_HPPeader_Item::~File_HPPeader_Item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Get the item data for a given column and role
QVariant sak::outliner::File_HPPeader_Item::get_data(int a_role) const
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
void sak::outliner::File_HPPeader_Item::do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position)
{
    shadup(a_view, a_model,a_position);

    QMenu menu{};
    menu.addAction("Files context menu");

    // Create and add a new File
    auto l_action_add_file = menu.addAction("Add new File");
    QObject::connect(l_action_add_file, &QAction::triggered, [=]()
    {
        // Either this call triggers the data change in model, or we have to make that call here.
        auto l_file = this->get_project().make_file();
        this->get_project().get_signalbox()->added(l_file); // outbound signal to project
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

// Do whatever we want when an item has been double clicked on.
void sak::outliner::File_HPPeader_Item::do_double_clicked(QAbstractItemView* a_view, model_type* a_model)
{
    return this->item_type::do_double_clicked(a_view, a_model);
}

// Additional Interface
//============================================================
sak::Project& sak::outliner::File_HPPeader_Item::get_project()
{
    return get_true_parent()->get_project();
}

sak::Project const& sak::outliner::File_HPPeader_Item::cget_project() const
{
    return get_true_parent()->cget_project();
}

// What index is the File_Item that holds this File_Handle reside at?
// Returns get_child_count() if it is not found.
std::size_t sak::outliner::File_HPPeader_Item::index_of_file(File_Handle const& a_file) const
{
    std::size_t l_index{0};
    for(auto l_end = static_cast<std::size_t>(inherited_type::get_child_count()); l_index != l_end; ++l_index)
    {
        if (get_true_child_at(static_cast<int>(l_index))->cget_file() == a_file)
        {
            break;
        }
    }
    return l_index;
}

// What File_Item holds this File_Handle? Returns nullptr if not found.
sak::outliner::File_Item* sak::outliner::File_HPPeader_Item::item_of_file(File_Handle const& a_file) const
{
    auto l_index = static_cast<int>(index_of_file(a_file));
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
void sak::outliner::File_HPPeader_Item::name_changed(File_Handle const& a_file)
{
    assert(a_file.is_valid());
    // reorder the Files based on the sorting...
}

// When a File has been added, this is called.
void sak::outliner::File_HPPeader_Item::added(File_Handle const& a_file)
{
    assert(a_file.is_valid());
    // insert a child in a location that obeys the sorting...
    append_child(std::make_unique<File_Item>(this, a_file));
}

// When a File has been removed, this is called.
void sak::outliner::File_HPPeader_Item::removed(File_Handle const& a_file)
{
    assert(a_file.is_valid());
    // insert the child with this data...
    remove_child(index_of_file(a_file));
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------
// sak::outliner::File_Item
//---------------------------------------------------------------------------
// Outliner item that represents a File of a Project.

// Special 6
//============================================================
sak::outliner::File_Item::File_Item(parent_type* a_parent, File_Handle const& a_file):
    inherited_type(a_parent),
    m_file{a_file}
{
    assert(a_parent != nullptr);
    assert(a_file.is_valid());
}

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
    else if (a_role == Qt::ToolTipRole)
    {
        return QVariant(cget_file().cget().cget_description());
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
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemNeverHasChildren;
}

// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing.  Position is the position in terms of
// the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
// to get the position relative to the window for a properly placed menu.
void sak::outliner::File_Item::do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position)
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
        this->get_project().get_signalbox()->requests_editor(m_file); // outbound signal. currently to project.
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
        this->get_project().get_signalbox()->removed(m_file); // outbound signal. currently to project.
    });

    // Execute the menu at the global posiiton.
    menu.exec(a_view->viewport()->mapToGlobal(a_position));
}

// Do whatever we want when an item has been double clicked on.
void sak::outliner::File_Item::do_double_clicked(QAbstractItemView*, model_type*)
{
    this->get_project().get_signalbox()->requests_editor(m_file); // outbound signal. currently to project.
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

sak::File_Handle const& sak::outliner::File_Item::cget_file() const
{
    return m_file;
}

QString sak::outliner::File_Item::cget_file_name() const
{
    return m_file.cget().cget_name();
}

void sak::outliner::File_Item::set_file_name(QString const& a_name)
{
    m_file.get().set_name(a_name);
}
