#include "all_nodes.h"

#include "types.h"

#include <QDebug>


void Saklib::test_nodes()
{
    NodeID nodeid1{1};
    Uptr<INode> node1{new Data_Node<Int>(invalid_NodeID(), true, "Some_Name", true, true, 5, true)};
    INode* node1_aid{node1.get()};

    qDebug() << "Node was created:";

    qDebug() << "user_can_destroy = " << node1_aid->user_can_destroy();

    //qDebug() << "nodeid = " << node1_aid->nodeid().value();

    qDebug() << "has_parent = " << node1_aid->has_parent();
    qDebug() << "parent = " << node1_aid->parent().value();
    qDebug() << "user_can_set_parent = " << node1_aid->user_can_set_parent();

    qDebug() << "name = " << node1_aid->name().c_str();
    qDebug() << "user_can_set_name = " << node1_aid->user_can_set_name();

    qDebug() << "never_has_children = " << node1_aid->user_can_set_parent();
    qDebug() << "can_have_children = " << node1_aid->can_have_children();
    qDebug() << "has_children = " << node1_aid->has_children();
    qDebug() << "child_count = " << node1_aid->child_count();

    qDebug() << "Type = " << node1_aid->type_string().c_str();
    qDebug() << "Data = " << node1_aid->data_interface<Int>()->data();


    Saklib::Limited_Access_Data<Vector<Int>> lad_vector{};
    lad_vector.user_push_back(5);
}
