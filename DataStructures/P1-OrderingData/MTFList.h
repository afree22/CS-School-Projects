//
//  MTFList.cpp
//  aof7P1
//
//  Created by Anne Freeman on 9/28/18.
//  Copyright © 2018 Anne Freeman. All rights reserved.
//

#ifndef MTFLIST_H
#define MTFLIST_H

#include <fstream>
#include <string>
#include <iostream>
#include "Node.h"
using namespace std;

class MTFList
{
public:
    MTFList();
    MTFList(string);
    ~MTFList();
    int sequentialSearch(int);
    void print();
    
private:
    Node *head;
    int size;
};


// Default constructor
MTFList::MTFList()
{
    size = 0;
    head = NULL;
}

// Constructor
MTFList::MTFList(string fileName)
{
    head = NULL;
    size = 0;

    ifstream inFile;
    int element;
    inFile.open(fileName.c_str());
    
    if(!inFile)
    {
        cout << "Error opening file" << endl;
    }
    else{
        inFile >> size;
        for(int i = 0; i < size+1; i++)
        {
            inFile >> element;
            if(head == NULL)
            {
                head = new Node(element, NULL);
            }
            else{
                Node *temp = new Node(element, head);
                temp->next = head;
                head = temp;
            }
        }
        
        inFile.close();
    }
    
}


int MTFList::sequentialSearch(int query)
{
    Node *current = head;
    Node *prev = current;
    while(current != NULL)
    {
        if (current->data == query)
        {
            if(current != prev)
            {
                prev->next = current->next;
                current->next = head;
                head = current;
            }
            return 1;
        }
        
        prev = current;
        current = current->next;
    }
    return 0;
}

// Destructor
MTFList::~MTFList()
{
    while(head != NULL)
    {
        Node * temp = head;
        head = head->next;
        delete temp;
    }
}

#endif // MTFLIST
