//Repository Header 
#ifndef REPOSITORY_H
#define REPOSITORY_H
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<windows.h>

using namespace std;

//class of repository 
class Repository {
private:
    string repoName;
    bool isPrivate;
    int fileCount;
    int commitCount;
    int forkCount;

    //class of file node, using linked list for files and commits
    class FileNode {
    public:
        File* file;
        FileNode* next;

        //parametrized constructor 
        FileNode(File* f);
    };
    FileNode* fileHead;

    //class of commit node 
    class CommitNode {
    public:
        Commit* commit;
        CommitNode* next;
        
        //parametrized constructor
        CommitNode(Commit* c);
    };
    CommitNode* commitHead;
public:
    //parametrized constructor
    Repository(string name, bool priv);

    //function to get repository name 
    string getRepoName() const;

    //function to get that repository is private or not 
    bool getIsPrivate() const;

    //function to get file name 
    int getFileCount() const;

    //function to get the count of commit count 
    int getCommitCount() const;

    //function to get the count of fork 
    int getForkCount() const;

    //function to add file in the repository 
    void addFile(string fileName);

    //function to delete file 
    void deleteFile(string fileName);

    //function to add commit 
    void addCommit(string commitHash, string message);

    //function to delete the commit 
    void deleteCommit(string commitHash);

    //function to view the stats 
    void viewStatus();

    //function to increment the fork count 
    void incrementForkCount();

    //function to clean up dynamically allocated memory
    ~Repository();

};

#endif 
