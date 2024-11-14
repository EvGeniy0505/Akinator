#include <string.h>
#include <malloc.h>
#include <assert.h>

#include "akinator.h"
#include "file_read_and_write.h"

static const int MAX_STR_LEN = 100;

void game(Node* nd)
{
    printf("Привет, привет, мэнчик!\nХочешь поиграть в акинатор или найти есть ли слово в базе данных?\n");
    printf("Введи ключевое слово:\n1)Поиграть\n2)Найти\n");
    char user_answ[256] = {};
    user_request(user_answ);

    if(!strcasecmp(user_answ, "Поиграть"))
        akinator(nd);
    else if(!strcasecmp(user_answ, "Найти"))
    {
        printf("Заебись, теперь введи слово, которое хочешь найти\n");
        user_request(user_answ);
        find_word(nd, user_answ);
    }
}

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

    write_questions_to_file(nd);

    Dot_dump(nd, 1);
}

void find_word(Node* nd, const char* word)
{
    int* bin_path = (int*) calloc(find_tree_deep(nd, 0), sizeof(int));

    path_to_word path = find_def_word_in_tree(nd, word, bin_path, 0);

    if(!path.is_there_path)
        color_printf(stdout, RED, "У тебя нет прав на это слово, это полный пиздец\n");
    else
    {
        print_path(nd, path.path, 0);
        putchar('\n');
    }

    free(bin_path);
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

path_to_word find_def_word_in_tree(Node* nd, const char* str, int* arr, int num_of_nd)
{
    if(!strcasecmp(str, nd -> data))
    {
        return {arr, true};
    }

    if(nd -> left)
    {
        arr[num_of_nd] = 0;

        path_to_word path = find_def_word_in_tree(nd -> left, str, arr, num_of_nd + 1);

        if(path.is_there_path)
            return {arr, true};
    }
    if(nd -> right)
    {
        arr[num_of_nd] = 1;

        path_to_word path = find_def_word_in_tree(nd -> right, str, arr, num_of_nd + 1);

        if(path.is_there_path)
            return {arr, true};
    }
    return {arr, false};
}

void print_path(Node* nd, int* arr, int num_of_nd)
{
    if(!nd -> left)
        return;

    if(arr[num_of_nd] == 0)
    {
        printf("%s ", nd -> data);

        print_path(nd -> left, arr, num_of_nd + 1);
    }
    if(arr[num_of_nd] == 1)
    {
        printf("Не %s ", nd -> data);

        print_path(nd -> right, arr, num_of_nd + 1);
    }
}