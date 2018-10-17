//
//  HashTable.h
//  HashTable
//
//  Created by Anne Freeman on 12/6/17.
//  Copyright © 2017 Anne Freeman. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h


#include <string>
#include "HashTableLevel2.h"
#include "math.h"

using std::string;

class HashTable{
private:
    int collisions;
    int wordCount;
    unsigned int tableSize;
    bool secondLevelHashExists;
    HashTableLevel2 *ht;
    int hash(string key);
public:
    HashTable(unsigned int t = 107);
    ~HashTable();
    bool contains(string &x);
    void makeEmpty();
    void insert(string &x);
    int size(){return tableSize;}
    int getCollisions(){return collisions;}
    int getWordCount(){return wordCount;} 
};

HashTable::HashTable(unsigned int t)
{
    collisions = 0;
    wordCount = 0;
    tableSize = t;
    // create outer hash table
    ht = new HashTableLevel2[t];
    // each cell contains a HashTable with tableSize^2 size
    // Access the inner table by ht[index]
    for(int i = 0; i<tableSize; i++)
    {
        ht[i] = *new HashTableLevel2(t*t);
    }
}

HashTable::~HashTable()
{
    delete [] ht;
}

// Function to hash into the outer table
int HashTable::hash(string key)
{
    int hashVal = 13;
    for(int i = 0; i < key.length(); i++)
    {
        hashVal = hashVal*37 + key[i];
    }
    return hashVal % tableSize;
}

bool HashTable::contains(string &x)
{
    // get index where it was hashed in outer table
    int index = hash(x);
    // call in inner table
    return ht->contains(ht[index], x);
}

void HashTable::insert(string &x)
{
    int index = hash(x);
    if(!(ht[index].isFirstEmpty(ht[index])))
    {
        // there is already a node in that index
        collisions++;
    }
    if(!(ht->contains(ht[index], x)))
    {
        // insert using HashTableLevel2 function
        // only insert if not already in table -- no repeats
        ht->insert(ht[index], x);
        //ht[index].insert(x);
    }
}

#endif /* HashTable_h */
