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

        ~Implementation() override;

        explicit Implementation(Project& a_project);

        // When a File has had its name changed, this is called.
        void name_changed(File_Handle const& a_file) override final;
        // When a File has had its description changed, this is called.
        void description_changed(File_Handle const& a_file) override final;
        // When a File has its data changed(anything but the name), this is called.
        void data_changed(File_Handle const& a_file) override final;
        // When a File has its data changed in a specific place, this is called.
        void data_changed_at(File_Handle const& a_file, std::size_t a_section) override final;
        // When a File has been added, this is called.
        void added(File_Handle const& a_file) override final;
        // When a File has been removed, this is called.
        void removed(File_Handle const& a_file) override final;
        // When a File editor is to be opened, this is called.
        void requests_editor(File_Handle const& a_file) override final;
        // When focus is changed to be on a File, call this
        void requests_focus(File_Handle const& a_file) override final;
    };
}

sak::Project_Outliner::Implementation::~Implementation() = default;

sak::Project_Outliner::Implementation::Implementation(Project& a_project):
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
    assert(m_model.index(0,0,QModelIndex()).internalPointer() == m_root.get()->get_true_child());
    //assert(m_model.index(0,0,m_model.index(0,0,QModelIndex())).internalPointer() == m_root.get()->get_child(0));

    m_treeview->setItemDelegate(&m_delegate);
    m_treeview->set_model(&m_model);

    m_project.add_signalbox(this);

    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);

    m_layout->addWidget(m_treeview.get());
}

// When a File has had its name changed, this is called.
void sak::Project_Outliner::Implementation::name_changed(File_Handle const& a_file)
{
    qDebug() << "Project_Outliner::Implementation::name_changed";
    auto l_files_item = m_root->file_header_item();
    auto l_model_index = m_model.create_index_from_item(l_files_item);
    auto l_file_index = m_model.index(static_cast<int>(l_files_item->index_of_file(a_file)),0,l_model_index);

    // no movement right now....
    l_files_item->name_changed(a_file);
    m_model.data_changed(l_file_index, l_file_index, QVector<int>(Qt::DisplayRole));
}
// When a File has had its description changed, this is called.
void sak::Project_Outliner::Implementation::description_changed(File_Handle const& )
{
    qDebug() << "Project_Outliner::Implementation::description_changed";
    // don't actively care about description, it will jsut be different next time it's looked up.
}
// When a File has its data changed(anything but the name), this is called.
void sak::Project_Outliner::Implementation::data_changed(File_Handle const&)
{
    qDebug() << "Project_Outliner::Implementation::data_changed";
    // don't care about data
}
// When a File has its data changed in a specific place, this is called.
void sak::Project_Outliner::Implementation::data_changed_at(File_Handle const&, std::size_t)
{
    qDebug() << "Project_Outliner::Implementation::data_changed_at";
    // don't care about data
}
// When a File has been added, this is called.
void sak::Project_Outliner::Implementation::added(File_Handle const& a_file)
{
    qDebug() << "Project_Outliner::Implementation::added";
    auto l_files_item = m_root->file_header_item();

    // if the file header doesn't exist (we previously had no files), make it
    if(l_files_item == nullptr)
    {
        // we previously had no files, so we have to build the header first.
        auto l_project_index = m_model.create_index_from_item(m_root->project_item());
        auto l_inserter = m_model.make_row_inserter(0,l_project_index);
        m_root->project_item()->initialise_files(false);
        l_files_item = m_root->file_header_item();
    }
    // add the file
    auto l_model_index = m_model.create_index_from_item(l_files_item);
    auto l_file_position = static_cast<int>(l_files_item->index_of_file(a_file));
    auto l_inserter = m_model.make_row_inserter(l_file_position,l_model_index);
    // add a new file

    auto l_old = l_files_item->get_child_count();
    l_files_item->added(a_file);
    assert(l_old + 1 == l_files_item->get_child_count());

}

// When a File has been removed, this is called.
void sak::Project_Outliner::Implementation::removed(File_Handle const& a_file)
{
    qDebug() << "Project_Outliner::Implementation::removed";
    auto l_files_item = m_root->file_header_item();
    auto l_model_index = m_model.create_index_from_item(l_files_item);
    auto l_file_position = static_cast<int>(l_files_item->index_of_file(a_file));
    {
        auto l_remover = m_model.make_row_remover(l_file_position,l_model_index);
        auto l_old = l_files_item->get_child_count();
        l_files_item->removed(a_file);
        assert(l_old - 1 == l_files_item->get_child_count());
    }
    // if we no longer have any files, get rid of the file header.
    if (!m_project.has_files())
    {
        auto l_project_item = m_root->project_item();
        auto l_project_index = m_model.create_index_from_item(l_project_item);
        auto l_files_position = static_cast<int>(l_files_item->index_in_parent());
        auto l_remover = m_model.make_row_remover(l_files_position,l_project_index);
        auto l_old = l_project_item->get_child_count();
        l_project_item->close_files();
        assert(l_old - 1 == l_project_item->get_child_count());
    }
}

// When a File editor is to be opened, this is called.
void sak::Project_Outliner::Implementation::requests_editor(File_Handle const&)
{
    qDebug() << "Project_Outliner::Implementation::requests_editor";
    // Don't care.
}

// When focus is changed to be on a File, call this
void sak::Project_Outliner::Implementation::requests_focus(File_Handle const& a_file)
{
    qDebug() << "Project_Outliner::Implementation::requests_focus";
    // Change the item selection in the outliner to this File.
    auto l_item = m_root->file_header_item()->item_of_file(a_file);
    auto l_index = m_model.create_index_from_item(l_item);
    m_treeview->setCurrentIndex(l_index);
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
