#include "tree.h"
#include "user_answer.h"
#include "akinator.h"
#include "file_read_and_write.h"

int main()
{
    Node* nd = read_questions_from_file();

    // Print(nd);

    akinator(nd);

    write_questions_to_file(nd);

    Dot_dump(nd, 1);

    Tree_dtor(nd);

    return 0;
}