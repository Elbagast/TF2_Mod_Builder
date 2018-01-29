#include "project_main_widget.hpp"

#include "section_data.hpp"
#include "section_handle.hpp"
#include "section_widget.hpp"
#include "project_interface.hpp"
//#include "section_interface.hpp"

#include "abstract_project_signalbox.hpp"
#include "project_editor_widget.hpp"
#include "project_outliner_widget.hpp"

#include <cassert>
#include <iterator>
#include <algorithm>

#include <QDebug>
#include <QHBoxLayout>
#include <QSplitter>

//---------------------------------------------------------------------------
// Project_Main_Widget::Implementation
//---------------------------------------------------------------------------

// Pimpl Data
//============================================================
namespace sak
{
  class Project_Main_Widget::Implementation :
      public Abstract_Project_Signalbox
  {
  public:
    Project_Interface* m_project;
    std::unique_ptr<QHBoxLayout> m_layout;

    // Because QSplitter takes ownership it must be before the widgets it holds.
    // This means the unique_ptr destructor is called after it knows its children are dead.
    std::unique_ptr<QSplitter> m_splitter;
    std::unique_ptr<Project_Outliner_Widget> m_outliner;
    std::unique_ptr<Project_Editor_Widget> m_editor;

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


sak::Project_Main_Widget::Implementation::Implementation(Project_Interface* a_project):
  m_project{a_project},
  m_layout{std::make_unique<QHBoxLayout>()},
  m_splitter{std::make_unique<QSplitter>(Qt::Horizontal, nullptr)},
  m_outliner{std::make_unique<Project_Outliner_Widget>(m_project, nullptr)},
  m_editor{std::make_unique<Project_Editor_Widget>(m_project, nullptr)}
{
  // For now this is a signalbox. It doesn't have to be.
  m_project->add_signalbox(this);

  m_splitter->addWidget(m_outliner.get());
  m_splitter->addWidget(m_editor.get());
  m_splitter->setStretchFactor(0,1);
  m_splitter->setStretchFactor(1,3);
  m_splitter->setChildrenCollapsible(false);

  m_layout->addWidget(m_splitter.get());
  m_layout->setSpacing(0);
}

sak::Project_Main_Widget::Implementation::~Implementation() = default;


// When a File has its data changed(anything but the name), this is called.
void sak::Project_Main_Widget::Implementation::changed(File_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::data_changed " << QString::fromStdString(File_Data::type());
}
// When a File has its data changed in a specific place, this is called.
void sak::Project_Main_Widget::Implementation::changed_at(File_Handle const&, std::size_t )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::data_changed_at " << QString::fromStdString(File_Data::type());
}
// When a File has been added, this is called.
void sak::Project_Main_Widget::Implementation::added(File_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::added " << QString::fromStdString(File_Data::type());
}
// When a File has been removed, this is called.
void sak::Project_Main_Widget::Implementation::removed(File_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::removed " << QString::fromStdString(File_Data::type());
}
// When a File editor is to be opened, this is called.
void sak::Project_Main_Widget::Implementation::requests_editor(File_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::requests_editor " << QString::fromStdString(File_Data::type());
}
// When focus is changed to be on a File, call this
void sak::Project_Main_Widget::Implementation::requests_focus(File_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::requests_focus " << QString::fromStdString(File_Data::type());
}


// When a texture has its data changed(anything but the name), this is called.
void sak::Project_Main_Widget::Implementation::changed(Texture_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::data_changed " << QString::fromStdString(Texture_Data::type());
}
// When a texture has its data changed in a specific place, this is called.
void sak::Project_Main_Widget::Implementation::changed_at(Texture_Handle const&, std::size_t )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::data_changed_at " << QString::fromStdString(Texture_Data::type());
}
// When a texture has been added, this is called.
void sak::Project_Main_Widget::Implementation::added(Texture_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::added " << QString::fromStdString(Texture_Data::type());
}
// When a texture has been removed, this is called.
void sak::Project_Main_Widget::Implementation::removed(Texture_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::removed " << QString::fromStdString(Texture_Data::type());
}
// When a texture editor is to be opened, this is called.
void sak::Project_Main_Widget::Implementation::requests_editor(Texture_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::requests_editor " << QString::fromStdString(Texture_Data::type());
}
// When focus is changed to be on a texture, call this
void sak::Project_Main_Widget::Implementation::requests_focus(Texture_Handle const& )
{
  qDebug() << "sak::Project_Main_Widget::Implementation::requests_focus " << QString::fromStdString(Texture_Data::type());
}



//---------------------------------------------------------------------------
// Project_Main_Widget
//---------------------------------------------------------------------------

// Special 6
//============================================================
// Create a Project with the given filepath.
sak::Project_Main_Widget::Project_Main_Widget(Project_Interface* a_project, QWidget* a_parent):
  QWidget(a_parent),
  m_data{std::make_unique<Implementation>(a_project)}
{
  this->setLayout(imp().m_layout.get());
}

sak::Project_Main_Widget::~Project_Main_Widget() = default;
