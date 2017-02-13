#ifndef OUTLINER_ABSTRACT_ITEM_H
#define OUTLINER_ABSTRACT_ITEM_H

#include <Qt> // for Qt::ItemFlags

class QPoint;
class QVariant;
class QWidget;
class QModelIndex;
class QAbstractItemView;

namespace qtlib
{
    namespace outliner
    {
        class Model;

        namespace abstract
        {
            //---------------------------------------------------------------------------
            // outliner::abstract::Item
            //---------------------------------------------------------------------------
            // Defines the interface used by outliner::Model, outliner::delegate and
            // outliner::View_Widget. There is only ever one column.
            // Subclass this and create a tree Item subclasses.

            class Item
            {
            public:
                using item_type = Item;
                using model_type = Model;

                // Special 6
                //============================================================
                virtual ~Item() = 0;

                // Virtual Interface
                //============================================================
                // Parent
                //----------------------------------------
                // Does this item have a parent item?
                virtual bool has_parent() const = 0;
                // Get the item that is the parent of this
                virtual item_type* get_parent() const = 0;
                // Get the item at the root of the structure
                virtual item_type* get_root() const = 0;
                // The row that this item is in relative to the parent e.g. if the parent has
                // 5 children, and this is the third, then row is 2. If this has no parent
                // then -1 is returned.
                virtual int index_in_parent() const = 0;

                // Children
                //----------------------------------------
                // Does this item have any child items?
                virtual bool has_children() const = 0;
                // The number of child items this item has
                virtual int get_child_count() const = 0;
                // Does this item have a child item at this index?
                virtual bool has_child_at(int a_index) const = 0;
                // Get the child at a given row, return nullptr if there is no child at the index
                virtual item_type* get_child_at(int a_index) const = 0;

                // Underlying data access
                //----------------------------------------
                // Get the item data for a given column and role
                virtual QVariant get_data(int a_role = Qt::DisplayRole) const = 0;
                // Set the data in item with the given value
                virtual void set_data(QVariant const& a_value) = 0;

                // Editors
                //----------------------------------------
                // Make the appropriate editor for this item, parenting it to parent
                virtual QWidget* get_editor(QWidget* a_parent) = 0;
                // Set the data in the editor to the value in the item
                virtual void set_editor_data(QWidget* a_editor) = 0;
                // Get the data in the editor and return it
                virtual  QVariant get_editor_data(QWidget* a_editor) = 0;

                // Other
                //----------------------------------------
                // Get the flags for this item
                virtual Qt::ItemFlags get_flags() const = 0;
                // Make and act on the context menu for this item. Need the model pointer here so that
                // actions can call functions in it for editing
                virtual void do_custom_context_menu(QAbstractItemView* a_view, model_type* a_model, QPoint const& a_point) = 0;

                // Encapsulate the casting of the void* stored in index to Item*
                static item_type* from_index(QModelIndex const& a_index);
            };

        } // namespace abstract
    } // namespace outliner
} // namespace qtlib

#endif // OUTLINER_ABSTRACT_ITEM_H
