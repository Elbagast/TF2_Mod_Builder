#ifndef SAKLIB_ELEMENT_H
#define SAKLIB_ELEMENT_H

#ifndef SAKLIB_ELEMENT__FWD_H
#include "element__fwd.h"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

namespace saklib
{
    //---------------------------------------------------------------------------
    // Element
    //---------------------------------------------------------------------------
    // API class for undo-enabled editing of Element data.

    class Element
    {
    public:
        // Special 6
        //============================================================
        // How will these be made...
        Element();
        ~Element();

        Element(Element const& a_other);
        Element& operator=(Element const& a_other);

        Element(Element && a_other);
        Element& operator=(Element && a_other);

        // Interface
        //============================================================

    private:
        // Data Members
        //============================================================
        class Implementation;

        Implementation* get_implementation();
        Implementation const* cget_implementation() const;

        std::unique_ptr<Implementation> m_implementation;
    };
} // namespace saklib


#endif // ELEMENT_H
