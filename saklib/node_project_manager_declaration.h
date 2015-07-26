#ifndef NODE_PROJECT_MANAGER_DECLARATION_H
#define NODE_PROJECT_MANAGER_DECLARATION_H

#include "types.h"
#include "all_attributes.h"
#include "element_definition_manager.h"
#include "node_manager.h"
#include "command_history.h"

namespace Saklib
{
    class INode;
    class IData;
    class IAttribute;
    class IElement;
    class Node_Project_Observer;

    /*
    Node_Project_Manager
    ====================================================================================================
    */
    class Node_Project_Manager
    {
    public:
        // Special 6
        //============================================================
        Node_Project_Manager();
        explicit Node_Project_Manager(Path const& filepath);
        ~Node_Project_Manager();

        // NO COPYING
        Node_Project_Manager(Node_Project_Manager const& other) = delete;
        Node_Project_Manager& operator=(Node_Project_Manager const& other) = delete;

        // Implicit default move
        //Node_Project_Manager(Node_Project_Manager && other) = default;
        //Node_Project_Manager& operator=(Node_Project_Manager && other) = default;

        // Interface
        //============================================================

        // Overall Project
        //------------------------------------------------------------

        void new_project(Path const& filepath);
        void open_project(Path const& filepath);

        void save() const;
        void save_as(Path const& filepath);
        void clear();

        NodeID project_nodeid() const;
        Path const& project_filepath() const;
        void set_project_filepath(Path const& filepath);


        void add_observer(Node_Project_Observer* observer);
        void remove_observer(Node_Project_Observer* observer);

        // Lifetime
        //------------------------------------------------------------
        void register_element_definition(Element_Definition&& definition);
        bool has_element_definition(String const& type) const;
        Element_Definition const& element_definition(String const& type) const;

        Vector_String all_registered_element_types() const;


        // Make a new Element_Node and return all info about it
        NodeID make_element_node(String const& type);

        // Make a new Attribute_Node<T> and return the NodeID
        template <typename T>
        NodeID make_attribute_node(NodeID elementid, String const& name, T const& value = T());

        // Destory an Element and everything associated with it
        void destroy_node(NodeID nodeid);

        // Does this refer to something in this? - rename these to has(blah) ?
        bool is_valid(NodeID nodeid) const;


        // INode Interface
        //------------------------------------------------------------
        //Forwarding access to the entire INode interface
        INode* inode(NodeID nodeid);
        INode const* inode(NodeID nodeid) const;

        bool inode_user_can_destroy(NodeID nodeid) const;
        void inode_set_user_can_destroy(NodeID nodeid, bool state);

        // This Node's id
        //NodeID nodeid() const;
        //void set_nodeid(NodeID new_id);

        // Parent
        bool inode_has_parent(NodeID nodeid) const;
        NodeID inode_parent(NodeID nodeid) const;
        void inode_set_parent(NodeID nodeid, NodeID new_parentid);
        bool inode_user_set_parent(NodeID nodeid, NodeID new_parentid);
        bool inode_user_can_set_parent(NodeID nodeid) const;
        void inode_set_user_can_set_parent(NodeID nodeid, bool state);

        // Name
        String const& inode_name(NodeID nodeid) const;
        void inode_set_name(NodeID nodeid, String const& new_name);
        bool inode_user_can_set_name(NodeID nodeid) const;
        bool inode_user_set_name(NodeID nodeid, String const& new_name);
        void inode_set_user_can_set_name(NodeID nodeid, bool state);

        // Children
        bool inode_never_has_children(NodeID nodeid) const;
        bool inode_can_have_children(NodeID nodeid) const;
        bool inode_has_children(NodeID nodeid) const;
        size_type inode_child_count(NodeID nodeid) const;
        Vector_NodeID inode_children(NodeID nodeid) const;

        // Data
        Type_Enum inode_type_enum(NodeID nodeid) const;
        String inode_type_string(NodeID nodeid) const;



        // IData<T> interface
        //------------------------------------------------------------
        // Forwarding access to the entire IData<T> interface
        template <typename T>
        IData<T>* idata(NodeID nodeid);
        template <typename T>
        IData<T> const* idata(NodeID nodeid) const;


        // IData_Shared
        //------------------------------------------------------------
        bool idata_user_can_set_data(NodeID nodeid) const;
        void idata_set_user_can_set_data(NodeID nodeid, bool state);

        // IData<T>
        //------------------------------------------------------------
        template <typename T>
        T const& idata_data(NodeID nodeid) const;
        template <typename T>
        void idata_set_data(NodeID nodeid, T const& value);
        template <typename T>
        bool idata_user_set_data(NodeID nodeid, T const& value);


        // IData<Vector<T>>
        //------------------------------------------------------------
        template <typename T>
        Vector<T> const& idata_vector(NodeID nodeid) const;
        template <typename T>
        void idata_vector_set_vector(NodeID nodeid, Vector<T> const& vector_value);
        template <typename T>
        bool idata_vector_user_set_vector(NodeID nodeid, Vector<T> const& vector_value);

        template <typename T>
        void idata_vector_swap_vector(NodeID nodeid, Vector<T>& vector_value);
        template <typename T>
        bool idata_vector_user_swap_vector(NodeID nodeid, Vector<T>& vector_value);

        template <typename T>
        bool idata_vector_empty(NodeID nodeid) const;
        template <typename T>
        size_type idata_vector_size(NodeID nodeid) const;

        template <typename T>
        void idata_vector_clear(NodeID nodeid);
        template <typename T>
        bool idata_vector_user_clear(NodeID nodeid);

        template <typename T>
        T const& idata_vector_at(NodeID nodeid, size_type index) const;
        template <typename T>
        void idata_vector_set_at(NodeID nodeid, size_type index, T const& value);
        template <typename T>
        bool idata_vector_user_set_at(NodeID nodeid, size_type index, T const& value);

        template <typename T>
        T const& idata_vector_front(NodeID nodeid) const;
        template <typename T>
        void idata_vector_set_front(NodeID nodeid, T const& value);
        template <typename T>
        bool idata_vector_user_set_front(NodeID nodeid, T const& value);

        template <typename T>
        T const& idata_vector_back(NodeID nodeid) const;
        template <typename T>
        void idata_vector_set_back(NodeID nodeid, T const& value);
        template <typename T>
        bool idata_vector_user_set_back(NodeID nodeid, T const& value);

        template <typename T>
        void idata_vector_swap_at(NodeID nodeid, size_type index, size_type other_index);
        template <typename T>
        bool idata_vector_user_swap_at(NodeID nodeid, size_type index, size_type other_index);

        template <typename T>
        void idata_vector_push_back(NodeID nodeid, T const& value);
        template <typename T>
        bool idata_vector_user_push_back(NodeID nodeid, T const& value);

        template <typename T>
        void idata_vector_pop_back(NodeID nodeid);
        template <typename T>
        bool idata_vector_user_pop_back(NodeID nodeid);

        template <typename T>
        void idata_vector_insert_at(NodeID nodeid, size_type index, T const& value);
        template <typename T>
        bool idata_vector_user_insert_at(NodeID nodeid, size_type index, T const& value);

        template <typename T>
        void idata_vector_remove_at(NodeID nodeid, size_type index);
        template <typename T>
        bool idata_vector_user_remove_at(NodeID nodeid, size_type index);


        // Elements
        //------------------------------------------------------------
        IElement* element(NodeID elementid);
        IElement const* element(NodeID elementid) const;

        String const& element_type(NodeID elementid) const; //?

        // Attributes
        //------------------------------------------------------------
        IAttribute* attribute(NodeID attributeid);
        IAttribute const* attribute(AttributeID attributeid) const;


        // Attribute_Type<T> Constraint Stuff
        //------------------------------------------------------------
        // Get a vector of possible Element types for this attributeid
        Vector_String attribute_element_types(AttributeID attributeid) const;



        // Undoable INode Interface
        //------------------------------------------------------------
        void undoable_inode_set_user_can_destroy(NodeID nodeid, bool state);

        // This Node's id
        //NodeID nodeid() const;
        //void set_nodeid(NodeID new_id);

        // Parent
        bool undoable_inode_set_parent(NodeID nodeid, NodeID new_parentid);
        bool undoable_inode_user_set_parent(NodeID nodeid, NodeID new_parentid);
        bool undoable_inode_set_user_can_set_parent(NodeID nodeid, bool state);

        // Name
        bool undoable_inode_set_name(NodeID nodeid, String const& new_name);
        bool undoable_inode_user_set_name(NodeID nodeid, String const& new_name);
        bool undoable_inode_set_user_can_set_name(NodeID nodeid, bool state);

        // Undoable IData_Shared
        //------------------------------------------------------------
        bool undoable_idata_set_user_can_set_data(NodeID nodeid, bool state);

        // Undoable IData<T>
        //------------------------------------------------------------
        template <typename T>
        void undoable_idata_set_data(NodeID nodeid, T const& value);
        template <typename T>
        bool undoable_idata_user_set_data(NodeID nodeid, T const& value);


        // Undoable IData<Vector<T>>
        //------------------------------------------------------------
        template <typename T>
        bool undoable_idata_vector_set_vector(NodeID nodeid, Vector<T> const& vector_value);
        template <typename T>
        bool undoable_idata_vector_user_set_vector(NodeID nodeid, Vector<T> const& vector_value);

        template <typename T>
        bool undoable_idata_vector_swap_vector(NodeID nodeid, Vector<T>& vector_value);
        template <typename T>
        bool undoable_idata_vector_user_swap_vector(NodeID nodeid, Vector<T>& vector_value);

        template <typename T>
        bool undoable_idata_vector_clear(NodeID nodeid);
        template <typename T>
        bool undoable_idata_vector_user_clear(NodeID nodeid);

        template <typename T>
        bool undoable_idata_vector_set_at(NodeID nodeid, size_type index, T const& value);
        template <typename T>
        bool undoable_idata_vector_user_set_at(NodeID nodeid, size_type index, T const& value);

        template <typename T>
        bool undoable_idata_vector_set_front(NodeID nodeid, T const& value);
        template <typename T>
        bool undoable_idata_vector_user_set_front(NodeID nodeid, T const& value);

        template <typename T>
        bool undoable_idata_vector_set_back(NodeID nodeid, T const& value);
        template <typename T>
        bool undoable_idata_vector_user_set_back(NodeID nodeid, T const& value);

        template <typename T>
        bool undoable_idata_vector_swap_at(NodeID nodeid, size_type index, size_type other_index);
        template <typename T>
        bool undoable_idata_vector_user_swap_at(NodeID nodeid, size_type index, size_type other_index);

        template <typename T>
        bool undoable_idata_vector_push_back(NodeID nodeid, T const& value);
        template <typename T>
        bool undoable_idata_vector_user_push_back(NodeID nodeid, T const& value);

        template <typename T>
        bool undoable_idata_vector_pop_back(NodeID nodeid);
        template <typename T>
        bool undoable_idata_vector_user_pop_back(NodeID nodeid);

        template <typename T>
        bool undoable_idata_vector_insert_at(NodeID nodeid, size_type index, T const& value);
        template <typename T>
        bool undoable_idata_vector_user_insert_at(NodeID nodeid, size_type index, T const& value);

        template <typename T>
        bool undoable_idata_vector_remove_at(NodeID nodeid, size_type index);
        template <typename T>
        bool undoable_idata_vector_user_remove_at(NodeID nodeid, size_type index);

        // Flat Access
        //------------------------------------------------------------
        Vector_NodeID all_elementids() const;
        Vector_NodeID root_elementids() const;

        Vector_NodeID all_nodeids() const;
        Vector_NodeID root_nodeids() const;

        // These should be doable via INode
        /*
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
        */



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

    private:
        // Internal
        //============================================================
        // make sure an operation will work
        void assert_node(NodeID nodeid) const;

        template <typename T>
        void assert_data(NodeID nodeid) const;

        template <typename Func, typename... Args>
        void inode_function(NodeID nodeid, Func member_function, Args... args);

        template <typename T, typename Func, typename... Args>
        void idata_function(NodeID nodeid, Func member_function, Args... args);

        void set_unsaved_edits(bool state);

        // Observer Signals
        //============================================================
        void observers_begin_model_reset() const;
        void observers_end_model_reset() const;

        void observers_node_name_changed(NodeID nodeid) const;
        void observers_node_parent_changed(NodeID nodeid) const;
        void observers_node_destroyed(NodeID nodeid) const;

        void observers_node_data_changed(NodeID nodeid) const;

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
        Node_Manager m_node_manager;
        Command_History m_command_history;

        NodeID m_project_nodeid;
        NodeID m_project_filepath; // ref to filepath storage

        bool m_unsaved_edits;
        Vector<Node_Project_Observer*> m_observers;
    };


    // Templated member function specialisations must be declared outside of the class...
    // IData<T>
    //------------------------------------------------------------
    template <>
    void idata_set_data(NodeID nodeid, T const& value);


    // IData<Vector<T>>
    //------------------------------------------------------------
    template <>
    void idata_vector_set_vector(NodeID nodeid, Vector<NodeID> const& vector_value);

    template <>
    void idata_vector_swap_vector(NodeID nodeid, Vector<NodeID>& vector_value);

    template <>
    void idata_vector_clear(NodeID nodeid);

    template <>
    void idata_vector_set_at(NodeID nodeid, size_type index, NodeID const& value);

    template <>
    void idata_vector_set_front(NodeID nodeid, NodeID const& value);

    template <>
    void idata_vector_set_back(NodeID nodeid, NodeID const& value);

    template <>
    void idata_vector_swap_at(NodeID nodeid, size_type index, size_type other_index);

    template <>
    void idata_vector_push_back(NodeID nodeid, NodeID const& value);

    template <>
    void idata_vector_pop_back(NodeID nodeid);

    template <>
    void idata_vector_insert_at(NodeID nodeid, size_type index, NodeID const& value);

    template <>
    void idata_vector_remove_at(NodeID nodeid, size_type index);

}  // namespace Saklib

#endif // NODE_PROJECT_MANAGER_DECLARATION_H

