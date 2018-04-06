#include "project_outliner_widget.hpp"


//#include "handle.hpp"
//#include "project_interface.hpp"
//#include "section_interface.hpp"
//#include "abstract_project_signalbox.hpp"
#include "outliner_model.hpp"
#include "outliner_delegate.hpp"
#include "outliner_view_widget.hpp"
#include "abstract_outliner_item.hpp"
//#include "project_outliner_items.hpp"
//#include "section_outliner_items.hpp"

#include "abstract_project_outliner_root_item.hpp"

#include "project.hpp"

#include <sak/abstract_observer.hpp>
#include <sak/entity_manager.hpp>
#include <sak/signal.hpp>

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
          public Abstract_Observer
  {
  private:
    // Data Members
    //============================================================
    Project* m_project;
    Outliner_Model m_model;
    Outliner_Delegate m_delegate;
    std::unique_ptr<Abstract_Outliner_Project_Root_Item> m_root;
    std::unique_ptr<QHBoxLayout> m_layout;
    std::unique_ptr<Outliner_View_Widget> m_view;

  public:
    // Special 6
    //============================================================
    Implementation(Project_Outliner_Widget* a_owner, Project* a_project);
    ~Implementation() override final;

    // Recieve a project signal. It should contain everything needed to update
    // and representation of the Project. Guaranteed to be valid for at least
    // the duration of this call.
    void recieve(Signal const& a_signal) override final;

  };
}

sak::Project_Outliner_Widget::Implementation::Implementation(Project_Outliner_Widget* a_owner, Project* a_project):
  Abstract_Observer(),
  m_project{a_project},
  m_model{},
  m_delegate{},
  m_root{std::make_unique<Dummy_Outliner_Project_Root_Item>(a_project).release()},
  m_layout{std::make_unique<QHBoxLayout>()},
  m_view{std::make_unique<Outliner_View_Widget>()}
{
  m_model.set_root(m_root.get());
  assert(m_model.is_active());
  //assert(m_root->get_child_count() == 1);

  // testing the model
  //assert(m_model.parent(QModelIndex()) == QModelIndex());
  //assert(m_model.index(0,0,QModelIndex()).internalPointer() == m_root.get()->get_true_child());
  //assert(m_model.index(0,0,m_model.index(0,0,QModelIndex())).internalPointer() == m_root.get()->get_child(0));

  m_view->setItemDelegate(&m_delegate);
  m_view->set_model(&m_model);

  m_project->entity_manager()->add_observer(this);

  m_layout->setSpacing(0);
  m_layout->setContentsMargins(0,0,0,0);

  m_layout->addWidget(m_view.get());

  a_owner->setLayout(m_layout.get());
}

sak::Project_Outliner_Widget::Implementation::~Implementation() = default;

// Recieve a project signal. It should contain everything needed to update
// and representation of the Project. Guaranteed to be valid for at least
// the duration of this call.
void sak::Project_Outliner_Widget::Implementation::recieve(Signal const& a_signal)
{

}


// Special 6
//============================================================
sak::Project_Outliner_Widget::Project_Outliner_Widget(Project* a_project, QWidget* a_parent):
  QWidget(a_parent),
  m_data{std::make_unique<Implementation>(this, a_project)}
{
}
sak::Project_Outliner_Widget::~Project_Outliner_Widget() = default;

