#include "outliner_model.h"

#include "../project_widget.h"
#include "../../project_manager.h"

#include "../qvariant_operations.h"
#include "../qstring_operations.h"

#include <QMenu>
#include <QAbstractItemView>
#include <QtDebug>

// Special 6
//============================================================
Saklib::Qtlib::Outliner_Model::Outliner_Model(Project_Widget* project_widget, QObject* parent):
    QAbstractItemModel(parent),
    mp_project_widget(project_widget)
{
    assert(mp_project_widget);
}
Saklib::Qtlib::Outliner_Model::~Outliner_Model() = default;


// Virtual Overrides
//============================================================
// Read functions
//----------------------------------------
// Get the flags for a given QModelIndex.
Qt::ItemFlags Saklib::Qtlib::Outliner_Model::flags(QModelIndex const& index) const
{
    // if index is valid
    if (index.isValid())
    {
        // Make a proxy out of the id
        ProxyID indexid{ProxyID::unpack(index.internalId())};
        assert(index.internalId() == ProxyID::pack(indexid));

        if (!indexid.is_valid())
        {
            return Qt::NoItemFlags;
        }
        else if (indexid.is_element())
        {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable; // for name edit
        }
        else if (indexid.is_attribute())
        {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
    }

    // else no flags
    return Qt::NoItemFlags;
}
// Get the data for the Outliner_Item at a given QModelIndex.
QVariant Saklib::Qtlib::Outliner_Model::data(QModelIndex const& index, int role) const
{
    // if index is valid
    if (index.isValid()
        && role == Qt::DisplayRole
        && index.column() == 0)
    {
        // Make a proxy out of the id
        ProxyID indexid{ProxyID::unpack(index.internalId())};
        assert(index.internalId() == ProxyID::pack(indexid));

        // what does it represent?
        // get the approriate data
        if (!indexid.is_valid())
        {
            return QVariant("None");
        }
        else if (indexid.is_element())
        {
            return to_QVariant(mp_project_widget->project_manager().element_name(indexid.elementid()));
        }
        else if (indexid.is_attribute())
        {
            return to_QVariant(mp_project_widget->project_manager().attribute_name(indexid.attributeid()));
        }
    }

    // else return nothing
    return QVariant();
}
// The number of rows (children) the ProxyID at a given QModelIndex has.
int Saklib::Qtlib::Outliner_Model::rowCount(QModelIndex const& index) const
{
    if (index.column() > 0)
    {
        return 0;
    }

    if (!index.isValid())
    {
        return mp_project_widget->project_manager().outliner_row_count_root();
    }

    // Make a proxy out of the id
    ProxyID indexid{ProxyID::unpack(index.internalId())};
    assert(index.internalId() == ProxyID::pack(indexid));

    if (!indexid.is_valid())
    {
        //return mp_project_widget->project_manager().outliner_row_count_root();
        return 0;
    }
    else if (indexid.is_element())
    {
        //qDebug() << "ElementID = " << indexid.elementid_value();
        return mp_project_widget->project_manager().outliner_row_count(indexid.elementid());
    }
    else if (indexid.is_attribute())
    {
        //qDebug() << "AttributeID = " << indexid.elementid_value() <<" : "<< indexid.attribute_index();
        return mp_project_widget->project_manager().outliner_row_count(indexid.attributeid());
    }
    //else if (!index.isValid()) // root index
    //{
     //   return mp_project_widget->project_manager().outliner_row_count_root();
    //}
    else
    {
        return 0;
    }
}
// The number of columns (children) the item at a given QModelIndex has,
// but this just returns 1 as there is only one column.
int Saklib::Qtlib::Outliner_Model::columnCount(QModelIndex const& /*parent*/) const
{
    return 1;
}

// Write functions
// This is used to edit the data structure with or without a delegate installed.
bool Saklib::Qtlib::Outliner_Model::setData(QModelIndex const& index, QVariant const& value, int role)
{
    // if index is valid and the role is editing, edit the data and return true
    if (index.isValid() && role == Qt::EditRole)
    {
        // get the id
        ProxyID index_id{ProxyID::unpack(index.internalId())};
        if (index_id.is_element())
        {
            // EDIT THE DATA

            // make a command to edit the name...
            mp_project_widget->project_manager().undoable_element_set_name(index_id.elementid(), to_String(value));

            //Works! but going to want to reorganise updating data in views...

            // Emit a signal to tell attatched views that the data has changed at this index
            emit QAbstractItemModel::dataChanged(index, index);
            return true;
        }

    }
    // edit conditions not met so return false
    return false;
}

/*
bool Saklib::Qtlib::Outliner_Model::insertRows(int row, int count, QModelIndex const& parent)
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
bool Saklib::Qtlib::Outliner_Model::removeRows(int row, int count, QModelIndex const& parent)
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
// Get the index of the item at the given position

QModelIndex Saklib::Qtlib::Outliner_Model::index(int row, int column, QModelIndex const& parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    ProxyID parentid = invalid_proxyid();
    if (parent.isValid())
    {
        parentid = ProxyID::unpack(parent.internalId());
        assert(parent.internalId() == ProxyID::pack(parentid));
    }

    // if parent is the root
    if (!parentid.is_valid())
    {
        // Then this index represents a Root ElementID

        auto root_elementids = mp_project_widget->project_manager().root_elementids();
        // If the inputs make sense
        if (row >= 0 && row < static_cast<int>(root_elementids.size()))
        {
            // Get the ElementID at row
            ElementID index_elementid{mp_project_widget->project_manager().root_elementids().at(row)};

            // Test it before making an index
            if (index_elementid.is_valid())
            {
                return QAbstractItemModel::createIndex(row, 0, ProxyID::pack(index_elementid));
            }
        }
    }
    // else it's an Element
    else if (parentid.is_element())
    {
        // Then this index represents an ElementID

        // get the item by row in parent
        AttributeID index_attributeid{mp_project_widget->project_manager().outliner_child_at_row(parentid.elementid(), row)};

        // Test it before making an index
        if (index_attributeid.is_valid())
        {
            return QAbstractItemModel::createIndex(row, 0, ProxyID::pack(index_attributeid));
        }

    }
    // else it's an Attribute
    else if (parentid.is_attribute())
    {
        // Then this index represents an AttributeID

        // get the item by row in parent
        ElementID index_elementid{mp_project_widget->project_manager().outliner_child_at_row(parentid.attributeid(), row)};

        // Test it before making an index
        if (index_elementid.is_valid())
        {
            return QAbstractItemModel::createIndex(row, 0, ProxyID::pack(index_elementid));
        }
    }

    // No conditions were met
    return QModelIndex();
}
// Get the index of the parent of the item at a given index
QModelIndex Saklib::Qtlib::Outliner_Model::parent(QModelIndex const& index) const
{
    // if the index is nonsense the return the root
    if (!index.isValid())
    {
        return QModelIndex();
    }

    // indexid is the id in the index
    ProxyID indexid{ProxyID::unpack(index.internalId())};
    assert(index.internalId() == ProxyID::pack(indexid));

    // if the indexid is root
    if (!indexid.is_valid())
    {
        // then return a root index as the parent
        return QModelIndex();
    }
    // else it's an Element
    else if (indexid.is_element())
    {
        // get the parent
        AttributeID parent{mp_project_widget->project_manager().parent_of(indexid.elementid())};

        // Test it
        if (parent.is_valid())
        {
            // then make an index for the parentid
            int row = mp_project_widget->project_manager().outliner_row_in_parent(parent);
            return QAbstractItemModel::createIndex(row, 0, ProxyID::pack(parent));
        }
    }
    // else it's an Attribute
    else if (indexid.is_attribute())
    {
        // get the parent
        ElementID parent{indexid.elementid()};

        // Test it
        if (parent.is_valid())
        {
            // then make an index for the parentid
            int row = mp_project_widget->project_manager().outliner_row_in_parent(parent);
            return QAbstractItemModel::createIndex(row, 0, ProxyID::pack(parent));
        }
    }

    return QModelIndex();
}

// Custom Access
//============================================================
// Make a QModelIndex of this item by searching through the model until a postition is found that matches this
QModelIndex Saklib::Qtlib::Outliner_Model::make_index_of(ElementID elementid) const
{
    return make_index_of(ProxyID(elementid));
}
QModelIndex Saklib::Qtlib::Outliner_Model::make_index_of(AttributeID attributeid) const
{
    return make_index_of(ProxyID(attributeid));
}
QModelIndex Saklib::Qtlib::Outliner_Model::make_index_of(ProxyID proxyid) const
{
    size_type target_match{ProxyID::pack(proxyid)};

    // if supplied with an invalid input, return a root index
    if (!proxyid.is_valid())
    {
        return QModelIndex();
    }
    // This is going to be slooooooooow
    QModelIndex root_index{};
    return make_index_of(root_index, target_match);

    // This is a candidate for another way of doing this -> maybe make a list of ProxyID that form an ownership chain to the target?
}
QModelIndex Saklib::Qtlib::Outliner_Model::make_index_of(QModelIndex const& parent, size_type proxyid_value) const
{
    for (int row = 0, end = rowCount(parent); row != end; ++row)
    {
        QModelIndex next_index{index(row, 0, parent)};
        assert(next_index.isValid());
        if (next_index.internalId() == proxyid_value)
        {
            return next_index;
        }
        else
        {
            // recurse through children
            return make_index_of(next_index, proxyid_value);
        }
    }

    auto proxyid = ProxyID::unpack(proxyid_value);
    if (proxyid.is_element())
        qDebug() << "ElementID not found: " << proxyid.elementid_value();
    else if (proxyid.is_element())
        qDebug() << "AttributeID not found: " << proxyid.elementid_value() << ":" << proxyid.attribute_index();

    return QModelIndex();
}

void Saklib::Qtlib::Outliner_Model::child_indexes(Vector<QModelIndex>& results, QModelIndex const& parent) const
{
    int row_count = this->rowCount(parent);
    for (int row = 0; row != row_count; ++row)
    {
        auto child_index = this->index(row,0,parent);
        results.push_back(child_index);
        if (this->rowCount(child_index) > 0)
            child_indexes(results, child_index);
    }
}

Saklib::Vector<QModelIndex> Saklib::Qtlib::Outliner_Model::all_indexes() const
{
    Vector<QModelIndex> result{};
    child_indexes(result, QModelIndex());
    return result;
}

// Return true if make_index_of returns a valid, non-root QModelIndex
bool Saklib::Qtlib::Outliner_Model::has_index_of(ElementID elementid) const
{
    return make_index_of(elementid) != QModelIndex();
}
bool Saklib::Qtlib::Outliner_Model::has_index_of(AttributeID attributeid) const
{
    return make_index_of(attributeid) != QModelIndex();
}
bool Saklib::Qtlib::Outliner_Model::has_index_of(ProxyID proxyid) const
{
    return make_index_of(proxyid) != QModelIndex();
}

// Reset the entire model
void Saklib::Qtlib::Outliner_Model::update_all()
{
    beginResetModel();
    endResetModel();
}

// Update the data for a specific item
void Saklib::Qtlib::Outliner_Model::update_item(ElementID elementid)
{
    auto index = make_index_of(elementid);
    emit QAbstractItemModel::dataChanged(index, index);
}
void Saklib::Qtlib::Outliner_Model::update_item(AttributeID attributeid)
{
    // This just updates the text in this index...
    auto index = make_index_of(attributeid);
    emit QAbstractItemModel::dataChanged(index, index);
}

// Update the data for a specific item's children
void Saklib::Qtlib::Outliner_Model::update_children(ElementID elementid)
{
    auto child_count = mp_project_widget->project_manager().element(elementid).attribute_count();
    if (child_count > 0)
    {
        auto first_child = make_index_of(AttributeID(elementid, 0));
        auto last_child = make_index_of(AttributeID(elementid, child_count - 1));
        // Emit a signal to tell attatched views that the data has changed at this index
        emit QAbstractItemModel::dataChanged(first_child, last_child);
    }
}
void Saklib::Qtlib::Outliner_Model::update_children(AttributeID attributeid)
{
    auto type = mp_project_widget->project_manager().attribute_type_enum(attributeid);
    if (type == Type_Enum::ElementID)
    {
        auto child_elementid = mp_project_widget->project_manager().attribute_type_cast<ElementID>(attributeid)->value();
        if (child_elementid.is_valid())
        {
            auto child_index = make_index_of(child_elementid);
            //assert(child_index.isValid());
            // Emit a signal to tell attatched views that the data has changed at this index
            emit QAbstractItemModel::dataChanged(child_index, child_index);
        }
    }
    else if (type == Type_Enum::Vector_ElementID)
    {
        auto const& children = mp_project_widget->project_manager().attribute_type_cast<Vector_ElementID>(attributeid)->vector();

        if (!children.empty())
        {
            auto first_child = make_index_of(children.front());
            auto last_child = make_index_of(children.back());
            assert(first_child.isValid() && last_child.isValid());
            // Emit a signal to tell attatched views that the data has changed at this index
            emit QAbstractItemModel::dataChanged(first_child, last_child);
        }
    }
}

// Add or remove rows from Attributes
void Saklib::Qtlib::Outliner_Model::add_row(AttributeID attributeid, int row)
{
    auto index = make_index_of(attributeid);
    this->beginInsertRows(index, row, row);
    this->endInsertRows();
}

void Saklib::Qtlib::Outliner_Model::remove_row(AttributeID attributeid, int row)
{
    auto index = make_index_of(attributeid);
    this->beginRemoveRows(index, row, row);
    this->endRemoveRows();
}


// Request for a context menu by view at index and position
void Saklib::Qtlib::Outliner_Model::custom_context_menu(QAbstractItemView* view, QModelIndex const& index, QPoint position)
{
    // indexid will be the id in the index but starts invalid
    ProxyID indexid{};

    // if the index is valid then get the id from it
    if (index.isValid())
    {
        // indexid is the id in the index
        indexid = ProxyID::unpack(index.internalId());
        assert(index.internalId() == ProxyID::pack(indexid));
    }

    // start the context menu
    QMenu menu{};
    // now fill it dependent on what this index represents

    // if the indexid is root
    if (!indexid.is_valid())
    {
        // then do the general context menu
        menu.addAction("Root Context Menu")->setEnabled(false);
        menu.addSeparator();
    }
    // else it's an Element
    else if (indexid.is_element())
    {
        auto index_elementid = indexid.elementid();
        auto menu_title = mp_project_widget->project_manager().element_name(index_elementid);

        menu.addAction(menu_title.c_str())->setEnabled(false);
        menu.addSeparator();

        // Rename this Element
        auto rename_action = menu.addAction("Rename");
        // connect the action to a lambda that calls edit in the view
        QObject::connect(rename_action, &QAction::triggered,
                         [view, &index](){ view->edit(index); });

        // Open the editor widget for this Element
        auto edit_action = menu.addAction("Edit");
        QObject::connect(edit_action, &QAction::triggered,
                         [this, index_elementid](){ this->request_editor(index_elementid); });

    }
    // else it's an Attribute
    else if (indexid.is_attribute())
    {
        auto index_attributeid = indexid.attributeid();
        auto index_elementid = index_attributeid.elementid();

        auto menu_title = mp_project_widget->project_manager().element_name(index_elementid)
                          + " : "
                          + mp_project_widget->project_manager().attribute_name(index_attributeid);

        menu.addAction(menu_title.c_str())->setEnabled(false);
        menu.addSeparator();

        // Open the editor widget for the Attribute's Element
        auto edit_action = menu.addAction("Edit");
        QObject::connect(edit_action, &QAction::triggered,
                         [this, index_elementid](){ this->request_editor(index_elementid); });

    }
    else
    {
        menu.addAction("Bad context menu request.")->setEnabled(false);
    }

    menu.exec(position);
    // Assembling the context menu is going to need some thought.
}

// Allow a view to request an editor for a given index
void Saklib::Qtlib::Outliner_Model::request_editor(QModelIndex const& index)
{
    // indexid will be the id in the index but starts invalid
    ProxyID indexid{};

    // if the index is valid then get the id from it
    if (index.isValid())
    {
        // indexid is the id in the index
        indexid = ProxyID::unpack(index.internalId());
        assert(index.internalId() == ProxyID::pack(indexid));
    }

    // if the indexid is root
    if (!indexid.is_valid())
    {
        // nothing
    }
    // else it's an Element
    else if (indexid.is_element())
    {
        request_editor(indexid.elementid());
    }
    // else it's an Attribute
    else if (indexid.is_attribute())
    {
        request_editor(indexid.elementid());
    }
    else
    {
        // nothing
    }
}

// Forward this request to the Project_Manager
void Saklib::Qtlib::Outliner_Model::request_editor(ElementID elementid)
{
    mp_project_widget->open_editor(elementid);
}

void Saklib::Qtlib::Outliner_Model::begin_model_reset()
{
    this->beginResetModel();
}

void Saklib::Qtlib::Outliner_Model::end_model_reset()
{
    this->endResetModel();
}
