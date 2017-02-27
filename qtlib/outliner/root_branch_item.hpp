#ifndef OUTLINER_ROOT_BRANCH_ITEM_HPP
#define OUTLINER_ROOT_BRANCH_ITEM_HPP

#include "abstract_root_item.hpp"
#include <vector>
#include <memory>
//#include <type_traits>
#include <QVariant>

namespace qtlib
{
    namespace outliner
    {
        //---------------------------------------------------------------------------
        // outliner::Root_Branch_Item<Children>
        //---------------------------------------------------------------------------
        // Subclass of abstract::Root_Item to give the implementation of a root item
        // with 0+ children of a given type.

        template <typename C>
        class Root_Branch_Item :
                public abstract::Root_Item
        {
        public:
            using item_type = abstract::Root_Item::item_type;
            using model_type = abstract::Root_Item::model_type;

            using child_type = C;

            //static_assert(std::is_base_of<abstract::Item, child_type>::value, "child_type must inherit qtlib::outliner::abstract::Item");

            // Special 6
            //============================================================
            Root_Branch_Item();
            ~Root_Branch_Item() override;

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
            child_type* get_true_child_at(int a_index) const;

            void append_child(std::unique_ptr<child_type>&& a_item);
        private:
            std::vector<std::unique_ptr<child_type>> m_children;
        };
    } // namespace outliner
} // namespace qtlib


//---------------------------------------------------------------------------
// outliner::Root_Branch_Item<Children>
//---------------------------------------------------------------------------
// Subclass of abstract::Root_Item to give the implementation of a root item
// with 0+ children of a given type.

// Special 6
//============================================================
template <typename C>
qtlib::outliner::Root_Branch_Item<C>::Root_Branch_Item():
    m_children{}
{}

template <typename C>
qtlib::outliner::Root_Branch_Item<C>::~Root_Branch_Item() = default;

// Virtual Interface
//============================================================
// Does this item have any child items?
template <typename C>
bool qtlib::outliner::Root_Branch_Item<C>::has_children() const
{
    return !m_children.empty();
}
// The number of children this item has
template <typename C>
int qtlib::outliner::Root_Branch_Item<C>::get_child_count() const
{
    return static_cast<int>(m_children.size());
}

// Does this item have a child item at this index?
template <typename C>
bool qtlib::outliner::Root_Branch_Item<C>::has_child_at(int a_index) const
{
    return a_index >= 0 && a_index < static_cast<int>(m_children.size());
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename C>
typename qtlib::outliner::Root_Branch_Item<C>::item_type* qtlib::outliner::Root_Branch_Item<C>::get_child_at(int a_index) const
{
    return m_children.at(a_index).get();
}

// Additional Interface
//============================================================
template <typename C>
typename qtlib::outliner::Root_Branch_Item<C>::child_type* qtlib::outliner::Root_Branch_Item<C>::get_true_child_at(int a_index) const
{
    return m_children.at(a_index).get();
}
template <typename C>
void qtlib::outliner::Root_Branch_Item<C>::append_child(std::unique_ptr<child_type>&& a_item)
{
    m_children.push_back(std::move(a_item));
}


#endif // OUTLINER_ROOT_BRANCH_ITEM_HPP
