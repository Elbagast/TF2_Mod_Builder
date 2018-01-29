#include "project_outliner_widget.hpp"

#include "section_handle.hpp"
#include "project_interface.hpp"
#include "section_interface.hpp"
#include "abstract_project_signalbox.hpp"
#include "outliner_model.hpp"
#include "outliner_delegate.hpp"
#include "outliner_view_widget.hpp"
#include "project_outliner_items.hpp"
#include "section_outliner_items.hpp"

#include <QHBoxLayout>
#include <QTreeView>
#include <QLabel>
#include <QDebug>
#include <cassert>

//---------------------------------------------------------------------------
// Project_Outliner
//---------------------------------------------------------------------------

// Pimpl Data
//============================================================
namespace sak
{
  class Project_Outliner_Widget::Implementation :
          public Abstract_Project_Signalbox
  {
  public:
    Project_Interface* m_project;
    Outliner_Model m_model;
    Outliner_Delegate m_delegate;

    std::unique_ptr<Project_Outliner_Root_Item> m_root;

    std::unique_ptr<QHBoxLayout> m_layout;
    std::unique_ptr<Outliner_View_Widget> m_view;


    explicit Implementation(Project_Interface* a_project);
    ~Implementation() override;

    // When a File has its data changed(anything but the name), this is called.
    void changed(File_Handle const& a_file) override final;
    // When a File has its data changed in a specific place, this is called.
    void changed_at(File_Handle const& a_file, std::size_t a_section) override final;
    // When a File has been added, this is called.
    void added(File_Handle const& a_file) override final;
    // When a File has been removed, this is called.
    void removed(File_Handle const& a_file) override final;
    // When a File editor is to be opened, this is called.
    void requests_editor(File_Handle const& a_file) override final;
    // When focus is changed to be on a File, call this
    void requests_focus(File_Handle const& a_file) override final;

    // When a texture has its data changed(anything but the name), this is called.
    void changed(Texture_Handle const& a_texture) override final;
    // When a texture has its data changed in a specific place, this is called.
    void changed_at(Texture_Handle const& a_texture, std::size_t a_section) override final;
    // When a texture has been added, this is called.
    void added(Texture_Handle const& a_texture) override final;
    // When a texture has been removed, this is called.
    void removed(Texture_Handle const& a_texture) override final;
    // When a texture editor is to be opened, this is called.
    void requests_editor(Texture_Handle const& a_texture) override final;
    // When focus is changed to be on a texture, call this
    void requests_focus(Texture_Handle const& a_texture) override final;
  };
}

namespace sak
{
  namespace
  {
    // can this bit be canned?...
    template <typename T>
    struct header_traits_typedefs
    {
      using Data_Type = T;
      using Item_Type = Section_Outliner_Item<Data_Type>;
      using Header_Item_Type = Section_Outliner_Header_Item<Data_Type>;
      using Root_Item_Type = Project_Outliner_Root_Item;
    };

    template <typename T>
    struct header_traits;

    template <>
    struct header_traits<File_Data> : public header_traits_typedefs<File_Data>
    {
      static Header_Item_Type* get(Root_Item_Type* a_root)
      {
        return a_root->file_header_item();
      }
      static void initialise(Root_Item_Type* a_root)
      {
        a_root->get_project_item()->initialise_files(false);
      }

      static void close(Root_Item_Type* a_root)
      {
        a_root->get_project_item()->close_files();
      }
    };

    template <>
    struct header_traits<Texture_Data> : public header_traits_typedefs<Texture_Data>
    {
      static Header_Item_Type* get(Root_Item_Type* a_root)
      {
        return a_root->texture_header_item();
      }
      static void initialise(Root_Item_Type* a_root)
      {
        a_root->get_project_item()->initialise_textures(false);
      }

      static void close(Root_Item_Type* a_root)
      {
        a_root->get_project_item()->close_textures();
      }
    };


    template <typename T>
    struct do_stuff
    {
      using Data_Type = T;
      using Handle_Type = Section_Handle<Data_Type>;
      using Item_Type = Section_Outliner_Item<Data_Type>;
      using Header_Item_Type = Section_Outliner_Header_Item<Data_Type>;

      using Root_Item_Type = Project_Outliner_Root_Item;


      // When a object has its data changed in a specific place, this is called.
      static void changed_at(Header_Item_Type* a_header, Outliner_Model& a_model, Handle_Type const& a_handle, std::size_t a_section)
      {
        qDebug() << "sak::Project_Outliner_Widget::Implementation::changed_at "<< QString::fromStdString(Data_Type::type()) <<" " << a_handle.id().value() << " " << a_section;
        if (a_section == 0)
        {
          auto l_i = a_header->index_of(a_handle);
          auto l_header_index = a_model.create_index_from_item(a_header); //don't know the full type of shared::outliner::header_item?....
          auto l_object_index = a_model.index(static_cast<int>(l_i),0,l_header_index);

          // no movement right now....
          a_header->name_changed(a_handle);
          a_model.data_changed(l_object_index, l_object_index, QVector<int>(Qt::DisplayRole));
        }
      }
      // When a object has been added, this is called.
      static void added(Project_Outliner_Root_Item* a_root, Outliner_Model& a_model, Handle_Type const& a_handle)
      {
        qDebug() << "sak::Project_Outliner_Widget::Implementation::added "<< QString::fromStdString(Data_Type::type()) <<" " << a_handle.id().value();

        auto l_header = header_traits<Data_Type>::get(a_root);
      /*
        // if the file header doesn't exist (we previously had no files), make it
        if(l_header == nullptr)
        {
            // we previously had no files, so we have to build the header first.
            auto l_project_index = a_model.create_index_from_item(a_root->get_project_item());
            auto l_inserter = a_model.make_row_inserter(0,l_project_index);
            header_traits<Data_Type>::initialise(a_root);
            l_header = header_traits<Data_Type>::get(a_root);
        }*/
        // add the file
        auto l_model_index = a_model.create_index_from_item(l_header);
        auto l_object_position = static_cast<int>(l_header->index_of(a_handle));
        auto l_inserter = a_model.make_row_inserter(l_object_position,l_model_index);
        // add a new file

        auto l_old = l_header->get_child_count();
        l_header->added(a_handle);
        assert(l_old + 1 == l_header->get_child_count());
      }
      // When a object has been removed, this is called.
      static void removed(Project_Outliner_Root_Item* a_root, Outliner_Model& a_model, Handle_Type const& a_handle)
      {
        qDebug() << "sak::Project_Outliner_Widget::Implementation::removed "<< QString::fromStdString(Data_Type::type()) <<" " << a_handle.id().value();
        auto l_header_item = header_traits<Data_Type>::get(a_root);
        auto l_header_index = a_model.create_index_from_item(l_header_item);
        auto l_item_position = static_cast<int>(l_header_item->index_of(a_handle));
        {
          auto l_remover = a_model.make_row_remover(l_item_position,l_header_index);
          auto l_old = l_header_item->get_child_count();
          l_header_item->removed(a_handle);
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
      static void requests_editor(Handle_Type const& a_handle)
      {
        qDebug() << "sak::Project_Outliner_Widget::Implementation::requests_editor "<< QString::fromStdString(Data_Type::type()) <<" " << a_handle.id().value() << "does nothing.";
      }
      // When focus is changed to be on a object, call this
      static void requests_focus(Outliner_View_Widget* a_treeview, Project_Outliner_Root_Item* a_root, Outliner_Model& a_model, Handle_Type const& a_handle)
      {
        qDebug() << "sak::Project_Outliner_Widget::Implementation::requests_focus "<< QString::fromStdString(Data_Type::type()) <<" " << a_handle.id().value();
        // Change the item selection in the outliner to this File.
        auto l_item = header_traits<Data_Type>::get(a_root)->item_of(a_handle);
        auto l_index = a_model.create_index_from_item(l_item);
        a_treeview->setCurrentIndex(l_index);
      }
    };
  }
}



sak::Project_Outliner_Widget::Implementation::Implementation(Project_Interface* a_project):
    Abstract_Project_Signalbox(),
    m_project{a_project},
    m_model{},
    m_delegate{},
    m_root{std::make_unique<Project_Outliner_Root_Item>(a_project)},
    m_layout{std::make_unique<QHBoxLayout>()},
    m_view{std::make_unique<Outliner_View_Widget>()}
{
    m_model.set_root(m_root.get());
    assert(m_model.is_active());
    assert(m_root->get_child_count() == 1);

    // testing the model
    assert(m_model.parent(QModelIndex()) == QModelIndex());
    assert(m_model.index(0,0,QModelIndex()).internalPointer() == m_root.get()->get_true_child());
    //assert(m_model.index(0,0,m_model.index(0,0,QModelIndex())).internalPointer() == m_root.get()->get_child(0));

    m_view->setItemDelegate(&m_delegate);
    m_view->set_model(&m_model);

    m_project->add_signalbox(this);

    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);

    m_layout->addWidget(m_view.get());
}

sak::Project_Outliner_Widget::Implementation::~Implementation() = default;

// When a File has its data changed(anything but the name), this is called.
void sak::Project_Outliner_Widget::Implementation::changed(File_Handle const& a_file)
{
  //qDebug() << "sak::Project_Outliner_Widget::Implementation::changed " << QString::fromStdString(File_Data::type());
  //qDebug() << "outliner::widget::Implementation::data_changed";
  // don't care about except for the name, so pass it on
  changed_at(a_file, 0);
}
// When a File has its data changed in a specific place, this is called.
void sak::Project_Outliner_Widget::Implementation::changed_at(File_Handle const& a_file, std::size_t a_section)
{
  //qDebug() << "sak::Project_Outliner_Widget::Implementation::changed_at " << QString::fromStdString(File_Data::type());
  assert(m_root->file_header_item() != nullptr);
  do_stuff<File_Data>::changed_at(m_root->file_header_item(), m_model, a_file, a_section);
}
// When a File has been added, this is called.
void sak::Project_Outliner_Widget::Implementation::added(File_Handle const& a_file)
{
  //qDebug() << "sak::Project_Outliner_Widget::Implementation::added " << QString::fromStdString(File_Data::type());
  do_stuff<File_Data>::added(m_root.get(), m_model, a_file);
}

// When a File has been removed, this is called.
void sak::Project_Outliner_Widget::Implementation::removed(File_Handle const& a_file)
{
  //qDebug() << "sak::Project_Outliner_Widget::Implementation::removed " << QString::fromStdString(File_Data::type());
  do_stuff<File_Data>::removed(m_root.get(), m_model, a_file);
}

// When a File editor is to be opened, this is called.
void sak::Project_Outliner_Widget::Implementation::requests_editor(File_Handle const& a_file)
{
  //qDebug() << "sak::Project_Outliner_Widget::Implementation::requests_editor " << QString::fromStdString(File_Data::type());
  do_stuff<File_Data>::requests_editor(a_file);
}

// When focus is changed to be on a File, call this
void sak::Project_Outliner_Widget::Implementation::requests_focus(File_Handle const& a_file)
{
  //qDebug() << "sak::Project_Outliner_Widget::Implementation::requests_focus " << QString::fromStdString(File_Data::type());
  do_stuff<File_Data>::requests_focus(m_view.get(), m_root.get(), m_model, a_file);
}



// When a texture has its data changed(anything but the name), this is called.
void sak::Project_Outliner_Widget::Implementation::changed(Texture_Handle const& a_texture)
{
  //qDebug() << "sak::Project_Outliner_Widget::Implementation::changed " << QString::fromStdString(Texture_Data::type());
  //qDebug() << "outliner::widget::Implementation::data_changed";
  // don't care about except for the name, so pass it on
  changed_at(a_texture, 0);
}
// When a texture has its data changed in a specific place, this is called.
void sak::Project_Outliner_Widget::Implementation::changed_at(Texture_Handle const& a_texture, std::size_t a_section)
{
  //qDebug() << "sak::Project_Outliner_Widget::Implementation::changed_at " << QString::fromStdString(Texture_Data::type());
  assert(m_root->texture_header_item() != nullptr);
  do_stuff<Texture_Data>::changed_at(m_root->texture_header_item(), m_model, a_texture, a_section);
}
// When a texture has been added, this is called.
void sak::Project_Outliner_Widget::Implementation::added(Texture_Handle const& a_texture)
{
  //qDebug() << "sak::Project_Outliner_Widget::Implementation::texture_header_item " << QString::fromStdString(Texture_Data::type());
  do_stuff<Texture_Data>::added(m_root.get(), m_model, a_texture);
}

// When a texture has been removed, this is called.
void sak::Project_Outliner_Widget::Implementation::removed(Texture_Handle const& a_texture)
{
  //qDebug() << "sak::Project_Outliner_Widget::Implementation::removed " << QString::fromStdString(Texture_Data::type());
  do_stuff<Texture_Data>::removed(m_root.get(), m_model, a_texture);
}

// When a texture editor is to be opened, this is called.
void sak::Project_Outliner_Widget::Implementation::requests_editor(Texture_Handle const& a_texture)
{
  //qDebug() << "sak::Project_Outliner_Widget::Implementation::requests_editor " << QString::fromStdString(Texture_Data::type());
  do_stuff<Texture_Data>::requests_editor(a_texture);
}

// When focus is changed to be on a texture, call this
void sak::Project_Outliner_Widget::Implementation::requests_focus(Texture_Handle const& a_texture)
{
  //qDebug() << "sak::Project_Outliner_Widget::Implementation::requests_focus " << QString::fromStdString(Texture_Data::type());
  do_stuff<Texture_Data>::requests_focus(m_view.get(), m_root.get(), m_model, a_texture);
}

// Special 6
//============================================================
sak::Project_Outliner_Widget::Project_Outliner_Widget(Project_Interface* a_project, QWidget* a_parent):
  QWidget(a_parent),
  m_data{std::make_unique<Implementation>(a_project)}
{
  this->setLayout(imp().m_layout.get());
}
sak::Project_Outliner_Widget::~Project_Outliner_Widget() = default;

