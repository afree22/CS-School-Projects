//
//  Header.h
//  MinHeap
//
//  Created by Anne Freeman on 10/25/17.
//  Copyright © 2017 Anne Freeman. All rights reserved.
//

#ifndef MinHeap_h
#define MinHeap_h
#include <iostream>


class MinHeap
{
private:
    int *data;     // pointer to dynamic array
    int capacity;  // current capacity of dynamic array -- sentinel is in 0th position
                    // so can fit capcity-1 keys after sentinel
    int numNodes;  // number filled in dynamic array, current index of last node
                    // is equal to number of total nodes
    
public:
    // constructor
    MinHeap();
    // with parameters
    MinHeap(int cap);
    //Copy Constructor
    MinHeap(const MinHeap &mh);
    //Destructor
    ~MinHeap();
    
    //Resize Scheme
    void resize() throw (std::bad_alloc);
    // public member functions
    void insert(int key);
    
    // removes min nodes (root) of heap
    int remove();
    // to heapify a subtree with root at index i
    void MinHeapify(int i);
    
    // getter for numNodes
    int getNumNodes(){return numNodes;}
    
    // to get index of parent of node at index i
    int parent(int i) { return (i-1)/2; }
    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }
    
    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }
    
    // prints nodes
    void print(int i);
};



#endif /* Header_h */
