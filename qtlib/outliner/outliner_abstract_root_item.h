#ifndef OUTLINER_ROOT_H
#define OUTLINER_ROOT_H

#include "outliner_abstract_item.h"

namespace qtlib
{
    namespace outliner
    {
        namespace abstract
        {
            //---------------------------------------------------------------------------
            // outliner::abstract::Root_Item
            //---------------------------------------------------------------------------
            // Abstract subclass of abstract::Item. Subclass from this for your root
            // (invisible) object in an outliner item tree. Functions that are part of
            // the abstract::Item interface that will not be called on the root item
            // are finalised with do-nothing implemenations. Your implemenation of
            // do_custom_context_menu is what will be carried out in the view if one is
            // requested where no item is present.

            class Root_Item :
                    public abstract::Item
            {
            public:
                using item_type = abstract::Item::item_type;
                using model_type = abstract::Item::model_type;

                // Special 6
                //============================================================
                ~Root_Item() override;

                // Virtual Interface
                //============================================================
                // Parent
                //----------------------------------------
                // Does this item have a parent item?
                bool has_parent() const override final;
                // Get the item that is the parent of this
                item_type* get_parent() const override final;
                // Get the item at the root of the structure
                item_type* get_root() const override final;
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
                item_type* get_child_at(int a_row) const override = 0;

                // Underlying data access
                //----------------------------------------
                // Get the item data for a given column and role
                QVariant get_data(int a_role = Qt::DisplayRole) const override final;
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
            };
        } // namespace abstract
    } // namespace outliner
} // namespace qtlib

#endif // OUTLINER_ROOT_H