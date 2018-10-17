//
//  main.cpp
//  BTree
//
//  Created by Anne Freeman on 11/16/17.
//  Copyright © 2017 Anne Freeman. All rights reserved.
//

#include<fstream>
#include<string>
#include<iostream>
#include<sstream>
#include "BTree.h"

using namespace std;

int main(int argc, const char * argv[])
{
    int maxTerms;
    string fname = argv[1];
    ifstream inFile;
    inFile.open(fname.c_str());
    
    if(!inFile)
    {
        cout << "File failed to open" << endl;
    }
    
    else
    {
        inFile >> maxTerms;
        BTree bt(maxTerms);
        int addKey;
        while(inFile >> addKey)
        {
            bt.insert(addKey);
            bt.print();
            cout << endl << endl;
        }
        cout << endl;
        cout << "You have created an: "<< maxTerms << "-ary B-Tree" << endl;
        cout << "The current state of the B-Tree is displayed below:" << endl;
        bt.print();
        cout << endl;
        
        // User Interface Menu
        bool keepLooping = true;
        while(keepLooping)
        {
            char cmd;
            int key;
            cout << "Enter command (a = add, r = remove, p = print, q = quit):" << endl;
            cin >> cmd;
            switch (cmd)
            {
                case 'q':
                    keepLooping=false;
                    break;
                case 'a':
                    cin >> key;
                    bt.insert(key);
                    bt.print();
                    cout << endl;
                    break;
                case 'r':
                    cin >> key;
                    bt.remove(key);
                    bt.print();
                    cout << endl;
                    break;
                case 'p':
                    bt.print();
                    cout << endl;
                    break;
                default:
                    break;
            }
            cout << endl;
        }
        return 0;
    }
}
