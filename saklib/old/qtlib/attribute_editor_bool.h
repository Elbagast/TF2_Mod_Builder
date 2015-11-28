#ifndef ATTRIBUTE_EDITOR_BOOL_H
#define ATTRIBUTE_EDITOR_BOOL_H

#include "attribute_editor.h"
#include "../types.h"

class QCheckBox;
class QHBoxLayout;

namespace saklib
{
    namespace Qtlib
    {
        class Attribute_Editor_Bool :
                public Attribute_Editor
        {
            //Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Bool(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            Attribute_Editor_Bool(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent = nullptr);
            ~Attribute_Editor_Bool() override;

        protected:
            void v_refresh_data() override;
            void v_editing_finished() override;

        private:
            void shared_construction();

            // Data Members
            //============================================================
            QUptr<QCheckBox> m_checkbox;
            QUptr<QHBoxLayout> m_layout;
        };

    } // namespace Qtlib
} // namespace saklib

#endif // ATTRIBUTE_EDITOR_BOOL_H