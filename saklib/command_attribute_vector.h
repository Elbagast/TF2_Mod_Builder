#ifndef COMMAND_ATTRIBUTE_VECTOR_H
#define COMMAND_ATTRIBUTE_VECTOR_H

#include "types.h"
#include "command.h"
#include "elementid.h"
#include "attributeid.h"
#include <vector>

namespace Saklib
{
    // does all this need to be in this header on its own? the other one already includes <vector> and
    // you need to know all the commands to use them...


    /*
    Command_Attribute_Vector<T>
    ====================================================================================================
    Intermediate abstract class to save repetition of using declarations and shared construction.
    */
    template <typename T>
    class Command_Attribute_Vector :
        public Command
    {
    public:
        using attribute_type = Attribute_Type < Vector<T> >;
		        
        using stored_type = typename attribute_type::stored_type;
        using stored_type_traits = typename attribute_type::stored_type_traits;

        using value_type = typename attribute_type::value_type;
        using value_type_traits = typename attribute_type::value_type_traits;
               

        Command_Attribute_Vector(AttributeID&& attributeid) :
            Command(),
            m_attributeid(std::forward<AttributeID>(attributeid)),
            mp_attribute(m_attributeid.attribute_type_cast<stored_type>())
        {
            assert(mp_attribute != nullptr);
        }
        Command_Attribute_Vector(ElementID const& elementid, String const& attribute_name, stored_type&& new_value) :
            Command_Attribute_Vector(AttributeID(elementid, attribute_name), std::forward<stored_type>(new_value))
        {}
        ~Command_Attribute_Vector() override = default;

    protected:
        attribute_type* attribute() const
        { 
            return mp_attribute;
        }

        void v_execute() override = 0;
        void v_unexecute() override = 0;
    private:
        AttributeID m_attributeid;
        attribute_type* mp_attribute;  // lifetime dependent on that of m_attributeid
    };

    
    /*
    Command_Attribute_Vector_Set_Value_At<T>
    ====================================================================================================
    Encapsulate a reversible call to change a vector value at a given index.

    Currently will break if the index call is out of bounds.

    */
    template <typename T>
    class Command_Attribute_Vector_Set_Value_At :
        public Command_Attribute_Vector<T>
    {
    public:
        Command_Attribute_Vector_Set_Value_At(AttributeID&& attributeid, size_type index, value_type new_value) :
            Command_Attribute_Vector<T>(std::forward<AttributeID>(attributeid)),
            m_index(index),
            m_old_value(attribute()->vector().at(index)),
            m_new_value(std::move(new_value))
        {}
        Command_Attribute_Vector_Set_Value_At(ElementID const& elementid, String const& attribute_name, size_type index, value_type new_value) :
            Command_Attribute_Vector_Set_Value_At(AttributeID(elementid, attribute_name), index, new_value)
        {}
        ~Command_Attribute_Vector_Set_Value_At() override = default;

    protected:
        void v_execute() override
        {
            attribute()->vector().at(m_index) = m_new_value;
        }
        void v_unexecute() override
        {
            attribute()->vector().at(m_index) = m_old_value;
        }

    private:
        size_type m_index;

        value_type m_old_value;
        value_type m_new_value;
    };

    /*
    Command_Attribute_Vector_Set_Back<T>
    ====================================================================================================
    Encapsulate a reversible call to change a vector value at the back of the vector.

    Currently will break if the index call is out of bounds.

    */
    template <typename T>
    class Command_Attribute_Vector_Set_Back :
        public Command_Attribute_Vector<T>
    {
    public:
        Command_Attribute_Vector_Set_Back(AttributeID&& attributeid, value_type new_value) :
            Command_Attribute_Vector<T>(std::forward<AttributeID>(attributeid)),
            m_old_value(attribute()->vector().at(index)),
            m_new_value(std::move(new_value))
        {}
        Command_Attribute_Vector_Set_Back(ElementID const& elementid, String const& attribute_name, value_type new_value) :
            Command_Attribute_Vector_Set_Back(AttributeID(elementid, attribute_name), new_value)
        {}
        ~Command_Attribute_Vector_Set_Back() override = default;

    protected:
        void v_execute() override
        {
            attribute()->vector().back() = m_new_value;
        }
        void v_unexecute() override
        {
            attribute()->vector().back() = m_old_value;
        }

    private:
        value_type m_old_value;
        value_type m_new_value;
    };

    /*
    Command_Attribute_Vector_Set_Front<T>
    ====================================================================================================
    Encapsulate a reversible call to change a vector value at the front of the vector.

    Currently will break if the index call is out of bounds.

    */
    template <typename T>
    class Command_Attribute_Vector_Set_Front :
        public Command_Attribute_Vector<T>
    {
    public:
        Command_Attribute_Vector_Set_Front(AttributeID&& attributeid, value_type new_value) :
            Command_Attribute_Vector<T>(std::forward<AttributeID>(attributeid)),
            m_old_value(attribute()->vector().at(index)),
            m_new_value(std::move(new_value))
        {}
        Command_Attribute_Vector_Set_Front(ElementID const& elementid, String const& attribute_name, value_type new_value) :
            Command_Attribute_Vector_Set_Front(AttributeID(elementid, attribute_name), new_value)
        {}
        ~Command_Attribute_Vector_Set_Front() override = default;

    protected:
        void v_execute() override
        {
            attribute()->vector().front() = m_new_value;
        }
        void v_unexecute() override
        {
            attribute()->vector().front() = m_old_value;
        }

    private:        
        value_type m_old_value;
        value_type m_new_value;
    };

    /*
    Command_Attribute_Vector_Push_Back<T>
    ====================================================================================================
    Encapsulate a reversible call to push_back a value to a vector.
    */
    template <typename T>
    class Command_Attribute_Vector_Push_Back :
        public Command_Attribute_Vector<T>
    {
    public:
        Command_Attribute_Vector_Push_Back(AttributeID&& attributeid, value_type new_value) :
            Command_Attribute_Vector<T>(std::forward<AttributeID>(attributeid)),
            m_new_value(std::move(new_value))
        {}
        Command_Attribute_Vector_Push_Back(ElementID const& elementid, String const& attribute_name, value_type new_value) :
            Command_Attribute_Vector_Push_Back(AttributeID(elementid, attribute_name), new_value)
        {}
        ~Command_Attribute_Vector_Push_Back() override = default;

    protected:
        void v_execute() override
        {
            attribute()->vector().push_back(m_new_value);
        }
        void v_unexecute() override
        {
            attribute()->vector().pop_back();
        }

    private:
        value_type m_new_value;
    };

    /*
    Command_Attribute_Vector_Push_Front<T>
    ====================================================================================================
    Encapsulate a reversible call to push_front a value to a vector.
    */
    template <typename T>
    class Command_Attribute_Vector_Push_Front :
        public Command_Attribute_Vector<T>
    {
    public:
        Command_Attribute_Vector_Push_Front(AttributeID&& attributeid, value_type new_value) :
            Command_Attribute_Vector<T>(std::forward<AttributeID>(attributeid)),
            m_new_value(std::move(new_value))
        {}
        Command_Attribute_Vector_Push_Front(ElementID const& elementid, String const& attribute_name, value_type new_value) :
            Command_Attribute_Vector_Push_Front(AttributeID(elementid, attribute_name), new_value)
        {}
        ~Command_Attribute_Vector_Push_Front() override = default;

    protected:
        void v_execute() override
        {
            attribute()->vector().push_front(m_new_value);
        }
        void v_unexecute() override
        {
            attribute()->vector().pop_front();
        }

    private:
        value_type m_new_value;
    };

    /*
    Command_Attribute_Vector_Pop_Back<T>
    ====================================================================================================
    Encapsulate a reversible call to pop_back a vector.
    */
    template <typename T>
    class Command_Attribute_Vector_Pop_Back :
        public Command_Attribute_Vector<T>
    {
    public:
        Command_Attribute_Vector_Pop_Back(AttributeID&& attributeid) :
            Command_Attribute_Vector<T>(std::forward<AttributeID>(attributeid)),
            m_old_back_value(attribute()->vector().back())
        {}
        Command_Attribute_Vector_Pop_Back(ElementID const& elementid, String const& attribute_name) :
            Command_Attribute_Vector_Pop_Back(AttributeID(elementid, attribute_name))
        {}
        ~Command_Attribute_Vector_Pop_Back() override = default;

    protected:
        void v_execute() override
        {
            attribute()->vector().pop_back();
        }
        void v_unexecute() override
        {
            attribute()->vector().push_back(m_old_back_value);
        }
    private:
        value_type m_old_back_value;
    };

    /*
    Command_Attribute_Vector_Pop_Front<T>
    ====================================================================================================
    Encapsulate a reversible call to pop_front a vector.
    */
    template <typename T>
    class Command_Attribute_Vector_Pop_Front :
        public Command_Attribute_Vector<T>
    {
    public:
        Command_Attribute_Vector_Pop_Front(AttributeID&& attributeid) :
            Command_Attribute_Vector<T>(std::forward<AttributeID>(attributeid)),
            m_old_front_value(attribute()->vector().front())
        {}
        Command_Attribute_Vector_Pop_Front(ElementID const& elementid, String const& attribute_name) :
            Command_Attribute_Vector_Pop_Front(AttributeID(elementid, attribute_name))
        {}
        ~Command_Attribute_Vector_Pop_Front() override = default;

    protected:
        void v_execute() override
        {
            attribute()->vector().pop_front();
        }
        void v_unexecute() override
        {
            attribute()->vector().push_front(m_old_front_value);
        }
    private:
        value_type m_old_front_value;
    };


    /*
    Command_Attribute_Vector_Clear<T>
    ====================================================================================================
    Encapsulate a reversible call to clear a vector, though it doesn't actually call clear.
    */
    template <typename T>
    class Command_Attribute_Vector_Clear :
        public Command_Attribute_Vector<T>
    {
    public:
        Command_Attribute_Vector_Clear(AttributeID&& attributeid) :
            Command_Attribute_Vector<T>(std::forward<AttributeID>(attributeid)),
            m_vector_contents() // default empty vector
        {}
        Command_Attribute_Vector_Clear(ElementID const& elementid, String const& attribute_name) :
            Command_Attribute_Vector_Clear(AttributeID(elementid, attribute_name))
        {}
        ~Command_Attribute_Vector_Clear() override = default;

    protected:
        void v_execute() override
        {
            m_vector_contents.clear();
            attribute()->vector().swap(m_vector_contents);
        }
        void v_unexecute() override
        {
            attribute()->vector().swap(m_vector_contents);
        }

    private:
        stored_type m_vector_contents;
    };

} // namespace Saklib

#endif // COMMAND_ATTRIBUTE_VECTOR_H