#include "outliner_model.h"
#include "outliner_abstract_item.h"
#include <cassert>
#include <QDebug>

//---------------------------------------------------------------------------
// outliner::Model
//---------------------------------------------------------------------------
// A specialised model with only one column. Create a sublclass of abstract::Item
// and give it to this class in order to use it. Model relies entirely
// on the public interface of abstract::Item.

// Special 6
//============================================================
// Construct without an associated root item. The model will function but be empty.
qtlib::outliner::Model::Model(QObject* a_parent):
    QAbstractItemModel(a_parent),
    m_root{nullptr}
{
}

// Construct with an associated root item. The model will function using this root.
qtlib::outliner::Model::Model(abstract::Item* a_root, QObject* a_parent):
    QAbstractItemModel(a_parent),
    m_root{a_root}
{
}
qtlib::outliner::Model::~Model() = default;


// Virtual Overrides
//============================================================
// Read functions
//----------------------------------------
// Get the flags for the abstract::Item at a given QModelIndex.
Qt::ItemFlags qtlib::outliner::Model::flags(QModelIndex const& a_index) const
{
    // if the model is inactive
    if (!is_active())
    {
        return Qt::NoItemFlags;
    }

    // if this index exists, get the flags from the abstract::Item* stored in the index
    if (a_index.isValid())//isIndexValid(index))
    {
        return abstract::Item::from_index(a_index)->get_flags();
    }
    // else no flags
    else
    {
        return Qt::NoItemFlags;
    }
}
// Get the data for the abstract::Item at a given QModelIndex.
QVariant qtlib::outliner::Model::data(QModelIndex const& a_index, int a_role) const
{
    // if the model is inactive
    if (!is_active())
    {
        return QVariant();
    }

    // if  this index exists, get the data from the abstract::Item* stored in the index
    if (a_index.isValid()
        //&& a_role == Qt::DisplayRole
        && a_index.column() == 0
        )//isIndexValid(index))
    {
        return abstract::Item::from_index(a_index)->get_data(a_role);
    }
    // else return nothing
    else
    {
        return QVariant();
    }
}
// Write functions
// This is used to edit the data structure with or without a delegate installed.
bool qtlib::outliner::Model::setData(QModelIndex const& index, QVariant const& value, int role)
{
    // if the model is inactive
    if (!is_active())
    {
        return false;
    }

    // if index is valid and the role is editing, edit the data and return true
    if (index.isValid()//isIndexValid(index)
        && role == Qt::EditRole)
    {
        // Virtual call to item pointer stored in index
        abstract::Item::from_index(index)->set_data(value);
        // Emit a signal to tell attatched views that the data has changed at this index
        emit QAbstractItemModel::dataChanged(index, index);
        return true;
    }
    // else do nothing and return false
    else
    {
        return false;
    }
}

/*
bool qtlib::outliner::Model::insertRows(int row, int count, QModelIndex const& parent)
{
    if (parent.isValid())
    {
        emit beginInsertRows(parent, row, row+count);

        // do stuff

        emit endInsertRows();
        return true;
    }
    else
        return false;
}
bool qtlib::outliner::Model::removeRows(int row, int count, QModelIndex const& parent)
{
    if (parent.isValid())
    {
        emit beginRemoveRows(parent, row, row+count);

        // do stuff

        emit endInsertRows();
        return true;
    }
    else
        return false;
}
*/

// Indexing
//----------------------------------------
// The number of rows (children) the abstract::Item at a given QModelIndex has.
int qtlib::outliner::Model::rowCount(QModelIndex const& a_parent) const
{
    //qDebug() << "rowCount: " << a_parent;

    // if the model is inactive
    if (!is_active())
    {
        //qDebug() << " inactive";
        return 0;
    }

    // if bad column
    if (a_parent.column() > 0)
    {
        //qDebug() << " bad column";
        return 0;
    }

    // Make a pointer that will be the l_parent_item for parent
    abstract::Item const* l_item{nullptr};

    // if the index is valid then l_parent_item is the root item
    if (a_parent.isValid()) // && hasIndex(parent.row(), parent.column(), parent.parent()) ??
    {
        //qDebug() << " children = " << Outliner_Item::from_index(a_parent)->child_count();
        l_item = abstract::Item::from_index(a_parent);
    }
    // else l_parent_item is the root item
    else
    {
        //qDebug() << " root children = " << m_root->child_count();
        l_item = m_root;
    }
    // Get the child count from the item.
    return l_item->get_child_count();
}

// The number of columns (children) the abstract::Item at a given QModelIndex has,
// but this just returns 1 as there is only one column.
int qtlib::outliner::Model::columnCount(QModelIndex const& /*a_parent*/) const
{
    //qDebug() << "columnCount: " << a_parent;
    // if the model is inactive
    if (!is_active())
    {
        //qDebug() << " inactive";
        return 0;
    }
    //qDebug() << " = 1";
    return 1;
}

// Get the index of the item at the given position
QModelIndex qtlib::outliner::Model::index(int a_row, int a_column, QModelIndex const& a_parent) const
{
    //qDebug() << "index: " << a_row << " " << a_column << " " << a_parent;

    // if the model is inactive
    if (!is_active())
    {
        //qDebug() << " model not active";
        return QModelIndex();
    }

    // if the model doesn't have an index for this, return an empty (root) index
    if (!hasIndex(a_row, a_column, a_parent))
    {
        //qDebug() << " no index";
        return QModelIndex();
    }

    // Make a pointer that will be the l_parent_item for the index returned
    abstract::Item* l_parent_item{nullptr};

    // if the parent index is valid
    if (a_parent.isValid())
    {
        // get the item
        l_parent_item = abstract::Item::from_index(a_parent);
    }
    // else it's the root
    else
    {
        l_parent_item = m_root;
    }
    assert(l_parent_item != nullptr);
    assert(a_row != -1);
    assert(a_row < l_parent_item->get_child_count());
    // Make a pointer that will be the item for the index returned
    abstract::Item* l_child_item{l_parent_item->get_child_at(a_row)};

    // if l_child_item is valid (parent had a child at row) then create and return and index for l_child_item
    if (l_child_item != nullptr)
    {
        //qDebug() << " result = " << a_row << ", " << a_column << ", " << l_child_item->get_data() ;
        return QAbstractItemModel::createIndex(a_row, a_column, l_child_item); // THIS IS WHERE THE MAGIC HAPPENS
    }
    // else return an empty (root) index
    else
    {
        //qDebug() << " no child at row";
        return QModelIndex();
    }
}
// Get the index of the parent of the item at a given index
QModelIndex qtlib::outliner::Model::parent(QModelIndex const& a_index) const
{
    //qDebug() << "parent: " << a_index;

    // if the model is inactive
    if (!is_active())
    {
        //qDebug() << " model not active";
        return QModelIndex();
    }

    // if root is not set or the model doesn't have an index for this, return an empty (root) index
    if (!a_index.isValid())
    {
        //qDebug() << " invalid";
        return QModelIndex();
    }

    // l_child_item is the item in the index
    abstract::Item* l_child_item = abstract::Item::from_index(a_index);

    // l_parent_item is the parent of l_child_item
    abstract::Item* l_parent_item = l_child_item->get_parent();

    assert(l_child_item != nullptr);
    assert(l_parent_item != nullptr);

    // if the parent is the root, then return an empty (root) index
    if (l_parent_item == m_root)
    {
        //qDebug() << " parent is root";
        return QModelIndex();
    }
    // else create and return and index for l_parent_item
    else
    {
        //qDebug() << " result = " << l_parent_item->row() << ", " << 0 << ", " << l_parent_item ;
        return QAbstractItemModel::createIndex(l_parent_item->index_in_parent(), 0, l_parent_item);
    }
}

// Custom Access
//============================================================
// Does the model have any data to show? i.e. is there a root item?
bool qtlib::outliner::Model::is_active() const
{
    return m_root != nullptr;
}
// Access the root item. The root is not owned by Outliner_Model.
qtlib::outliner::abstract::Item* qtlib::outliner::Model::get_root() const
{
    return m_root;
}
// Replace the root item and refresh the model in all views. The old
// root is not deleted. The new root is not owned by Outliner_Model.
void qtlib::outliner::Model::set_root(abstract::Item* a_root)
{
    this->beginResetModel();
    m_root = a_root;
    this->endResetModel();
}

// Make an index from an item, mostly so that abstract::Item can make an index of itself without being a friend
QModelIndex qtlib::outliner::Model::create_index_from_item(abstract::Item* a_item) const
{
    // if the model is inactive
    if (!is_active())
    {
        return QModelIndex();
    }

    // if the item is a nullptr
    if (a_item == nullptr)
    {
        return QModelIndex();
    }

    // Should probably check if the item is in this model somewhere.

    // if the item is the root, make a root (empty) index
    if (a_item == m_root)
    {
        return QModelIndex();
    }
    // else forward to existing protected function.
    else
    {
        // Column is always 0 in this model, so be wary if copying this code.
        return QAbstractItemModel::createIndex(a_item->index_in_parent(), 0, static_cast<void*>(a_item));
    }
}

// Helper classes
//============================================================
// Providing access to these signals without implementing the actions.

qtlib::outliner::Model::Rows_Mover::Rows_Mover(Model* a_model, QModelIndex const& a_source_parent, int a_source_first, int a_source_last, QModelIndex const& a_destination_parent, int a_destination_child):
    m_model{a_model}
{
    m_model->beginMoveRows(a_source_parent, a_source_first, a_source_last, a_destination_parent, a_destination_child);
}

qtlib::outliner::Model::Rows_Mover::~Rows_Mover()
{
    m_model->endMoveRows();
}

qtlib::outliner::Model::Rows_Inserter::Rows_Inserter(Model* a_model, int a_row, int a_last, QModelIndex const& a_parent):
    m_model{a_model}
{
    m_model->beginInsertRows(a_parent, a_row, a_last);
}

qtlib::outliner::Model::Rows_Inserter::~Rows_Inserter()
{
    m_model->endInsertRows();
}

qtlib::outliner::Model::Rows_Remover::Rows_Remover(Model* a_model, int a_row, int a_last, QModelIndex const& a_parent):
    m_model{a_model}
{
    m_model->beginRemoveRows(a_parent, a_row, a_last);
}

qtlib::outliner::Model::Rows_Remover::~Rows_Remover()
{
    m_model->endRemoveRows();
}



void qtlib::outliner::Model::data_changed(QModelIndex const& a_top_left, QModelIndex const& a_bottom_right, QVector<int> const& a_roles)
{
    emit dataChanged(a_top_left, a_bottom_right, a_roles);
}

qtlib::outliner::Model::Rows_Mover qtlib::outliner::Model::make_rows_mover(QModelIndex const& a_source_parent, int a_source_row, int a_source_last, QModelIndex const& a_destination_parent, int a_destination_child)
{
    return Rows_Mover(this, a_source_parent, a_source_row, a_source_last, a_destination_parent, a_destination_child);
}

qtlib::outliner::Model::Rows_Inserter qtlib::outliner::Model::make_rows_inserter(int a_row, int a_last, QModelIndex const& a_parent)
{
    return Rows_Inserter(this, a_row, a_last, a_parent);
}

qtlib::outliner::Model::Rows_Remover qtlib::outliner::Model::make_rows_remover(int a_row, int a_last, QModelIndex const& a_parent)
{
    return Rows_Remover(this, a_row, a_last, a_parent);
}

qtlib::outliner::Model::Rows_Mover qtlib::outliner::Model::make_row_mover(QModelIndex const& a_source_parent, int a_source_row, QModelIndex const& a_destination_parent, int a_destination_child)
{
    return Rows_Mover(this, a_source_parent, a_source_row, a_source_row, a_destination_parent, a_destination_child);
}

qtlib::outliner::Model::Rows_Inserter qtlib::outliner::Model::make_row_inserter(int a_row, QModelIndex const& a_parent)
{
    return Rows_Inserter(this, a_row, a_row, a_parent);
}

qtlib::outliner::Model::Rows_Remover qtlib::outliner::Model::make_row_remover(int a_row, QModelIndex const& a_parent)
{
    return Rows_Remover(this, a_row, a_row, a_parent);
}
