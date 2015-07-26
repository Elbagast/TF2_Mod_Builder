#ifndef DATA_NODE_H
#define DATA_NODE_H

#include "node_children_impl.h"

namespace Saklib
{
    /*
    Data_Node<T>
    ====================================================================================================
    Simple INode full class that stores a given
    */
    template <typename T>
    class Data_Node :
            public Node_Children_Impl<T>
    {
    public:
        // Special 6
        //============================================================
        Data_Node(NodeID parent_nodeid,
                  bool parent_is_editable,
                  String const& name,
                  bool name_is_editable,
                  bool user_can_destroy,
                  stored_type const& value,
                  bool value_is_editable):
            Node_Children_Impl<T>(parent_nodeid,
                                  parent_is_editable,
                                  name,
                                  name_is_editable,
                                  user_can_destroy,
                                  value,
                                  value_is_editable)
        {}
        ~Data_Node() override = default;

        // NO COPYING
        Data_Node(Data_Node const& other) = delete;
        Data_Node& operator=(Data_Node const& other) = delete;

        // Implicit default move
        //Data_Node(Data_Node && other) = default;
        //Data_Node& operator=(Data_Node && other) = default;

    };

} // namespace Saklib


#endif // DATA_NODE_H

