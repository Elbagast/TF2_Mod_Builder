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
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Double(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            Attribute_Editor_Double(Project_Widget*const project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent = nullptr);
            ~Attribute_Editor_Double() override;

        protected:
            void v_refresh_data() override;

        private slots:
            // Slot used to capture the signal editingFinished() from the QDoubleSpinBox
            void slot_editingFinished();

        private:
            void shared_construction();

            // Data Members
            //============================================================
            Uptr<QDoubleSpinBox> m_spinbox;
            //Uptr<QLabel> m_label;
            Uptr<QHBoxLayout> m_layout;
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // ATTRIBUTE_EDITOR_DOUBLE_H
