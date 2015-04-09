#ifndef CONSTRAINT_TYPE_ELEMENTID_H
#define CONSTRAINT_TYPE_ELEMENTID_H

#include "constraint_type.h"

namespace Saklib
{
    /*
    Constraint_Type<ElementID>
    ====================================================================================================
    Overload for ElementID rather than providing a version called Constraint_ElementID

    This interface doesn't really make sense...

    */
    template <>
    class Constraint_Type<ElementID>
    {
    public:
        Constraint_Type(Vector_String const& element_types):
            m_element_types(element_types)
        {}
        ~Constraint_Type() override = default;

        Vector_String const& element_types() const { return m_element_types; }
        // edit after construction?...

    protected:
        bool v_value_can_be(ElementID const& value) override
        {
            // Not going to make sense without a Project_Manager...
            return false;
        }
    private:
        Vector_String m_element_types;
    };

} // namespace Saklib

#endif // CONSTRAINT_TYPE_ELEMENTID_H
