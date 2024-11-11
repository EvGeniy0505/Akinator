#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tree.h"
#include "user_answer.h"

Node* Tree_ctor(char* first_question)
{
    Node* nd = Create_node(first_question);

    return nd;
}

// void Insert(Node* nd, char* new_vca)
// {
//     if(!nd)   return;

//     if(new_val < nd -> data)
//     {
//         Insert(nd -> left, new_val);

//         if(nd -> left == NULL)
//             nd -> left = (Node*)Create_node(new_val);
//     }
//     else
//     {
//         Insert(nd -> right, new_val);

//         if(nd -> right == NULL)
//             nd -> right = (Node*)Create_node(new_val);
//     }
// }


void Print(Node* nd)
{
    if(!nd)   return;

    putchar('(');

    if(nd -> left)
        Print(nd -> left);

    printf("%s", nd -> data);

    if(nd -> right)
        Print(nd -> right);

    printf(")");
}

Node* Create_node(char* new_question)
{
    Node* nd = (Node*) calloc(1, sizeof(Node));

    nd -> data  = new_question;
    nd -> left  = NULL;
    nd -> right = NULL;

    return nd;
}

void Print_tree_to_dot_file(Node* nd, FILE* f_dot)
{
    fprintf(f_dot, "\tnode%p[shape=Mrecord, color=purple, label=\" {{<f0> data=%s} | { <l>LEFT | <r>RIGHT}}\"]\n", &nd -> data, nd -> data);

    if(nd -> left)
    {
        fprintf(f_dot, "\tnode%p:<l> -> node%p;\n", &nd->data, &nd->left->data);
        Print_tree_to_dot_file(nd -> left, f_dot);
    }

    if(nd -> right)
    {
        fprintf(f_dot, "\tnode%p:<r> -> node%p;\n", &nd->data, &nd->right->data);
        Print_tree_to_dot_file(nd -> right, f_dot);
    }
}

void Dot_dump(Node* nd, int num_graph)
{
    FILE* f_dot = fopen("output/tree.dot", "w");

    assert(f_dot);
    assert(nd);
    if(ferror(f_dot))
        fprintf(stderr, "FILE OPEN ERROR!!!\n");

    fprintf(f_dot, "digraph TREE%d {\n\tbgcolor = \"lightgrey:lightblue\";\n", num_graph);

    fprintf(f_dot, "\tlabel=\"TREE BY Evgeniy Rogov\";\n\tfontsize=30;\n\tfontname=\"Times-Roman\";\n\tlabelloc=\"t\";\n");

    Print_tree_to_dot_file(nd, f_dot);

    fprintf(f_dot, "}");

    fclose(f_dot);

    Dot_file_compile(num_graph);
}

void Dot_file_compile(int num_pucture)
{
    char com1[40] = "dot -Tpng output/tree.dot > output/tree";
    char com2[5]  = ".png";

    char com[47] = "";

    char num_str[3] = "";

    snprintf(num_str, sizeof(num_str), "%d", num_pucture);

    sprintf(com, "%s%s%s", com1, num_str, com2);

    system(com);
}

void Tree_dtor(Node* nd)
{
    if(nd -> right)
        Tree_dtor(nd -> right);

    if(nd -> left)
        Tree_dtor(nd -> left);

    free(nd);
}