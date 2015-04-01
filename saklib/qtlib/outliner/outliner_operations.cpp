#include "outliner_operations.h"
#include "outliner_model.h"

Saklib::Qtlib::Outliner_Row_Inserter::Outliner_Row_Inserter(Outliner_Model* model, QModelIndex const& index, int row):
    mp_outliner_model(model)
{
    mp_outliner_model->beginInsertRows(index, row, row);
}

Saklib::Qtlib::Outliner_Row_Inserter::Outliner_Row_Inserter(Outliner_Model* model, QModelIndex const& index, int start_row, int end_row):
    mp_outliner_model(model)
{
    mp_outliner_model->beginInsertRows(index, start_row, end_row);
}

Saklib::Qtlib::Outliner_Row_Inserter::~Outliner_Row_Inserter()
{
    mp_outliner_model->endInsertRows();
}

// Special 6
//============================================================
Saklib::Qtlib::Outliner_Row_Remover::Outliner_Row_Remover(Outliner_Model* model, QModelIndex const& index, int row):
    mp_outliner_model(model)
{
    mp_outliner_model->beginRemoveRows(index, row, row);
}
Saklib::Qtlib::Outliner_Row_Remover::Outliner_Row_Remover(Outliner_Model* model, QModelIndex const& index, int start_row, int end_row):
    mp_outliner_model(model)
{
    mp_outliner_model->beginRemoveRows(index, start_row, end_row);
}
Saklib::Qtlib::Outliner_Row_Remover::~Outliner_Row_Remover()
{
    mp_outliner_model->endRemoveRows();
}
