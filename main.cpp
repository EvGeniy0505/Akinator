#include "tree.h"
#include "user_answer.h"
#include "akinator.h"

int main()
{
    Node* nd = Tree_ctor("Это человек?");

    nd -> right = Create_node("Стас Зыкин");
    nd -> left  = Create_node("Полина Новикова");

    akinator(nd);

    Dot_dump(nd, 1);

    Tree_dtor(nd);

    return 0;
}