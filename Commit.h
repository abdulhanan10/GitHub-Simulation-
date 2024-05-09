//Commit Header 
#ifndef COMMIT_H
#define COMMIT_H
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<windows.h>

using namespace std;

//class of commit 
class Commit {
private:
    string commitHash;
    string message;
public:
    //parametrized constructor
    Commit(string hash, string msg);

    //function to get commit hash
    string getCommitHash() const;

    //function to get message 
    string getMessage() const;  
};
#endif 
