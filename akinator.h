#include "tree.h"
#include "user_answer.h"

struct path_to_word
{
    int* path;
    bool is_there_path;
};

void akinator(Node* nd);

void check_user_word(Node* nd, char* user_answer);

void find_word(Node* nd, const char* word);

void cmp_path_words(Node* nd, const char* word1, const char* word2);

int game(Node* nd);

void print_def(Node* nd);

void print_no_def(Node* nd);

path_to_word find_def_word_in_tree(Node* nd, const char* str, int* arr, int num_of_nd);

void print_path(Node* nd, int* arr, int num_of_nd);
