#ifndef OUTLINER_OPERATIONS_H
#define OUTLINER_OPERATIONS_H

class QModelIndex;

namespace Saklib
{
    namespace Qtlib
    {
        class Outliner_Model;

        /*
        Outliner_Row_Inserter
        ====================================================================================================
        Delegate class for Outliner_Model which provides the ability to use specific editors. At the moment
        it only allows editing on Element names via a QLineEdit widget.
         */

        class Outliner_Row_Inserter
        {
        public:
            // Special 6
            //============================================================
            Outliner_Row_Inserter(Outliner_Model* model, QModelIndex const& index, int start_row, int row_count);
            ~Outliner_Row_Inserter();
        private:
            Outliner_Model* mp_outliner_model;
        };

        class Outliner_Row_Remover
        {
        public:
            // Special 6
            //============================================================
            Outliner_Row_Remover(Outliner_Model* model, QModelIndex const& index, int start_row, int row_count);
            ~Outliner_Row_Remover();
        private:
            Outliner_Model* mp_outliner_model;
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // OUTLINER_OPERATIONS_H
