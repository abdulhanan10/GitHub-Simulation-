//AVL_Implementation
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
AVLNode::AVLNode(Repository* repo) :repository(repo), left(nullptr), right(nullptr), height(1) { }

//default constructor 
AVLTree::AVLTree() :root(nullptr) { }

//function to get the height of the avl tree
int AVLTree::height(AVLNode* node)
{
    if (!node)
    {
        return 0;
    }
    return node->height;
}

//function to get the balance factor 
int AVLTree::balanceFactor(AVLNode* node)
{
    if (!node)
    {
        return 0;
    }
    return (height(node->left) - height(node->right));
}

//function to rotate the tree right 
AVLNode* AVLTree::rotateRight(AVLNode* y)
{
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

//function to rotate the tree left
AVLNode* AVLTree::rotateLeft(AVLNode* x)
{
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

//function to insert the elements into the tree
AVLNode* AVLTree::insert(AVLNode* node, Repository* repo)
{
    if (!node)
    {
        return new AVLNode(repo);
    }

    if (repo->getRepoName() < node->repository->getRepoName())
    {
        node->left = insert(node->left, repo);
    }
    else
    {
        node->right = insert(node->right, repo);
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    //LL case
    if (balance > 1 && repo->getRepoName() < node->left->repository->getRepoName())
    {
        return rotateRight(node);
    }

    //RR case
    if (balance < -1 && repo->getRepoName() > node->right->repository->getRepoName())\
    {
        return rotateLeft(node);
    }

    //LR case
    if (balance > 1 && repo->getRepoName() > node->left->repository->getRepoName())
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    //RL case
    if (balance < -1 && repo->getRepoName() < node->right->repository->getRepoName())
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

//helping function to insert the elements into the tree
void AVLTree::insert(Repository* repo)
{
    root = insert(root, repo);
}

//function to find the minimum value node 
AVLNode* AVLTree::minValueNode(AVLNode* node)
{
    AVLNode* current = node;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

//function to delete the node
AVLNode* AVLTree::deleteNode(AVLNode* root, const string& repoName)
{
    if (!root)
    {
        return root;
    }

    if (repoName < root->repository->getRepoName())
    {
        root->left = deleteNode(root->left, repoName);
    }
    else if (repoName > root->repository->getRepoName())
    {
        root->right = deleteNode(root->right, repoName);
    }
    else
    {
        if (!root->left || !root->right)
        {
            AVLNode* temp = root->left ? root->left : root->right;
            if (!temp)
            {
                temp = root;
                root = nullptr;
            }
            else
            {
                *root = *temp;
            }
            delete temp;
        }
        else
        {
            AVLNode* temp = minValueNode(root->right);
            root->repository = temp->repository;
            root->right = deleteNode(root->right, temp->repository->getRepoName());
        }
    }

    if (!root)
    {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = balanceFactor(root);

    //LL case
    if (balance > 1 && balanceFactor(root->left) >= 0)
    {
        return rotateRight(root);
    }

    //LR case
    if (balance > 1 && balanceFactor(root->left) < 0)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    //RR case
    if (balance < -1 && balanceFactor(root->right) <= 0)
    {
        return rotateLeft(root);
    }

    //RL case
    if (balance < -1 && balanceFactor(root->right) > 0)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

//helping function to delete the node 
void AVLTree::remove(const string& repoName)
{
    root = deleteNode(root, repoName);
}

//function to search for the repository
Repository* AVLTree::search(const string& repoName) const
{
    AVLNode* current = root;
    while (current)
    {
        if (current->repository->getRepoName() == repoName)
        {
            return current->repository;
        }
        if (repoName < current->repository->getRepoName())
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return nullptr;
}

//function to clean up the repository 
void AVLTree::cleanup(AVLNode* node)
{
    if (node)
    {
        cleanup(node->left);
        cleanup(node->right);
        delete node->repository;
        delete node;
    }
}

//function to clean up dynamically allocated memory
AVLTree::~AVLTree()
{
    cleanup(root);
}
