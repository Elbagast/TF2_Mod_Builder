#ifndef SAK_OUTLINER_DELEGATE_HPP
#define SAK_OUTLINER_DELEGATE_HPP

#ifndef SAK_OUTLINER_DELEGATE_FWD_HPP
#include "outliner_delegate_fwd.hpp"
#endif

#ifndef INCLUDE_QT_QITEMDELEGATE
#define INCLUDE_QT_QITEMDELEGATE
#include <QItemDelegate>
#endif

namespace sak
{
  //---------------------------------------------------------------------------
  // Outliner_Delegate
  //---------------------------------------------------------------------------
  // Delegate class for Model which provides the ability to use specific
  // editors. It forwards functions to Outliner_Item which have virtual implementations.

  class Outliner_Delegate :
      public QItemDelegate
  {
    Q_OBJECT
  public:
    // Special 6
    //============================================================
    explicit Outliner_Delegate(QWidget* a_parent = nullptr);
    ~Outliner_Delegate() override;

    // Virtual Overrides
    //============================================================
    QWidget* createEditor(QWidget* a_parent,  QStyleOptionViewItem const& a_option, QModelIndex const& a_index) const override;

    void setEditorData(QWidget* a_editor,  QModelIndex const& a_index) const override;
    void setModelData(QWidget* a_editor, QAbstractItemModel* a_model,  QModelIndex const& a_index) const override;

    void updateEditorGeometry(QWidget* a_editor, QStyleOptionViewItem const& a_option, QModelIndex const& a_index) const override;
  };
} // namespace sak

#endif // SAK_OUTLINER_DELEGATE_HPP
