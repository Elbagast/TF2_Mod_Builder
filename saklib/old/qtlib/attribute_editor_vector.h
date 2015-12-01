#ifndef ATTRIBUTE_EDITOR_VECTOR_H
#define ATTRIBUTE_EDITOR_VECTOR_H

#include "attribute_editor.h"
#include "../types.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QPushButton;

namespace saklib
{
    namespace Qtlib
    {
        class Element_Widget;

        class Attribute_Editor_Vector_Component;

        /*
        Attribute_Editor_Vector
        ====================================================================================================
        Generic editor class for Attributes that are vectors. The Editors for each item in the vector are
        type specific.
        */

        class Attribute_Editor_Vector :
                public Attribute_Editor
        {
            friend class Attribute_Editor_Vector_Component;
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Vector(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Vector() override;

            size_type attribute_vector_size() const;

        protected:
            void v_refresh_data() override;

            // actions from the buttons/context menu...use the virtual functions to implement them?
        protected slots:
            void slot_custom_context_menu(QPoint const& pos);

            virtual void slot_append() = 0;
            virtual void slot_insert_at(size_type index) = 0;
            virtual void slot_remove_at(size_type index) = 0;
            virtual void slot_remove_last() = 0;
            virtual void slot_swap(size_type index, size_type other_index) = 0;
            virtual void slot_move_up(size_type index) = 0;
            virtual void slot_move_down(size_type index) = 0;
            virtual void slot_clear() = 0;

        private:
            // Data Members
            //============================================================
            QUptr<QVBoxLayout> m_layout;
            QUptr<QVBoxLayout> m_component_layout;

            QUptr<QHBoxLayout> m_button_layout;
            QUptr<QPushButton> m_append_button; // button that append the end that
            QUptr<QPushButton> m_clear_button; // button that append the end that

            std::vector<QUptr<Attribute_Editor_Vector_Component>> m_vector_widgets;
        };


        /*
        Attribute_Editor_Vector_Component
        ====================================================================================================
        Contains a type-specific Attribute_Editor wrapped in buttons which provide vector editing facilities
        relevent to the given index
        */
        class Attribute_Editor_Vector_Component :
                public QWidget
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Vector_Component(Project_Widget* project_widget, AttributeID attributeid, size_type index, Attribute_Editor_Vector* parent);
            ~Attribute_Editor_Vector_Component() override;

            void refresh_data()                 { m_editor->refresh_data(); }
            size_type vector_index() const      { return m_editor->vector_index(); }
            Attribute_Editor* editor() const    { return m_editor.get(); }

            // Button slots
        protected slots:
            void slot_insert_before();
            void slot_remove();
            void slot_move_up();
            void slot_move_down();

        private:
            Attribute_Editor_Vector* mp_parent;

            QUptr<QHBoxLayout> m_layout;
            QUptr<QVBoxLayout> m_move_button_layout;
            QUptr<QPushButton> m_move_up_button;
            QUptr<QPushButton> m_move_down_button;
            QUptr<QVBoxLayout> m_other_button_layout;
            QUptr<QPushButton> m_insert_button;
            QUptr<QPushButton> m_remove_button;

            QUptr<Attribute_Editor> m_editor;
        };

    } // namespace Qtlib
} // namespace saklib


#endif // ATTRIBUTE_EDITOR_VECTOR_H
