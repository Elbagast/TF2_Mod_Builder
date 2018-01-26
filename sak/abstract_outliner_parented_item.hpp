#ifndef SAK_ABSTRACT_OUTLINER_PARENTED_ITEM_HPP
#define SAK_ABSTRACT_OUTLINER_PARENTED_ITEM_HPP

#ifndef SAK_ABSTRACT_OUTLINER_PARENTED_ITEM_FWD_HPP
#include "abstract_outliner_parented_item_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_OUTLINER_ITEM_HPP
#include "abstract_outliner_item.hpp"
#endif

#ifndef INCLUDE_QT_QVARIANT
#define INCLUDE_QT_QVARIANT
#include <QVariant>
#endif

//#include <type_traits>

namespace sak
{
  //---------------------------------------------------------------------------
  // Abstract_Outliner_Parented_Item<Parent>
  //---------------------------------------------------------------------------
  // Subclass of Abstract_Outliner_Item which implements the item having a parent of
  // a distinct item type.

  template <typename T_Parent_Item>
  class Abstract_Outliner_Parented_Item :
      public Abstract_Outliner_Item
  {
  public:
    using Parent_Item_Type = T_Parent_Item;

    //static_assert(std::is_base_of<Abstract_Outliner_Item, Parent_Item_Type>::value, "Parent_Item_Type must inherit qtlib::outliner::Abstract_Outliner_Item");

    // Special 6
    //============================================================
    explicit Abstract_Outliner_Parented_Item(Parent_Item_Type* a_parent);
    ~Abstract_Outliner_Parented_Item() override;

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
    // Get the flags for this item
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
    Parent_Item_Type* get_true_parent() const;

    void set_parent(Parent_Item_Type* a_parent);
  private:
    Parent_Item_Type* m_parent;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Outliner_Leaf_Item<Parent>
  //---------------------------------------------------------------------------
  // Subclass of Abstract_Outliner_Item which is at the end of a tree (i.e. it never
  // has any children).

  template <typename T_Parent_Item>
  class Abstract_Outliner_Leaf_Item :
      public Abstract_Outliner_Parented_Item<T_Parent_Item>
  {
  public:
    //using Abstract_Outliner_Parented_Item<P>::Parent_Item_Type;

    //static_assert(std::is_base_of<Abstract_Outliner_Item, Parent_Item_Type>::value, "Parent_Item_Type must inherit qtlib::outliner::Abstract_Outliner_Item");

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
    // Get the flags for this item
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
    using Abstract_Outliner_Parented_Item<T_Parent_Item>::set_parent;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Readonly_Leaf_Item<Parent>
  //---------------------------------------------------------------------------
  // Subclass of Leaf_Item<Parent> with the write interface implemented as
  // dummy functions. This exists to solve multiple inheritance problems if
  // you want to use features together.

  template <typename T_Parent_Item>
  class Abstract_Outliner_Readonly_Leaf_Item :
          public Abstract_Outliner_Leaf_Item<T_Parent_Item>
  {
  public:
    // Special 6
    //============================================================
    explicit Abstract_Outliner_Readonly_Leaf_Item(Parent_Item_Type* a_parent);
    ~Abstract_Outliner_Readonly_Leaf_Item() override;

    // Virtual Interface
    //============================================================
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
    // Get the flags for this item
    Qt::ItemFlags get_flags() const override final;
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
    using Abstract_Outliner_Leaf_Item<T_Parent_Item>::get_true_parent;
    using Abstract_Outliner_Leaf_Item<T_Parent_Item>::set_parent;
  };



} // namespace sak


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Outliner_Parented_Item<Parent>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename P>
sak::Abstract_Outliner_Parented_Item<P>::Abstract_Outliner_Parented_Item(Parent_Item_Type* a_parent):
    m_parent{a_parent}
{}

template <typename P>
sak::Abstract_Outliner_Parented_Item<P>::~Abstract_Outliner_Parented_Item() = default;

// Virtual Interface
//============================================================
// Parent
//----------------------------------------
// Does this item have a parent item?
template <typename P>
bool sak::Abstract_Outliner_Parented_Item<P>::has_parent() const
{
  return m_parent != nullptr;
}
// Get the item that is the parent of this
template <typename P>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Parented_Item<P>::get_parent() const
{
  return m_parent;
}
// Get the item at the root of the structure
template <typename P>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Parented_Item<P>::get_root() const
{
  if (has_parent())
  {
    return m_parent->get_root();
  }
  else
  {
    return nullptr;
  }
}

// The row that this item is in relative to the parent e.g. if the parent has
// 5 children, and this is the third, then row is 2. If this has no parent
// then -1 is returned.
template <typename P>
int sak::Abstract_Outliner_Parented_Item<P>::index_in_parent() const
{
  if (m_parent != nullptr)
  {
    for (int l_index = 0, l_end = m_parent->get_child_count(); l_index != l_end; ++l_index)
    {
      if (m_parent->get_child_at(l_index) == this)
      {
        return l_index;
      }
    }
  }

  return -1;
}

// Additional Interface
//============================================================
template <typename P>
typename sak::Abstract_Outliner_Parented_Item<P>::Parent_Item_Type* sak::Abstract_Outliner_Parented_Item<P>::get_true_parent() const
{
  return m_parent;
}
template <typename P>
void sak::Abstract_Outliner_Parented_Item<P>::set_parent(Parent_Item_Type* a_parent)
{
  m_parent = a_parent;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Outliner_Leaf_Item<Parent>
//---------------------------------------------------------------------------
// Subclass of Abstract_Outliner_Item which is at the end of a tree (i.e. it never
// has any children).

// Special 6
//============================================================
template <typename P>
sak::Abstract_Outliner_Leaf_Item<P>::Abstract_Outliner_Leaf_Item(Parent_Item_Type* a_parent):
    Abstract_Outliner_Parented_Item<P>(a_parent)
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
// Subclass of Abstract_Outliner_Leaf_Item<Parent> with the write interface implemented as
// dummy functions. This exists to solve multiple inheritance problems if
// you want to use features together.

// Special 6
//============================================================
template <typename P>
sak::Abstract_Outliner_Readonly_Leaf_Item<P>::Abstract_Outliner_Readonly_Leaf_Item(Parent_Item_Type* a_parent):
    Abstract_Outliner_Item<P>(a_parent)
{}

template <typename P>
sak::Abstract_Outliner_Readonly_Leaf_Item<P>::~Abstract_Outliner_Readonly_Leaf_Item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Set the data in item with the given value
template <typename P>
void sak::Abstract_Outliner_Readonly_Leaf_Item<P>::set_data(QVariant const& a_value)
{
  this->Abstract_Outliner_Item::set_data(a_value);
}

// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
template <typename P>
QWidget* sak::Abstract_Outliner_Readonly_Leaf_Item<P>::get_editor(QWidget* a_parent)
{
  return this->Abstract_Outliner_Item::get_editor(a_parent);
}
// Set the data in the editor to the value in the item
template <typename P>
void sak::Abstract_Outliner_Readonly_Leaf_Item<P>::set_editor_data(QWidget* a_editor)
{
  this->Abstract_Outliner_Item::set_editor_data(a_editor);
}
// Get the data in the editor and return it
template <typename P>
QVariant sak::Abstract_Outliner_Readonly_Leaf_Item<P>::get_editor_data(QWidget* a_editor)
{
  return this->Abstract_Outliner_Item::get_editor_data(a_editor);
}

// Other
//----------------------------------------
// Get the flags for this item
template <typename P>
Qt::ItemFlags sak::Abstract_Outliner_Readonly_Leaf_Item<P>::get_flags() const
{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

#endif // SAK_ABSTRACT_OUTLINER_PARENTED_ITEM_HPP
