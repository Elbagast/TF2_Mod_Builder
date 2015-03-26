#ifndef ATTRIBUTE_EDITOR_H
#define ATTRIBUTE_EDITOR_H

#include "../attributeid.h"
#include <QWidget>

class QLabel;
class QHBoxLayout;

namespace Saklib
{
    namespace Qtlib
    {
        class Project_Widget;

        class Attribute_Editor :
                public QWidget
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor() override;

            void refresh_data()                         { v_refresh_data(); }
            AttributeID attributeid() const             { return m_attributeid; }
            Project_Widget*const project_widget() const { return mp_project_widget; }

        protected:
            virtual void v_refresh_data() = 0;
        private:
            Project_Widget*const mp_project_widget;
            AttributeID m_attributeid;
        };

        class Attribute_Editor_Dummy :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Dummy(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Dummy() override;
        protected:
            void v_refresh_data() override {}
        private:
            Uptr<QLabel> m_label;
            Uptr<QHBoxLayout> m_layout;
        };

        // Function with a typeswitch
        Uptr<Attribute_Editor> make_Attribute_Editor(Project_Widget*const project_widget, AttributeID attributeid);

    } // namespace Qtlib
} // namespace Saklib
#endif // ATTRIBUTE_EDITOR_H
