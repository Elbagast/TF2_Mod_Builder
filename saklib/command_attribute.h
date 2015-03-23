#ifndef COMMAND_ATTRIBUTE_H
#define COMMAND_ATTRIBUTE_H

#include "types.h"
#include "command.h"
#include "elementid.h"
#include "attributeid.h"
#include "attribute_type.h"

namespace Saklib
{
    /*
    Command_Attribute_Type<T>
    ====================================================================================================
    Intermediate abstract class to save repetition of using declarations and shared construction.

    */
    template <typename T>
    class Command_Attribute :
        public Command
    {
    public:
        // Typedefs
        //============================================================
        using attribute_type = Attribute_Type < T >;
		
        using stored_type = typename attribute_type::stored_type;
        using stored_type_traits = typename attribute_type::stored_type_traits;

        // Special 6
        //============================================================
        Command_Attribute(AttributeID const& attributeid) :
            Command(),
            m_attributeid(attributeid),
            mp_attribute(m_attributeid.attribute_type_cast<stored_type>())
        {
            assert(mp_attribute != nullptr);
        }
        Command_Attribute(ElementID const& elementid, String const& attribute_name) :
            Command_Attribute(AttributeID(elementid, attribute_name))
        {}
        ~Command_Attribute() override = default;

    protected:
        // Interface
        //============================================================
        attribute_type* attribute() const
        { 
            return mp_attribute;
        }

        // Virtuals
        //============================================================
        void v_execute() override = 0;
        void v_unexecute() override = 0;
    private:
        AttributeID m_attributeid;
        attribute_type* mp_attribute;  // lifetime dependent on that of m_attributeid
    };


    /*
    Command_Attribute_Set_Value<T>
    ====================================================================================================
    Encapsulate the changing of a value for a given Attribute_Simple<T>, storing an ElementID so that
    the relevent Element will still exist while the command does.

    */
    template <typename T>
    class Command_Attribute_Set:
        public Command_Attribute<T>
    {
    public:
        Command_Attribute_Set(AttributeID const& attributeid, stored_type const& new_value) :
            Command_Attribute<T>(attributeid),
            m_old_value(attribute()->get()),
            m_new_value(new_value)
        {}
        Command_Attribute_Set(ElementID const& elementid, String const& attribute_name, stored_type const& new_value) :
            Command_Attribute_Set(AttributeID(elementid, attribute_name), new_value)
        {}
        ~Command_Attribute_Set() override = default;

    protected:
        void v_execute() override
        {
            attribute()->set(m_new_value);
        }
        void v_unexecute() override
        {
            attribute()->set(m_old_value);
        }

    private:
        stored_type m_old_value;
        stored_type m_new_value;
    };


    /*
    Command_Attribute_Set_Value<Vector<T>>>
    ====================================================================================================
    Encapsulate the changing of a value for a given Attribute_Simple<T>, storing an ElementID so that
    the relevent Element will still exist while the command does.

    */
    template <typename T>
    class Command_Attribute_Set<Vector<T>> :
        public Command_Attribute<Vector<T>>
    {
    public:
        Command_Attribute_Set(AttributeID const& attributeid, stored_type const& new_value) :
            Command_Attribute<Vector<T>>(attributeid),
            m_old_value(attribute()->vector()),
            m_new_value(new_value)
        {}
        Command_Attribute_Set(ElementID const& elementid, String const& attribute_name, stored_type const& new_value) :
            Command_Attribute_Set(AttributeID(elementid, attribute_name), new_value)
        {}
        ~Command_Attribute_Set() override = default;

    protected:
        void v_execute() override
        {
            attribute()->vector() = m_new_value;
        }
        void v_unexecute() override
        {
            attribute()->vector() = m_old_value;
        }

    private:
        stored_type m_old_value;
        stored_type m_new_value;
    };


} // namespace Saklib

#endif // COMMAND_ATTRIBUTE_H
