#ifndef NODE_MANAGER_H
#define NODE_MANAGER_H

#include "nodeid.h"
#include "inode.h"
#include "data.h"
#include "data_manager.h"

namespace Saklib
{
    class Node_Connection;
    class Node_Definition;

    /*
    Node_Manager
    ====================================================================================================
    Simple manager for Nodes via NodeIDs. It's really just map with a simplified interface. You will
    need access to this class to make use of the ID types.

    */

    class Node_Manager
    {
    public:
        // Special 6
        //============================================================
        Node_Manager();
        ~Node_Manager();

        // NO COPYING
        Node_Manager(Node_Manager const& other) = delete;
        Node_Manager& operator=(Node_Manager const& other) = delete;

        // Implicit default move
        //Node_Manager(Node_Manager && other) = default;
        //Node_Manager& operator=(Node_Manager && other) = default;

        // Interface
        //============================================================
        // Is this NodeID valid for this?
        bool is_valid(NodeID nodeid) const;

        // Build a new Map_Entry containing a new INode from the given Node_Definition and return the id to it
        NodeID make_node(Node_Definition const& definition, String const& name = String());

        void destroy_node(NodeID nodeid);
        /*
        // Do we want all these forwarding functions?....it'll be an ass if INode changes...

        // Destroy the Node associated with this id, including any children

        bool user_can_destroy(NodeID nodeid) const;
        void void_user_can_destroy(NodeID nodeid, bool state);
        bool user_destroy_node(NodeID nodeid);

        // Access the parent of this ID
        bool has_parent(NodeID nodeid) const;
        NodeID parent(NodeID nodeid) const;
        void set_parent(NodeID nodeid, NodeID new_parent);
        bool user_can_set_parent(NodeID nodeid) const;
        void void_user_can_set_parent(NodeID nodeid, bool state);
        bool user_set_parent(NodeID nodeid, NodeID new_parent);

        // Access the parent of this ID
        String const& name(NodeID nodeid) const;
        void set_name(NodeID nodeid, String const& new_name);
        bool user_can_set_name(NodeID nodeid) const;
        void void_user_can_set_name(NodeID nodeid, bool state);
        bool user_set_name(NodeID nodeid, String const& new_name);
        */
        // Access the Node associated with this ID
        INode* inode(NodeID nodeid);
        INode const* inode(NodeID nodeid) const;

        /*
        template <typename T>
        IData* idata(NodeID nodeid)
        {
            return inode(nodeid)->data_interface<T>();
        }
        template <typename T>
        IData const* idata(NodeID nodeid) const
        {
            return inode(nodeid)->data_interface<T>();
        }

        template <typename Node_Class>
        Node_Class* node_cast(NodeID nodeid)
        {
            return dynamic_cast<Node_Class*>(node(nodeid));
        }
        template <typename Node_Class>
        Node_Class const* node_cast(NodeID nodeid) const
        {
            return dynamic_cast<Node_Class*>(node(nodeid));
        }
        */

        // Auxillary access
        Vector_NodeID all_nodeids() const;
        // ElementIDs that have no parent
        Vector_NodeID root_nodeids() const;
        // Names of all Nodes
        Vector_String all_node_names() const;

        // All nodes related to this node by parenting that cannot be user broken
        Vector_NodeID subgraph(NodeID nodeid) const;

        // Destory everything
        void clear();

        // Command Interface
        //============================================================
        // Bits that only Command objects will end up using

        size_type command_ref_count(NodeID nodeid) const;

        // Adjust ref counts
        void increment_command_ref_count(NodeID nodeid);
        void decrement_command_ref_count(NodeID nodeid);

    private:
        String make_name_unique(String const& name);

        // Helpers
        //============================================================

        // Member Data
        //============================================================
        // What is a Node's parent Node?
        Data_Manager<NodeID> m_node_map_parent;

        // What is a Node's name?
        Data_Manager<String> m_node_map_name;

        // What are a Node's children?
        std::map <NodeID, Data<Vector_NodeID> > m_node_map_children;

        // Is a Node user destructable?
        Data_Manager<Bool> m_node_map_destructable;

        // How many stored commands reference this Node?
        Data_Manager<Uint> m_node_map_command_ref_count;

        mutable id_type m_next_id;
    };

} // namespace Saklib

#endif // NODE_MANAGER_H
