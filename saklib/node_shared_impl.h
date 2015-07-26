#ifndef NODE_SHARED_IMPL_H
#define NODE_SHARED_IMPL_H

#include "inode.h"
#include "limited_access_data.h"

namespace Saklib
{
    /*
    Node
    ====================================================================================================
    Intermediate class to implement the shared parts of nodes.
    */
    class Node_Shared_Impl :
            public INode
    {
    protected:
        // Special 6
        //============================================================
        Node_Shared_Impl(//NodeID nodeid,
             NodeID parent_nodeid,
             bool parent_is_editable,
             String const& name,
             bool name_is_editable,
             bool user_can_destroy):
            INode(),
            //m_nodeid(nodeid),
            m_parent_nodeid(parent_nodeid, parent_is_editable),
            m_name(name, name_is_editable),
            m_user_can_destroy(user_can_destroy)
        {}
        ~Node_Shared_Impl() override = 0 {}

        // NO COPYING
        Node_Shared_Impl(Node_Shared_Impl const& other) = delete;
        Node_Shared_Impl& operator=(Node_Shared_Impl const& other) = delete;

        // Implicit default move
        //Node(Node && other) = default;
        //Node& operator=(Node && other) = default;

        // Virtual Interface
        //============================================================

        // Lifetime
        bool user_can_destroy() const override              { return m_user_can_destroy; }
        void set_user_can_destroy(bool state) override      { m_user_can_destroy = state; }

        // This Node's id
        //NodeID nodeid() const override                      { return m_nodeid; }
        //void set_nodeid(NodeID new_id) override             { m_nodeid = new_id; }

        // Parent
        bool has_parent() const override                    { return m_parent_nodeid.value().is_valid(); }
        NodeID parent() const override                      { return m_parent_nodeid.value(); }
        void set_parent(NodeID new_parentid) override       { m_parent_nodeid.set_value(new_parentid); }
        bool user_can_set_parent() const override           { return m_parent_nodeid.user_can_edit(); }
        bool user_set_parent(NodeID new_parentid) override  { return m_parent_nodeid.user_set_value(new_parentid); }
        void set_user_can_set_parent(bool state) override   { m_parent_nodeid.set_user_can_edit(state); }

        // Name
        String const& name() const override                 { return m_name.value(); }
        void set_name(String const& new_name) override      { m_name.set_value(new_name); }
        bool user_can_set_name() const override             { return m_name.user_can_edit(); }
        bool user_set_name(String const& new_name) override { return m_name.user_set_value(new_name); }
        void set_user_can_set_name(bool state) override     { m_name.set_user_can_edit(state); }

        // Children
        bool never_has_children() const override = 0;
        bool can_have_children() const override = 0;
        //virtual Child_Interface_Enum child_interface_enum() const override = 0;
        bool has_children() const override = 0;
        size_type child_count() const override = 0;
        Vector_NodeID children() const override = 0;

        // Data
        //Type_Enum type_enum() const override = 0;
        //String type_string() const override = 0;

    private:
        NodeID m_nodeid;
        Limited_Access_Data<NodeID> m_parent_nodeid;
        Limited_Access_Data<String> m_name;
        bool m_user_can_destroy;
    };

} // namespace Saklib

#endif // NODE_SHARED_IMPL_H
