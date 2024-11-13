#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

#include "tree.h"
#include "user_answer.h"

static const int MAX_STR_LEN = 100;

struct str_params
{
    char* str;
    size_t len;
};

static str_params read_str_from_buff(char* buff);
static void from_buff_to_tree(Node** nd, char** buff);
static void from_file_to_tree(FILE* file, Node** nd);

Node* Tree_ctor(FILE* file)
{
    Node* nd = {};

    from_file_to_tree(file, &nd);
    // fprintf(stderr, "nad = %p\n", nd);
    // Print(nd);

    return nd;
}

size_t count_symbls(FILE* all_file)
{
    assert(all_file);

    struct stat st;

    fstat(fileno(all_file), &st);

    return (size_t)st.st_size;
}

static void from_file_to_tree(FILE* file, Node** nd)
{
    size_t len_file = count_symbls(file);

    char* akinator_data = (char*) calloc(len_file, 1);

    fread(akinator_data, 1, len_file, file);

    char* buff = akinator_data;
    from_buff_to_tree(nd, &buff);

    free(akinator_data);
}

int a = 0;

static void from_buff_to_tree(Node** nd, char** buff)
{
    *buff += 2;  // проходим [ + кавычки

    str_params question = read_str_from_buff(*buff);

    *nd = Create_node(question.str);

    *buff += question.len + 1;  // строка плюс кавычки

    fprintf(stderr, "level = %d\n", a);
    fprintf(stderr, "nd = %p\n", nd);
    fprintf(stderr, "%s\n", question.str);
    fprintf(stderr, "%c\n", **buff);

    if(**buff == '[')
    {
        ++a;
        from_buff_to_tree(&((*nd) -> left), buff);
    }

    if(**buff == '[')
    {
        ++a;
        from_buff_to_tree(&((*nd) -> right), buff);
    }

    if(**buff == ']')
    {
        ++(*buff);
        --a;
        return;
    }
}

static str_params read_str_from_buff(char* buff)
{
    size_t i = 0; // TODO: rename

    while(buff[i] != '\"') // TODO: std funct
        ++i;

    char* str = (char*) calloc(i + 1, 1);

    for(size_t j = 0; j < i; j++) // TODO: std functions
    {
        str[j] = buff[j];
    }

    return {str, i};
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

void Print_to_file(Node* nd, FILE* file)
{
    if(!nd)   return;

    putc('[', file);

    fprintf(file, "\"%s\"", nd -> data);

    if(nd -> left)
        Print_to_file(nd -> left, file);

    if(nd -> right)
        Print_to_file(nd -> right, file);

    putc(']', file);
}

Node* Create_node(char* new_question)
{
    Node* nd = (Node*) calloc(1, sizeof(Node));

    nd -> data  = new_question;
    nd -> left  = NULL;
    nd -> right = NULL;

    return nd;
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