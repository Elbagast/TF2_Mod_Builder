#ifndef SAKLIB_ELEMENT_DEFINITION_STORAGE_H
#define SAKLIB_ELEMENT_DEFINITION_STORAGE_H

#include "ielement_definition_storage.h"

namespace saklib
{
    namespace local
    {
        /*
        Element_Definition_Storage
        ====================================================================================================
        */
        class Element_Definition_Storage :
                public virtual IElement_Definition_Storage
        {
        public:
            using attribute_storage_type = IElement_Definition_Storage::attribute_storage_type;
            using attribute_definition_storage_type = IElement_Definition_Storage::attribute_definition_storage_type;

            ~Element_Definition_Storage() override;

        protected:
            attribute_storage_type v_make_attributes() const override;
        private:
            attribute_definition_storage_type m_attribute_definitions;
        };

    } // namespace local
} // namespace saklib


#endif // SAKLIB_ELEMENT_DEFINITION_STORAGE_H

