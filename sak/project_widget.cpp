#include "project_widget.h"

#include <QHBoxLayout>
//#include <QStackedWidget>
#include <QTabWidget>
#include <QScrollArea>
#include <QTreeView>
#include <QLabel>
#include <QDebug>
#include <cassert>
#include <iterator>
#include <algorithm>

#include "file_manager.h"
#include "file_widget.h"
#include "project.h"
#include "../qtlib/outliner/outliner_model.h"
#include "../qtlib/outliner/outliner_delegate.h"
#include "../qtlib/outliner/outliner_treeview.h"
#include "project_outliner_items.h"


//---------------------------------------------------------------------------
// Project_Widget
//---------------------------------------------------------------------------
// Internal constants and implementation
//============================================================
namespace
{
    /*
    Starting with tabs of a single type:
    - vector of widgets for all things of that type.
    - widgets are only made when needed, otherwise they're nullptr
    - widgets get reordered to match order changes in that type of thing.
    - tabs are closed when items are deleted.
    - widgets are deleted when tabs are closed.

    Ergo:
    std::vector<File_Widget> m_file_widgets;
    */




    class Project_Display :
            public QWidget
    {
    public:
        explicit Project_Display(sak::Project const& a_data):
            QWidget(),
            m_layout{std::make_unique<QVBoxLayout>()},
            m_name{std::make_unique<QLabel>(a_data.name())},
            m_location{std::make_unique<QLabel>(a_data.location())},
            m_filepath{std::make_unique<QLabel>(a_data.filepath())},
            m_message{std::make_unique<QLabel>(a_data.message())},
            m_content{std::make_unique<QLabel>(a_data.content())}
        {
            m_layout->addWidget(m_name.get());
            m_layout->addWidget(m_location.get());
            m_layout->addWidget(m_filepath.get());
            m_layout->addWidget(m_message.get());
            m_layout->addWidget(m_content.get());
            this->setLayout(m_layout.get());
        }



    private:
        std::unique_ptr<QVBoxLayout> m_layout;
        std::unique_ptr<QLabel> m_name;
        std::unique_ptr<QLabel> m_location;
        std::unique_ptr<QLabel> m_filepath;
        std::unique_ptr<QLabel> m_message;
        std::unique_ptr<QLabel> m_content;
    };

}

// Pimpl Data
//============================================================
namespace sak
{
    class Project_Widget::Implementation :
            public Project_Signalbox
    {
    public:
        std::unique_ptr<Project> m_data;
        qtlib::outliner::Model m_model;
        qtlib::outliner::Delegate m_delegate;

        std::unique_ptr<outliner::Root_Item> m_root;

        std::unique_ptr<QHBoxLayout> m_layout;
        std::unique_ptr<qtlib::outliner::Treeview> m_outliner;
        std::unique_ptr<QTabWidget> m_tabs;
        std::unique_ptr<Project_Display> m_display;

        std::vector<std::unique_ptr<File_Widget>> m_file_widgets;


        explicit Implementation(std::unique_ptr<Project>&& a_data, Project_Widget& a_widget):
            m_data{std::move(a_data)},
            m_model{},
            m_delegate{},
            m_root{std::make_unique<outliner::Root_Item>(*m_data, a_widget)},
            m_layout{std::make_unique<QHBoxLayout>()},
            m_outliner{std::make_unique<qtlib::outliner::Treeview>()},
            m_tabs{std::make_unique<QTabWidget>()},
            m_display{std::make_unique<Project_Display>(*m_data)},
            m_file_widgets{}
        {
            m_model.set_root(m_root.get());
            assert(m_model.is_active());
            assert(m_root->get_child_count() == 1);
            //assert(m_root->get_child_at(0)->child_count() == 2);
            //assert(m_root->get_child_at(0)->get_parent() == m_root.get());
            //assert(m_root->get_child_at(0)->get_data(Qt::DisplayRole) == m_data.name());

            // testing the model
            assert(m_model.parent(QModelIndex()) == QModelIndex());
            assert(m_model.index(0,0,QModelIndex()).internalPointer() == m_root.get()->get_child_at(0));
            //assert(m_model.index(0,0,m_model.index(0,0,QModelIndex())).internalPointer() == m_root.get()->get_child(0));

            m_outliner->setItemDelegate(&m_delegate);
            m_outliner->set_model(&m_model);

            m_data->add_signalbox(this);

            m_tabs->setMovable(true);
            m_tabs->setTabsClosable(false); // ok how are we supporting this

            m_layout->addWidget(m_outliner.get());
            m_layout->setStretchFactor(m_outliner.get(),1);
            m_layout->addWidget(m_tabs.get());
            m_layout->setStretchFactor(m_tabs.get(),2);
            m_layout->addWidget(m_display.get());
        }

        ~Implementation() override = default;

        // When the Files section has changed order due to a name change, this is called.
        void file_names_reordered() override final
        {
            // Outliner update
            //-----------------------------------
            auto l_files_item = m_root->get_true_child()->get_true_child<0>();
            auto l_file_count = l_files_item->get_child_count();
            if (l_file_count > 1)
            {
                auto l_top_left_index = m_model.create_index_from_item(l_files_item->get_true_child_at(0));
                auto l_bottom_right_index = m_model.create_index_from_item(l_files_item->get_true_child_at(l_file_count));
                m_model.data_changed(l_top_left_index, l_bottom_right_index, QVector<int>(Qt::DisplayRole));
            }

            // Editor update
            //-----------------------------------
            // don't care


        }
        // When a File has had its name changed, this is called.
        void file_name_changed(File_Handle const& a_file, std::size_t a_index_old, std::size_t a_index_new) override final
        {
            // Outliner update
            //-----------------------------------
            //qDebug() << "Move " << a_index_old << " to " << a_index_new;

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

            // Editor update
            //-----------------------------------
            // Find the editor for this handle
            auto l_found = std::find_if(m_file_widgets.cbegin(),
                                        m_file_widgets.cend(),
                                        File_Widget_Equals_Handle(a_file));

            // if it exists, update it
            if (l_found != m_file_widgets.cend())
            {
                // update the widget contents
                l_found->get()->update();


                // update the tab name

                m_tabs->setUpdatesEnabled(false);
                // If we want an icon it goes in here....

                for (int l_index = 0, l_end = m_tabs->count(); l_index != l_end; ++l_index)
                {
                    if (m_tabs->widget(l_index) == l_found->get())
                    {
                        m_tabs->setTabText(l_index, a_file.cget().cget_name());
                        break;
                    }
                }

                m_tabs->setUpdatesEnabled(true);
            }
        }
        // When a File has its data changed(anything but the name), this is called.
        void file_data_changed(File_Handle const& a_file, std::size_t a_index) override final
        {
            // Outliner update
            //-----------------------------------
            // no outliner changes

            // Editor update
            //-----------------------------------
            // Find the editor for this handle
            auto l_found = std::find_if(m_file_widgets.cbegin(),
                                        m_file_widgets.cend(),
                                        File_Widget_Equals_Handle(a_file));

            // if it exists, update it
            if (l_found != m_file_widgets.cend())
            {
                l_found->get()->update();
            }
        }
        // When a File has been added, this is called.
        void file_added(File_Handle const& a_file, std::size_t a_index) override final
        {
            // Outliner update
            //-----------------------------------
            auto l_files_item = m_root->get_true_child()->get_true_child<0>();
            auto l_model_index = m_model.create_index_from_item(l_files_item);
            auto l_inserter = m_model.make_row_inserter(a_index,l_model_index);
            // add a new file
            auto l_old = l_files_item->get_child_count();
            l_files_item->update();
            assert(l_old + 1 == l_files_item->get_child_count());


            // Editor update
            //-----------------------------------
            // update the file widget count and open the widget for it.
            // Shouldn't exist yet
            assert(std::find_if(m_file_widgets.cbegin(),
                                m_file_widgets.cend(),
                                File_Widget_Equals_Handle(a_file))
                    == m_file_widgets.cend());
            m_file_widgets.push_back(std::make_unique<File_Widget>(a_file, nullptr));

            // Add it to the tabwidget
            m_tabs->setUpdatesEnabled(false);
            // insert the tab at the front
            // If we want an icon it goes in here....
            m_tabs->insertTab(0,m_file_widgets.back().get(), a_file.cget().cget_name());
            m_tabs->setUpdatesEnabled(true);
            m_tabs->setCurrentIndex(0);
        }

        // When a File has been removed, this is called.
        void file_removed(File_Handle const& a_file, std::size_t a_index) override final
        {
            // Outliner update
            //-----------------------------------

            auto l_files_item = m_root->get_true_child()->get_true_child<0>();
            auto l_model_index = m_model.create_index_from_item(l_files_item);
            auto l_remover = m_model.make_row_remover(a_index,l_model_index);
            // add a new file
            auto l_old = l_files_item->get_child_count();
            l_files_item->update();
            assert(l_old - 1 == l_files_item->get_child_count());

            // Editor update
            //-----------------------------------
            // Find the editor for this handle
            auto l_found = std::find_if(m_file_widgets.begin(),
                                        m_file_widgets.end(),
                                        File_Widget_Equals_Handle(a_file));

            // if it exists, remove it
            if (l_found != m_file_widgets.cend())
            {
                // Add it to the tabwidget
                m_tabs->setUpdatesEnabled(false);
                // If we want an icon it goes in here....

                for (int l_index = 0, l_end = m_tabs->count(); l_index != l_end; ++l_index)
                {
                    if (m_tabs->widget(l_index) == l_found->get())
                    {
                        m_tabs->removeTab(l_index);
                        break;
                    }
                }

                m_tabs->setUpdatesEnabled(true);

                // make sure the widget dies
                l_found->reset();
                // erase it
                m_file_widgets.erase(l_found);
            }
        }

        void file_editor_requested(File_Handle const& a_file, std::size_t a_index)
        {
            // Find the editor for this handle
            auto l_found = std::find_if(m_file_widgets.begin(),
                                        m_file_widgets.end(),
                                        File_Widget_Equals_Handle(a_file));
            // if it exists, focus on it
            if (l_found != m_file_widgets.cend())
            {
                for (int l_index = 0, l_end = m_tabs->count(); l_index != l_end; ++l_index)
                {
                    if (m_tabs->widget(l_index) == l_found->get())
                    {
                        m_tabs->setCurrentIndex(l_index);
                        break;
                    }
                }
            }
            // otherwise make it and focus on it
            else
            {
                m_file_widgets.push_back(std::make_unique<File_Widget>(a_file, nullptr));

                // Add it to the tabwidget
                m_tabs->setUpdatesEnabled(false);
                // insert the tab at the front
                // If we want an icon it goes in here....
                m_tabs->insertTab(0,m_file_widgets.back().get(), a_file.cget().cget_name());
                m_tabs->setUpdatesEnabled(true);
                m_tabs->setCurrentIndex(0);
            }
        }

    };
}

// Special 6
//============================================================
/*
sak::Project_Widget::Project_Widget(QString const& a_name, QString const& a_location, QWidget* a_parent):
    QWidget(a_parent),
    m_data{std::make_unique<Data>(Project_Data{(a_name, a_location)})}
{
    data().m_layout->addWidget(data().m_outliner.get());
    data().m_layout->setStretchFactor(data().m_outliner.get(),1);
    data().m_layout->addWidget(data().m_tabs.get());
    data().m_layout->setStretchFactor(data().m_tabs.get(),2);
    data().m_layout->addWidget(data().m_display.get());

    this->setLayout(data().m_layout.get());
}
*/

// Create a Project with the given filepath.
sak::Project_Widget::Project_Widget(std::unique_ptr<Project>&& a_project, QWidget* a_parent):
   // Project_Widget(QFileInfo(a_filepath).fileName(), QFileInfo(a_filepath).absoluteDir().absolutePath(), a_parent)
    QWidget(a_parent),
    m_data{std::make_unique<Implementation>(std::move(a_project),*this)}
{
    this->setLayout(imp().m_layout.get());
}


// Menu Actions
//============================================================
// Actions that can be done on a project that needs direct support in the widget.
// Some of these tasks will have come from the Project_Window.

// Menu Bar -> File
//============================================================
// Save the Project data.
void sak::Project_Widget::save_project()
{
    cimp().m_data->save();
}

// Menu Bar -> Edit
//============================================================
// Undo the last command issued.
void sak::Project_Widget::undo()
{

}

// Redo the last undone command in the command history
void sak::Project_Widget::redo()
{

}

// View the entire command history of the project.
void sak::Project_Widget::view_history()
{

}

// Cleat the undo/redo history of of the Project.
void sak::Project_Widget::clear_history()
{

}

// Menu Bar -> Component
//============================================================
// Create a new File in the active Project;
void sak::Project_Widget::create_file()
{

}

// Create a new Texture in the active Project;
void sak::Project_Widget::create_texture()
{

}

// Create a new Material in the active Project;
void sak::Project_Widget::create_material()
{

}

// Create a new Model in the active Project;
void sak::Project_Widget::create_model()
{

}

// Create a new Package in the active Project;
void sak::Project_Widget::create_package()
{

}

// Create a new Release in the active Project;
void sak::Project_Widget::create_release()
{

}

// Menu Bar -> Build
//============================================================
// Build all the components of the Project.
void sak::Project_Widget::build_project()
{

}

// Reuild all the components of the Project.
void sak::Project_Widget::rebuild_project()
{

}

// Delete all the temporary and resulting files from building the Project.
void sak::Project_Widget::clean_project()
{

}

// Build the currently selected Component of the Project.
void sak::Project_Widget::build_component()
{

}

// Reuild the currently selected Component of the Project.
void sak::Project_Widget::rebuild_component()
{

}

// Delete all the temporary and resulting files from building the currently
// selected Component of the Project.
void sak::Project_Widget::clean_component()
{

}

// Menu Bar -> Install
//============================================================
// Review the current install status of all components.
void sak::Project_Widget::install_status()
{

}

// Install the current component. Opens a dialog detailing required options
// and the status of the install.
void sak::Project_Widget::install_component()
{

}

// Delete all the temporary and resulting files from building the Project.
void sak::Project_Widget::uninstall_component()
{

}

// Uninstalls all the components that are currently installed.
void sak::Project_Widget::uninstall_all()
{

}

// Interface
//============================================================
// State query helpers for determining whether actions are
// currently active, and what they do.


// Get the name of the project.
QString sak::Project_Widget::name() const
{
    return cimp().m_data->name();
}

// Get the root directory of the project.
QString sak::Project_Widget::location() const
{
    return cimp().m_data->location();
}

// Can we currently call undo?
bool sak::Project_Widget::can_undo() const
{
    return false;
}

// Can we currently call redo?
bool sak::Project_Widget::can_redo() const
{
    return false;
}

// Get the name of the currently selected component. Empty if none is selected.
QString sak::Project_Widget::selected_component_name() const
{
    return QString();
}

// Is a component selected? If no project is open, this is always false.
bool sak::Project_Widget::is_component_selected() const
{
    return false;
}

// Is the selected component buildable? If no component is open, this is always false.
bool sak::Project_Widget::is_component_buildable() const
{
    return false;
}

// Is the selected component installable? If no component is open, this is always false.
bool sak::Project_Widget::is_component_installable() const
{
    return false;
}

// File Interface
//============================================================
// Open the editor for the File at this index.
// This is called by outliner::File_Item can might be better off hidden?
void sak::Project_Widget::open_file_editor(std::size_t a_index)
{
    imp().file_editor_requested(cimp().m_data->get_file_at(a_index), a_index);
}
