#include "outliner_treeview.h"
#include "outliner_model.h"
#include "outliner_abstract_item.h"
#include <QHeaderView>
#include <QMenu>

//---------------------------------------------------------------------------
// outliner::Treeview
//---------------------------------------------------------------------------
// Class derived from QTreeView for use with Model which provides the capability
// to act on custom context menus and double clicks for abstract::Item classes.
// There is also some custom behaviour for adding items, and there may be more
// in the future - it depends what has to be done here.

// Special 6
//============================================================
qtlib::outliner::Treeview::Treeview(QWidget* a_parent) :
    QTreeView(a_parent)
{
    // Connect the base class signal to the new slot so that we can do our own context menu
    QObject::connect(this, &QTreeView::customContextMenuRequested,
                     this, &Treeview::slot_custom_context_menu_requested);

    // Connect the base class signal to the new slot so that we can do our own double click thing
    QObject::connect(this, &QTreeView::doubleClicked,
                     this, &Treeview::slot_double_clicked);

    apply_settings();
}

qtlib::outliner::Treeview::~Treeview() = default;

// Since there is a bunch of additional behaviour, this is a new
// function that will apply it and also limit the type of model
// that can be used.
void qtlib::outliner::Treeview::set_model(Model* a_model)
{
    this->QTreeView::setModel(a_model);
    apply_settings();
}

// Slots
//============================================================
void qtlib::outliner::Treeview::slot_custom_context_menu_requested(QPoint const& a_position)
{
    // Gives the currently selected index (always valid)
    //QModelIndex index = this->currentIndex();

    // Cast to the assumed correct model type
    auto l_model = dynamic_cast<Model*>(this->model());

    // if the cast worked (sanity check)
    if (l_model && l_model->is_active())
    {
        // Gives the index at pos (not always an item, so not always valid)
        auto l_index = this->indexAt(a_position);

        // if menu requested on an item
        if(l_index.isValid())
        {
            // Get the custom context menu for the selected item
            // Position is the position in terms of the widget rather than the window.
            // Use a_view->viewport()->mapToGlobal(a_position)
            abstract::Item::from_index(l_index)->do_context_menu(this, l_model, a_position);
        }
        // else not requested on an item (clicking away from any items)
        else
        {
            // Get the custom context menu for the root item (which is not visible)
            l_model->get_root()->do_context_menu(this, l_model, a_position);
        }
    }
}

// Connected to this->doubleClicked
void qtlib::outliner::Treeview::slot_double_clicked(QModelIndex const& a_index)
{
    // Cast to the assumed correct model type
    auto l_model = dynamic_cast<Model*>(this->model());

    // if the cast worked (sanity check)
    if (l_model && l_model->is_active())
    {
        // if menu requested on an item
        if(a_index.isValid())
        {
            //Do double click for the selected item
            abstract::Item::from_index(a_index)->do_double_clicked(this, l_model);
        }
        // else not requested on an item (clicking away from any items)
        else
        {
            // Do double click for the root item (which is not visible)
            l_model->get_root()->do_double_clicked(this, l_model);
        }
    }
}

// Virtual Overrides
//============================================================
void qtlib::outliner::Treeview::rowsInserted(QModelIndex const& a_parent, int a_start, int a_end)
{
    // Make sure the parent is expanded, it may not have had children before this and
    // we want them to be visible.
    setExpanded(a_parent, true);
    // Do the base class' normal behaviour for this operation.
    // Must do this after so that the expand button appears properly when it's new.
    QTreeView::rowsInserted(a_parent, a_start, a_end);
}

// Convenience
//============================================================
void qtlib::outliner::Treeview::apply_settings()
{
    // Disable calling edit on double click because we use abstract::Item::do_double_clicked
    // for double-click instead.
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // This has to be disabled regardless
    header()->setStretchLastSection(true);
    //header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // Close the header, we aren't going to use it
    header()->close();
    // Items in the view have right-click menus
    setContextMenuPolicy(Qt::CustomContextMenu);
    // Whether or not the root children get expansion markers
    setRootIsDecorated(true);

    // wanted?
    setItemsExpandable(false);
    expandAll();

    // Want scroll bars whenever they are needed
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Set the scrollbar to adapt as the data changes
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
}
