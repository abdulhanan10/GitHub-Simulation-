//Repository_Implementation
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
Repository::FileNode::FileNode(File* f) :file(f), next(nullptr) { }

//parametrized constructor
Repository::CommitNode::CommitNode(Commit* c) :commit(c), next(nullptr) { }

//parametrized constructor
Repository::Repository(string name, bool priv) :repoName(name), isPrivate(priv), fileHead(nullptr), fileCount(0),
commitHead(nullptr), commitCount(0), forkCount(0) {

}

//function to get repository name 
string Repository::getRepoName() const
{
    return repoName;
}

//function to get that repository is private or not 
bool Repository::getIsPrivate() const
{
    return isPrivate;
}

//function to get file name
int Repository::getFileCount() const
{
    return fileCount;
}

//function to get the count of commit count
int Repository::getCommitCount() const
{
    return commitCount;
}

//function to get the count of fork 
int Repository::getForkCount() const
{
    return forkCount;
}

//function to add file in the repository 
void Repository::addFile(string fileName)
{
    File* newFile = new File(fileName);
    FileNode* newNode = new FileNode(newFile);
    newNode->next = fileHead;
    fileHead = newNode;
    fileCount++;
}

//function to delete file 
void Repository::deleteFile(string fileName)
{
    FileNode* current = fileHead;
    FileNode* prev = nullptr;

    while (current)
    {
        if (current->file->getFileName() == fileName)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                fileHead = current->next;
            }
            delete current->file;
            delete current;
            fileCount--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

//function to add commit 
void Repository::addCommit(string commitHash, string message)
{
    Commit* newCommit = new Commit(commitHash, message);
    CommitNode* newNode = new CommitNode(newCommit);
    newNode->next = commitHead;
    commitHead = newNode;
    commitCount++;
}

//function to delete the commit 
void Repository::deleteCommit(string commitHash)
{
    CommitNode* current = commitHead;
    CommitNode* prev = nullptr;

    while (current)
    {
        if (current->commit->getCommitHash() == commitHash)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                commitHead = current->next;
            }
            delete current->commit;
            delete current;
            commitCount--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

//function to view the status 
void Repository::viewStatus()
{
    cout << "Repository Name: " << repoName << endl;
    cout << "Visibility: " << (isPrivate ? "Private" : "Public") << endl;
    cout << "Files in Repository: " << endl;
    FileNode* filePtr = fileHead;
    while (filePtr)
    {
        cout << "* " << filePtr->file->getFileName() << endl;
        filePtr = filePtr->next;
    }
    cout << "Commits in Repository: " << endl;
    CommitNode* commitPtr = commitHead;
    while (commitPtr)
    {
        cout << "* Hash: " << commitPtr->commit->getCommitHash() << ", Message: " << 
            commitPtr->commit->getMessage() << endl;
        commitPtr = commitPtr->next;
    }
    cout << "Fork Count: " << forkCount << endl;
}

//function to increment the fork count
void Repository::incrementForkCount()
{
    forkCount++;
}

//function to clean up dynamically allocated memory
Repository::~Repository()
{
    FileNode* filePtr = fileHead;
    while (filePtr)
    {
        FileNode* temp = filePtr;
        filePtr = filePtr->next;
        delete temp->file;
        delete temp;
    }

    CommitNode* commitPtr = commitHead;
    while (commitPtr)
    {
        CommitNode* temp = commitPtr;
        commitPtr = commitPtr->next;
        delete temp->commit;
        delete temp;
    }
}


