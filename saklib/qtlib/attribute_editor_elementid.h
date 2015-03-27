#ifndef ATTRIBUTE_EDITOR_ELEMENTID_H
#define ATTRIBUTE_EDITOR_ELEMENTID_H

#include "attribute_editor.h"
#include "../types.h"

class QHBoxLayout;

namespace Saklib
{
    namespace Qtlib
    {
        class Attribute_Editor_ElementID :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_ElementID(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Bool() override;

        protected:
            void v_refresh_data() override;

        private slots:
            // Slot used to capture...what
            void slot_clicked();

        private:
            // Data Members
            //============================================================
            ElementID m_elementid;

            Uptr<QHBoxLayout> m_layout;
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // ATTRIBUTE_EDITOR_ELEMENTID_H
