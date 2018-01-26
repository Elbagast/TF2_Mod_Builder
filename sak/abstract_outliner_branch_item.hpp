#ifndef SAK_ABSTRACT_OUTLINER_BRANCH_ITEM_HPP
#define SAK_ABSTRACT_OUTLINER_BRANCH_ITEM_HPP

#ifndef SAK_ABSTRACT_OUTLINER_BRANCH_ITEM_FWD_HPP
#include "abstract_outliner_branch_item_fwd.hpp"
#endif

#ifndef SAK_ABSTRACT_OUTLINER_PARENTED_ITEM_HPP
#include "abstract_outliner_parented_item.hpp"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

#ifndef INCLUDE_STD_ITERATOR
#define INCLUDE_STD_ITERATOR
#include <iterator>
#endif

//#include <type_traits>

#ifndef INCLUDE_QT_QVARIANT
#define INCLUDE_QT_QVARIANT
#include <QVariant>
#endif

namespace sak
{
  namespace internal
  {
    //---------------------------------------------------------------------------
    // internal::Outliner_Branch_Item_Implementation<Child>
    //---------------------------------------------------------------------------
    // Seperating out the implementation so that the inheritance is simpler and
    // shared details are in one place.

    template <typename T_Child_Item>
    class Outliner_Branch_Item_Implementation
    {
    public:
      using Child_Item_Type = T_Child_Item;

      // Special 6
      //============================================================
      Outliner_Branch_Item_Implementation();
      ~Outliner_Branch_Item_Implementation();

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

      Child_Item_Type* get_true_child_at(int a_index) const;
      void append_child(std::unique_ptr<Child_Item_Type>&& a_item);
      void insert_child(std::size_t a_index, std::unique_ptr<Child_Item_Type>&& a_item);
      void remove_last_child();
      void remove_child(std::size_t a_index);

    private:
      std::vector<std::unique_ptr<Child_Item_Type>> m_children;
    };
  }
  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Outliner_Branch_Item<Parent, Children>
  //---------------------------------------------------------------------------
  // Subclass of Abstract_Outliner_Item which is in the middle of the tree. Item may have
  // differenct distinct types for the parent and children, so long as they are
  // both subclasses of Abstract_Outliner_Item.

  template <typename T_Parent_Item, typename T_Child_Item>
  class Abstract_Outliner_Branch_Item :
      public Abstract_Outliner_Parented_Item<T_Parent_Item>
  {
  public:
    using Child_Item_Type = T_Child_Item;

    //static_assert(std::is_base_of<Abstract_Outliner_Item, Parent_Item_Type>::value, "Parent_Item_Type must inherit qtlib::outliner::Abstract_Outliner_Item");
    //static_assert(std::is_base_of<Abstract_Outliner_Item, Child_Item_Type>::value, "Child_Item_Type must inherit qtlib::outliner::Abstract_Outliner_Item");

    // Special 6
    //============================================================
    explicit Abstract_Outliner_Branch_Item(Parent_Item_Type* a_parent);
    ~Abstract_Outliner_Branch_Item() override;

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

    Child_Item_Type* get_true_child_at(int a_index) const;
    void append_child(std::unique_ptr<Child_Item_Type>&& a_item);
    void insert_child(std::size_t a_index, std::unique_ptr<Child_Item_Type>&& a_item);
    void remove_last_child();
    void remove_child(std::size_t a_index);
  private:
    internal::Outliner_Branch_Item_Implementation<T_Child_Item> m_data;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Abstract_Outliner_Readonly_Branch_Item<Parent, Children>
  //---------------------------------------------------------------------------
  // Subclass of Branch_Item<Parent, Children> with the write interface
  // implemented as dummy functions. This exists to solve multiple inheritance
  // problems if you want to use features together.

  template <typename T_Parent_Item, typename T_Child_Item>
  class Abstract_Outliner_Readonly_Branch_Item :
      public Abstract_Outliner_Branch_Item<T_Parent_Item, T_Child_Item>
  {
  public:
    using Child_Item_Type = T_Child_Item;

    // Special 6
    //============================================================
    explicit Abstract_Outliner_Readonly_Branch_Item(Parent_Item_Type* a_parent);
    ~Abstract_Outliner_Readonly_Branch_Item() override;

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
    using Abstract_Outliner_Branch_Item<T_Parent_Item, T_Child_Item>::get_true_parent;
    using Abstract_Outliner_Branch_Item<T_Parent_Item, T_Child_Item>::set_parent;

    using Abstract_Outliner_Branch_Item<T_Parent_Item, T_Child_Item>::get_true_child_at;
    using Abstract_Outliner_Branch_Item<T_Parent_Item, T_Child_Item>::append_child;
    using Abstract_Outliner_Branch_Item<T_Parent_Item, T_Child_Item>::insert_child;
    using Abstract_Outliner_Branch_Item<T_Parent_Item, T_Child_Item>::remove_last_child;
    using Abstract_Outliner_Branch_Item<T_Parent_Item, T_Child_Item>::remove_child;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // outliner::Root_Branch_Item<Children>
  //---------------------------------------------------------------------------
  // Subclass of abstract::Root_Item to give the implementation of a root item
  // with 0+ children of a given type.

  template <typename T_Child_Item>
  class Abstract_Outliner_Root_Branch_Item :
      public Abstract_Outliner_Root_Item
  {
  public:
    using Child_Item_Type = T_Child_Item;

    //static_assert(std::is_base_of<Abstract_Outliner_Item, Child_Item_Type>::value, "Child_Item_Type must inherit qtlib::outliner::Abstract_Outliner_Item");

    // Special 6
    //============================================================
    Abstract_Outliner_Root_Branch_Item();
    ~Abstract_Outliner_Root_Branch_Item() override;

    // Virtual Interface
    //============================================================
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

    // Additional Interface
    //============================================================
    Child_Item_Type* get_true_child_at(int a_index) const;
    void append_child(std::unique_ptr<Child_Item_Type>&& a_item);
    void insert_child(std::size_t a_index, std::unique_ptr<Child_Item_Type>&& a_item);
    void remove_last_child();
    void remove_child(std::size_t a_index);
  private:
    internal::Outliner_Branch_Item_Implementation<T_Child_Item> m_data;
  };
} // namespace sak

//------------------------------------------------------------------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------
// internal::Outliner_Branch_Item_Implementation<Child>
//---------------------------------------------------------------------------
// Seperating out the implementation so that the inheritance is simpler and
// shared details are in one place.

// Special 6
//============================================================
template <typename C>
sak::internal::Outliner_Branch_Item_Implementation<C>::Outliner_Branch_Item_Implementation():
  m_children{}
{}

template <typename C>
sak::internal::Outliner_Branch_Item_Implementation<C>::~Outliner_Branch_Item_Implementation() = default;

// Interface
//============================================================
// Children
//----------------------------------------
// Does this item have any child items?
template <typename C>
bool sak::internal::Outliner_Branch_Item_Implementation<C>::has_children() const
{
  return !m_children.empty();
}

// The number of children this item has
template <typename C>
int sak::internal::Outliner_Branch_Item_Implementation<C>::get_child_count() const
{
  return static_cast<int>(m_children.size());
}

// Does this item have a child item at this index?
template <typename C>
bool sak::internal::Outliner_Branch_Item_Implementation<C>::has_child_at(int a_index) const
{
  return a_index >= 0 && a_index < static_cast<int>(m_children.size());
}

// Get the child at a given row, return nullptr if there is no child at row
template <typename C>
sak::Abstract_Outliner_Item* sak::internal::Outliner_Branch_Item_Implementation<C>::get_child_at(int a_index) const
{
  return (has_child_at(a_index) ? m_children.at(a_index).get() : nullptr);
}

template <typename C>
typename sak::internal::Outliner_Branch_Item_Implementation<C>::Child_Item_Type* sak::internal::Outliner_Branch_Item_Implementation<C>::get_true_child_at(int a_index) const
{
  return (has_child_at(a_index) ? m_children.at(a_index).get() : nullptr);
}

template <typename C>
void sak::internal::Outliner_Branch_Item_Implementation<C>::append_child(std::unique_ptr<Child_Item_Type>&& a_item)
{
  m_children.push_back(std::move(a_item));
}

template <typename C>
void sak::internal::Outliner_Branch_Item_Implementation<C>::insert_child(std::size_t a_index, std::unique_ptr<Child_Item_Type>&& a_item)
{
  auto l_position = m_children.begin();
  std::advance(l_position, a_index);
  m_children.insert(l_position, std::move(a_item));
}

template <typename C>
void sak::internal::Outliner_Branch_Item_Implementation<C>::remove_last_child()
{
  m_children.pop_back();
}

template <typename C>
void sak::internal::Outliner_Branch_Item_Implementation<C>::remove_child(std::size_t a_index)
{
  auto l_position = m_children.begin();
  std::advance(l_position, a_index);
  l_position->reset();
  m_children.erase(l_position);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Outliner_Branch_Item<Parent, Children>
//---------------------------------------------------------------------------
// Subclass of Abstract_Outliner_Item which is in the middle of the tree. Item may have
// differenct distinct types for the parent and children, so long as they are
// both subclasses of Abstract_Outliner_Item.

// Special 6
//============================================================
template <typename P, typename C>
sak::Abstract_Outliner_Branch_Item<P,C>::Abstract_Outliner_Branch_Item(Parent_Item_Type* a_parent):
    Abstract_Outliner_Parented_Item<P>(a_parent),
    m_data{}
{}

template <typename P, typename C>
sak::Abstract_Outliner_Branch_Item<P,C>::~Abstract_Outliner_Branch_Item() = default;

// Virtual Interface
//============================================================

// Children
//----------------------------------------
// Does this item have any child items?
template <typename P, typename C>
bool sak::Abstract_Outliner_Branch_Item<P,C>::has_children() const
{
  return m_data.has_children();
}
// The number of children this item has
template <typename P, typename C>
int sak::Abstract_Outliner_Branch_Item<P,C>::get_child_count() const
{
  return m_data.get_child_count();
}

// Does this item have a child item at this index?
template <typename P, typename C>
bool sak::Abstract_Outliner_Branch_Item<P,C>::has_child_at(int a_index) const
{
  return m_data.has_child_at(a_index);
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename P, typename C>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Branch_Item<P,C>::get_child_at(int a_index) const
{
  return m_data.get_child_at(a_index);
}


// Additional Interface
//============================================================
template <typename P, typename C>
typename sak::Abstract_Outliner_Branch_Item<P,C>::Child_Item_Type* sak::Abstract_Outliner_Branch_Item<P,C>::get_true_child_at(int a_index) const
{
  return m_data.get_true_child_at(a_index);
}

template <typename P, typename C>
void sak::Abstract_Outliner_Branch_Item<P,C>::append_child(std::unique_ptr<Child_Item_Type>&& a_item)
{
  m_data.append_child(std::move(a_item));
}

template <typename P, typename C>
void sak::Abstract_Outliner_Branch_Item<P,C>::insert_child(std::size_t a_index, std::unique_ptr<Child_Item_Type>&& a_item)
{
  m_data.insert_child(a_index, std::move(a_item));
}

template <typename P, typename C>
void sak::Abstract_Outliner_Branch_Item<P,C>::remove_last_child()
{
  m_data.remove_last_child();
}

template <typename P, typename C>
void sak::Abstract_Outliner_Branch_Item<P,C>::remove_child(std::size_t a_index)
{
  m_data.remove_child(a_index);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Outliner_Readonly_Branch_Item<Parent, Children>
//---------------------------------------------------------------------------
// Subclass of Branch_Item<Parent, Children> with the write interface
// implemented as dummy functions. This exists to solve multiple inheritance
// problems if you want to use features together.

// Special 6
//============================================================
template <typename P, typename C>
sak::Abstract_Outliner_Readonly_Branch_Item<P,C>::Abstract_Outliner_Readonly_Branch_Item(Parent_Item_Type* a_parent):
  Abstract_Outliner_Branch_Item<P,C>(a_parent)
{}

template <typename P, typename C>
sak::Abstract_Outliner_Readonly_Branch_Item<P,C>::~Abstract_Outliner_Readonly_Branch_Item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Set the data in item with the given value
template <typename P, typename C>
void sak::Abstract_Outliner_Readonly_Branch_Item<P,C>::set_data(QVariant const& a_value)
{
  this->Abstract_Outliner_Item::set_data(a_value);
}

// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
template <typename P, typename C>
QWidget* sak::Abstract_Outliner_Readonly_Branch_Item<P,C>::get_editor(QWidget* a_parent)
{
  return this->Abstract_Outliner_Item::get_editor(a_parent);
}
// Set the data in the editor to the value in the item
template <typename P, typename C>
void sak::Abstract_Outliner_Readonly_Branch_Item<P,C>::set_editor_data(QWidget* a_editor)
{
  this->Abstract_Outliner_Item::set_editor_data(a_editor);
}
// Get the data in the editor and return it
template <typename P, typename C>
QVariant sak::Abstract_Outliner_Readonly_Branch_Item<P,C>::get_editor_data(QWidget* a_editor)
{
  return this->Abstract_Outliner_Item::get_editor_data(a_editor);
}

// Other
//----------------------------------------
// Get the flags for this item
template <typename P, typename C>
Qt::ItemFlags sak::Abstract_Outliner_Readonly_Branch_Item<P,C>::get_flags() const
{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Outliner_Root_Branch_Item<Children>
//---------------------------------------------------------------------------
// Subclass of abstract::Root_Item to give the implementation of a root item
// with 0+ children of a given type.

// Special 6
//============================================================
template <typename C>
sak::Abstract_Outliner_Root_Branch_Item<C>::Abstract_Outliner_Root_Branch_Item():
    m_data{}
{}

template <typename C>
sak::Abstract_Outliner_Root_Branch_Item<C>::~Abstract_Outliner_Root_Branch_Item() = default;

// Virtual Interface
//============================================================

// Children
//----------------------------------------
// Does this item have any child items?
template <typename C>
bool sak::Abstract_Outliner_Root_Branch_Item<C>::has_children() const
{
  return m_data.has_children();
}
// The number of children this item has
template <typename C>
int sak::Abstract_Outliner_Root_Branch_Item<C>::get_child_count() const
{
  return m_data.get_child_count();
}

// Does this item have a child item at this index?
template <typename C>
bool sak::Abstract_Outliner_Root_Branch_Item<C>::has_child_at(int a_index) const
{
  return m_data.has_child_at(a_index);
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename C>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Root_Branch_Item<C>::get_child_at(int a_index) const
{
  return m_data.get_child_at(a_index);
}


// Additional Interface
//============================================================
template <typename C>
typename sak::Abstract_Outliner_Root_Branch_Item<C>::Child_Item_Type* sak::Abstract_Outliner_Root_Branch_Item<C>::get_true_child_at(int a_index) const
{
  return m_data.get_true_child_at(a_index);
}

template <typename C>
void sak::Abstract_Outliner_Root_Branch_Item<C>::append_child(std::unique_ptr<Child_Item_Type>&& a_item)
{
  m_data.append_child(std::move(a_item));
}

template <typename C>
void sak::Abstract_Outliner_Root_Branch_Item<C>::insert_child(std::size_t a_index, std::unique_ptr<Child_Item_Type>&& a_item)
{
  m_data.insert_child(a_index, std::move(a_item));
}

template <typename C>
void sak::Abstract_Outliner_Root_Branch_Item<C>::remove_last_child()
{
  m_data.remove_last_child();
}

template <typename C>
void sak::Abstract_Outliner_Root_Branch_Item<C>::remove_child(std::size_t a_index)
{
  m_data.remove_child(a_index);
}


#endif // SAK_ABSTRACT_OUTLINER_BRANCH_ITEM_HPP
