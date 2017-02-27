#include "project_editor.hpp"

#include <QHBoxLayout>
#include <QStackedWidget>
#include <QTabWidget>
#include <QDebug>
#include <QLabel>
#include <cassert>
#include <iterator>
#include <algorithm>

#include "project_signalbox.hpp"
#include "file_manager.hpp"
#include "file_widget.hpp"
#include "project.hpp"
#include "file_interface.hpp"

//---------------------------------------------------------------------------
// Project_Editor
//---------------------------------------------------------------------------
namespace
{
    QString make_background_text(sak::Project& a_project)
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
        explicit Background_Widget(sak::Project& a_project):
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
    class Project_Editor::Implementation :
            public Project_Signalbox
    {
    public:
        Project& m_project;
        std::unique_ptr<QHBoxLayout> m_layout;
        std::unique_ptr<QStackedWidget> m_stackwidget;
        std::unique_ptr<Background_Widget> m_background;
        std::unique_ptr<QTabWidget> m_tabwidget;
        std::vector<std::unique_ptr<File_Widget>> m_file_widgets;

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

        void close_tab(int a_index);

        void update_visible();
    };
}


sak::Project_Editor::Implementation::~Implementation() = default;

sak::Project_Editor::Implementation::Implementation(Project& a_project):
    Project_Signalbox(),
    m_project{a_project},
    m_layout{std::make_unique<QHBoxLayout>()},
    m_stackwidget{std::make_unique<QStackedWidget>()},
    m_background{std::make_unique<Background_Widget>(a_project)},
    m_tabwidget{std::make_unique<QTabWidget>()},
    m_file_widgets{}
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
                     [this](int a_index){ this->close_tab(a_index); });

    QObject::connect(m_tabwidget.get(), &QTabWidget::currentChanged,
                     [this](int a_index)
    {
        if (a_index != -1)
        {
            auto l_widget = static_cast<File_Widget*>(this->m_tabwidget->widget(a_index));
            if (l_widget != nullptr)
            {
                File_Handle const& l_file = l_widget->cget_file();
                this->m_project.get_signalbox()->requests_focus(l_file);
            }
        }
    });
}

// When a File has had its name changed, this is called.
void sak::Project_Editor::Implementation::name_changed(File_Handle const& a_file)
{
    qDebug() << "Project_Editor::Implementation::name_changed";
    // Find the editor for this handle
    auto l_found = std::find_if(m_file_widgets.cbegin(),
                                m_file_widgets.cend(),
                                File_Widget_Equals_Handle(a_file));

    // if it exists, update it
    if (l_found != m_file_widgets.cend())
    {
        // update the widget contents
        l_found->get()->update_name();

        // update the tab name

        m_tabwidget->setUpdatesEnabled(false);
        // If we want an icon it goes in here....

        for (int l_index = 0, l_end = m_tabwidget->count(); l_index != l_end; ++l_index)
        {
            if (m_tabwidget->widget(l_index) == l_found->get())
            {
                m_tabwidget->setTabText(l_index, a_file.cget().cget_name());
                break;
            }
        }

        m_tabwidget->setUpdatesEnabled(true);
    }
}
// When a File has had its description changed, this is called.
void sak::Project_Editor::Implementation::description_changed(File_Handle const& a_file)
{
    qDebug() << "Project_Editor::Implementation::description_changed";
    // Find the editor for this handle
    auto l_found = std::find_if(m_file_widgets.cbegin(),
                                m_file_widgets.cend(),
                                File_Widget_Equals_Handle(a_file));

    // if it exists, update it
    if (l_found != m_file_widgets.cend())
    {
        // update the widget contents
        l_found->get()->update_description();
    }
}
// When a File has its data changed(anything but the name), this is called.
void sak::Project_Editor::Implementation::data_changed(File_Handle const& a_file)
{
    qDebug() << "Project_Editor::Implementation::data_changed";
    // Find the editor for this handle
    auto l_found = std::find_if(m_file_widgets.cbegin(),
                                m_file_widgets.cend(),
                                File_Widget_Equals_Handle(a_file));

    // if it exists, update it
    if (l_found != m_file_widgets.cend())
    {
        l_found->get()->update_data();
    }

}
// When a File has its data changed(anything but the name), this is called.
void sak::Project_Editor::Implementation::data_changed_at(File_Handle const& a_file, std::size_t a_section)
{
    qDebug() << "Project_Editor::Implementation::data_changed_at";
    // Find the editor for this handle
    auto l_found = std::find_if(m_file_widgets.cbegin(),
                                m_file_widgets.cend(),
                                File_Widget_Equals_Handle(a_file));

    // if it exists, update it
    if (l_found != m_file_widgets.cend())
    {
        l_found->get()->update_data_at(a_section);
    }

}
// When a File has been added, this is called.
void sak::Project_Editor::Implementation::added(File_Handle const& a_file)
{
    qDebug() << "Project_Editor::Implementation::added";
    // update the file widget count and open the widget for it.
    // Shouldn't exist yet
    assert(std::find_if(m_file_widgets.cbegin(),
                        m_file_widgets.cend(),
                        File_Widget_Equals_Handle(a_file))
            == m_file_widgets.cend());
    m_file_widgets.push_back(std::make_unique<File_Widget>(a_file, nullptr));

    // Add it to the tabwidget
    m_tabwidget->setUpdatesEnabled(false);
    // insert the tab at the front
    // If we want an icon it goes in here....
    m_tabwidget->insertTab(0,m_file_widgets.back().get(), a_file.cget().cget_name());
    m_tabwidget->setUpdatesEnabled(true);
    m_tabwidget->setCurrentIndex(0);
    update_visible();
}

// When a File has been removed, this is called.
void sak::Project_Editor::Implementation::removed(File_Handle const& a_file)
{
    qDebug() << "Project_Editor::Implementation::removed";
    auto l_found = std::find_if(m_file_widgets.begin(),
                                m_file_widgets.end(),
                                File_Widget_Equals_Handle(a_file));

    // if it exists, remove it
    if (l_found != m_file_widgets.cend())
    {
        // Add it to the tabwidget
        m_tabwidget->setUpdatesEnabled(false);
        // If we want an icon it goes in here....

        for (int l_index = 0, l_end = m_tabwidget->count(); l_index != l_end; ++l_index)
        {
            if (m_tabwidget->widget(l_index) == l_found->get())
            {
                m_tabwidget->removeTab(l_index);
                break;
            }
        }

        m_tabwidget->setUpdatesEnabled(true);

        // make sure the widget dies
        l_found->reset();
        // erase it
        m_file_widgets.erase(l_found);
    }
    update_visible();
}

void sak::Project_Editor::Implementation::requests_editor(File_Handle const& a_file)
{
    qDebug() << "Project_Editor::Implementation::requests_editor";
    // Find the editor for this handle
    auto l_found = std::find_if(m_file_widgets.begin(),
                                m_file_widgets.end(),
                                File_Widget_Equals_Handle(a_file));
    // if it exists, focus on it
    if (l_found != m_file_widgets.cend())
    {
        for (int l_index = 0, l_end = m_tabwidget->count(); l_index != l_end; ++l_index)
        {
            if (m_tabwidget->widget(l_index) == l_found->get())
            {
                m_tabwidget->setCurrentIndex(l_index);
                break;
            }
        }
    }
    // otherwise make it and focus on it
    else
    {
        m_file_widgets.push_back(std::make_unique<File_Widget>(a_file, nullptr));

        // Add it to the tabwidget
        m_tabwidget->setUpdatesEnabled(false);
        // insert the tab at the front
        // If we want an icon it goes in here....
        m_tabwidget->insertTab(0,m_file_widgets.back().get(), a_file.cget().cget_name());
        m_tabwidget->setUpdatesEnabled(true);
        m_tabwidget->setCurrentIndex(0);
    }
    update_visible();
}

void sak::Project_Editor::Implementation::requests_focus(File_Handle const&)
{
    qDebug() << "Project_Editor::Implementation::requests_focus";
    // nothing for now
}

void sak::Project_Editor::Implementation::close_tab(int a_index)
{
    auto l_editor = static_cast<File_Widget*>(m_tabwidget->widget(a_index));
    m_tabwidget->removeTab(a_index);
    // Now kill the actual widget
    auto l_found = std::find_if(m_file_widgets.begin(),
                                m_file_widgets.end(),
                                [l_editor](std::unique_ptr<File_Widget> const& a_widget){ return a_widget.get() == l_editor; });
    l_found->reset();
    m_file_widgets.erase(l_found);
    update_visible();
}

void sak::Project_Editor::Implementation::update_visible()
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
sak::Project_Editor::Project_Editor(Project& a_project, QWidget* a_parent):
    QWidget(a_parent),
    m_data{std::make_unique<Implementation>(a_project)}
{
    this->setLayout(imp().m_layout.get());
}
sak::Project_Editor::~Project_Editor() = default;
