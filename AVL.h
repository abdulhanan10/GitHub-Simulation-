//AVL Header 
#ifndef AVL_H
#define AVL_H
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<windows.h>

using namespace std;

//class of avl node 
class AVLNode {
public:
    Repository* repository;
    AVLNode* left;
    AVLNode* right;
    int height;

    //parametrized constructor
    AVLNode(Repository* repo);
};

//class of avl treee
class AVLTree {
private:
    AVLNode* root;
public:
    //default constructor 
    AVLTree();

    //function to get the height of the avl tree
    int height(AVLNode* node);

    //function to get the balance factor 
    int balanceFactor(AVLNode* node);

    //function to rotate the tree right 
    AVLNode* rotateRight(AVLNode* y);

    //function to rotate the tree left
    AVLNode* rotateLeft(AVLNode* x);

    //function to insert the elements into the tree
    AVLNode* insert(AVLNode* node, Repository* repo);

    //helping function to insert the elements into the tree
    void insert(Repository* repo);

    //function to find the minimum value node 
    AVLNode* minValueNode(AVLNode* node);

    //function to delete the node 
    AVLNode* deleteNode(AVLNode* root, const string& repoName);

    //helping function to delete the node 
    void remove(const string& repoName);

    //function to search for the repository  
    Repository* search(const string& repoName) const;

    //function to clean up the repository 
    void cleanup(AVLNode* node);

    //function to clean up dynamically allocated memory
    ~AVLTree();
};
#endif