#include "node_model.h"
#include "../../node_project_manager.h"

// Special 6
//============================================================
Saklib::Qtlib::Node_Model::Node_Model(QObject* parent):
    QAbstractItemModel(parent),
    mp_project_manager{nullptr}
{

}

Saklib::Qtlib::Node_Model::Node_Model(Node_Project_Manager* project_manager, QObject* parent):
    Node_Model(parent)
{
    set_project_manager(project_manager);
}

Saklib::Qtlib::Node_Model::~Node_Model() = default;


// Virtual Overrides
//============================================================
// These are all the public virtual functions of QAbstractItemModel, not all need to be implemented

//QModelIndex Saklib::Qtlib::Node_Model::buddy(QModelIndex const& index) const
//bool Saklib::Qtlib::Node_Model::canDropMimeData(QMimeData const* data, Qt::DropAction action, int row, int column, const QModelIndex & parent) const
//bool Saklib::Qtlib::Node_Model::canFetchMore(QModelIndex const& parent) const

int Saklib::Qtlib::Node_Model::columnCount(QModelIndex const& parent) const
{
    if (mp_project_manager && index.isValid())
    {

    }

    return 0;
}

QVariant Saklib::Qtlib::Node_Model::data(QModelIndex const& index, int role) const
{
    // if index is valid
    if (mp_project_manager && index.isValid())
    {
        // if this is a request to display data
        if (role == Qt::DisplayRole)
        {
            // Return data based on the given NodeID and column
            NodeID indexid{index.internalId()};
            int column{index.column()};

            return data_to_qvariant(mp_project_manager, indexid, column);
        }
    }

    // else return nothing
    return QVariant();
}

//bool Saklib::Qtlib::Node_Model::dropMimeData(QMimeData const* data, Qt::DropAction action, int row, int column, const QModelIndex & parent)
//void Saklib::Qtlib::Node_Model::fetchMore(QModelIndex const& parent)

Qt::ItemFlags Saklib::Qtlib::Node_Model::flags(QModelIndex const& index) const
{
    // if index is valid
    if (mp_project_manager && index.isValid())
    {
        // Make a NodeID out of the id
        NodeID indexid{index.internalId()};

        if (!indexid.is_valid())
        {
            return Qt::NoItemFlags;
        }
        else
        {
            // Actual stuff goes here...
            assert(0);
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; // for name edit
        }
    }

    // else no flags
    return Qt::NoItemFlags;
}

bool Saklib::Qtlib::Node_Model::hasChildren(QModelIndex const& parent) const
{
    // If the index is valid
    if (mp_project_manager && parent.isValid())
    {
        // Get the stored NodeID
        NodeID indexid{parent.internalId()};
        // Ask the project_manager if this nodeid has children...

        return mp_project_manager->inode_has_children(indexid);
    }

    return false;
}

QVariant Saklib::Qtlib::Node_Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    // we only care about the column header right now...
    if (mp_project_manager)
    {
        // if this is a request for the title
        if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        {
            // Get the title for the given section...
            assert(0);
        }
    }

    // Fall through to nothing
    return QVariant();
}

QModelIndex Saklib::Qtlib::Node_Model::index(int row, int column, QModelIndex const& parent) const
{
    if (mp_project_manager && hasIndex(row, column, parent))
    {
        // Make a NodeID out of the id
        NodeID parentid = invalid_NodeID();
        if (parent.isValid())
        {
            parentid = NodeID(parent.internalId());
        }

        // Get the children of this node, THIS MUST WORK ON THE ROOT TOO
        auto child_nodes = mp_project_manager->inode_children(parentid);
        // If the inputs make sense
        if (row >= 0 && row < static_cast<int>(child_nodes.size()))
        {
            // Get the NodeID at row
            NodeID indexid{child_nodes.at(row)};

            // Test it before making an index
            if (indexid.is_valid())
            {
                return QAbstractItemModel::createIndex(row, 0, indexid.value());
            }
        }
    }

    // No conditions were met
    return QModelIndex();
}

bool Saklib::Qtlib::Node_Model::insertColumns(int column, int count, QModelIndex const& parent)
{
    if (mp_project_manager)
    {
        //assert(0);
    }

    return false;
}

bool Saklib::Qtlib::Node_Model::insertRows(int row, int count, QModelIndex const& parent)
{
    if (mp_project_manager)
    {
        //assert(0);
    }

    return false;
}

//QMap<int, QVariant> Saklib::Qtlib::Node_Model::itemData(QModelIndex const& index) const
//QModelIndexList Saklib::Qtlib::Node_Model::match(QModelIndex const& start, int role, const QVariant & value, int hits, Qt::MatchFlags flags) const
//QMimeData* Saklib::Qtlib::Node_Model::mimeData(QModelIndexList const& indexes) const
//QStringList Saklib::Qtlib::Node_Model::mimeTypes() const

bool Saklib::Qtlib::Node_Model::moveColumns(QModelIndex const& sourceParent, int sourceColumn, int count, QModelIndex const& destinationParent, int destinationChild)
{
    if (mp_project_manager)
    {
        //assert(0);
    }

    return false;
}

bool Saklib::Qtlib::Node_Model::moveRows(QModelIndex const& sourceParent, int sourceRow, int count, QModelIndex const& destinationParent, int destinationChild)
{
    if (mp_project_manager)
    {
        //assert(0);
    }

    return false;
}

QModelIndex Saklib::Qtlib::Node_Model::parent(QModelIndex const& index) const
{
    // if the index is nonsense the return the root
    if (mp_project_manager && index.isValid())
    {
        // Make a NodeID out of the id
        NodeID indexid = invalid_NodeID();
        if (index.isValid())
        {
            indexid = NodeID(index.internalId());
        }

        // if the indexid is root
        if (!indexid.is_valid())
        {
            // then return a root index as the parent
            return QModelIndex();
        }
        else
        {
            // Get the parent nodeid
            NodeID parentid = mp_project_manager->inode_parent(indexid);

            // If it's valid
            if (parentid.is_valid())
            {
                // then make an index for the parentid
                int row = mp_project_manager->row_in_parent(parentid);
                return QAbstractItemModel::createIndex(row, 0, parentid.value());
            }
        }
    }

    // Fall through to a default (root) index
    return QModelIndex();
}

bool Saklib::Qtlib::Node_Model::removeColumns(int column, int count, QModelIndex const& parent)
{
    if (mp_project_manager)
    {
        //assert(0);
    }

    return false;
}

bool Saklib::Qtlib::Node_Model::removeRows(int row, int count, QModelIndex const& parent)
{
    if (mp_project_manager)
    {
        //assert(0);
    }

    return false;
}

//QHash<int, QByteArray> Saklib::Qtlib::Node_Model::roleNames() const

int Saklib::Qtlib::Node_Model::rowCount(QModelIndex const& parent) const
{
    if (mp_project_manager)
    {
        return mp_project_manager->inode_child_count(NodeID(parent.internalId()));
    }

    return 0;
}

bool Saklib::Qtlib::Node_Model::setData(QModelIndex const& index, QVariant const& value, int role)
{
    // if index is valid and the role is editing, edit the data and return true
    if (mp_project_manager && index.isValid() && role == Qt::EditRole)
    {
        // Get the parent nodeid
        NodeID indexid{index.internalId()};

        // At this point we should only be attempting to edit data that can be edited

        // Emit a signal to tell attatched views that the data has changed at this index
        emit QAbstractItemModel::dataChanged(index, index);
        return true;

    }
    // edit conditions not met so return false
    return false;
}

bool Saklib::Qtlib::Node_Model::setHeaderData(int section, Qt::Orientation orientation, QVariant const& value, int role)
{
    if (mp_project_manager)
    {
        //assert(0);
    }

    return false;
}

//bool Saklib::Qtlib::Node_Model::setItemData(QModelIndex const& index, const QMap<int, QVariant> & roles)
//QModelIndex Saklib::Qtlib::Node_Model::sibling(int row, int column, QModelIndex const& index) const
//void Saklib::Qtlib::Node_Model::sort(int column, Qt::SortOrder order = Qt::AscendingOrder)
//QSize Saklib::Qtlib::Node_Model::span(QModelIndex const& index) const
//Qt::DropActions Saklib::Qtlib::Node_Model::supportedDragActions() const
//Qt::DropActions Saklib::Qtlib::Node_Model::supportedDropActions() const


// Custom Access
//============================================================
Saklib::Node_Project_Manager* Saklib::Qtlib::Node_Model::project_manager() const
{
    return mp_project_manager;
}

void Saklib::Qtlib::Node_Model::set_project_manager(Node_Project_Manager* new_project_manager)
{
    if (mp_project_manager != new_project_manager)
    {
        this->beginResetModel();
        mp_project_manager = new_project_manager;
        this->endResetModel();
    }
}

// Make a QModelIndex of this item by searching through the model until a postition is found that matches this
QModelIndex Saklib::Qtlib::Node_Model::make_index_of(NodeID nodeid) const
{
    if (mp_project_manager)
    {
        assert(0);
    }

    return QModelIndex();
}

QModelIndex Saklib::Qtlib::Node_Model::make_index_of(QModelIndex const& parent, size_type nodeid_value) const
{
    if (mp_project_manager)
    {
        assert(0);
    }

    return QModelIndex();
}

//void Saklib::Qtlib::Node_Model::child_indexes(Vector<QModelIndex>& results, QModelIndex const& parent) const;
//Vector<QModelIndex> Saklib::Qtlib::Node_Model::all_indexes() const;

// Return true if make_index_of returns a valid, non-root QModelIndex
bool Saklib::Qtlib::Node_Model::has_index_of(NodeID nodeid) const
{
    if (mp_project_manager)
    {
        assert(0);
    }

    return QModelIndex();
}

// Reset the entire model
void Saklib::Qtlib::Node_Model::update_all()
{

}

// Update the data for a specific item
void Saklib::Qtlib::Node_Model::update_node(NodeID nodeid)
{
    if (mp_project_manager)
    {
        assert(0);
    }
}

// Update the data for a specific item's children
void Saklib::Qtlib::Node_Model::update_node_children(NodeID nodeid)
{
    if (mp_project_manager)
    {
        assert(0);
    }
}

// Request for a context menu by view at index and position
void Saklib::Qtlib::Node_Model::context_menu(QAbstractItemView* view, QModelIndex const& index, QPoint position)
{
    if (mp_project_manager)
    {
        assert(0);
    }
}

// Allow a view to request an editor for a given index
void Saklib::Qtlib::Node_Model::request_editor(QModelIndex const& index)
{
    if (mp_project_manager)
    {
        assert(0);
    }
}

// Forward this request to the Project_Manager
//void Saklib::Qtlib::Node_Model:: request_editor(ElementID elementid);

//void Saklib::Qtlib::Node_Model::begin_model_reset();
//void Saklib::Qtlib::Node_Model::end_model_reset();
