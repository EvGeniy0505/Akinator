#include <malloc.h>
#include <string.h>

#include "tree.h"
#include "user_answer.h"
#include "akinator.h"
#include "file_read_and_write.h"

int main()
{
    Node* nd = read_questions_from_file_to_tree();

    game(nd);

    Tree_dtor(nd);

    return 0;
}