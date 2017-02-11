#ifndef OUTLINER_ITEM_ROOT_H
#define OUTLINER_ITEM_ROOT_H


class Outliner_Item_Root
{
public:
    Outliner_Item_Root();
};


#include "outliner_item.h"

namespace qtlib
{
    //---------------------------------------------------------------------------
    // Outliner_Item_Root
    //---------------------------------------------------------------------------
    // Derived class of Outliner_Item which provides dummy implementations of all
    // functions that do nothing and are final. Inherit this to make it clear
    // what you are doing, and so your root (invisible) item doesn't do anything.

    class Outliner_Item_Root :
            public Outliner_Item
    {
    public:
        // Special 6
        //============================================================
        Outliner_Item_Root();
        ~Outliner_Item_Root() override;

    protected:
        // Virtuals
        //============================================================

        // Underlying data access
        QVariant v_get_data(int a_role) const override final;
        void v_set_data(QVariant const& a_value) override final;

        // Editors
        QWidget* v_get_editor(QWidget* a_parent) override final;
        void v_set_editor_data(QWidget* a_editor) override final;
        QVariant v_get_editor_data(QWidget* a_editor) override final;

        // Other
        Qt::ItemFlags v_flags() const override final;
        void v_custom_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position) override final;
    };
} // namespace qtlib



#endif // OUTLINER_ITEM_ROOT_H
