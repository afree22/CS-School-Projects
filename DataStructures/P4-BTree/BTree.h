//
//  BTree.h
//  BTree
//
//  Created by Anne Freeman on 11/16/17.
//  Copyright © 2017 Anne Freeman. All rights reserved.
//

#ifndef BTree_h
#define BTree_h
#include <cmath>
#include "BTreeNode.h"

class BTree
{
    BTreeNode *root;  // Pointer to root node
    int minPtrs;      // Minimum number of keys for a node
    int maxDegree;    // Maximum Degree
public:
    // Constructor
    BTree(int md);
    
    // print function that is called from main
    void print();
    void print_help(BTreeNode *node);
    void print_help(BTreeNode *node, int level);
    // prints out the BTreeNodes by level
    void print_level(BTreeNode *node, int level);
    
    // Function to insert key in BTree by calling splitChild and insertNonFull
    // functions in BTreeNode class
    void insert(int k);
    
    // Function to remove key from BTree by calling remove() function in
    // BTreeNode Class
    void remove(int k);
};

BTree::BTree(int md)
{
    root = NULL;
    maxDegree = md;
    minPtrs = ceil(md/2.0);
}



//void BTree::print()
//{
//    if (root == NULL)
//    {
//        std::cout << "CANNOT PRINT: TREE IS EMPTY"  << std::endl;
//        return;
//    }
//    else
//    {
//        print_help(root);
//    }
//}
//
//void BTree::print_help(BTreeNode *node)
//{
//    cout << "[";
//    if(node==NULL)
//    {
//        return;
//    }
//    for(int i = 0; i < node->keyCount; i++)
//    {
//        cout << node->keys[i];
//        if(i+1 < node->keyCount)
//            cout <<",";
//    }
//    if(node->leaf == false)
//    {
//        for(int j = 0; j < node->maxPointers-1; j++)
//        {
//            if(node->children[j] != NULL)
//            {
//                print_help(node->children[j]);
//            }
//        }
//    }
//    cout << "]";
//}







void BTree::print()
{
    //empty tree
    if (root == NULL)
    {
        std::cout << "CANNOT PRINT: TREE IS EMPTY"  << std::endl;
        return;
    }

    //find the height of the b-tree
    int height = 0;
    BTreeNode *ptr;
    ptr = root;
    while (ptr->children[0] != NULL)
    {
        ptr = ptr->children[0];
        height++;
    }

    //print out the elements recursively for each level/height
    std::cout << "Printing in level-order" << std::endl;
    for (int i = 0; i <= height; i++)
    {
        std::cout << "Depth " << i << "---->";
        print_help(root, i);
        std::cout << std::endl;
    }
}


void BTree::print_help(BTreeNode *node, int level)
{
    if (node == NULL)
    {
        return;
    }
    if (level == 0)
    {
        std::cout << "  |";
        for (int i = 0; i < node->keyCount; i++)
        {
            std::cout << node->keys[i];
            if(i<node->keyCount-1)
            {
                std::cout << "  ";
            }
        }
        std::cout << "|  ";
    }
    else if (level > 0)
    {
        for (int i = 0; i <= node->keyCount; i++)
        {
            print_help(node->children[i], level-1);
        }
    }
}
















// Function to insert key in BTree by calling splitChild and insertNonFull
// functions in BTreeNode class
void BTree::insert(int k)
{
    // If tree is empty -- root is NULL
    if (root == NULL)
    {
        root = new BTreeNode(minPtrs, maxDegree, true);
        // Insert key at first position
        root->keys[0] = k;
        root->keyCount = 1;
    }
    else // Tree is not empty
    {
        // If root is full -- tree grows in height
        if (root->keyCount == maxDegree-1)
        {
            // Allocate memory for new root
            BTreeNode *new_root = new BTreeNode(minPtrs, maxDegree, false);
            
            // The old root will be the child of the new root
            new_root->children[0] = root;
            
            // Split the old root and promote median key to the new root
            new_root->splitChild(0, root);
            
            // New root has two children now
            // Decide which should have the key k
            int i = 0;
            if (new_root->keys[0] < k)
            {
                i++;
            }
            
            // insert key into child -- know child isn't full because split
            new_root->children[i]->insertNonFull(k);
            
            // Change root to the new root
            root = new_root;
        }
        else  // Root is not full
        {
            //call insertNonFull function in the BTreeNode class for the root
            root->insertNonFull(k);
        }
    }
}

// Function to remove key from BTree by calling remove() function in
// BTreeNode Class
void BTree::remove(int k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }
    
    // Call the remove function for root BTreeNode
    root->remove(k);
    
    if (root->keyCount==0) //If root has 0 keys
    {
        BTreeNode *tmp = root;
        if (root->leaf)
        {
            // If root has no children (it is a leaf), set root to NULL
            root = NULL;
        }
        else
        {
            // Make root's first child as the new root
            root = root->children[0];
        }
        delete tmp;
    }
    return;
}

#endif /* BTree_h */

