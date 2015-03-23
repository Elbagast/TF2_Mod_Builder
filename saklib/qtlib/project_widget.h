#ifndef PROJECT_WIDGET_H
#define PROJECT_WIDGET_H

#include "../types.h"
#include "../elementid.h"
#include "../element_manager.h"
#include "../command_history.h"
#include "element_widget.h"
#include "project_manager.h"

//#include "outliner/outliner_manager.h"

class QHBoxLayout;
class QTabWidget;
class QScrollArea;

namespace Saklib
{
    namespace Qtlib
    {
        class Project_Main_Window;
        class Outliner_Model;
        class Outliner_Delegate;
        class Outliner_Treeview;

        /*
        Project_Widget
        ====================================================================================================
        This widget is the root widget of an entire project and forms the central widget of the window
        class that holds it.
        - an Element_Manager
        - a root ElementID
        - means to generate new Elements in the manager
        - An outliner to view the overall structure
        - An Editor of some kind for given Elements
            - e.g. singular or tab widget (start singular)
        */
        class Project_Widget:
                public QWidget
        {
            Q_OBJECT
        public:


            // Special 6
            //============================================================
            explicit Project_Widget(Path const& filePath, Project_Main_Window* parent = nullptr);
            ~Project_Widget() override;

            // Interface
            //============================================================
            Path const& filepath() const;
            void set_filepath(Path const& filePath);

            void save() const;
            void save_as(Path const& filePath);

            //void reload();

            // Open an Element_Widget for this Element
            void open_editor(ElementID const& elementid);

        signals:
            void signal_unsavedEdits(bool state) const;

        public slots:
            //void slot_editorRequestedFor(ElementID elementid);
            //void slot_unsavedEdits(bool state) const;

        private:
            // Data Members
            //============================================================

            //data
            Project_Main_Window* mp_main_window;
            Command_History m_command_history;
            Project_Manager m_project_manager;
            ElementID m_root_elementid;
            AttributeID m_root_filepath; // ref to filepath storage

            // Outliner model
            Uptr<Outliner_Delegate> m_outliner_delegate;

            // Widgets
            Uptr<Outliner_Treeview> m_outliner; // Element outliner (No direct attribute access)
            Uptr<QScrollArea> m_scroll_area; // area that will contain m_editor
            //Uptr<Element_Widget> m_editor;  // widget to the currently open Element

            Uptr<QHBoxLayout> m_layout;

            // Static Helpers
            //============================================================
            // Make an ElementID with the supplied manager by registering the Element type the first time
            // this is run
            static ElementID make_Project(Command_History& command_history, Project_Manager& project_manager);
        };

    } // namespace Qtlib
}  // namespace Saklib

#endif // PROJECT_WIDGET_H
