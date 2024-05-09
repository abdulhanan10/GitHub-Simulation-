//Graph_Implementation
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
Graph::Edge::Edge(Vertex* v) :vertex(v), next(nullptr) { }

//parametrized constructor
Graph::Vertex::Vertex(User* u) :user(u), next(nullptr), edge(nullptr) { }

//parametrized constructor
Graph::Graph(int s) :size(s), vertices(nullptr) { }

//function to add vertex 
void Graph::addVertex(User* user)
{
    Vertex* newVertex = new Vertex(user);
    newVertex->next = vertices;
    vertices = newVertex;
}

//function to add edges 
void Graph::addEdge(User* from, User* to)
{
    Vertex* fromVertex = findVertex(from);
    Vertex* toVertex = findVertex(to);

    if (fromVertex && toVertex)
    {
        Edge* newEdge = new Edge(toVertex);
        newEdge->next = fromVertex->edge;
        fromVertex->edge = newEdge;
    }
}

//function to find the vertex 
Graph::Vertex* Graph::findVertex(User* user)
{
    Vertex* current = vertices;
    while (current)
    {
        if (current->user == user)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

//function to display 
void Graph::display()
{
    Vertex* current = vertices;
    while (current)
    {
        cout << current->user->getUsername() << " -> ";
        Edge* edge = current->edge;
        while (edge)
        {
            cout << edge->vertex->user->getUsername() << " -> ";
            edge = edge->next;
        }
        cout << "nullptr" << endl;
        current = current->next;
    }
}

//function to clean up dynamically allocated memory
Graph::~Graph()
{
    //deleting all edges
    Vertex* currentVertex = vertices;
    while (currentVertex)
    {
        Edge* currentEdge = currentVertex->edge;
        while (currentEdge)
        {
            Edge* tempEdge = currentEdge;
            currentEdge = currentEdge->next;
            delete tempEdge;
        }

        //first move to the next vertex and then delete the current vertex 
        Vertex* tempVertex = currentVertex;
        currentVertex = currentVertex->next;
        delete tempVertex;
    }
}
