#ifndef PROJECT_MANAGER_COMMANDS_H
#define PROJECT_MANAGER_COMMANDS_H

#include "project_manager_declaration.h"
#include "command.h"

namespace Saklib
{
    /*
    Command_Value<T>
    ====================================================================================================
    Wrapper class for storing values inside commands. By using this the increment/decrementing of ref
    counts for Elements is dealt with in the specialisations of this class rather than inside
    specialisations of Command classes.
    */
    template <typename T>
    class Command_Value
    {
    public:
        Command_Value(Project_Manager* /*project_manager*/, T const& value) :
            m_value(value)
      {}
        ~Command_Value() = default;

        T& value ()                             { return m_value; }
        T const& cvalue() const                 { return m_value; }

        operator T& ()                          { return m_value; }
        operator T const& () const              { return m_value; }
    private:
        T m_value;
    };

    /*
    Command_Value<ElementID>
    ====================================================================================================
    */
    template <>
    class Command_Value<ElementID>
    {
    public:
        Command_Value(Project_Manager* project_manager, ElementID const& value) :
              mp_project_manager{project_manager},
              m_value{value}
        {
            assert(mp_project_manager);
            mp_project_manager->increment_command_ref_count(m_value);
        }
        ~Command_Value()
        {
            mp_project_manager->decrement_command_ref_count(m_value);
        }

        ElementID& value ()                     { return m_value; }
        ElementID const& cvalue() const         { return m_value; }

        operator ElementID& ()                  { return m_value; }
        operator ElementID const& () const      { return m_value; }

        Project_Manager* project_manager()      { return mp_project_manager; }

    private:
        Project_Manager* mp_project_manager;
        ElementID m_value;
    };


    /*
    Command_Value<Vector<ElementID>>
    ====================================================================================================
    */
    template <>
    class Command_Value<Vector<ElementID>>
    {
    public:
        Command_Value(Project_Manager* project_manager, Vector<ElementID> const& value) :
              mp_project_manager{project_manager},
              m_value(value)
        {
            assert(mp_project_manager);
            for (auto const& value : m_value)
            {
                mp_project_manager->increment_command_ref_count(value);
            }
        }
        ~Command_Value()
        {
            for (auto const& value : m_value)
            {
                mp_project_manager->increment_command_ref_count(value);
            }
        }

        Vector<ElementID>& value ()                 { return m_value; }
        Vector<ElementID> const& cvalue() const     { return m_value; }

        operator Vector<ElementID>& ()              { return m_value; }
        operator Vector<ElementID> const& () const  { return m_value; }

        Project_Manager* project_manager()          { return mp_project_manager; }

    private:
        Project_Manager* mp_project_manager;
        Vector<ElementID> m_value;
    };

    /*
    Command_Value<AttributeID>
    ====================================================================================================
    */
    template <>
    class Command_Value<AttributeID>
    {
    public:
        Command_Value(Project_Manager* project_manager, AttributeID const& value) :
              mp_project_manager{project_manager},
              m_value{value}
        {
            assert(mp_project_manager);
            mp_project_manager->increment_command_ref_count(m_value);
        }
        ~Command_Value()
        {
            mp_project_manager->decrement_command_ref_count(m_value);
        }

        AttributeID& value ()                   { return m_value; }
        AttributeID const& cvalue() const       { return m_value; }

        operator AttributeID& ()                { return m_value; }
        operator AttributeID const& () const    { return m_value; }

        Project_Manager* project_manager()      { return mp_project_manager; }

    private:
        Project_Manager* mp_project_manager;
        AttributeID m_value;
    };


    /*
    Project_Manager_Command_Element
    ====================================================================================================
    Shared garbage collection modifications go here
    */
    class Project_Manager_Command_Element:
            public Command
    {
    public:
        Project_Manager_Command_Element(Project_Manager* project_manager, ElementID const& elementid):
            Command(),
            m_elementid(project_manager, elementid)
        {
        }
        ~Project_Manager_Command_Element() override = default;

        Project_Manager* project_manager()          { return m_elementid.project_manager(); }
        ElementID const& elementid() const          { return m_elementid; }

    protected:
        void v_execute() override = 0;
        void v_unexecute() override = 0;
    private:
        Command_Value<ElementID> m_elementid;
    };

    /*
    Project_Manager_Command_Attribute
    ====================================================================================================
    Shared garbage collection modifications go here
    */
    class Project_Manager_Command_Attribute:
            public Command
    {
    public:
        Project_Manager_Command_Attribute(Project_Manager* project_manager, AttributeID const& attributeid):
            Command(),
            m_attributeid(project_manager, attributeid)
        {
        }
        ~Project_Manager_Command_Attribute() override = default;

        Project_Manager* project_manager()          { return m_attributeid.project_manager(); }
        ElementID const& elementid() const          { return m_attributeid.cvalue().elementid(); }
        AttributeID const& attributeid() const      { return m_attributeid; }

    protected:
        void v_execute() override = 0;
        void v_unexecute() override = 0;
    private:
        Command_Value<AttributeID> m_attributeid;
    };

    /*
    PMC_Element_Set_Name
    ====================================================================================================
    */
    class PMC_Element_Set_Name:
            public Project_Manager_Command_Element
    {
    public:
        PMC_Element_Set_Name(Project_Manager* project_manager, ElementID const& elementid, String const& name):
            Project_Manager_Command_Element(project_manager, elementid),
            m_old_name(project_manager, project_manager->element_name(elementid)),
            m_new_name(project_manager, name)
        {}
        ~PMC_Element_Set_Name() override = default;

    protected:
        void v_execute() override
        {
            project_manager()->element_set_name(elementid(), m_new_name);
        }
        void v_unexecute() override
        {
            project_manager()->element_set_name(elementid(), m_old_name);
        }
    private:
        Command_Value<String> m_old_name;
        Command_Value<String> m_new_name;
    };

    /*
    PMC_Attribute_Set_Value<T>
    ====================================================================================================
    */
    template <typename T>
    class PMC_Attribute_Set_Value:
            public Project_Manager_Command_Attribute
    {
    public:
        PMC_Attribute_Set_Value(Project_Manager* project_manager, AttributeID const& attributeid, T const& value):
            Project_Manager_Command_Attribute(project_manager, attributeid),
            m_old_value(project_manager, project_manager->template attribute_value<T>(attributeid)),
            m_new_value(project_manager, value)
        {}
        ~PMC_Attribute_Set_Value() override = default;

    protected:
        void v_execute() override
        {
            project_manager()->template attribute_set_value<T>(attributeid(), m_new_value);
        }
        void v_unexecute() override
        {
            project_manager()->template attribute_set_value<T>(attributeid(), m_old_value);
        }
    private:
        Command_Value<T> m_old_value;
        Command_Value<T> m_new_value;
    };

    /*
    PMC_Attribute_Vector_Clear<T>
    ====================================================================================================
    */
    template <typename T>
    class PMC_Attribute_Vector_Clear:
            public Project_Manager_Command_Attribute
    {
    public:
        PMC_Attribute_Vector_Clear(Project_Manager* project_manager, AttributeID const& attributeid):
            Project_Manager_Command_Attribute(project_manager, attributeid),
            m_old_vector(project_manager, project_manager->template attribute_vector_vector<T>(attributeid))
        {}
        ~PMC_Attribute_Vector_Clear() override = default;

    protected:
        void v_execute() override
        {
            project_manager()->template attribute_vector_clear<T>(attributeid());
        }
        void v_unexecute() override
        {
            project_manager()->template attribute_vector_set_vector<T>(attributeid(), m_old_vector);
        }
    private:
        Command_Value<Vector<T>> m_old_vector;
    };

    /*
    PMC_Attribute_Vector_Set_At<T>
    ====================================================================================================
    */
    template <typename T>
    class PMC_Attribute_Vector_Set_At:
            public Project_Manager_Command_Attribute
    {
    public:
        PMC_Attribute_Vector_Set_At(Project_Manager* project_manager, AttributeID const& attributeid, size_type index, T const& value):
            Project_Manager_Command_Attribute(project_manager, attributeid),
            m_index(index),
            m_new_value(project_manager, value),
            m_old_value(project_manager, project_manager->template attribute_vector_at<T>(attributeid, index))
        {}
        ~PMC_Attribute_Vector_Set_At() override = default;

    protected:
        void v_execute() override
        {
            project_manager()->template attribute_vector_set_at<T>(attributeid(), m_index, m_new_value);
        }
        void v_unexecute() override
        {
            project_manager()->template attribute_vector_set_at<T>(attributeid(), m_index, m_old_value);
        }
    private:
        size_type m_index;
        Command_Value<T> m_new_value;
        Command_Value<T> m_old_value;
    };

    /*
    PMC_Attribute_Vector_Set_Front<T>
    ====================================================================================================
    */
    template <typename T>
    class PMC_Attribute_Vector_Set_Front:
            public Project_Manager_Command_Attribute
    {
    public:
        PMC_Attribute_Vector_Set_Front(Project_Manager* project_manager, AttributeID const& attributeid, T const& value):
            Project_Manager_Command_Attribute(project_manager, attributeid),
            m_new_value(project_manager, value),
            m_old_value(project_manager, project_manager->attribute_vector_front<T>(attributeid))
        {}
        ~PMC_Attribute_Vector_Set_Front() override = default;

    protected:
        void v_execute() override
        {
            project_manager()->template attribute_vector_set_front<T>(attributeid(), m_new_value);
        }
        void v_unexecute() override
        {
            project_manager()->template attribute_vector_set_front<T>(attributeid(), m_old_value);
        }
    private:
        Command_Value<T> m_new_value;
        Command_Value<T> m_old_value;
    };

    /*
    PMC_Attribute_Vector_Set_Back<T>
    ====================================================================================================
    */
    template <typename T>
    class PMC_Attribute_Vector_Set_Back:
            public Project_Manager_Command_Attribute
    {
    public:
        PMC_Attribute_Vector_Set_Back(Project_Manager* project_manager, AttributeID const& attributeid, T const& value):
            Project_Manager_Command_Attribute(project_manager, attributeid),
            m_new_value(project_manager, value),
            m_old_value(project_manager, project_manager->attribute_vector_back<T>(attributeid))
        {}
        ~PMC_Attribute_Vector_Set_Back() override = default;

    protected:
        void v_execute() override
        {
            project_manager()->template attribute_vector_set_back<T>(attributeid(), m_new_value);
        }
        void v_unexecute() override
        {
            project_manager()->template attribute_vector_set_back<T>(attributeid(), m_old_value);
        }
    private:
        Command_Value<T> m_new_value;
        Command_Value<T> m_old_value;
    };

    /*
    PMC_Attribute_Vector_Swap_At<T>
    ====================================================================================================
    */
    template <typename T>
    class PMC_Attribute_Vector_Swap_At:
            public Project_Manager_Command_Attribute
    {
    public:
        PMC_Attribute_Vector_Swap_At(Project_Manager* project_manager, AttributeID const& attributeid, size_type index, size_type other_index):
            Project_Manager_Command_Attribute(project_manager, attributeid),
            m_index(index),
            m_other_index(other_index)
        {}
        ~PMC_Attribute_Vector_Swap_At() override = default;

    protected:
        void v_execute() override
        {
            project_manager()->template attribute_vector_swap_at<T>(attributeid(), m_index, m_other_index);
        }
        void v_unexecute() override
        {
            project_manager()->template attribute_vector_swap_at<T>(attributeid(), m_index, m_other_index);
        }
    private:
        size_type m_index;
        size_type m_other_index;
    };

    /*
    PMC_Attribute_Vector_Push_Back<T>
    ====================================================================================================
    */
    template <typename T>
    class PMC_Attribute_Vector_Push_Back:
            public Project_Manager_Command_Attribute
    {
    public:
        PMC_Attribute_Vector_Push_Back(Project_Manager* project_manager, AttributeID const& attributeid, T const& value):
            Project_Manager_Command_Attribute(project_manager, attributeid),
            m_new_value(project_manager, value)
        {}
        ~PMC_Attribute_Vector_Push_Back() override = default;
    protected:
        void v_execute() override
        {
            project_manager()->template attribute_vector_push_back<T>(attributeid(), m_new_value);
        }
        void v_unexecute() override
        {
            project_manager()->template attribute_vector_pop_back<T>(attributeid());
        }
    private:
        Command_Value<T> m_new_value;
    };

    /*
    PMC_Attribute_Vector_Pop_Back<T>
    ====================================================================================================
    */
    template <typename T>
    class PMC_Attribute_Vector_Pop_Back:
            public Project_Manager_Command_Attribute
    {
    public:
        PMC_Attribute_Vector_Pop_Back(Project_Manager* project_manager, AttributeID const& attributeid):
            Project_Manager_Command_Attribute(project_manager, attributeid),
            m_old_value(project_manager, project_manager->attribute_vector_back<T>(attributeid))
        {}
        ~PMC_Attribute_Vector_Pop_Back() override = default;

    protected:
        void v_execute() override
        {
            project_manager()->template attribute_vector_pop_back<T>(attributeid());
        }
        void v_unexecute() override
        {
            project_manager()->template attribute_vector_push_back<T>(attributeid(), m_old_value);
        }
    private:
        Command_Value<T> m_old_value;
    };

    /*
    PMC_Attribute_Vector_Insert_At<T>
    ====================================================================================================
    */
    template <typename T>
    class PMC_Attribute_Vector_Insert_At:
            public Project_Manager_Command_Attribute
    {
    public:
        PMC_Attribute_Vector_Insert_At(Project_Manager* project_manager, AttributeID const& attributeid, size_type index, T const& value):
            Project_Manager_Command_Attribute(project_manager, attributeid),
            m_index(index),
            m_value(project_manager, value)
        {}
        ~PMC_Attribute_Vector_Insert_At() override = default;

    protected:
        void v_execute() override
        {
            project_manager()->template attribute_vector_insert_at<T>(attributeid(), m_index, m_value);
        }
        void v_unexecute() override
        {
            project_manager()->template attribute_vector_remove_at<T>(attributeid(), m_index);
        }
    private:
        size_type m_index;
        Command_Value<T> m_value;
    };

    /*
    PMC_Attribute_Vector_Remove_At<T>
    ====================================================================================================
    */
    template <typename T>
    class PMC_Attribute_Vector_Remove_At:
            public Project_Manager_Command_Attribute
    {
    public:
        PMC_Attribute_Vector_Remove_At(Project_Manager* project_manager, AttributeID const& attributeid, size_type index):
            Project_Manager_Command_Attribute(project_manager, attributeid),
            m_index(index),
            m_value(project_manager, project_manager->attribute_vector_at<T>(attributeid, index))
        {}
        ~PMC_Attribute_Vector_Remove_At() override = default;

    protected:
        void v_execute() override
        {
            project_manager()->template attribute_vector_remove_at<T>(attributeid(), m_index);
        }
        void v_unexecute() override
        {
            project_manager()->template attribute_vector_insert_at<T>(attributeid(), m_index, m_value);
        }
    private:
        size_type m_index;
        Command_Value<T> m_value;
    };

}  // namespace Saklib


#endif // PROJECT_MANAGER_COMMANDS_H

