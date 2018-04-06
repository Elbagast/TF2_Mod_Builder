#include "project_main_widget.hpp"

#include "project.hpp"
#include "project_editor_widget.hpp"
#include "project_outliner_widget.hpp"

#include <cassert>
#include <iterator>
#include <algorithm>

#include <QDebug>
#include <QHBoxLayout>
#include <QSplitter>


// Pimpl Data
//============================================================
namespace sak
{
  //---------------------------------------------------------------------------
  // Project_Main_Widget::Implementation
  //---------------------------------------------------------------------------
  class Project_Main_Widget::Implementation
  {
  private:
    // Data Members
    //============================================================
    Project* m_project;
    std::unique_ptr<QHBoxLayout> m_layout;

    // Because QSplitter takes ownership it must be before the widgets it holds.
    // This means the unique_ptr destructor is called after it knows its children are dead.
    std::unique_ptr<QSplitter> m_splitter;
    std::unique_ptr<Project_Outliner_Widget> m_outliner;
    std::unique_ptr<Project_Editor_Widget> m_editor;

  public:
    // Special 6
    //============================================================
    Implementation(Project_Main_Widget* a_owner, Project* a_project);
    ~Implementation();
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Project_Main_Widget::Implementation
//---------------------------------------------------------------------------
sak::Project_Main_Widget::Implementation::Implementation(Project_Main_Widget* a_owner, Project* a_project):
  m_project{a_project},
  m_layout{std::make_unique<QHBoxLayout>()},
  m_splitter{std::make_unique<QSplitter>(Qt::Horizontal, nullptr)},
  m_outliner{std::make_unique<Project_Outliner_Widget>(m_project, nullptr)},
  m_editor{std::make_unique<Project_Editor_Widget>(m_project, nullptr)}
{
  m_splitter->addWidget(m_outliner.get());
  m_splitter->addWidget(m_editor.get());
  m_splitter->setStretchFactor(0,1);
  m_splitter->setStretchFactor(1,3);
  m_splitter->setChildrenCollapsible(false);

  m_layout->addWidget(m_splitter.get());
  m_layout->setSpacing(0);

  a_owner->setLayout(m_layout.get());
}

sak::Project_Main_Widget::Implementation::~Implementation() = default;


//------------------------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Project_Main_Widget
//---------------------------------------------------------------------------

// Special 6
//============================================================
// Create a Project with the given filepath.
sak::Project_Main_Widget::Project_Main_Widget(Project* a_project, QWidget* a_parent):
  QWidget(a_parent),
  m_data{std::make_unique<Implementation>(this, a_project)}
{
}

sak::Project_Main_Widget::~Project_Main_Widget() = default;
