#ifndef ELEMENT_WIDGET_H
#define ELEMENT_WIDGET_H

#include "../types.h"
#include "../elementid.h"
#include "../attributeid.h"
#include "../attribute_type.h"
#include "quptr.h"
#include <QWidget>

class QLabel;
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QFormLayout;

namespace Saklib
{
    class Project_Manager;
    class Element_Manager;
    class Element;

    namespace Qtlib
    {
        class Attribute_Editor;
        class Project_Widget;
        /*
        Element_Widget
        ====================================================================================================
        Provide editor access through a Grid arrangement of Attribute data.
        */
        class Element_Widget :
                public QWidget
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            Element_Widget(Project_Widget*const project_widget, ElementID elementid);
            ~Element_Widget() override;

            // NO COPYING
            Element_Widget(Element_Widget const& other) = delete;
            Element_Widget& operator=(Element_Widget const& other) = delete;

            // Implict default move

            // Interface
            //============================================================
            ElementID elementid() const                     { return m_elementid; }

            // Update the data displayed by this widget and its children
            void refresh_data();
            void refresh_data(size_type attribute_index);

            // Change the Element name?
            // Issue edit commands...
            // Subclass Attribute Editors and have them do this themselves, or capture their signals?

        private:
            // Data Members
            //============================================================
            Project_Widget*const mp_project_widget; // Commands reference this so that data is updated properly
            ElementID const m_elementid;         // Reference to the Element being edited
            AttributeID m_parentid;

            // Widgets
            QUptr<QHBoxLayout> m_self_header_layout;
            QUptr<QLabel> m_element_type_label;
            QUptr<QLabel> m_element_name_label;
            QUptr<QLabel> m_element_id_label;

            QUptr<QLabel> m_parent_id_label;  // Label for the parent AttributeID

            //Vector<Uptr<QLabel>> m_attribute_names;
            //Vector<Uptr<QLabel>> m_attribute_types;
            Vector<QUptr<QHBoxLayout>> m_attribute_layouts;
            Vector<QUptr<Attribute_Editor>> m_attribute_editors;

            //Uptr<QGridLayout> m_layout; // Layout for this
            QUptr<QVBoxLayout> m_layout; // Layout for this
            QUptr<QHBoxLayout> m_parent_header_layout;
            QUptr<QFormLayout> m_attribute_layout; // Layout for Attributes
        };

    } // namespace Qtlib
}  // namespace Saklib

#endif // ELEMENT_WIDGET_H
