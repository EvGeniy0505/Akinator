#include <string.h>
#include <malloc.h>
#include <assert.h>

#include "akinator.h"

void akinator(Node* nd)
{
    if(!nd)     return;

    char user_answer[256] = {};

    if(nd -> left && nd -> right)
    {
        printf("%s\n", nd -> data);
        user_request(user_answer);
        check_answer(user_answer);
    }

    if(check_input_yes(user_answer))
    {
        akinator(nd -> left);
        if(nd -> left == NULL)
        {
            check_user_word(nd, user_answer);
        }
    }
    else
    {
        akinator(nd -> right);
        if(nd -> right == NULL)
        {
            check_user_word(nd, user_answer);
        }
    }
}

void check_user_word(Node* nd, char* user_answer)
{
    printf("%s\n", nd -> data);
    printf("Это то, что ты загадал???\n");

    user_request(user_answer);
    check_answer(user_answer);

    if(check_input_yes(user_answer))
        color_printf(stdout, PURPLE, "ОАОАОАОА, ЖООООООСКО, да да да??? я крут??? Это ж просто кайфы, что слово совпало\n");
    else
    {
        char* past_user_answer = {};
        past_user_answer = nd -> data;

        printf("Бля, грустно((\nВведи вопрос БЕЗ СЛОВА НЕТ(НЕ), ответом на который является твоё слово\n");

        char* user_question = (char*) calloc(100, 1);
        user_request(user_question);
        nd -> data = user_question;

        nd -> right = Create_node(past_user_answer);

        printf("Введи твоё слово\n");
        user_request(user_answer);
        nd -> left = Create_node(user_answer);

        color_printf(stdout, RED, "Заебись! Теперь ваш вариант есть в базе данных!\n");
    }
}

Node* read_questions_from_file()
{
    FILE* f_data = fopen("akinator_data.txt", "r");

    assert(f_data);

    Node* nd = Tree_ctor(f_data);

    fclose(f_data);

    return nd;
}

void write_questions_to_file(Node* nd)
{
    FILE* f_data = fopen("akinator_data.txt", "w");

    assert(f_data);
    assert(nd);
    if(ferror(f_data))
        fprintf(stderr, "FILE OPEN ERROR!!!\n");

    Print_to_file(nd, f_data);

    fclose(f_data);
}