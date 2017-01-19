#ifndef SAKLIB_INTERNAL_ELEMENT_ID_H
#define SAKLIB_INTERNAL_ELEMENT_ID_H

#ifndef SAKLIB_INTERNAL_ELEMENT_ID__FWD_H
#include "element_id__fwd.h"
#endif

#ifndef SAKLIB_INTERNAL_UINT_ID_H
#include "uint_id.h"
#endif

#ifndef INCLUDE_STD_CSTDDEF
#define INCLUDE_STD_CSTDDEF
#include <cstddef>
#endif

namespace saklib
{
    namespace internal
    {
        //---------------------------------------------------------------------------
        // Unsigned_Integer_ID<T>
        //---------------------------------------------------------------------------
        class Element_ID
        {
            friend class Element_ID_Factory;
        public:
            // Typedefs
            //============================================================
            using id_type = Unsigned_Integer_ID<std::size_t>;
            using value_type = id_type::uint_type;

            // Special 6
            //============================================================
            Element_ID();
            explicit Element_ID(value_type a_value);
            explicit Element_ID(id_type a_id);
            ~Element_ID();

            Element_ID(Element_ID const& a_other);
            Element_ID& operator=(Element_ID const& a_other);

            Element_ID(Element_ID && a_other);
            Element_ID& operator=(Element_ID && a_other);

            // Interface
            //============================================================
            bool is_valid() const;
            bool is_null() const;

            value_type get_value() const;

            explicit operator bool() const;

            static value_type get_null_value();

        private:
            // Data Members
            //============================================================
            id_type m_id;
        };

        // Comparison Operators
        //============================================================
        bool operator==(Element_ID lhs, Element_ID rhs);
        bool operator!=(Element_ID lhs, Element_ID rhs);
        bool operator<(Element_ID lhs, Element_ID rhs);
        bool operator>(Element_ID lhs, Element_ID rhs);
        bool operator<=(Element_ID lhs, Element_ID rhs);
        bool operator>=(Element_ID lhs, Element_ID rhs);


        //---------------------------------------------------------------------------
        // Element_ID_Factory
        //---------------------------------------------------------------------------
        class Element_ID_Factory
        {
        public:
            // Typedefs
            //============================================================
            using id_factory_type = Unsigned_Integer_ID_Factory<std::size_t>;

            // Special 6
            //============================================================
            Element_ID_Factory();

            // Interface
            //============================================================
            static Element_ID make_null_id();

            Element_ID issue_id();

            void revoke_id(Element_ID a_id);

        private:
            // Data Members
            //============================================================
            id_factory_type m_factory;
        };

    } // namespace internal
} // namespace saklib


#endif // SAKLIB_INTERNAL_ELEMENT_ID_H
