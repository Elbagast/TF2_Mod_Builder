#ifndef NODE_MODEL_H
#define NODE_MODEL_H

#include "../../types.h"
#include "../../elementid.h"
#include "../../attributeid.h"
#include "../../proxyid.h"

#include <QAbstractItemModel>
class QAbstractItemView;

namespace Saklib
{
    class Node_Project_Manager;

    namespace Qtlib
    {
        enum class Node_Outliner_Columns : int
        {
            Name = 0,
            NodeID,
            Data_Type,
            Data
        };

        /*
        Node_Model
        ====================================================================================================
        A model that displays ALL of the information about ALL nodes relative to the given setup of each node.
        */
        class Node_Model :
                public QAbstractItemModel
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            explicit Node_Model(QObject* parent = nullptr);
            explicit Node_Model(Node_Project_Manager* project_manager, QObject* parent = nullptr);
            ~Node_Model() override;

            // NO COPYING
            Node_Model(Node_Model const& other) = delete;
            Node_Model& operator=(Node_Model const& other) = delete;

            // Implicit default move
            //Node_Model(Node_Model && other) = default;
            //Node_Model& operator=(Node_Model && other) = default;

            // Virtual Overrides
            //============================================================
            // These are all the public virtual functions of QAbstractItemModel, not all need to be implemented

            //QModelIndex buddy(QModelIndex const& index) const override;
            //bool canDropMimeData(QMimeData const* data, Qt::DropAction action, int row, int column, const QModelIndex & parent) const override;
            //bool canFetchMore(QModelIndex const& parent) const override;
            int columnCount(QModelIndex const& parent = QModelIndex()) const override;
            QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;
            //bool dropMimeData(QMimeData const* data, Qt::DropAction action, int row, int column, const QModelIndex & parent) override;
            //void fetchMore(QModelIndex const& parent) override;
            Qt::ItemFlags flags(QModelIndex const& index) const override;
            bool hasChildren(QModelIndex const& parent = QModelIndex()) const override;
            QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
            QModelIndex index(int row, int column, QModelIndex const& parent = QModelIndex()) const override;
            bool insertColumns(int column, int count, QModelIndex const& parent = QModelIndex()) override;
            bool insertRows(int row, int count, QModelIndex const& parent = QModelIndex()) override;
            //QMap<int, QVariant> itemData(QModelIndex const& index) const override;
            //QModelIndexList match(QModelIndex const& start, int role, const QVariant & value, int hits = 1, Qt::MatchFlags flags = Qt::MatchFlags( Qt::MatchStartsWith | Qt::MatchWrap )) const override;
            //QMimeData* mimeData(QModelIndexList const& indexes) const override;
            //QStringList mimeTypes() const override;
            bool moveColumns(QModelIndex const& sourceParent, int sourceColumn, int count, QModelIndex const& destinationParent, int destinationChild) override;
            bool moveRows(QModelIndex const& sourceParent, int sourceRow, int count, QModelIndex const& destinationParent, int destinationChild) override;
            QModelIndex parent(QModelIndex const& index) const override;
            bool removeColumns(int column, int count, QModelIndex const& parent = QModelIndex()) override;
            bool removeRows(int row, int count, QModelIndex const& parent = QModelIndex()) override;
            //QHash<int, QByteArray> roleNames() const override;
            int rowCount(QModelIndex const& parent = QModelIndex()) const override;
            bool setData(QModelIndex const& index, QVariant const& value, int role = Qt::EditRole) override;
            bool setHeaderData(int section, Qt::Orientation orientation, QVariant const& value, int role = Qt::EditRole) override;
            //bool setItemData(QModelIndex const& index, const QMap<int, QVariant> & roles) override;
            //QModelIndex sibling(int row, int column, QModelIndex const& index) const override;
            //void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;
            //QSize span(QModelIndex const& index) const override;
            //Qt::DropActions supportedDragActions() const override;
            //Qt::DropActions supportedDropActions() const override;


            // Custom Access
            //============================================================
            Node_Project_Manager* project_manager() const;
            void set_project_manager(Node_Project_Manager* new_project_manager);

            // Make a QModelIndex of this item by searching through the model until a postition is found that matches this
            QModelIndex make_index_of(NodeID nodeid) const;
            QModelIndex make_index_of(QModelIndex const& parent, size_type nodeid_value) const;

            //void child_indexes(Vector<QModelIndex>& results, QModelIndex const& parent) const;
            //Vector<QModelIndex> all_indexes() const;

            // Return true if make_index_of returns a valid, non-root QModelIndex
            bool has_index_of(NodeID nodeid) const;

            // Reset the entire model
            void update_all();

            // Update the data for a specific item
            void update_node(NodeID nodeid);

            // Update the data for a specific item's children
            void update_node_children(NodeID nodeid);

            // Request for a context menu by view at index and position
            void context_menu(QAbstractItemView* view, QModelIndex const& index, QPoint position);

            // Allow a view to request an editor for a given index
            void request_editor(QModelIndex const& index);

            // Forward this request to the Project_Manager
            //void request_editor(ElementID elementid);

            //void begin_model_reset();
            //void end_model_reset();

        private:
            // Data Members
            //============================================================
            Node_Project_Manager* mp_project_manager;
        };

    } // namespace Qtlib
}  // namespace Saklib



#endif // NODE_MODEL_H
