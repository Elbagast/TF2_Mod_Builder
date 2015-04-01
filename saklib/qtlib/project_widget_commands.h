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
        Shared garbage collection modifications go here
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

                mp_project_widget->increment_command_ref_count(m_elementid);
            }
            ~Project_Widget_Command_Element() override
            {
                mp_project_widget->decrement_command_ref_count(m_elementid);
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
        Shared garbage collection modifications go here
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

                mp_project_widget->increment_command_ref_count(m_attributeid);
            }
            ~Project_Widget_Command_Attribute() override
            {
                mp_project_widget->decrement_command_ref_count(m_attributeid);
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
                project_widget()->attribute_set_value<T>(attributeid(), m_new_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_set_value<T>(attributeid(), m_old_value);
            }
        private:
            T m_old_value;
            T m_new_value;
        };

        template <>
        class PWC_Attribute_Set_Value<ElementID>:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Set_Value(Project_Widget*const project_widget, AttributeID attributeid, ElementID const& value):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_old_value(project_widget->attribute_type_cast<ElementID>(attributeid)->value()),
                m_new_value(value)
            {
                this->project_widget()->increment_command_ref_count(m_old_value);
                this->project_widget()->increment_command_ref_count(m_new_value);
            }
            ~PWC_Attribute_Set_Value() override
            {
                this->project_widget()->decrement_command_ref_count(m_old_value);
                this->project_widget()->decrement_command_ref_count(m_new_value);
            }

        protected:
            void v_execute() override
            {
                project_widget()->attribute_set_value<ElementID>(attributeid(), m_new_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_set_value<ElementID>(attributeid(), m_old_value);
            }
        private:
            ElementID m_old_value;
            ElementID m_new_value;
        };



        /*
        PWC_Attribute_Vector_Clear<T>
        ====================================================================================================
        */
        template <typename T>
        class PWC_Attribute_Vector_Clear:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Clear(Project_Widget*const project_widget, AttributeID attributeid):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_old_vector(project_widget->attribute_type_cast<Vector<T>>(attributeid)->vector())
            {}
            ~PWC_Attribute_Vector_Clear() override = default;

        protected:
            void v_execute() override
            {
                //project_widget()->attribute_vector_clear<T>(attributeid());
            }
            void v_unexecute() override
            {
                //project_widget()->attribute_vector_set_vector<T>(attributeid(), m_old_vector);
            }
        private:
            Vector<T> m_old_vector;
        };

        /*
        PWC_Attribute_Vector_Set_At<T>
        ====================================================================================================
        */
        template <typename T>
        class PWC_Attribute_Vector_Set_At:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Set_At(Project_Widget*const project_widget, AttributeID attributeid, size_type index, T const& value):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_index(index),
                m_new_value(value),
                m_old_value(project_widget->attribute_type_cast<Vector<T>>(attributeid)->at(index))
            {}
            ~PWC_Attribute_Vector_Set_At() override = default;

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_set_at<T>(attributeid(), m_index, m_new_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_set_at<T>(attributeid(), m_index, m_old_value);
            }
        private:
            size_type m_index;
            T m_new_value;
            T m_old_value;
        };

        template <>
        class PWC_Attribute_Vector_Set_At<ElementID>:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Set_At(Project_Widget*const project_widget, AttributeID attributeid, size_type index, ElementID const& value):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_index(index),
                m_new_value(value),
                m_old_value(project_widget->attribute_type_cast<Vector<ElementID>>(attributeid)->at(index))
            {
                this->project_widget()->increment_command_ref_count(m_old_value);
                this->project_widget()->increment_command_ref_count(m_new_value);
            }
            ~PWC_Attribute_Vector_Set_At() override
            {
                this->project_widget()->decrement_command_ref_count(m_old_value);
                this->project_widget()->decrement_command_ref_count(m_new_value);
            }

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_set_at<ElementID>(attributeid(), m_index, m_new_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_set_at<ElementID>(attributeid(), m_index, m_old_value);
            }
        private:
            size_type m_index;
            ElementID m_new_value;
            ElementID m_old_value;
        };

        /*
        PWC_Attribute_Vector_Set_Front<T>
        ====================================================================================================
        */
        template <typename T>
        class PWC_Attribute_Vector_Set_Front:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Set_Front(Project_Widget*const project_widget, AttributeID attributeid, T const& value):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_new_value(value),
                m_old_value(project_widget->attribute_type_cast<Vector<T>>(attributeid)->front())
            {}
            ~PWC_Attribute_Vector_Set_Front() override = default;

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_set_front<T>(attributeid(), m_new_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_set_front<T>(attributeid(), m_old_value);
            }
        private:
            T m_new_value;
            T m_old_value;
        };

        template <>
        class PWC_Attribute_Vector_Set_Front<ElementID>:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Set_Front(Project_Widget*const project_widget, AttributeID attributeid, ElementID const& value):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_new_value(value),
                m_old_value(project_widget->attribute_type_cast<Vector<ElementID>>(attributeid)->front())
            {
                this->project_widget()->increment_command_ref_count(m_old_value);
                this->project_widget()->increment_command_ref_count(m_new_value);
            }
            ~PWC_Attribute_Vector_Set_Front() override
            {
                this->project_widget()->decrement_command_ref_count(m_old_value);
                this->project_widget()->decrement_command_ref_count(m_new_value);
            }

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_set_front<ElementID>(attributeid(), m_new_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_set_front<ElementID>(attributeid(), m_old_value);
            }
        private:
            ElementID m_new_value;
            ElementID m_old_value;
        };

        /*
        PWC_Attribute_Vector_Set_Back<T>
        ====================================================================================================
        */
        template <typename T>
        class PWC_Attribute_Vector_Set_Back:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Set_Back(Project_Widget*const project_widget, AttributeID attributeid, T const& value):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_new_value(value),
                m_old_value(project_widget->attribute_type_cast<Vector<T>>(attributeid)->front())
            {}
            ~PWC_Attribute_Vector_Set_Back() override = default;

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_set_back<T>(attributeid(), m_new_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_set_back<T>(attributeid(), m_old_value);
            }
        private:
            T m_new_value;
            T m_old_value;
        };

        template <>
        class PWC_Attribute_Vector_Set_Back<ElementID>:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Set_Back(Project_Widget*const project_widget, AttributeID attributeid, ElementID const& value):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_new_value(value),
                m_old_value(project_widget->attribute_type_cast<Vector<ElementID>>(attributeid)->front())
            {
                this->project_widget()->increment_command_ref_count(m_old_value);
                this->project_widget()->increment_command_ref_count(m_new_value);
            }
            ~PWC_Attribute_Vector_Set_Back() override
            {
                this->project_widget()->decrement_command_ref_count(m_old_value);
                this->project_widget()->decrement_command_ref_count(m_new_value);
            }

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_set_back<ElementID>(attributeid(), m_new_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_set_back<ElementID>(attributeid(), m_old_value);
            }
        private:
            ElementID m_new_value;
            ElementID m_old_value;
        };

        /*
        PWC_Attribute_Vector_Swap_At<T>
        ====================================================================================================
        */
        template <typename T>
        class PWC_Attribute_Vector_Swap_At:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Swap_At(Project_Widget*const project_widget, AttributeID attributeid, size_type index, size_type other_index):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_index(index),
                m_other_index(other_index)
            {}
            ~PWC_Attribute_Vector_Swap_At() override = default;

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_swap_at<T>(attributeid(), m_index, m_other_index);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_swap_at<T>(attributeid(), m_index, m_other_index);
            }
        private:
            size_type m_index;
            size_type m_other_index;
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
                project_widget()->attribute_vector_push_back<T>(attributeid(), m_new_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_pop_back<T>(attributeid());
            }
        private:
            T m_new_value;
        };

        template <>
        class PWC_Attribute_Vector_Push_Back<ElementID>:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Push_Back(Project_Widget*const project_widget, AttributeID attributeid, ElementID const& value):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_new_value(value)
            {
                this->project_widget()->increment_command_ref_count(m_new_value);
            }
            ~PWC_Attribute_Vector_Push_Back() override
            {
                this->project_widget()->decrement_command_ref_count(m_new_value);
            }

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_push_back<ElementID>(attributeid(), m_new_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_pop_back<ElementID>(attributeid());
            }
        private:
            ElementID m_new_value;
        };

        /*
        PWC_Attribute_Vector_Pop_Back<T>
        ====================================================================================================
        */
        template <typename T>
        class PWC_Attribute_Vector_Pop_Back:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Pop_Back(Project_Widget*const project_widget, AttributeID attributeid):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_old_value(project_widget->attribute_type_cast<Vector<T>>(attributeid)->back())
            {}
            ~PWC_Attribute_Vector_Pop_Back() override = default;

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_pop_back<T>(attributeid());
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_push_back<T>(attributeid(), m_old_value);
            }
        private:
            T m_old_value;
        };

        template <>
        class PWC_Attribute_Vector_Pop_Back<ElementID>:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Pop_Back(Project_Widget*const project_widget, AttributeID attributeid):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_old_value(project_widget->attribute_type_cast<Vector<ElementID>>(attributeid)->back())
            {
                this->project_widget()->increment_command_ref_count(m_old_value);
            }
            ~PWC_Attribute_Vector_Pop_Back() override
            {
                this->project_widget()->decrement_command_ref_count(m_old_value);
            }

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_pop_back<ElementID>(attributeid());
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_push_back<ElementID>(attributeid(), m_old_value);
            }
        private:
            ElementID m_old_value;
        };

        /*
        PWC_Attribute_Vector_Insert_At<T>
        ====================================================================================================
        */
        template <typename T>
        class PWC_Attribute_Vector_Insert_At:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Insert_At(Project_Widget*const project_widget, AttributeID attributeid, size_type index, T const& value):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_index(index),
                m_value(value)
            {}
            ~PWC_Attribute_Vector_Insert_At() override = default;

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_insert_at<T>(attributeid(), m_index, m_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_remove_at<T>(attributeid(), m_index);
            }
        private:
            size_type m_index;
            T m_value;
        };

        template <>
        class PWC_Attribute_Vector_Insert_At<ElementID>:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Insert_At(Project_Widget*const project_widget, AttributeID attributeid, size_type index, ElementID const& value):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_index(index),
                m_value(value)
            {
                this->project_widget()->increment_command_ref_count(m_value);
            }
            ~PWC_Attribute_Vector_Insert_At() override
            {
                this->project_widget()->decrement_command_ref_count(m_value);
            }

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_insert_at<ElementID>(attributeid(), m_index, m_value);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_remove_at<ElementID>(attributeid(), m_index);
            }
        private:
            size_type m_index;
            ElementID m_value;
        };

        /*
        PWC_Attribute_Vector_Remove_At<T>
        ====================================================================================================
        */
        template <typename T>
        class PWC_Attribute_Vector_Remove_At:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Remove_At(Project_Widget*const project_widget, AttributeID attributeid, size_type index):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_index(index),
                m_value(project_widget->attribute_vector_at<T>(attributeid, index))
            {}
            ~PWC_Attribute_Vector_Remove_At() override = default;

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_remove_at<T>(attributeid(), m_index);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_insert_at<T>(attributeid(), m_index, m_value);
            }
        private:
            size_type m_index;
            T m_value;
        };

        template <>
        class PWC_Attribute_Vector_Remove_At<ElementID>:
                public Project_Widget_Command_Attribute
        {
        public:
            PWC_Attribute_Vector_Remove_At(Project_Widget*const project_widget, AttributeID attributeid, size_type index):
                Project_Widget_Command_Attribute(project_widget, attributeid),
                m_index(index),
                m_value(project_widget->attribute_vector_at<ElementID>(attributeid, index))
            {
                this->project_widget()->increment_command_ref_count(m_value);
            }
            ~PWC_Attribute_Vector_Remove_At() override
            {
                this->project_widget()->decrement_command_ref_count(m_value);
            }

        protected:
            void v_execute() override
            {
                project_widget()->attribute_vector_remove_at<ElementID>(attributeid(), m_index);
            }
            void v_unexecute() override
            {
                project_widget()->attribute_vector_insert_at<ElementID>(attributeid(), m_index, m_value);
            }
        private:
            size_type m_index;
            ElementID m_value;
        };

    } // namespace Qtlib
}  // namespace Saklib


#endif // PROJECT_WIDGET_COMMANDS

