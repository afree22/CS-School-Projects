//
//  main.cpp
//  aof7P1
//
//  Created by Anne Freeman on 9/28/18.
//  Copyright © 2018 Anne Freeman. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <iomanip>
#include "OrderedList.h"
#include "MTFList.h"

using namespace std;

int main(int argc, const char * argv[]) {
    clock_t timeBegin, timeEnd;
    string fileName;
    string trash;
    int lengthList;
    int numQueries;
    int query;
    
    // get file name from command line argument
    fileName = string(argv[1]);
    
    ifstream inFile;
    inFile.open(fileName.c_str());
    
    if(!inFile)
    {
        cout << "could not open file" << endl;
        return 0;
    }
    
    /// TEST THE ORDERED LIST
    
    timeBegin = clock(); // start clock
    OrderedList orderedList(fileName); // add items to orderedList & sort
    getline(inFile, trash); // gets the first line
    getline(inFile, trash); // gets the second line
    
    // Gets number of queries and searches data structure for
    inFile >> numQueries;
    for (int i = 0; i < numQueries; i++)
    {
        inFile >> query;
        orderedList.binarySearch(query);
    }
    timeEnd = clock();
    double ordered_totalTime = (double)(timeEnd - timeBegin)/CLOCKS_PER_SEC;
    inFile.close();
    
    
    
    // TEST MTF LIST
    ifstream inFile2;
    inFile2.open(fileName.c_str());
    
    timeBegin = clock(); // start clock
    MTFList mtflist(fileName);
    
    getline(inFile2, trash); // gets the first line
    getline(inFile2, trash); // gets the second line
    
    // Gets number of queries and searches data structure for
    inFile2 >> numQueries;
    for (int i = 0; i < numQueries; i++)
    {
        inFile2 >> query;
        mtflist.sequentialSearch(query);
    }
    timeEnd = clock(); // end clock
    double  mtf_totalTime = (double)(timeEnd - timeBegin)/CLOCKS_PER_SEC;
    inFile2.close();
    
    cout << "Time for ordered list: " << ordered_totalTime << endl;
    cout << "Time for MTFList: " << mtf_totalTime << endl;
    
    if (ordered_totalTime > mtf_totalTime)
        cout << "MTFList is faster" << endl;
    else if (mtf_totalTime > ordered_totalTime)
        cout << "OrderedList is faster" << endl;
    else
        cout << "The two take the same time" << endl;
    
 
    return 0;
}
