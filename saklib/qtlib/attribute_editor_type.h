#ifndef ATTRIBUTE_EDITOR_TYPE_H
#define ATTRIBUTE_EDITOR_TYPE_H

#include "attribute_editor.h"

class QLabel;
class QHBoxLayout;

namespace Saklib
{
    class Project_Manager;

    namespace Qtlib
    {
        class Project_Widget;

        /*
        Attribute_Editor_Type<T>
        ====================================================================================================
        Derived class template that adds functionality to Attribute_Editor
        */
        template <typename T>
        class Attribute_Editor_Type :
                public Attribute_Editor
        {
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Type(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            Attribute_Editor_Type(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent = nullptr);
            ~Attribute_Editor_Type() override;

        protected:
            // Require subclasses to match with the data they represent
            void v_refresh_data() override;
            void v_editing_finished() override;

        private:

        };

        class Attribute_Editor_Dummy :
                public Attribute_Editor
        {
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Dummy(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Dummy() override;
        protected:
            void v_refresh_data() override {}
            void v_editing_finished() override {}
        private:
            QUptr<QLabel> m_label;
            QUptr<QHBoxLayout> m_layout;
        };

        // Function with a typeswitch
        QUptr<Attribute_Editor> make_Attribute_Editor(Project_Widget* project_widget, AttributeID attributeid);

        // Function with a typeswitch
        QUptr<Attribute_Editor> make_Attribute_Editor(Project_Widget* project_widget, AttributeID attributeid, size_type vector_index);

    } // namespace Qtlib
} // namespace Saklib

#endif // ATTRIBUTE_EDITOR_TYPE_H

