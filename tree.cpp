#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tree.h"
#include "user_answer.h"
#include "file_read_and_write.h"

Node* Tree_ctor(FILE* file)
{
    Node* nd = {};

    from_file_to_tree(file, &nd);

    return nd;
}

// void Insert(Node* nd, char* new_val)
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

    putc('[', stdout);

    fprintf(stdout, "\"%s\"", nd -> data);

    if(nd -> left)
        Print_to_file(nd -> left, stdout);

    if(nd -> right)
        Print_to_file(nd -> right, stdout);

    printf("]\n");
}

Node* Create_node(char* new_question)
{
    Node* nd = (Node*) calloc(1, sizeof(Node));

    nd -> data  = new_question;
    nd -> left  = NULL;
    nd -> right = NULL;

    return nd;
}
int max_deep = 0;
int find_tree_deep(Node* nd, int start_deep)
{
    if(!nd -> left && !nd -> right)
    {
        if(start_deep > max_deep)
            max_deep = start_deep;
        return 0;
    }

    if(nd -> left)
    {
        find_tree_deep(nd -> left, start_deep + 1);
    }
    if(nd -> right)
    {
        find_tree_deep(nd -> right, start_deep + 1);
    }

    return max_deep;
}

static void Print_tree_to_dot_file(Node* nd, FILE* f_dot)
{
    fprintf(f_dot, "\tnode%p[color=purple, label=\" %s\"]\n", &nd -> data, nd -> data);

    if(nd -> left)
    {
        fprintf(f_dot, "\tnode%p -> node%p[label=\"Да\", fontcolor=\"red\"];\n", &nd->data, &nd->left->data);
        Print_tree_to_dot_file(nd -> left, f_dot);
    }

    if(nd -> right)
    {
        fprintf(f_dot, "\tnode%p -> node%p[label=\"Нет\", fontcolor=\"red\"];\n", &nd->data, &nd->right->data);
        Print_tree_to_dot_file(nd -> right, f_dot);
    }
}

void Dot_dump(Node* nd, int num_graph)
{
    FILE* f_dot = fopen("output/akinator.dot", "w");

    assert(f_dot);
    assert(nd);
    if(ferror(f_dot))
        fprintf(stderr, "FILE OPEN ERROR!!!\n");

    fprintf(f_dot, "digraph TREE%d {\n\tbgcolor = \"lightgrey:lightblue\";\n", num_graph);

    fprintf(f_dot, "\tlabel=\"Akinator by Evgeniy Rogov\";\n\tfontsize=30;\n\tfontname=\"Times-Roman\";\n\tlabelloc=\"t\";\n");

    Print_tree_to_dot_file(nd, f_dot);

    fprintf(f_dot, "}");

    fclose(f_dot);

    Dot_file_compile(num_graph);
}

void Dot_file_compile(int num_pucture)
{
    char com1[48] = "dot -Tpng output/akinator.dot > output/akinator";
    char com2[5]  = ".png";

    char com[56] = "";

    char num_str[3] = "";

    snprintf(num_str, sizeof(num_str), "%d", num_pucture);

    sprintf(com, "%s%s%s", com1, num_str, com2);

    system(com);
}

void Tree_dtor(Node* nd)
{
    assert(nd);

    if(nd -> data)
        free(nd -> data);

    if(nd -> right)
        Tree_dtor(nd -> right);

    if(nd -> left)
        Tree_dtor(nd -> left);

    free(nd);
}