#ifndef OUTLINER_MODEL_H
#define OUTLINER_MODEL_H

#include <vector>
#include <memory>
#include <QAbstractItemModel>
class QAbstractItemView;

namespace qtlib
{
    class Outliner_Item;

    //---------------------------------------------------------------------------
    // Outliner_Model
    //---------------------------------------------------------------------------
    // A specialised model with only one column. Create a sublclass of Outliner_Item
    // and give it to this class in order to use it. Outliner_Model relies entirely
    // on the public interface of Outliner_Item.

    class Outliner_Model :
            public QAbstractItemModel
    {
        Q_OBJECT
    public:
        // Special 6
        //============================================================
        // Construct without an associated root item. The model will function but be empty.
        explicit Outliner_Model(QObject* a_parent = nullptr);
        // Construct with an associated root item. The model will function using this root.
        explicit Outliner_Model(Outliner_Item* a_root, QObject* a_parent = nullptr);

        ~Outliner_Model() override;

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
       // bool setHeaderData ( int section, Qt::Orientation orientation, QVariant const& value, int role = Qt::EditRole ) override;

        // these are the inbuilt functions for this, but it isn't clear how they would be used in this case...
        //bool insertRows(int row, int count, QModelIndex const& parent = QModelIndex() ) override;
        //bool removeRows(int row, int count, QModelIndex const& parent = QModelIndex() ) override;

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
        Outliner_Item* get_root() const;
        // Replace the root item and refresh the model in all views. The old
        // root is not deleted. The new root is not owned by Outliner_Model.
        void set_root(Outliner_Item* a_root);

        // Make an index from an item, mostly so that Outliner_Item can make an index of itself without being a friend
        QModelIndex create_index_from_item(Outliner_Item* item) const;

        // call QAbstractItemView->edit on this item
        //void callEditInView(QAbstractItemView* view, Outliner_Item* item);
        //void callEditInView(QAbstractItemView* view, QModelIndex const& index);

    signals:
        void signal_editor_requested(Outliner_Item* a_item);
        void signal_unsaved_edits(bool a_state);


    private:
        // Data Members
        //============================================================
        Outliner_Item* m_root;
    };

} // namespace qtlib

#endif // OUTLINER_MODEL_H
