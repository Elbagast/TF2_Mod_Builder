#ifndef ATTRIBUTE_EDITOR_H
#define ATTRIBUTE_EDITOR_H

#include "../attributeid.h"
#include <QWidget>

class QLabel;

namespace Saklib
{
    namespace Qtlib
    {
        class Project_Manager;

        class Attribute_Editor :
                public QWidget
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor(Project_Manager& project_manager, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor() override;

            void refresh_data()                 { v_refresh_data(); }
            AttributeID attributeid() const     { return m_attributeid; }

        protected:
            virtual void v_refresh_data() = 0;

            Project_Manager& mr_project_manager;
            AttributeID m_attributeid;
        };

        class Attribute_Editor_Dummy :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Dummy(Project_Manager& project_manager, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Dummy() override;
        protected:
            void v_refresh_data() override {}
        private:
            Uptr<QLabel> m_label;
        };

        // Function with a typeswitch
        Uptr<Attribute_Editor> make_Attribute_Editor(Project_Manager& project_manager, AttributeID attributeid);

    } // namespace Qtlib
} // namespace Saklib
#endif // ATTRIBUTE_EDITOR_H
