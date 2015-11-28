#ifndef ATTRIBUTE_EDITOR_STRING_H
#define ATTRIBUTE_EDITOR_STRING_H

#include "attribute_editor.h"
#include "../types.h"

class QLineEdit;
class QHBoxLayout;

namespace saklib
{
    namespace Qtlib
    {
        class Attribute_Editor_String :
                public Attribute_Editor
        {
        public:
            // Special 6
            //============================================================
            Attribute_Editor_String(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            Attribute_Editor_String(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent = nullptr);
            ~Attribute_Editor_String() override;

        protected:
            void v_refresh_data() override;
            void v_editing_finished() override;

        private:
            void shared_construction();

            // Data Members
            //============================================================
            QUptr<QLineEdit> m_line_edit;
            QUptr<QHBoxLayout> m_layout;
        };

    } // namespace Qtlib
} // namespace saklib

#endif // ATTRIBUTE_EDITOR_STRING_H
