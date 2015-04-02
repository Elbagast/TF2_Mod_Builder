#ifndef ATTRIBUTE_EDITOR_ELEMENTID_H
#define ATTRIBUTE_EDITOR_ELEMENTID_H

#include "attribute_editor.h"
#include "../types.h"

class QLabel;
class QPushButton;
class QHBoxLayout;

namespace Saklib
{
    namespace Qtlib
    {
        /*
        Attribute_Editor_ElementID
        ====================================================================================================
        A button that adds an Element if the ElementID is invalid, or opens the editor for it if it's set.
        */
        class Attribute_Editor_ElementID :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_ElementID(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            Attribute_Editor_ElementID(Project_Widget*const project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent = nullptr);
            ~Attribute_Editor_ElementID() override;

            ElementID elementid() const { return m_elementid; }

        protected:
            void v_refresh_data() override;

        private slots:
            void slot_clicked();

        private:
            void shared_construction();

            // Internal
            //============================================================
            QString button_text() const;
            QString name_label_text() const;
            QString type_label_text() const;

            // Data Members
            //============================================================
            ElementID m_elementid;

            QUptr<QPushButton> m_button;
            QUptr<QLabel> m_name_label;
            QUptr<QLabel> m_type_label; // type changer?

            QUptr<QHBoxLayout> m_layout;
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // ATTRIBUTE_EDITOR_ELEMENTID_H
