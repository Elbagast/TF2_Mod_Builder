#ifndef ATTRIBUTE_EDITOR_H
#define ATTRIBUTE_EDITOR_H

#include "../types.h"
#include "../attributeid.h"
#include <QWidget>

namespace Saklib
{
    class Command_History;
    class Project_Manager;

    namespace Qtlib
    {
        class Attribute_Editor :
                public QWidget
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            explicit Attribute_Editor(QWidget* parent = nullptr):
                QWidget(parent)
            {}
            ~Attribute_Editor() override = default;

        public:
            void refresh_data() { v_refresh_data(); }

        protected:
            virtual void v_refresh_data() = 0;
        };

        class Attribute_Editor_Dummy :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            explicit Attribute_Editor_Dummy(QWidget* parent = nullptr):
                Attribute_Editor(parent)
            {}
            ~Attribute_Editor_Dummy() override = default;

        protected:
            void v_refresh_data() override {}
        };

        // Function with a typeswitch
        inline Uptr<Attribute_Editor> make_Attribute_Editor(Command_History& command_history, Project_Manager& project_manager, AttributeID attributeid)
        {
            return Uptr<Attribute_Editor>(new Attribute_Editor_Dummy());
        }

    } // namespace Qtlib
} // namespace Saklib
#endif // ATTRIBUTE_EDITOR_H
