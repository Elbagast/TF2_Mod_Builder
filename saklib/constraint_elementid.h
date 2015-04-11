#ifndef CONSTRAINT_ELEMENTID_H
#define CONSTRAINT_ELEMENTID_H

#include "constraint.h"
#include "maybe.h"

namespace Saklib
{
    /*
    Constraint<ElementID>
    ====================================================================================================
    Overload for ElementID rather than providing a version called Constraint_ElementID


    */
    template <>
    class Constraint<ElementID>
    {
    public:
        // Special 6
        //============================================================
        explicit Constraint(Vector_String const& element_types, String const& default_type = String()):
            m_element_types(element_types),
            m_default_element_type()
        {
            if (!default_type.empty()) // and is in the supplied vector...
            {
                set_default_type(default_type);
            }
        }
        ~Constraint() = default;

        Constraint(Constraint const& other) = default;
        Constraint& operator=(Constraint const& other) = default;

        //Constraint(Constraint && other) = default;
        //Constraint& operator=(Constraint && other) = default;

        // Interface
        //============================================================
        Vector_String const& element_types() const
        {
            return m_element_types;
        }
        // edit m_element_types after construction?

        bool has_default_type() const
        {
            return m_default_element_type.used();
        }
        String const& default_type() const
        {
            return m_default_element_type.value();
        }

        void set_default_type(String const& element_type)
        {
            m_default_element_type.set_value(element_type);
        }
        void unset_default_type()
        {
            m_default_element_type.unset_value();
        }

    private:
        Vector_String m_element_types;
        Maybe<String> m_default_element_type;
    };

} // namespace Saklib

#endif // CONSTRAINT_ELEMENTID_H
