#ifndef NODE_H
#define NODE_H

#include "types.h"
#include "nodeid.h"

namespace Saklib
{
    enum class Data_Type_Enum
    {
        Undefined = 0,
        NodeID,
        Int,
        Vector_NodeID,
        Vector_Int
    };

    template <typename T>
    Data_Type_Enum enum_type_of();

    class Data
    {
    protected:
        virtual ~Data() = default;
    };

    template <typename T>
    class Data_Type
    {
    public:
        Data_Type(T const& value = T()) :
            m_value(value)
        {}
        ~Data_Type() override = default;

        T const& get_value() const
        {
            return m_value;
        }
        void set_value(T const& value)
        {
            m_value = value;
        }
    private:
        T m_value;
    };

    template <typename T>
    class Data_Type<Vector<T>>
    {
    public:
        Data_Type(Vector<T> const& vector = Vector<T>()):
            m_vector(value)
        {}
        ~Data_Type() override = default;

        Vector<T> const& get_vector() const
        {
            return m_vector;
        }
        void set_vector(Vector<T> const& vector)
        {
            m_vector = vector;
        }

        bool is_empty() const
        {
            return m_vector.empty();
        }
    private:
        Vector<T> m_vector;
    };

    Uptr<Data> make_Data_Type(Data_Enum data_type);

    enum class Node_Type_Enum
    {
        Node,
        Attribute,
        Element
    };

    /*
    Node
    ====================================================================================================

    */
    class Node
    {
    protected:
        // Special 6
        //============================================================
        Node(NodeID parent,
             bool parent_is_editable,
             String const& name,
             bool name_is_editable,
             Node_Type_Enum node_type_enum,
             String const& node_type_string,
             bool data_is_user_editable,
             Data_Type_Enum data_type_enum,
             //String const& data_type_string,
             Uptr<Data>&& data):
            m_parent(parent),
            m_parent_is_user_editable(parent_is_editable),
            m_name(name),
            m_name_is_user_editable(name_is_editable),
            m_node_type_enum(node_type_enum),
            m_node_type_string(node_type_string),
            m_data_is_user_editable(data_is_user_editable),
            m_data_type_enum(data_type_enum),
            //m_data_type_string(data_type_string),
            m_data(data.release())
        {
            assert(m_data);
        }

        virtual ~Node() = default;

        // Internal Interface
        //============================================================
        // set members without checks
        void force_set_parent(NodeID value)
        {
            m_parent = value;
        }
        void force_set_name(String const& value)
        {
            m_name = value;
        }

    public:
        // Public Interface
        //============================================================
        bool can_have_children() const
        {
            return m_data_type_enum == Data_Type_Enum::NodeID || m_data_type_enum == Data_Type_Enum::Vector_NodeID;
        }
        bool has_children() const
        {
            if (m_data_type_enum == Data_Type_Enum::NodeID)
            {
                return get_data_cast<NodeID>().get_value().is_valid();
            }
            else if(m_data_type_enum == Data_Type_Enum::Vector_NodeID)
            {
                for (auto nodeid : get_data_cast<Vector_NodeID>().get_vector())
                {
                    if (nodeid.is_valid())
                    {
                        return true;
                    }
                }
                return false;
            }
            else
            {
                return false;
            }
        }
        size_type get_child_count() const
        {
            if (m_data_type_enum == Data_Type_Enum::NodeID && get_data_cast<NodeID>().get_value().is_valid())
            {
                return 1;
            }
            else if(m_data_type_enum == Data_Type_Enum::Vector_NodeID && !get_data_cast<Vector_NodeID>().is_empty())
            {
                auto const& vector = get_data_cast<Vector_NodeID>().get_vector();
                size_type result{0};
                for (auto nodeid : vector)
                {
                    if (nodeid.is_valid())
                    {
                        ++result;
                    }
                }
                return result;
            }
            else
            {
                return 0;
            }
        }
        //size_type get_valid_child_count() const;

        bool parent_is_user_editable() const
        {
            return m_parent_is_user_editable;
        }
        bool has_parent() const
        {
            return m_parent.is_valid();
        }
        NodeID get_parent() const
        {
            return m_parent;
        }
        void set_parent(NodeID value)
        {
            if (m_parent_is_user_editable)
                m_parent = value;
        }

        String const& get_name() const
        {
            return m_name;
        }
        bool name_is_user_editable() const
        {
            return m_name_is_user_editable;
        }
        void set_name(String const& value)
        {
            if (m_name_is_user_editable)
                m_name = value;
        }

        Node_Type_Enum get_node_type_enum() const
        {
            return m_node_type_enum;
        }
        String const& get_node_type_string() const
        {
            return m_node_type_string;
        }
        bool is_composite_type() const
        {
            return !m_composite_type.empty();
        }

        bool data_is_user_editable() const
        {
            return m_data_is_user_editable;
        }
        Data_Type_Enum get_data_type() const
        {
            return m_data_type_enum;
        }
        /*
        Data* get_data()
        {
            return m_data.get();
        }
        Data const* get_data() const
        {
            return m_data.get();
        }
        */
        template <typename T>
        Data_Type<T>& get_data_cast()
        {
            return *static_cast<Data_Type<T>*>(m_data.get());
        }
        template <typename T>
        Data_Type<T> const& get_data_cast() const
        {
            return *static_cast<Data_Type<T>*>(m_data.get());
        }

    private:
        // Data Members
        //============================================================
        NodeID m_parent;
        bool m_parent_is_user_editable;
        String m_name;
        bool m_name_is_user_editable;
        Node_Type_Enum m_node_type_enum;
        String m_node_type_string;
        bool m_data_is_user_editable;
        Data_Type_Enum m_data_type_enum;
        //String m_data_type_string;
        Uptr<Data> m_data;
    };

    /*
    Attribute_Node<T>
    ====================================================================================================
    Node subclass that contains a data value.
    */
    template <typename T>
    class Attribute_Node:
            public Node
    {
    public:
        // Special 6
        //============================================================
        Attribute_Node(NodeID parent, String const& name, T const& value = T()):
            Node(parent,
                 false,
                 name,
                 false,
                 Node_Type_Enum::Attribute,
                 "Attribute_Node",
                 true,
                 enum_type_of<T>(),
                 std::make_unique<Data>(new Data_Type<T>(value))),
            mr_true_data(get_data_cast<T>())
        {
        }
        ~Attribute_Node() override = default;

        // Public Interface
        //============================================================

        // forwarding functions to Data_Type<T>

    private:
        // Data Members
        //============================================================
        Data_Type<T>& mr_true_data;
    };

    /*
    Element_Node
    ====================================================================================================
    Node subclass that contains a Vector_NodeID that contains only Attribute_Nodes
    */
    class Element_Node:
            public Node
    {
    public:
        Element_Node(String const& name, String const& element_type_string, NodeID parent = invalid_NodeID()):
            Node(parent,
                 true,
                 name,
                 true,
                 Node_Type_Enum::Element,
                 element_type_string,
                 false,
                 enum_type_of<T>(),
                 std::make_unique<Data>(new Data_Type<T>(value))),
            mr_attributes(get_data_cast<Vector<NodeID>>()->get_value())
        {
        }
        ~Element_Node() override = default;

        // Public Interface
        //============================================================
        // Attribute access....

    private:
        Vector_NodeID& mr_attributes;
    };

} // namespace Saklib

#endif // NODE_H
