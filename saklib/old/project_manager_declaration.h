#ifndef PROJECT_MANAGER_DECLARATION_H
#define PROJECT_MANAGER_DECLARATION_H

#include "types.h"
#include "all_attributes.h"
#include "element_definition_manager.h"
#include "element_manager.h"
#include "command_history.h"

namespace saklib
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

        std::vector<String> all_registered_element_types() const;


        // Make a new Element and return all info about it
        ElementID make_element(String const& type);
        // Destory an Element and everything associated with it
        void destroy_element(ElementID const& elementid);

        // Does this refer to something in this? - rename these to has(blah) ?
        bool has_elementid(ElementID const& elementid) const;
        bool has_attributeid(AttributeID const& attributeid) const;

        // Elements
        //------------------------------------------------------------
        Element* element(ElementID const& elementid);
        Element const* celement(ElementID const& elementid) const; // return a pointer?

        String const& element_type(ElementID const& elementid) const;

        String const& element_name(ElementID const& elementid) const;
        void element_set_name(ElementID const& elementid, String const& value);

        bool element_can_be_root(ElementID const& elementid) const;

        AttributeID element_parent(ElementID const& elementid) const;
        void element_set_parent(ElementID const& elementid, AttributeID attributeid = invalid_attributeid());


        // Attributes
        //------------------------------------------------------------
        AttributeID attributeid(ElementID const& elementid, String const& attribute_name) const;

        Attribute* attribute(AttributeID const& attributeid);
        Attribute* attribute(ElementID const& elementid, size_type attribute_index);
        Attribute* attribute(ElementID const& elementid, String const& attribute_name);

        Attribute const* attribute(AttributeID const& attributeid) const;
        Attribute const* attribute(ElementID const& elementid, size_type attribute_index) const;
        Attribute const* attribute(ElementID const& elementid, String const& attribute_name) const;


        // Attribute forwarding functions
        //------------------------------------------------------------
        String const& attribute_name(AttributeID const& attributeid) const;
        Type_Enum attribute_type_enum(AttributeID const& attributeid) const;
        String attribute_type_string(AttributeID const& attributeid) const;
        bool attribute_is_constrained(AttributeID const& attributeid) const;

        // Attribute_Type<T> forwarding functions
        //------------------------------------------------------------
        // These functions set the data without question, and tell the model and widget to update.

        template <typename T>
        T const& attribute_value(AttributeID const& attributeid) const;

        template <typename T>
        void attribute_set_value(AttributeID const& attributeid, T const& value);

        // Attribute_Type<Vector<T>> Type-Anonymous Functions
        //------------------------------------------------------------
        // We do not need to know the underlying type to call these functions, but this must figure
        // it out and act appropriately.

        bool any_attribute_vector_empty(AttributeID const& attributeid) const;
        size_type any_attribute_vector_size(AttributeID const& attributeid) const;

        void any_attribute_vector_clear(AttributeID const& attributeid);
        void any_attribute_vector_pop_back(AttributeID const& attributeid);
        void any_attribute_vector_swap_at(AttributeID const& attributeid, size_type index, size_type other_index);

        void any_attribute_vector_remove_at(AttributeID const& attributeid, size_type index);

        // Attribute_Type<Vector<T>> forwarding functions
        //------------------------------------------------------------
        // We must know the type to use these ones, and they should be called without specifying the
        // explicitly so that the ElementID overload can be used (specialisation for it doesn't work).

        template <typename T>
        std::vector<T> const& attribute_vector_vector(AttributeID const& attributeid);

        template <typename T>
        void attribute_vector_set_vector(AttributeID const& attributeid, std::vector<T> const& other_vector);

        template <typename T>
        bool attribute_vector_empty(AttributeID const& attributeid) const;

        template <typename T>
        size_type attribute_vector_size(AttributeID const& attributeid) const;

        template <typename T>
        void attribute_vector_clear(AttributeID const& attributeid);



        template <typename T>
        T const& attribute_vector_at(AttributeID const& attributeid, size_type index) const;

        template <typename T>
        T const& attribute_vector_front(AttributeID const& attributeid) const;

        template <typename T>
        T const& attribute_vector_back(AttributeID const& attributeid) const;

        template <typename T>
        void attribute_vector_set_at(AttributeID const& attributeid, size_type index, T const& value);

        template <typename T>
        void attribute_vector_set_front(AttributeID const& attributeid, T const& value);

        template <typename T>
        void attribute_vector_set_back(AttributeID const& attributeid, T const& value);

        template <typename T>
        void attribute_vector_swap_at(AttributeID const& attributeid, size_type index, size_type other_index);

        template <typename T>
        void attribute_vector_push_back(AttributeID const& attributeid, T const& value);

        template <typename T>
        void attribute_vector_pop_back(AttributeID const& attributeid);

        template <typename T>
        void attribute_vector_insert_at(AttributeID const& attributeid, size_type index, T const& value);

        template <typename T>
        void attribute_vector_remove_at(AttributeID const& attributeid, size_type index);

        // Attribute_Type<T> Constraint Stuff
        //------------------------------------------------------------
        // Get a vector of possible Element types for this attributeid
        std::vector<String> attribute_element_types(AttributeID const& attributeid) const;


        // Attribute_Type<T>
        //------------------------------------------------------------
        bool undoable_element_set_name(ElementID const& elementid, String const& value);

        template <typename T>
        bool undoable_attribute_set_value(AttributeID const& attributeid, T const& value);


        // Attribute_Type<Vector<T>>
        //------------------------------------------------------------
        // any type

        bool undoable_any_attribute_vector_clear(AttributeID const& attributeid);
        bool undoable_any_attribute_vector_swap_at(AttributeID const& attributeid, size_type index, size_type other_index);
        bool undoable_any_attribute_vector_pop_back(AttributeID const& attributeid);
        bool undoable_any_attribute_vector_remove_at(AttributeID const& attributeid, size_type index);

        // specific type

        template <typename T>
        bool undoable_attribute_vector_clear(AttributeID const& attributeid);

        template <typename T>
        bool undoable_attribute_vector_set_at(AttributeID const& attributeid, size_type index, T const& value);

        template <typename T>
        bool undoable_attribute_vector_set_front(AttributeID const& attributeid, T const& value);

        template <typename T>
        bool undoable_attribute_vector_set_back(AttributeID const& attributeid, T const& value);

        template <typename T>
        bool undoable_attribute_vector_swap_at(AttributeID const& attributeid, size_type index, size_type other_index);

        template <typename T>
        bool undoable_attribute_vector_push_back(AttributeID const& attributeid, T const& value);

        template <typename T>
        bool undoable_attribute_vector_pop_back(AttributeID const& attributeid);

        template <typename T>
        bool undoable_attribute_vector_insert_at(AttributeID const& attributeid, size_type index, T const& value);

        template <typename T>
        bool undoable_attribute_vector_remove_at(AttributeID const& attributeid, size_type index);

        // Flat Access
        //------------------------------------------------------------
        std::vector<ElementID> all_elementids() const;
        std::vector<ElementID> root_elementids() const;

        // Model Interface
        //------------------------------------------------------------
        // Functions that provide data to the outliner model

        // What are this item's children?
        std::vector<AttributeID> outliner_children(ElementID const& elementid) const;
        std::vector<ElementID> outliner_children(AttributeID const& attributeid) const;

        // What item is the child at row?
        AttributeID outliner_child_at_row(ElementID const& elementid, int row) const;
        ElementID outliner_child_at_row(AttributeID const& attributeid, int row) const;

        // How many rows does this item have?
        int outliner_row_count_root() const;
        int outliner_row_count(ElementID const& elementid) const;
        int outliner_row_count(AttributeID const& attributeid) const;

        // What is the parent of this item?
        AttributeID parent_of(ElementID const& elementid) const;
        ElementID parent_of(AttributeID const& attributeid) const; // duh

        // What row is this in its parent as far as the model is concerned?
        int outliner_row_in_parent(ElementID const& elementid) const;
        int outliner_row_in_parent(AttributeID const& attributeid) const;




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

        size_type command_ref_count(ElementID const& elementid) const;

        void increment_command_ref_count(ElementID const& elementid);
        void increment_command_ref_count(AttributeID const& attributeid);

        void decrement_command_ref_count(ElementID const& elementid);
        void decrement_command_ref_count(AttributeID const& attributeid);



        // Element Widget
        //------------------------------------------------------------
        // Alter the Element currently being edited

        // Make an Element_Widget for this ElementID
        void open_editor(ElementID const& elementid);

        // The ElementID of the Element that is currently being edited
        ElementID currently_open_elementid() const;



    private:
        // Internal
        //============================================================
        // make sure an operation will work
        void assert_element(ElementID const& elementid) const;

        template <typename T>
        void assert_attribute(AttributeID const& attributeid) const;

        void attribute_changed(AttributeID const& attributeid);

        void set_unsaved_edits(bool state);

        // Observer Signals
        //============================================================
        void observers_begin_model_reset() const;
        void observers_end_model_reset() const;

        void observers_element_name_changed(ElementID const& elementid) const;
        void observers_element_parent_changed(ElementID const& elementid) const;
        void observers_element_destroyed(ElementID const& elementid) const;

        void observers_attribute_value_changed(AttributeID const& attributeid) const;

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
        std::vector<Project_Observer*> m_observers;
    };


    // Templated member function specialisations must be declared outside of the class...

    template <>
    void Project_Manager::attribute_set_value<ElementID>(AttributeID const& attributeid, ElementID const& value);


    template <>
    void Project_Manager::attribute_vector_set_vector<ElementID>(AttributeID const& attributeid, std::vector<ElementID> const& other_vector);
    template <>
    void Project_Manager::attribute_vector_clear<ElementID>(AttributeID const& attributeid);
    template <>
    void Project_Manager::attribute_vector_set_at<ElementID>(AttributeID const& attributeid, size_type index, ElementID const& value);
    template <>
    void Project_Manager::attribute_vector_set_front<ElementID>(AttributeID const& attributeid, ElementID const& value);
    template <>
    void Project_Manager::attribute_vector_set_back<ElementID>(AttributeID const& attributeid, ElementID const& value);
    template <>
    void Project_Manager::attribute_vector_swap_at<ElementID>(AttributeID const& attributeid, size_type index, size_type other_index);
    template <>
    void Project_Manager::attribute_vector_push_back<ElementID>(AttributeID const& attributeid, ElementID const& value);
    template <>
    void Project_Manager::attribute_vector_pop_back<ElementID>(AttributeID const& attributeid);
    template <>
    void Project_Manager::attribute_vector_insert_at<ElementID>(AttributeID const& attributeid, size_type index, ElementID const& value);
    template <>
    void Project_Manager::attribute_vector_remove_at<ElementID>(AttributeID const& attributeid, size_type index);

}  // namespace saklib

#endif // PROJECT_MANAGER_DECLARATION_H
