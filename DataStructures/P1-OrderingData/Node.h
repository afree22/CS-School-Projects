//
//  Node.h
//  aof7P1
//
//  Created by Anne Freeman on 10/3/18.
//  Copyright © 2018 Anne Freeman. All rights reserved.
//

#ifndef Node_h
#define Node_h

class Node
{
public:
    int data;
    Node * next;
    Node(int, Node *);
};


Node::Node(int value, Node * nextNode)
{
    data = value;
    next = nextNode;
}

#endif /* Node_h */
