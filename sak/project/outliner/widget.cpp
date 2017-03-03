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

#include <sak/project/object.hpp>
#include <sak/project/signalbox.hpp>
#include <qtlib/outliner/model.hpp>
#include <qtlib/outliner/delegate.hpp>
#include <qtlib/outliner/treeview.hpp>

#include "root_item.hpp"
#include "project_item.hpp"
#include <sak/shared/outliner/item.hpp>
#include <sak/shared/outliner/header_item.hpp>

//---------------------------------------------------------------------------
// Project_Outliner
//---------------------------------------------------------------------------

// Pimpl Data
//============================================================
namespace sak
{
  namespace project
  {
    namespace outliner
    {
      class widget::impl :
              public abstract::signalbox
      {
      public:
          object& m_project;
          qtlib::outliner::Model m_model;
          qtlib::outliner::Delegate m_delegate;

          std::unique_ptr<outliner::root_item> m_root;

          std::unique_ptr<QHBoxLayout> m_layout;
          std::unique_ptr<qtlib::outliner::Treeview> m_treeview;

          ~impl() override;

          explicit impl(object& a_project);

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

          // When a texture has its data changed(anything but the name), this is called.
          void changed(texture::extended_handle const& a_texture) override final;
          // When a texture has its data changed in a specific place, this is called.
          void changed_at(texture::extended_handle const& a_texture, std::size_t a_section) override final;
          // When a texture has been added, this is called.
          void added(texture::extended_handle const& a_texture) override final;
          // When a texture has been removed, this is called.
          void removed(texture::extended_handle const& a_texture) override final;
          // When a texture editor is to be opened, this is called.
          void requests_editor(texture::extended_handle const& a_texture) override final;
          // When focus is changed to be on a texture, call this
          void requests_focus(texture::extended_handle const& a_texture) override final;
      };
    }
  }
}

namespace sak
{
  namespace shared
  {
    // can this bit be canned?...
    template <typename T>
    struct header_traits_typedefs
    {
      using object_type = T;
      using item_type = outliner::item<object_type>;
      using header_item_type = outliner::header_item<object_type>;
      using root_item_type = project::outliner::root_item;
    };

    template <typename T>
    struct header_traits;

    template <>
    struct header_traits<file::object> : public header_traits_typedefs<file::object>
    {
      static header_item_type* get(root_item_type* a_root)
      {
        return a_root->file_header_item();
      }
      static void initialise(root_item_type* a_root)
      {
        a_root->get_project_item()->initialise_files(false);
      }

      static void close(root_item_type* a_root)
      {
        a_root->get_project_item()->close_files();
      }
    };

    template <>
    struct header_traits<texture::object> : public header_traits_typedefs<texture::object>
    {
      static header_item_type* get(root_item_type* a_root)
      {
        return a_root->texture_header_item();
      }
      static void initialise(root_item_type* a_root)
      {
        a_root->get_project_item()->initialise_textures(false);
      }

      static void close(root_item_type* a_root)
      {
        a_root->get_project_item()->close_textures();
      }
    };


    template <typename T>
    struct do_stuff
    {
      using object_type = T;
      using extended_handle_type = extended_handle<object_type>;
      using item_type = outliner::item<object_type>;
      using header_item_type = outliner::header_item<object_type>;

      using root_item_type = project::outliner::root_item;


      // When a object has its data changed in a specific place, this is called.
      static void changed_at(header_item_type* a_header, qtlib::outliner::Model& a_model, extended_handle_type const& a_ehandle, std::size_t a_section)
      {
        qDebug() << "sak::outliner::widget::impl::changed_at "<< QString::fromStdString(object_type::type()) <<" " << a_ehandle.id().get() << " " << a_section;
        if (a_section == 0)
        {
          auto l_i = a_header->index_of(a_ehandle);
          auto l_header_index = a_model.create_index_from_item(a_header); //don't know the full type of shared::outliner::header_item?....
          auto l_object_index = a_model.index(static_cast<int>(l_i),0,l_header_index);

          // no movement right now....
          a_header->name_changed(a_ehandle);
          a_model.data_changed(l_object_index, l_object_index, QVector<int>(Qt::DisplayRole));
        }
      }
      // When a object has been added, this is called.
      static void added(project::outliner::root_item* a_root, qtlib::outliner::Model& a_model, extended_handle_type const& a_ehandle)
      {
        qDebug() << "sak::outliner::widget::impl::added "<< QString::fromStdString(object_type::type()) <<" " << a_ehandle.id().get();

        auto l_header = header_traits<object_type>::get(a_root);
      /*
        // if the file header doesn't exist (we previously had no files), make it
        if(l_header == nullptr)
        {
            // we previously had no files, so we have to build the header first.
            auto l_project_index = a_model.create_index_from_item(a_root->get_project_item());
            auto l_inserter = a_model.make_row_inserter(0,l_project_index);
            header_traits<object_type>::initialise(a_root);
            l_header = header_traits<object_type>::get(a_root);
        }*/
        // add the file
        auto l_model_index = a_model.create_index_from_item(l_header);
        auto l_object_position = static_cast<int>(l_header->index_of(a_ehandle));
        auto l_inserter = a_model.make_row_inserter(l_object_position,l_model_index);
        // add a new file

        auto l_old = l_header->get_child_count();
        l_header->added(a_ehandle);
        assert(l_old + 1 == l_header->get_child_count());
      }
      // When a object has been removed, this is called.
      static void removed(project::outliner::root_item* a_root, qtlib::outliner::Model& a_model, extended_handle_type const& a_ehandle)
      {
        qDebug() << "sak::outliner::widget::impl::removed "<< QString::fromStdString(object_type::type()) <<" " << a_ehandle.id().get();
        qDebug() << "outliner::widget::impl::removed";
        auto l_header_item = header_traits<object_type>::get(a_root);
        auto l_header_index = a_model.create_index_from_item(l_header_item);
        auto l_item_position = static_cast<int>(l_header_item->index_of(a_ehandle));
        {
          auto l_remover = a_model.make_row_remover(l_item_position,l_header_index);
          auto l_old = l_header_item->get_child_count();
          l_header_item->removed(a_ehandle);
          assert(l_old - 1 == l_header_item->get_child_count());
        }
        /*
        // if we no longer have any files, get rid of the header.
        if (!a_project.has_files())
        {
          auto l_project_item = a_root->get_project_item();
          auto l_project_index = a_model.create_index_from_item(l_project_item);
          auto l_files_position = static_cast<int>(l_files_item->index_in_parent());
          auto l_remover = m_model.make_row_remover(l_files_position,l_project_index);
          auto l_old = l_project_item->get_child_count();
          l_project_item->close_files();
          assert(l_old - 1 == l_project_item->get_child_count());
        }
        */
      }
      // When a object editor is to be opened, this is called.
      static void requests_editor(extended_handle_type const& a_ehandle)
      {
        qDebug() << "sak::outliner::widget::impl::requests_editor "<< QString::fromStdString(object_type::type()) <<" " << a_ehandle.id().get() << "does nothing.";
      }
      // When focus is changed to be on a object, call this
      static void requests_focus(qtlib::outliner::Treeview* a_treeview, project::outliner::root_item* a_root, qtlib::outliner::Model& a_model, extended_handle_type const& a_ehandle)
      {
        qDebug() << "sak::outliner::widget::impl::requests_focus "<< QString::fromStdString(object_type::type()) <<" " << a_ehandle.id().get();
        qDebug() << "outliner::widget::impl::requests_focus";
        // Change the item selection in the outliner to this File.
        auto l_item = header_traits<object_type>::get(a_root)->item_of(a_ehandle);
        auto l_index = a_model.create_index_from_item(l_item);
        a_treeview->setCurrentIndex(l_index);
      }
    };
  }
}


sak::project::outliner::widget::impl::~impl() = default;

sak::project::outliner::widget::impl::impl(object& a_project):
    abstract::signalbox(),
    m_project{a_project},
    m_model{},
    m_delegate{},
    m_root{std::make_unique<root_item>(a_project)},
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
void sak::project::outliner::widget::impl::changed(file::extended_handle const& a_file)
{
  //qDebug() << "outliner::widget::impl::data_changed";
  // don't care about except for the name, so pass it on
  changed_at(a_file, 0);
}
// When a File has its data changed in a specific place, this is called.
void sak::project::outliner::widget::impl::changed_at(file::extended_handle const& a_file, std::size_t a_section)
{
  assert(m_root->file_header_item() != nullptr);
  shared::do_stuff<file::object>::changed_at(m_root->file_header_item(), m_model, a_file, a_section);
}
// When a File has been added, this is called.
void sak::project::outliner::widget::impl::added(file::extended_handle const& a_file)
{
  shared::do_stuff<file::object>::added(m_root.get(), m_model, a_file);
}

// When a File has been removed, this is called.
void sak::project::outliner::widget::impl::removed(file::extended_handle const& a_file)
{
  shared::do_stuff<file::object>::removed(m_root.get(), m_model, a_file);
}

// When a File editor is to be opened, this is called.
void sak::project::outliner::widget::impl::requests_editor(file::extended_handle const& a_file)
{
  shared::do_stuff<file::object>::requests_editor(a_file);
}

// When focus is changed to be on a File, call this
void sak::project::outliner::widget::impl::requests_focus(file::extended_handle const& a_file)
{
  shared::do_stuff<file::object>::requests_focus(m_treeview.get(), m_root.get(), m_model, a_file);
}



// When a texture has its data changed(anything but the name), this is called.
void sak::project::outliner::widget::impl::changed(texture::extended_handle const& a_texture)
{
  //qDebug() << "outliner::widget::impl::data_changed";
  // don't care about except for the name, so pass it on
  changed_at(a_texture, 0);
}
// When a texture has its data changed in a specific place, this is called.
void sak::project::outliner::widget::impl::changed_at(texture::extended_handle const& a_texture, std::size_t a_section)
{
  assert(m_root->texture_header_item() != nullptr);
  shared::do_stuff<texture::object>::changed_at(m_root->texture_header_item(), m_model, a_texture, a_section);
}
// When a texture has been added, this is called.
void sak::project::outliner::widget::impl::added(texture::extended_handle const& a_texture)
{
  shared::do_stuff<texture::object>::added(m_root.get(), m_model, a_texture);
}

// When a texture has been removed, this is called.
void sak::project::outliner::widget::impl::removed(texture::extended_handle const& a_texture)
{
  shared::do_stuff<texture::object>::removed(m_root.get(), m_model, a_texture);
}

// When a texture editor is to be opened, this is called.
void sak::project::outliner::widget::impl::requests_editor(texture::extended_handle const& a_texture)
{
  shared::do_stuff<texture::object>::requests_editor(a_texture);
}

// When focus is changed to be on a texture, call this
void sak::project::outliner::widget::impl::requests_focus(texture::extended_handle const& a_texture)
{
  shared::do_stuff<texture::object>::requests_focus(m_treeview.get(), m_root.get(), m_model, a_texture);
}

// Special 6
//============================================================
sak::project::outliner::widget::widget(object& a_project, QWidget* a_parent):
    QWidget(a_parent),
    m_data{std::make_unique<impl>(a_project)}
{
    this->setLayout(imp().m_layout.get());
}
sak::project::outliner::widget::~widget() = default;
