

/*
 * aof7P4.cpp
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

#include "DateTime.h"
#include "IncidentLog.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;




//function prototype
void loadData(string, char, IncidentLog &);

/* *******************
**                  **
**   Entering Main  **
**                  **
// *******************/
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
            ProcessTimer pt;
            string inputFileName = " ";
            inputFileName = string(argv[1]);
            
            fstream inFile(inputFileName.c_str(), ios::in | ios::binary);
            
            
            IncidentLog MyIncidentLog;
            
            char fileType = '?';
            fileType = argv[2][0];
            
            loadData(inputFileName, fileType, MyIncidentLog);
            
            //starting the clock
            pt.setTimeStart(clock());
            
            //Display report in order from highest to lowest
            MyIncidentLog.displayReport();
            
            //ending the clock
            pt.setTimeEnd(clock());
            
            cout << pt << endl;
            
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

        // test to setIncidentCode
        // instatiate derived class
        // set to base
        if((MyHMDataStruct.fatal != 0) || (MyHMDataStruct.injure != 0))
        {
            FatalityOrInjury FOI(MyHMDataStruct);
            FOI.setIncidentCode('f');
            HazMat7k *addThis = &FOI;
            MyIncidentLog.appendObject(addThis);
            
        }
        else
        {
            LossOrDamage LOD(MyHMDataStruct);
            LOD.setIncidentCode('l');
            HazMat7k *addThis = &LOD;
            MyIncidentLog.appendObject(addThis);
        }
        
 
        inFile.read(reinterpret_cast<char *>(& MyHMDataStruct), sizeof(MyHMDataStruct));
    }

    inFile.close();
    
}


