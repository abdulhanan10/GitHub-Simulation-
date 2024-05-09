//Graph Header 
#ifndef GRAPH_H
#define GRAPH_H
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<windows.h>

using namespace std;

//class of graph
class Graph {
    int size;
    struct Vertex;

    //class of edges 
    class Edge {
    public:
        Vertex* vertex;
        Edge* next;

        //parametrized constructor
        Edge(Vertex* v);
    };

    //class of vertex 
    class Vertex {
    public:
        User* user;
        Vertex* next;
        Edge* edge;

        //parametrized constructor
        Vertex(User* u);
    };
    Vertex* vertices;
public:
    //parametrized constructor
    Graph(int s);

    //function to add vertex 
    void addVertex(User* user);

    //function to add edges  
    void addEdge(User* from, User* to);

    //function to find the vertex 
    Vertex* findVertex(User* user);

    //function to display 
    void display();

    //function to clean up dynamically allocated memory
    ~Graph();

};

#endif 