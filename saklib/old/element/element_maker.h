#ifndef SAKLIB_ELEMENT_MAKER_H
#define SAKLIB_ELEMENT_MAKER_H

#include "ielement_maker.h"
#include "element.h"
#include "../object/iobject_pointer_storage.h"
#include "../attribute/iattribute_definition_base.h"

namespace saklib
{
    class IObject_Name_R;

    namespace local
    {
        /*
        Element_Maker
        ====================================================================================================
        */
        class Element_Maker :
                public virtual IElement_Maker
        {
        public:
            Element_Maker(IObject_Type_R const& ar_type, IObject_Pointer_Storage_R<IAttribute_Definition_Base> const& ar_storage):
                IElement_Maker(),
                mr_type(ar_type),
                mr_storage(ar_storage)
            {}

            ~Element_Maker() override = default;

        protected:
            std::unique_ptr<IElement> v_make_element(String const& ar_name) const override
            {
                std::vector<std::unique_ptr<IAttribute_Base>> made_attributes{};
                made_attributes.reserve(mr_storage.size());
                for(size_type index = 0, end = mr_storage.size(); index != end; ++index)
                {
                    made_attributes.push_back(mr_storage.cat(index)->make_attribute());
                }
                std::unique_ptr<IElement> result{ new Element(mr_type, ar_name, std::move(made_attributes)) };
                return result;
            }
        private:
            IObject_Type_R const& mr_type;
            IObject_Pointer_Storage_R<IAttribute_Definition_Base> const& mr_storage;
        };
    } // namespace local
} // namespace saklib

#endif // SAKLIB_ELEMENT_MAKER_H

