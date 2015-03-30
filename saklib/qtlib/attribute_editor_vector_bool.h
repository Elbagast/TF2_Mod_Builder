#ifndef ATTRIBUTE_EDITOR_VECTOR_BOOL_H
#define ATTRIBUTE_EDITOR_VECTOR_BOOL_H

#include "attribute_editor_vector.h"
#include "../types.h"

namespace Saklib
{
    namespace Qtlib
    {
        class Attribute_Editor_Vector_Bool:
                public Attribute_Editor_Vector
        {
        public:
            using value_type = Bool;
            using stored_type = Vector<value_type>;

            // Special 6
            //============================================================
            Attribute_Editor_Vector_Bool(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Vector_Bool() override;

        protected:
            // make an appropriately typed component widget
            Uptr<Attribute_Editor> make_component_widget(size_type index) const override;

            void slot_append() override;
        };

    } // namespace Qtlib
} // namespace Saklib

#endif // ATTRIBUTE_EDITOR_VECTOR_BOOL_H
