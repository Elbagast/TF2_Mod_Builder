#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

#include "../types.h"
#include "../command.h"
#include "../command_history.h"
#include "../command_attribute.h"
#include "../elementid.h"
#include "../attributeid.h"
#include "../proxyid.h"
#include "../element.h"
#include "../all_attributes.h"
#include "../element_manager.h"
#include "element_widget_manager.h"


namespace Saklib
{

    namespace Qtlib
    {
        class Outliner_Model;
        class Project_Widget;

        class PMC_Element_Set_Name;
        template <typename T>
        class PMC_Attribute_Set_Value;
        /*
        Project_Manager
        ====================================================================================================
        The bit that binds Element management with extended features like Widgets and keeps them all in sync

        Commands are managed inside this class.

        Should this actually be the widget class rather than talk to it? - I guess this'll depend on what
        happens when we start messing with switching editors to focus on different Elements...
        */

        class Project_Manager
        {
        public:
            // Special 6
            //============================================================
            explicit Project_Manager(Project_Widget* widget = nullptr);
            ~Project_Manager();

            // NO COPYING
            Project_Manager(Project_Manager const& other) = delete;
            Project_Manager& operator=(Project_Manager const& other) = delete;

            // Interface
            //============================================================

            // Lifetime
            //------------------------------------------------------------
            // Make a new Element and return all info about it
            ElementID make_element(String const& type);
            // Destory an Element and everything associated with it
            void destroy_element(ElementID elementid);

            // Disconnect all Qt classes to prevent double-deletes
            void prepare_to_die();

            // Does this refer to something in this? - rename these to has(blah) ?
            bool is_valid(ElementID elementid) const;
            bool is_valid(AttributeID attributeid) const;
            bool is_valid(ProxyID proxyid) const;

            // Data Access - read only
            //------------------------------------------------------------
            Element const& element(ElementID elementid) const; // return a pointer?

            String const& element_name(ElementID elementid) const;
            String const& element_type(ElementID elementid) const;
            AttributeID element_parent(ElementID elementid) const;

            Attribute const*const attribute(AttributeID attributeid) const;
            Attribute const*const attribute(ElementID elementid, size_type attribute_index) const;
            Attribute const*const attribute(ElementID elementid, String const& attribute_name) const;

            String const& attribute_name(AttributeID attributeid) const;
            Type_Enum attribute_type_enum(AttributeID attributeid) const;
            String attribute_type_string(AttributeID attributeid) const;

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

            // Data Setters - the only part with write access
            //============================================================
            // These functions set the data without question, and tell the model and widget to update.

            void set_element_name(ElementID elementid, String const& value);

            template <typename T>
            void set_attribute_value_type(AttributeID attributeid, T const& value)
            {
                assert(attributeid.is_valid());
                assert(this->attribute_type_enum(attributeid) == Type_Traits<T>::type_enum());
                assert(this->attribute_type_cast<T>(attributeid)->value() != value);
                m_data_manager.element(attributeid.elementid()).attribute_type_cast<T>(attributeid.index())->set_value(value);
                update_widget(attributeid);
                update_model(attributeid);
            }

            template <Type_Enum TE>
            void set_attribute_value_enum(AttributeID attributeid, TypeHolder_st<TE> const& value)
            {
                set_attribute_value_type<TypeHolder_st<TE> >(attributeid, value);
            }

            // Commands - indirect write access
            //============================================================
            // To support undoing edits use these functions to edit data from the outliner/widgets.

            bool undoable_set_element_name(ElementID elementid, String const& value);

            template <typename T>
            bool undoable_set_attribute_value_type(AttributeID attributeid, T const& value)
            {
                // if conditions are right to issue a command
                if(attributeid.is_valid()
                   && this->attribute_type_enum(attributeid) == Type_Traits<T>::type_enum()
                   && this->attribute_type_cast<T>(attributeid)->value() != value)
                {
                    // do it. The command should call the update_... function(s) when it is executed/unexecuted
                    m_command_history.emplace_execute<PMC_Attribute_Set_Value<T>>(*this, attributeid, value);
                    command_history_changed();
                    return true;
                }
                else
                {
                    return false;
                }
            }

            template <Type_Enum TE>
            bool undoable_set_attribute_value_enum(AttributeID attributeid, TypeHolder_st<TE> const& value)
            {
                return undoable_set_attribute_value_type<TypeHolder_st<TE> >(attributeid, value);
            }

            // Command History
            //============================================================
            // Provide limited access to the underlying history
            //Command_History const& command_history() const;

            // Will calling undo do anything?
            bool can_undo() const;
            // Will calling redo do anything?
            bool can_redo() const;

            // How many times can undo() be called()?
            size_type undo_count() const;
            // How many times can redo() be called()?
            size_type redo_count() const;

            // Call unexecute() in the current command and step back one in the history.
            void undo();
            // Step forward one in the history and call execute() on that command.
            void redo();

            // Clear all stored commands.
            void clear_history();

            // Call whenever commands are issued or called
            void command_history_changed();


            // Widget
            //============================================================
            // this communicates with the widget to tell it when things in it need to change, like when
            // an editor is requested....hmmm

            Project_Widget*const widget() const;
            void set_widget(Project_Widget* widget);
            bool has_widget() const;


        private:
            // Internal
            //============================================================
            void update_widget(ElementID elementid);
            void update_widget(AttributeID attributeid);

            void update_model(ElementID elementid);
            void update_model(AttributeID attributeid);

            // Data Members
            //============================================================
            Command_History m_command_history;          // editing history
            Element_Manager m_data_manager;             // actual data
            Element_Widget_Manager m_widget_manager;    // widgets that the user edits data through
            Uptr<Outliner_Model> m_outliner_model;      // model that references data via Proxy objects
            Project_Widget* mp_widget;                  // widget to inform of data changes directly
        };


        /*
        PMC_Element_Set_Name
        ====================================================================================================
        Project_Manager Commands need to be in this header to avoid a circular dependency with the template.
        */
        class PMC_Element_Set_Name:
                public Command
        {
        public:
            PMC_Element_Set_Name(Project_Manager& project_mananger, ElementID elementid, String const& name):
                Command(),
                mr_project_mananger(project_mananger),
                m_elementid(elementid),
                m_old_name(mr_project_mananger.element_name(elementid)),
                m_new_name(name)
            {
                assert(mr_project_mananger.is_valid(elementid));
            }
            ~PMC_Element_Set_Name() override = default;

        protected:
            void v_execute() override
            {
                mr_project_mananger.set_element_name(m_elementid, m_new_name);
            }
            void v_unexecute() override
            {
                mr_project_mananger.set_element_name(m_elementid, m_old_name);
            }
        private:
            Project_Manager& mr_project_mananger;
            ElementID m_elementid;
            String m_old_name;
            String m_new_name;
        };

        /*
        PMC_Attribute_Set_Value<T>
        ====================================================================================================
        Project_Manager Commands need to be in this header to avoid a circular dependency with the template.
        */
        template <typename T>
        class PMC_Attribute_Set_Value:
                public Command
        {
        public:
            PMC_Attribute_Set_Value(Project_Manager& project_mananger, AttributeID attributeid, T const& value):
                Command(),
                mr_project_mananger(project_mananger),
                m_attributeid(attributeid),
                m_old_value(mr_project_mananger.attribute_type_cast<T>(attributeid)->value()),
                m_new_value(value)
            {
                assert(mr_project_mananger.is_valid(attributeid));
            }
            ~PMC_Attribute_Set_Value() override = default;

        protected:
            void v_execute() override
            {
                mr_project_mananger.set_attribute_value_type<T>(m_attributeid, m_new_value);
            }
            void v_unexecute() override
            {
                mr_project_mananger.set_attribute_value_type<T>(m_attributeid, m_old_value);
            }
        private:
            Project_Manager& mr_project_mananger;
            AttributeID m_attributeid;
            T m_old_value;
            T m_new_value;
        };



    } // namespace Qtlib
} // namespace Saklib
#endif // PROJECT_MANAGER_H
