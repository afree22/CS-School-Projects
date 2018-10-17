
/*
 * IncidentLog.h
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

#ifndef IncidentLog_h
#define IncidentLog_h

#include "PHMSA7000.h"
#include "LL.h"

#include <vector>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;



class IncidentLog
{
private:
    LL<HazMat7k*> allIncidents;

public:
    IncidentLog();
    ~IncidentLog();
    void displayReport() const;
    void appendObject (HazMat7k *myHM7K) {allIncidents.insert(myHM7K);}
    unsigned long size() const;
};


//Constructor
IncidentLog::IncidentLog()
{
    
}

//Destructor
IncidentLog::~IncidentLog()
{
    
}


void IncidentLog::displayReport() const
{
    try
    {
       
        cout << "Form PHMSA F 7000-1 Accident Report -";
        cout << " Hazardous Liquid Pipeline Systems (";
        cout << allIncidents.size();
        cout << ") records" << endl << endl;
        
        
        
        LL_iterator<HazMat7k *> itr1 = allIncidents.begin();
        while( itr1 != allIncidents.end())
        {
            (*itr1)->summaryReport();
            ++itr1;
        }
        
        
        
        /*
        for(int i = 0; i < allIncidents.size(); i++)
        {
            allIncidents.at(i)->summaryReport();
            cout << endl << endl;
        }
        */
        
    }
    catch(std::out_of_range orErr)
    {
        string errorMessage = "out_of_range caught from displayReport function";
        throw errorMessage;
    }
}


unsigned long IncidentLog::size() const
{
    
    unsigned long llSize = allIncidents.size();
    return llSize;
}


#endif



