#ifndef OUTLINER_ROOT_TRUNK_ITEM_HPP
#define OUTLINER_ROOT_TRUNK_ITEM_HPP

#include "abstract_root_item.hpp"
#include <memory>
//#include <type_traits>
#include <QVariant>

namespace qtlib
{
    namespace outliner
    {
        //---------------------------------------------------------------------------
        // outliner::Root_Trunk_Item<Child>
        //---------------------------------------------------------------------------
        // Subclass of abstract::Root_Item to give the implementation of a root item
        // with 0 or 1 child of a given type.

        template <typename C>
        class Root_Trunk_Item :
                public abstract::Root_Item
        {
        public:
            using item_type = abstract::Root_Item::item_type;
            using model_type = abstract::Root_Item::model_type;

            using child_type = C;

            //static_assert(std::is_base_of<abstract::Item, child_type>::value, "child_type must inherit qtlib::outliner::abstract::Item");

            // Special 6
            //============================================================
            Root_Trunk_Item();
            ~Root_Trunk_Item() override;

            // Virtual Interface
            //============================================================
            // Does this item have any child items?
            bool has_children() const override final;
            // The number of children this item has
            int get_child_count() const override final;

            // Does this item have a child item at this index?
            bool has_child_at(int a_index) const override final;
            // Get the child at a given row, return nullptr if there is no child at row
            item_type* get_child_at(int a_index) const override final;

            // Other
            //----------------------------------------
            // Make and act on the context menu for this item. Need the model pointer here so that
            // actions can call functions in it for editing.  Position is the position in terms of
            // the widget rather than the window. Use a_view->viewport()->mapToGlobal(a_position)
            // to get the position relative to the window for a properly placed menu.
            void do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position) override = 0;
            // Do whatever we want when an item has been double clicked on.
            void do_double_clicked(QAbstractItemView* a_view, model_type* a_model) override = 0;

        //protected:
            // Additional Interface
            //============================================================
            child_type* get_true_child() const;

            void set_child(std::unique_ptr<child_type>&& a_item);
        private:
            std::unique_ptr<child_type> m_child;
        };


    } // namespace outliner
} // namespace qtlib


//---------------------------------------------------------------------------
// outliner::Root_Trunk_Item<Parent, Child>
//---------------------------------------------------------------------------
// Subclass of abstract::Item which is in the middle of the tree. It has a
// single parent and a single child that may or may not be present. Root_Trunk_Item
// may have differenct distinct types for the parent and child, so long as they
// are both subclasses of abstract::Item.

// Special 6
//============================================================
template <typename C>
qtlib::outliner::Root_Trunk_Item<C>::Root_Trunk_Item():
    m_child{}
{}

template <typename C>
qtlib::outliner::Root_Trunk_Item<C>::~Root_Trunk_Item() = default;

// Virtual Interface
//============================================================
// Does this item have any child items?
template <typename C>
bool qtlib::outliner::Root_Trunk_Item<C>::has_children() const
{
    return m_child != nullptr;
}
// The number of children this item has
template <typename C>
int qtlib::outliner::Root_Trunk_Item<C>::get_child_count() const
{
    return (m_child != nullptr ? 1 : 0);
}

// Does this item have a child item at this index?
template <typename C>
bool qtlib::outliner::Root_Trunk_Item<C>::has_child_at(int a_index) const
{
    return m_child != nullptr && a_index == 0;
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename C>
typename qtlib::outliner::Root_Trunk_Item<C>::item_type* qtlib::outliner::Root_Trunk_Item<C>::get_child_at(int a_index) const
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
typename qtlib::outliner::Root_Trunk_Item<C>::child_type* qtlib::outliner::Root_Trunk_Item<C>::get_true_child() const
{
    return m_child.get();
}
template <typename C>
void qtlib::outliner::Root_Trunk_Item<C>::set_child(std::unique_ptr<child_type>&& a_item)
{
    m_child = std::move(a_item);
}


#endif // OUTLINER_ROOT_TRUNK_ITEM_HPP
