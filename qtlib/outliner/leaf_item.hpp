#ifndef OUTLINER_LEAF_ITEM_HPP
#define OUTLINER_LEAF_ITEM_HPP

#include "parented_item.hpp"
#include <vector>
#include <memory>
//#include <type_traits>
#include <QVariant>

namespace qtlib
{
    namespace outliner
    {
        //---------------------------------------------------------------------------
        // outliner::Leaf_Item<Parent>
        //---------------------------------------------------------------------------
        // Subclass of abstract::Item which is at the end of a tree (i.e. it never
        // has any children).

        template <typename P>
        class Leaf_Item :
                public Parented_Item<P>
        {
        public:
            using item_type = typename Parented_Item<P>::item_type;
            using model_type = typename Parented_Item<P>::model_type;

            using parent_type = typename Parented_Item<P>::parent_type;

            //static_assert(std::is_base_of<abstract::Item, parent_type>::value, "parent_type must inherit qtlib::outliner::abstract::Item");

            // Special 6
            //============================================================
            explicit Leaf_Item(parent_type* a_parent);
            ~Leaf_Item() override;

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
            // actions can call functions in it for editing
            void do_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_position) override = 0;
            // Do whatever we want when an item has been double clicked on.
            void do_double_clicked(QAbstractItemView* a_view, model_type* a_model) override = 0;

        //protected:
            // Additional Interface
            //============================================================
            using Parented_Item<P>::get_true_parent;
            using Parented_Item<P>::set_parent;
        };

        //---------------------------------------------------------------------------
        // outliner::Readonly_Leaf_Item<Parent>
        //---------------------------------------------------------------------------
        // Subclass of Leaf_Item<Parent> with the write interface implemented as
        // dummy functions. This exists to solve multiple inheritance problems if
        // you want to use features together.

        template <typename P>
        class Readonly_Leaf_Item :
                public Leaf_Item<P>
        {
        public:
            using item_type = typename Leaf_Item<P>::item_type;
            using model_type = typename Leaf_Item<P>::model_type;

            using parent_type = typename Leaf_Item<P>::parent_type;

            // Special 6
            //============================================================
            explicit Readonly_Leaf_Item(parent_type* a_parent);
            ~Readonly_Leaf_Item() override;

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
            using Leaf_Item<P>::get_true_parent;
            using Leaf_Item<P>::set_parent;
        };
    } // namespace outliner
} // namespace qtlib

//---------------------------------------------------------------------------
// outliner::Leaf_Item<Parent>
//---------------------------------------------------------------------------
// Subclass of abstract::Item which is at the end of a tree (i.e. it never
// has any children).

// Special 6
//============================================================
template <typename P>
qtlib::outliner::Leaf_Item<P>::Leaf_Item(parent_type* a_parent):
    Parented_Item<P>(a_parent)
{}

template <typename P>
qtlib::outliner::Leaf_Item<P>::~Leaf_Item() = default;

// Virtual Interface
//============================================================
// Children
//----------------------------------------
// Does this item have any child items?
template <typename P>
bool qtlib::outliner::Leaf_Item<P>::has_children() const
{
    return false;
}
// The number of children this item has
template <typename P>
int qtlib::outliner::Leaf_Item<P>::get_child_count() const
{
    return 0;
}

// Does this item have a child item at this index?
template <typename P>
bool qtlib::outliner::Leaf_Item<P>::has_child_at(int /*a_index*/) const
{
    return false;
}
// Get the child at a given row, return nullptr if there is no child at row
template <typename P>
typename qtlib::outliner::Leaf_Item<P>::item_type* qtlib::outliner::Leaf_Item<P>::get_child_at(int /*a_index*/) const
{
    return nullptr;
}


//---------------------------------------------------------------------------
// outliner::Readonly_Leaf_Item<Parent>
//---------------------------------------------------------------------------
// Subclass of Leaf_Item<Parent> with the write interface implemented as
// dummy functions. This exists to solve multiple inheritance problems if
// you want to use features together.

// Special 6
//============================================================
template <typename P>
qtlib::outliner::Readonly_Leaf_Item<P>::Readonly_Leaf_Item(parent_type* a_parent):
    Leaf_Item<P>(a_parent)
{}

template <typename P>
qtlib::outliner::Readonly_Leaf_Item<P>::~Readonly_Leaf_Item() = default;

// Virtual Interface
//============================================================
// Underlying data access
//----------------------------------------
// Set the data in item with the given value
template <typename P>
void qtlib::outliner::Readonly_Leaf_Item<P>::set_data(QVariant const& a_value)
{
    this->abstract::Item::set_data(a_value);
}

// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
template <typename P>
QWidget* qtlib::outliner::Readonly_Leaf_Item<P>::get_editor(QWidget* a_parent)
{
    return this->abstract::Item::get_editor(a_parent);
}
// Set the data in the editor to the value in the item
template <typename P>
void qtlib::outliner::Readonly_Leaf_Item<P>::set_editor_data(QWidget* a_editor)
{
    this->abstract::Item::set_editor_data(a_editor);
}
// Get the data in the editor and return it
template <typename P>
QVariant qtlib::outliner::Readonly_Leaf_Item<P>::get_editor_data(QWidget* a_editor)
{
    return this->abstract::Item::get_editor_data(a_editor);
}

// Other
//----------------------------------------
// Get the flags for this item
template <typename P>
Qt::ItemFlags qtlib::outliner::Readonly_Leaf_Item<P>::get_flags() const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}



#endif // OUTLINER_LEAF_ITEM_HPP
