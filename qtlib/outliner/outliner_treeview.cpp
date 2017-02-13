#include "outliner_treeview.h"
#include "outliner_model.h"
#include "outliner_abstract_item.h"
#include <QHeaderView>
#include <QMenu>

//---------------------------------------------------------------------------
// outliner::Treeview
//---------------------------------------------------------------------------
// Class derived from QTreeView for use with Model which provides the capability
// to act on custom context menus for abstract::Item classes. There is also some custom
// behaviour for adding items, and there may be more in the future - it depends what has
// to be done here.

// Special 6
//============================================================
qtlib::outliner::Treeview::Treeview(QWidget* a_parent) :
    QTreeView(a_parent)
{
    // Connect the base class signal to the new slot so that we can do our own context menu
    QObject::connect(this, &QTreeView::customContextMenuRequested,
                     this, &Treeview::slot_custom_context_menu_requested);

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

    // Gives the index at pos (not always an item, so not always valid)
    auto l_index = this->indexAt(a_position);

    // Cast to the assumed correct model type
    auto l_model = dynamic_cast<Model*>(this->model());

    // if the cast worked (sanity check)
    if (l_model && l_model->is_active())
    {
        // if menu requested on an item
        if(l_index.isValid())
        {
            // Get the custom context menu for the selected item
            abstract::Item::from_index(l_index)->do_custom_context_menu(this, l_model, viewport()->mapToGlobal(a_position));
        }
        // else not requested on an item (clicking away from any items)
        else
        {
            // Get the custom context menu for the root item (which is not visible)
            l_model->get_root()->do_custom_context_menu(this, l_model, viewport()->mapToGlobal(a_position));
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
    // This has to be disabled regardless
    header()->setStretchLastSection(false);
    header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // Close the header, we aren't going to use it
    header()->close();
    // Items in the view have right-click menus
    setContextMenuPolicy(Qt::CustomContextMenu);
    // Whether or not the root children get expansion markers
    setRootIsDecorated(true);
    // wanted?
    expandAll();

    // Want scroll bars whenever they are needed
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Set the scrollbar to adapt as the data changes
    setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
}
