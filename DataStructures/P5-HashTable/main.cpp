//
//  main.cpp
//  HashTable
//
//  Created by Anne Freeman on 12/6/17.
//  Copyright © 2017 Anne Freeman. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "HashTable.h"
using namespace std;

int main(int argc, const char * argv[])
{
    // argc should be 3 - need two files to run program
    if ( argc != 3 )
    {
        // output error message
        cout << "Please enter two files" << endl;
        return 0;
    }
    
    
    // open the first file -- the dictionary file
    HashTable h1;
    int incorrectCount = 0;
    
    string fname = argv[1];
    ifstream inFile;
    inFile.open(fname.c_str());
    
    // check to see if file opening was successful
    if (!inFile.is_open())
    {
        cout << "\nERROR: Could not open file\n\n";
        return 0;
    }
    
    string dictWord;
    double sumHashTime =0;
    clock_t timeBegin, timeEnd;
    timeBegin = clock();
    while(inFile >> dictWord)
    {
        h1.insert(dictWord);
    }
    timeEnd = clock();
    sumHashTime += ((double)(timeEnd-timeBegin))/CLOCKS_PER_SEC;
    cout << endl;
    
    // open second file -- personal file
    string filename = argv[2];
    ifstream iFile;
    iFile.open(filename.c_str());
    // check to see if file opening was successful
    if (!iFile)
    {
        return 0;
    }
    
    string checkWord;
    while(iFile >> checkWord)
    {
        if(h1.contains(checkWord))
        {
            //word contained in file!
        }
        else
        {
            //word not contained in file
            //cout << checkWord << endl;
            incorrectCount++;
        }
    }
    cout << "Time to make Hash Table: " << sumHashTime << endl;
    cout << "Number of incorrect words: " << incorrectCount << endl;
    return 0;
}
