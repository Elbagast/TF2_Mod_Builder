#ifndef ATTRIBUTE_EDITOR_INT_H
#define ATTRIBUTE_EDITOR_INT_H

#include "attribute_editor.h"
#include "../types.h"

class QLabel;
class QSpinBox;
class QHBoxLayout;
class QLineEdit;
class QIntValidator;

namespace saklib
{
    namespace Qtlib
    {
        class Attribute_Editor_Int_SB :
                public Attribute_Editor
        {
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Int_SB(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            Attribute_Editor_Int_SB(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent = nullptr);
            ~Attribute_Editor_Int_SB() override;

        protected:
            void v_refresh_data() override;
            void v_editing_finished() override;

        private:
            void shared_construction();

            // Data Members
            //============================================================
            QUptr<QSpinBox> m_spinbox;
            //QUptr<QLabel> m_label;
            QUptr<QHBoxLayout> m_layout;
        };

        class Attribute_Editor_Int_LE :
                public Attribute_Editor
        {
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Int_LE(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            Attribute_Editor_Int_LE(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent = nullptr);
            ~Attribute_Editor_Int_LE() override;

        protected:
            void v_refresh_data() override;
            void v_editing_finished() override;

        private:
            void shared_construction();

            // Data Members
            //============================================================
            QUptr<QHBoxLayout> m_layout;

            QUptr<QLineEdit> m_line_edit;
            QUptr<QIntValidator> m_validator;
        };

        using Attribute_Editor_Int = Attribute_Editor_Int_LE;

    } // namespace Qtlib
} // namespace saklib


#endif // ATTRIBUTE_EDITOR_INT_H
