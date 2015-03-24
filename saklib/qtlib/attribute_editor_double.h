#ifndef ATTRIBUTE_EDITOR_DOUBLE_H
#define ATTRIBUTE_EDITOR_DOUBLE_H

#include "attribute_editor.h"
#include "../types.h"

class QLabel;
class QDoubleSpinBox;
class QHBoxLayout;

namespace Saklib
{
    class Project_Manager;

    namespace Qtlib
    {
        class Attribute_Editor_Double :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Double(Project_Manager& project_manager, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Double() override;

        protected:
            void v_refresh_data() override;

        private slots:
            // Slot used to capture the signal value_changed() from the QSpinBox
            void slot_valueChanged(double value);

        private:
            // Data Members
            //============================================================
            Uptr<QDoubleSpinBox> m_spinbox;
            Uptr<QLabel> m_label;
            Uptr<QHBoxLayout> m_layout;
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // ATTRIBUTE_EDITOR_DOUBLE_H
