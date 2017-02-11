#include "outliner_item_readonly.h"
#include <QVariant>

//---------------------------------------------------------------------------
// Outliner_Item_ReadOnly
//---------------------------------------------------------------------------
// Derived class of Outliner_Item which provides dummy implementations of write
// access functions that do nothing and are final. Inherit this to make it clear
// what you are doing, and so you only need to provide what is needed in read
// only cases.

// Special 6
//============================================================
qtlib::Outliner_Item_ReadOnly::Outliner_Item_ReadOnly(Outliner_Item* a_parent):
    Outliner_Item(a_parent)
{
}
qtlib::Outliner_Item_ReadOnly::~Outliner_Item_ReadOnly() = default;

// Virtuals
//============================================================
// Underlying data access

void qtlib::Outliner_Item_ReadOnly::v_set_data(QVariant const& a_value)
{
    // Dummy implementation
    return this->Outliner_Item::v_set_data(a_value);
}

// Editors

QWidget* qtlib::Outliner_Item_ReadOnly::v_get_editor(QWidget* a_parent)
{
    // Dummy implementation
    return this->Outliner_Item::v_get_editor(a_parent);
}

void qtlib::Outliner_Item_ReadOnly::v_set_editor_data(QWidget* a_editor)
{
    // Dummy implementation
    this->Outliner_Item::v_get_editor_data(a_editor);
}

QVariant qtlib::Outliner_Item_ReadOnly::v_get_editor_data(QWidget* a_editor)
{
    // Dummy implementation
    return this->Outliner_Item::v_get_editor_data(a_editor);
}

// Other

Qt::ItemFlags qtlib::Outliner_Item_ReadOnly::v_flags() const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
