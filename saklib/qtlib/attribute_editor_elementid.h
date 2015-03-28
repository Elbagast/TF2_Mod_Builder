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
            ~Attribute_Editor_ElementID() override;

            ElementID elementid() const { return m_elementid; }

        protected:
            void v_refresh_data() override;

        private slots:
            void slot_clicked();

        private:
            // Internal
            //============================================================
            QString button_text() const;
            QString name_label_text() const;
            QString type_label_text() const;

            // Data Members
            //============================================================
            ElementID m_elementid;

            Uptr<QPushButton> m_button;
            Uptr<QLabel> m_name_label;
            Uptr<QLabel> m_type_label; // type changer?

            Uptr<QHBoxLayout> m_layout;
        };

        /*
        Attribute_Editor_Vector_Component_ElementID
        ====================================================================================================
        A version of the above for an ElmentID inside a Vector.

        It's mostly just a straight copy right now since I can't figure out a sensible abstraction to reuse
        the shared code...

        This name is a bit ridiculous.

        class Attribute_Editor_Vector_Component_ElementID :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Vector_Component_ElementID(Project_Widget*const project_widget, AttributeID attributeid, size_type index, QWidget* parent = nullptr);
            ~Attribute_Editor_Vector_Component_ElementID() override;

            ElementID elementid() const { return m_elementid; }
            size_type index() const     { return m_index; }

        protected:
            void v_refresh_data() override;

        private slots:
            void slot_clicked();

        private:
            // Internal
            //============================================================
            QString button_text() const;
            QString name_label_text() const;
            QString type_label_text() const;

            // Data Members
            //============================================================
            ElementID m_elementid;
            size_type m_index;

            Uptr<QPushButton> m_button;
            Uptr<QLabel> m_name_label;
            Uptr<QLabel> m_type_label; // type changer?

            Uptr<QHBoxLayout> m_layout;
        };
*/
    } // namespace Qtlib
} // namespace Saklib

#endif // ATTRIBUTE_EDITOR_ELEMENTID_H
