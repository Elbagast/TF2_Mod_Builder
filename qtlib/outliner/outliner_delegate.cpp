#include "outliner_delegate.h"
#include "outliner_abstract_item.h"

//---------------------------------------------------------------------------
// outliner::Delegate
//---------------------------------------------------------------------------
// Delegate class for Outliner_Model which provides the ability to use specific
// editors. It forwards functions to Outliner_Item which have virtual implementations.

// Special 6
//============================================================
qtlib::outliner::Delegate::Delegate(QWidget* a_parent):
    QItemDelegate(a_parent)
{
}
qtlib::outliner::Delegate::~Delegate() = default;

// Virtual Overrides
//============================================================
QWidget* qtlib::outliner::Delegate::createEditor(QWidget* a_parent, QStyleOptionViewItem const& /*a_option*/, QModelIndex const& a_index) const
{
    // Assuming the model using the delegate does its own sanity checks
    if (!a_index.isValid())
    {
        return nullptr;
    }
    // casting required to get around const, then upcast to the right type
    auto l_true_item = abstract::Item::from_index(a_index);
    if (l_true_item)
    {
        return l_true_item->get_editor(a_parent); // virtual func
    }
    else
    {
        return nullptr;
    }
}

void qtlib::outliner::Delegate::setEditorData(QWidget* a_editor, QModelIndex const& a_index) const
{
    if (!a_index.isValid())
    {
        return;
    }
    // casting required to get around const, then upcast to the right type
    auto true_item = abstract::Item::from_index(a_index);
    if (true_item)
    {
        true_item->set_editor_data(a_editor); // virtual func
    }
}

void qtlib::outliner::Delegate::setModelData(QWidget* editor, QAbstractItemModel* a_model, QModelIndex const& a_index) const
{
    auto true_item = abstract::Item::from_index(a_index);
    a_model->setData(a_index, true_item->get_editor_data(editor), Qt::EditRole);  // using virtual func
}

void qtlib::outliner::Delegate::updateEditorGeometry(QWidget *a_editor, QStyleOptionViewItem const& a_option, QModelIndex const& /*a_index*/) const
{
    a_editor->setGeometry(a_option.rect);
}