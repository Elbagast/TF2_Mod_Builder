#ifndef ATTRIBUTE_EDITOR_BOOL_H
#define ATTRIBUTE_EDITOR_BOOL_H

#include "attribute_editor.h"
#include "../types.h"

class QCheckBox;
class QHBoxLayout;

namespace Saklib
{
    namespace Qtlib
    {
        class Attribute_Editor_Bool :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Bool(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            Attribute_Editor_Bool(Project_Widget*const project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent = nullptr);
            ~Attribute_Editor_Bool() override;

        protected:
            void v_refresh_data() override;

        private slots:
            // Slot used to capture the signal clicked() from the QCheckBox
            void slot_clicked();

        private:
            void shared_construction();

            // Data Members
            //============================================================
            Uptr<QCheckBox> m_checkbox;
            Uptr<QHBoxLayout> m_layout;
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // ATTRIBUTE_EDITOR_BOOL_H
