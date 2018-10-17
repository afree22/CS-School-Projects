
/*
 * aof7P2.cpp
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
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "IncidentLog.h"
#include "PHMSA7000.h"

//function prototype
void loadData(string, char, IncidentLog &);

// *******************
//   Entering Main
// *******************
int main(int argc, char * argv[])
{
    
    try
    {
        
        if ( argc < 3)
        {
            // not enough command line arguments
            throw 25;
        }
        
        else
        {
            
            string inputFileName = " ";
            inputFileName = string(argv[1]);
            
            fstream inFile(inputFileName.c_str(), ios::in | ios::binary);
            
            
            IncidentLog MyIncidentLog;
            LL<FatalityOrInjury>FOI;
            LL<LossOrDamage>LOD;
            
            char fileType = '?';
            fileType = argv[2][0];
            //const char *cptr = argv[2];
            //const char fileType = *cptr;
            
            loadData(inputFileName, fileType, MyIncidentLog);
            
            //Display report in order from highest to lowest
            MyIncidentLog.displayReport();
            
            inFile.close();
            
        }
    }
    
    //catches exception if <3 command line arguments
    catch(int x)
    {
        cout << "Please pass the full path and file name of the input data file as";
        cout << " a command line argument." << endl;
        cout << "The program cannot continue..." << endl;
    }
    
    //catches out_of_range exception and exception from loadData
    catch(string errorMessage)
    {
        cout << errorMessage << endl;
    }
    catch(out_of_range OOR)
    {
        cout << "out_of_range Exception caught" << endl;
    }
    catch(bad_alloc)
    {
        cout << "bad_alloc Exception caught" << endl;
    }
    catch(...)
    {
        cout << "Unknown Exception caught" << endl;
    }
    
    return 0;
}



// **************************
//     Function Definition
// **************************
void loadData(string fName, char fType, IncidentLog &MyIncidentLog)
{
    string fileProbMessage = "";
    
    //open the input data file
    fstream inFile;
    inFile.open(fName.c_str(), ios::in | ios::binary);
    
    //Check to see if file opened
    if(!inFile)
    {
        fileProbMessage = "Exception Thown -- File failed to open";
        
        //throw exception
        throw fileProbMessage;
        
    }
    
    HazMatData MyHMDataStruct;
    
    // read each file record into a HazMat Data struct
    inFile.read(reinterpret_cast<char *>(& MyHMDataStruct), sizeof(MyHMDataStruct));
    while (!inFile.eof())
    {
        // Instantiate FatalityOrInjury object
        // Pass struct to class' convert constructor
        if((MyHMDataStruct.fatal != 0) || (MyHMDataStruct.injure != 0))
        {

            FatalityOrInjury FOI(MyHMDataStruct);
            MyIncidentLog.appendObject(FOI);
        }
        
        // Instantiate LossOrDamage Object
        // Pass struct to class' convert constructor
        else
        {
            LossOrDamage LOD(MyHMDataStruct);
            MyIncidentLog.appendObject(LOD);
        }
        
        inFile.read(reinterpret_cast<char *>(& MyHMDataStruct), sizeof(MyHMDataStruct));
    }
    cout << "Leaving loadData function" << endl;
    inFile.close();
    
}
