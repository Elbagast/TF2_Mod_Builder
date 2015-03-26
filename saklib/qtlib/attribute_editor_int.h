#ifndef ATTRIBUTE_EDITOR_INT_H
#define ATTRIBUTE_EDITOR_INT_H

#include "attribute_editor.h"
#include "../types.h"

class QLabel;
class QSpinBox;
class QHBoxLayout;

namespace Saklib
{
    class Project_Manager;

    namespace Qtlib
    {
        class Attribute_Editor_Int :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Int(Project_Manager& project_manager, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Int() override;

        protected:
            void v_refresh_data() override;

        private slots:
            // Slot used to capture the signal editingFinished() from the QSpinBox
            void slot_editingFinished();

        private:
            // Data Members
            //============================================================
            Uptr<QSpinBox> m_spinbox;
            Uptr<QLabel> m_label;
            Uptr<QHBoxLayout> m_layout;
        };

    } // namespace Qtlib
} // namespace Saklib


#endif // ATTRIBUTE_EDITOR_INT_H
