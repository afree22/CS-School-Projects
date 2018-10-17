//
//  Polynomial.hpp
//  Polynomial2
//
//  Created by Anne Freeman on 10/15/17.
//  Copyright © 2017 Anne Freeman. All rights reserved.
//

#ifndef Polynomial_h
#define Polynomial_h

#include <iostream>
#include <stdexcept>
#include <exception>
#include <cmath>

using namespace std;

/*
 Node Class
 I made the nodes singly linked because it saves space and it saves steps for
 rearranging the prev pointer when adding nodes to the linked list (even though it
 does require using a "previous" node to follow
 */
class Node
{
public:
    int coefficient;
    int exponent;
    Node *next;
    Node(){ next = NULL; }
    Node (int coeff, int exp, Node* next );
};



/*
 Polynomial Class
 I implemented the Polynomial as a Linked List because it will not store unnecessary blank spaces
 like a coefficient array would. The Polynomial Linked List will only store nodes of the polynomial that
 are initialized with a coefficient and exponent. In my polynomial linked list class, I keep track of the
 head and tail because it makes it easier to add to the tail.
 */
class Polynomial
{
    friend ostream& operator<<( ostream &os, const Polynomial &p1 ); // overloaded stream insertion
    friend Polynomial operator+( const Polynomial &p1, const Polynomial &p2 ) throw (overflow_error);
    friend Polynomial operator*( const Polynomial &p1, const Polynomial &p2 ) throw (overflow_error);
private:
    Node *head;
    Node *tail;
    
public:
    // default constructor
    Polynomial( ){ head = tail = NULL; }
    // copy constructor
    Polynomial( const Polynomial &p );
    //desctructor
     ~Polynomial();
    
    // overloaded assignment operator
    const Polynomial &operator=( const Polynomial &p1 );
    
    // to add a Node to the list
    // inserts in correct, highest exponent to lowest, and adds coefficient
    void insert(int coeff, int exp)throw(std::overflow_error, std::bad_alloc);

    Polynomial& polyPower( Polynomial p, int n ) throw (overflow_error, bad_alloc);
    int eval( double x ) throw (overflow_error);

};
#endif /* Polynomial_h */
