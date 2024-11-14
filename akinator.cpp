#include <string.h>
#include <malloc.h>
#include <assert.h>

#include "akinator.h"

static const int MAX_STR_LEN = 100;

void akinator(Node* nd)
{
    if(!nd)
        return;

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

        char* user_question = (char*) calloc(MAX_STR_LEN, 1);
        user_request(user_question);
        nd -> data = user_question;

        nd -> right = Create_node(past_user_answer);

        printf("Введи твоё слово\n");
        char* user_word = (char*) calloc(MAX_STR_LEN, 1);
        user_request(user_word);
        nd -> left = Create_node(user_word);

        color_printf(stdout, RED, "Заебись! Теперь ваш вариант есть в базе данных!\n");
    }
}

int i = 0;

bool find_def_word_in_tree(Node* nd, const char* str)
{
    // int arr[256] = {};

    if(!strcasecmp(str, nd -> data))
    {
        // print_path(nd, arr, i);
        printf("str = %s\n", nd -> data);
        return true;
    }

    if(nd -> left)
    {
        // arr[i] = 0;
        // ++i;
        // printf("%d ", arr[i]);
        if(find_def_word_in_tree(nd -> left, str))
        {
            printf("str = %s\n", nd -> data);
            return true;
        }
    }
    if(nd -> right)
    {
        // arr[i] = 1;
        // ++i;
        // printf("%d ", arr[i]);
        if(find_def_word_in_tree(nd -> right, str))
        {
            printf("str = %s\n", nd -> data);
            return true;
        }
    }
    return false;
}

// void print_path(Node* nd, int* arr, int i)
// {
//     printf("%d\n", i);
//     for(int j = 0; j < i; j++)
//     {
//         switch(arr[j + 1])
//         {
//            case 0:
//                 printf("%s\n", nd -> data);
//                 nd -> left = nd;
//             case 1:
//                 printf("%s\n", nd -> data);
//                 nd -> right = nd;
//             default:
//                 printf("хуй\n");


//         }
//     }
// }