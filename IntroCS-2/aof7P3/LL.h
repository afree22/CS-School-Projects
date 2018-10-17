
/*
 * LL.h
 *
 * COSC 052 Fall 2016
 * Project #3
 *
 * Due on: NOV 1, 2016
 * Author: Anne Freeman
 *
 *
 * In accordance with the class policies and Georgetown's
 * Honor Code, I certify that, with the exception of the
 * class resources and those items noted below, I have neither
 * given nor received any assistance on this project.
 *
 * References not otherwise commented within the program source code.
 * Note that you should not mention any help from the TAs, the professor,
 * or any code taken from the class textbooks.
 */


#ifndef LL_h
#define LL_h

#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <exception>
#include <stdexcept>
using std::ostream;
using std::string;
using std::out_of_range;
using std::ostringstream;


template <typename T>
class Node
{
public:
    T info;
    Node<T> *next;
    Node(T = T(), Node<T>* = NULL);
};
template <typename T>
Node<T>::Node(T val, Node<T> *ptr)
{
    info = val;
    next = ptr;
}

template <typename T>
class LL
{
    template <typename F>
    friend ostream& operator <<(ostream &os, const LL<F> &rhsObj);
private:
    unsigned long count;
    Node<T> *head;
    
    //CopyList is a private function called by both
    // copy constructor and overloaded = operator
    void copylist(const LL<T> &listToCopy);
    
public:
    LL();
    ~LL();
    
    //copy constructor
    LL(const LL<T> &otherLL);
    
    //overloaded = operator
    LL<T> &operator=(const LL<T> &rhsObj);
    void push_back(T);
    void insert(T);
    void pop_back();
    void clear();
    unsigned long size() const {return count;}
    T& at(int ndx) const;
    
};



template <typename T>
LL<T>::LL()
{
    count = 0;
    this->head = NULL;
}


template <typename T>
LL<T>::~LL()
{
    this->clear();
}

//copy constructor
template <typename T>
LL<T>:: LL(const LL<T> &otherLL)
{
    this->head = NULL;
    this->count = 0;
    
    if(otherLL.count == 0)
    {
        //list is empty, do nothing
    }
    
    else
    {
        copyList(otherLL);
    }
}

//Private function called by overloaded=
template <typename T>
void LL<T> :: copylist(const LL<T> &listToCopy)
{
    Node<T> *currentOther = this->head;
    while (currentOther != NULL)
    {
        this->push_back(currentOther->info);
        currentOther = currentOther->next;
    }
}

//overloaded = operator
template <typename T>
LL<T>& LL<T>:: operator=(const LL<T> &rhsObj)
{
    //test for self-assignment
    if(this == &rhsObj)
    {
        //self assignment
    }
    else
    {
        this->clear();
        copyList(rhsObj);
    }
}



//push_back adds new Node<T> to the end of the linked list
template <typename T>
void LL<T>:: push_back(T value)
{
    try
    {
        if(head == NULL)
        {
            //list is empty
            head = new Node<T>(value);
        }
        else
        {
            //list contains at least one Node object
            Node<T> *current = head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            Node<T> *addMe;
            addMe = new Node<T>(value);
            current->next = addMe;
        }
        count++;
    }
    catch(std::bad_alloc)
    {
        string notGood = "Error bad allocation";
        throw notGood;
    }
}


//insert places Node<T> in ascending order by incident #
template <typename T>
void LL<T>:: insert(T value)
{
    try
    {
        if (head == NULL || (head->info >= value))
        {
            //element to be inserted in first position
            Node<T> *addMe = new Node<T>(value);
            addMe->next = head;
            head = addMe;
            count++;
        }
        else
        {
            Node<T> *current = head->next;
            Node<T> *trailCurrent = head;
            
            while(current != NULL && (current->info < value))
            {
                trailCurrent = current;
                current = current->next;
            }
            Node<T> *addMe = new Node<T>(value, NULL);
            trailCurrent->next = addMe;     //node before addMe
            addMe->next = current;    //node after addMe
            count++;
        }
    }
    catch(std::bad_alloc)
    {
        string notGood = "Error bad allocation";
        throw notGood;
    }

}


//pop_back removes the last list object and deallocates memory
template <typename T>
void LL<T>:: pop_back()
{
    Node<T> *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    delete(current);
    count--;
}


//clear - removes all objects from list and deallocates memory
template <typename T>
void LL<T>::clear()
{
    Node<T> *current = head;
    while(current != NULL)
    {
        current = current->next;
        delete head;
        head = current;
        count--;
    }
    head = NULL;
    current = NULL;
}


//at, same as at function of vector class
template <typename T>
T& LL<T> :: at(int ndx) const
{

    ostringstream orStrm;
    string errorMessage = "out of range error";
    
    orStrm << "bad index in member function LL::at( ";
    orStrm << ndx;
    orStrm << " )\n";
    orStrm << "number of Nodes on the list is ";
    orStrm << this->size();
    
    errorMessage = orStrm.str();
    
    out_of_range orErr(errorMessage);
    
    if ( ndx < 0 || ndx >= count )
    {
        throw orErr;
    }
    Node<T> *current = head;
    for ( int i = 0; i < ndx && current != NULL; i++ )
    {
        current = current->next;
    }
   
    if ( !current )
    {
        throw orErr;
    }
    
    return current->info;

}

template <typename F>
ostream& operator <<(ostream &os, const LL<F> &rhsObj)
{
    Node<F> *current = rhsObj.head;
    while(current != NULL)
    {
        os << current->info << std::endl;
        
        current = current->next;
    }
    
    return os;
}


#endif
