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
        class Element_Widget;

        /*
        Attribute_Editor_Vector
        ====================================================================================================
        Generic editor class for Attributes that are vectors. The Editors for each item in the vector are
        type specific.
        */

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

            // actions from the buttons/context menu...use the virtual functions to implement them?
        protected slots:
            void slot_custom_context_menu(QPoint const& pos);

            // only type dependent calls are virtual...or they could just use type switches..
            virtual void slot_append() = 0;
            virtual void slot_insert(size_type index) = 0;
            void slot_remove(size_type index);
            void slot_remove_last();
            void slot_swap(size_type index, size_type other_index);
            void slot_move_up(size_type index);
            void slot_move_down(size_type index);
            void slot_clear();

        private:
            // Data Members
            //============================================================
            Uptr<QPushButton> m_append_button; // button that append the end that
            Uptr<QVBoxLayout> m_layout;

            Uptr<QVBoxLayout> m_component_layout;

            Vector<Uptr<Attribute_Editor>> m_vector_widgets;
        };

    } // namespace Qtlib
} // namespace Saklib


#endif // ATTRIBUTE_EDITOR_VECTOR_H
