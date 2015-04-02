#ifndef PROJECT_WIDGET_H
#define PROJECT_WIDGET_H

#include "../types.h"
#include "../project_observer.h"
#include "quptr.h"
#include <QWidget>

class QHBoxLayout;
class QTabWidget;
class QScrollArea;

namespace Saklib
{
    class Project_Manager;

    namespace Qtlib
    {
        class Element_Widget;
        class Outliner_Model;
        class Outliner_Delegate;
        class Outliner_Treeview;

        /*
        Project_Widget
        ====================================================================================================
        This widget is the root widget of an entire project and forms the central widget of the window
        class that holds it. When something happens that needs to update the window (e.g. enable/disable
        menu actions) it emits signals that will already have been connected as appropriate.
        */
        class Project_Widget:
                public QWidget,
                public Project_Observer
        {
            Q_OBJECT
        public:
            explicit Project_Widget(Project_Manager& project_manager, QWidget* parent = nullptr);
            ~Project_Widget() override;

            // Use this function to access the Project_Manager
            using Project_Observer::project_manager;

            //Project_Manager& project_manager() { return Project_Observer::project_manager(); }


            // Element Widget
            //------------------------------------------------------------
            // Alter the Element currently being edited
            // Make an Element_Widget for this ElementID
            void open_editor(ElementID elementid);
            // The ElementID of the Element that is currently being edited
            ElementID currently_open_elementid() const;
            // Overall Project
            //------------------------------------------------------------
            ElementID project_elementid() const;
            Path const& project_filepath() const;
            void set_project_filepath(Path const& filepath);
            void save() const;
            void save_as(Path const& filepath);

        protected:
            // Project_Observer Virtuals
            //============================================================
            void begin_model_reset() override;
            void end_model_reset() override;

            void data_changed(ElementID elementid) override;
            void data_changed(AttributeID attributeid) override;

            void element_name_changed(ElementID elementid) override;
            void element_parent_changed(ElementID elementid) override;
            void element_destroyed(ElementID elementid) override;

            void attribute_value_changed(AttributeID attributeid) override;

            void unsaved_edits_changed(bool state) override;
            void undo_counts_changed(size_type undo_count, size_type redo_count) override;

        signals:
            // Signals
            //============================================================
            // Emitted whenever data is changed and the changes were not saved
            void signal_unsaved_edits(bool state) const;
            // Emitted whenever a Command_History function is called so that the window can update actions
            void signal_update_undo_actions(size_type undo_count, size_type redo_count) const;


        private:
            // Data Members
            //============================================================
            // Outliner model
            QUptr<Outliner_Model> m_outliner_model;
            QUptr<Outliner_Delegate> m_outliner_delegate;

            // Widgets
            QUptr<Outliner_Treeview> m_outliner; // Element outliner (No direct attribute access)
            QUptr<QScrollArea> m_scroll_area; // area that will contain m_editor
            QUptr<Element_Widget> m_editor; // editor for a given ElementID

            QUptr<QHBoxLayout> m_layout;
        };

    } // namespace Qtlib
}  // namespace Saklib

#endif // PROJECT_WIDGET_H
