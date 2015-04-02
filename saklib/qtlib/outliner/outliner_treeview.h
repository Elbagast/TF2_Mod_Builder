#ifndef OUTLINER_TREEVIEW_H
#define OUTLINER_TREEVIEW_H

#include <QTreeView>
#include "../../types.h"

namespace Saklib
{
    namespace Qtlib
    {
        /*
        Outliner_Treeview
        ====================================================================================================
        Class derived from QTreeView for use with Outliner_Model which provides the capability to request a
        custom context menu for a QModelIndex when the model for it is an Outliner_Model. It also has some
        default settings that need to be reapplied whenever the model is updated (annoying).
        */

        class Outliner_Treeview :
                public QTreeView
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            explicit Outliner_Treeview(QWidget *parent = nullptr);
            ~Outliner_Treeview() override;

            // Adding additional behaviour
            void setModel(QAbstractItemModel * newModel) override;

            void cache_expanded_indexes();
            void restore_expanded_indexes();

        public slots:
            // Slots
            //============================================================
            // Connected to this->customContextMenuRequested
            void slot_customContextMenuRequested(QPoint const& pos);

        protected:
            // Virtual Overrides
            //============================================================
            // Added behaviour when adding rows
            void rowsInserted(QModelIndex const& parent, int start, int end) override;

            // To add opening edtitors on double-click
            void mouseDoubleClickEvent(QMouseEvent* mouse_event) override;

        private:
            // Convenience
            //============================================================
            // Called on construction and after the model is changed
            void applySettings();

            Vector<QModelIndex> m_expanded_indexes;
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // OUTLINER_TREEVIEW_H
