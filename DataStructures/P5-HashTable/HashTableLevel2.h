//
//  HashTableLevel2.h
//  HashTable
//
//  Created by Anne Freeman on 12/6/17.
//  Copyright © 2017 Anne Freeman. All rights reserved.
//

#ifndef HashTableLevel2_h
#define HashTableLevel2_h

using std::string;
using std::cout;
using std::endl;

class Node
{
public:
    string value;
    int key;
    int getKey(string value){return key;}
    Node(){value = "?"; key=0;}
    Node(string v){value = v;}
    Node(string v, int k) {value = v; key = k;}
};

class HashTableLevel2
{
private:
    int collisions;
    int wordCount;
    unsigned int innerTableSize;
    Node *arr;
    int hash(string key);
    int hash2(string key);
    int hash3(string key);
public:
    HashTableLevel2(unsigned int t = 541);
    ~HashTableLevel2();
    bool contains(HashTableLevel2 &ht, string &x);
    bool isFirstEmpty(HashTableLevel2 &ht);
    void insert(string &x);
    void insert(HashTableLevel2 &ht, string &x);
    int size() const;
    int getCollisions() const;
    int getWordCount() const;
};


bool HashTableLevel2:: isFirstEmpty(HashTableLevel2 &ht)
{
    bool returnVal = true; // assume empty
    if(ht.arr[0].value != "?")
    {
        returnVal = false;
    }
    return returnVal;
}


HashTableLevel2::HashTableLevel2(unsigned int t)
{
    collisions = 0;
    wordCount = 0;
    innerTableSize = t;
    arr = new Node[innerTableSize];
    for(int i = 0; i < innerTableSize; i++)
    {
        //-- denotes that there is no info in the node
        arr[i] = Node();
    }
    
}

HashTableLevel2::~HashTableLevel2()
{
    delete [] arr;
}

int HashTableLevel2::hash(string key)
{
    int hashVal = 17;
    for(int i = 0; i < key.length(); i++)
    {
        hashVal = hashVal*37 + key[i];
    }
    
    hashVal = hashVal %innerTableSize;
    if(hashVal<0)
        hashVal += innerTableSize;
    return hashVal;
}
int HashTableLevel2::hash2(string key)
{
    int hashVal = 31;
    for(int i = 0; i < key.length(); i++)
    {
        hashVal = hashVal*37 + key[i];
    }
    
    hashVal = hashVal %innerTableSize;
    if(hashVal<0)
        hashVal += innerTableSize;
    return hashVal;
}


bool HashTableLevel2::contains(HashTableLevel2 &ht, string &x)
{
   
    int index = hash(x);
    int index2 = hash2(x);
    
    bool found = false;
    if(ht.arr[index].value == x)
    {
        found =  true;
    }
    else if(ht.arr[index2].value == x)
    {
        found =  true;
    }
    return found;
}


void HashTableLevel2::insert(HashTableLevel2 &ht, string &x)
{
    Node addMe = *new Node(x);
    addMe.key = hash(x);
    if(ht.arr[addMe.key].value != "?")
    {
        // there is a collision
        // hash the key again
        addMe.key = hash2(x);
    }
    if(!(contains(ht, x)))
    {
        ht.arr[addMe.key].value = x;
        wordCount++;
    }
}

int HashTableLevel2::size() const
{
    return innerTableSize;
}

int HashTableLevel2::getWordCount() const
{
    return wordCount;
}

int HashTableLevel2::getCollisions() const
{
    return collisions;
}

#endif /* HashTableLevel2_h */
