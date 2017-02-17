#include "project_outliner.h"

#include <QHBoxLayout>
#include <QTreeView>
#include <QLabel>
#include <QDebug>
#include <cassert>

#include "file_manager.h"
#include "file_widget.h"
#include "project.h"
#include "project_signalbox.h"
#include "../qtlib/outliner/outliner_model.h"
#include "../qtlib/outliner/outliner_delegate.h"
#include "../qtlib/outliner/outliner_treeview.h"
#include "project_outliner_items.h"

//---------------------------------------------------------------------------
// Project_Outliner
//---------------------------------------------------------------------------

// Pimpl Data
//============================================================
namespace sak
{
    class Project_Outliner::Implementation :
            public Project_Signalbox
    {
    public:
        Project& m_project;
        qtlib::outliner::Model m_model;
        qtlib::outliner::Delegate m_delegate;

        std::unique_ptr<outliner::Root_Item> m_root;

        std::unique_ptr<QHBoxLayout> m_layout;
        std::unique_ptr<qtlib::outliner::Treeview> m_treeview;

        ~Implementation() override = default;

        explicit Implementation(Project& a_project):
            Project_Signalbox(),
            m_project{a_project},
            m_model{},
            m_delegate{},
            m_root{std::make_unique<outliner::Root_Item>(a_project)},
            m_layout{std::make_unique<QHBoxLayout>()},
            m_treeview{std::make_unique<qtlib::outliner::Treeview>()}
        {
            m_model.set_root(m_root.get());
            assert(m_model.is_active());
            assert(m_root->get_child_count() == 1);

            // testing the model
            assert(m_model.parent(QModelIndex()) == QModelIndex());
            assert(m_model.index(0,0,QModelIndex()).internalPointer() == m_root.get()->get_child_at(0));
            //assert(m_model.index(0,0,m_model.index(0,0,QModelIndex())).internalPointer() == m_root.get()->get_child(0));

            m_treeview->setItemDelegate(&m_delegate);
            m_treeview->set_model(&m_model);

            m_project.add_signalbox(this);

            m_layout->setSpacing(0);
            m_layout->addWidget(m_treeview.get());
        }

        // When the Files section has changed order due to a name change, this is called.
        void file_names_reordered() override final
        {
            auto l_files_item = m_root->get_true_child()->get_true_child<0>();
            auto l_file_count = l_files_item->get_child_count();
            if (l_file_count > 1)
            {
                auto l_top_left_index = m_model.create_index_from_item(l_files_item->get_true_child_at(0));
                auto l_bottom_right_index = m_model.create_index_from_item(l_files_item->get_true_child_at(l_file_count));
                m_model.data_changed(l_top_left_index, l_bottom_right_index, QVector<int>(Qt::DisplayRole));
            }
        }
        // When a File has had its name changed, this is called.
        void file_name_changed(File_Handle const&, std::size_t a_index_old, std::size_t a_index_new) override final
        {
            auto l_files_item = m_root->get_true_child()->get_true_child<0>();
            auto l_model_index = m_model.create_index_from_item(l_files_item);
            auto l_index_old = static_cast<int>(a_index_old);

            if (a_index_old == a_index_new)
            {
                // The file didn't move so do this signal
                auto l_file_index = m_model.index(l_index_old,0,l_model_index);
                m_model.data_changed(l_file_index, l_file_index, QVector<int>(Qt::DisplayRole));
            }
            else if(a_index_old > a_index_new)
            {
                // The file moved so do this signal

                auto l_mover = m_model.make_row_mover(l_model_index, l_index_old, l_model_index,static_cast<int>(a_index_new));
            }
            else if(a_index_old < a_index_new)
            {
                // The file moved so do this signal
                // As per the documentation of QAbstractItemModel::beginMoveRows, when moving a row down the
                // destination must be outside of the range (first_index, last_index+1). This means we have to
                // correct the destination
                auto l_mover = m_model.make_row_mover(l_model_index, l_index_old, l_model_index,static_cast<int>(a_index_new)+1);
            }
        }
        // When a File has its data changed(anything but the name), this is called.
        void file_data_changed(File_Handle const&, std::size_t) override final
        {
            // don't care about data
        }
        // When a File has been added, this is called.
        void file_added(File_Handle const&, std::size_t a_index) override final
        {
            auto l_files_item = m_root->get_true_child()->get_true_child<0>();
            auto l_model_index = m_model.create_index_from_item(l_files_item);
            auto l_inserter = m_model.make_row_inserter(a_index,l_model_index);
            // add a new file
            auto l_old = l_files_item->get_child_count();
            l_files_item->update();
            assert(l_old + 1 == l_files_item->get_child_count());
        }

        // When a File has been removed, this is called.
        void file_removed(File_Handle const&, std::size_t a_index) override final
        {
            auto l_files_item = m_root->get_true_child()->get_true_child<0>();
            auto l_model_index = m_model.create_index_from_item(l_files_item);
            auto l_remover = m_model.make_row_remover(a_index,l_model_index);
            // add a new file
            auto l_old = l_files_item->get_child_count();
            l_files_item->update();
            assert(l_old - 1 == l_files_item->get_child_count());
        }

        void file_requests_editor(File_Handle const&, std::size_t) override
        {
            // Don't care.
        }
    };
}


// Special 6
//============================================================
sak::Project_Outliner::Project_Outliner(Project& a_project, QWidget* a_parent):
    QWidget(a_parent),
    m_data{std::make_unique<Implementation>(a_project)}
{
    this->setLayout(imp().m_layout.get());
}
sak::Project_Outliner::~Project_Outliner() = default;
