#ifndef ATTRIBUTE_EDITOR_DOUBLE_H
#define ATTRIBUTE_EDITOR_DOUBLE_H

#include "attribute_editor.h"
#include "../types.h"

class QLabel;
class QDoubleSpinBox;
class QHBoxLayout;
class QLineEdit;
class QDoubleValidator;

namespace saklib
{
    namespace Qtlib
    {
        class Attribute_Editor_Double_SB :
                public Attribute_Editor
        {
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Double_SB(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            Attribute_Editor_Double_SB(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent = nullptr);
            ~Attribute_Editor_Double_SB() override;

        protected:
            void v_refresh_data() override;
            void v_editing_finished() override;

        private:
            void shared_construction();

            // Data Members
            //============================================================
            QUptr<QDoubleSpinBox> m_spinbox;
            QUptr<QHBoxLayout> m_layout;
        };

        class Attribute_Editor_Double_LE :
                public Attribute_Editor
        {
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Double_LE(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            Attribute_Editor_Double_LE(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent = nullptr);
            ~Attribute_Editor_Double_LE() override;

        protected:
            void v_refresh_data() override;
            void v_editing_finished() override;

        private:
            void shared_construction();

            // Data Members
            //============================================================
            QUptr<QHBoxLayout> m_layout;

            QUptr<QLineEdit> m_line_edit;
            QUptr<QDoubleValidator> m_validator;
        };

        using Attribute_Editor_Double = Attribute_Editor_Double_LE;

    } // namespace Qtlib
} // namespace saklib

#endif // ATTRIBUTE_EDITOR_DOUBLE_H
