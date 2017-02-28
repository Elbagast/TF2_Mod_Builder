#include "widget.hpp"

#include <QHBoxLayout>
#include <QTreeView>
#include <QLabel>
#include <QDebug>
#include <cassert>

#include <sak/shared/object.hpp>
#include <sak/shared/manager.hpp>
#include <sak/shared/extended_manager.hpp>
#include <sak/shared/interface_traits.hpp>
#include <sak/shared/interface.hpp>
#include <sak/shared/outliner_item.hpp>

#include <sak/project.hpp>
#include <sak/project_signalbox.hpp>
#include <qtlib/outliner/model.hpp>
#include <qtlib/outliner/delegate.hpp>
#include <qtlib/outliner/treeview.hpp>
#include "root_item.hpp"
#include "project_item.hpp"

namespace
{
  void test()
  {
    sak::shared::outliner::header_item<sak::file::object> hi{nullptr, false};
    auto b = hi.has_children();
    auto i = hi.index_of(sak::file::extended_handle());
    sak::shared::outliner::item<sak::file::object> it{&hi, sak::file::extended_handle()};
  }
}

// For reasons unknown right now, this file can't see the sak::shared::outliner::header_item<T> interface...
// WHAT THE FUCK

//---------------------------------------------------------------------------
// Project_Outliner
//---------------------------------------------------------------------------

// Pimpl Data
//============================================================
namespace sak
{
  namespace outliner
  {
    class widget::Implementation :
            public Project_Signalbox
    {
    public:
        Project& m_project;
        qtlib::outliner::Model m_model;
        qtlib::outliner::Delegate m_delegate;

        std::unique_ptr<outliner::root_item> m_root;

        std::unique_ptr<QHBoxLayout> m_layout;
        std::unique_ptr<qtlib::outliner::Treeview> m_treeview;

        ~Implementation() override;

        explicit Implementation(Project& a_project);

        // When a File has its data changed(anything but the name), this is called.
        void changed(file::extended_handle const& a_file) override final;
        // When a File has its data changed in a specific place, this is called.
        void changed_at(file::extended_handle const& a_file, std::size_t a_section) override final;
        // When a File has been added, this is called.
        void added(file::extended_handle const& a_file) override final;
        // When a File has been removed, this is called.
        void removed(file::extended_handle const& a_file) override final;
        // When a File editor is to be opened, this is called.
        void requests_editor(file::extended_handle const& a_file) override final;
        // When focus is changed to be on a File, call this
        void requests_focus(file::extended_handle const& a_file) override final;
    };
  }
}

sak::outliner::widget::Implementation::~Implementation() = default;

sak::outliner::widget::Implementation::Implementation(Project& a_project):
    Project_Signalbox(),
    m_project{a_project},
    m_model{},
    m_delegate{},
    m_root{std::make_unique<outliner::root_item>(a_project)},
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

// When a File has its data changed(anything but the name), this is called.
void sak::outliner::widget::Implementation::changed(file::extended_handle const& a_file)
{
    qDebug() << "outliner::widget::Implementation::data_changed";
    // don't care about except for the name, so pass it on
    changed_at(a_file, 0);
}
// When a File has its data changed in a specific place, this is called.
void sak::outliner::widget::Implementation::changed_at(file::extended_handle const& a_file, std::size_t a_section)
{
    qDebug() << "outliner::widget::Implementation::data_changed_at";
    // don't care about data
    if (a_section == 0)
    {
      auto l_files_item = m_root->file_header_item();
      static_assert(std::is_same<decltype(l_files_item), sak::file::outliner::header_item*>::value, "bad ptr");
      //sak::file::outliner::header_item* l_files_item = m_root->file_header_item();
      //l_files_item->
      auto l_i = l_files_item->index_of(a_file);

      assert(l_files_item != nullptr);
      auto l_model_index = m_model.create_index_from_item(l_files_item); //don't know the full type of shared::outliner::header_item?....
      auto l_file_index = m_model.index(static_cast<int>(l_files_item->index_of(a_file)),0,l_model_index);

      // no movement right now....
      l_files_item->name_changed(a_file);
      m_model.data_changed(l_file_index, l_file_index, QVector<int>(Qt::DisplayRole));
    }
}
// When a File has been added, this is called.
void sak::outliner::widget::Implementation::added(file::extended_handle const& a_file)
{
    qDebug() << "outliner::widget::Implementation::added";
    auto l_files_item = m_root->file_header_item();

    // if the file header doesn't exist (we previously had no files), make it
    if(l_files_item == nullptr)
    {
        // we previously had no files, so we have to build the header first.
        auto l_project_index = m_model.create_index_from_item(m_root->get_project_item());
        auto l_inserter = m_model.make_row_inserter(0,l_project_index);
        m_root->get_project_item()->initialise_files(false);
        l_files_item = m_root->file_header_item();
    }
    // add the file
    auto l_model_index = m_model.create_index_from_item(l_files_item);
    auto l_file_position = static_cast<int>(l_files_item->index_of(a_file));
    auto l_inserter = m_model.make_row_inserter(l_file_position,l_model_index);
    // add a new file

    auto l_old = l_files_item->get_child_count();
    l_files_item->added(a_file);
    assert(l_old + 1 == l_files_item->get_child_count());

}

// When a File has been removed, this is called.
void sak::outliner::widget::Implementation::removed(file::extended_handle const& a_file)
{
    qDebug() << "outliner::widget::Implementation::removed";
    auto l_files_item = m_root->file_header_item();
    auto l_model_index = m_model.create_index_from_item(l_files_item);
    auto l_file_position = static_cast<int>(l_files_item->index_of(a_file));
    {
        auto l_remover = m_model.make_row_remover(l_file_position,l_model_index);
        auto l_old = l_files_item->get_child_count();
        l_files_item->removed(a_file);
        assert(l_old - 1 == l_files_item->get_child_count());
    }
    // if we no longer have any files, get rid of the file header.
    if (!m_project.has_files())
    {
        auto l_project_item = m_root->get_project_item();
        auto l_project_index = m_model.create_index_from_item(l_project_item);
        auto l_files_position = static_cast<int>(l_files_item->index_in_parent());
        auto l_remover = m_model.make_row_remover(l_files_position,l_project_index);
        auto l_old = l_project_item->get_child_count();
        l_project_item->close_files();
        assert(l_old - 1 == l_project_item->get_child_count());
    }
}

// When a File editor is to be opened, this is called.
void sak::outliner::widget::Implementation::requests_editor(file::extended_handle const&)
{
    qDebug() << "outliner::widget::Implementation::requests_editor";
    // Don't care.
}

// When focus is changed to be on a File, call this
void sak::outliner::widget::Implementation::requests_focus(file::extended_handle const& a_file)
{
    qDebug() << "outliner::widget::Implementation::requests_focus";
    // Change the item selection in the outliner to this File.
    auto l_item = m_root->file_header_item()->item_of(a_file);
    auto l_index = m_model.create_index_from_item(l_item);
    m_treeview->setCurrentIndex(l_index);
}

// Special 6
//============================================================
sak::outliner::widget::widget(Project& a_project, QWidget* a_parent):
    QWidget(a_parent),
    m_data{std::make_unique<Implementation>(a_project)}
{
    this->setLayout(imp().m_layout.get());
}
sak::outliner::widget::~widget() = default;
