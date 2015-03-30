#ifndef PROJECT_WIDGET_COMMANDS
#define PROJECT_WIDGET_COMMANDS

#include "project_widget_declaration.h"
#include "../command.h"

namespace Saklib
{
    namespace Qtlib
    {
        /*
        Project_Widget_Command_Element
        ====================================================================================================
        Shared garbage collection modiifications go here
        */
        class Project_Widget_Command_Element:
                public Command
        {
        public:
            Project_Widget_Command_Element(Project_Widget*const project_widget, ElementID elementid):
                Command(),
                mp_project_widget(project_widget),
                m_elementid(elementid)
            {
                assert(mp_project_widget);
                assert(mp_project_widget->is_valid(m_elementid));

                // ref count change for ElementID
            }
            ~Project_Widget_Command_Element() override
            {
                // ref count change for ElementID
            }

            Project_Widget*const project_widget() const { return mp_project_widget; }
            ElementID elementid() const                 { return m_elementid; }

        protected:
            void v_execute() override = 0;
            void v_unexecute() override = 0;
        private:
            Project_Widget*const mp_project_widget;
            ElementID m_elementid;
        };

        /*
        Project_Widget_Command_Attribute
        ====================================================================================================
        Shared garbage collection modiifications go here
        */
        class Project_Widget_Command_Attribute:
                public Command
        {
        public:
            Project_Widget_Command_Attribute(Project_Widget*const project_widget, AttributeID attributeid):
                Command(),
                mp_project_widget(project_widget),
                m_attributeid(attributeid)
            {
                assert(mp_project_widget);
                assert(mp_project_widget->is_valid(m_attributeid));

                // ref count change for AttributeID
            }
            ~Project_Widget_Command_Attribute() override
            {
                // ref count change for AttributeID
            }

            Project_Widget*const project_widget() const { return mp_project_widget; }
            ElementID elementid() const                 { return m_attributeid.elementid(); }
            AttributeID attributeid() const             { return m_attributeid; }

        protected:
            void v_execute() override = 0;
            void v_unexecute() override = 0;
        private:
            Project_Widget*const mp_project_widget;
            AttributeID m_attributeid;
        };



        /*
        PWC_Element_Set_Name
        ====================================================================================================
        */
        class PWC_Element_Set_Name:
                public Project_Widget_Command_Element
        {
        public:
            PWC_Element_Set_Name(Project_Widget*const project_widget, ElementID elementid, String const& name):
                Project_Widget_Command_Element(project_widget, elementid),
                m_old_name(project_widget->element_name(elementid)),
                m_new_name(name)
            {}
            ~PWC_Element_Set_Name() override = default;

        protected:
            void v_execute() override
            {
                project_widget()->element_set_name(elementid(), m_new_name);
            }
            void v_unexecute() override
            {
                project_widget()->element_set_name(elementid(), m_old_name);
            }
        private:
            String m_old_name;
            String m_new_name;
        };

        /*
        PWC_Attribute_Set_Value<T>
        ====================================================================================================
        */
        template <typename T>
        class PWC_Attribute_Set_Value:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Set_Value(Project_Widget*const project_widget, AttributeID attributeid, T const& value):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_old_value(project_widget->attribute_type_cast<T>(attributeid)->value()),
                m_new_value(value)
            {}
            ~PWC_Attribute_Set_Value() override = default;

        protected:
            void v_execute() override
            {
                project_widget()->attribute_set_value(attributeid(), m_new_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_set_value(attributeid(), m_old_value);
            }
        private:
            T m_old_value;
            T m_new_value;
        };



        /*
        PWC_Attribute_Vector_Push_Back<T>
        ====================================================================================================
        */
        template <typename T>
        class PWC_Attribute_Vector_Push_Back:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Push_Back(Project_Widget*const project_widget, AttributeID attributeid, T const& value):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_new_value(value)
            {}
            ~PWC_Attribute_Vector_Push_Back() override = default;

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_push_back(attributeid(), m_new_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_pop_back(attributeid());
            }
        private:
            T m_new_value;
        };


        /*
        PWC_Attribute_Vector_Set_Value_At<T>
        ====================================================================================================
        */
        template <typename T>
        class PWC_Attribute_Vector_Set_Value_At:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Set_Value_At(Project_Widget*const project_widget, AttributeID attributeid, size_type index, T const& value):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_index(index),
                m_new_value(value),
                m_old_value(project_widget->attribute_type_cast<Vector<T>>(attributeid)->at(index))
            {}
            ~PWC_Attribute_Vector_Set_Value_At() override = default;

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_set_at(attributeid(), m_index, m_new_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_set_at(attributeid(), m_index, m_old_value);
            }
        private:
            size_type m_index;
            T m_new_value;
            T m_old_value;
        };

    } // namespace Qtlib
}  // namespace Saklib


#endif // PROJECT_WIDGET_COMMANDS

