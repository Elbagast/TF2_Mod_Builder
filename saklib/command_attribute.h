#ifndef COMMAND_ATTRIBUTE_H
#define COMMAND_ATTRIBUTE_H

#include "types.h"
#include "command.h"
#include "elementid.h"
#include "attributeid.h"
#include "attribute_type.h"
#include "element_manager.h"

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
        Command_Attribute(Element_Manager& manager, AttributeID attributeid) :
            Command(),
            mr_manager(manager),
            m_attributeid(attributeid),
            mp_attribute(attribute_type_cast<stored_type>(mr_manager.attribute(m_attributeid)))
        {
            assert(mr_manager.is_valid(m_attributeid));
            assert(mp_attribute != nullptr);
        }
        ~Command_Attribute() override = default;

    protected:
        // Interface
        //============================================================
        attribute_type*const attribute() const
        { 
            return mp_attribute;
        }

        // Virtuals
        //============================================================
        void v_execute() override = 0;
        void v_unexecute() override = 0;
    private:
        Element_Manager& mr_manager;
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
    class Command_Attribute_Set_Value:
        public Command_Attribute<T>
    {
    public:
        Command_Attribute_Set_Value(Element_Manager& manager, AttributeID attributeid, stored_type const& new_value) :
            Command_Attribute<T>(manager, attributeid),
            m_old_value(attribute()->value()),
            m_new_value(new_value)
        {}
        ~Command_Attribute_Set_Value() override = default;

    protected:
        void v_execute() override
        {
            attribute()->set_value(m_new_value);
        }
        void v_unexecute() override
        {
            attribute()->set_value(m_old_value);
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
    class Command_Attribute_Set_Value<Vector<T>> :
        public Command_Attribute<Vector<T>>
    {
    public:
        Command_Attribute_Set_Value(Element_Manager& manager, AttributeID attributeid, stored_type const& new_value) :
            Command_Attribute<Vector<T>>(manager, attributeid),
            m_old_value(attribute()->vector()),
            m_new_value(new_value)
        {}
        ~Command_Attribute_Set_Value() override = default;

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
