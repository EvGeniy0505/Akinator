#include <sys/stat.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "file_read_and_write.h"

struct str_params
{
    char* str;
    size_t len;
};

static str_params read_str_from_buff(char* buff);
static void from_buff_to_tree(Node** nd, char** buff);

Node* read_questions_from_file()
{
    FILE* f_data = fopen("akinator_data.txt", "r");

    assert(f_data);

    Node* nd = Tree_ctor(f_data);

    fclose(f_data);

    return nd;
}

size_t count_symbls(FILE* all_file)
{
    assert(all_file);

    struct stat st;

    fstat(fileno(all_file), &st);

    return (size_t)st.st_size;
}

void from_file_to_tree(FILE* file, Node** nd)
{
    size_t len_file = count_symbls(file);

    char* akinator_data = (char*) calloc(len_file, 1);

    fread(akinator_data, 1, len_file, file);

    char* buff = akinator_data;
    from_buff_to_tree(nd, &buff);

    free(akinator_data);
}

static void from_buff_to_tree(Node** nd, char** buff)
{
    *buff += 2;  // проходим [ + кавычки

    str_params question = read_str_from_buff(*buff);

    *nd = Create_node(question.str);

    *buff += question.len + 1;  // строка плюс кавычки

    // fprintf(stderr, "level = %d\n", a);
    // fprintf(stderr, "nd = %p\n", nd);
    // fprintf(stderr, "%s\n", question.str);
    // fprintf(stderr, "%c\n", **buff);

    if(**buff == '[')
        from_buff_to_tree(&((*nd) -> left), buff);

    if(**buff == '[')
        from_buff_to_tree(&((*nd) -> right), buff);

    if(**buff == ']')
    {
        ++(*buff);
        return;
    }
}

static str_params read_str_from_buff(char* buff)
{
    char* str_ptr = 0;

    str_ptr = strchr(buff, '\"');

    size_t str_len = (str_ptr - buff);

    char* str = (char*) calloc(str_len + 1, 1);

    memcpy(str, buff, str_len);

    return {str, str_len};
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

void write_questions_to_file(Node* nd)
{
    FILE* f_data = fopen("akinator_data.txt", "w");

    assert(f_data);
    assert(nd);
    if(ferror(f_data))
        fprintf(stderr, "FILE OPEN ERROR!!!\n");

    Print_to_file(nd, f_data);

    fclose(f_data);
}
