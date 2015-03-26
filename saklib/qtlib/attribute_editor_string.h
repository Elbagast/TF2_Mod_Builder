#ifndef ATTRIBUTE_EDITOR_STRING_H
#define ATTRIBUTE_EDITOR_STRING_H

#include "attribute_editor.h"
#include "../types.h"

class QLineEdit;
class QHBoxLayout;

namespace Saklib
{
    class Project_Manager;

    namespace Qtlib
    {
        class Attribute_Editor_String :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_String(Project_Manager& project_manager, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_String() override;

        protected:
            void v_refresh_data() override;

        private slots:
            // Slot used to capture the signal editingFinished() from the QLineEdit
            void slot_editingFinished();

        private:
            // Data Members
            //============================================================
            Uptr<QLineEdit> m_line_edit;
            Uptr<QHBoxLayout> m_layout;
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // ATTRIBUTE_EDITOR_STRING_H
