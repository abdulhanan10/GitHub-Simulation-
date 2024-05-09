//GitHub Header 
#ifndef GITHUB_H
#define GITHUB_H
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<windows.h>

using namespace std;

//clasd of git hub 
class GitHub {
private:
    //class of user node 
    class UserNode {
    public:
        User* user;
        UserNode* next;

        //parameterized constructor 
        UserNode(User* u);
    };

    UserNode* userHead;
    int userCount;
    AVLTree repositories;

public:
    //default constructor 
    GitHub();

    //function to register the user into the github 
    void registerUser(const string& username, const string& password);

    //function to login the user into the github
    bool login(const string& username, const string& password);

    //function to get the user  
    User* getUser(const string& username) const;

    //function to fork repository 
    void forkRepository(const string& username, const string& targetUsername, const string& repoName);

    //function to write all the data into the csv file 
    void writeCSV();

    //function to clean up dynamically allocated memory
    ~GitHub();
};

#endif 