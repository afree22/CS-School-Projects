
/*
 *  aof7P1.cpp
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
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "IncidentLog.h"
#include "PHMSA7000.h"

//function prototype
void loadData(string fName, string fType, IncidentLog &MyIncidentLog);

// *******************
//   Entering Main
// *******************
int main(int argc, char * argv[])
{

    
    string inputFileName = " ";
    cout << argv[0] << endl << argv[1] << endl << argv[2];
    
    if ( argc < 3)
    {
        // not enough command line arguments
        cout << "Please pass the full path and file name of the input data file as";
        cout << "a command line argument." << endl;
        cout << "The program cannot continue..." << endl;
        
    }
    else if (string(argv[2]) != "b" && string(argv[2]) != "t" && string(argv[2]) != "f")
    {
        cout << "must use a valid file type" << endl;
    }
    else if (string(argv[2]) != "b")
    {
        cout << "Can only process binary files at this time" << endl;
        cout << "Program cannot continue..." << endl;
    }
    else
    {

        inputFileName = string(argv[1]);
        
        fstream inFile(inputFileName.c_str(), ios::in | ios::binary);

        
        if (!inFile)
        {
            cout << "file: " << inputFileName << "\nfailed to open\n";
        }
        else
        {
            IncidentLog MyIncidentLog;
            string fileType = string(argv[2]);
            loadData(inputFileName, fileType, MyIncidentLog);
            MyIncidentLog.displayReport();
            
        }
        inFile.close();
        
    }
    return 0;
}



// **************************
//     Function Definition
// **************************
void loadData(string fName, string fType, IncidentLog &MyIncidentLog)
{
    //open the input data file
    fstream inFile;
    inFile.open(fName.c_str(), ios::in | ios::binary);
    
    if(inFile)
    {
        
        HazMatData HMD1;
        
        inFile.read(reinterpret_cast<char *>(& HMD1), sizeof(HMD1));
        while (!inFile.eof())
        {
            //HMD1 ----> HazMat7k
            HazMat7k MyHazMat7k(HMD1);
            
            
            // HazMat7k attached to Incident Log
            MyIncidentLog.appendObject(MyHazMat7k);
            
            inFile.read(reinterpret_cast<char *>(& HMD1), sizeof(HMD1));
        }
        
        inFile.close();
    }
    else
    {
        cout << "file failed to open" << endl;
    }
}
