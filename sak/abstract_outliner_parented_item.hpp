#ifndef SAK_ABSTRACT_OUTLINER_PARENTED_ITEM_HPP
#define SAK_ABSTRACT_OUTLINER_PARENTED_ITEM_HPP

#ifndef SAK_ABSTRACT_OUTLINER_PARENTED_ITEM_FWD_HPP
#include "abstract_outliner_parented_item_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_OUTLINER_ITEM_HPP
#include "abstract_outliner_item.hpp"
#endif

namespace sak
{
  namespace internal
  {
    //---------------------------------------------------------------------------
    // internal::Outliner_Parented_Item_Implementation<T_Parent_Item>
    //---------------------------------------------------------------------------
    // Seperating out the implementation so that the inheritance is simpler and
    // shared details are in one place.

    template <typename T_Parent_Item>
    class Outliner_Parented_Item_Implementation
    {
    public:
      using Parent_Item_Type = T_Parent_Item;

      // Special 6
      //============================================================
      explicit Outliner_Parented_Item_Implementation(Parent_Item_Type* a_parent);
      ~Outliner_Parented_Item_Implementation();

      // Interface
      //============================================================
      // Does this item have a parent item?
      bool has_parent() const;
      // Get the item that is the parent of this
      Abstract_Outliner_Item* get_parent() const;
      // Get the item at the root of the structure
      Abstract_Outliner_Item* get_root() const;
      // The row that this item is in relative to the parent e.g. if the parent has
      // 5 children, and this is the third, then row is 2. If this has no parent
      // then -1 is returned.
      int index_in_parent(Abstract_Outliner_Item const* a_item) const;
      Abstract_Outliner_Item* get_child_at(int a_index) const;

      Parent_Item_Type* get_true_parent() const;
      void set_true_parent(Parent_Item_Type* a_parent);

    private:
      Parent_Item_Type* m_parent;
    };
  }

  //---------------------------------------------------------------------------
  // Abstract_Outliner_Parented_Item<Parent>
  //---------------------------------------------------------------------------

  template <typename T_Parent_Item>
  class Abstract_Outliner_Parented_Item :
      public Abstract_Outliner_Item
  {
  public:
    using Parent_Item_Type = T_Parent_Item;

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
    void set_true_parent(Parent_Item_Type* a_parent);
  private:
    internal::Outliner_Parented_Item_Implementation<T_Parent_Item> m_data;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Outliner_Readonly_Parented_Item<Parent>
  //---------------------------------------------------------------------------

  template <typename T_Parent_Item>
  class Abstract_Outliner_Readonly_Parented_Item :
      public Abstract_Outliner_Readonly_Item
  {
  public:
    using Parent_Item_Type = T_Parent_Item;

    // Special 6
    //============================================================
    explicit Abstract_Outliner_Readonly_Parented_Item(Parent_Item_Type* a_parent);
    ~Abstract_Outliner_Readonly_Parented_Item() override;

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
    Abstract_Outliner_Item* get_child_at(int a_index) const override = 0;


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

    // Additional Interface
    //============================================================
    Parent_Item_Type* get_true_parent() const;
    void set_true_parent(Parent_Item_Type* a_parent);
  private:
    internal::Outliner_Parented_Item_Implementation<T_Parent_Item> m_data;
  };

} // namespace sak

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// internal::Outliner_Parented_Item_Implementation<Parent>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename P>
sak::internal::Outliner_Parented_Item_Implementation<P>::Outliner_Parented_Item_Implementation(Parent_Item_Type* a_parent):
    m_parent{a_parent}
{}

template <typename P>
sak::internal::Outliner_Parented_Item_Implementation<P>::~Outliner_Parented_Item_Implementation() = default;

// Parent
//----------------------------------------
// Does this item have a parent item?
template <typename P>
bool sak::internal::Outliner_Parented_Item_Implementation<P>::has_parent() const
{
  return m_parent != nullptr;
}

// Get the item that is the parent of this
template <typename P>
sak::Abstract_Outliner_Item* sak::internal::Outliner_Parented_Item_Implementation<P>::get_parent() const
{
  return m_parent;
}

// Get the item at the root of the structure
template <typename P>
sak::Abstract_Outliner_Item* sak::internal::Outliner_Parented_Item_Implementation<P>::get_root() const
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
int sak::internal::Outliner_Parented_Item_Implementation<P>::index_in_parent(Abstract_Outliner_Item const* a_item) const
{
  if (m_parent != nullptr)
  {
    for (int l_index = 0, l_end = m_parent->get_child_count(); l_index != l_end; ++l_index)
    {
      if (m_parent->get_child_at(l_index) == a_item)
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
typename sak::internal::Outliner_Parented_Item_Implementation<P>::Parent_Item_Type* sak::internal::Outliner_Parented_Item_Implementation<P>::get_true_parent() const
{
  return m_parent;
}

template <typename P>
void sak::internal::Outliner_Parented_Item_Implementation<P>::set_true_parent(Parent_Item_Type* a_parent)
{
  m_parent = a_parent;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Outliner_Parented_Item<Parent>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename P>
sak::Abstract_Outliner_Parented_Item<P>::Abstract_Outliner_Parented_Item(Parent_Item_Type* a_parent):
  Abstract_Outliner_Item(),
  m_data{a_parent}
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
  return m_data.has_parent();
}

// Get the item that is the parent of this
template <typename P>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Parented_Item<P>::get_parent() const
{
  return m_data.get_parent();
}

// Get the item at the root of the structure
template <typename P>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Parented_Item<P>::get_root() const
{
  return m_data.get_root();
}

// The row that this item is in relative to the parent e.g. if the parent has
// 5 children, and this is the third, then row is 2. If this has no parent
// then -1 is returned.
template <typename P>
int sak::Abstract_Outliner_Parented_Item<P>::index_in_parent() const
{
  return m_data.index_in_parent(this);
}

// Additional Interface
//============================================================
template <typename P>
typename sak::Abstract_Outliner_Parented_Item<P>::Parent_Item_Type* sak::Abstract_Outliner_Parented_Item<P>::get_true_parent() const
{
  return m_data.get_true_parent();
}

template <typename P>
void sak::Abstract_Outliner_Parented_Item<P>::set_true_parent(Parent_Item_Type* a_parent)
{
  m_data.set_true_parent(a_parent);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Outliner_Readonly_Parented_Item<Parent>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename P>
sak::Abstract_Outliner_Readonly_Parented_Item<P>::Abstract_Outliner_Readonly_Parented_Item(Parent_Item_Type* a_parent):
  Abstract_Outliner_Readonly_Item(),
  m_data{a_parent}
{}

template <typename P>
sak::Abstract_Outliner_Readonly_Parented_Item<P>::~Abstract_Outliner_Readonly_Parented_Item() = default;

// Virtual Interface
//============================================================
// Parent
//----------------------------------------
// Does this item have a parent item?
template <typename P>
bool sak::Abstract_Outliner_Readonly_Parented_Item<P>::has_parent() const
{
  return m_data.has_parent();
}

// Get the item that is the parent of this
template <typename P>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Readonly_Parented_Item<P>::get_parent() const
{
  return m_data.get_parent();
}

// Get the item at the root of the structure
template <typename P>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Readonly_Parented_Item<P>::get_root() const
{
  return m_data.get_root();
}

// The row that this item is in relative to the parent e.g. if the parent has
// 5 children, and this is the third, then row is 2. If this has no parent
// then -1 is returned.
template <typename P>
int sak::Abstract_Outliner_Readonly_Parented_Item<P>::index_in_parent() const
{
  return m_data.index_in_parent(this);
}

// Additional Interface
//============================================================
template <typename P>
typename sak::Abstract_Outliner_Readonly_Parented_Item<P>::Parent_Item_Type* sak::Abstract_Outliner_Readonly_Parented_Item<P>::get_true_parent() const
{
  return m_data.get_true_parent();
}

template <typename P>
void sak::Abstract_Outliner_Readonly_Parented_Item<P>::set_true_parent(Parent_Item_Type* a_parent)
{
  m_data.set_true_parent(a_parent);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // SAK_ABSTRACT_OUTLINER_PARENTED_ITEM_HPP
