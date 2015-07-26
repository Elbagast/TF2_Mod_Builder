#ifndef INODE_H
#define INODE_H

#include "types.h"
#include "nodeid.h"


namespace Saklib
{
    template <typename T>
    class IData;
    /*
    INode
    ====================================================================================================
    Class which describes the interface that all Node objects must implement. This should include all
    the generic data and operations that can be done with Nodes.
    */
    class INode
    {
    public:
        virtual ~INode() = 0;

        // Virtual Interface
        //============================================================

        // Lifetime
        //------------------------------------------------------------
        virtual bool user_can_destroy() const = 0;
        virtual void set_user_can_destroy(bool state) = 0;

        // This Node's id
        //virtual NodeID nodeid() const = 0;
        //virtual void set_nodeid(NodeID new_id) = 0;

        // Root Status
        //------------------------------------------------------------
        //virtual bool can_be_root() const = 0;
        //virtual void set_can_be_root(bool state) = 0;
        //virtual bool user_set_can_be_root(state bool) = 0;
        //virtual bool user_can_set_can_be_root() const = 0;
        //virtual void set_user_can_set_can_be_root(bool state) = 0;

        // Editing Lock (for everything)
        //------------------------------------------------------------
        //virtual bool is_editable() = 0;
        //virtual void set_is_editable(state bool) = 0;
        //virtual bool user_set_is_editable(state bool) = 0;
        //virtual bool user_can_set_is_editable() const = 0;
        //virtual void set_user_can_set_is_editable(bool state) = 0;


        // Parent
        //------------------------------------------------------------
        virtual bool has_parent() const = 0;
        virtual NodeID parent() const = 0;
        virtual void set_parent(NodeID new_parentid) = 0;
        virtual bool user_set_parent(NodeID new_parentid) = 0;
        virtual bool user_can_set_parent() const = 0;
        virtual void set_user_can_set_parent(bool state) = 0;

        // Name
        //------------------------------------------------------------
        virtual String const& name() const = 0;
        virtual void set_name(String const& new_name) = 0;
        virtual bool user_can_set_name() const = 0;
        virtual bool user_set_name(String const& new_name) = 0;
        virtual void set_user_can_set_name(bool state) = 0;

        // Children
        //------------------------------------------------------------
        virtual bool never_has_children() const = 0;
        virtual bool can_have_children() const = 0;
        //virtual Child_Interface_Enum child_interface_enum() const = 0;
        virtual bool has_children() const = 0;
        virtual size_type child_count() const = 0;
        virtual Vector_NodeID children() const = 0;

        // Data
        //------------------------------------------------------------
        //virtual Type_Enum type_enum() const = 0;
        //virtual String type_string() const = 0;
        //virtual bool user_can_set_data() const = 0;
        //virtual void set_user_can_set_data(bool state) = 0;

        template <typename T>
        IData<T>* data_interface()
        {
            return dynamic_cast<IData<T>*>(this);
        }
        template <typename T>
        IData<T> const* data_interface() const
        {
            return dynamic_cast<IData<T> const*>(this);
        }
    };

} // namespace Saklib

Saklib::INode::~INode() = default;

#endif // INODE_H

