#ifndef ATTRIBUTE_NODE_H
#define ATTRIBUTE_NODE_H

#include "data_node.h"

namespace Saklib
{
    /*
    Attribute_Node<T>
    ====================================================================================================
    Intermediate class to implement Node children specific operations. This separates out the
    specialisations for NodeID storing nodes.
    */
    template <typename T>
    class Attribute_Node :
            public Data_Node<T>
    {
    public:
        // Special 6
        //============================================================
        Attribute_Node(NodeID parent_nodeid,
                  String const& name,
                  stored_type const& value):
            Data_Node<T>(parent_nodeid, false, name, false, false, value, true)
        {
            assert(this->parent().is_valid());
            assert(!this->name().empty());
            assert(this->type_enum() != Type_Enum::Undefined);
        }
        ~Attribute_Node() override = default;

        // NO COPYING
        Attribute_Node(Attribute_Node const& other) = delete;
        Attribute_Node& operator=(Attribute_Node const& other) = delete;

        // Implicit default move
        //Attribute_Node(Attribute_Node && other) = default;
        //Attribute_Node& operator=(Attribute_Node && other) = default;

    };

    template <typename T>
    Attribute_Node<T>* attribute_node_cast(INode* node_ptr)
    {
        return static_cast<Attribute_Node<T>*>(node_ptr);
    }
    template <typename T>
    Attribute_Node<T> const* attribute_node_cast(INode const* node_ptr)
    {
        return static_cast<Attribute_Node<T> const*>(node_ptr);
    }

} // namespace Saklib

#endif // ATTRIBUTE_NODE_H

