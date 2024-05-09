//Hash_Implementation
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<windows.h>
#include"Commit.h"
#include"File.h"
#include"Repository.h"
#include"User.h"
#include"Hash.h"
#include"AVL.h"
#include"Graph.h"
#include"GitHub.h"
using namespace std;

//parameterized constructor 
HashTable::HashNode::HashNode(string k, User* v) :key(k), value(v), next(nullptr) { }

//default constructor 
HashTable::HashTable()
{
    for (int i = 0; i < tableSize; ++i)
    {
        table[i] = nullptr;
    }
}

//function to insert in the hash table 
void HashTable::insert(const string& key, User* value)
{
    int index = hashFunction(key);
    if (!table[index])
    {
        table[index] = new HashNode(key, value);
    }
    else
    {
        HashNode* temp = table[index];
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = new HashNode(key, value);
    }
}

//function for the hash function 
int HashTable::hashFunction(const string& key)
{
    int hashValue = 0;
    for (char ch : key)
    {
        hashValue += ch;
    }
    return hashValue % tableSize;
}

//function to search for the user in the hash table
User* HashTable::search(const string& key)
{
    int index = hashFunction(key);
    HashNode* temp = table[index];
    while (temp)
    {
        if (temp->key == key)
        {
            return temp->value;
        }
        temp = temp->next;
    }
    return nullptr;
}

//function to clean up dynamically allocated memory
HashTable::~HashTable()
{
    for (int i = 0; i < tableSize; ++i)
    {
        HashNode* temp = table[i];
        while (temp)
        {
            HashNode* delNode = temp;
            temp = temp->next;
            delete delNode->value;
            delete delNode;
        }
    }
}