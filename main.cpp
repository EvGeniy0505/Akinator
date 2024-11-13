#include "tree.h"
#include "user_answer.h"
#include "akinator.h"

int main()
{
    Node* nd = read_questions_from_file();

    Print(nd);

    // Node* nd = Create_node("Это человек?");

    // nd -> right = Create_node("Стас Зыкин");
    // nd -> left  = Create_node("Полина Новикова");


    akinator(nd);

    write_questions_to_file(nd);

    Dot_dump(nd, 1);

    Tree_dtor(nd);

    return 0;
}