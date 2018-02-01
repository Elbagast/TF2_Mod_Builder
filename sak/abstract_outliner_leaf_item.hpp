#ifndef SAK_ABSTRACT_OUTLINER_LEAF_ITEM_HPP
#define SAK_ABSTRACT_OUTLINER_LEAF_ITEM_HPP

#ifndef SAK_ABSTRACT_OUTLINER_LEAF_ITEM_FWD_HPP
#include "abstract_outliner_leaf_item_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_OUTLINER_PARENTED_ITEM_HPP
#include "abstract_outliner_parented_item.hpp"
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Outliner_Leaf_Item<Parent>
  //---------------------------------------------------------------------------

  template <typename T_Parent_Item>
  class Abstract_Outliner_Leaf_Item :
      public Abstract_Outliner_Parented_Item<T_Parent_Item>
  {
  public:
    // Special 6
    //============================================================
    explicit Abstract_Outliner_Leaf_Item(Parent_Item_Type* a_parent);
    ~Abstract_Outliner_Leaf_Item() override;

    // Virtual Interface
    //============================================================
    // Children
    //----------------------------------------
    // Does this item have any child items?
    bool has_children() const override final;
    // The number of children this item has
    int get_child_count() const override final;
    // Does this item have a child item at this index?
    bool has_child_at(int a_index) const override final;
    // Get the child at a given row, return nullptr if there is no child at row
    Abstract_Outliner_Item* get_child_at(int a_index) const override final;

    // Underlying data access
    //----------------------------------------
    // Get the item data for a given column and role
    QVariant get_data(int a_role = Qt::DisplayRole) const override = 0;
    // Set the data in item with the given value
    void set_data(QVariant const& a_value) override = 0;

    // Editors
    //----------------------------------------
    // Make the appropriate editor for this item, parenting it to parent
    QWidget* get_editor(QWidget* a_parent) override = 0;
    // Set the data in the editor to the value in the item
    void set_editor_data(QWidget* a_editor) override = 0;
    // Get the data in the editor and return it
    QVariant get_editor_data(QWidget* a_editor) override = 0;

    // Other
    //----------------------------------------
    // Get the flags for this item. This item never has children so include
    // Qt::ItemNeverHasChildren.
    Qt::ItemFlags get_flags() const override = 0;
    // Make and act on the context menu for this item. Need the model pointer here so that
    // actions can call functions in it for editing
    void do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) override = 0;
    // Do whatever we want when an item has been double clicked on.
    void do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model) override = 0;

  //protected:
    // Additional Interface
    //============================================================
    using Abstract_Outliner_Parented_Item<T_Parent_Item>::get_true_parent;
    using Abstract_Outliner_Parented_Item<T_Parent_Item>::set_true_parent;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Readonly_Leaf_Item<Parent>
  //---------------------------------------------------------------------------

  template <typename T_Parent_Item>
  class Abstract_Outliner_Readonly_Leaf_Item :
      public Abstract_Outliner_Readonly_Parented_Item<T_Parent_Item>
  {
  public:
    // Special 6
    //============================================================
    explicit Abstract_Outliner_Readonly_Leaf_Item(Parent_Item_Type* a_parent);
    ~Abstract_Outliner_Readonly_Leaf_Item() override;

    // Virtual Interface
    //============================================================
    // Children
    //----------------------------------------
    // Does this item have any child items?
    bool has_children() const override final;
    // The number of children this item has
    int get_child_count() const override final;
    // Does this item have a child item at this index?
    bool has_child_at(int a_index) const override final;
    // Get the child at a given row, return nullptr if there is no child at row
    Abstract_Outliner_Item* get_child_at(int a_index) const override final;

    // Underlying data access
    //----------------------------------------
    // Get the item data for a given column and role
    QVariant get_data(int a_role = Qt::DisplayRole) const override = 0;

    // Other
    //----------------------------------------
    // Get the flags for this item. This item never has children so include
    // Qt::ItemNeverHasChildren.
    Qt::ItemFlags get_flags() const override = 0;
    // Make and act on the context menu for this item. Need the model pointer here so that
    // actions can call functions in it for editing.  Position is the position in terms of
    // the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
    // to get the position relative to the window for a properly placed menu.
    void do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) override = 0;
    // Do whatever we want when an item has been double clicked on.
    void do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model) override = 0;

  //protected:
    // Additional Interface
    //============================================================
    using Abstract_Outliner_Readonly_Parented_Item<T_Parent_Item>::get_true_parent;
    using Abstract_Outliner_Readonly_Parented_Item<T_Parent_Item>::set_true_parent;
  };

} // namespace sak

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Outliner_Leaf_Item<Parent>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename P>
sak::Abstract_Outliner_Leaf_Item<P>::Abstract_Outliner_Leaf_Item(Parent_Item_Type* a_parent):
    Abstract_Outliner_Parented_Item(a_parent)
{}

template <typename P>
sak::Abstract_Outliner_Leaf_Item<P>::~Abstract_Outliner_Leaf_Item() = default;

// Virtual Interface
//============================================================
// Children
//----------------------------------------
// Does this item have any child items?
template <typename P>
bool sak::Abstract_Outliner_Leaf_Item<P>::has_children() const
{
  return false;
}

// The number of children this item has
template <typename P>
int sak::Abstract_Outliner_Leaf_Item<P>::get_child_count() const
{
  return 0;
}

// Does this item have a child item at this index?
template <typename P>
bool sak::Abstract_Outliner_Leaf_Item<P>::has_child_at(int /*a_index*/) const
{
  return false;
}

// Get the child at a given row, return nullptr if there is no child at row
template <typename P>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Leaf_Item<P>::get_child_at(int /*a_index*/) const
{
  return nullptr;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Outliner_Readonly_Leaf_Item<Parent>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename P>
sak::Abstract_Outliner_Readonly_Leaf_Item<P>::Abstract_Outliner_Readonly_Leaf_Item(Parent_Item_Type* a_parent):
    Abstract_Outliner_Readonly_Parented_Item(a_parent)
{}

template <typename P>
sak::Abstract_Outliner_Readonly_Leaf_Item<P>::~Abstract_Outliner_Readonly_Leaf_Item() = default;

// Virtual Interface
//============================================================
// Children
//----------------------------------------
// Does this item have any child items?
template <typename P>
bool sak::Abstract_Outliner_Readonly_Leaf_Item<P>::has_children() const
{
  return false;
}

// The number of children this item has
template <typename P>
int sak::Abstract_Outliner_Readonly_Leaf_Item<P>::get_child_count() const
{
  return 0;
}

// Does this item have a child item at this index?
template <typename P>
bool sak::Abstract_Outliner_Readonly_Leaf_Item<P>::has_child_at(int /*a_index*/) const
{
  return false;
}

// Get the child at a given row, return nullptr if there is no child at row
template <typename P>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Readonly_Leaf_Item<P>::get_child_at(int /*a_index*/) const
{
  return nullptr;
}


#endif // SAK_ABSTRACT_OUTLINER_LEAF_ITEM_HPP
