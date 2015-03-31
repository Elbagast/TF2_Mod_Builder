#ifndef ATTRIBUTE_EDITOR_VECTOR_TYPE_H
#define ATTRIBUTE_EDITOR_VECTOR_TYPE_H

#include "attribute_editor_vector.h"
#include "project_widget.h"

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
                project_widget()->undoable_attribute_vector_push_back<T>(attributeid(), T());
            }
            void slot_insert(size_type index) override
            {
                //project_widget()->undoable_attribute_vector_insert_at<T>(attributeid(), index, T());
            }
        };


    } // namespace Qtlib
} // namespace Saklib

#endif // ATTRIBUTE_EDITOR_VECTOR_TYPE_H

