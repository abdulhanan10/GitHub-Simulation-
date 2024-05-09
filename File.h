//File Header 
#ifndef FILE_H
#define FILE_H
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<windows.h>

using namespace std;

//class of File 
class File {
private:
    string fileName;
public:
    //parametrized constructor
    File(string name);

    //function to get the file name 
    string getFileName() const;
};

#endif
