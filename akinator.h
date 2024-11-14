#include "tree.h"
#include "user_answer.h"

void akinator(Node* nd);

void check_user_word(Node* nd, char* user_answer);

bool find_def_word_in_tree(Node* nd, const char* str);

void print_path(Node* nd, int* arr, int i);
