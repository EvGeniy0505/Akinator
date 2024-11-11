#ifndef TREE
#define TREE

#include <stdio.h>

struct Node
{
    char* data;
    Node* left;
    Node* right;
};

Node* Tree_ctor(const char* first_question);

Node* Create_node(char* new_question);

// void Insert(Node* nd, char* new_question);

void Dot_file_compile(int num_pucture);

void Dot_dump(Node* nd, int num_graph);

void Print(Node* nd);

void Tree_dtor(Node* nd);

void akinator(Node* nd);


#endif