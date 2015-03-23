#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

#include "../types.h"
#include "../command.h"
//#include "../command_history.h"
#include "../elementid.h"
#include "../attributeid.h"
#include "../proxyid.h"
#include "../element.h"
#include "../all_attributes.h"
#include "../element_manager.h"
#include "element_widget_manager.h"


namespace Saklib
{
    class Command_History; // passed in and connected to components that need it.

    namespace Qtlib
    {
        class Outliner_Model;
        /*
        Project_Manager
        ====================================================================================================
        The bit that binds Element management with extended features like Widgets and keeps them all in sync

        What we want is an API that Commands can use to easily set data and have dependent views update.

        ...Alternatively this has a simple API that uses Commands inside it...which way around?...
        */

        class Project_Manager
        {
        public:
            // Special 6
            //============================================================
            explicit Project_Manager(Command_History& command_history);
            ~Project_Manager();

            // NO COPYING
            Project_Manager(Project_Manager const& other) = delete;
            Project_Manager& operator=(Project_Manager const& other) = delete;

            // Interface
            //============================================================

            // Lifetime
            //------------------------------------------------------------
            // Make a new Element and return all info about it
            ElementID make_element(Command_History& command_history, String const& type);
            // Destory an Element and everything associated with it
            void destroy_element(ElementID elementid);

            // Disconnect all Qt classes to prevent double-deletes
            void prepare_to_die();

            // Does this refer to something in this? - rename these to has(blah) ?
            bool is_valid(ElementID elementid) const;
            bool is_valid(AttributeID attributeid) const;
            bool is_valid(ProxyID proxyid) const;

            // Data Access
            //------------------------------------------------------------
            //Element& element(ElementID elementid);
            Element const& element(ElementID elementid) const;

            String const& element_name(ElementID elementid) const;
            String const& element_type(ElementID elementid) const;
            AttributeID element_parent(ElementID elementid) const;

            //Attribute *const attribute(AttributeID attributeid) const;
            //Attribute *const attribute(ElementID elementid, size_type attribute_index) const;
            //Attribute *const attribute(ElementID elementid, String const& attribute_name) const;

            Attribute const*const attribute(AttributeID attributeid) const;
            Attribute const*const attribute(ElementID elementid, size_type attribute_index) const;
            Attribute const*const attribute(ElementID elementid, String const& attribute_name) const;

            String const& attribute_name(AttributeID attributeid) const;
            Type_Enum attribute_type_enum(AttributeID attributeid) const;
            String attribute_type_string(AttributeID attributeid) const;

            /*
            template <typename T>
            Attribute_Type<T> *const attribute_type_cast(AttributeID attributeid) const
            {
                return Saklib::attribute_type_cast<T>(attribute(attributeid));
            }
            template <typename T>
            Attribute_Type<T> *const attribute_type_cast(ElementID elementid, size_type attribute_index) const
            {
                return Saklib::attribute_type_cast<T>(attribute(elementid, attribute_index));
            }
            template <typename T>
            Attribute_Type<T> *const attribute_type_cast(ElementID elementid, String const& attribute_name) const
            {
                return Saklib::attribute_type_cast<T>(attribute(elementid, attribute_name));
            }
            */
            template <typename T>
            Attribute_Type<T> const*const attribute_type_cast(AttributeID attributeid) const
            {
                return Saklib::attribute_type_cast<T>(attribute(attributeid));
            }
            template <typename T>
            Attribute_Type<T> const*const attribute_type_cast(ElementID elementid, size_type attribute_index) const
            {
                return Saklib::attribute_type_cast<T>(attribute(elementid, attribute_index));
            }
            template <typename T>
            Attribute_Type<T> const*const attribute_type_cast(ElementID elementid, String const& attribute_name) const
            {
                return Saklib::attribute_type_cast<T>(attribute(elementid, attribute_name));
            }


            /*
            template <Type_Enum TE>
            Attribute_Type<TypeHolder_st<TE>> *const attribute_enum_cast(AttributeID attributeid) const
            {
                return Saklib::attribute_enum_cast<TE>(attribute(attributeid));
            }
            template <Type_Enum TE>
            Attribute_Type<TypeHolder_st<TE>> *const attribute_enum_cast(ElementID elementid, size_type attribute_index) const
            {
                return Saklib::attribute_enum_cast<TE>(attribute(elementid, attribute_index));
            }
            template <Type_Enum TE>
            Attribute_Type<TypeHolder_st<TE>> *const attribute_enum_cast(ElementID elementid, String const& attribute_name) const
            {
                return Saklib::attribute_enum_cast<TE>(attribute(elementid, attribute_name));
            }
            */
            template <Type_Enum TE>
            Attribute_Type<TypeHolder_st<TE>> const*const attribute_enum_cast(AttributeID attributeid) const
            {
                return Saklib::attribute_enum_cast<TE>(attribute(attributeid));
            }
            template <Type_Enum TE>
            Attribute_Type<TypeHolder_st<TE>> const*const attribute_enum_cast(ElementID elementid, size_type attribute_index) const
            {
                return Saklib::attribute_enum_cast<TE>(attribute(elementid, attribute_index));
            }
            template <Type_Enum TE>
            Attribute_Type<TypeHolder_st<TE>> const*const attribute_enum_cast(ElementID elementid, String const& attribute_name) const
            {
                return Saklib::attribute_enum_cast<TE>(attribute(elementid, attribute_name));
            }

            Element_Widget*const widget(ElementID elementid) const;
            Element_Widget*const widget(ProxyID proxyid) const;


            // Convert ID Types
            //------------------------------------------------------------
            AttributeID attributeid(ElementID elementid, String const& attribute_name) const;

            // Flat Access
            //------------------------------------------------------------
            Vector_ElementID all_elementids() const;
            Vector_ElementID root_elementids() const;

            // Model Interface
            //============================================================
            // So that views can use it
            Outliner_Model*const outliner_model() const;

            // What are this item's children?
            Vector_AttributeID outliner_children(ElementID elementid) const;
            Vector_ElementID outliner_children(AttributeID attributeid) const;

            // What item is the child at row?
            AttributeID outliner_child_at_row(ElementID elementid, int row) const;
            ElementID outliner_child_at_row(AttributeID attributeid, int row) const;

            // How many rows does this item have?
            int outliner_row_count_root() const;
            int outliner_row_count(ElementID elementid) const;
            int outliner_row_count(AttributeID attributeid) const;

            // What is the parent of this item?
            AttributeID parent_of(ElementID elementid) const;
            ElementID parent_of(AttributeID attributeid) const; // duh

            // What row is this in its parent as far as the model is concerned?
            int outliner_row_in_parent(ElementID elementid) const;
            int outliner_row_in_parent(AttributeID attributeid) const;

            // Data Setters
            //============================================================
            // You must only set data though these in order to keep everything in sync

            void set_element_name(ElementID elementid, String const& value);

            template <typename T>
            void set_attribute_type(AttributeID attributeid, T const& value)
            {
                if(attributeid.is_valid())
                {
                    m_data_manager.element(attributeid.elementid()).attribute_type_cast<T>(attributeid.index())->set(value);
                    update_widget(attributeid);
                    update_model(attributeid);
                }
            }

            template <Type_Enum TE>
            void set_attribute_enum(AttributeID attributeid, TypeHolder_st<TE> const& value)
            {
                if(attributeid.is_valid())
                {
                    m_data_manager.element(attributeid.elementid()).attribute_enum_cast<TE>(attributeid.index())->set(value);
                    update_widget(attributeid);
                    update_model(attributeid);
                }
            }


        private:
            // Internal
            //============================================================
            void update_widget(ElementID elementid);
            void update_widget(AttributeID attributeid);

            void update_model(ElementID elementid);
            void update_model(AttributeID attributeid);

            // Data Members
            //============================================================
            Element_Manager m_data_manager;             // actual data
            Element_Widget_Manager m_widget_manager;    // widgets that the user edits data through
            Uptr<Outliner_Model> m_outliner_model;                  // model that references data via Proxy objects
        };
    } // namespace Qtlib
} // namespace Saklib
#endif // PROJECT_MANAGER_H
