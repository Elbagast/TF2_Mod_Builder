#ifndef SAKLIB_ELEMENT_ATTRIBUTE_STORAGE_H
#define SAKLIB_ELEMENT_ATTRIBUTE_STORAGE_H

#include "ielement_attribute_storage.h"

namespace saklib
{
    class IAttribute_Base;
    namespace local
    {
        /*
        Element_Attribute_Storage
        ====================================================================================================
        */
        class Element_Attribute_Storage :
                public virtual IElement_Attribute_Storage
        {
        public:
            using storage_type = std::vector<std::unique_ptr<IAttribute_Base>>;

            // Special 6
            //============================================================
            Element_Attribute_Storage(storage_type& a_attributes);
            ~Element_Attribute_Storage() override;

        protected:
            // Virtuals
            //============================================================
            size_type v_attribute_count() const override;
            size_type v_attribute_count_of_type(Type_Enum type) const override;

            bool v_has_attribute(String const& name) const override;
            bool v_has_attribute(size_type index) const override;

            IAttribute_Base* v_attribute(String const& name) override;
            IAttribute_Base* v_attribute(size_type index) override;

            IAttribute_Base const* v_cattribute(String const& name) const override;
            IAttribute_Base const* v_cattribute(size_type index) const override;

            std::vector<String> v_attribute_names() const override;
        private:
            storage_type m_attributes;
        };
    } // namespace local
} // namespace saklib

#endif // SAKLIB_ELEMENT_ATTRIBUTE_STORAGE_H
