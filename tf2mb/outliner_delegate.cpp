#include "outliner_delegate.hpp"

#include "abstract_outliner_item.hpp"

//---------------------------------------------------------------------------
// outliner::Delegate
//---------------------------------------------------------------------------
// Delegate class for Outliner_Model which provides the ability to use specific
// editors. It forwards functions to Outliner_Item which have virtual implementations.

// Special 6
//============================================================
sak::Outliner_Delegate::Outliner_Delegate(QWidget* a_parent):
  QItemDelegate(a_parent)
{
}
sak::Outliner_Delegate::~Outliner_Delegate() = default;

// Virtual Overrides
//============================================================
QWidget* sak::Outliner_Delegate::createEditor(QWidget* a_parent, QStyleOptionViewItem const& /*a_option*/, QModelIndex const& a_index) const
{
  // Assuming the model using the delegate does its own sanity checks
  if (!a_index.isValid())
  {
    return nullptr;
  }
  // casting required to get around const, then upcast to the right type
  auto l_true_item = Abstract_Outliner_Item::from_index(a_index);
  if (l_true_item)
  {
    return l_true_item->get_editor(a_parent); // virtual func
  }
  else
  {
    return nullptr;
  }
}

void sak::Outliner_Delegate::setEditorData(QWidget* a_editor, QModelIndex const& a_index) const
{
  if (!a_index.isValid())
  {
    return;
  }
  // casting required to get around const, then upcast to the right type
  auto l_true_item = Abstract_Outliner_Item::from_index(a_index);
  if (l_true_item)
  {
    l_true_item->set_editor_data(a_editor); // virtual func
  }
}

void sak::Outliner_Delegate::setModelData(QWidget* editor, QAbstractItemModel* a_model, QModelIndex const& a_index) const
{
  auto l_true_item = Abstract_Outliner_Item::from_index(a_index);
  a_model->setData(a_index, l_true_item->get_editor_data(editor), Qt::EditRole);  // using virtual func
}

void sak::Outliner_Delegate::updateEditorGeometry(QWidget *a_editor, QStyleOptionViewItem const& a_option, QModelIndex const& /*a_index*/) const
{
  a_editor->setGeometry(a_option.rect);
}
