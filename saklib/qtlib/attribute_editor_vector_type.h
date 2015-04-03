#ifndef ATTRIBUTE_EDITOR_VECTOR_TYPE_H
#define ATTRIBUTE_EDITOR_VECTOR_TYPE_H

#include "attribute_editor_vector.h"
#include "project_widget.h"
#include "../project_manager.h"

namespace Saklib
{
    namespace Qtlib
    {
        /*
        Attribute_Editor_Vector_Type<T>
        ====================================================================================================
        Subclass to supply virtual versions of actions which are type dependent. By default new items added
        to the vector are default-constructed.
        */

        template <typename T>
        class Attribute_Editor_Vector_Type:
                public Attribute_Editor_Vector
        {
        public:
            Attribute_Editor_Vector_Type(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr):
                Attribute_Editor_Vector(project_widget, attributeid, parent)
            {}
            ~Attribute_Editor_Vector_Type() override = default;
        protected:
            void slot_append() override
            {
                project_widget()->project_manager().undoable_attribute_vector_push_back<T>(attributeid(), T());
            }
            void slot_insert_at(size_type index) override
            {
                project_widget()->project_manager().undoable_attribute_vector_insert_at<T>(attributeid(), index, T());
            }
            void slot_remove_at(size_type index) override
            {
                project_widget()->project_manager().undoable_attribute_vector_remove_at<T>(attributeid(), index);
            }
            void slot_remove_last() override
            {
                project_widget()->project_manager().undoable_attribute_vector_pop_back<T>(attributeid());
            }
            void slot_swap(size_type index, size_type other_index) override
            {
                project_widget()->project_manager().undoable_attribute_vector_swap_at<T>(attributeid(), index, other_index);
            }
            void slot_move_up(size_type index) override
            {
                auto size = attribute_vector_size();
                if (size > 1 && index < size && index > 0)
                    project_widget()->project_manager().undoable_attribute_vector_swap_at<T>(attributeid(), index, index - 1);
            }
            void slot_move_down(size_type index) override
            {
                auto size = attribute_vector_size();
                if (size > 1 && index < size && index + 1 < size)
                    project_widget()->project_manager().undoable_attribute_vector_swap_at<T>(attributeid(), index, index + 1);
            }
            void slot_clear() override
            {
                project_widget()->project_manager().undoable_attribute_vector_clear<T>(attributeid());
            }
        };


    } // namespace Qtlib
} // namespace Saklib

#endif // ATTRIBUTE_EDITOR_VECTOR_TYPE_H

