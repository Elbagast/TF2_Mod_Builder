#ifndef QTLIB_OUTLINER_DELEGATE_HPP
#define QTLIB_OUTLINER_DELEGATE_HPP

#include <QItemDelegate>

namespace qtlib
{
    namespace outliner
    {
        //---------------------------------------------------------------------------
        // outliner::Delegate
        //---------------------------------------------------------------------------
        // Delegate class for Model which provides the ability to use specific
        // editors. It forwards functions to Outliner_Item which have virtual implementations.

        class Delegate :
                public QItemDelegate
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            explicit Delegate(QWidget* a_parent = nullptr);
            ~Delegate() override;

            // Virtual Overrides
            //============================================================
            QWidget* createEditor(QWidget* a_parent,  QStyleOptionViewItem const& a_option, QModelIndex const& a_index) const override;

            void setEditorData(QWidget* a_editor,  QModelIndex const& a_index) const override;
            void setModelData(QWidget* a_editor, QAbstractItemModel* a_model,  QModelIndex const& a_index) const override;

            void updateEditorGeometry(QWidget* a_editor, QStyleOptionViewItem const& a_option, QModelIndex const& a_index) const override;
        };
    }
} // namespace qtlib

#endif // QTLIB_OUTLINER_DELEGATE_HPP
