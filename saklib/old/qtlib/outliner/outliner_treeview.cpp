#include "outliner_treeview.h"
#include "outliner_model.h"

#include <QHeaderView>
#include <QMenu>
#include <QMouseEvent>

// Special 6
//============================================================
saklib::Qtlib::Outliner_Treeview::Outliner_Treeview(QWidget* parent) :
    QTreeView(parent),
    m_expanded_indexes()
{
    // Connect the base class signal to the new slot so that we can do our own context menu
    QObject::connect(this, &QTreeView::customContextMenuRequested,
                     this, &Outliner_Treeview::slot_customContextMenuRequested);

    applySettings();
}

saklib::Qtlib::Outliner_Treeview::~Outliner_Treeview() = default;


// Adding additional behaviour
void saklib::Qtlib::Outliner_Treeview::setModel(QAbstractItemModel* newModel)
{
    QTreeView::setModel(newModel);
    applySettings();
}

void saklib::Qtlib::Outliner_Treeview::cache_expanded_indexes()
{
    m_expanded_indexes.clear();
    // Cast to the assumed correct model type
    auto model = dynamic_cast<Outliner_Model*>(this->model());
    if (model)
    {
        auto all_indexes = model->all_indexes();
        for (auto const& index : all_indexes)
        {
            if (isExpanded(index))
            {
                m_expanded_indexes.push_back(index);
            }
        }
    }
}

void saklib::Qtlib::Outliner_Treeview::restore_expanded_indexes()
{
    auto model = dynamic_cast<Outliner_Model*>(this->model());
    if (model)
    {
        for (auto const& index : m_expanded_indexes)
        {
            if (model->hasIndex(index.row(), index.column(), index.parent()))
            {
                setExpanded(index, true);
            }
        }
    }
}

// Slots
//============================================================
void saklib::Qtlib::Outliner_Treeview::slot_customContextMenuRequested(QPoint const& pos)
{
    // Gives the currently selected index (always valid)
    //QModelIndex index = this->currentIndex();

    // Gives the index at pos (not always an item, so not always valid)
    auto index = this->indexAt(pos);

    // Cast to the assumed correct model type
    auto model = dynamic_cast<Outliner_Model*>(this->model());

    // if the cast worked (sanity check)
    if (model)
    {
        // Send a request for a context menu at this index, the model will determine behaviour.
        model->custom_context_menu(this, index, viewport()->mapToGlobal(pos));
    }
}


// Virtual Overrides
//============================================================
void saklib::Qtlib::Outliner_Treeview::rowsInserted(QModelIndex const& parent, int start, int end)
{
    // Make sure the parent is expanded, it may not have had children before this and
    // we want them to be visible.
    setExpanded(parent, true);
    // Do the base class' normal behaviour for this operation.
    // Must do this after so that the expand button appears properly when it's new.
    QTreeView::rowsInserted(parent, start, end);
}

// To add opening editors on double-click
void saklib::Qtlib::Outliner_Treeview::mouseDoubleClickEvent(QMouseEvent* mouse_event)
{
    if (mouse_event->button() == Qt::LeftButton)
    {
        // Cast to the assumed correct model type
        auto model = dynamic_cast<Outliner_Model*>(this->model());

        // if the cast worked (sanity check)
        if (model)
        {
            // Send a request for an editor at this index, the model will determine behaviour.
            model->request_editor(this->currentIndex());
        }
    }
}


// Convenience
//============================================================
void saklib::Qtlib::Outliner_Treeview::applySettings()
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