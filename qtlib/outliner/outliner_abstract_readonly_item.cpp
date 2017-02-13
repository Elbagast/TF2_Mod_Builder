#include "outliner_abstract_readonly_item.h"

#include <QVariant>

//---------------------------------------------------------------------------
// outliner::abstract::Readonly_Item
//---------------------------------------------------------------------------
// Abstract subclass of abstract::Item. Subclass from this for items that will
// not be editable inside the outliner. Write functions are finalised with
// dummy implemenations.

// Special 6
//============================================================
qtlib::outliner::abstract::Readonly_Item::~Readonly_Item() = default;

// Interface
//============================================================
// Set the data in item with the given value
void qtlib::outliner::abstract::Readonly_Item::set_data(QVariant const& a_value)
{
    return this->abstract::Item::set_data(a_value);
}

// Editors
//----------------------------------------
// Make the appropriate editor for this item, parenting it to parent
QWidget* qtlib::outliner::abstract::Readonly_Item::get_editor(QWidget* a_parent)
{
    return this->abstract::Item::get_editor(a_parent);
}

// Set the data in the editor to the value in the item
void qtlib::outliner::abstract::Readonly_Item::set_editor_data(QWidget* a_editor)
{
    return this->abstract::Item::set_editor_data(a_editor);
}

// Get the data in the editor and return it
QVariant qtlib::outliner::abstract::Readonly_Item::get_editor_data(QWidget* a_editor)
{
    return this->abstract::Item::get_editor_data(a_editor);
}

// Other
//----------------------------------------
// Get the flags for this item
Qt::ItemFlags qtlib::outliner::abstract::Readonly_Item::get_flags() const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
