#include "tree.h"
#include "user_answer.h"


void akinator(Node* nd);

Node* read_questions_from_file();

void write_questions_to_file(Node* nd);

void check_user_word(Node* nd, char* user_answer);