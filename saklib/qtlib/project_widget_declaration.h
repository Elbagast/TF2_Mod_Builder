#ifndef PROJECT_WIDGET_DECLARATION
#define PROJECT_WIDGET_DECLARATION

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

            // Elements
            //------------------------------------------------------------
            Element& element(ElementID elementid);
            Element const& element(ElementID elementid) const; // return a pointer?

            String const& element_type(ElementID elementid) const;

            String const& element_name(ElementID elementid) const;
            void element_set_name(ElementID elementid, String const& value);

            bool element_can_be_root(ElementID elementid) const;

            AttributeID element_parent(ElementID elementid) const;
            void element_set_parent(ElementID elementid, AttributeID attributeid = invalid_attributeid());


            // Attributes
            //------------------------------------------------------------
            AttributeID attributeid(ElementID elementid, String const& attribute_name) const;

            Attribute *const attribute(AttributeID attributeid);
            Attribute *const attribute(ElementID elementid, size_type attribute_index);
            Attribute *const attribute(ElementID elementid, String const& attribute_name);

            Attribute const*const attribute(AttributeID attributeid) const;
            Attribute const*const attribute(ElementID elementid, size_type attribute_index) const;
            Attribute const*const attribute(ElementID elementid, String const& attribute_name) const;


            // Attribute forwarding functions
            //------------------------------------------------------------
            String const& attribute_name(AttributeID attributeid) const;
            Type_Enum attribute_type_enum(AttributeID attributeid) const;
            String attribute_type_string(AttributeID attributeid) const;

            // Attribute_Type<T> casting
            //------------------------------------------------------------

            template <typename T>
            Attribute_Type<T> *const attribute_type_cast(AttributeID attributeid);

            template <typename T>
            Attribute_Type<T> *const attribute_type_cast(ElementID elementid, size_type attribute_index);

            template <typename T>
            Attribute_Type<T> *const attribute_type_cast(ElementID elementid, String const& attribute_name);

            template <typename T>
            Attribute_Type<T> const*const attribute_type_cast(AttributeID attributeid) const;

            template <typename T>
            Attribute_Type<T> const*const attribute_type_cast(ElementID elementid, size_type attribute_index) const;

            template <typename T>
            Attribute_Type<T> const*const attribute_type_cast(ElementID elementid, String const& attribute_name) const;

            // Attribute_Type<T> forwarding functions
            //------------------------------------------------------------
            // These functions set the data without question, and tell the model and widget to update.

            template <typename T>
            T const& attribute_value(AttributeID attributeid) const;

            template <typename T>
            void attribute_set_value(AttributeID attributeid, T const& value);
            //template <>
            //void attribute_set_value(AttributeID attributeid, ElementID const& value);
            //void attribute_set_value(AttributeID attributeid, ElementID value);

            // Attribute_Type<Vector<T>> Type-Anonymous Functions
            //------------------------------------------------------------
            // We do not need to know the underlying type to call these functions, but this must figure
            // it out and act appropriately.

            bool any_attribute_vector_empty(AttributeID attributeid) const;
            size_type any_attribute_vector_size(AttributeID attributeid) const;

            void any_attribute_vector_clear(AttributeID attributeid);
            void any_attribute_vector_pop_back(AttributeID attributeid);
            void any_attribute_vector_swap_at(AttributeID attributeid, size_type index, size_type other_index);

            void any_attribute_vector_remove_at(AttributeID attributeid, size_type index);

            // Attribute_Type<Vector<T>> forwarding functions
            //------------------------------------------------------------
            // We must know the type to use these ones, and they should be called without specifying the
            // explicitly so that the ElementID overload can be used (specialisation for it doesn't work).

            //template <typename T>
            //void attribute_vector_swap_vector(AttributeID attributeid, Vector<T> other_vector) {}

            template <typename T>
            bool attribute_vector_empty(AttributeID attributeid) const;

            template <typename T>
            size_type attribute_vector_size(AttributeID attributeid) const;

            template <typename T>
            void attribute_vector_clear(AttributeID attributeid);



            template <typename T>
            T const& attribute_vector_at(AttributeID attributeid, size_type index) const;

            template <typename T>
            T const& attribute_vector_front(AttributeID attributeid) const;

            template <typename T>
            T const& attribute_vector_back(AttributeID attributeid) const;

            template <typename T>
            void attribute_vector_set_at(AttributeID attributeid, size_type index, T const& value);

            template <typename T>
            void attribute_vector_set_front(AttributeID attributeid, T const& value);

            template <typename T>
            void attribute_vector_set_back(AttributeID attributeid, T const& value);

            template <typename T>
            void attribute_vector_swap_at(AttributeID attributeid, size_type index, size_type other_index);

            template <typename T>
            void attribute_vector_push_back(AttributeID attributeid, T const& value);

            template <typename T>
            void attribute_vector_pop_back(AttributeID attributeid);

            template <typename T>
            void attribute_vector_insert_at(AttributeID attributeid, size_type index, T const& value);

            template <typename T>
            void attribute_vector_remove_at(AttributeID attributeid, size_type index);

            // Attribute_Type<T>
            //------------------------------------------------------------
            bool undoable_element_set_name(ElementID elementid, String const& value);

            template <typename T>
            bool undoable_attribute_set_value(AttributeID attributeid, T const& value);


            // Attribute_Type<Vector<T>>
            //------------------------------------------------------------
            // any type

            bool undoable_any_attribute_vector_clear(AttributeID attributeid);
            bool undoable_any_attribute_vector_swap_at(AttributeID attributeid, size_type index, size_type other_index);
            bool undoable_any_attribute_vector_pop_back(AttributeID attributeid);
            bool undoable_any_attribute_vector_remove_at(AttributeID attributeid, size_type index);

            // specific type

            template <typename T>
            bool undoable_attribute_vector_clear(AttributeID attributeid);

            template <typename T>
            bool undoable_attribute_vector_set_at(AttributeID attributeid, size_type index, T const& value);

            template <typename T>
            bool undoable_attribute_vector_set_front(AttributeID attributeid, T const& value);

            template <typename T>
            bool undoable_attribute_vector_set_back(AttributeID attributeid, T const& value);

            template <typename T>
            bool undoable_attribute_vector_swap_at(AttributeID attributeid, size_type index, size_type other_index);

            template <typename T>
            bool undoable_attribute_vector_push_back(AttributeID attributeid, T const& value);

            template <typename T>
            bool undoable_attribute_vector_pop_back(AttributeID attributeid);

            template <typename T>
            bool undoable_attribute_vector_insert_at(AttributeID attributeid, size_type index, T const& value);

            template <typename T>
            bool undoable_attribute_vector_remove_at(AttributeID attributeid, size_type index);

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

            size_type command_ref_count(ElementID elementid) const;

            void increment_command_ref_count(ElementID elementid);
            void increment_command_ref_count(AttributeID attributeid);

            void decrement_command_ref_count(ElementID elementid);
            void decrement_command_ref_count(AttributeID attributeid);



            // Element Widget
            //------------------------------------------------------------
            // Alter the Element currently being edited

            // Make an Element_Widget for this ElementID
            void open_editor(ElementID elementid);

            // The ElementID of the Element that is currently being edited
            ElementID currently_open_elementid() const;

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
            void assert_element(ElementID elementid) const;

            template <typename T>
            void assert_attribute(AttributeID attributeid) const;

            template <typename T, typename Func, typename... Args>
            void attribute_function(AttributeID attributeid, Func member_function, Args... args);

            //void update_representations(ElementID elementid);
            //void update_representations(AttributeID attributeid);

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


        // Templated member function specialisations must be declared outside of the class...

        template <>
        void Project_Widget::attribute_set_value<ElementID>(AttributeID attributeid, ElementID const& value);

        template <>
        void Project_Widget::attribute_vector_clear<ElementID>(AttributeID attributeid);
        template <>
        void Project_Widget::attribute_vector_set_at<ElementID>(AttributeID attributeid, size_type index, ElementID const& value);
        template <>
        void Project_Widget::attribute_vector_set_front<ElementID>(AttributeID attributeid, ElementID const& value);
        template <>
        void Project_Widget::attribute_vector_set_back<ElementID>(AttributeID attributeid, ElementID const& value);
        template <>
        void Project_Widget::attribute_vector_push_back<ElementID>(AttributeID attributeid, ElementID const& value);
        template <>
        void Project_Widget::attribute_vector_pop_back<ElementID>(AttributeID attributeid);
        template <>
        void Project_Widget::attribute_vector_insert_at<ElementID>(AttributeID attributeid, size_type index, ElementID const& value);
        template <>
        void Project_Widget::attribute_vector_remove_at<ElementID>(AttributeID attributeid, size_type index);


    } // namespace Qtlib
}  // namespace Saklib

#endif // PROJECT_WIDGET_DECLARATION

