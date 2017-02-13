#ifndef OUTLINER_TREEVIEW_H
#define OUTLINER_TREEVIEW_H

#include <QTreeView>

namespace qtlib
{
    namespace outliner
    {
        class Model;

        //---------------------------------------------------------------------------
        // outliner::Treeview
        //---------------------------------------------------------------------------
        // Class derived from QTreeView for use with Model which provides the capability
        // to act on custom context menus for abstract::Item classes. There is also some custom
        // behaviour for adding items, and there may be more in the future - it depends what has
        // to be done here.

        class Treeview :
                public QTreeView
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            explicit Treeview(QWidget* a_parent = nullptr);
            ~Treeview() override;

            // Since there is a bunch of additional behaviour, this is a new
            // function that will apply it and also limit the type of model
            // that can be used.
            void set_model(Model* a_model);

        public slots:
            // Slots
            //============================================================
            // Connected to this->customContextMenuRequested
            void slot_custom_context_menu_requested(QPoint const& a_position);

        protected:
            // Virtual Overrides
            //============================================================
            // Added behaviour when adding rows
            void rowsInserted(QModelIndex const& a_parent, int a_start, int a_end) override;

        private:
            // hide this since it is effectively replaced.
            using QTreeView::setModel;

            // Convenience
            //============================================================
            // Called on construction and after the model is changed
            void apply_settings();
        };
    }


} // namespace qtlib

#endif // OUTLINER_TREEVIEW_H
