#include "outliner_operations.h"
#include "outliner_model.h"
#include "outliner_treeview.h"

Saklib::Qtlib::Outliner_Model_Row_Inserter::Outliner_Model_Row_Inserter(Outliner_Model* model, QModelIndex const& index, int row):
    mp_outliner_model(model)
{
    mp_outliner_model->beginInsertRows(index, row, row);
}

Saklib::Qtlib::Outliner_Model_Row_Inserter::Outliner_Model_Row_Inserter(Outliner_Model* model, QModelIndex const& index, int start_row, int end_row):
    mp_outliner_model(model)
{
    mp_outliner_model->beginInsertRows(index, start_row, end_row);
}

Saklib::Qtlib::Outliner_Model_Row_Inserter::~Outliner_Model_Row_Inserter()
{
    mp_outliner_model->endInsertRows();
}

// Special 6
//============================================================
Saklib::Qtlib::Outliner_Model_Row_Remover::Outliner_Model_Row_Remover(Outliner_Model* model, QModelIndex const& index, int row):
    mp_outliner_model(model)
{
    mp_outliner_model->beginRemoveRows(index, row, row);
}
Saklib::Qtlib::Outliner_Model_Row_Remover::Outliner_Model_Row_Remover(Outliner_Model* model, QModelIndex const& index, int start_row, int end_row):
    mp_outliner_model(model)
{
    mp_outliner_model->beginRemoveRows(index, start_row, end_row);
}
Saklib::Qtlib::Outliner_Model_Row_Remover::~Outliner_Model_Row_Remover()
{
    mp_outliner_model->endRemoveRows();
}


// Special 6
//============================================================
Saklib::Qtlib::Outliner_Model_Reseter::Outliner_Model_Reseter(Outliner_Model* model):
    mp_outliner_model(model)
{
    mp_outliner_model->beginResetModel();
}
Saklib::Qtlib::Outliner_Model_Reseter::~Outliner_Model_Reseter()
{
    mp_outliner_model->endResetModel();
}


// Special 6
//============================================================
Saklib::Qtlib::Outliner_Refresh::Outliner_Refresh(Outliner_Model* outliner_model, Outliner_Treeview* outliner_view):
    mp_outliner_model(outliner_model),
    mp_outliner_view(outliner_view),
    m_expanded_indexes()
{
    auto all_indexes = mp_outliner_model->all_indexes();
    for (auto const& index : all_indexes)
    {
        if (mp_outliner_view->isExpanded(index))
        {
            m_expanded_indexes.push_back(index);
        }
    }
    mp_outliner_model->beginResetModel();
}
Saklib::Qtlib::Outliner_Refresh::~Outliner_Refresh()
{
    mp_outliner_model->endResetModel();
    for (auto const& index : m_expanded_indexes)
    {
        if (mp_outliner_model->hasIndex(index.row(), index.column(), index.parent()))
        {
            mp_outliner_view->setExpanded(index, true);
        }
    }
}
