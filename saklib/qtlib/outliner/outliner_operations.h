#ifndef OUTLINER_OPERATIONS_H
#define OUTLINER_OPERATIONS_H

#include "../../types.h"
class QModelIndex;

namespace Saklib
{
    namespace Qtlib
    {
        class Outliner_Model;
        class Outliner_Treeview;

        /*
        Outliner_Model_Row_Inserter
        ====================================================================================================
        Class which starts and stops a row insertion on the given Outliner_Model based on this object's
        lifetime.
         */

        class Outliner_Model_Row_Inserter
        {
        public:
            // Special 6
            //============================================================
            Outliner_Model_Row_Inserter(Outliner_Model* model, QModelIndex const& index, int row);
            Outliner_Model_Row_Inserter(Outliner_Model* model, QModelIndex const& index, int start_row, int end_row);
            ~Outliner_Model_Row_Inserter();
        private:
            Outliner_Model* mp_outliner_model;
        };

        /*
        Outliner_Model_Row_Remover
        ====================================================================================================
        Class which starts and stops a row removal on the given Outliner_Model based on this object's
        lifetime.
         */

        class Outliner_Model_Row_Remover
        {
        public:
            // Special 6
            //============================================================
            Outliner_Model_Row_Remover(Outliner_Model* model, QModelIndex const& index, int row);
            Outliner_Model_Row_Remover(Outliner_Model* model, QModelIndex const& index, int start_row, int end_row);
            ~Outliner_Model_Row_Remover();
        private:
            Outliner_Model* mp_outliner_model;
        };

        /*
        Outliner_Model_Reseter
        ====================================================================================================
        Class which starts and stops a reset on the given Outliner_Model based on this object's lifetime.
         */

        class Outliner_Model_Reseter
        {
        public:
            // Special 6
            //============================================================
            explicit Outliner_Model_Reseter(Outliner_Model* model);
            ~Outliner_Model_Reseter();
        private:
            Outliner_Model* mp_outliner_model;
        };

        /*
        Outliner_Refresh
        ====================================================================================================
        Class which starts and stops a reset on the given Outliner_Model based on this object's lifetime,
        whilst also capturing the expansion properties of the given Outliner_Treeview and restoring them
        based on this object's lifetime,
         */

        class Outliner_Refresh
        {
        public:
            // Special 6
            //============================================================
            Outliner_Refresh(Outliner_Model* outliner_model, Outliner_Treeview* outliner_view);
            ~Outliner_Refresh();
        private:
            Outliner_Model* mp_outliner_model;
            Outliner_Treeview* mp_outliner_view;
            Vector<QModelIndex> m_expanded_indexes;
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // OUTLINER_OPERATIONS_H
