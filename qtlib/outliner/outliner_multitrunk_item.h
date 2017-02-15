#ifndef OUTLINER_MUTITRUNK_ITEM_H
#define OUTLINER_MUTITRUNK_ITEM_H

#include "outliner_parented_item.h"
#include <memory>
#include <vector>
#include <tuple>
#include <type_traits>
#include <QVariant>
#include <cassert>

namespace qtlib
{
    namespace outliner
    {
        namespace internal
        {
            template <typename...Args>
            using uptr_tuple = std::tuple<std::unique_ptr<Args>...>;

            static_assert(std::is_same<
                          std::tuple<std::unique_ptr<bool>,std::unique_ptr<int>, std::unique_ptr<float>>,
                          uptr_tuple<bool,int,float>
                          >::value, "oops");

            template <typename Tuple>
            struct Has_Active_Ptrs;

            template <typename... Args>
            struct Has_Active_Ptrs<std::tuple<std::unique_ptr<Args>...>>
            {
                using tuple_type = std::tuple<std::unique_ptr<Args>...>;

                template <std::size_t Index, std::size_t End = std::tuple_size<tuple_type>::value>
                struct Execute_Loop
                {
                    bool operator()(tuple_type const& a_tuple) const
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
                    bool operator()(tuple_type const& ) const
                    {
                        return false;
                    }
                };

                bool operator()(tuple_type const& a_tuple) const
                {
                    return Execute_Loop<0>()(a_tuple);
                }
            };


            template <typename...Args>
            bool has_active_ptrs(uptr_tuple<Args...> const& a_tuple)
            {
                return Has_Active_Ptrs<uptr_tuple<Args...>>()(a_tuple);
            }



            template <typename Tuple>
            struct Active_Ptr_Count;

            template <typename... Args>
            struct Active_Ptr_Count<std::tuple<std::unique_ptr<Args>...>>
            {
                using tuple_type = std::tuple<std::unique_ptr<Args>...>;

                template <std::size_t Index, std::size_t End = std::tuple_size<tuple_type>::value>
                struct Execute_Loop
                {
                    void operator()(std::size_t& a_count, tuple_type const& a_tuple) const
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
                    void operator()(std::size_t& , tuple_type const& ) const
                    {

                    }
                };

                std::size_t operator()(tuple_type const& a_tuple) const
                {
                    std::size_t l_count{0};
                    Execute_Loop<0>()(l_count, a_tuple);
                    return l_count;
                }
            };


            template <typename Base, typename Tuple>
            struct Vector_of_Active_Ptrs;

            template <typename... Args>
            struct Vector_of_Active_Ptrs<abstract::Item, std::tuple<std::unique_ptr<Args>...>>
            {
                using base_type = abstract::Item;
                using result_type = std::vector<base_type*>;
                using tuple_type = std::tuple<std::unique_ptr<Args>...>;

                template <std::size_t Index, std::size_t End = std::tuple_size<tuple_type>::value>
                struct Execute_Loop
                {
                    void operator()(result_type& a_result, tuple_type const& a_tuple) const
                    {
                        base_type* l_ptr= std::get<Index>(a_tuple).get();
                        a_result.push_back(l_ptr);
                        Execute_Loop<Index+1,End>()(a_result, a_tuple);
                    }
                };

                template <std::size_t End>
                struct Execute_Loop<End,End>
                {
                    void operator()(result_type& , tuple_type const& ) const
                    {
                    }
                };

                result_type operator()(tuple_type const& a_tuple) const
                {
                    result_type l_result{};
                    Execute_Loop<0>()(l_result, a_tuple);
                    return l_result;
                }
            };

            template <typename T, typename...Args>
            std::vector<T*> active_ptr_as_base(uptr_tuple<Args...> const& a_tuple)
            {
                return Vector_of_Active_Ptrs<T, uptr_tuple<Args...>>()(a_tuple);
            }

            template <typename T, typename...Args>
            std::size_t active_ptr_count(uptr_tuple<Args...> const& a_tuple)
            {
                return active_ptr_as_base<T, uptr_tuple<Args...>>(a_tuple).size();
            }
        }


        //---------------------------------------------------------------------------
        // outliner::Multitrunk_item<Parent, Child>
        //---------------------------------------------------------------------------
        // Subclass of abstract::Item which is in the middle of the tree. It has a
        // single parent and a multiple children that may or may not be present. Each
        // child has a distinct type.

        template <typename P, typename... Cs>
        class Multitrunk_item :
                public Parented_Item<P>
        {
            //template <typename...Args>
            //using uptr_tuple = std::tuple<std::unique_ptr<Args>...>;
        public:
            using item_type = typename Parented_Item<P>::item_type;
            using model_type = typename Parented_Item<P>::model_type;

            using parent_type = typename Parented_Item<P>::parent_type;

            using tuple_type = internal::uptr_tuple<Cs...>;


            template <std::size_t N>
            using child_type = typename std::tuple_element_t<N, tuple_type>::element_type;

            //static_assert(std::is_base_of<abstract::Item, parent_type>::value, "parent_type must inherit qtlib::outliner::abstract::Item");
            //static_assert(std::is_base_of<abstract::Item, child_type>::value, "child_type must inherit qtlib::outliner::abstract::Item");

            // Special 6
            //============================================================
            explicit Multitrunk_item(parent_type* a_parent);
            ~Multitrunk_item() override;

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
            item_type* get_child_at(int a_index) const override final;

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
            void do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position) override = 0;

        protected:
            // Additional Interface
            //============================================================
            using Parented_Item<P>::get_true_parent;
            using Parented_Item<P>::set_parent;

            template <std::size_t N>
            child_type<N>* get_true_child() const;

            template <std::size_t N>
            void set_child(std::unique_ptr<child_type<N>>&& a_item);
        private:
            parent_type* m_parent;
            tuple_type m_children;
        };


        //---------------------------------------------------------------------------
        // outliner::Readonly_Multitrunk_item<Parent, Child>
        //---------------------------------------------------------------------------
        // Subclass of Multitrunk_item<Parent, Child> with the write interface
        // implemented as dummy functions. This exists to solve multiple inheritance
        // problems if you want to use features together.

        template <typename P, typename... Cs>
        class Readonly_Multitrunk_item :
                public Multitrunk_item<P,Cs...>
        {
        public:
            using item_type = typename Multitrunk_item<P,Cs...>::item_type;
            using model_type = typename Multitrunk_item<P,Cs...>::model_type;

            using parent_type = typename Multitrunk_item<P,Cs...>::parent_type;

            template <std::size_t N>
            using child_type = typename Multitrunk_item<P,Cs...>::child_type<N>;

            // Special 6
            //============================================================
            explicit Readonly_Multitrunk_item(parent_type* a_parent);
            ~Readonly_Multitrunk_item() override;

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
            void do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position) override = 0;

        protected:
            // Additional Interface
            //============================================================
            using Multitrunk_item<P,Cs...>::get_true_parent;
            using Multitrunk_item<P,Cs...>::set_parent;

            using Multitrunk_item<P,Cs...>::get_true_child;
            using Multitrunk_item<P,Cs...>::set_child;
        };
    } // namespace outliner
} // namespace qtlib


//---------------------------------------------------------------------------
// outliner::Multitrunk_item<Parent, Child>
//---------------------------------------------------------------------------
// Subclass of abstract::Item which is in the middle of the tree. It has a
// single parent and a single child that may or may not be present. Multitrunk_item
// may have differenct distinct types for the parent and child, so long as they
// are both subclasses of abstract::Item.

// Special 6
//============================================================
template <typename P, typename... Cs>
qtlib::outliner::Multitrunk_item<P,Cs...>::Multitrunk_item(parent_type* a_parent):
    Parented_Item<P>(a_parent),
    m_children{}
{}

template <typename P, typename... Cs>
qtlib::outliner::Multitrunk_item<P,Cs...>::~Multitrunk_item() = default;

// Virtual Interface
//============================================================
// Children
//----------------------------------------

// Does this item have any child items?
template <typename P, typename... Cs>
bool qtlib::outliner::Multitrunk_item<P,Cs...>::has_children() const
{
    return internal::Has_Active_Ptrs<tuple_type>()(m_children);
}
// The number of children this item has
template <typename P, typename... Cs>
int qtlib::outliner::Multitrunk_item<P,Cs...>::get_child_count() const
{
    return static_cast<int>(internal::Active_Ptr_Count<tuple_type>()(m_children));
}

// Does this item have a child item at this index?
template <typename P, typename... Cs>
bool qtlib::outliner::Multitrunk_item<P,Cs...>::has_child_at(int a_index) const
{
    return internal::Has_Active_Ptrs<tuple_type>()(m_children)
            && a_index >= 0
            && a_index <= static_cast<int>(internal::Vector_of_Active_Ptrs<item_type,tuple_type>()(m_children).size());
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename P, typename... Cs>
typename qtlib::outliner::Multitrunk_item<P,Cs...>::item_type* qtlib::outliner::Multitrunk_item<P,Cs...>::get_child_at(int a_index) const
{
    auto l_children{internal::Vector_of_Active_Ptrs<item_type,tuple_type>()(m_children)};
    return l_children.at(a_index);
}

// Additional Interface
//============================================================
template <typename P, typename... Cs>
template <std::size_t N>
typename qtlib::outliner::Multitrunk_item<P,Cs...>::child_type<N>* qtlib::outliner::Multitrunk_item<P,Cs...>::get_true_child() const
{
    return std::get<N>(m_children).get();
}
template <typename P, typename... Cs>
template <std::size_t N>
void qtlib::outliner::Multitrunk_item<P,Cs...>::set_child(std::unique_ptr<child_type<N>>&& a_item)
{
    std::get<N>(m_children) = std::move(a_item);
}

//---------------------------------------------------------------------------
// outliner::Readonly_Multitrunk_item<Parent, Child>
//---------------------------------------------------------------------------
// Subclass of Multitrunk_item<Parent, Child> with the write interface
// implemented as dummy functions. This exists to solve multiple inheritance
// problems if you want to use features together.

// Special 6
//============================================================
template <typename P, typename... Cs>
qtlib::outliner::Readonly_Multitrunk_item<P,Cs...>::Readonly_Multitrunk_item(parent_type* a_parent):
    Multitrunk_item<P,Cs...>(a_parent)
{}

template <typename P, typename... Cs>
qtlib::outliner::Readonly_Multitrunk_item<P,Cs...>::~Readonly_Multitrunk_item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Set the data in item with the given value
template <typename P, typename... Cs>
void qtlib::outliner::Readonly_Multitrunk_item<P,Cs...>::set_data(QVariant const& a_value)
{
    this->abstract::Item::set_data(a_value);
}

// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
template <typename P, typename... Cs>
QWidget* qtlib::outliner::Readonly_Multitrunk_item<P,Cs...>::get_editor(QWidget* a_parent)
{
    return this->abstract::Item::get_editor(a_parent);
}
// Set the data in the editor to the value in the item
template <typename P, typename... Cs>
void qtlib::outliner::Readonly_Multitrunk_item<P,Cs...>::set_editor_data(QWidget* a_editor)
{
    this->abstract::Item::set_editor_data(a_editor);
}
// Get the data in the editor and return it
template <typename P, typename... Cs>
QVariant qtlib::outliner::Readonly_Multitrunk_item<P,Cs...>::get_editor_data(QWidget* a_editor)
{
    return this->abstract::Item::get_editor_data(a_editor);
}

// Other
//----------------------------------------
// Get the flags for this item
template <typename P, typename... Cs>
Qt::ItemFlags qtlib::outliner::Readonly_Multitrunk_item<P,Cs...>::get_flags() const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


#endif // OUTLINER_MUTIMultitrunk_item_H
