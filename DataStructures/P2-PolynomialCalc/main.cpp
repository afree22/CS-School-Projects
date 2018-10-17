//
//  main.cpp
//  Polynomial2
//
//  Created by Anne Freeman on 10/15/17.
//  Copyright © 2017 Anne Freeman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include "Polynomial.h"
using namespace std;

int main(int argc, const char * argv[])
{
    // argc should be 2 - need file to run
    if ( argc != 2 )
        
        // output error message
        cout << "Please enter file name as command line argument" << endl;
    
    else
    {
        ifstream inFile ( argv[1] );
        
        // check to see if file opening was successful
        if ( !inFile.is_open() )
            cout << "\nERROR: Could not open file\n\n";
    
        else
        {
            string str1;
            string str2;
            
            // two lines containing the information for Polynomials
            getline(inFile, str1);
            getline(inFile, str2);
            
            //First Polynomial
            istringstream iss1(str1);
            int exp;
            int coeff;
        
            Polynomial p1;

            //add terms to polynomial 1
            while(iss1 >> coeff >> exp)
            {
                p1.insert(coeff, exp);
            }
        
            // print out the first polynomial and its evaluation at 10
            cout << "Polynomial 1:"<< endl << p1;
            int resultP1 = p1.eval(10);
            if(resultP1 > -100000000)
            {
                cout << "P1 evaluated for x = 10: ";
                cout << resultP1 << endl << endl;
            }
            //cout << "P1 evaluated for x=10: \n" << p1.eval(10) << endl << endl;
        
            //add terms to polynomial 2
            Polynomial p2;
            istringstream iss2(str2);
            while(iss2 >> coeff >> exp)
            {
                p2.insert(coeff, exp);
            }
            
            
            //output polynomial 2
            cout << "Polynomial 2" << endl;
            cout << p2;
            
            int resultP2 = p2.eval(10);
            if(resultP2 > -100000000)
            {
                cout << "P2 evaluated for x = 10: ";
                cout << resultP2 << endl << endl;
            }
            
            //get sum of polynomials
            Polynomial p3 ( p1 + p2 );
            cout << "Polynomial 3 - Add P1 and P2\n" << p3;
            int resultP3 = p3.eval(10);
            if(resultP3 > -100000000)
            {
               cout << "Sum of P1 and P2 evaluated for x=10: " << p3.eval(10) <<  endl << endl;
            }
            
            
            // get product of polynomials
            p3 = p1*p2;
            cout << "Product of P1 and P2: \n" << p3;
            int resultP4 = p3.eval(2);
            if(resultP4 > -100000000)
            {
                cout << "Product of P1 and P2 evaluated for x=2: ";
                cout << resultP4 << endl << endl;
            }
            
            // get the powers of the polynomials
            cout << "P1 rasied to the third power: \n" << p1.polyPower(p1, 3) << endl;
            
            
            int resultP5 = p2.eval(5);
            if(resultP5 > -100000000)
            {
                cout << "P1 raised to the " << p2.eval(5) << " power: \n";
                cout << p1.polyPower(p1, p2.eval(5)) << endl << endl;
            }
    }
        
    }
    return 0;
}
