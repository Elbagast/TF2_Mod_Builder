#ifndef PROJECT_MAIN_WINDOW_H
#define PROJECT_MAIN_WINDOW_H
/*
Project_Main_Window
============================================================
QMainWindow subclass which forms the basis of the application. It manages a project (one
for now) although it may be started without a project.

*/
#include "../types.h"

#include <QMainWindow>
#include "windowtitle.h"

namespace Ui
{
    class Project_Main_Window;
}

namespace Saklib
{
    class ElementID;

    namespace Qtlib
    {
        class Project_Widget;

        class Project_Main_Window :
                public QMainWindow
        {
            Q_OBJECT

        public:
            // Special 6
            //============================================================
            explicit Project_Main_Window(QWidget *parent = nullptr);
            // Called if the program is opened with a file
            explicit Project_Main_Window(Path const& projectFilePath, QWidget *parent = nullptr);

            ~Project_Main_Window() override;

        private slots:
            // Menu Action Slots
            //============================================================
            // Connection syntax:
            // QObject::connect(m_ui->action[NAME], &QAction::triggered, this, &ProjectMainWindow::actionSlot_[NAME] );
            // return true if the action is carried out to completion

            // File
            //====================
            bool actionSlot_New_Project();
            bool actionSlot_Open_Project();
            //--------------------
            bool actionSlot_Save_Project();
            bool actionSlot_Save_Project_As();
            //--------------------
            bool actionSlot_Exit();


            // Other Slots
            //============================================================
            // If something edits data, call this.
            void slot_unsavedEdits(bool);

        protected:
            // Virtuals
            //============================================================
            // Needed so that the console window can be cleaned up properly.
             void closeEvent(QCloseEvent *event) override;

        private:
            // Convenience
            //============================================================
            // Makes a new, empty project with a placeholder name
            void new_project();
            // Opens an existing project and loads the data found in the file.
            void open_project(Path const& filePath);
            void open_project(QString const& filePath);

            // Spawn a message box asking if the user wants to save the current project,
            // act on it and return true if the action was never canceled.
            bool ask_to_save();

            // Report whether there are currently unsaved edits
            bool has_unsaved_edits() const;

            // Data Members
            //============================================================

            // Form built UI
            Uptr<Ui::Project_Main_Window> m_ui;
            Uptr<Project_Widget> m_project_widget;
            WindowTitle m_window_title;

            // Static Data Members
            //============================================================
            static String const s_app_name;
            static String const s_new_name_front;
            static size_type s_new_count;
        };

    } // namespace Qtlib
}  // namespace Saklib

#endif // PROJECT_MAIN_WINDOW_H
