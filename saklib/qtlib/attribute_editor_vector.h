#ifndef ATTRIBUTE_EDITOR_VECTOR_H
#define ATTRIBUTE_EDITOR_VECTOR_H

#include "attribute_editor.h"
#include "../types.h"

class QVBoxLayout;
class QGridLayout;
class QPushButton;

namespace Saklib
{
    namespace Qtlib
    {
        class Attribute_Editor_Vector_Component;

        class Attribute_Editor_Vector :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Vector(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Vector() override;

            size_type attribute_vector_size() const;

        protected:
            void v_refresh_data() override;

            // make an appropriately typed component widget
            virtual Uptr<Attribute_Editor_Vector_Component> make_component_widget(size_type index) const = 0;

            // actions from the buttons/context menu...use the virtual functions to implement them?
        private slots:
            void slot_append();

        private:
            // Data Members
            //============================================================
            Uptr<QPushButton> m_append_button; // button that append the end that
            Uptr<QVBoxLayout> m_layout; // the layout that must be refilled from scratch if things are added...

            Vector<Uptr<Attribute_Editor_Vector_Component>> m_vector_widgets;
        };

        class Attribute_Editor_Vector_Component:
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Vector_Component(Project_Widget*const project_widget, AttributeID attributeid, size_type index, QWidget* parent = nullptr):
                Attribute_Editor(project_widget, attributeid, parent),
                m_index(index)
            {
            }
            ~Attribute_Editor_Vector_Component() override = default;

            size_type index() const { return m_index; }

        private:
            // Data Members
            //============================================================
            size_type m_index;
        };

    } // namespace Qtlib
} // namespace Saklib


#endif // ATTRIBUTE_EDITOR_VECTOR_H
