#ifndef OUTLINER_ITEM_H
#define OUTLINER_ITEM_H

#include <vector>
#include <memory>
#include <Qt> // for Qt::ItemFlags

class QPoint;
class QVariant;
class QWidget;
class QModelIndex;
class QAbstractItemView;

namespace qtlib
{
    class Outliner_Model;

    //---------------------------------------------------------------------------
    // Outliner_Item
    //---------------------------------------------------------------------------
    // Defines the interface used by Outliner_Model for actions specific to the
    // model. There is only ever one column. Subclass this and create a Outliner_Item
    // hierarchy that the model will use in order to do all the crap it needs to do.
    //
    // Basically you are creating an adapter for your data.

    class Outliner_Item
    {
    public:
        // Special 6
        //============================================================
        explicit Outliner_Item(Outliner_Item* a_parent = nullptr);
        virtual ~Outliner_Item();

        // Interface
        //============================================================
        // Reparent this
        void set_parent(Outliner_Item* parent);
        // Get the item that is the parent of this
        Outliner_Item* get_parent() const;
        // Get the item at the root of the structure
        Outliner_Item* get_root() const;
        // Get the child at a given row, return nullptr if there is no child at row
        Outliner_Item* get_child(int a_row) const;
        // Add a new child, setting its parent to this
        void append_child(std::unique_ptr<Outliner_Item>&& a_child);
        // Remove all children
        void clear_children();
        // The number of children this item has
        int child_count() const;
        // The row that this item is in relative to the parent e.g. if the parent has
        // 5 children, and this is the third, then row is 2
        int row() const;

        // Underlying data access
        //----------------------------------------
        // Get the item data for a given column and role
        QVariant get_data(int a_role = Qt::DisplayRole) const;
        // Set the data in item with the given value
        void set_data(QVariant const& a_value);

        // Editors
        //----------------------------------------
        // Make the appropriate editor for this item, parenting it to parent
        QWidget* get_editor(QWidget* a_parent);
        // Set the data in the editor to the value in the item
        void set_editor_data(QWidget* a_editor);
        QVariant get_editor_data(QWidget* a_editor);

        // Other
        //----------------------------------------
        // Get the flags for this item in a given column
        Qt::ItemFlags flags() const;
        // Make and act on the context menu for this item. Need the model pointer here so that
        // actions can call functions in it for editing
        void custom_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_point);

        // Encapsulate the casting of the void* stored in index to Outliner_Item*
        static Outliner_Item* from_index(QModelIndex const& a_index);

    protected:
        // Virtuals
        //============================================================
        // While these functions are pure virtual, implementations that can serve
        // as dummies (i.e. do nothing) are provided. Thus explicitly calling them
        // means you won't have to re-provide a dummy implementation.

        // Underlying data access
        //----------------------------------------
        virtual QVariant v_get_data(int a_role) const = 0;
        virtual void v_set_data(QVariant const& a_value) = 0;

        // Editors
        //----------------------------------------
        virtual QWidget* v_get_editor(QWidget* a_parent) = 0;
        virtual void v_set_editor_data(QWidget* a_editor) = 0;
        virtual QVariant v_get_editor_data(QWidget* a_editor) = 0;

        // Other
        //----------------------------------------
        virtual Qt::ItemFlags v_flags() const = 0;
        virtual void v_custom_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) = 0;
    private:
        Outliner_Item* m_parent;
        std::vector<std::unique_ptr<Outliner_Item> > m_children;
    };
} // namespace qtlib

#endif // OUTLINER_ITEM_H
