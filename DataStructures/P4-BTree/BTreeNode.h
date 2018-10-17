//
//  BTreeNode.h
//  BTree
//
//  Created by Anne Freeman on 11/16/17.
//  Copyright © 2017 Anne Freeman. All rights reserved.
//

#ifndef BTreeNode_h
#define BTreeNode_h

#include<iostream>
#include <math.h>
using namespace std;

// A BTree node
class BTreeNode
{
    int *keys;             // An array of keys
    int maxPointers;       // Maximum number of pointers in the node
    int maxKeys;           // Minimum number of pointers in the node
    int minKeys;           // Minimum number of keys in the node
    int minPointers;       // Minimum number of pointers in the node
    BTreeNode **children;  // pointer to an array of pointers
    int keyCount;          // keeps track of number of keys in each node
    bool leaf;             // is true when node is leaf -- if node is internal than false
    
public:
    
    // Constructor for BTreeNode
    BTreeNode(int minPt, int maxPt, bool leaf_val);
    
    // Function to return index of first key that is >= k
    int findKey(int k);
    
    // Function to insert new key into a non-full node
    void insertNonFull(int k);
    
    // Function to split the child node full_node
    void splitChild(int i, BTreeNode *full_node);
    
    // Function to remove key from any part of the subtree of the caller
    void remove(int k);
    
    // Function to remove key present at index from a non-leaf
    void removeFromNonLeaf(int index);
    
    // Function to add keys to the node children[index] if that child has less than
    // minKeys keys
    void addKeys(int index);
    
    // Function to merge a child with its sibling
    void merge(int index);
    
    // This makes BTree a friend so that the private members of this class are accessible
    // in BTree functions -- don't need getters/setters
    friend class BTree;
};



//Constructor for BTreeNode
BTreeNode::BTreeNode(int minPt, int maxPt, bool leaf_val)
{
    minPointers = minPt;
    minKeys = minPointers -1;
    leaf = leaf_val;
    maxPointers = maxPt;
    maxKeys = maxPointers -1;
    
    keys = new int[maxKeys];
    children = new BTreeNode *[maxPointers];
    
    keyCount = 0;
}

// Function to return index of first key that is >= k
int BTreeNode::findKey(int k)
{
    int index=0;
    while (index<keyCount && keys[index] < k)
        ++index;
    return index;
}

// Function to insert new key into a non-full node
void BTreeNode::insertNonFull(int k)
{
    // Initialize index as index of rightmost element
    int i = keyCount-1;
    
    // check if leaf node
    if (leaf == true)
    {
        // Loop to find location of new key and move
        // all greater keys to appropriate position one place ahead
        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }
        
        // Insert the new key at correct location
        keys[i+1] = k;
        keyCount = keyCount+1;
    }
    // otherwise it is not a leaf node
    // need to continue traversal to leaf node
    else
    {
        // Find the appropriate child for the new key
        while (i >= 0 && keys[i] > k)
            i--;
        
        // Determine if the child is full
        if (children[i+1]->keyCount == maxPointers-1)
        {
            // If the child is full, split it
            splitChild(i+1, children[i+1]);
            
            // Determine which of the two is going to have the new key
            if (keys[i+1] < k)
                i++;
        }
        // insert k into non-full node
        children[i+1]->insertNonFull(k);
    }
}


// Function to split the child node full_node
void BTreeNode::splitChild(int i, BTreeNode *full_node)
{
    BTreeNode *new_node = new BTreeNode(full_node->minPointers, maxPointers, full_node->leaf);
    //new_node->keyCount = minKeys;
    if(maxPointers%2 == 0) // if even
    {
        new_node->keyCount = minKeys;
    }
    else if(maxPointers%2 == 1) // if odd
    {
        new_node->keyCount = minKeys-1;
    }
    
    // Copy keys of full_node to new_node
    for (int j = 0; j < minKeys; j++)
        new_node->keys[j] = full_node->keys[j+minPointers];
    
    // Copy children of full_node to new_node
    if (full_node->leaf == false)
    {
        for (int j = 0; j < minPointers; j++)
            new_node->children[j] = full_node->children[j+minPointers];
    }
    
    full_node->keyCount = minKeys;
    
    // Create space for new child in this node
    for (int j = keyCount; j >= i+1; j--)
        children[j+1] = children[j];
    
    children[i+1] = new_node;
    
    // Adjust keys to make space for key from full_node
    for (int j = keyCount-1; j >= i; j--)
        keys[j+1] = keys[j];
    
    // Copy the middle key of full_node to keys[]
    keys[i] = full_node->keys[minKeys];
    
    keyCount = keyCount + 1;

    
}


// Function to remove key from any part of the subtree of the caller
void BTreeNode::remove(int k)
{
    int index = findKey(k);
    
    // The key to be removed is present in this node
    if (index < keyCount && keys[index] == k)
    {
        if (leaf)
        {
            // Node is a leaf node
            // Can delete key inside the node immediately
            
            // Re-adjust the keys
            for (int i=index+1; i<keyCount; ++i)
            {
                // move all keys after (index) one place backward
                keys[i-1] = keys[i];
            }
            
            // Decrement keyCount (account for remove)
            keyCount--;
        }
        else
        {
            // node is not a leaf node -- must continue down the tree
            // checking each node along the way to see if it violates B-Tree
            // call removeFromNonLeaf function
            removeFromNonLeaf(index);
        }
    }
    // Key to be removed is not present in this node
    else
    {
        // If this node is a leaf node, then key is not in tree
        if (leaf)
        {
            cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }
        // Otherwise the key to be removed is present in the subtree
        
        // The flag indicates whether the key is present in the subtree
        // rooted within the last child of this node.
        bool flag = ( (index==keyCount)? true : false );
        
        
        if (children[index]->keyCount < minPointers)
        {
            // If the child where the key is supposed to be has less the minPointers keys,
            // then add keys to that child
            addKeys(index);
        }
        
        if (flag && index > keyCount)
        {
            // If the last child has been merged, it will have been merged with
            // the previous child --> continue to call remove function
            // with (index-1)th child
            children[index-1]->remove(k);
        }
        else
        {
            // Otherwise call remove function with (index)th child
            // which will now have at least minPointers
            children[index]->remove(k);
        }
    }
}

// Function to remove key present at index from non-leaf
void BTreeNode::removeFromNonLeaf(int index)
{
    
    int k = keys[index];
    
    // If the child that precedes k (children[index]) has at least minPointers
    // find the predecessor of k and replace k by pred.
    // Recursively delete pred in children[index]
    if (children[index]->keyCount >= minPointers)
    {
        // Find predecessor node
        BTreeNode *cur=children[index];
        while (!cur->leaf)
            cur = cur->children[cur->keyCount];
        
        int predecessor = cur->keys[cur->keyCount-1];
        
        keys[index] = predecessor;
        children[index]->remove(predecessor);
    }
    
    // If the child children[index] has less than minPointers, examine children[index+1]
    // If children[index+1] has at least minPointers
    // find the successor of k and replace k by succ
    // Recursively delete succ in children[index+1]
    else if  (children[index+1]->keyCount >= minPointers)
    {
        // Find Successor Node
        BTreeNode *cur = children[index+1];
        while (!cur->leaf)
            cur = cur->children[0];
        
        int successor = cur->keys[0];
        keys[index] = successor;
        children[index+1]->remove(successor);
    }
    
    // If both children[index] and children[index+1] has less than minPointers,
    // merge k and all of children[index+1] into children[index]
    // Now children[index] contains 2(minPointers)-1 keys
    else
    {
        merge(index);
        children[index]->remove(k);
    }
    return;
}



// Function to add keys to the node children[index] if that child has less than
// minKeys keys
void BTreeNode::addKeys(int index)
{
    
    // If the previous child(children[index-1]) has more than minKeys keys,
    // borrow a key from that child
    if (index!=0 && children[index-1]->keyCount>=minPointers)
    {
        BTreeNode *child=children[index];
        BTreeNode *sibling=children[index-1];
        
        // The last key from children[index-1] is promoted to the parent and key[index-1]
        // from parent is demoted to the first key in children[index]. Thus, the  loses
        // sibling one key and child gains one key
        
        // Moving all key in children[index] one step ahead
        for (int i=child->keyCount-1; i>=0; --i)
            child->keys[i+1] = child->keys[i];
        
        // If children[index] is not a leaf, move all its child pointers one step ahead
        if (!child->leaf)
        {
            for(int i=child->keyCount; i>=0; --i)
                child->children[i+1] = child->children[i];
        }
        
        // Setting child's first key equal to keys[index-1] from the current node
        child->keys[0] = keys[index-1];
        
        // Moving sibling's last child as children[index]'s first child
        if (!leaf)
            child->children[0] = sibling->children[sibling->keyCount];
        
        // Moving the key from the sibling to the parent
        // This reduces the number of keys in the sibling
        keys[index-1] = sibling->keys[sibling->keyCount-1];
        
        child->keyCount += 1;
        sibling->keyCount -= 1;
    }
    
    // If the next child(children[index+1]) has more than minKeys keys,
    // borrow a key from that child
    else if (index!=keyCount && children[index+1]->keyCount>=minPointers)
    {
        BTreeNode *child=children[index];
        BTreeNode *sibling=children[index+1];
        
        // keys[index] is inserted as the last key in children[index]
        child->keys[(child->keyCount)] = keys[index];
        
        // Sibling's first child becomes the last child of children[index]
        if (!(child->leaf))
            child->children[(child->keyCount)+1] = sibling->children[0];
        
        //The first key from sibling is inserted into keys[index]
        keys[index] = sibling->keys[0];
        
        // Shifting the keys in the sibling one step down
        for (int i=1; i<sibling->keyCount; ++i)
            sibling->keys[i-1] = sibling->keys[i];
        
        // Shifting the child pointers one step down
        if (!sibling->leaf)
        {
            for(int i=1; i<=sibling->keyCount; ++i)
                sibling->children[i-1] = sibling->children[i];
        }
        
        //Adjust keyCounts
        child->keyCount += 1;
        sibling->keyCount -= 1;
    }
    
    else
    {
        if (index != keyCount)
        {
            // if children[index] isn't the last child, merge with it's next sibling
            merge(index);
        }
        else
        {
            // if it is the last child, merge with it's previous sibling
            merge(index-1);
        }
    }
    return;
}

// Function to merge a child with its sibling
void BTreeNode::merge(int index)
{
    BTreeNode *child = children[index];
    BTreeNode *sibling = children[index+1];
    
    // Inserting key from current node into (minKeys)th position
    child->keys[minKeys] = keys[index];
    
    // Copying the keys from children[index+1] to children[index] at the end
    for (int i=0; i<sibling->keyCount; ++i)
        child->keys[i+minPointers] = sibling->keys[i];
    
    // Copy the child pointers - if not leaf
    if (!child->leaf)
    {
        for(int i=0; i<=sibling->keyCount; ++i)
            child->children[i+minPointers] = sibling->children[i];
    }
    
    // Adjust keys after index in the current node to fill the gap
    for (int i=index+1; i<keyCount; ++i)
        keys[i-1] = keys[i];
    
    // Adjust the child pointers
    for (int i=index+2; i<=keyCount; ++i)
        children[i-1] = children[i];
    
    // Update the keyCount
    child->keyCount += sibling->keyCount+1;
    keyCount--;
    
    delete(sibling);
    return;
}


#endif /* BTreeNode_h */
