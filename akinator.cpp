#include "akinator.h"

void akinator(Node* nd, char* new_question)
{
    char user_answer[256] = {};

    user_request(user_answer);

    while(!check_input_yes(user_answer) &&
          !check_input_no (user_answer))
    {
        printf("Да заебал, введи нормально ответ, да да, нет нет\n");
        user_request(user_answer);
    }
    if(check_input_yes(user_answer))
    {
        akinator(nd -> left, read_questions_from_file());
        if(nd -> left == NULL)
           nd -> left = (Node*)Create_node(new_question);
    }
    else
    {
        akinator(nd -> right, read_questions_from_file());
        if(nd -> right == NULL)
           nd -> right = (Node*)Create_node(new_question);
    }
}

char* read_questions_from_file()
{
    FILE* fp = fopen("akinator.json", "rw");


}