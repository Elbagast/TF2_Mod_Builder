#include "project_main_window.h"
#include "ui_project_main_window.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QtGlobal>
#include <numeric>

#include "qstring_operations.h"
#include "project_widget.h"

// Static Data Members
//============================================================
Saklib::String const Saklib::Qtlib::Project_Main_Window::s_app_name{"TF2 Mod Builder"};
Saklib::String const Saklib::Qtlib::Project_Main_Window::s_new_name_front{"new_"};
Saklib::size_type Saklib::Qtlib::Project_Main_Window::s_new_count{0};

// Special 6
//============================================================
Saklib::Qtlib::Project_Main_Window::Project_Main_Window(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::Project_Main_Window),
    m_project_widget(nullptr),
    m_window_title(this, s_app_name.c_str())
{
    // Setup the ui
    m_ui->setupUi(this);

    // Connect and setup the Menu actions

    // File
    //====================
    QObject::connect(m_ui->actionNew_Project, &QAction::triggered, this, &Project_Main_Window::actionSlot_New_Project);
    QObject::connect(m_ui->actionOpen_Project, &QAction::triggered, this, &Project_Main_Window::actionSlot_Open_Project);
    QObject::connect(m_ui->actionSave_Project, &QAction::triggered, this, &Project_Main_Window::actionSlot_Save_Project);
    QObject::connect(m_ui->actionSave_Project_As, &QAction::triggered, this, &Project_Main_Window::actionSlot_Save_Project_As);
    QObject::connect(m_ui->actionExit, &QAction::triggered, this, &Project_Main_Window::actionSlot_Exit);

    // Edit
    //====================
    QObject::connect(m_ui->actionUndo, &QAction::triggered, this, &Project_Main_Window::actionSlot_Undo);
    QObject::connect(m_ui->actionRedo, &QAction::triggered, this, &Project_Main_Window::actionSlot_Redo);
    QObject::connect(m_ui->actionClear_History, &QAction::triggered, this, &Project_Main_Window::actionSlot_Clear_History);

    // Make a new project in m_project_widget, updating the window title when doing so
    new_project();
    // Alternatively open a supplied filepath?
}
Saklib::Qtlib::Project_Main_Window::Project_Main_Window(Path const& filepath, QWidget *parent) :
    Project_Main_Window(parent)
{
    // runs the main constructor, then opens the project
    open_project(filepath);
}

// Qt Creator hates this line even though it's legal and works
Saklib::Qtlib::Project_Main_Window::~Project_Main_Window() = default;

// Menu Action Slots
//============================================================

// File
//====================
bool Saklib::Qtlib::Project_Main_Window::actionSlot_New_Project()
{
    // if there's a project ask to save it and stop if the user cancels out
    if (m_project_widget
        && has_unsaved_edits()
        && !ask_to_save() )
        return false;

    new_project();
    return true;
}
bool Saklib::Qtlib::Project_Main_Window::actionSlot_Open_Project()
{
    // if there's a project ask to save it and stop if the user cancels out
    if (m_project_widget
        && has_unsaved_edits()
        && !ask_to_save() )
        return false;

    // get a fileName that may exist
    QString filepath = QFileDialog::getOpenFileName(this,
                                                    tr("Open Project"),
                                                    "", // application default project folder would go here
                                                    tr("TF2MB Projects (*.tf2mb)"));
     // if we didn't get something we can use then stop
    if (filepath.isEmpty())
        return false;

    open_project(to_Path(filepath));
    return true;
}
//--------------------
bool Saklib::Qtlib::Project_Main_Window::actionSlot_Save_Project()
{
    // if there is a project widget and project data (sanity check)
    if (m_project_widget)// && m_project_widget->getProject())
    {
        // if the project name starts with "new_", call saveAs
        if(m_project_widget->filepath().empty()
           || to_QString(m_project_widget->filepath()).startsWith(s_new_name_front.c_str())
           )
        {
            return actionSlot_Save_Project_As();
        }
        else
        {
            m_project_widget->save();
            m_window_title.set_unsaved_edits(false);
            return true;
        }
    }
    else
        return false;
}
bool Saklib::Qtlib::Project_Main_Window::actionSlot_Save_Project_As()
{
    // if there is a project widget and project data (sanity check)
    if (m_project_widget)// && m_project_widget->getProject())
    {
        // get a fileName that may not exist
        QString filePath = QFileDialog::getSaveFileName(this,
                                                        tr("New Project"),
                                                        "", // application default project folder would go here
                                                        tr("TF2MB Projects (*.tf2mb)"));
        // if we didn't get something we can use then stop
        if (filePath.isEmpty())
            return false;

        m_project_widget->save_as(to_String(filePath));

        // Update the window title with the new file path and editing state
        m_window_title.set_variable_title(filePath);

        return true;
    }
    else
        return false;
}
//--------------------
bool Saklib::Qtlib::Project_Main_Window::actionSlot_Exit()
{
    // Forward to a close event that is dealt with in closeEvent()
    return QMainWindow::close();
}

// Edit
//====================
void Saklib::Qtlib::Project_Main_Window::actionSlot_Undo()
{
    m_project_widget->undo();
}

void Saklib::Qtlib::Project_Main_Window::actionSlot_Redo()
{
    m_project_widget->redo();
}

void Saklib::Qtlib::Project_Main_Window::actionSlot_Clear_History()
{
    m_project_widget->clear_history();
}


// Other Slots
//============================================================
// If something edits data, call this.
void Saklib::Qtlib::Project_Main_Window::slot_unsaved_edits(bool state)
{
    m_window_title.set_unsaved_edits(state);
}
void Saklib::Qtlib::Project_Main_Window::slot_update_undo_actions(size_type undo_count, size_type redo_count)
{
    m_ui->actionUndoCount->setText(to_QString(undo_count));
    m_ui->actionRedoCount->setText(to_QString(redo_count));

    // enable or disable Undo
    if (undo_count == 0)
        m_ui->actionUndo->setEnabled(false);
    else
        m_ui->actionUndo->setEnabled(true);

    // enable or disable Redo
    if (redo_count == 0)
        m_ui->actionRedo->setEnabled(false);
    else
        m_ui->actionRedo->setEnabled(true);

    // enable or disable Clear History
    if (undo_count == 0 && redo_count == 0)
        m_ui->actionClear_History->setEnabled(false);
    else
        m_ui->actionClear_History->setEnabled(true);
}

// Virtuals
//============================================================
// Needed so that the console window can be cleaned up properly.
void Saklib::Qtlib::Project_Main_Window::closeEvent(QCloseEvent *event)
{
    // if any of these are true then we can saftely exit and will
    if (!m_project_widget                    // no widget so nothing in it to save
        || !has_unsaved_edits()               // there is data but it's saved already so just exit
        || ask_to_save()                    // ask the user if we can exit via the save dialog
        )
    {
        // Handle the event as normal
        QMainWindow::closeEvent(event);
    }
    // else ignore it and stay open
    else
        event->ignore();
}

// Convenience
//============================================================
// Makes a new, empty project with a placeholder name
void Saklib::Qtlib::Project_Main_Window::new_project()
{
    String project_name = s_new_name_front + std::to_string(++s_new_count);

    m_project_widget = std::make_unique<Project_Widget>(Saklib::to_Path(project_name));

    setCentralWidget(m_project_widget.get());
    QObject::connect(m_project_widget.get(), &Project_Widget::signal_unsaved_edits,
                     this, &Project_Main_Window::slot_unsaved_edits);
    QObject::connect(m_project_widget.get(), &Project_Widget::signal_update_undo_actions,
                     this, &Project_Main_Window::slot_update_undo_actions);

    // Update the window title with the new file path and editing state
    m_window_title.set_variable_title(to_QString(m_project_widget->filepath()));
    slot_update_undo_actions(0,0);
}
// Opens a project and loads the data found in the file.
void Saklib::Qtlib::Project_Main_Window::open_project(Path const& filepath)   // currently a clone of newProject
{
    // Make a completely new widget using this file path - potentially want to change this?
    m_project_widget = std::make_unique<Project_Widget>(filepath);

    // Make it into the central widget
    setCentralWidget(m_project_widget.get());

    QObject::connect(m_project_widget.get(), &Project_Widget::signal_unsaved_edits,
                     this, &Project_Main_Window::slot_unsaved_edits);
    QObject::connect(m_project_widget.get(), &Project_Widget::signal_update_undo_actions,
                     this, &Project_Main_Window::slot_update_undo_actions);

    // Update the window title with the new file path and editing state
    m_window_title.set_variable_title(to_QString(m_project_widget->filepath()));
    slot_update_undo_actions(0,0);
}
void Saklib::Qtlib::Project_Main_Window::open_project(QString const& filePath)
{
    open_project(to_Path(filePath));
}

// Spawn a message box asking if the user wants to save the current project,
// act on it and return true if the action was never canceled.
bool Saklib::Qtlib::Project_Main_Window::ask_to_save()
{
    int msgBoxRet = QMessageBox::question(this,
                                          s_app_name.c_str(),
                                          tr("The project has been modified.\n"
                                             "Do you want to save your changes?"),
                                          QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                          QMessageBox::Save);

    switch (msgBoxRet)
    {
    case QMessageBox::Save:
        // Save was clicked
        return actionSlot_Save_Project(); // if the save is rejected then this returns false
    case QMessageBox::Discard:
        // Discard was clicked
        return true;
    case QMessageBox::Cancel:
        // Cancel was clicked
        return false;
    default:
        // should never be reached
        return false;
    }
}

// Report whether there are currently unsaved edits
bool Saklib::Qtlib::Project_Main_Window::has_unsaved_edits() const
{
    return m_window_title.has_unsaved_edits();
}
