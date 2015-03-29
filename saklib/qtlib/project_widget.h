#ifndef Project_Widget_H
#define Project_Widget_H

#include "../types.h"
#include "../all_attributes.h"
#include "../element_manager.h"
#include "../command_history.h"

#include <QWidget>

class QHBoxLayout;
class QTabWidget;
class QScrollArea;

namespace Saklib
{
    namespace Qtlib
    {
        class Element_Widget;
        class Outliner_Model;
        class Outliner_Delegate;
        class Outliner_Treeview;

        /*
        Project_Widget
        ====================================================================================================
        This widget is the root widget of an entire project and forms the central widget of the window
        class that holds it. When something happens that needs to update the window (e.g. enable/disable
        menu actions) it emits signals that will already have been connected as appropriate.
        */
        class Project_Widget:
                public QWidget
        {
            Q_OBJECT
        public:
            // Special 6
            //============================================================
            explicit Project_Widget(Path const& filePath, QWidget* parent = nullptr);
            ~Project_Widget() override;

            // NO COPYING
            Project_Widget(Project_Widget const& other) = delete;
            Project_Widget& operator=(Project_Widget const& other) = delete;

            // Implicit default move
            //Project_Widget(Project_Widget && other) = default;
            //Project_Widget& operator=(Project_Widget && other) = default;

            // Interface
            //============================================================

            // Lifetime
            //------------------------------------------------------------
            // Make a new Element and return all info about it
            ElementID make_element(String const& type);
            // Destory an Element and everything associated with it
            void destroy_element(ElementID elementid);

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

            // if the attribute is a vector, return it's size, otherwise 0
            size_type attribute_vector_size(AttributeID attributeid) const;
            bool attribute_vector_empty(AttributeID attributeid) const;

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

            // Convert ID Types
            //------------------------------------------------------------
            AttributeID attributeid(ElementID elementid, String const& attribute_name) const;

            // Flat Access
            //------------------------------------------------------------
            Vector_ElementID all_elementids() const;
            Vector_ElementID root_elementids() const;

            // Model Interface
            //------------------------------------------------------------
            // Functions that provide data to the outliner model

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
            //------------------------------------------------------------
            // These functions set the data without question, and tell the model and widget to update.

            void element_set_name(ElementID elementid, String const& value);

            template <typename T>
            void attribute_set_value(AttributeID attributeid, T const& value)
            {
                // god dammit have to specificy the template right now, but it works
                attribute_function<T, decltype(&Attribute_Type<T>::set_value), T>(attributeid, &Attribute_Type<T>::set_value, value);
            }
            template <>
            void attribute_set_value<ElementID>(AttributeID attributeid, ElementID const& value);


            // vector functions....all of them.........

            template <typename T>
            void attribute_vector_clear(AttributeID attributeid)
            {
                attribute_function<T, decltype(&Attribute_Type<Vector<T>>::clear)>(attributeid, &Attribute_Type<Vector<T>>::clear);
            }
            template <>
            void attribute_vector_clear<ElementID>(AttributeID attributeid);

            template <typename T>
            void attribute_vector_swap_at(AttributeID attributeid, size_type index, size_type other_index)
            {
                attribute_function<T, decltype(&Attribute_Type<Vector<T>>::swap_at), size_type, size_type>(attributeid, &Attribute_Type<Vector<T>>::swap_at, index, other_index);
            }
            template <>
            void attribute_vector_swap_at<ElementID>(AttributeID attributeid, size_type index, size_type other_index);

            template <typename T>
            void attribute_vector_set_at(AttributeID attributeid, size_type index, T const& value)
            {
                attribute_function<T, decltype(&Attribute_Type<Vector<T>>::set_at), size_type, T>(attributeid, &Attribute_Type<Vector<T>>::set_at, index, value);
            }
            template <>
            void attribute_vector_set_at<ElementID>(AttributeID attributeid, size_type index, ElementID const& value);

            template <typename T>
            void attribute_vector_set_front(AttributeID attributeid, T const& value)
            {
                attribute_function<T, decltype(&Attribute_Type<Vector<T>>::set_front), T>(attributeid, &Attribute_Type<Vector<T>>::set_front);
            }
            template <>
            void attribute_vector_set_front<ElementID>(AttributeID attributeid, ElementID const& value);

            template <typename T>
            void attribute_vector_set_back(AttributeID attributeid, T const& value)
            {
                attribute_function<T, decltype(&Attribute_Type<Vector<T>>::set_back), T>(attributeid, &Attribute_Type<Vector<T>>::set_back, value);
            }
            template <>
            void attribute_vector_set_back<ElementID>(AttributeID attributeid, ElementID const& value);

            template <typename T>
            void attribute_vector_push_front(AttributeID attributeid, T const& value)
            {
                attribute_function<T, decltype(&Attribute_Type<Vector<T>>::push_front), T>(attributeid, &Attribute_Type<Vector<T>>::push_front, value);
            }
            template <>
            void attribute_vector_push_front<ElementID>(AttributeID attributeid, ElementID const& value);

            template <typename T>
            void attribute_vector_push_back(AttributeID attributeid, T const& value)
            {
                attribute_function<T, decltype(&Attribute_Type<Vector<T>>::push_back), T>(attributeid, &Attribute_Type<Vector<T>>::push_back, value);
            }
            void attribute_vector_push_back(AttributeID attributeid, ElementID const& value);

            template <typename T>
            void attribute_vector_pop_back(AttributeID attributeid)
            {
                attribute_function<T, decltype(&Attribute_Type<Vector<T>>::pop_back)>(attributeid, &Attribute_Type<Vector<T>>::pop_back);
            }
            void attribute_vector_pop_back_ElementID(AttributeID attributeid);

            template <typename T>
            void attribute_vector_pop_front(AttributeID attributeid)
            {
                attribute_function<T, decltype(&Attribute_Type<Vector<T>>::pop_front)>(attributeid, &Attribute_Type<Vector<T>>::pop_front);
            }
            template <>
            void attribute_vector_pop_front<ElementID>(AttributeID attributeid);

            // Commands - indirect write access
            //------------------------------------------------------------
            // To support undoing edits use these functions to edit data from the outliner/widgets.

            bool undoable_element_set_name(ElementID elementid, String const& value);

            template <typename T>
            bool undoable_attribute_set_value(AttributeID attributeid, T const& value)
            {
                // if conditions are right to issue a command
                if(attributeid.is_valid()
                   && this->attribute_type_enum(attributeid) == Type_Traits<T>::type_enum()
                   && this->attribute_type_cast<T>(attributeid)->value() != value)
                {
                    // do it. The command should call the update_... function(s) when it is executed/unexecuted
                    m_command_history.emplace_execute<PWC_Attribute_Set_Value<T>>(this, attributeid, value);
                    command_history_changed();
                    return true;
                }
                else
                {
                    return false;
                }
            }

            template <typename T>
            bool undoable_attribute_vector_set_value_at(AttributeID attributeid, size_type index, T const& value)
            {
                if(attributeid.is_valid()
                   && this->attribute_type_enum(attributeid) == Type_Traits<Vector<T>>::type_enum()
                   && this->attribute_type_cast<Vector<T>>(attributeid)->at(index) != value)
                {
                    // do it. The command should call the update_... function(s) when it is executed/unexecuted
                    m_command_history.emplace_execute<PWC_Attribute_Vector_Set_Value_At<T>>(this, attributeid, index, value);
                    command_history_changed();
                    return true;
                }
                else
                {
                    return false;
                }
            }


            template <typename T>
            bool undoable_attribute_vector_push_back(AttributeID attributeid, T const& value)
            {
                // if conditions are right to issue a command
                if(attributeid.is_valid()
                   && this->attribute_type_enum(attributeid) == Type_Traits<Vector<T>>::type_enum() )
                {
                    // do it. The command should call the update_... function(s) when it is executed/unexecuted
                    m_command_history.emplace_execute<PWC_Attribute_Vector_Push_Back<T>>(this, attributeid, value);
                    command_history_changed();
                    return true;
                }
                else
                {
                    return false;
                }
            }

            // Command History
            //------------------------------------------------------------
            // Provide access to the command history whilst keeping data representations updated (if necessary)

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


            // Element Widget
            //------------------------------------------------------------
            // Alter the Element currently being edited

            // Make an Element_Widget for this ElementID
            void open_editor(ElementID elementid);

            // The ElementID of the Element that is currently being edited
            ElementID currently_open_elementid() const;


            // Hmmmm these might be better handled elsewhere...

            // Overall Project
            //------------------------------------------------------------
            ElementID project_elementid() const;
            Path const& project_filepath() const;
            void set_project_filepath(Path const& filepath);

            void save() const;
            void save_as(Path const& filepath);

            // Signals
            //============================================================
        signals:
            // Emitted whenever data is changed and the changes were not saved
            void signal_unsaved_edits(bool state) const;

            // Emitted whenever a Command_History function is called so that the window can update actions
            void signal_update_undo_actions(size_type undo_count, size_type redo_count) const;

        private:
            // Internal
            //============================================================

            // make sure an operation will work
            template <typename T>
            void verify_attribute(AttributeID attributeid)
            {
                assert(attributeid.is_valid());
                assert(this->attribute_type_enum(attributeid) == Type_Traits<T>::type_enum());
                //assert(this->attribute_type_cast<T>(attributeid)->value() != value);
            }

            /*
            template <typename T, typename Func>
            void attribute_function(AttributeID attributeid, Func member_function)
            {
                verify_attribute<T>(attributeid);
                m_element_manager.element(attributeid.elementid()).attribute_type_cast<T>(attributeid.index())->(*member_function)();
                update_widget(attributeid);
                update_model(attributeid);
                emit signal_unsaved_edits(true);
            }
            */
            template <typename T, typename Func, typename... Args>
            void attribute_function(AttributeID attributeid, Func member_function, Args... args)
            {
                verify_attribute<T>(attributeid);
                (m_element_manager.element(attributeid.elementid()).attribute_type_cast<T>(attributeid.index())->*member_function)(std::forward<Args>(args)...);
                //m_element_manager.element(attributeid.elementid()).attribute_type_cast<T>(attributeid.index())->(member_function)(std::forward<Args>(args)...);
                update_widget(attributeid);
                update_model(attributeid);
                emit signal_unsaved_edits(true);
            }



            void update_representations(ElementID elementid);
            void update_representations(AttributeID attributeid);

            void update_widget(ElementID elementid);
            void update_widget(AttributeID attributeid);

            void update_model(ElementID elementid);
            void update_model(AttributeID attributeid);


        private:
            // Data Members
            //============================================================

            //data
            Element_Manager m_element_manager;
            Command_History m_command_history;

            ElementID m_project_elementid;
            AttributeID m_project_filepath; // ref to filepath storage

            // if you wanted to store other stuff in other Elements....

            // Outliner model
            Uptr<Outliner_Model> m_outliner_model;
            Uptr<Outliner_Delegate> m_outliner_delegate;

            // Widgets
            Uptr<Outliner_Treeview> m_outliner; // Element outliner (No direct attribute access)
            Uptr<QScrollArea> m_scroll_area; // area that will contain m_editor
            Uptr<Element_Widget> m_editor; // editor for a given ElementID

            Uptr<QHBoxLayout> m_layout;

            // Static Helpers
            //============================================================
            // Make an ElementID with the supplied manager by registering the Element type the first time this is run
            static ElementID make_Project(Element_Manager& element_manager);
        };



        /*
        PWC_Element_Set_Name
        ====================================================================================================
        Project_Widget Commands need to be in this header to avoid a circular dependency with the template.
        */
        class PWC_Element_Set_Name:
                public Command
        {
        public:
            PWC_Element_Set_Name(Project_Widget*const project_widget, ElementID elementid, String const& name):
                Command(),
                mp_project_widget(project_widget),
                m_elementid(elementid),
                m_old_name(mp_project_widget->element_name(elementid)),
                m_new_name(name)
            {
                assert(mp_project_widget);
                assert(mp_project_widget->is_valid(elementid));
            }
            ~PWC_Element_Set_Name() override = default;

        protected:
            void v_execute() override
            {
                mp_project_widget->element_set_name(m_elementid, m_new_name);
            }
            void v_unexecute() override
            {
                mp_project_widget->element_set_name(m_elementid, m_old_name);
            }
        private:
            Project_Widget*const mp_project_widget;
            ElementID m_elementid;
            String m_old_name;
            String m_new_name;
        };

        /*
        PWC_Attribute_Set_Value<T>
        ====================================================================================================
        Project_Widget Commands need to be in this header to avoid a circular dependency with the template.
        */
        template <typename T>
        class PWC_Attribute_Set_Value:
                public Command
        {
        public:
            PWC_Attribute_Set_Value(Project_Widget*const project_widget, AttributeID attributeid, T const& value):
                Command(),
                mp_project_widget(project_widget),
                m_attributeid(attributeid),
                m_old_value(mp_project_widget->attribute_type_cast<T>(attributeid)->value()),
                m_new_value(value)
            {
                assert(mp_project_widget);
                assert(mp_project_widget->is_valid(attributeid));
            }
            ~PWC_Attribute_Set_Value() override = default;

        protected:
            void v_execute() override
            {
                mp_project_widget->attribute_set_value<T>(m_attributeid, m_new_value);
            }
            void v_unexecute() override
            {
                mp_project_widget->attribute_set_value<T>(m_attributeid, m_old_value);
            }
        private:
            Project_Widget*const mp_project_widget;
            AttributeID m_attributeid;
            T m_old_value;
            T m_new_value;
        };



        /*
        PWC_Attribute_Vector_Push_Back<T>
        ====================================================================================================
        Project_Widget Commands need to be in this header to avoid a circular dependency with the template.
        */
        template <typename T>
        class PWC_Attribute_Vector_Push_Back:
                public Command
        {
        public:
            PWC_Attribute_Vector_Push_Back(Project_Widget*const project_widget, AttributeID attributeid, T const& value):
                Command(),
                mp_project_widget(project_widget),
                m_attributeid(attributeid),
                m_new_value(value)
            {
                assert(mp_project_widget);
                assert(mp_project_widget->is_valid(attributeid));
            }
            ~PWC_Attribute_Vector_Push_Back() override = default;

        protected:
            void v_execute() override
            {
                mp_project_widget->attribute_vector_push_back(m_attributeid, m_new_value);
            }
            void v_unexecute() override
            {
                mp_project_widget->attribute_vector_pop_back_ElementID(m_attributeid);
            }
        private:
            Project_Widget*const mp_project_widget;
            AttributeID m_attributeid;
            T m_new_value;
        };


        /*
        PWC_Attribute_Vector_Set_Value_At<T>
        ====================================================================================================
        Project_Widget Commands need to be in this header to avoid a circular dependency with the template.
        */
        template <typename T>
        class PWC_Attribute_Vector_Set_Value_At:
                public Command
        {
        public:
            PWC_Attribute_Vector_Set_Value_At(Project_Widget*const project_widget, AttributeID attributeid, size_type index, T const& value):
                Command(),
                mp_project_widget(project_widget),
                m_attributeid(attributeid),
                m_index(index),
                m_new_value(value),
                m_old_value(mp_project_widget->attribute_type_cast<Vector<T>>(attributeid)->at(index))
            {
                assert(mp_project_widget);
                assert(mp_project_widget->is_valid(attributeid));
            }
            ~PWC_Attribute_Vector_Set_Value_At() override = default;

        protected:
            void v_execute() override
            {
                //mp_project_widget->attribute_vector_set_at(m_attributeid, m_index, m_new_value);
            }
            void v_unexecute() override
            {
                //mp_project_widget->attribute_vector_set_at(m_attributeid, m_index, m_old_value);
            }
        private:
            Project_Widget*const mp_project_widget;
            AttributeID m_attributeid;
            size_type m_index;
            T m_new_value;
            T m_old_value;
        };


    } // namespace Qtlib
}  // namespace Saklib


#endif // Project_Widget_H
