//
//  OrderedList.cpp
//  aof7P1
//
//  Created by Anne Freeman on 9/28/18.
//  Copyright © 2018 Anne Freeman. All rights reserved.
//

#ifndef ORDERED_LIST
#define ORDERED_LIST

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class OrderedList
{
public:
    OrderedList(string fileName);
    ~OrderedList();
    void mergeSort(int[], int, int);
    void merge(int[], int, int, int);
    int binarySearch(int);
    void print();
    
private:
    int *orderedList;
    int size;
};

// Constructor -- reads in the file and calls mergeSort
OrderedList::OrderedList(string fileName)
{
    ifstream inFile;
    
    inFile.open(fileName.c_str());
    
    // reads in the size (first line in file)
    inFile >> size;
    
    // allocates memory for dynamic array
    int *temp = new int[size];
    
    for(int i = 0; i < size; i++)
    {
        inFile >> temp[i];
    }
    
    orderedList = temp;
    inFile.close();
    
    // sort array after create it
    mergeSort(orderedList, 0, size-1);
}


// Destructor
OrderedList::~OrderedList()
{
    delete []orderedList;
}


void OrderedList::mergeSort(int data[], int first, int last)
{
    if (first < last)
    {
        int mid = (first + last) / 2;
        mergeSort(data, first, mid);
        mergeSort(data, mid+1, last);
        merge(data, first, mid, last);
    }
}

// Merge is called by mergesort
void OrderedList::merge(int data[], int first, int mid, int last)
{
    int leftLength = mid - first + 1;
    int rightLength =  last - mid;
    
    // Creates temp arrays for left and right half of array.
    int L[leftLength], R[rightLength];
    
    // Copies data from array to left and right halves.
    for (int i = 0; i < leftLength; i++)
    {
        L[i] = data[first + i];
    }
    for (int j = 0; j < rightLength; j++) {
        R[j] = data[mid + 1 + j];
    }
    
    // Resets iterators
    int i = 0;
    int j = 0;
    int k = first;
    
    // Merges temp arrays back into main array.
    while (i < leftLength && j < rightLength)
    {
        if (L[i] <= R[j])
        {
            data[k] = L[i];
            i++;
        }
        else
        {
            data[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Load remaining elements from left array.
    for (i; i < leftLength; i++, k++)
    {
        data[k] = L[i];
    }
    
    // Load remaining elements from right array.
    for (j; j < rightLength; j++, k++)
    {
        data[k] = R[j];
    }
}



int OrderedList::binarySearch(int query)
{
    int low = 0;
    int mid;
    int high = size - 1;
    
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (query < orderedList[mid])
        {
            high = mid - 1;
        }
        else if (query > orderedList[mid])
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}



void OrderedList::print()
{
    for (int i = 0; i < size; i++)
    {
        cout << orderedList[i] << " ";
    }
    cout << endl;
}


#endif // ORDERED_LIST













