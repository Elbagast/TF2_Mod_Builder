#include "root_item.hpp"

#include <QDebug>
#include <QString>
#include <QVariant>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QAbstractItemView>

#include <qtlib/outliner/model.hpp>
//#include <sak/project/object.hpp>
//#include <sak/project/signalbox.hpp>
#include "project_item.hpp"

namespace
{
    template <typename... Args>
    void shadup(Args&&...)
    {

    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------
// sak::project::outliner::root_item
//---------------------------------------------------------------------------
// Outliner root item for a single project. This item is invisible and
// defines the default context menu.

// Special 6
//============================================================
sak::project::outliner::root_item::root_item(object& a_project):
    inherited_type(),
    m_project{a_project}
{
    this->set_child(std::make_unique<child_type>(this));
}
sak::project::outliner::root_item::~root_item() = default;

// Virtual Interface
//============================================================
// Other
//----------------------------------------
// Make and act on the context menu for this item. Need the model pointer here so that
// actions can call functions in it for editing.  Position is the position in terms of
// the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
// to get the position relative to the window for a properly placed menu.
void sak::project::outliner::root_item::do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position)
{
    shadup(a_view, a_model,a_position);

    QMenu menu{};
    menu.addAction("Root context menu");
    menu.addSeparator();
    menu.addAction("blah blah blah");
    menu.exec(a_view->viewport()->mapToGlobal(a_position));
}

// Do whatever we want when an item has been double clicked on.
void sak::project::outliner::root_item::do_double_clicked(QAbstractItemView* a_view, model_type* a_model)
{
    return item_type::do_double_clicked(a_view, a_model);
}

// Additional Interface
//============================================================
sak::project::object& sak::project::outliner::root_item::get_project()
{
    return m_project;
}

sak::project::object const& sak::project::outliner::root_item::cget_project() const
{
    return m_project;
}

sak::project::outliner::project_item* sak::project::outliner::root_item::get_project_item() const
{
    return this->get_true_child();
}
sak::file::outliner::header_item* sak::project::outliner::root_item::file_header_item() const
{
    return this->get_true_child()->file_header_item();
}
