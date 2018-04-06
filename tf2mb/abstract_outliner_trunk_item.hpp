#ifndef SAK_ABSTRACT_OUTLINER_TRUNK_ITEM_HPP
#define SAK_ABSTRACT_OUTLINER_TRUNK_ITEM_HPP

#ifndef SAK_ABSTRACT_OUTLINER_TRUNK_ITEM_FWD_HPP
#include "abstract_outliner_trunk_item_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_OUTLINER_PARENTED_ITEM_HPP
#include "abstract_outliner_parented_item.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

namespace sak
{
  namespace internal
  {
    //---------------------------------------------------------------------------
    // internal::Outliner_Trunk_Item_Implementation<Child>
    //---------------------------------------------------------------------------
    // Seperating out the implementation so that the inheritance is simpler and
    // shared details are in one place.

    template <typename T_Child_Item>
    class Outliner_Trunk_Item_Implementation
    {
    public:
      using Child_Item_Type = T_Child_Item;

      // Special 6
      //============================================================
      Outliner_Trunk_Item_Implementation();
      ~Outliner_Trunk_Item_Implementation();

      // Interface
      //============================================================
      // Children
      //----------------------------------------
      // Does this item have any child items?
      bool has_children() const;
      // The number of children this item has
      int get_child_count() const;
      // Does this item have a child item at this index?
      bool has_child_at(int a_index) const;
      // Get the child at a given row, return nullptr if there is no child at row
      Abstract_Outliner_Item* get_child_at(int a_index) const;

      Child_Item_Type* get_true_child() const;
      void set_true_child(std::unique_ptr<Child_Item_Type>&& a_item);

    private:
        std::unique_ptr<Child_Item_Type> m_child;
    };
  }

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Outliner_Trunk_Item<Parent, Child>
  //---------------------------------------------------------------------------
  // Subclass of Abstract_Outliner_Item which is in the middle of the tree. It has a
  // single parent and a single child that may or may not be present. Trunk_Item
  // may have differenct distinct types for the parent and child, so long as they
  // are both subclasses of Abstract_Outliner_Item.

  template <typename T_Parent_Item, typename T_Child_Item>
  class Abstract_Outliner_Trunk_Item :
          public Abstract_Outliner_Parented_Item<T_Parent_Item>
  {
  public:
    //using Parent_Item_Type = typename Abstract_Outliner_Parented_Item<T_Parent_Item>::Parent_Item_Type;
    using Child_Item_Type = T_Child_Item;

    // Special 6
    //============================================================
    explicit Abstract_Outliner_Trunk_Item(Parent_Item_Type* a_parent);
    ~Abstract_Outliner_Trunk_Item() override;

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
    // actions can call functions in it for editing.  Position is the position in terms of
    // the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
    // to get the position relative to the window for a properly placed menu.
    void do_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) override = 0;
    // Do whatever we want when an item has been double clicked on.
    void do_double_clicked(QAbstractItemView* a_view, Outliner_Model* a_model) override = 0;

    //protected:
    // Additional Interface
    //============================================================
    using Abstract_Outliner_Parented_Item<T_Parent_Item>::get_true_parent;
    using Abstract_Outliner_Parented_Item<T_Parent_Item>::set_parent;

    Child_Item_Type* get_true_child() const;
    void set_true_child(std::unique_ptr<Child_Item_Type>&& a_item);

  private:
    //std::unique_ptr<Child_Item_Type> m_child;
    internal::Outliner_Trunk_Item_Implementation<Child_Item_Type> m_data;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Outliner_Readonly_Trunk_Item<Parent, Child>
  //---------------------------------------------------------------------------
  // Subclass of Trunk_Item<Parent, Child> with the write interface
  // implemented as dummy functions. This exists to solve multiple inheritance
  // problems if you want to use features together.

  template <typename T_Parent_Item, typename T_Child_Item>
  class Abstract_Outliner_Readonly_Trunk_Item :
      public Abstract_Outliner_Readonly_Parented_Item<T_Parent_Item>
  {
  public:
    //using Parent_Item_Type = typename Trunk_Item<P,C>::Parent_Item_Type;
    using Child_Item_Type = T_Child_Item;

    // Special 6
    //============================================================
    explicit Abstract_Outliner_Readonly_Trunk_Item(Parent_Item_Type* a_parent);
    ~Abstract_Outliner_Readonly_Trunk_Item() override;

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
    using Abstract_Outliner_Readonly_Parented_Item<T_Parent_Item>::get_true_parent;
    using Abstract_Outliner_Readonly_Parented_Item<T_Parent_Item>::set_parent;

    Child_Item_Type* get_true_child() const;
    void set_true_child(std::unique_ptr<Child_Item_Type>&& a_item);

  private:
    internal::Outliner_Trunk_Item_Implementation<Child_Item_Type> m_data;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // outliner::Root_Trunk_Item<Child>
  //---------------------------------------------------------------------------
  // Subclass of abstract::Root_Item to give the implementation of a root item
  // with 0 or 1 child of a given type.

  template <typename T_Child_Item>
  class Abstract_Outliner_Root_Trunk_Item :
      public Abstract_Outliner_Root_Item
  {
  public:
    using Child_Item_Type = T_Child_Item;

    //static_assert(std::is_base_of<Abstract_Outliner_Item, Child_Item_Type>::value, "Child_Item_Type must inherit qtlib::outliner::Abstract_Outliner_Item");

    // Special 6
    //============================================================
    Abstract_Outliner_Root_Trunk_Item();
    ~Abstract_Outliner_Root_Trunk_Item() override;

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

    // Other
    //----------------------------------------
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
    Child_Item_Type* get_true_child() const;
    void set_true_child(std::unique_ptr<Child_Item_Type>&& a_item);
  private:
    internal::Outliner_Trunk_Item_Implementation<Child_Item_Type> m_data;
  };
} // namespace sak

//------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------
// internal::Outliner_Trunk_Item_Implementation<Child>
//---------------------------------------------------------------------------
// Seperating out the implementation so that the inheritance is simpler and
// shared details are in one place.


// Special 6
//============================================================
template <typename C>
sak::internal::Outliner_Trunk_Item_Implementation<C>::Outliner_Trunk_Item_Implementation():
  m_child{}
{}

template <typename C>
sak::internal::Outliner_Trunk_Item_Implementation<C>::~Outliner_Trunk_Item_Implementation() = default;

// Virtual Interface
//============================================================
// Does this item have any child items?
template <typename C>
bool sak::internal::Outliner_Trunk_Item_Implementation<C>::has_children() const
{
  return m_child != nullptr;
}
// The number of children this item has
template <typename C>
int sak::internal::Outliner_Trunk_Item_Implementation<C>::get_child_count() const
{
  return (m_child == nullptr ? 0 : 1);
}

// Does this item have a child item at this index?
template <typename C>
bool sak::internal::Outliner_Trunk_Item_Implementation<C>::has_child_at(int a_index) const
{
    return a_index == 0 && m_child != nullptr;
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename C>
sak::Abstract_Outliner_Item* sak::internal::Outliner_Trunk_Item_Implementation<C>::get_child_at(int a_index) const
{
  if( m_child != nullptr && a_index == 0 )
  {
    return m_child.get();
  }
  else
  {
    return nullptr;
  }
}

// Additional Interface
//============================================================
template <typename C>
typename sak::internal::Outliner_Trunk_Item_Implementation<C>::Child_Item_Type* sak::internal::Outliner_Trunk_Item_Implementation<C>::get_true_child() const
{
  return m_child.get();
}
template <typename C>
void sak::internal::Outliner_Trunk_Item_Implementation<C>::set_true_child(std::unique_ptr<Child_Item_Type>&& a_item)
{
  m_child = std::move(a_item);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Outliner_Trunk_Item<Parent, Child>
//---------------------------------------------------------------------------
// Subclass of Abstract_Outliner_Item which is in the middle of the tree. It has a
// single parent and a single child that may or may not be present. Trunk_Item
// may have differenct distinct types for the parent and child, so long as they
// are both subclasses of Abstract_Outliner_Item.

// Special 6
//============================================================
template <typename P, typename C>
sak::Abstract_Outliner_Trunk_Item<P,C>::Abstract_Outliner_Trunk_Item(Parent_Item_Type* a_parent):
  Abstract_Outliner_Parented_Item<P>(a_parent),
  m_data{}
{}

template <typename P, typename C>
sak::Abstract_Outliner_Trunk_Item<P,C>::~Abstract_Outliner_Trunk_Item() = default;

// Virtual Interface
//============================================================
// Children
//----------------------------------------
// Does this item have any child items?
template <typename P, typename C>
bool sak::Abstract_Outliner_Trunk_Item<P,C>::has_children() const
{
  return m_data.has_children();
}
// The number of children this item has
template <typename P, typename C>
int sak::Abstract_Outliner_Trunk_Item<P,C>::get_child_count() const
{
  return m_data.get_child_count();
}

// Does this item have a child item at this index?
template <typename P, typename C>
bool sak::Abstract_Outliner_Trunk_Item<P,C>::has_child_at(int a_index) const
{
  return m_data.has_child_at(a_index);
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename P, typename C>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Trunk_Item<P,C>::get_child_at(int a_index) const
{
  return m_data.get_child_at(a_index);
}

// Additional Interface
//============================================================
template <typename P, typename C>
typename sak::Abstract_Outliner_Trunk_Item<P,C>::Child_Item_Type* sak::Abstract_Outliner_Trunk_Item<P,C>::get_true_child() const
{
  return m_data.get_true_child();
}
template <typename P, typename C>
void sak::Abstract_Outliner_Trunk_Item<P,C>::set_true_child(std::unique_ptr<Child_Item_Type>&& a_item)
{
  m_data.set_true_child(std::move(a_item));
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// outliner::Readonly_Trunk_Item<Parent, Child>
//---------------------------------------------------------------------------
// Subclass of Trunk_Item<Parent, Child> with the write interface
// implemented as dummy functions. This exists to solve multiple inheritance
// problems if you want to use features together.

// Special 6
//============================================================
template <typename P, typename C>
sak::Abstract_Outliner_Readonly_Trunk_Item<P,C>::Abstract_Outliner_Readonly_Trunk_Item(Parent_Item_Type* a_parent):
  Abstract_Outliner_Trunk_Item<P,C>(a_parent)
{}

template <typename P, typename C>
sak::Abstract_Outliner_Readonly_Trunk_Item<P,C>::~Abstract_Outliner_Readonly_Trunk_Item() = default;

// Virtual Interface
//============================================================
// Children
//----------------------------------------
// Does this item have any child items?
template <typename P, typename C>
bool sak::Abstract_Outliner_Readonly_Trunk_Item<P,C>::has_children() const
{
  return m_data.has_children();
}
// The number of children this item has
template <typename P, typename C>
int sak::Abstract_Outliner_Readonly_Trunk_Item<P,C>::get_child_count() const
{
  return m_data.get_child_count();
}

// Does this item have a child item at this index?
template <typename P, typename C>
bool sak::Abstract_Outliner_Readonly_Trunk_Item<P,C>::has_child_at(int a_index) const
{
  return m_data.has_child_at(a_index);
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename P, typename C>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Readonly_Trunk_Item<P,C>::get_child_at(int a_index) const
{
  return m_data.get_child_at(a_index);
}

// Additional Interface
//============================================================
template <typename P, typename C>
typename sak::Abstract_Outliner_Readonly_Trunk_Item<P,C>::Child_Item_Type* sak::Abstract_Outliner_Readonly_Trunk_Item<P,C>::get_true_child() const
{
  return m_data.get_true_child();
}
template <typename P, typename C>
void sak::Abstract_Outliner_Readonly_Trunk_Item<P,C>::set_true_child(std::unique_ptr<Child_Item_Type>&& a_item)
{
  m_data.set_true_child(std::move(a_item));
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// outliner::Root_Trunk_Item<Parent, Child>
//---------------------------------------------------------------------------
// Subclass of Abstract_Outliner_Item which is in the middle of the tree. It has a
// single parent and a single child that may or may not be present. Root_Trunk_Item
// may have differenct distinct types for the parent and child, so long as they
// are both subclasses of Abstract_Outliner_Item.

// Special 6
//============================================================
template <typename C>
sak::Abstract_Outliner_Root_Trunk_Item<C>::Abstract_Outliner_Root_Trunk_Item():
  Abstract_Outliner_Root_Item(),
  m_data{}
{}

template <typename C>
sak::Abstract_Outliner_Root_Trunk_Item<C>::~Abstract_Outliner_Root_Trunk_Item() = default;

// Virtual Interface
//============================================================
// Does this item have any child items?
template <typename C>
bool sak::Abstract_Outliner_Root_Trunk_Item<C>::has_children() const
{
  return m_data.has_children();
}
// The number of children this item has
template <typename C>
int sak::Abstract_Outliner_Root_Trunk_Item<C>::get_child_count() const
{
  return m_data.get_child_count();
}

// Does this item have a child item at this index?
template <typename C>
bool sak::Abstract_Outliner_Root_Trunk_Item<C>::has_child_at(int a_index) const
{
  return m_data.has_child_at(a_index);
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename C>
typename sak::Abstract_Outliner_Root_Trunk_Item<C>::Abstract_Outliner_Item* sak::Abstract_Outliner_Root_Trunk_Item<C>::get_child_at(int a_index) const
{
  return m_data.get_child_at(a_index);
}

// Additional Interface
//============================================================
template <typename C>
typename sak::Abstract_Outliner_Root_Trunk_Item<C>::Child_Item_Type* sak::Abstract_Outliner_Root_Trunk_Item<C>::get_true_child() const
{
  return m_data.get_true_child();
}
template <typename C>
void sak::Abstract_Outliner_Root_Trunk_Item<C>::set_true_child(std::unique_ptr<Child_Item_Type>&& a_item)
{
  m_data.set_true_child(std::move(a_item));
}

#endif // SAK_ABSTRACT_OUTLINER_TRUNK_ITEM_HPP
