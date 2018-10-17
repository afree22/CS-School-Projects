//
//  main.cpp
//  MinHeap
//
//  Created by Anne Freeman on 10/25/17.
//  Copyright © 2017 Anne Freeman. All rights reserved.
//

#include <iostream>
#include "MinHeap.h"
using namespace std;

int main(int argc, const char * argv[]) {
    
    MinHeap mh;
    bool keepLooping = true;
    while(keepLooping)
    {
        char cmd;
        int key;
        cout << "Enter command (a = add, r = remove, q = quit):" << endl;
        cin >> cmd;
        if(cmd == 'q')
        {
            keepLooping = false;
        }
        else
        {
            if(cmd == 'a')
            {
                cin >> key;
                mh.insert(key);
                mh.print(0);

            }
            else if(cmd == 'r')
            {
                if(mh.getNumNodes() > 0)
                {
                    mh.remove();
                    mh.print(0);
                }
                else
                {
                    cout << "Cannot remove node, no nodes on heap" << endl;
                }
            }
        }

    }
    return 0;
}
