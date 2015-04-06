#ifndef ATTRIBUTE_EDITOR_INT_H
#define ATTRIBUTE_EDITOR_INT_H

#include "attribute_editor.h"
#include "../types.h"

class QLabel;
class QSpinBox;
class QHBoxLayout;

namespace Saklib
{
    namespace Qtlib
    {
        class Attribute_Editor_Int :
                public Attribute_Editor
        {
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Int(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            Attribute_Editor_Int(Project_Widget*const project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent = nullptr);
            ~Attribute_Editor_Int() override;

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

    } // namespace Qtlib
} // namespace Saklib


#endif // ATTRIBUTE_EDITOR_INT_H
