#include "project_editor_widget.hpp"

#include <sak/abstract_observer.hpp>
#include <sak/signal.hpp>
#include <sak/entity_manager.hpp>

#include "project.hpp"


#include <cassert>
#include <iterator>
#include <algorithm>

#include <QHBoxLayout>
#include <QStackedWidget>
#include <QTabWidget>
#include <QDebug>
#include <QLabel>

//---------------------------------------------------------------------------
// Project_Editor_Widget
//---------------------------------------------------------------------------
namespace
{
  QString make_background_text(sak::Project* a_project)
  {
    QString l_result{a_project->name()};
    l_result.append(u8"\n\nNothing open. Open an item from the outliner.");
    return l_result;
  }

  // Seperating out since we might want to change this to display information.
  class Background_Widget :
        public QLabel
  {
  public:
    explicit Background_Widget(sak::Project* a_project):
        QLabel(make_background_text(a_project), nullptr)
    {
        this->setAlignment(Qt::AlignCenter);
    }
    ~Background_Widget() override = default;
  };
}




// Pimpl Data
//============================================================
namespace sak
{
  class Project_Editor_Widget::Implementation :
      public Abstract_Observer
  {
  private:
    Project* m_project;
    std::unique_ptr<QHBoxLayout> m_layout;
    std::unique_ptr<QStackedWidget> m_stackwidget;
    std::unique_ptr<Background_Widget> m_background;
    std::unique_ptr<QTabWidget> m_tabwidget;
    //std::vector<std::unique_ptr<File_Widget>> m_file_widgets;
    //std::vector<std::unique_ptr<Texture_Widget>> m_texture_widgets;

  public:
    Implementation(Project_Editor_Widget* a_owner, Project* a_project);
    ~Implementation() override final;

    // Recieve a project signal. It should contain everything needed to update
    // and representation of the Project. Guaranteed to be valid for at least
    // the duration of this call.
    void recieve(Signal const& a_signal) override final;

    //void close_tab(int a_index);

    void update_visible();

  };
}


sak::Project_Editor_Widget::Implementation::Implementation(Project_Editor_Widget* a_owner, Project* a_project):
  Abstract_Observer(),
  m_project{a_project},
  m_layout{std::make_unique<QHBoxLayout>()},
  m_stackwidget{std::make_unique<QStackedWidget>()},
  m_background{std::make_unique<Background_Widget>(a_project)},
  m_tabwidget{std::make_unique<QTabWidget>()}
{
  m_tabwidget->setMovable(true);
  m_tabwidget->setTabsClosable(true);

  m_project->entity_manager()->add_observer(this);

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
    //if (do_stuff<File_Data>::close_widget(this->m_file_widgets, this->m_tabwidget.get(), a_index)) return;
    //if (do_stuff<Texture_Data>::close_widget(this->m_texture_widgets, this->m_tabwidget.get(), a_index)) return;
  });

  QObject::connect(m_tabwidget.get(), &QTabWidget::currentChanged,
                   [this](int a_index)
  {
    if (a_index != -1)
    {
      {
        //if (do_stuff<File_Data>::set_focus(this->m_project, this->m_tabwidget.get(), a_index)) return;
        //if (do_stuff<Texture_Data>::set_focus(this->m_project, this->m_tabwidget.get(), a_index)) return;
      }
    }
  });

  // Initialise the owner of this.
  a_owner->setLayout(m_layout.get());
}

sak::Project_Editor_Widget::Implementation::~Implementation()
{
  m_project->entity_manager()->remove_observer(this);
}

// Recieve a project signal. It should contain everything needed to update
// and representation of the Project. Guaranteed to be valid for at least
// the duration of this call.
void sak::Project_Editor_Widget::Implementation::recieve(Signal const& a_signal)
{

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
sak::Project_Editor_Widget::Project_Editor_Widget(Project* a_project, QWidget* a_parent):
  QWidget(a_parent),
  m_data{std::make_unique<Implementation>(this, a_project)}
{
}
sak::Project_Editor_Widget::~Project_Editor_Widget() = default;
