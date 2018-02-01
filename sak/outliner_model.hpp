#ifndef SAK_OUTLINER_MODEL_HPP
#define SAK_OUTLINER_MODEL_HPP

#ifndef SAK_OUTLINER_MODEL_FWD_HPP
#include "outliner_model_fwd.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#ifndef INCLUDE_QT_QABSTRACTITEMMODEL
#define INCLUDE_QT_QABSTRACTITEMMODEL
#include <QAbstractItemModel>
#endif

class QAbstractItemView;

namespace sak
{
  class Abstract_Outliner_Item;

  //---------------------------------------------------------------------------
  // Outliner_Model
  //---------------------------------------------------------------------------
  // A specialised model with only one column. Create a sublclass of Abstract_Outliner_Item
  // and give it to this class in order to use it. Outliner_Model relies entirely
  // on the public interface of Abstract_Outliner_Item

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
    explicit Outliner_Model(Abstract_Outliner_Item* a_root, QObject* a_parent = nullptr);

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
    Abstract_Outliner_Item* get_root() const;
    // Replace the root item and refresh the model in all views. The old
    // root is not deleted. The new root is not owned by Outliner_Model.
    void set_root(Abstract_Outliner_Item* a_root);

    // Make an index from an item, mostly so that Outliner_Item can make an index of itself without being a friend
    QModelIndex create_index_from_item(Abstract_Outliner_Item* item) const;

    // call QAbstractItemView->edit on this item
    //void callEditInView(QAbstractItemView* view, Outliner_Item* item);
    //void callEditInView(QAbstractItemView* view, QModelIndex const& index);

    // Update Calls
    //============================================================
    // Functions to tell the model to emit change signals

    void data_changed(QModelIndex const& a_top_left, QModelIndex const& a_bottom_right, QVector<int> const& a_roles = QVector<int>());

    // Helper classes
    //============================================================
    // Providing access to these signals without implementing the actions.
    friend class Outliner_Rows_Mover;
    friend class Outliner_Rows_Inserter;
    friend class Outliner_Rows_Remover;

    Outliner_Rows_Mover make_rows_mover(QModelIndex const& a_source_parent, int a_source_row, int a_source_last, QModelIndex const& a_destination_parent, int a_destination_child);
    Outliner_Rows_Inserter make_rows_inserter(int a_row, int a_last, QModelIndex const& a_parent = QModelIndex());
    Outliner_Rows_Remover make_rows_remover(int a_row, int a_last, QModelIndex const& a_parent = QModelIndex());

    Outliner_Rows_Mover make_row_mover(QModelIndex const& a_source_parent, int a_source_row, QModelIndex const& a_destination_parent, int a_destination_child);
    Outliner_Rows_Inserter make_row_inserter(int a_row, QModelIndex const& a_parent = QModelIndex());
    Outliner_Rows_Remover make_row_remover(int a_row, QModelIndex const& a_parent = QModelIndex());


  signals:
    void signal_editor_requested(Abstract_Outliner_Item* a_item);
    void signal_unsaved_edits(bool a_state);


  private:
    // Data Members
    //============================================================
    Abstract_Outliner_Item* m_root;
  };

  // Helper classes
  //============================================================
  // Providing access to these signals without implementing the actions.

  //---------------------------------------------------------------------------
  // Outliner_Rows_Mover
  //---------------------------------------------------------------------------
  class Outliner_Rows_Mover
  {
  private:
    friend class Outliner_Model;
    Outliner_Rows_Mover(Outliner_Model* a_model,
                        QModelIndex const& a_source_parent,
                        int a_source_row,
                        int a_source_last,
                        QModelIndex const& a_destination_parent,
                        int a_destination_child);
  public:
    ~Outliner_Rows_Mover();
  private:
    Outliner_Model* m_model;
  };

  //---------------------------------------------------------------------------
  // Outliner_Rows_Inserter
  //---------------------------------------------------------------------------
  class Outliner_Rows_Inserter
  {
  private:
    friend class Outliner_Model;
    Outliner_Rows_Inserter(Outliner_Model* a_model,
                           int a_row, int a_last,
                           QModelIndex const& a_parent = QModelIndex());
  public:
    ~Outliner_Rows_Inserter();
  private:
    Outliner_Model* m_model;
  };

  //---------------------------------------------------------------------------
  // Outliner_Rows_Remover
  //---------------------------------------------------------------------------
  class Outliner_Rows_Remover
  {
  private:
    friend class Outliner_Model;
    Outliner_Rows_Remover(Outliner_Model* a_model,
                          int a_row,
                          int a_last,
                          QModelIndex const& a_parent = QModelIndex());
  public:
    ~Outliner_Rows_Remover();
  private:
      Outliner_Model* m_model;
  };
} // namespace sak


#endif // SAK_OUTLINER_MODEL_HPP
