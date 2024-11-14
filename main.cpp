#include "tree.h"
#include "user_answer.h"
#include "akinator.h"
#include "file_read_and_write.h"

int main()
{
    Node* nd = read_questions_from_file();

    // akinator(nd);

    if(!find_def_word_in_tree(nd, "Полторашка"))
        color_printf(stdout, RED, "У тебя нет прав на это слово, это полный пиздец\n");

    write_questions_to_file(nd);

    Dot_dump(nd, 1);

    Tree_dtor(nd);

    return 0;
}