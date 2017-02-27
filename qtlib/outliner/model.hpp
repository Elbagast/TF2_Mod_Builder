#ifndef OUTLINER_MODEL_HPP
#define OUTLINER_MODEL_HPP

#include <vector>
#include <memory>
#include <QAbstractItemModel>
class QAbstractItemView;

namespace qtlib
{
    namespace outliner
    {
        namespace abstract
        {
            class Item;
        }
        //---------------------------------------------------------------------------
        // outliner::Model
        //---------------------------------------------------------------------------
        // A specialised model with only one column. Create a sublclass of abstract::Item
        // and give it to this class in order to use it. Model relies entirely
        // on the public interface of abstract::Item.

        class Model :
                public QAbstractItemModel
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            // Construct without an associated root item. The model will function but be empty.
            explicit Model(QObject* a_parent = nullptr);
            // Construct with an associated root item. The model will function using this root.
            explicit Model(abstract::Item* a_root, QObject* a_parent = nullptr);

            ~Model() override;

            // Virtual Overrides
            //============================================================
            // Read functions
            //----------------------------------------
            // Get the flags for the Outliner_Item at a given QModelIndex.
            Qt::ItemFlags flags(QModelIndex const& a_index) const override;
            // Get the data for the Outliner_Item at a given QModelIndex.
            QVariant data(QModelIndex const& a_index, int a_role) const override;
            // Get the header data for a given section and orientation
            //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

            // Write functions
            //----------------------------------------
            // Set the data at a given index with value, using role
            bool setData(QModelIndex const& a_index, QVariant const& a_value, int a_role = Qt::EditRole) override;
            //bool setHeaderData ( int section, Qt::Orientation orientation, QVariant const& value, int role = Qt::EditRole ) override;

            // these are the inbuilt functions for this, but it isn't clear how they would be used in this case...
            //bool insertRows(int row, int count, QModelIndex const& parent = QModelIndex() ) override;
            //bool removeRows(int row, int count, QModelIndex const& parent = QModelIndex() ) override;
            //bool moveRows(QModelIndex const& a_source_parent, int a_source_row, int a_count, QModelIndex const& a_destination_parent, int a_destination_child) override;

            // Indexing
            //----------------------------------------
            // The number of rows (children) the Outliner_Item at a given QModelIndex has.
            int rowCount(QModelIndex const& a_parent = QModelIndex()) const override;
            // Always returns 1
            int columnCount(QModelIndex const& a_parent = QModelIndex()) const override;
            // Get the index of the item at the given position
            QModelIndex index(int a_row, int a_column, QModelIndex const& a_parent = QModelIndex()) const override;
            // Get the index of the parent of the item at a given index
            QModelIndex parent(QModelIndex const& a_index) const override;

            // Custom Access
            //============================================================
            // Does the model have any data to show? i.e. is there a root item?
            bool is_active() const;
            // Access the root item. The root is not owned by Outliner_Model.
            abstract::Item* get_root() const;
            // Replace the root item and refresh the model in all views. The old
            // root is not deleted. The new root is not owned by Outliner_Model.
            void set_root(abstract::Item* a_root);

            // Make an index from an item, mostly so that Outliner_Item can make an index of itself without being a friend
            QModelIndex create_index_from_item(abstract::Item* item) const;

            // call QAbstractItemView->edit on this item
            //void callEditInView(QAbstractItemView* view, Outliner_Item* item);
            //void callEditInView(QAbstractItemView* view, QModelIndex const& index);

            // Update Calls
            //============================================================
            // Functions to tell the model to emit change signals


            // Helper classes
            //============================================================
            // Providing access to these signals without implementing the actions.



            friend class Rows_Mover;
            class Rows_Mover
            {
            public:
                explicit Rows_Mover(Model* a_model, QModelIndex const& a_source_parent, int a_source_row, int a_source_last, QModelIndex const& a_destination_parent, int a_destination_child);
                ~Rows_Mover();
            private:
                Model* m_model;
            };

            friend class Rows_Mover;
            class Rows_Inserter
            {
            public:
                explicit Rows_Inserter(Model* a_model, int a_row, int a_last, QModelIndex const& a_parent = QModelIndex());
                ~Rows_Inserter();
            private:
                Model* m_model;
            };

            friend class Rows_Remover;
            class Rows_Remover
            {
            public:
                explicit Rows_Remover(Model* a_model, int a_row, int a_last, QModelIndex const& a_parent = QModelIndex());
                ~Rows_Remover();
            private:
                Model* m_model;
            };

            void data_changed(QModelIndex const& a_top_left, QModelIndex const& a_bottom_right, QVector<int> const& a_roles = QVector<int>());
            Rows_Mover make_rows_mover(QModelIndex const& a_source_parent, int a_source_row, int a_source_last, QModelIndex const& a_destination_parent, int a_destination_child);
            Rows_Inserter make_rows_inserter(int a_row, int a_last, QModelIndex const& a_parent = QModelIndex());
            Rows_Remover make_rows_remover(int a_row, int a_last, QModelIndex const& a_parent = QModelIndex());


            Rows_Mover make_row_mover(QModelIndex const& a_source_parent, int a_source_row, QModelIndex const& a_destination_parent, int a_destination_child);
            Rows_Inserter make_row_inserter(int a_row, QModelIndex const& a_parent = QModelIndex());
            Rows_Remover make_row_remover(int a_row, QModelIndex const& a_parent = QModelIndex());


        signals:
            void signal_editor_requested(abstract::Item* a_item);
            void signal_unsaved_edits(bool a_state);


        private:
            // Data Members
            //============================================================
            abstract::Item* m_root;
        };
    }

} // namespace qtlib

#endif // OUTLINER_MODEL_HPP
