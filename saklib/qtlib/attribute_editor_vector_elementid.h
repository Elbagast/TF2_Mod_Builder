#ifndef ATTRIBUTE_EDITOR_VECTOR_ELEMENTID_H
#define ATTRIBUTE_EDITOR_VECTOR_ELEMENTID_H

#include "attribute_editor_vector.h"
#include "../types.h"

class QVBoxLayout;
class QPushButton;

namespace Saklib
{
    namespace Qtlib
    {
       // using Attribute_Editor_Vector_ElementID = Attribute_Editor_Vector_Type<ElementID>;

        class Attribute_Editor_Vector_Component_ElementID;

        class Attribute_Editor_Vector_ElementID:
                public Attribute_Editor_Vector
        {
        public:
            using value_type = ElementID;
            using stored_type = Vector<value_type>;

            // Special 6
            //============================================================
            Attribute_Editor_Vector_ElementID(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Vector_ElementID() override;

        protected:
            // make an appropriately typed component widget
            Uptr<Attribute_Editor_Vector_Component> make_component_widget(size_type index) const override;
        };



        class Attribute_Editor_Vector_Component_ElementID:
                public Attribute_Editor_Vector_Component
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Vector_Component_ElementID(Project_Widget*const project_widget, AttributeID attributeid, size_type index, QWidget* parent = nullptr);
            ~Attribute_Editor_Vector_Component_ElementID() override;

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
        class Attribute_Editor_Vector_ElementID :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Vector_ElementID(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Vector_ElementID() override;

        protected:
            void v_refresh_data() override;

        private slots:
            void slot_append();

        private:
            // Data Members
            //============================================================
            Uptr<QPushButton> m_append_button; // button that append the end that
            Uptr<QVBoxLayout> m_layout; // the layout that must be refilled from scratch if things are added...

            Vector<Uptr<Attribute_Editor_Vector_Component_ElementID>> m_vector_widgets;
        };
        */
    } // namespace Qtlib
} // namespace Saklib

#endif // ATTRIBUTE_EDITOR_VECTOR_ELEMENTID_H
