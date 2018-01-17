#include "project_editor_widget.hpp"

#include <cassert>
#include <iterator>
#include <algorithm>

#include <QHBoxLayout>
#include <QStackedWidget>
#include <QTabWidget>
#include <QDebug>
#include <QLabel>

#include "section_data.hpp"
#include "section_handle.hpp"
#include "section_interface.hpp"
#include "section_widget.hpp"

#include "project_data.hpp"
#include "abstract_project_signalbox.hpp"

//---------------------------------------------------------------------------
// Project_Editor_Widget
//---------------------------------------------------------------------------
namespace
{
  QString make_background_text(sak::Project_Data& a_project)
  {
    QString l_result{a_project.name()};
    l_result.append(u8"\n\nNothing open. Open an item from the outliner.");
    return l_result;
  }

  // Seperating out since we might want to change this to display information.
  class Background_Widget :
        public QLabel
  {
  public:
    explicit Background_Widget(sak::Project_Data& a_project):
        QLabel(make_background_text(a_project), nullptr)
    {
        this->setAlignment(Qt::AlignCenter);
    }
    ~Background_Widget() override = default;
  };


  template <typename T>
  struct widget_equals_handle
  {

    using Handle_Type = sak::Section_Handle<T>;
    using Widget_Type = sak::Section_Widget<T>;

    Handle_Type const& m_handle;

    explicit widget_equals_handle(Handle_Type const& a_handle):
      m_handle{a_handle}
    {}

    bool operator()(std::unique_ptr<Widget_Type> const& a_widget)
    {
      return m_handle == a_widget->cget_handle();
    }
  };
}




// Pimpl Data
//============================================================
namespace sak
{
  class Project_Editor_Widget::Implementation :
      public Abstract_Project_Signalbox
  {
  public:
    Project_Data& m_project;
    std::unique_ptr<QHBoxLayout> m_layout;
    std::unique_ptr<QStackedWidget> m_stackwidget;
    std::unique_ptr<Background_Widget> m_background;
    std::unique_ptr<QTabWidget> m_tabwidget;
    std::vector<std::unique_ptr<File_Widget>> m_file_widgets;
    std::vector<std::unique_ptr<Texture_Widget>> m_texture_widgets;

    explicit Implementation(Project_Data& a_project);
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

    //void close_tab(int a_index);

    void update_visible();
  };
}


namespace sak
{
  //---------------------------------------------------------------------------
  // sak::shared::do_signals<T>
  //---------------------------------------------------------------------------
  // Signal logic goes here so it doesn't need to be repeated
  template <typename T>
  struct do_stuff
  {
    using Data_Type = T;
    using Handle_Type = Section_Handle<Data_Type>;
    using Widget_Type = Section_Widget<Data_Type>;

    using vector_type = std::vector<std::unique_ptr<Widget_Type>>;

    // When a texture has its data changed(anything but the name), this is called.
    static void changed(vector_type& a_widgets, Handle_Type const& a_handle)
    {
      qDebug() << "sak::Project_Editor_Widget::Implementation::data_changed "<< QString::fromStdString(Data_Type::type()) <<" " << a_handle.id().value();
      // Find the editor for this handle
      auto l_found = std::find_if(a_widgets.cbegin(),
                                  a_widgets.cend(),
                                  widget_equals_handle<Data_Type>(a_handle));
      // if it exists, update it
      if (l_found != a_widgets.cend())
      {
        l_found->get()->changed();
      }
    }

    // When a texture has its data changed in a specific place, this is called.
    static void changed_at(vector_type& a_widgets, QTabWidget* a_tabwidget, Handle_Type const& a_handle, std::size_t a_section)
    {
      qDebug() << "sak::Project_Editor_Widget::Implementation::data_changed_at "<< QString::fromStdString(Data_Type::type()) <<" " << a_handle.id().value() << " " << a_section;
      // Find the editor for this handle
      auto l_found = std::find_if(a_widgets.cbegin(),
                                  a_widgets.cend(),
                                  widget_equals_handle<Data_Type>(a_handle));

      // if it exists, update it
      if (l_found != a_widgets.cend())
      {
        // tell the widget to update
        l_found->get()->changed_at(a_section);

        // If it's section 0, i.e. the name, we have more to do
        if (a_section == 0)
        {
          // Update the tab title
          a_tabwidget->setUpdatesEnabled(false);
          // If we want an icon it goes in here....

          for (int l_index = 0, l_end = a_tabwidget->count(); l_index != l_end; ++l_index)
          {
            if (a_tabwidget->widget(l_index) == l_found->get())
            {
              a_tabwidget->setTabText(l_index, a_handle->cmember_at<0>());
              break;
            }
          }

          a_tabwidget->setUpdatesEnabled(true);
        }
      }
    }

    // When a texture has been added, this is called.
    static void added(vector_type& a_widgets, QTabWidget* a_tabwidget, Project_Data& a_project, Handle_Type const& a_handle)
    {
      qDebug() << "sak::Project_Editor_Widget::Implementation::added "<< QString::fromStdString(Data_Type::type()) <<" " << a_handle.id().value();
      // update the file widget count and open the widget for it.
      // Shouldn't exist yet
      assert(std::find_if(a_widgets.cbegin(),
                          a_widgets.cend(),
                          widget_equals_handle<Data_Type>(a_handle))
              == a_widgets.cend());
      a_widgets.push_back(std::make_unique<Widget_Type>(a_project, a_handle, nullptr));

      // Add it to the tabwidget
      a_tabwidget->setUpdatesEnabled(false);
      // insert the tab at the front
      // If we want an icon it goes in here....
      a_tabwidget->insertTab(0,a_widgets.back().get(), a_handle->cmember_at<0>());
      a_tabwidget->setUpdatesEnabled(true);
      a_tabwidget->setCurrentIndex(0);
    }

    // When a texture has been removed, this is called.
    static void removed(vector_type& a_widgets, QTabWidget* a_tabwidget, Handle_Type const& a_handle)
    {
      qDebug() << "sak::Project_Editor_Widget::Implementation::removed "<< QString::fromStdString(Data_Type::type()) <<" " << a_handle.id().value();
      auto l_found = std::find_if(a_widgets.begin(),
                                  a_widgets.end(),
                                  widget_equals_handle<Data_Type>(a_handle));

      // if it exists, remove it
      if (l_found != a_widgets.cend())
      {
          // Add it to the tabwidget
          a_tabwidget->setUpdatesEnabled(false);
          // If we want an icon it goes in here....

          for (int l_index = 0, l_end = a_tabwidget->count(); l_index != l_end; ++l_index)
          {
              if (a_tabwidget->widget(l_index) == l_found->get())
              {
                  a_tabwidget->removeTab(l_index);
                  break;
              }
          }

          a_tabwidget->setUpdatesEnabled(true);

          // make sure the widget dies
          l_found->reset();
          // erase it
          a_widgets.erase(l_found);
      }
    }

    // When a texture editor is to be opened, this is called.
    static void requests_editor(vector_type& a_widgets, QTabWidget* a_tabwidget, Project_Data& a_project, Handle_Type const& a_handle)
    {
      qDebug() << "sak::Project_Editor_Widget::Implementation::requests_editor "<< QString::fromStdString(Data_Type::type()) <<" " << a_handle.id().value();
      // Find the editor for this handle
      auto l_found = std::find_if(a_widgets.begin(),
                                  a_widgets.end(),
                                  widget_equals_handle<Data_Type>(a_handle));
      // if it exists, focus on it
      if (l_found != a_widgets.cend())
      {
          for (int l_index = 0, l_end = a_tabwidget->count(); l_index != l_end; ++l_index)
          {
              if (a_tabwidget->widget(l_index) == l_found->get())
              {
                  a_tabwidget->setCurrentIndex(l_index);
                  break;
              }
          }
      }
      // otherwise make it and focus on it
      else
      {
          a_widgets.push_back(std::make_unique<Widget_Type>(a_project, a_handle, nullptr));

          // Add it to the tabwidget
          a_tabwidget->setUpdatesEnabled(false);
          // insert the tab at the front
          // If we want an icon it goes in here....
          a_tabwidget->insertTab(0,a_widgets.back().get(), a_handle->cmember_at<0>());
          a_tabwidget->setUpdatesEnabled(true);
          a_tabwidget->setCurrentIndex(0);
      }
    }

    // When focus is changed to be on a texture, call this
    static void requests_focus(Handle_Type const& a_handle)
    {
      qDebug() << "sak::Project_Editor_Widget::Implementation::requests_focus "<< QString::fromStdString(Data_Type::type()) <<" " << a_handle.id().value() << " does nothing.";
    }

    // cast the tabwidget at this index and close it if it's the right type
    static bool close_widget(vector_type& a_widgets, QTabWidget* a_tabwidget, int a_index)
    {
      auto l_editor = dynamic_cast<Widget_Type*>(a_tabwidget->widget(a_index));
      if (l_editor != nullptr)
      {
        a_tabwidget->removeTab(a_index);
        // Now kill the actual widget
        auto l_found = std::find_if(a_widgets.begin(),
                                    a_widgets.end(),
                                    [l_editor](std::unique_ptr<Widget_Type> const& a_widget){ return a_widget.get() == l_editor; });
        l_found->reset();
        a_widgets.erase(l_found);
        return true;
      }
      else
      {
        return false;
      }
    }

    static bool set_focus(Project_Data& a_project, QTabWidget* a_tabwidget, int a_index)
    {
      auto l_editor = dynamic_cast<Widget_Type*>(a_tabwidget->widget(a_index));
      if (l_editor != nullptr)
      {
        Handle_Type const& l_handle = l_editor->cget_handle();
        a_project.get_interface<T>().request_focus(l_handle);

        return true;
      }
      else
      {
        return false;
      }
    }
  };
}


sak::Project_Editor_Widget::Implementation::~Implementation() = default;

sak::Project_Editor_Widget::Implementation::Implementation(Project_Data& a_project):
  Abstract_Project_Signalbox(),
  m_project{a_project},
  m_layout{std::make_unique<QHBoxLayout>()},
  m_stackwidget{std::make_unique<QStackedWidget>()},
  m_background{std::make_unique<Background_Widget>(a_project)},
  m_tabwidget{std::make_unique<QTabWidget>()},
  m_file_widgets{},
  m_texture_widgets{}
{
  m_tabwidget->setMovable(true);
  m_tabwidget->setTabsClosable(true);

  m_project.add_signalbox(this);

  m_stackwidget->addWidget(m_background.get());
  m_stackwidget->addWidget(m_tabwidget.get());
  m_stackwidget->setCurrentIndex(0);
  m_stackwidget->setContentsMargins(0,0,0,0);

  m_layout->addWidget(m_stackwidget.get());
  m_layout->setSpacing(0);
  m_layout->setContentsMargins(0,0,0,0);

  QObject::connect(m_tabwidget.get(), &QTabWidget::tabCloseRequested,
                   [this](int a_index)
  {
    if (do_stuff<File_Data>::close_widget(this->m_file_widgets, this->m_tabwidget.get(), a_index)) return;
    if (do_stuff<Texture_Data>::close_widget(this->m_texture_widgets, this->m_tabwidget.get(), a_index)) return;
  });

  QObject::connect(m_tabwidget.get(), &QTabWidget::currentChanged,
                   [this](int a_index)
  {
    if (a_index != -1)
    {
      {
        if (do_stuff<File_Data>::set_focus(this->m_project, this->m_tabwidget.get(), a_index)) return;
        if (do_stuff<Texture_Data>::set_focus(this->m_project, this->m_tabwidget.get(), a_index)) return;
      }
    }
  });
}

// When a File has its data changed(anything but the name), this is called.
void sak::Project_Editor_Widget::Implementation::changed(File_Handle const& a_handle)
{
  do_stuff<File_Data>::changed(m_file_widgets, a_handle);
}
// When a File has its data changed(anything but the name), this is called.
void sak::Project_Editor_Widget::Implementation::changed_at(File_Handle const& a_handle, std::size_t a_section)
{
  do_stuff<File_Data>::changed_at(m_file_widgets, m_tabwidget.get(), a_handle, a_section);
}
// When a File has been added, this is called.
void sak::Project_Editor_Widget::Implementation::added(File_Handle const& a_handle)
{
  do_stuff<File_Data>::added(m_file_widgets, m_tabwidget.get(), m_project, a_handle);
  update_visible();
}

// When a File has been removed, this is called.
void sak::Project_Editor_Widget::Implementation::removed(File_Handle const& a_handle)
{
  do_stuff<File_Data>::removed(m_file_widgets, m_tabwidget.get(), a_handle);
  update_visible();
}

void sak::Project_Editor_Widget::Implementation::requests_editor(File_Handle const& a_handle)
{
  do_stuff<File_Data>::requests_editor(m_file_widgets, m_tabwidget.get(), m_project, a_handle);
  update_visible();
}

void sak::Project_Editor_Widget::Implementation::requests_focus(File_Handle const& a_handle)
{
  do_stuff<File_Data>::requests_focus(a_handle);
}

// When a texture has its data changed(anything but the name), this is called.
void sak::Project_Editor_Widget::Implementation::changed(Texture_Handle const& a_handle)
{
  do_stuff<Texture_Data>::changed(m_texture_widgets, a_handle);
}
// When a texture has its data changed(anything but the name), this is called.
void sak::Project_Editor_Widget::Implementation::changed_at(Texture_Handle const& a_handle, std::size_t a_section)
{
  do_stuff<Texture_Data>::changed_at(m_texture_widgets, m_tabwidget.get(), a_handle, a_section);
}
// When a texture has been added, this is called.
void sak::Project_Editor_Widget::Implementation::added(Texture_Handle const& a_handle)
{
  do_stuff<Texture_Data>::added(m_texture_widgets, m_tabwidget.get(), m_project, a_handle);
  update_visible();
}

// When a texture has been removed, this is called.
void sak::Project_Editor_Widget::Implementation::removed(Texture_Handle const& a_handle)
{
  do_stuff<Texture_Data>::removed(m_texture_widgets, m_tabwidget.get(), a_handle);
  update_visible();
}

void sak::Project_Editor_Widget::Implementation::requests_editor(Texture_Handle const& a_handle)
{
  do_stuff<Texture_Data>::requests_editor(m_texture_widgets, m_tabwidget.get(), m_project, a_handle);
  update_visible();
}

void sak::Project_Editor_Widget::Implementation::requests_focus(Texture_Handle const& a_handle)
{
  do_stuff<Texture_Data>::requests_focus(a_handle);
}

/*
void sak::Project_Editor_Widget::Implementation::close_tab(int a_index)
{
    auto l_editor = static_cast<file::widget*>(m_tabwidget->widget(a_index));
    m_tabwidget->removeTab(a_index);
    // Now kill the actual widget
    auto l_found = std::find_if(m_file_widgets.begin(),
                                m_file_widgets.end(),
                                [l_editor](std::unique_ptr<file::widget> const& a_widget){ return a_widget.get() == l_editor; });
    l_found->reset();
    m_file_widgets.erase(l_found);
    update_visible();
}
*/
void sak::Project_Editor_Widget::Implementation::update_visible()
{
  if (m_tabwidget->count() == 0)
  {
    m_stackwidget->setCurrentIndex(0);
  }
  else
  {
    m_stackwidget->setCurrentIndex(1);
  }
}

// Special 6
//============================================================
sak::Project_Editor_Widget::Project_Editor_Widget(Project_Data& a_project, QWidget* a_parent):
  QWidget(a_parent),
  m_data{std::make_unique<Implementation>(a_project)}
{
  this->setLayout(imp().m_layout.get());
}
sak::Project_Editor_Widget::~Project_Editor_Widget() = default;

//sak::Project_Editor_Widget::Project_Editor_Widget(Project_Editor_Widget && a_other) = default;
//sak::Project_Editor_Widget& sak::Project_Editor_Widget::operator=(Project_Editor_Widget && a_other) = default;
