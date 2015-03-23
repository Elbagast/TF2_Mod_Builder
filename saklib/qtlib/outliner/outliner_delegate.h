#ifndef OUTLINER_DELEGATE_H
#define OUTLINER_DELEGATE_H

#include <QItemDelegate>
class QAbstractItemModel;

namespace Saklib
{
    namespace Qtlib
    {
        /*
        Outliner_Delegate
        ======================================
        Delegate class for Outliner_Model which provides the ability to use specific editors. It forwards
        functions to Proxy_Interface which have virtual implementations.
         */

        class Outliner_Delegate :
                public QItemDelegate
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            explicit Outliner_Delegate(QWidget* parent = nullptr);
            ~Outliner_Delegate() override;

            // Virtual Overrides
            //============================================================
            QWidget* createEditor(QWidget* parent,  QStyleOptionViewItem const& option, QModelIndex const& index) const override;

            void setEditorData(QWidget* editor,  QModelIndex const& index) const override;
            void setModelData(QWidget* editor, QAbstractItemModel* model,  QModelIndex const& index) const override;

            void updateEditorGeometry(QWidget* editor, QStyleOptionViewItem const& option, QModelIndex const& index) const override;
        };
    } // namespace Qtlib
} // namespace Saklib

#endif // OUTLINER_DELEGATE_H
