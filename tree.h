#include <stdio.h>


struct Node
{
    char* data;
    Node* left;
    Node* right;
};

Node* Tree_ctor(int first_tree_val);

Node* Create_node(int new_val);

void Insert(Node* nd, int new_val);

void Dot_file_compile(int num_pucture);

void Dot_dump(Node* nd, int num_graph);

void Print(Node* nd);

void Tree_dtor(Node* nd);
