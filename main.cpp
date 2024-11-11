#include "tree.h"
#include "user_answer.h"
#include "akinator.h"

int main()
{
    Node* nd = Tree_ctor("Это человек?");

    Print(nd);

    putchar('\n');

    akinator(nd, "Это человек?");



    Tree_dtor(nd);

    return 0;
}