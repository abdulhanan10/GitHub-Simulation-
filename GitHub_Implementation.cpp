//GitHub_Implementation
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
GitHub::UserNode::UserNode(User* u) :user(u), next(nullptr) { }

//default constructor 
GitHub::GitHub() :userHead(nullptr), userCount(0) {}

//function to register the user into the github 
void GitHub::registerUser(const string& username, const string& password)
{
    User* newUser = new User(username, password);
    UserNode* newNode = new UserNode(newUser);
    newNode->next = userHead;
    userHead = newNode;
    userCount++;
}

//function to login the user into the github
bool GitHub::login(const string& username, const string& password)
{
    UserNode* current = userHead;
    while (current)
    {
        if (current->user->getUsername() == username && current->user->getPassword() == password)
        {
            cout << "| --- Login successful! --- |" << endl;
            return true;
        }
        current = current->next;
    }
    cout << "| --- Invalid Username or Password! Try Again. --- |" << endl;
    return false;
}

//function to get the user 
User* GitHub::getUser(const string& username) const
{
    UserNode* current = userHead;
    while (current)
    {
        if (current->user->getUsername() == username)
        {
            return current->user;
        }
        current = current->next;
    }
    return nullptr;
}

//function to fork repository 
void GitHub::forkRepository(const string& username, const string& targetUsername, const string& repoName)
{
    User* user = getUser(username);
    User* targetUser = getUser(targetUsername);
    if (user && targetUser)
    {
        Repository* repo = targetUser->getRepository(repoName);
        if (repo && !repo->getIsPrivate())
        {
            user->createRepository(repoName + " - Fork", repo->getIsPrivate());
            repo->incrementForkCount();
            cout << "| --- Repository Forked Successfully! --- |" << endl;
        }
        else
        {
            cout << "| --- Repository is Private! OR Does Not Exist. --- |" << endl;
        }
    }
    else
    {
        cout << "| --- Invalid Username! --- |" << endl;
    }
}

//function to write all the data into the csv file 
void GitHub::writeCSV()
{
    ofstream csvFile("repositories.csv"); 

    if (!csvFile.is_open())
    { 
        cout << "| --- ERROR! Unable to Open CSV File! --- |" << endl;
        return;
    }

    UserNode* current = userHead;
    while (current)
    {
        User* user = current->user;

        //this will find the strongest match of the repository node type
        User::RepositoryNode* repoNode = user->getRepositoryHead(); 

        while (repoNode)
        {
            Repository* repo = repoNode->repository;

            //this will write username into the csv file 
            csvFile << user->getUsername() << ","; 

            //this will write the repository name, check it is private or public and write it into the file, 
            //write the file count, commit count, and fork count 
            csvFile << repo->getRepoName() << ","
                << (repo->getIsPrivate() ? "Private" : "Public") << ","
                << repo->getFileCount() << ","
                << repo->getCommitCount() << ","
                << repo->getForkCount() << endl;

            //jump towards the next repository 
            repoNode = repoNode->next; 
        }

        //jump towards the next user 
        current = current->next; 
    }

    csvFile.close(); 
    cout << "| --- Changes Saved! In the CSV file 'repositories.csv'! --- |" << endl;
}

//function to clean up dynamically allocated memory
GitHub::~GitHub()
{
    UserNode* current = userHead;
    while (current)
    {
        UserNode* temp = current;
        current = current->next;
        delete temp->user;
        delete temp;
    }
}