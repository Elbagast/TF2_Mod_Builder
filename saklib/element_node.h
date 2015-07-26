#ifndef ELEMENT_NODE_H
#define ELEMENT_NODE_H

#include "data_node.h"

namespace Saklib
{
    /*
    Element_Node
    ====================================================================================================
    */
    class Element_Node :
            public Data_Node<Vector<NodeID>>
    {
    public:
        // Special 6
        //============================================================
        Element_Node(NodeID parent_nodeid,
                  String const& name,
                  stored_type const& value):
            Data_Node<Vector<NodeID>>(parent_nodeid, false, name, false, false, value, true)
        {
            assert(!this->name().empty());
        }
        ~Element_Node() override = default;

        // NO COPYING
        Element_Node(Element_Node const& other) = delete;
        Element_Node& operator=(Element_Node const& other) = delete;

        // Implicit default move
        //Element_Node(Element_Node && other) = default;
        //Element_Node& operator=(Element_Node && other) = default;

        // Interface
        //============================================================

        // user data editing functions won't work because the data is set to not be user editable
        // ...but maybe they should be hidden anyway?
    };

} // namespace Saklib

#endif // ELEMENT_NODE_H

