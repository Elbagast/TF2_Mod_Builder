#ifndef COMMAND_ELEMENT_H
#define COMMAND_ELEMENT_H

#include "types.h"
#include "command.h"
#include "elementid.h"
#include "attributeid.h"
#include "attribute_type.h"
#include "element_manager.h"

namespace saklib
{
    /*
    Command_Element_Set_Name
    ====================================================================================================

    */
    class Command_Element_Set_Name :
        public Command
    {
    public:
        // Special 6
        //============================================================
        Command_Element_Set_Name(Element_Manager& manager, ElementID elementid, String const& new_name) :
            Command(),
            mr_manager(manager),
            m_elementid(elementid),
            mp_element(mr_manager.element(m_elementid)),
            m_old_name(mp_element->name()),
            m_new_name(new_name)
        {
            assert(mr_manager.has_elementid(m_elementid));
        }
        ~Command_Element_Set_Name() override = default;

    protected:
        // Interface
        //============================================================
        Element* element()
        {
            return mp_element;
        }
        Element const* celement() const
        {
            return mp_element;
        }

        // Virtuals
        //============================================================
        void v_execute() override
        {
            mp_element->set_name(m_new_name);
        }
        void v_unexecute() override
        {
            mp_element->set_name(m_old_name);
        }
    private:
        Element_Manager& mr_manager;
        ElementID m_elementid;
        Element* mp_element;  // lifetime dependent on that of m_elementid
        String m_old_name;
        String m_new_name;
    };

} // namespace saklib

#endif // COMMAND_ELEMENT_H
