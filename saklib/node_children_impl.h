#ifndef NODE_CHILDREN_IMPL_H
#define NODE_CHILDREN_IMPL_H

#include "node_data_impl.h"

namespace Saklib
{
    /*
    Node_Children_Impl<T>
    ====================================================================================================
    Intermediate class to implement Node children specific operations. This separates out the
    specialisations for NodeID storing nodes.
    */
    template <typename T>
    class Node_Children_Impl :
            public Node_Data_Impl<T>
    {
    public:
        // Special 6
        //============================================================
        Node_Children_Impl(NodeID parent_nodeid,
                  bool parent_is_editable,
                  String const& name,
                  bool name_is_editable,
                  bool user_can_destroy,
                  stored_type const& value,
                  bool value_is_editable):
            Node_Data_Impl<T>(parent_nodeid, parent_is_editable, name, name_is_editable, user_can_destroy, value, value_is_editable)
        {}
        ~Node_Children_Impl() override = default;

        // NO COPYING
        Node_Children_Impl(Node_Children_Impl const& other) = delete;
        Node_Children_Impl& operator=(Node_Children_Impl const& other) = delete;

        // Implicit default move
        //Node_Children_Impl(Node_Children_Impl && other) = default;
        //Node_Children_Impl& operator=(Node_Children_Impl && other) = default;

        // Virtual Interface
        //============================================================

        // Children
        bool never_has_children() const override    { return true; }
        bool can_have_children() const override     { return false; }
        //Child_Interface_Enum child_interface_enum() const override = 0;
        bool has_children() const override          { return false; }
        size_type child_count() const override      { return 0; }
        Vector_NodeID children() const override     { return Vector_NodeID(); }
    };


    /*
    Node_Children_Impl<NodeID>
    ====================================================================================================
    */
    template <>
    class Node_Children_Impl<NodeID > :
            public Node_Data_Impl<NodeID>
    {
    public:
        // Special 6
        //============================================================
        Node_Children_Impl(NodeID parent_nodeid,
                  bool parent_is_editable,
                  String const& name,
                  bool name_is_editable,
                  bool user_can_destroy,
                  stored_type const& value,
                  bool value_is_editable):
            Node_Data_Impl<NodeID>(parent_nodeid, parent_is_editable, name, name_is_editable, user_can_destroy, value, value_is_editable)
        {}
        ~Node_Children_Impl() override = 0 {}

        // NO COPYING
        Node_Children_Impl(Node_Children_Impl const& other) = delete;
        Node_Children_Impl& operator=(Node_Children_Impl const& other) = delete;

        // Implicit default move
        //Node_Children_Impl(Node_Children_Impl && other) = default;
        //Node_Children_Impl& operator=(Node_Children_Impl && other) = default;

        // Virtual Interface
        //============================================================

        // Children
        bool never_has_children() const override    { return false; }
        bool can_have_children() const override     { return true; }
        //Child_Interface_Enum child_interface_enum() const override = 0;
        bool has_children() const override          { return data().is_valid(); }
        size_type child_count() const override      { return (data().is_valid() ? 1 : 0); }
        Vector_NodeID children() const override
        {
            Vector_NodeID result{};
            if (data().is_valid())
            {
                result.reserve(1);
                result.push_back(data());
            }
            return result;
        }
    };

    /*
    Node_Children_Impl<Vector<NodeID>>
    ====================================================================================================
    */
    template <>
    class Node_Children_Impl<Vector<NodeID> > :
            public Node_Data_Impl<Vector<NodeID> >
    {
    public:
        // Special 6
        //============================================================
        Node_Children_Impl(NodeID parent_nodeid,
                  bool parent_is_editable,
                  String const& name,
                  bool name_is_editable,
                  bool user_can_destroy,
                  stored_type const& value,
                  bool value_is_editable):
            Node_Data_Impl<Vector<NodeID> >(parent_nodeid, parent_is_editable, name, name_is_editable, user_can_destroy, value, value_is_editable)
        {}
        ~Node_Children_Impl() override = 0 {}

        // NO COPYING
        Node_Children_Impl(Node_Children_Impl const& other) = delete;
        Node_Children_Impl& operator=(Node_Children_Impl const& other) = delete;

        // Implicit default move
        //Node_Children_Impl(Node_Children_Impl && other) = default;
        //Node_Children_Impl& operator=(Node_Children_Impl && other) = default;

        // Virtual Interface
        //============================================================

        // Children
        bool never_has_children() const override    { return true; }
        bool can_have_children() const override     { return false; }
        //Child_Interface_Enum child_interface_enum() const override = 0;
        bool has_children() const override          { return false; }
        size_type child_count() const override      { return size(); }
        Vector_NodeID children() const override     { return vector(); }
    };

} // namespace Saklib

#endif // NODE_CHILDREN_IMPL_H

