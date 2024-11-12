#include "tree.h"
#include "user_answer.h"
#include "akinator.h"

int main()
{
    Node* nd = Tree_ctor("Это человек?");

    Dot_dump(nd, 1);

    akinator(nd);



    Tree_dtor(nd);

    return 0;
}