

/*
 *  IncidentLog.cpp
 *
 *  COSC 052 Fall 2016
 *  Project #1
 *
 *  Due on: SEP 27, 2016
 *  Author: Anne Freeman
 *
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 *
 *  References not otherwise commented within the program source code.
 *  Note that you should not mention any help from the TAs, the professor,
 *  or any code taken from the class textbooks.
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include "IncidentLog.h"
using std::cout;
using std::endl;

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
    double records = allIncidents.size();
    
    cout << "Form PHMSA F 7000-1 Accident Report - Hazardous Liquid Pipeline Systems (" << records << ") records:" << endl << endl;
    
    for(int i =0; i < allIncidents.size(); i++)
    {
        allIncidents[i].summaryReport();
        cout << endl << endl;
    }
}

//Add HazMat7k Object to IncidentLog Vector
void IncidentLog::appendObject (const HazMat7k &myHM7k)
{
    allIncidents.push_back(myHM7k);
}


unsigned long IncidentLog::size() const
{
    unsigned long x;
    x = sizeof(allIncidents);
    return x;
}




