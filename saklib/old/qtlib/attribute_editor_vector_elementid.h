#ifndef ATTRIBUTE_EDITOR_VECTOR_ELEMENTID_H
#define ATTRIBUTE_EDITOR_VECTOR_ELEMENTID_H

#include "attribute_editor_vector_type.h"
#include "../types.h"

namespace saklib
{
    namespace Qtlib
    {
        /*
        Attribute_Editor_Vector_Type<ElementID>
        ====================================================================================================
        Template specialisation so that the user is prompted to select an Element type to create whenever
        one is added to the vector.
        */
        template<>
        class Attribute_Editor_Vector_Type<ElementID> :
                public Attribute_Editor_Vector
        {
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Vector_Type(Project_Widget* project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Vector_Type() override;

        protected:
            void slot_append() override;
            void slot_insert_at(size_type index) override;
            void slot_remove_at(size_type index) override;
            void slot_remove_last() override;
            void slot_swap(size_type index, size_type other_index) override;
            void slot_move_up(size_type index) override;
            void slot_move_down(size_type index) override;
            void slot_clear() override;
        };

    } // namespace Qtlib
} // namespace saklib

#endif // ATTRIBUTE_EDITOR_VECTOR_ELEMENTID_H
