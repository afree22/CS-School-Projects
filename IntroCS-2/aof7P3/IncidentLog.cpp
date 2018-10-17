

/*
 * IncidentLog.cpp
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

#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
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
    try
    {
    
        double FatalityOrInjuryRecords = llFatalityOrInjury.size();
        cout << "Form PHMSA F 7000-1 Accident Report -";
        cout << " Hazardous Liquid Pipeline Systems (";
        cout << FatalityOrInjuryRecords;
        cout << ") records with a fatality or injury" << endl << endl;
        
        
        
        for(int i =0; i < llFatalityOrInjury.size(); i++)
        {
            llFatalityOrInjury.at(i).summaryReport();
            cout << endl << endl;
        }
    
        double LossOrDamageRecords = llLossOrDamage.size();
        cout << "Form PHMSA F 7000-1 Accident Report -";
        cout << " Hazardous Liquid Pipeline Systems (";
        cout << LossOrDamageRecords;
        cout << ") records with only material loss or damage" << endl << endl;
        for(int i =0; i < llLossOrDamage.size(); i++)
        {
            llLossOrDamage.at(i).summaryReport();
            cout << endl << endl;
        }
        
    }
    catch(std::out_of_range orErr)
    {
        std::ostringstream osMsg;  //instatiates object
        osMsg << "ERROR: out_of_range exception caught\n";
        string rtnMsg = osMsg.str();
        throw rtnMsg;
    }
}

//Add FatalityOrInjury Object to Vector
void IncidentLog::appendObject (const FatalityOrInjury &foi)
{
    try
    {
    llFatalityOrInjury.insert(foi);
    }
    catch(...)
    {
        throw;
    }
    
}

//Add LossOrDamage Object to Vector
void IncidentLog::appendObject(const LossOrDamage &lod)
{
    try
    {
    llLossOrDamage.insert(lod);
    }
    catch(...)
    {
        throw;
    }
}

unsigned long IncidentLog::sizeFatalityOrInjury() const
{
    
    unsigned long llSize = llFatalityOrInjury.size();
    return llSize;
}

unsigned long IncidentLog::sizeLossOrDamage() const
{
    unsigned long llLength = llLossOrDamage.size();
    return llLength;
}


