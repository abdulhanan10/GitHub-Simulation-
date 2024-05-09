//Commit_Implementation
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

//parametrized constructor
Commit::Commit(string hash, string msg) :commitHash(hash), message(msg) { }

//function to get commit hash
string Commit::getCommitHash() const
{
    return commitHash;
}

//function to get message
string Commit::getMessage() const
{
    return message;
}