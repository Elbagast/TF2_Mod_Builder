#ifndef SAK_ABSTRACT_OUTLINER_ITEM_HPP
#define SAK_ABSTRACT_OUTLINER_ITEM_HPP

#ifndef SAK_ABSTRACT_OUTLINER_ITEM_FWD_HPP
#include "abstract_outliner_item_fwd.hpp"
#endif

#ifndef SAK_OUTLINER_MODEL_FWD_HPP
#include "outliner_model_fwd.hpp"
#endif

#ifndef INCLUDE_QT_QT
#define INCLUDE_QT_QT
#include <Qt> // for Qt::ItemFlags
#endif

class QPoint;
class QVariant;
class QWidget;
class QModelIndex;
class QAbstractItemView;

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Outliner_Item
  //---------------------------------------------------------------------------
  // Defines the interface used by Outliner_Model, Outliner_delegate and
  // Outliner_View_Widget. There is only ever one column.
  // Subclass this and create a tree item subclasses.

  class Abstract_Outliner_Item
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Outliner_Item() = 0;

    // Virtual Interface
    //============================================================
    // Parent
    //----------------------------------------
    // Does this item have a parent item?
    virtual bool has_parent() const = 0;
    // Get the item that is the parent of this
    virtual Abstract_Outliner_Item* get_parent() const = 0;
    // Get the item at the root of the structure
    virtual Abstract_Outliner_Item* get_root() const = 0;
    // The row that this item is in relative to the parent e.g. if the parent has
    // 5 children, and this is the third, then row is 2. If this has no parent
    // then -1 is returned.
    virtual int index_in_parent() const = 0;

    // Children
    //----------------------------------------
    // Does this item have any child items?
    virtual bool has_children() const = 0;
    // The number of child items this item has
    virtual int get_child_count() const = 0;
    // Does this item have a child item at this index?
    virtual bool has_child_at(int a_index) const = 0;
    // Get the child at a given row, return nullptr if there is no child at the index
    virtual Abstract_Outliner_Item* get_child_at(int a_index) const = 0;

    // Underlying data access
    //----------------------------------------
    // Get the item data for a given column and role
    virtual QVariant get_data(int a_role = Qt::DisplayRole) const = 0;
    // Set the data in item with the given value
    virtual void set_data(QVariant const& a_value) = 0;

    // Editors
    //----------------------------------------
    // Make the appropriate editor for this item, parenting it to parent
    virtual QWidget* get_editor(QWidget* a_parent) = 0;
    // Set the data in the editor to the value in the item
    virtual void set_editor_data(QWidget* a_editor) = 0;
    // Get the data in the editor and return it
    virtual  QVariant get_editor_data(QWidget* a_editor) = 0;

    // Other
    //----------------------------------------
    // Get the flags for this item
    virtual Qt::ItemFlags get_flags() const = 0;
    // Make and act on the context menu for this item. Need the model pointer here so that
    // actions can call functions in it for editing.  Position is the position in terms of
    // the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
    // to get the position relative to the window for a properly placed menu.
    virtual void do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) = 0;
    // Do whatever we want when an item has been double clicked on.
    virtual void do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model) = 0;

    // Encapsulate the casting of the void* stored in index to Item*
    static Abstract_Outliner_Item* from_index(QModelIndex const& a_index);
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Outliner_Readonly_Item
  //---------------------------------------------------------------------------
  // Abstract subclass of Abstract_Outliner_Item. Subclass from this for items that will
  // not be editable inside the outliner. Write functions are finalised with
  // dummy implemenations.

  class Abstract_Outliner_Readonly_Item :
      public Abstract_Outliner_Item
  {
  public:
    // Special 6
    //============================================================
    ~Abstract_Outliner_Readonly_Item() override = 0;

    // Virtual Interface
    //============================================================
    // Parent
    //----------------------------------------
    // Does this item have a parent item?
    bool has_parent() const override = 0;
    // Get the item that is the parent of this
    Abstract_Outliner_Item* get_parent() const override = 0;
    // Get the item at the root of the structure
    Abstract_Outliner_Item* get_root() const override = 0;
    // The row that this item is in relative to the parent e.g. if the parent has
    // 5 children, and this is the third, then row is 2. If this has no parent
    // then -1 is returned.
    int index_in_parent() const override = 0;

    // Children
    //----------------------------------------
    // Does this item have any child items?
    bool has_children() const override = 0;
    // The number of children this item has
    int get_child_count() const override = 0;
    // Does this item have a child item at this index?
    bool has_child_at(int a_index) const override = 0;
    // Get the child at a given row, return nullptr if there is no child at row
    Abstract_Outliner_Item* get_child_at(int a_index) const override = 0;

    // Underlying data access
    //----------------------------------------
    // Get the item data for a given column and role
    QVariant get_data(int a_role = Qt::DisplayRole) const override = 0;
    // Set the data in item with the given value
    void set_data(QVariant const& a_value) override final;

    // Editors
    //----------------------------------------
    // Make the appropriate editor for this item, parenting it to parent
    QWidget* get_editor(QWidget* a_parent) override final;
    // Set the data in the editor to the value in the item
    void set_editor_data(QWidget* a_editor) override final;
    // Get the data in the editor and return it
    QVariant get_editor_data(QWidget* a_editor) override final;

    // Other
    //----------------------------------------
    // Get the flags for this item. Do not use the flag Qt::ItemIsEditable when
    // inheriting from this class because you will not be able to edit the data.
    Qt::ItemFlags get_flags() const override = 0;
    // Make and act on the context menu for this item. Need the model pointer here so that
    // actions can call functions in it for editing.  Position is the position in terms of
    // the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
    // to get the position relative to the window for a properly placed menu.
    void do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) override = 0;
    // Do whatever we want when an item has been double clicked on.
    void do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model) override = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Outliner_Root_Item
  //---------------------------------------------------------------------------
  // Abstract subclass of Abstract_Outliner_Item. Subclass from this for your root
  // (invisible) object in an outliner item tree. Functions that are part of
  // the Abstract_Outliner_Item interface that will not be called on the root item
  // are finalised with do-nothing implementations. Your implementation of
  // do_custom_context_menu is what will be carried out in the view if one is
  // requested where no item is present.

  class Abstract_Outliner_Root_Item :
      public Abstract_Outliner_Item
  {
  public:
    // Special 6
    //============================================================
    ~Abstract_Outliner_Root_Item() override = 0;

    // Virtual Interface
    //============================================================
    // Parent
    //----------------------------------------
    // Does this item have a parent item?
    bool has_parent() const override final;
    // Get the item that is the parent of this
    Abstract_Outliner_Item* get_parent() const override final;
    // Get the item at the root of the structure
    Abstract_Outliner_Item* get_root() const override final;
    // The row that this item is in relative to the parent e.g. if the parent has
    // 5 children, and this is the third, then row is 2. If this has no parent
    // then -1 is returned.
    int index_in_parent() const override final;

    // Children
    //----------------------------------------
    // Does this item have any child items?
    bool has_children() const override = 0;
    // The number of children this item has
    int get_child_count() const override = 0;
    // Does this item have a child item at this index?
    bool has_child_at(int a_index) const override = 0;
    // Get the child at a given row, return nullptr if there is no child at row
    Abstract_Outliner_Item* get_child_at(int a_row) const override = 0;

    // Underlying data access
    //----------------------------------------
    // Get the item data for a given column and role
    QVariant get_data(int a_role = Qt::DisplayRole) const override final;
    // Set the data in item with the given value
    void set_data(QVariant const& a_value) override final;

    // Editors
    //----------------------------------------
    // Make the appropriate editor for this item, parenting it to parent
    QWidget* get_editor(QWidget* a_parent) override final;
    // Set the data in the editor to the value in the item
    void set_editor_data(QWidget* a_editor) override final;
    // Get the data in the editor and return it
    QVariant get_editor_data(QWidget* a_editor) override final;

    // Other
    //----------------------------------------
    // Get the flags for this item
    Qt::ItemFlags get_flags() const override final;
    // Make and act on the context menu for this item. Need the model pointer here so that
    // actions can call functions in it for editing.  Position is the position in terms of
    // the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
    // to get the position relative to the window for a properly placed menu.
    void do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) override = 0;
    // Do whatever we want when an item has been double clicked on.
    void do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model) override = 0;
  };

} // namespace sak

#endif // SAK_ABSTRACT_OUTLINER_ITEM_HPP
