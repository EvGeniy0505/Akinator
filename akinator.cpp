#include "akinator.h"

void akinator(Node* nd)
{
    char user_answer[256] = {};

    printf("%s\n", nd -> data);

    user_request(user_answer);
    normal_question_check(user_answer);

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
    normal_question_check(user_answer);

    if(check_input_yes(user_answer))
        color_printf(stdout, PURPLE, "ОАОАОАОА, ЖООООООСКО, да да да??? я крут??? Это ж просто кайфы, что слово совпало\n");
    else
    {
        nd -> right = Create_node(nd -> data);

        printf("Бля, грустно((\nВведи вопрос БЕЗ СЛОВА НЕТ(НЕ), ответом на который является твоё слово\n");
        user_request(user_answer);
        nd -> data = user_answer;

        printf("Введи твоё слово\n");
        user_request(user_answer);
        nd -> left = Create_node(user_answer);

        color_printf(stdout, RED, "Заебись! Теперь ваш вариант есть в базе данных!\n");
    }
}

void read_questions_from_file(Node* nd)
{
    FILE* fp = fopen("akinator.json", "r");

    fscanf(fp, "%s", nd -> data);

    fclose(fp);
}

void write_questions_to_file(Node* nd)
{

}