#ifndef SAKLIB_ELEMENT_H
#define SAKLIB_ELEMENT_H

#ifndef SAKLIB_ELEMENT__FWD_H
#include "element__fwd.h"
#endif

namespace saklib
{
    template <typename T>
    class Vector;

    class Attribute;
    class Size_Type;

    class Element
    {
    public:
        Attribute cget_parent_attribute() const;
        Element cget_parent_element() const;

        Size_Type cget_child_element_count() const;
        Vector<Element> cget_child_elements() const;

        Size_Type cget_ancestor_element_count() const;
        Vector<Element> cget_ancestor_elements() const;

        Size_Type cget_descendent_element_count() const;
        Vector<Element> cget_descendent_elements() const;
    };

} // namespace saklib

#endif // SAKLIB_ELEMENT_H

