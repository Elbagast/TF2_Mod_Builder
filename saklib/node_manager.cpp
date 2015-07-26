#include "node_manager.h"

// Special 6
//============================================================
Saklib::Node_Manager::Node_Manager():
    m_node_map{},
    m_node_command_ref_count_map{},
    m_next_id{0}
{
}

Saklib::Node_Manager::~Node_Manager() = default;

// Interface
//============================================================
// Is this NodeID valid for this?
bool Saklib::Node_Manager::is_valid(NodeID nodeid) const
{
    return nodeid.is_valid() && m_node_map.find(nodeid) != m_node_map.end();
}

// Build a new Map_Entry containing a new INode from the given Node_Definition and return the id to it
Saklib::NodeID Saklib::Node_Manager::make_node(Node_Definition const& definition, String const& name)
{
    NodeID newid{++m_next_id};

    assert(0);

    return newid;
}

void Saklib::Node_Manager::destroy_node(NodeID nodeid)
{
    m_node_map.erase(nodeid);
    m_node_command_ref_count_map.erase(nodeid);
}
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
Saklib::INode* Saklib::Node_Manager::inode(NodeID nodeid)
{
    auto found = m_node_map.find(nodeid);
    if (found != m_node_map.end())
        return found->second.get();
    else
        return nullptr;
}
Saklib::INode const* Saklib::Node_Manager::inode(NodeID nodeid) const
{
    auto found = m_node_map.find(nodeid);
    if (found != m_node_map.end())
        return found->second.get();
    else
        return nullptr;
}

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
Saklib::Vector_NodeID Saklib::Node_Manager::all_nodeids() const
{
    Vector_NodeID result{};
    for (auto const& value : m_node_map)
    {
        assert(value.first.is_valid());
        result.push_back(value.first);
    }
    return result;
}
// ElementIDs that have no parent
Saklib::Vector_NodeID Saklib::Node_Manager::root_nodeids() const
{
    Vector_NodeID result{};
    for (auto const& value : m_node_map)
    {
        if (!value.second->has_parent() && value.second->can_be_root() )
        {
            assert(value.first.is_valid());
            result.push_back(value.first);
        }
    }
    return result;
}
// Names of all Nodes
Saklib::Vector_String Saklib::Node_Manager::all_node_names() const
{

}

// Destory everything
void Saklib::Node_Manager::clear()
{

}

// Command Interface
//============================================================
// Bits that only Command objects will end up using

Saklib::size_type Saklib::Node_Manager::command_ref_count(NodeID nodeid) const
{

}

// Adjust ref counts
void Saklib::Node_Manager::increment_command_ref_count(NodeID nodeid)
{

}
void Saklib::Node_Manager::decrement_command_ref_count(NodeID nodeid)
{

}

Saklib::String Saklib::Node_Manager::make_name_unique(String const& name)
{

}

// Helpers
//============================================================
