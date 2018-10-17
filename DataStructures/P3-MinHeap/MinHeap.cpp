//
//  MinHeap.cpp
//  MinHeap
//
//  Created by Anne Freeman on 11/2/17.
//  Copyright © 2017 Anne Freeman. All rights reserved.
//

#include <stdio.h>
#include "MinHeap.h"
#include <iostream>
using namespace std;


//function to swap two integers
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Default constructor
MinHeap::MinHeap()
{
    data = new int[50];
    capacity = 15; // starting initial capacity
    numNodes = 0; // start at 1st position
}

//constructor
MinHeap::MinHeap(int cap)
{
    capacity = cap;
    data = new int[capacity]; //dynamically create new array
    numNodes = 0; //start at 1st position
}

//Copy Constructor
MinHeap::MinHeap(const MinHeap &mh)
{
    capacity = mh.capacity;
    numNodes = mh.numNodes;
    data = new int[capacity];
    for (int i = 0; i < capacity; ++i)
    {
        data[i] = mh.data[i];
    }
}

//destructor
MinHeap::~MinHeap()
{
    delete[] data;
}

// Simple Resizing Scheme
// Doubles size of current array
void MinHeap::resize() throw (bad_alloc)
{
    try {
        if (capacity == 0)
        {
            capacity = 1;
        }
        else
        {
            capacity = capacity*2;
        }
    } catch (bad_alloc &bad_alloc_err) {
        cout << "Error allocating memory" << endl;
    }
}

// Method to remove min element (root) of min heap
int MinHeap::remove()
{
    if (numNodes == 0)
        return -32767; //sentinel to indicate empty
    
    if (numNodes == 1)
    {
        numNodes--;
        return data[1];
    }
    
    // Store the minimum value, and remove it from heap
    int root = data[0];
    data[0] = data[numNodes-1];
    numNodes--;
    MinHeapify(0);
    
    return root;
}


// A recursive method to heapify a subtree with root at given index
// This method assumes that the subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < numNodes && data[l] < data[i])
        smallest = l;
    if (r < numNodes && data[r] < data[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&data[i], &data[smallest]);
        MinHeapify(smallest);
    }
}


// use the heapify method of inserting because
// it is worst case O(nlogn)
void MinHeap::insert(int key)
{
    if (numNodes == capacity)
    {
        resize();
        insert(key);
    }
    else
    {
        // insert the key at the end
        numNodes++;
        int i = numNodes-1;
        data[i] = key;
        // Fix the min heap property if it is violated
        while (i != 0 && data[parent(i)] > data[i])
        {
            swap(&data[i], &data[parent(i)]);
            i = parent(i);
        }
    }
}


void MinHeap::print(int i )
{
    if(numNodes == 0)
    {
        //heap is empty
        cout << "There are no items in the heap" << endl;
    }
    else
    {
        cout << " [" << data[i];
        i=i*2+1;
        if(i < numNodes)
        {
            // call recursive function with doubled i
            print(i);
            // increment to get right
            i++;
            if(i < numNodes)
            {
                // call recursive function with left i
                print(i);
                cout << "] ";
            }
            else
            {
                // depth reached
                cout << "]";
            }
        }
        else
        {
            // depth reached
            cout << "]";
        }
    }
    
}
