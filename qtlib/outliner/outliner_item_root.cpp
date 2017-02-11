#include "outliner_item_root.h"
#include <QVariant>

//---------------------------------------------------------------------------
// Outliner_Item_Root
//---------------------------------------------------------------------------
// Derived class of Outliner_Item which provides dummy implementations of all
// functions that do nothing and are final. Inherit this to make it clear
// what you are doing, and so your root (invisible) item doesn't do anything.

// Special 6
//============================================================
qtlib::Outliner_Item_Root::Outliner_Item_Root():
    Outliner_Item(nullptr)
{
}
qtlib::Outliner_Item_Root::~Outliner_Item_Root() = default;

// Virtuals
//============================================================
// Underlying data access

QVariant qtlib::Outliner_Item_Root::v_get_data(int a_role) const
{
    // Dummy implementation
    return this->Outliner_Item::v_get_data(a_role);
}

void qtlib::Outliner_Item_Root::v_set_data(QVariant const& a_value)
{
    // Dummy implementation
    return this->Outliner_Item::v_set_data(a_value);
}

// Editors

QWidget* qtlib::Outliner_Item_Root::v_get_editor(QWidget* a_parent)
{
    // Dummy implementation
    return this->Outliner_Item::v_get_editor(a_parent);
}

void qtlib::Outliner_Item_Root::v_set_editor_data(QWidget* a_editor)
{
    // Dummy implementation
    this->Outliner_Item::v_get_editor_data(a_editor);
}

QVariant qtlib::Outliner_Item_Root::v_get_editor_data(QWidget* a_editor)
{
    // Dummy implementation
    return this->Outliner_Item::v_get_editor_data(a_editor);
}

// Other

Qt::ItemFlags qtlib::Outliner_Item_Root::v_flags() const
{
    // Dummy implementation
    return this->Outliner_Item::v_flags();
}

void qtlib::Outliner_Item_Root::v_custom_context_menu(QAbstractItemView* a_view, Outliner_Model* a_model, QPoint const& a_position)
{
    // Dummy implementation
    return this->Outliner_Item::v_custom_context_menu(a_view, a_model,a_position);
}
