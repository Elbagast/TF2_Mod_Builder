#ifndef OUTLINER_ITEM_HPP
#define OUTLINER_ITEM_HPP

#include "outliner_parented_item.hpp"
#include <vector>
#include <memory>
#include <type_traits>
#include <iterator>
#include <QVariant>

namespace qtlib
{
    namespace outliner
    {
        //---------------------------------------------------------------------------
        // outliner::Branch_Item<Parent, Children>
        //---------------------------------------------------------------------------
        // Subclass of abstract::Item which is in the middle of the tree. Item may have
        // differenct distinct types for the parent and children, so long as they are
        // both subclasses of abstract::Item.

        template <typename P, typename C>
        class Branch_Item :
                public Parented_Item<P>
        {
        public:
            using item_type = typename Parented_Item<P>::item_type;
            using model_type = typename Parented_Item<P>::model_type;

            using parent_type = typename Parented_Item<P>::parent_type;
            using child_type = C;

            //static_assert(std::is_base_of<abstract::Item, parent_type>::value, "parent_type must inherit qtlib::outliner::abstract::Item");
            //static_assert(std::is_base_of<abstract::Item, child_type>::value, "child_type must inherit qtlib::outliner::abstract::Item");

            // Special 6
            //============================================================
            explicit Branch_Item(parent_type* a_parent);
            ~Branch_Item() override;

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
            void do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position) override = 0;
            // Do whatever we want when an item has been double clicked on.
            void do_double_clicked(QAbstractItemView* a_view, model_type* a_model) override = 0;

        //protected:
            // Additional Interface
            //============================================================
            using Parented_Item<P>::get_true_parent;
            using Parented_Item<P>::set_parent;

            child_type* get_true_child_at(int a_index) const;
            void append_child(std::unique_ptr<child_type>&& a_item);
            void insert_child(std::size_t a_index, std::unique_ptr<child_type>&& a_item);
            void remove_last_child();
            void remove_child(std::size_t a_index);
        private:
            parent_type* m_parent;
            std::vector<std::unique_ptr<child_type>> m_children;
        };


        //---------------------------------------------------------------------------
        // outliner::Readonly_Branch_Item<Parent, Children>
        //---------------------------------------------------------------------------
        // Subclass of Branch_Item<Parent, Children> with the write interface
        // implemented as dummy functions. This exists to solve multiple inheritance
        // problems if you want to use features together.

        template <typename P, typename C>
        class Readonly_Branch_Item :
                public Branch_Item<P,C>
        {
        public:
            using item_type = typename Branch_Item<P,C>::item_type;
            using model_type = typename Branch_Item<P,C>::model_type;

            using parent_type = typename Branch_Item<P,C>::parent_type;
            using child_type = typename Branch_Item<P,C>::child_type;

            // Special 6
            //============================================================
            explicit Readonly_Branch_Item(parent_type* a_parent);
            ~Readonly_Branch_Item() override;

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
            void do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position) override = 0;
            // Do whatever we want when an item has been double clicked on.
            void do_double_clicked(QAbstractItemView* a_view, model_type* a_model) override = 0;

        //protected:
            // Additional Interface
            //============================================================
            using Branch_Item<P,C>::get_true_parent;
            using Branch_Item<P,C>::set_parent;

            using Branch_Item<P,C>::get_true_child_at;
            using Branch_Item<P,C>::append_child;
            using Branch_Item<P,C>::insert_child;
            using Branch_Item<P,C>::remove_last_child;
            using Branch_Item<P,C>::remove_child;
        };
    } // namespace outliner
} // namespace qtlib


//---------------------------------------------------------------------------
// outliner::Branch_Item<Parent, Children>
//---------------------------------------------------------------------------
// Subclass of abstract::Item which is in the middle of the tree. Item may have
// differenct distinct types for the parent and children, so long as they are
// both subclasses of abstract::Item.

// Special 6
//============================================================
template <typename P, typename C>
qtlib::outliner::Branch_Item<P,C>::Branch_Item(parent_type* a_parent):
    Parented_Item<P>(a_parent),
    m_children{}
{}

template <typename P, typename C>
qtlib::outliner::Branch_Item<P,C>::~Branch_Item() = default;

// Virtual Interface
//============================================================

// Children
//----------------------------------------
// Does this item have any child items?
template <typename P, typename C>
bool qtlib::outliner::Branch_Item<P,C>::has_children() const
{
    return !m_children.empty();
}
// The number of children this item has
template <typename P, typename C>
int qtlib::outliner::Branch_Item<P,C>::get_child_count() const
{
    return static_cast<int>(m_children.size());
}

// Does this item have a child item at this index?
template <typename P, typename C>
bool qtlib::outliner::Branch_Item<P,C>::has_child_at(int a_index) const
{
    return a_index >= 0 && a_index < static_cast<int>(m_children.size());
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename P, typename C>
typename qtlib::outliner::Branch_Item<P,C>::item_type* qtlib::outliner::Branch_Item<P,C>::get_child_at(int a_index) const
{
    return m_children.at(a_index).get();
}


// Additional Interface
//============================================================
template <typename P, typename C>
typename qtlib::outliner::Branch_Item<P,C>::child_type* qtlib::outliner::Branch_Item<P,C>::get_true_child_at(int a_index) const
{
    return m_children.at(a_index).get();
}

template <typename P, typename C>
void qtlib::outliner::Branch_Item<P,C>::append_child(std::unique_ptr<child_type>&& a_item)
{
    m_children.push_back(std::move(a_item));
}

template <typename P, typename C>
void qtlib::outliner::Branch_Item<P,C>::insert_child(std::size_t a_index, std::unique_ptr<child_type>&& a_item)
{
    auto l_position = m_children.begin();
    std::advance(l_position, a_index);
    m_children.insert(l_position, std::move(a_item));
}

template <typename P, typename C>
void qtlib::outliner::Branch_Item<P,C>::remove_last_child()
{
    m_children.pop_back();
}

template <typename P, typename C>
void qtlib::outliner::Branch_Item<P,C>::remove_child(std::size_t a_index)
{
    auto l_position = m_children.begin();
    std::advance(l_position, a_index);
    l_position->reset();
    m_children.erase(l_position);
}

//---------------------------------------------------------------------------
// outliner::Readonly_Branch_Item<Parent, Children>
//---------------------------------------------------------------------------
// Subclass of Branch_Item<Parent, Children> with the write interface
// implemented as dummy functions. This exists to solve multiple inheritance
// problems if you want to use features together.

// Special 6
//============================================================
template <typename P, typename C>
qtlib::outliner::Readonly_Branch_Item<P,C>::Readonly_Branch_Item(parent_type* a_parent):
    Branch_Item<P,C>(a_parent)
{}

template <typename P, typename C>
qtlib::outliner::Readonly_Branch_Item<P,C>::~Readonly_Branch_Item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Set the data in item with the given value
template <typename P, typename C>
void qtlib::outliner::Readonly_Branch_Item<P,C>::set_data(QVariant const& a_value)
{
    this->abstract::Item::set_data(a_value);
}

// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
template <typename P, typename C>
QWidget* qtlib::outliner::Readonly_Branch_Item<P,C>::get_editor(QWidget* a_parent)
{
    return this->abstract::Item::get_editor(a_parent);
}
// Set the data in the editor to the value in the item
template <typename P, typename C>
void qtlib::outliner::Readonly_Branch_Item<P,C>::set_editor_data(QWidget* a_editor)
{
    this->abstract::Item::set_editor_data(a_editor);
}
// Get the data in the editor and return it
template <typename P, typename C>
QVariant qtlib::outliner::Readonly_Branch_Item<P,C>::get_editor_data(QWidget* a_editor)
{
    return this->abstract::Item::get_editor_data(a_editor);
}

// Other
//----------------------------------------
// Get the flags for this item
template <typename P, typename C>
Qt::ItemFlags qtlib::outliner::Readonly_Branch_Item<P,C>::get_flags() const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


#endif // OUTLINER_ITEM_HPP
