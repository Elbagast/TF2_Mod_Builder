#ifndef SAKLIB_ELEMENT_H
#define SAKLIB_ELEMENT_H

#ifndef SAKLIB_ELEMENT__FWD_H
#include "element__fwd.h"
#endif

#ifndef INCLUDE_STD_MEMORY
#define INCLUDE_STD_MEMORY
#include <memory>
#endif

#ifndef INCLUDE_STD_VECTOR
#define INCLUDE_STD_VECTOR
#include <vector>
#endif

namespace saklib
{
    class ElementID;
    class String;
    class Attribute;

    //---------------------------------------------------------------------------
    // Element
    //---------------------------------------------------------------------------
    // API class for undo-enabled editing of Element data.

    namespace internal
    {
        class Element_Implementation;
    }

    class Element
    {
    public:
        // Special 6
        //============================================================
        // How will these be made...
        Element();
        explicit Element(std::unique_ptr<internal::Element_Implementation>&& a_implementation);
        ~Element();

        Element(Element const& a_other);
        Element& operator=(Element const& a_other);

        Element(Element && a_other);
        Element& operator=(Element && a_other);

        // Interface
        //============================================================
        bool is_valid() const;
        bool is_null() const;

        ElementID cget_id() const;

        String cget_type() const;

        String cget_name() const;
        void set_name(String a_name);

        std::size_t cget_attribute_count() const;
        bool has_attribute(std::size_t a_index) const;

        Attribute cget_attribute_at(std::size_t a_index) const;

        std::vector<Attribute> cget_attributes() const;
    private:
        // Data Members
        //============================================================
        internal::Element_Implementation* get_implementation();
        internal::Element_Implementation const* cget_implementation() const;

        std::unique_ptr<internal::Element_Implementation> m_implementation;
    };
} // namespace saklib


#endif // ELEMENT_H
