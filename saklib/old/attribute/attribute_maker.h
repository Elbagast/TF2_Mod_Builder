#ifndef SAKLIB_ATTRIBUTE_MAKER_H
#define SAKLIB_ATTRIBUTE_MAKER_H

#include "iattribute_maker.h"
#include "iattribute_constraint.h"
#include "attribute.h"

namespace saklib
{
    class IObject_Name_R;

    namespace local
    {
        /*
        Attribute_Maker<T>
        ====================================================================================================
        Implementation for a static typeid for T
        */
        template <typename T>
        class Attribute_Maker :
                public virtual IAttribute_Maker
        {
        public:
            Attribute_Maker(IObject_Name_R const& ar_name, IAttribute_Constraint_R<T> const& ar_constraint):
                IAttribute_Maker(),
                mr_name(ar_name),
                mr_constraint(ar_constraint)
            {}

            ~Attribute_Maker() override = default;

        protected:
            std::unique_ptr<IAttribute_Base> v_make_attribute() const override
            {
                std::unique_ptr<IAttribute_Base> result{ new Attribute<T>(mr_name, mr_constraint) };
                return result;
            }
        private:
            IObject_Name_R const& mr_name;
            IAttribute_Constraint_R<T> const& mr_constraint;
        };
    } // namespace local
} // namespace saklib

#endif // SAKLIB_ATTRIBUTE_MAKER_H

