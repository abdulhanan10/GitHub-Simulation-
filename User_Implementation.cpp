//User_Implementation
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
User::FollowerNode::FollowerNode(User* f) :follower(f), next(nullptr) { }

//parametrized constructor
User::FollowingNode::FollowingNode(User* f) :following(f), next(nullptr) { }

//parametrized constructor
User::RepositoryNode::RepositoryNode(Repository* r) :repository(r), next(nullptr) { }

//parametrized constructor
User::User(string uname, string pwd) :username(uname), password(pwd), followerHead(nullptr), 
followerCount(0), followingHead(nullptr), followingCount(0), repositoryHead(nullptr) {
  
}

//function to get the username
string User::getUsername() const
{
    return username;
}

//function to get the password 
string User::getPassword() const
{
    return password;
}

//function to add the followers
void User::addFollower(User* follower)
{
    FollowerNode* newNode = new FollowerNode(follower);
    newNode->next = followerHead;
    followerHead = newNode;
    followerCount++;
    
    //adding this user to the follower's following list
    follower->addFollowing(this); 
}

//function to add the following 
void User::addFollowing(User* following)
{
    FollowingNode* newNode = new FollowingNode(following);
    newNode->next = followingHead;
    followingHead = newNode;
    followingCount++;
}

//function to remove the followers
void User::removeFollower(User* follower)
{
    FollowerNode* current = followerHead;
    FollowerNode* prev = nullptr;
    while (current)
    {
        if (current->follower == follower)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                followerHead = current->next;
            }
            delete current;
            followerCount--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

//function to remove the following 
void User::removeFollowing(User* following)
{
    FollowingNode* current = followingHead;
    FollowingNode* prev = nullptr;
    while (current)
    {
        if (current->following == following)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                followingHead = current->next;
            }
            delete current;
            followingCount--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

//function to display the followers 
void User::displayFollowers()
{
    cout << "Followers:" << endl;
    FollowerNode* current = followerHead;
    while (current)
    {
        cout << "- " << current->follower->getUsername() << endl;
        current = current->next;
    }
}

//function to displat the following 
void User::displayFollowing()
{
    cout << "Following:" << endl;
    FollowingNode* current = followingHead;
    while (current)
    {
        cout << "- " << current->following->getUsername() << endl;
        current = current->next;
    }
}

//function to create the repository 
void User::createRepository(string repoName, bool isPrivate)
{
    Repository* newRepo = new Repository(repoName, isPrivate);
    RepositoryNode* newNode = new RepositoryNode(newRepo);
    newNode->next = repositoryHead;
    repositoryHead = newNode;
}

//function to delete the repository
void User::deleteRepository(string repoName)
{
    RepositoryNode* current = repositoryHead;
    RepositoryNode* prev = nullptr;
    while (current)
    {
        if (current->repository->getRepoName() == repoName)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                repositoryHead = current->next;
            }
            delete current->repository;
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

//function to get the repository
Repository* User::getRepository(const string& repoName) const
{
    RepositoryNode* current = repositoryHead;
    while (current)
    {
        if (current->repository->getRepoName() == repoName)
        {
            return current->repository;
        }
        current = current->next;
    }
    return nullptr;
}

//function to get the repository head  
User::RepositoryNode* User::getRepositoryHead() const
{
    return repositoryHead;
}

//function to display the repository 
void User::displayRepository()
{
    cout << "Repositories:" << endl;
    RepositoryNode* repoNode = repositoryHead;
    while (repoNode)
    {
        Repository* repo = repoNode->repository;
        cout << "- " << repo->getRepoName() << endl;
        repoNode = repoNode->next;
    }
}

//function to view the user profile 
void User::viewProfile()
{
    cout << "Username: " << username << endl;

    //calling the display followers function 
    displayFollowers();

    //calling the display users that this user is following to 
    displayFollowing();

    //calling the display repositories function 
    displayRepository();
}

//function to clean up dynamically allocated memory
User::~User()
{
    FollowerNode* currentFollower = followerHead;
    while (currentFollower)
    {
        FollowerNode* tempFollower = currentFollower;
        currentFollower = currentFollower->next;
        delete tempFollower;
    }

    FollowingNode* currentFollowing = followingHead;
    while (currentFollowing)
    {
        FollowingNode* tempFollowing = currentFollowing;
        currentFollowing = currentFollowing->next;
        delete tempFollowing;
    }

    RepositoryNode* currentRepo = repositoryHead;
    while (currentRepo)
    {
        RepositoryNode* tempRepo = currentRepo;
        currentRepo = currentRepo->next;
        delete tempRepo->repository;
        delete tempRepo;
    }
}

