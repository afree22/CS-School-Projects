//
//  Polynomial.cpp
//  Polynomial2
//
//  Created by Anne Freeman on 10/15/17.
//  Copyright © 2017 Anne Freeman. All rights reserved.
//

#include "Polynomial.h"
#include <iostream>

/*
 Constructor for Node
 sets the values for coefficient, exponent and
 the next pointer (default value of NULL)
 */
Node::Node(int coeff, int exp, Node *n)
{
    coefficient = coeff;
    exponent = exp;
    next = n;
}


/*
 Copy constructor for the Polynomial Class
 Used to initialize a Polynomial with the values of another
 Polynomial. Create a copy constructor to ensure that the
 pointers are not accidentally set equal to eachother (want a deep copy)
 */
Polynomial::Polynomial(const Polynomial& p)
{
    this->head = NULL;
    this->tail = NULL;
    
    Node *poly = p.head;
    
    while ( poly != NULL )
    {
        this->insert( poly->coefficient, poly->exponent);
        poly = poly->next;
    }
    
}

//destructor
Polynomial::~Polynomial()
{
    if (head == NULL)
    {
        // list is empty
    }
    else
    {
        while ( head != NULL)
        {
             // only one Node on the list
            if ( head == tail && head != NULL )
            {
                delete head;
                head = NULL;
                tail = NULL;
            }
            else
            {
                Node *poly = head->next;
                delete head;
                head = poly;
            }
        }
        head = NULL;
        tail = NULL;
    }
}



/*
 Overloaded assignment operator for Polynomials
 will assign the values of p to the values of this
 To do so, must first delete this, and then insert the
 values from p
 */
const Polynomial& Polynomial::operator= (const Polynomial& p)
{
    // check for self assignment
    if ( this!= &p )
    {
        // to copy over -- must delete nodes on
        // existing list
        while ( this->head != NULL )
        {
            // there is only node in list
            if ( this->head == this->tail )
            {
                delete this->head;
                this->head = NULL;
                this->tail = NULL;
            }
            else
            {
                Node *poly = this->head->next;
                delete this->head;
                this->head = poly;
            }
        }
        
        this->head = NULL;
        this->tail = NULL;
        

        Node *poly = p.head;
        

        while ( poly != NULL )
        {
            // add node onto new list
            this->insert(poly->coefficient, poly->exponent);
            poly = poly->next;
        }
    }
    return *this;
}


/*
 Insert operation for Polynomials
 Takes a coefficient and exponent as parameters and creates a Node
 Inserts that node at the proper position in the list -- or adds the coefficient to an
 existing node on the list if they have the same exponent
 Ordering my list when inserting the nodes makes sense --> it will save time when I need to
 output them in order and when I want to get the largest exponent of the polynomial it will be the head
 Additionally, it adds an easy way to set the sentinel value as the largest exponent of the polynomial
 will be the head.
 Adding the common terms when inserting the nodes makes sense --> it saves time as the list
 doesn't need to be searched through again to add the common terms and it saves space as nodes with common
 exponents don't need to be allocated as separate nodes
 */
void Polynomial::insert(int coeff, int exp)throw(std::overflow_error, std::bad_alloc)
{
    try
    {

        Node *newNode = new Node ( coeff, exp, NULL );
        
        Node *poly = head;
        
        // insert newNode at front of empty list
        if ( head == NULL )
        {
            head = tail = newNode;
        }
        
        // insert newNode at front of non-empty list
        else if ( newNode->exponent > poly->exponent)
        {
            newNode->next = poly;
            head = newNode;
        }
        
        // add newNode with front of non-empty list
        else if ( exp == poly->exponent )
        {
            // add their coefficients together
            int sumCoeff = poly->coefficient;
            poly->coefficient = sumCoeff + coeff;
            
            // throw an exception if this operation creates overflow
            if ((poly->coefficient) - sumCoeff != coeff )
                throw overflow_error("\nOverflow error detected.\n\n");
        }
        
        // scan list for place to insert or add newNode
        else
        {
            bool found = false;
            Node *poly = head;
            Node *previous = head;
            
            while (poly != NULL && found == false)
            {
                // if exponent to add is the same as node's exponent
                if ( poly->exponent == exp )
                {
                    // add their coefficients together
                    int sumCoeff = poly->coefficient;
                    poly->coefficient = sumCoeff + coeff;
                    
                    // throw an error if this operation creates overflow
                    if ((poly->coefficient) - sumCoeff != coeff )
                        throw overflow_error("\nOverflow error detected.\n\n");
                    
                    found = true;
                }
                
                // in the correct position
                else if ( exp > poly->exponent )
                {
                    // insert newNode before poly
                    previous->next = newNode;
                    previous = newNode;
                    newNode->next = poly;
                    found = true;
                }
                
                // if poly has reached the end of the list
                else if ( poly == tail )
                {
                    // insert at the end
                    tail->next = newNode;
                    newNode->next = NULL;
                    tail = newNode;
                    found = true;
                    
                }
                
                // still haven't found right spot in list -- keep searching
                else
                {
                    previous = poly;
                    poly = poly->next;
                }
            }
        }
        
    }
    
    catch ( overflow_error &oe1 )
    {
        cout << "\nERROR: Overflow Detected in addNode(): ";
    }
    catch ( bad_alloc &ba1 )
    {
        cout << "\nUnable to allocate memory\n";
    }
    
}




/*
 polyPower - find new polynomial --> p1^n
 checks if overflow after each multiplication
 
 */
Polynomial& Polynomial::polyPower(Polynomial p1, int n) throw(std::overflow_error, std::bad_alloc)
{
    // create a temporary poly object
    Polynomial *poly = new Polynomial(p1);
    
    // create sentinel
    Polynomial *sentinel = new Polynomial;
    
    // INT_MIN doesn't exist -- chck for -100000000
    // low coefficient at high exponent --> -100000000 should be first node in linked list
    sentinel->insert(-100000000, 100000000);
    bool end = false;
    
    try
    {
        // call multiplication function
        for ( int i = 0; i<(n-1) && end == false; i++ )
        {
            *poly = *poly * p1;
            
            // if the sentinel value has been set -- overflow has occurred
            if ( (*poly * p1).head->coefficient == -100000000 )
            {
                end = true;
            }
        }
        
        // check for overflow -- can't raise a polynomial to a negative power
        if ( end == true || n < 0 )
        {
            throw overflow_error("Overflow in polyPower");
        }
        
    }
    catch( overflow_error &oe1)
    {
        cout << "Overflow in polyPower ";
        return *sentinel;
    }
    catch ( bad_alloc &ba1 )
    {
        cout << "Allocation of memory error";
    }
    return *poly;
}




/*
 Evaluates polynomial for certain value x
 Takes advantages of the mathematical properties of exponents
 to calculate result iteratively
 */
int Polynomial::eval(double x) throw(std::overflow_error)
{
    Node *poly = head;
    int result = 0;
    
    // int min doesn't exist -- return this and check for it in main
    // if encounter error
    int sentinel = -100000000;
    
    try
    {
        while( poly!= NULL)
        {
            // if the exponent is even
            if ( poly->exponent % 2 == 0)
            {
                int val1 = result + poly->coefficient * pow(x*x, poly->exponent/2);
                
                // check for overflow
                if ( result + poly->coefficient * pow(x*x, poly->exponent/2) != val1 )
                    throw overflow_error("Overflow in eval\n");
                
                result = val1;
            }
            
            // if the exponent is odd
            else
            {
                int val2 = result + poly->coefficient * x * pow(x*x, (poly->exponent-1)/2);

                // check for overflow
                if ( result + poly->coefficient * x * pow(x*x, (poly->exponent-1)/2) != val2 )
                    throw overflow_error("Overflow in eval\n");
                result = val2;
            }
            poly = poly->next;
        }
    }
    
    catch ( overflow_error &oe1 )
    {
        cout << "Overflow in eval\n";
        return sentinel;
    }
    catch ( ... )
    {
        cout << "Exception caught in eval" << endl;
        return sentinel;
    }
    return result;
}



/*
 ******
 ******     Friend Functions     ******
 ******
 */

// overloaded operator <<
// outputs polynomial if an error hasn't occured
// outputs polynomial with correct formatting in correct order
std::ostream& operator << (std::ostream &os, const Polynomial &p1)
{

    Node *p = p1.head;
    
    if ( p1.head == NULL )
    {
            os << endl << "The polynomial is empty";
    }
    
    // check if the sentinel is set
    if(p1.head->coefficient == -100000000)
    {
        os << std::endl;
        return os;
    }
    // now just output from linked list
    while (p != NULL)
    {
        if ((p->coefficient) != 1)
        {
            os << " " << p->coefficient;
        }
        if(p->exponent != 0)
        {
            os << "x";
        }
        if(p->exponent > 1)
        {
            os << "^"<< p->exponent;
        }
        if (p->next != NULL && p->next->coefficient > 0)
        {
            os << "+";
        }
        p = p->next;
    }
    std::cout << std::endl;
    return os;
}



// overloaded multiplier
// creates a new polynomial by multiply p1 and p2 (adding exponents and
// multiplying coefficients
Polynomial operator * (const Polynomial& p1, const Polynomial& p2) throw(std::overflow_error)
{
    // create a temporary poly object
    Polynomial result;
    Polynomial sentinel;
    // low coefficient at high exponent --> -100000000 should be first node in linked list
    sentinel.insert(-100000000, 100000000);
    
    try
    {
        int sumCoeff = 0;
        int sumExp = 0;
        Node *poly1 = p1.head;
        Node *poly2 = p2.head;
        
        while ( poly1 != NULL )
        {
            while ( poly2 != NULL )
            {
                sumCoeff = poly1->coefficient * poly2->coefficient;
                
                // check for coefficient overflow
                if ( sumCoeff / poly1->coefficient != poly2->coefficient )
                {
                    throw overflow_error("Overflow in operator*\n");
                }
                
                // check for exponent overflow
                sumExp = poly1->exponent + poly2->exponent;
                if ( sumExp - poly1->exponent != poly2->exponent )
                {
                    throw overflow_error("Overflow in operator*\n");
                }
                poly2 = poly2->next;
                result.insert(sumCoeff, sumExp);
            }
            
            poly1 = poly1->next;
            poly2 = p2.head;
        }
        
    }
    catch( overflow_error &oe1)
    {
        cout << "Overflow in operator*\n";
        return sentinel;
    }
    catch ( ... )
    {
        cout << "Exception caught in operator*" << endl;
    }
        
    return result;
}
        
        
// overloaded addition -- creates new polynomial
// by adding p1 and p2
Polynomial operator+ (const Polynomial& p1, const Polynomial& p2) throw(std::overflow_error)
{
    Polynomial result;
    
    // sentinel to indicate error
    Polynomial sentinel;
    // low coefficient at high exponent --> -100000000 should be first node in linked list
    sentinel.insert(-100000000, 100000000);
    
    try
    {
        Node *poly1 = p1.head;
        Node *poly2 = p2.head;
        
        while( poly1 != NULL && poly2 != NULL )
        {
            // Insert nodes of first polynomial
            // if first > second    --- increment poly1
            if( poly1->exponent > poly2->exponent )
            {
                result.insert( poly1->coefficient, poly1->exponent );
                poly1 = poly1->next;
            }
            
            // Insert second polynomical if second > first
            // increment poly2
            else if( poly1->exponent < poly2->exponent )
            {
                result.insert(poly2->coefficient, poly2->exponent );
                poly2 = poly2->next;
            }
            
            // add coefficients when polynomials have the same power
            else
            {
                int sumCoeff = poly1->coefficient + poly2->coefficient;
                
                // check for overflow with coefficients
                if ( sumCoeff - poly1->coefficient != poly2->coefficient )
                    throw overflow_error("Overflow in operator+");
                
                result.insert( ((poly1->coefficient)+(poly2->coefficient)), poly1->exponent);
                poly1 = poly1->next;
                poly2 = poly2->next;
            }
            
        }
        
        // if at least one polynomial has values
        while(poly1 != NULL || poly2 != NULL )
        {
            // if polynomial 1 has values, insert them
            if( poly1 != NULL )
            {
                result.insert( poly1->coefficient, poly1->exponent);
                poly1 = poly1->next;
            }
            
            // if polynomial 2 has values, insert them
            if( poly2 != NULL )
            {
                result.insert( poly2->coefficient, poly2->exponent);
                poly2 = poly2->next;
            }
            
        }
        
    }
    catch( overflow_error &oe1)
    {
        cout << "Overflow in operator+";
        return sentinel;
    }
    catch ( ... )
    {
        cout << "Exception caught in operator+" << endl;
    }
    
    // return the sum of the two polynomials
    return result;
}

