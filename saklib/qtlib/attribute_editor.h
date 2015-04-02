#ifndef ATTRIBUTE_EDITOR_H
#define ATTRIBUTE_EDITOR_H

#include "../attributeid.h"
#include "project_widget.h"
#include "../project_manager.h"

#include <QWidget>

class QLabel;
class QHBoxLayout;

namespace Saklib
{
    class Project_Manager;

    namespace Qtlib
    {
        class Project_Widget;

        /*
        Attribute_Editor
        ====================================================================================================
        To avoid the need to multiple classes, an Attribute_Editor knows whether or not it is editing data
        in an Attribute_Type<T>, or a component in an Attribute_Type<Vector<T>>. It knows this from whether
        or not an index vale is supplied in the constructor.
        */
        class Attribute_Editor :
                public QWidget
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            Attribute_Editor(Project_Widget*const project_widget, AttributeID attributeid, size_type vector_index, QWidget* parent = nullptr);
            ~Attribute_Editor() override;

            void refresh_data()                         { v_refresh_data(); }
            Project_Widget*const project_widget() const { return mp_project_widget; }
            AttributeID attributeid() const             { return m_attributeid; }
            Type_Enum attribute_type_enum() const       { return m_attribute_type; }
            bool is_vector_component() const            { return m_is_vector_component; }
            size_type vector_index() const              { assert(m_is_vector_component); return m_vector_index; }

            template <typename T>
            T const& attribute_value()
            {
                if (m_is_vector_component)
                    return mp_project_widget->project_manager().attribute_type_cast<Vector<T>>(m_attributeid)->at(m_vector_index);
                else
                    return mp_project_widget->project_manager().attribute_type_cast<T>(m_attributeid)->value();
            }

        protected:
            // Require subclasses to match with the data they represent
            virtual void v_refresh_data() = 0;

        private:
            Project_Widget*const mp_project_widget;
            AttributeID m_attributeid;
            Type_Enum m_attribute_type;
            size_type m_vector_index;
            bool m_is_vector_component;
        };

        class Attribute_Editor_Dummy :
                public Attribute_Editor
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Attribute_Editor_Dummy(Project_Widget*const project_widget, AttributeID attributeid, QWidget* parent = nullptr);
            ~Attribute_Editor_Dummy() override;
        protected:
            void v_refresh_data() override {}
        private:
            Uptr<QLabel> m_label;
            Uptr<QHBoxLayout> m_layout;
        };

        // Function with a typeswitch
        Uptr<Attribute_Editor> make_Attribute_Editor(Project_Widget*const project_widget, AttributeID attributeid);

        // Function with a typeswitch
        Uptr<Attribute_Editor> make_Attribute_Editor(Project_Widget*const project_widget, AttributeID attributeid, size_type vector_index);

    } // namespace Qtlib
} // namespace Saklib
#endif // ATTRIBUTE_EDITOR_H
