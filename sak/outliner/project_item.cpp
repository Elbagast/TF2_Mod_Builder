#include "project_item.hpp"

#include <QDebug>
#include <QString>
#include <QVariant>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QAbstractItemView>

#include <qtlib/outliner/model.hpp>
#include <sak/project.hpp>
#include <sak/project_signalbox.hpp>
#include <sak/shared/outliner_item.hpp>
#include "root_item.hpp"

namespace
{
  template <typename... Args>
  void shadup(Args&&...)
  {

  }
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

sak::file::outliner::header_item* sak::outliner::Project_Item::file_header_item() const
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
