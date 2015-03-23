#ifndef OUTLINER_TREEVIEW_H
#define OUTLINER_TREEVIEW_H
/*
Outliner_Treeview
======================================
Class derived from QTreeView for use with Outliner_Model which provides the capability
to act on custom context menus for Outliner_Item classes. There is also some custom
behaviour for adding items, and there may be more in the future - it depends what has
to be done here.
*/

#include <QTreeView>
#include <memory>

namespace Saklib
{
    namespace Qtlib
    {

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

        private:
            // Convenience
            //============================================================
            // Called on construction and after the model is changed
            void applySettings();
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // OUTLINER_TREEVIEW_H
