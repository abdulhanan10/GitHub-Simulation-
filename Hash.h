//Hash Header 
#ifndef HASH_H
#define HASH_H
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<windows.h>

using namespace std;

//class of hash table for managing the users 
class HashTable {
private:
    static const int tableSize = 100;

    //class of hash node 
    class HashNode {
    public:
        string key;
        User* value;
        HashNode* next;

        //parameterized constructor 
        HashNode(string k, User* v);
    };

    HashNode* table[tableSize];
public:
    //default constructor 
    HashTable();

    //function to insert in the hash table 
    void insert(const string& key, User* value);

    //function for the hash function 
    int hashFunction(const string& key);

    //function to search for the user in the hash table 
    User* search(const string& key);

    //function to clean up dynamically allocated memory
    ~HashTable();
};

#endif 