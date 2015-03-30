#ifndef ATTRIBUTE_EDITOR_VECTOR_INT_H
#define ATTRIBUTE_EDITOR_VECTOR_INT_H

#include "attribute_editor_vector.h"
#include "../types.h"

namespace Saklib
{
    namespace Qtlib
    {
        class Attribute_Editor_Vector_Int:
                public Attribute_Editor_Vector
        {
        public:
            using value_type = Int;
            using stored_type = Vector<value_type>;

            // Special 6
            //============================================================
            Attribute_Editor_Vector_Int(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Vector_Int() override;

        protected:
            // make an appropriately typed component widget
            Uptr<Attribute_Editor> make_component_widget(size_type index) const override;

            void slot_append() override;
        };

    } // namespace Qtlib
} // namespace Saklib


#endif // ATTRIBUTE_EDITOR_VECTOR_INT_H
