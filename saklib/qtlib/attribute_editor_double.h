#ifndef ATTRIBUTE_EDITOR_DOUBLE_H
#define ATTRIBUTE_EDITOR_DOUBLE_H

#include "attribute_editor.h"
#include "../types.h"

class QLabel;
class QDoubleSpinBox;
class QHBoxLayout;

namespace Saklib
{
    namespace Qtlib
    {
        class Attribute_Editor_Double :
                public Attribute_Editor
        {
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Double(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            Attribute_Editor_Double(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent = nullptr);
            ~Attribute_Editor_Double() override;

        protected:
            void v_refresh_data() override;
            void v_editing_finished() override;

        private:
            void shared_construction();

            // Data Members
            //============================================================
            QUptr<QDoubleSpinBox> m_spinbox;
            //QUptr<QLabel> m_label;
            QUptr<QHBoxLayout> m_layout;
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // ATTRIBUTE_EDITOR_DOUBLE_H
