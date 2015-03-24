#ifndef ELEMENT_WIDGET_MANAGER_H
#define ELEMENT_WIDGET_MANAGER_H

#include "../types.h"
#include "../element.h"
#include "../elementid.h"
#include "../attributeid.h"
#include <map>

namespace Saklib
{
    namespace Qtlib
    {
        class Project_Manager;
        class Element_Widget;

        /*
        Element_Widget_Manager
        ====================================================================================================
        Simple manager for Element_Widgets via ElementIDs. It's really just map with a simplified interface.
        This class does not use Element_Manager but you must supply it so that it can construct
        Element_Widgets which do.

        This is really a class that you build in its final place.

        Since widgets exist at the behest of the gui and get parented/reparented by other widgets this might
        be better off with a different ownership strategy...
        */
        class Element_Widget_Manager // public QTabWidget?
        {
        public:
            // Special 6
            //============================================================
            Element_Widget_Manager();
            ~Element_Widget_Manager();

            // NO COPYING
            Element_Widget_Manager(Element_Widget_Manager const& other) = delete;
            Element_Widget_Manager& operator=(Element_Widget_Manager const& other) = delete;

            // Implict default move
            //Element_Widget_Manager(Element_Widget_Manager && other) = default;
            //Element_Widget_Manager& operator=(Element_Widget_Manager && other) = default;

            // Interface
            //============================================================
            // Build a new Element_Widget for a given ElementID and return it.
            // This function forwards all these arguments to the Element_Widget constructor as only
            // they will need to do anything with them.
            Element_Widget*const make_widget(Project_Manager& project_manager, ElementID elementid);
            // Destory the Element_Widget associated with this ElementID
            void destroy_widget(ElementID elementid);

            // Is this ElementID valid for this?
            bool has_widget(ElementID elementid) const;

            // Access the pre-exisiting Element_Widget associated with this ElementID
            Element_Widget*const widget(ElementID elementid) const;
            //Element_Widget const*const widget(ElementID elementid) const;

            // Refresh the data in the widget relevent to this id
            void refresh_widget_data(ElementID elementid);
            void refresh_widget_data(AttributeID attributeid);

            // Auxillary access
            Vector_ElementID all_elementids() const;

            void nullify_all_parents();

        private:
            // Member Data
            //============================================================
            using map_type = std::map < ElementID, Uptr<Element_Widget> >;
            using iterator = map_type::iterator;
            using const_iterator = map_type::const_iterator;

            map_type m_map;
        };
    } // namespace Qtlib
} //namespace Saklib

#endif // ELEMENT_WIDGET_MANAGER_H
