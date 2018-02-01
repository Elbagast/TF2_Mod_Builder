#ifndef SAK_ABSTRACT_OUTLINER_MULTITRUNK_ITEM_HPP
#define SAK_ABSTRACT_OUTLINER_MULTITRUNK_ITEM_HPP

#ifndef SAK_ABSTRACT_OUTLINER_MULTITRUNK_ITEM_FWD_HPP
#include "abstract_outliner_multitrunk_item_fwd.hpp"
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

#ifndef INCLUDE_STD_TUPLE
#define INCLUDE_STD_TUPLE
#include <tuple>
#endif

namespace sak
{
  namespace internal
  {
    //---------------------------------------------------------------------------
    // Outliner_Multitrunk_Item_Implementation<Children...>
    //---------------------------------------------------------------------------
    // Seperating out the implementation so that the inheritance is simpler and
    // shared details are in one place.
    template <typename... T_Children>
    class Outliner_Multitrunk_Item_Implementation
    {
    public:
      template <std::size_t N>
      using Child_Item_Type = std::tuple_element_t<N, std::tuple<T_Children...>>;

      // Special 6
      //============================================================
      Outliner_Multitrunk_Item_Implementation();
      ~Outliner_Multitrunk_Item_Implementation();

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

      template <std::size_t N>
      Child_Item_Type<N>* get_true_child() const;

      template <std::size_t N>
      void set_child(std::unique_ptr<Child_Item_Type<N>>&& a_item);

      template <std::size_t N>
      void remove_child();
    private:
      std::tuple<std::unique_ptr<T_Children>...> m_children;
    };
  }

  //------------------------------------------------------------------------------------------------------------------------------------------------------


  //---------------------------------------------------------------------------
  // Abstract_Outliner_Multitrunk_Item<Parent, Child>
  //---------------------------------------------------------------------------
  // Subclass of Abstract_Outliner_Item which is in the middle of the tree. It has a
  // single parent and a multiple children that may or may not be present. Each
  // child has a distinct type.

  template <typename T_Parent, typename... T_Children>
  class Abstract_Outliner_Multitrunk_Item :
    public Abstract_Outliner_Parented_Item<T_Parent>
  {
    //template <typename...Args>
    //using uptr_tuple = std::tuple<std::unique_ptr<Args>...>;
  public:
    template <std::size_t N>
    using Child_Item_Type = std::tuple_element_t<N, std::tuple<T_Children...>>;

    // Special 6
    //============================================================
    explicit Abstract_Outliner_Multitrunk_Item(Parent_Item_Type* a_parent);
    ~Abstract_Outliner_Multitrunk_Item() override;

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
    using Abstract_Outliner_Parented_Item<T_Parent>::get_true_parent;
    using Abstract_Outliner_Parented_Item<T_Parent>::set_true_parent;

    template <std::size_t N>
    Child_Item_Type<N>* get_true_child() const;

    template <std::size_t N>
    void set_child(std::unique_ptr<Child_Item_Type<N>>&& a_item);

    template <std::size_t N>
    void remove_child();
  private:
    internal::Outliner_Multitrunk_Item_Implementation<T_Children...> m_data;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------


  //---------------------------------------------------------------------------
  // Abstract_Outliner_Readonly_Multitrunk_item<Parent, Child>
  //---------------------------------------------------------------------------
  // Subclass of Multitrunk_item<Parent, Child> with the write interface
  // implemented as dummy functions. This exists to solve multiple inheritance
  // problems if you want to use features together.

  template <typename T_Parent, typename... T_Children>
  class Abstract_Outliner_Readonly_Multitrunk_Item :
      public Abstract_Outliner_Readonly_Parented_Item<T_Parent>
  {
  public:
    template <std::size_t N>
    using Child_Item_Type = std::tuple_element_t<N, std::tuple<T_Children...>>;

    // Special 6
    //============================================================
    explicit Abstract_Outliner_Readonly_Multitrunk_Item(Parent_Item_Type* a_parent);
    ~Abstract_Outliner_Readonly_Multitrunk_Item() override;

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

    // Additional Interface
    //============================================================
    using Abstract_Outliner_Readonly_Parented_Item<T_Parent>::get_true_parent;
    using Abstract_Outliner_Readonly_Parented_Item<T_Parent>::set_true_parent;

    template <std::size_t N>
    Child_Item_Type<N>* get_true_child() const;

    template <std::size_t N>
    void set_child(std::unique_ptr<Child_Item_Type<N>>&& a_item);

    template <std::size_t N>
    void remove_child();
  private:
    internal::Outliner_Multitrunk_Item_Implementation<T_Children...> m_data;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  // Abstract_Outliner_Root_Multitrunk_Item<Child>
  //---------------------------------------------------------------------------
  // Subclass of Multitrunk_item<Parent, Child> with the write interface
  // implemented as dummy functions. This exists to solve multiple inheritance
  // problems if you want to use features together.

  template <typename... T_Children>
  class Abstract_Outliner_Root_Multitrunk_Item :
      public Abstract_Outliner_Root_Item
  {
  public:
    template <std::size_t N>
    using Child_Item_Type = std::tuple_element_t<N, std::tuple<T_Children...>>;

    // Special 6
    //============================================================
    explicit Abstract_Outliner_Root_Multitrunk_Item();
    ~Abstract_Outliner_Root_Multitrunk_Item() override;

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

    // Additional Interface
    //============================================================
    template <std::size_t N>
    Child_Item_Type<N>* get_true_child() const;

    template <std::size_t N>
    void set_child(std::unique_ptr<Child_Item_Type<N>>&& a_item);

    template <std::size_t N>
    void remove_child();
  private:
    internal::Outliner_Multitrunk_Item_Implementation<T_Children...> m_data;
  };


  //------------------------------------------------------------------------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Implementation continued
  //---------------------------------------------------------------------------

  namespace internal
  {

    //---------------------------------------------------------------------------
    // Do_Has_Active_Ptrs<tuple>
    //---------------------------------------------------------------------------
    // Does a tuple of unique_ptr have any pointers that are not null?

    template <typename Tuple>
    class Do_Has_Active_Ptrs;

    template <typename... Args>
    class Do_Has_Active_Ptrs<std::tuple<std::unique_ptr<Args>...>>
    {
    private:
      using Tuple_Type = std::tuple<std::unique_ptr<Args>...>;

      template <std::size_t Index, std::size_t End = std::tuple_size<Tuple_Type>::value>
      struct Execute_Loop
      {
        bool operator()(Tuple_Type const& a_tuple) const
        {
          if(std::get<Index>(a_tuple).get() != nullptr)
          {
              return true;
          }
          else
          {
            return Execute_Loop<Index+1,End>()(a_tuple);
          }
        }
      };

      template <std::size_t End>
      struct Execute_Loop<End,End>
      {
        bool operator()(Tuple_Type const& ) const
        {
          return false;
        }
      };
    public:
      bool operator()(Tuple_Type const& a_tuple) const
      {
          return Execute_Loop<0>()(a_tuple);
      }
    };


    template <typename...Args>
    bool has_active_ptrs(std::tuple<std::unique_ptr<Args>...> const& a_tuple)
    {
      return Do_Has_Active_Ptrs<std::tuple<std::unique_ptr<Args>...>>()(a_tuple);
    }

    //---------------------------------------------------------------------------
    // Do_Active_Ptr_Count<tuple>
    //---------------------------------------------------------------------------
    // How many pointers are not null in a tuple of unique_ptr?

    template <typename Tuple>
    class Do_Active_Ptr_Count;

    template <typename... Args>
    class Do_Active_Ptr_Count<std::tuple<std::unique_ptr<Args>...>>
    {
    private:
      using Tuple_Type = std::tuple<std::unique_ptr<Args>...>;

      template <std::size_t Index, std::size_t End = std::tuple_size<Tuple_Type>::value>
      struct Execute_Loop
      {
        void operator()(std::size_t& a_count, Tuple_Type const& a_tuple) const
        {
          if(std::get<Index>(a_tuple).get() != nullptr)
          {
            ++a_count;
          }
          Execute_Loop<Index+1,End>()(a_count,a_tuple);
        }
      };

      template <std::size_t End>
      struct Execute_Loop<End,End>
      {
        void operator()(std::size_t& , Tuple_Type const& ) const
        {
        }
      };

    public:
      std::size_t operator()(Tuple_Type const& a_tuple) const
      {
        std::size_t l_count{0};
        Execute_Loop<0>()(l_count, a_tuple);
        return l_count;
      }
    };

    template <typename...Args>
    std::size_t active_ptr_count(std::tuple<std::unique_ptr<Args>...> const& a_tuple)
    {
      return Do_Active_Ptr_Count<std::tuple<std::unique_ptr<Args>...>>()(a_tuple);
    }

    //---------------------------------------------------------------------------
    // Do_Vector_Of_Active_Base_Ptr<Base,Tuple>
    //---------------------------------------------------------------------------
    // Get a vector of Base pointers from a tuple of unique_ptr. All types held
    // must inherit Base.

    template <typename Base, typename Tuple>
    class Do_Vector_Of_Active_Base_Ptr;

    template <typename... Args>
    class Do_Vector_Of_Active_Base_Ptr<Abstract_Outliner_Item, std::tuple<std::unique_ptr<Args>...>>
    {
    private:
      using Base_Type = Abstract_Outliner_Item;
      using Result_Type = std::vector<Base_Type*>;
      using Tuple_Type = std::tuple<std::unique_ptr<Args>...>;

      template <std::size_t Index, std::size_t End = std::tuple_size<Tuple_Type>::value>
      struct Execute_Loop
      {
        void operator()(Result_Type& a_result, Tuple_Type const& a_tuple) const
        {
          Base_Type* l_ptr= std::get<Index>(a_tuple).get();
          a_result.push_back(l_ptr);
          Execute_Loop<Index+1,End>()(a_result, a_tuple);
        }
      };

      template <std::size_t End>
      struct Execute_Loop<End,End>
      {
        void operator()(Result_Type& , Tuple_Type const& ) const
        {
        }
      };

    public:
      Result_Type operator()(Tuple_Type const& a_tuple) const
      {
        Result_Type l_result{};
        Execute_Loop<0>()(l_result, a_tuple);
        return l_result;
      }
    };

    template <typename...Args>
    std::vector<Abstract_Outliner_Item*> active_ptr_as_base(std::tuple<std::unique_ptr<Args>...> const& a_tuple)
    {
      return Do_Vector_Of_Active_Base_Ptr<Abstract_Outliner_Item, std::tuple<std::unique_ptr<Args>...>>()(a_tuple);
    }
  } // namespace internal
} // namespace sak

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Outliner_Multitrunk_Item_Implementation<Children...>
//---------------------------------------------------------------------------
// Seperating out the implementation so that the inheritance is simpler and
// shared details are in one place.

// Special 6
//============================================================

template <typename... Cs>
sak::internal::Outliner_Multitrunk_Item_Implementation<Cs...>::Outliner_Multitrunk_Item_Implementation():
  m_children{}
{}

template <typename... Cs>
sak::internal::Outliner_Multitrunk_Item_Implementation<Cs...>::~Outliner_Multitrunk_Item_Implementation() = default;

// Interface
//============================================================
// Children
//----------------------------------------
// Does this item have any child items?
template <typename... Cs>
bool sak::internal::Outliner_Multitrunk_Item_Implementation<Cs...>::has_children() const
{
  return has_active_ptrs(m_children);
}

// The number of children this item has
template <typename... Cs>
int sak::internal::Outliner_Multitrunk_Item_Implementation<Cs...>::get_child_count() const
{
  return static_cast<int>(active_ptr_count(m_children));
}

// Does this item have a child item at this index?
template <typename... Cs>
bool sak::internal::Outliner_Multitrunk_Item_Implementation<Cs...>::has_child_at(int a_index) const
{
  return has_active_ptrs(m_children)
          && a_index >= 0
          && a_index <= static_cast<int>(active_ptr_as_base(m_children).size());
}

// Get the child at a given row, return nullptr if there is no child at row
template <typename... Cs>
sak::Abstract_Outliner_Item* sak::internal::Outliner_Multitrunk_Item_Implementation<Cs...>::get_child_at(int a_index) const
{
  auto l_children{active_ptr_as_base(m_children)};
  return l_children.at(a_index);
}

template <typename... Cs>
template <std::size_t N>
typename sak::internal::Outliner_Multitrunk_Item_Implementation<Cs...>::Child_Item_Type<N>* sak::internal::Outliner_Multitrunk_Item_Implementation<Cs...>::get_true_child() const
{
  return std::get<N>(m_children).get();
}

template <typename... Cs>
template <std::size_t N>
void sak::internal::Outliner_Multitrunk_Item_Implementation<Cs...>::set_child(std::unique_ptr<Child_Item_Type<N>>&& a_item)
{
  std::get<N>(m_children) = std::move(a_item);
}

template <typename... Cs>
template <std::size_t N>
void sak::internal::Outliner_Multitrunk_Item_Implementation<Cs...>::remove_child()
{
  std::get<N>(m_children).reset();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Outliner_Multitrunk_Item<Parent, Children...>
//---------------------------------------------------------------------------
// Subclass of Abstract_Outliner_Item which is in the middle of the tree. It has a
// single parent and a single child that may or may not be present. Multitrunk_item
// may have differenct distinct types for the parent and child, so long as they
// are both subclasses of Abstract_Outliner_Item.

// Special 6
//============================================================
template <typename P, typename... Cs>
sak::Abstract_Outliner_Multitrunk_Item<P,Cs...>::Abstract_Outliner_Multitrunk_Item(Parent_Item_Type* a_parent):
  Abstract_Outliner_Parented_Item<P>(a_parent),
  m_data{}
{}

template <typename P, typename... Cs>
sak::Abstract_Outliner_Multitrunk_Item<P,Cs...>::~Abstract_Outliner_Multitrunk_Item() = default;

// Virtual Interface
//============================================================
// Children
//----------------------------------------

// Does this item have any child items?
template <typename P, typename... Cs>
bool sak::Abstract_Outliner_Multitrunk_Item<P,Cs...>::has_children() const
{
  return m_data.has_children();
}
// The number of children this item has
template <typename P, typename... Cs>
int sak::Abstract_Outliner_Multitrunk_Item<P,Cs...>::get_child_count() const
{
  return m_data.get_child_count();
}

// Does this item have a child item at this index?
template <typename P, typename... Cs>
bool sak::Abstract_Outliner_Multitrunk_Item<P,Cs...>::has_child_at(int a_index) const
{
  return m_data.has_child_at(a_index);
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename P, typename... Cs>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Multitrunk_Item<P,Cs...>::get_child_at(int a_index) const
{
  return m_data.get_child_at(a_index);
}

// Additional Interface
//============================================================
template <typename P, typename... Cs>
template <std::size_t N>
typename sak::Abstract_Outliner_Multitrunk_Item<P,Cs...>::Child_Item_Type<N>* sak::Abstract_Outliner_Multitrunk_Item<P,Cs...>::get_true_child() const
{
  return m_data.get_true_child<N>();
}
template <typename P, typename... Cs>
template <std::size_t N>
void sak::Abstract_Outliner_Multitrunk_Item<P,Cs...>::set_child(std::unique_ptr<Child_Item_Type<N>>&& a_item)
{
  m_data.set_child<N>(std::move(a_item));
}
template <typename P, typename... Cs>
template <std::size_t N>
void sak::Abstract_Outliner_Multitrunk_Item<P,Cs...>::remove_child()
{
  m_data.remove_child<N>();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Outliner_Readonly_Multitrunk_Item<Parent, Children...>
//---------------------------------------------------------------------------
// Special 6
//============================================================
template <typename P, typename... Cs>
sak::Abstract_Outliner_Readonly_Multitrunk_Item<P,Cs...>::Abstract_Outliner_Readonly_Multitrunk_Item(Parent_Item_Type* a_parent):
  Abstract_Outliner_Readonly_Parented_Item<P>(a_parent),
  m_data{}
{}

template <typename P, typename... Cs>
sak::Abstract_Outliner_Readonly_Multitrunk_Item<P,Cs...>::~Abstract_Outliner_Readonly_Multitrunk_Item() = default;

// Virtual Interface
//============================================================
// Children
//----------------------------------------

// Does this item have any child items?
template <typename P, typename... Cs>
bool sak::Abstract_Outliner_Readonly_Multitrunk_Item<P,Cs...>::has_children() const
{
  return m_data.has_children();
}
// The number of children this item has
template <typename P, typename... Cs>
int sak::Abstract_Outliner_Readonly_Multitrunk_Item<P,Cs...>::get_child_count() const
{
  return m_data.get_child_count();
}

// Does this item have a child item at this index?
template <typename P, typename... Cs>
bool sak::Abstract_Outliner_Readonly_Multitrunk_Item<P,Cs...>::has_child_at(int a_index) const
{
  return m_data.has_child_at(a_index);
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename P, typename... Cs>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Readonly_Multitrunk_Item<P,Cs...>::get_child_at(int a_index) const
{
  return m_data.get_child_at(a_index);
}

// Additional Interface
//============================================================
template <typename P, typename... Cs>
template <std::size_t N>
typename sak::Abstract_Outliner_Readonly_Multitrunk_Item<P,Cs...>::Child_Item_Type<N>* sak::Abstract_Outliner_Readonly_Multitrunk_Item<P,Cs...>::get_true_child() const
{
  return m_data.get_true_child<N>();
}
template <typename P, typename... Cs>
template <std::size_t N>
void sak::Abstract_Outliner_Readonly_Multitrunk_Item<P,Cs...>::set_child(std::unique_ptr<Child_Item_Type<N>>&& a_item)
{
  m_data.set_child<N>(std::move(a_item));
}
template <typename P, typename... Cs>
template <std::size_t N>
void sak::Abstract_Outliner_Readonly_Multitrunk_Item<P,Cs...>::remove_child()
{
  m_data.remove_child<N>();
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Outliner_Root_Multitrunk_Item<Children...>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename... Cs>
sak::Abstract_Outliner_Root_Multitrunk_Item<Cs...>::Abstract_Outliner_Root_Multitrunk_Item():
  Abstract_Outliner_Root_Item(),
  m_data{}
{}

template <typename... Cs>
sak::Abstract_Outliner_Root_Multitrunk_Item<Cs...>::~Abstract_Outliner_Root_Multitrunk_Item() = default;

// Virtual Interface
//============================================================
// Children
//----------------------------------------

// Does this item have any child items?
template <typename... Cs>
bool sak::Abstract_Outliner_Root_Multitrunk_Item<Cs...>::has_children() const
{
  return m_data.has_children();
}
// The number of children this item has
template <typename... Cs>
int sak::Abstract_Outliner_Root_Multitrunk_Item<Cs...>::get_child_count() const
{
  return m_data.get_child_count();
}

// Does this item have a child item at this index?
template <typename... Cs>
bool sak::Abstract_Outliner_Root_Multitrunk_Item<Cs...>::has_child_at(int a_index) const
{
  return m_data.has_child_at(a_index);
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename... Cs>
sak::Abstract_Outliner_Item* sak::Abstract_Outliner_Root_Multitrunk_Item<Cs...>::get_child_at(int a_index) const
{
  return m_data.get_child_at(a_index);
}

// Additional Interface
//============================================================
template <typename... Cs>
template <std::size_t N>
typename sak::Abstract_Outliner_Root_Multitrunk_Item<Cs...>::Child_Item_Type<N>* sak::Abstract_Outliner_Root_Multitrunk_Item<Cs...>::get_true_child() const
{
  return m_data.get_true_child<N>();
}
template <typename... Cs>
template <std::size_t N>
void sak::Abstract_Outliner_Root_Multitrunk_Item<Cs...>::set_child(std::unique_ptr<Child_Item_Type<N>>&& a_item)
{
  m_data.set_child<N>(std::move(a_item));
}
template <typename... Cs>
template <std::size_t N>
void sak::Abstract_Outliner_Root_Multitrunk_Item<Cs...>::remove_child()
{
  m_data.remove_child<N>();
}

#endif // SAK_ABSTRACT_OUTLINER_MULTITRUNK_ITEM_HPP
