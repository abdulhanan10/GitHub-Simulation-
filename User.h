//User Header 
#ifndef USER_H
#define USER_H
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<windows.h>
using namespace std;

//class of user 
class User {
private:
    string username;
    string password;
    int followingCount;
    int followerCount;

    //class of follower node 
    class FollowerNode {
    public:
        User* follower;
        FollowerNode* next;

        //parametrized constructor
        FollowerNode(User* f);
    };

    //head of the followers list in linked list 
    FollowerNode* followerHead;

    //class of following node
    class FollowingNode {
    public:
        User* following;
        FollowingNode* next;

        //parametrized constructor
        FollowingNode(User* f);
    };
    FollowingNode* followingHead;
public:
    //class of repositiry node
    class RepositoryNode {
        public:
        Repository* repository;
        RepositoryNode* next;

        //parametrized constructor
        RepositoryNode(Repository* r);
    };
    RepositoryNode* repositoryHead;

    //parametrized constructor
    User(string uname, string pwd);

    //function to get the username 
    string getUsername() const;

    //function to get the password 
    string getPassword() const;

    //function to add the followers 
    void addFollower(User* follower);

    //function to add the following 
    void addFollowing(User* following);

    //function to remove the followers
    void removeFollower(User* follower);

    //function to remove the following 
    void removeFollowing(User* following);

    //function to display the followers 
    void displayFollowers();

    //function to displat the following 
    void displayFollowing();

    //function to create the repository 
    void createRepository(string repoName, bool isPrivate);

    //function to delete the repository 
    void deleteRepository(string repoName);

    //function to get the repository
    Repository* getRepository(const string& repoName) const;

    //function to get the repository head 
    RepositoryNode* getRepositoryHead() const;

    //function to display the repository 
    void displayRepository();

    //function to view the user profile 
    void viewProfile();

    //function to clean up dynamically allocated memory
    ~User();

};

#endif 
