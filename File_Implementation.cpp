//File_Implementation
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
File::File(string name) :fileName(name) { }

//function to get the file name
string File::getFileName() const
{
    return fileName;
}