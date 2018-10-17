
/*
 * PHMSA7000.h
 *
 * COSC 052 Fall 2016
 * Project #4
 *
 * Due on: NOV 17, 2016
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

#include "DateTime.h"
#include "PHMSA7000.h"

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
 ^^                                                                        ^^
 ^^            SPECIALIZED    class Node declaration                       ^^
 ^^                                                                        ^^
 ****************************************************************************/

// new for P4 (template specialization)
template <>
class Node<HazMat7k*>
{
public:
    HazMat7k *info;
    Node<HazMat7k*> *next;
    
    //specialized to dynamically allocate memory, we will
    //discuss in class why this would be prudent to do
    //(afterall, a pointer was passed in, so why allocate memory again?)
    Node(HazMat7k*, Node<HazMat7k*> *n = NULL);
    
    //specialization to deallocate memory
    ~Node();
    
}; //END declaration for template specialization of class Node



/****************************************************************************
 ^^^^                                                                    ^^^^
 ^^^^       SPECIALIZED    class Node implementation                     ^^^^
 ^^^^                                                                    ^^^^
 ****************************************************************************/

// new for P4 (template specialization)
Node<HazMat7k*>::Node(HazMat7k *ptr7k, Node<HazMat7k*> *n)
{
    //cout << "inside specialized version of constructor Node() " << endl;
    
    HazMat7k *addMe = NULL;
    
    FatalityOrInjury *ptrFI = NULL;
    LossOrDamage *ptrLD = NULL;
    
    try
    {
        
        if ( ptr7k->getIncidentCode() == 'f')
        {
            ptrFI = static_cast<FatalityOrInjury*>(ptr7k);
            //cout << "allocating memory for FatalityOrInjury object" << endl;
            addMe = new FatalityOrInjury(*ptrFI);
        }
        
        else if ( ptr7k->getIncidentCode() == 'l' )
        {
            ptrLD = static_cast<LossOrDamage*>(ptr7k);
            //cout << "allocating memory for LossOrDamage object" << endl;
            addMe = new LossOrDamage(*ptrLD);
        }
        else
        {
            cout << "something went wrong inside specialized Node constructor with parameters\n";
            cout << "there was no match to the Incident Code, should be either f or l\n";
            cout << "see Milestone 4, changes required to the loadData function\n";
        }
        
        
        info = addMe;
        
        next = n;
    }
    catch (std::bad_alloc baErr)
    {
        throw;
    }
    catch (...)
    {
        throw string("unknown error in constructor of specialized Node class");
    }
}

// new for P4 (template specialization)
Node<HazMat7k*>::~Node()
{
    
    //cout << "inside specialized version of destructor ~Node() " << endl;
    delete info;
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
    LL<T> &operator=(const LL<T> &rhsObj);
    void push_back(T);
    void insert(T);
    void pop_back();
    void clear();
    unsigned long size() const {return count;}
    T& at(int ndx) const;
    LL_iterator<T> begin() const {return this->head;}
    LL_iterator<T> end() const {return NULL;}
    
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
    this->clear();
    Node<T> *currentOther = listToCopy->head;
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
        return *this;
    }
    else
    {
        return *(copyList(rhsObj));
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






#endif
