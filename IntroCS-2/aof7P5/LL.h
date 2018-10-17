
/*
 * PHMSA7000.h
 *
 * COSC 052 Fall 2016
 * Project #5
 *
 * Due on: DEC 1, 2015
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

const int LIST_SIZE = 1000;     //new for P5 (mandatory) (change this as necessary)

#include "DateTime.h"

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

using std::cout;
using std::endl;

/************************************************************
 ^^                    Global Constants                    ^^
 ************************************************************/

const int LOOP_OUTPUT_FREQUENCY = 5000;   //new for P5 (optional)
const int SORT_OUTPUT_FREQUENCY = 750;    //new for P5 (optional)


/****************************************************************************
 ^^                                                                        ^^
 ^^                         REGULAR Node class                             ^^
 ^^                                                                        ^^
 ****************************************************************************/


template <typename T>
class Node
{
public:
    T info;
    Node<T> *next;
    Node(T = T(), Node<T>* = NULL);
};

// Node class implementation
template <typename T>
Node<T>::Node(T val, Node<T> *ptr)
{
    info = val;
    next = ptr;
}



/****************************************************************************
 *                                                                          *
 *                   class LL_iterator declaration                          *
 *                                                                          *
 ****************************************************************************/

// new for P4
template <typename T>
class LL_iterator
{
    
private:
    Node<T> *current;
    //pointer to point to the current
    //node in the linked list
    
public:
    
    LL_iterator();
    //default constructor
    
    LL_iterator(Node<T> *ptr);
    //constructor with parameter
    
    T& operator*();
    //overloaded dereferencing operator *
    //Postcondition: Returns the info contained in the node
    
    LL_iterator operator++();
    //overloaded pre-increment operator
    //Postcondition: The iterator is advanced to the next node in the linked list
    
    bool operator==(const LL_iterator &rhsObj) const;
    //overloaded equality operato

    
    bool operator!=(const LL_iterator &rhsObj) const;
    //overloaded equality operator
    //Postcondition: Returns true if this iterator is NOT equal to the
    //               iterator specified on the right hand side
    //               otherwise returns false
    
    
}; //END class LL_iterator



/****************************************************************************
 *                                                                          *
 *               class LL_iterator implementation code                      *
 *                                                                          *
 ****************************************************************************/
template <typename T>
LL_iterator<T>::LL_iterator()
{
    this->current = NULL;
}

template <typename T>
LL_iterator<T>::LL_iterator(Node<T> *ptr)
{
    this->current = ptr;
}

template <typename T>
T& LL_iterator<T>:: operator*()
{
    return current->info;
    
}

template <typename T>
LL_iterator<T> LL_iterator<T> ::operator++()
{
    this->current = this->current->next;
    return *this;
}

template <typename T>
bool LL_iterator<T>:: operator==(const LL_iterator &rhsObj) const
{
    
    if(this->current == rhsObj.current)
    {
        return true;
    }
    else
        return false;
}

template <typename T>
bool LL_iterator<T>::operator!=(const LL_iterator &rhsObj) const
{
    return !(*this == rhsObj);
}



/****************************************************************************
 *                                                                          *
 *                         class Linked List                                *
 *                                                                          *
 ****************************************************************************/
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
    LL<T>& operator=(const LL<T> &rhsObj);
    void push_back(T);
    void insert(T);
    void pop_back();
    void clear();
    unsigned long size() const {return count;}
    T& at(int ndx) const;
    LL_iterator<T> begin() const {return this->head;}
    LL_iterator<T> end() const {return NULL;}
    
    
    void bubbleSort();           //new for P5
    void bubbleSortI();          //new for P5
    void selectionSort();        //new for P5
    int linearSearch(T lookFor); //new for P5
    //(returns index of first match, or -1 if not found)
    int binarySearch(T lookFor); //new for P5
    //(returns index of first match, or -1 if not found)
    
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
        copylist(otherLL);
    }
}

//Private function called by overloaded=
template <typename T>
void LL<T> :: copylist(const LL<T> &listToCopy)
{
    //cout << "In copy list" << endl;
    this->clear();
    Node<T> *current = listToCopy.head;
    while (current != NULL)
    {
        this->push_back(current->info);
        current = current->next;
    }
    
}

//overloaded = operator
template <typename T>
LL<T>& LL<T>:: operator=(const LL<T> &rhsObj)
{
    //test for self-assignment
    if(this != &rhsObj)
    {
        //self assignment
        this->clear();
        this->copylist(rhsObj);
    }
    return *this;
}



//push_back adds new Node<T> to the end of the linked list
template <typename T>
void LL<T>:: push_back(T value)
{
    //cout << "In push_back" << endl;
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
    if (head == NULL)
    {
        //the list is empty
    }
    else
    {
        //traverse the list, find next to last node, delete last node
        Node<T> *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        delete(current);
        current = NULL;
        count--;
    }
    
}


//clear - removes all objects from list and deallocates memory
template <typename T>
void LL<T>::clear()
{
    Node<T> *current = head;
    while ( current != NULL )
    {
        current = current->next;
        delete head;
        head = current;
        count--;
    }
    head = NULL;
    current = NULL;

    /*
     int numDeleted = 0;
     while (head != NULL)
     {
        pop_back();
        numDeleted++;
     }
     */
     
}


//at, same as at function of vector class
template <typename T>
T& LL<T> :: at(int ndx) const
{
    Node<T> *current = head;
    
    try
    {
        //testing for if out of bounds
        if ( ndx < 0 || ndx >= count )
        {
            throw string("ERROR: out of bounds in LL::at()");
        }
        
        
        
        for ( int i = 0; i < ndx && current != NULL; i++ )
        {
            current = current->next;
        }
        
    }
    catch ( out_of_range orErr )
    {
        cout << "\nrethrowing out_of_range exception from LL:at()" << endl;
    }
    catch (string a)
    {
        throw a;
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


/****************************************************************************
 **      class LL search and sort member function implementation code      **
 ****************************************************************************/


template <typename T>
void LL<T>::bubbleSort()
{
    cout << "Entered member function bubbleSort()" << endl;
    
    //for testing
    int swapCount = 0;
    
    T temp;
    int iteration;
    int index;
    
    for(iteration = 1; iteration < LIST_SIZE; iteration++)
    {
        for(index = 0; index < LIST_SIZE - iteration; index++)
        {
            if(at(index) > at(index+1))
            {
                temp = at(index);
                at(index) = at(index +1);
                at(index +1) = temp;
                swapCount++;
            }
        }
    }

    
    cout << "Exiting member function bubbleSort() \nswapCount = " << swapCount << endl;
    
} //END member function LL<T>::bubbleSort()



template <typename T>
void LL<T>::bubbleSortI()
{
    cout << "Entered member function bubbleSortI()" << endl;

    //for testing
    int swapCount = 0;
    T temp;
    int iteration;
    int index;
    
    LL_iterator<T> current;
    LL_iterator<T> after;
    
    for(iteration = 1; iteration < LIST_SIZE; iteration++)
    {
        current = begin();
        after = begin();
        ++after;
        
        for(index = 0; index < LIST_SIZE - iteration; index++)
        {
            if(*current > *after)
            {
                //cout << "entered swap" << endl;
                temp = *current;
                *current = *(after);
                *after = temp;
                
                swapCount++;
            }
            ++current;
            ++after;
        }
    }

    cout << "Exiting member function bubbleSortI() \nswapCount = " << swapCount << endl;
    
} //END member function LL<T>::bubbleSortI()



template <typename T>
void LL<T>::selectionSort()
{
    cout << "Entered function selectionSort() " << endl;
    
    //for testing
    int swapCount = 0;
    //int innerLoopCount = 0;
    //int outerLoopCount = 0;
    
    int index;
    int smallestIndex;
    int location;
    T temp;
    
    

     for(index = 0; index < LIST_SIZE - 1; index++)
    {
        smallestIndex = index;
        for(location = index + 1; location < LIST_SIZE; location++)
        {
            if(at(location) < at(smallestIndex))
            {
                smallestIndex = location;
            } //end if statement
            
        } //end inner loop
        if(at(smallestIndex) != at(index))
        {
            temp = at(smallestIndex);
            at(smallestIndex) = at(index);
            at(index) = temp;
            swapCount++;
        }
        
    }//end outer loop
    
    
    
    cout << "Exiting function selectionSort() \nswapCount = " << swapCount << endl;
    
} //END function member function LL<T>::selectionSort()



//new for P5
template <typename T>
int LL<T>::binarySearch(T lookFor)
{
    cout << "Entered function binarySearch(" << lookFor << ")" << endl;
    
    bool found = false;
    int first = 0;
    int last = LIST_SIZE-1;
    int mid;
    
    while(first <= last && !found)
    {
        mid = (first + last) / 2;
        if(at(mid) == lookFor)
        {
            found = true;
        }
        else if(at(mid) > lookFor)
        {
            last = mid-1;
        }
        else
        {
         
            first = mid + 1;
        }
    }
    
    cout << "Exiting function binarySearch()" << endl;

    return((found) ? mid: -1);
    
} //END member function LL<T>::binarySearch()


//new for P5
template <typename T>
int LL<T>::linearSearch(T lookFor)
{
    cout << "Entered function linearSearch(" << lookFor << ")" << endl;
    
    bool found = false;
    int loc = 0;
    while(loc < LIST_SIZE && !found)
    {
        if(at(loc) == lookFor)
        {
            found = true;
        }
        else
        {
            loc++;
        }
    }
    return((found) ? loc:-1);
    
    
} //END member function LL<T>::linearSearch()



#endif
