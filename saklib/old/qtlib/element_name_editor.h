#ifndef ELEMENT_NAME_EDITOR_H
#define ELEMENT_NAME_EDITOR_H

#include "../types.h"
#include "../elementid.h"
#include "quptr.h"
#include <QWidget>
class QLabel;
class QLineEdit;
class QStackedLayout;

namespace saklib
{
    namespace Qtlib
    {
        class Project_Widget;

        class Element_Name_Editor :
                public QWidget
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Element_Name_Editor(Project_Widget* project_widget, ElementID elementid, QWidget* parent = nullptr);
            ~Element_Name_Editor() override;

            void refresh_data();

        protected slots:
            // Slots
            //============================================================
            // Connected to this->customContextMenuRequested
            void slot_customContextMenuRequested(QPoint const& pos);

            void slot_start_editing();
            void slot_end_editing();

        protected:
            // Virtual Overrides
            //============================================================
            // To switching to the QLineEdit on double-click
            void mouseDoubleClickEvent(QMouseEvent* mouse_event) override;
            // To switch to the QLabel when focus on this is lost
            void focusOutEvent(QFocusEvent* event) override;

        private:
            //void shared_construction();

            // Data Members
            //============================================================
            Project_Widget* mp_project_widget;
            ElementID m_elementid;
            QUptr<QLabel> m_label;
            QUptr<QLineEdit> m_line_edit;
            QUptr<QStackedLayout> m_layout;
        };

    } // namespace Qtlib
} // namespace saklib

#endif // ELEMENT_NAME_EDITOR_H
