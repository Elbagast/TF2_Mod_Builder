#ifndef PROJECT_MANAGER_DECLARATION_H
#define PROJECT_MANAGER_DECLARATION_H

#include "types.h"
#include "all_attributes.h"
#include "element_definition_manager.h"
#include "element_manager.h"
#include "command_history.h"

namespace Saklib
{
    class Project_Observer;

    /*
    Project_Widget
    ====================================================================================================
    This widget is the root widget of an entire project and forms the central widget of the window
    class that holds it. When something happens that needs to update the window (e.g. enable/disable
    menu actions) it emits signals that will already have been connected as appropriate.
    */
    class Project_Manager
    {
    public:
        // Special 6
        //============================================================
        Project_Manager();
        explicit Project_Manager(Path const& filepath);
        ~Project_Manager();

        // NO COPYING
        Project_Manager(Project_Manager const& other) = delete;
        Project_Manager& operator=(Project_Manager const& other) = delete;

        // Implicit default move
        //Project_Widget(Project_Widget && other) = default;
        //Project_Widget& operator=(Project_Widget && other) = default;

        // Interface
        //============================================================

        // Overall Project
        //------------------------------------------------------------

        void new_project(Path const& filepath);
        void open_project(Path const& filepath);

        void save() const;
        void save_as(Path const& filepath);
        void clear();

        ElementID project_elementid() const;
        Path const& project_filepath() const;
        void set_project_filepath(Path const& filepath);


        void add_observer(Project_Observer* observer);
        void remove_observer(Project_Observer* observer);

        // Lifetime
        //------------------------------------------------------------
        void register_element_definition(Element_Definition&& definition);
        bool has_element_definition(String const& type) const;
        Element_Definition const& element_definition(String const& type) const;

        Vector_String all_registered_element_types() const;


        // Make a new Element and return all info about it
        ElementID make_element(String const& type);
        // Destory an Element and everything associated with it
        void destroy_element(ElementID elementid);

        // Does this refer to something in this? - rename these to has(blah) ?
        bool is_valid(ElementID elementid) const;
        bool is_valid(AttributeID attributeid) const;

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

        Attribute* attribute(AttributeID attributeid);
        Attribute* attribute(ElementID elementid, size_type attribute_index);
        Attribute* attribute(ElementID elementid, String const& attribute_name);

        Attribute const* attribute(AttributeID attributeid) const;
        Attribute const* attribute(ElementID elementid, size_type attribute_index) const;
        Attribute const* attribute(ElementID elementid, String const& attribute_name) const;


        // Attribute forwarding functions
        //------------------------------------------------------------
        String const& attribute_name(AttributeID attributeid) const;
        Type_Enum attribute_type_enum(AttributeID attributeid) const;
        String attribute_type_string(AttributeID attributeid) const;
        bool attribute_is_constrained(AttributeID attributeid) const;

        // Attribute_Type<T> casting
        //------------------------------------------------------------

        template <typename T>
        Attribute_Type<T>* attribute_type_cast(AttributeID attributeid);

        template <typename T>
        Attribute_Type<T>* attribute_type_cast(ElementID elementid, size_type attribute_index);

        template <typename T>
        Attribute_Type<T>* attribute_type_cast(ElementID elementid, String const& attribute_name);

        template <typename T>
        Attribute_Type<T> const* attribute_type_cast(AttributeID attributeid) const;

        template <typename T>
        Attribute_Type<T> const* attribute_type_cast(ElementID elementid, size_type attribute_index) const;

        template <typename T>
        Attribute_Type<T> const* attribute_type_cast(ElementID elementid, String const& attribute_name) const;

        // Attribute_Type<T> forwarding functions
        //------------------------------------------------------------
        // These functions set the data without question, and tell the model and widget to update.

        template <typename T>
        T const& attribute_value(AttributeID attributeid) const;

        template <typename T>
        void attribute_set_value(AttributeID attributeid, T const& value);

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

        template <typename T>
        void attribute_vector_set_vector(AttributeID attributeid, Vector<T> const& other_vector);

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

        // Attribute_Type<T> Constraint Stuff
        //------------------------------------------------------------
        // Get a vector of possible Element types for this attributeid
        Vector_String attribute_element_types(AttributeID attributeid) const;


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



    private:
        // Internal
        //============================================================
        // make sure an operation will work
        void assert_element(ElementID elementid) const;

        template <typename T>
        void assert_attribute(AttributeID attributeid) const;

        template <typename T, typename Func, typename... Args>
        void attribute_function(AttributeID attributeid, Func member_function, Args... args);

        void set_unsaved_edits(bool state);

        // Observer Signals
        //============================================================
        void observers_begin_model_reset() const;
        void observers_end_model_reset() const;

        void observers_element_name_changed(ElementID elementid) const;
        void observers_element_parent_changed(ElementID elementid) const;
        void observers_element_destroyed(ElementID elementid) const;

        void observers_attribute_value_changed(AttributeID attributeid) const;

        void observers_unsaved_edits_changed(bool state) const;
        void observers_undo_counts_changed(size_type undo_count, size_type redo_count) const;

        template <typename MemFunc>
        void all_observers_function(MemFunc func) const;

        template <typename MemFunc, typename... Args>
        void all_observers_function(MemFunc func, Args&&... args) const;

        // Data Members
        //============================================================

        //data
        Element_Definition_Manager m_internal_element_definitions;
        Element_Manager m_element_manager;
        Command_History m_command_history;

        ElementID m_project_elementid;
        AttributeID m_project_filepath; // ref to filepath storage

        bool m_unsaved_edits;
        Vector<Project_Observer*> m_observers;
    };


    // Templated member function specialisations must be declared outside of the class...

    template <>
    void Project_Manager::attribute_set_value<ElementID>(AttributeID attributeid, ElementID const& value);


    template <>
    void Project_Manager::attribute_vector_set_vector<ElementID>(AttributeID attributeid, Vector<ElementID> const& other_vector);
    template <>
    void Project_Manager::attribute_vector_clear<ElementID>(AttributeID attributeid);
    template <>
    void Project_Manager::attribute_vector_set_at<ElementID>(AttributeID attributeid, size_type index, ElementID const& value);
    template <>
    void Project_Manager::attribute_vector_set_front<ElementID>(AttributeID attributeid, ElementID const& value);
    template <>
    void Project_Manager::attribute_vector_set_back<ElementID>(AttributeID attributeid, ElementID const& value);
    template <>
    void Project_Manager::attribute_vector_swap_at<ElementID>(AttributeID attributeid, size_type index, size_type other_index);
    template <>
    void Project_Manager::attribute_vector_push_back<ElementID>(AttributeID attributeid, ElementID const& value);
    template <>
    void Project_Manager::attribute_vector_pop_back<ElementID>(AttributeID attributeid);
    template <>
    void Project_Manager::attribute_vector_insert_at<ElementID>(AttributeID attributeid, size_type index, ElementID const& value);
    template <>
    void Project_Manager::attribute_vector_remove_at<ElementID>(AttributeID attributeid, size_type index);

}  // namespace Saklib

#endif // PROJECT_MANAGER_DECLARATION_H

