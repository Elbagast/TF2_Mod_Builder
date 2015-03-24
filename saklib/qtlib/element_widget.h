#ifndef ELEMENT_WIDGET_H
#define ELEMENT_WIDGET_H

#include "../types.h"
#include "../elementid.h"
#include <QWidget>

class QLabel;
class QGridLayout;

namespace Saklib
{
    class Element_Manager;
    class Element;

    namespace Qtlib
    {
        class Attribute_Editor;
        class Project_Manager;
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
            Element_Widget(Project_Manager& project_manager, ElementID elementid);
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
            Project_Manager& mr_project_manager; // Commands reference this so that data is updated properly
            ElementID const m_elementid;         // Reference to the Element being edited

            // Widgets
            Uptr<QLabel> m_element_name_label;  // Label for the Element name - any editing done through this so it'd need its own class
            Uptr<QLabel> m_element_type_label;  // Label for the Element type

            Vector<Uptr<QLabel>> m_attribute_names;
            Vector<Uptr<QLabel>> m_attribute_types;
            Vector<Uptr<Attribute_Editor>> m_attribute_editors;

            Uptr<QGridLayout> m_layout; // Layout for this
        };

    } // namespace Qtlib
}  // namespace Saklib

#endif // ELEMENT_WIDGET_H
