#ifndef TREE
#define TREE

#include <stdio.h>

struct Node
{
    char* data;
    Node* left;
    Node* right;
};

Node* Tree_ctor(FILE* file);

Node* Create_node(char* new_question);

// void Insert(Node* nd, char* new_question);

void Dot_file_compile(int num_pucture);

void Dot_dump(Node* nd, int num_graph);

void Print_to_file(Node* nd, FILE* file);

void Print(Node* nd);

size_t count_symbls(FILE* all_file);

void Tree_dtor(Node* nd);

#endif