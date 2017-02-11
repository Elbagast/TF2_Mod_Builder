#ifndef OUTLINER_ITEM_READONLY_H
#define OUTLINER_ITEM_READONLY_H

#include "outliner_item.h"

namespace qtlib
{
    //---------------------------------------------------------------------------
    // Outliner_Item_ReadOnly
    //---------------------------------------------------------------------------
    // Derived class of Outliner_Item which provides dummy implementations of write
    // access functions that do nothing and are final. Inherit this to make it clear
    // what you are doing, and so you only need to provide what is needed in read
    // only cases.

    class Outliner_Item_ReadOnly :
            public Outliner_Item
    {
    public:
        // Special 6
        //============================================================
        explicit Outliner_Item_ReadOnly(Outliner_Item* parent = nullptr);
        ~Outliner_Item_ReadOnly() override;

    protected:
        // Virtuals
        //============================================================

        // Underlying data access
        QVariant v_get_data(int a_role) const override = 0;
        void v_set_data(QVariant const& a_value) override final;

        // Editors
        QWidget* v_get_editor(QWidget* a_parent) override final;
        void v_set_editor_data(QWidget* a_editor) override final;
        QVariant v_get_editor_data(QWidget* a_editor) override final;

        // Other
        Qt::ItemFlags v_flags() const override final;
        void v_custom_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) override = 0;
    };
} // namespace qtlib

#endif // OUTLINER_ITEM_READONLY_H
