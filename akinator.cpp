#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <ctype.h>

#include "akinator.h"
#include "file_read_and_write.h"

static const int MAX_STR_LEN = 100;

static void print_solve_path(Node* nd, int* arr, int num_of_nd, int solve_path);
static void print_different_path(Node* nd, int* arr, int num_of_nd, int solve_path);

int game(Node* nd)
{
    printf("Привет, привет, мэнчик!\nХочешь поиграть в акинатор, найти есть ли слово в базе данных или сравнить определения двух слов?\n");
    printf("Введи номер игры:\n1)Поиграть\n2)Найти\n3)Сравнить\n4)Выйти из акинатора\n");
    char user_answ[256] = {};
    user_request(user_answ);

    while((strcasecmp(user_answ, "Выйти") || strcasecmp(user_answ, "4")))
    {
        if(!strcasecmp(user_answ, "Поиграть") || !strcasecmp(user_answ, "1"))
            akinator(nd);
        else if(!strcasecmp(user_answ, "Найти") || !strcasecmp(user_answ, "2"))
        {
            printf("Заебись, теперь введи слово, которое хочешь найти\n");
            user_request(user_answ);
            find_word(nd, user_answ);
        }
        else if(!strcasecmp(user_answ, "Сравнить") || !strcasecmp(user_answ, "3"))
        {
            printf("Введи два слова для сравнения на каждой строке новое, сука!!!!\n");

            char user_word_1[256] = {};
            char user_word_2[256] = {};

            user_request(user_word_1);
            user_request(user_word_2);

            cmp_path_words(nd, user_word_1, user_word_2);
        }
        else
        {
            color_printf(stdout, RED, "До свидания!\n");
            return 1;
        }

        printf("Хочешь еще поразвлекаться со мной?)\nПовторю меню:\n1)Поиграть\n2)Найти\n3)Сравнить\n4)Выйти из акинатора\n");
        user_request(user_answ);
    }

    printf("Пока, пока, дорогой!\n");
    return 0;
}

void akinator(Node* nd)
{
    if(!nd)
        return;

    char user_answer[256] = {};

    if(nd -> left && nd -> right)
    {
        printf("%s?\n", nd -> data);
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

void cmp_path_words(Node* nd, const char* word1, const char* word2)
{
    int* bin_path1 = (int*) calloc(find_tree_deep(nd, 0), sizeof(int));
    int* bin_path2 = (int*) calloc(find_tree_deep(nd, 0), sizeof(int));

    path_to_word path1 = find_def_word_in_tree(nd, word1, bin_path1, 0);
    path_to_word path2 = find_def_word_in_tree(nd, word2, bin_path2, 0);

    int same_position = 0;

    while(bin_path1[same_position] == bin_path2[same_position])
        ++same_position;

    printf("Same path:\n");

    print_solve_path(nd, path1.path, 0, same_position);

    putchar('\n');

    printf("Differrent path for first str:\n");

    print_different_path(nd, path1.path, 0, same_position);

    putchar('\n');

    printf("Differrent path for second str:\n");

    print_different_path(nd, path2.path, 0, same_position);

    putchar('\n');

    free(bin_path1);
    free(bin_path2);
}

static void print_different_path(Node* nd, int* arr, int num_of_nd, int different_path)
{
    if(!nd -> left)
        return;

    if(arr[num_of_nd] == 0)
    {
        if(different_path <= num_of_nd)
            print_def(nd);

        print_different_path(nd -> left, arr, num_of_nd + 1, different_path);
    }
    if(arr[num_of_nd] == 1)
    {
        if(different_path <= num_of_nd)
            print_no_def(nd);

        print_different_path(nd -> right, arr, num_of_nd + 1, different_path);
    }
}

static void print_solve_path(Node* nd, int* arr, int num_of_nd, int solve_path)
{
    if(!nd -> left)
        return;

    if(arr[num_of_nd] == 0)
    {
        if(solve_path > num_of_nd)
            print_def(nd);

        print_solve_path(nd -> left, arr, num_of_nd + 1, solve_path);
    }
    if(arr[num_of_nd] == 1)
    {
        if(solve_path > num_of_nd)
            print_no_def(nd);

        print_solve_path(nd -> right, arr, num_of_nd + 1, solve_path);
    }
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

        printf("Бля, грустно((\nВведи определение загаданного слова БЕЗ СЛОВА НЕТ(НЕ)\n");

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
        print_def(nd);

        print_path(nd -> left, arr, num_of_nd + 1);
    }
    if(arr[num_of_nd] == 1)
    {
        print_no_def(nd);

        print_path(nd -> right, arr, num_of_nd + 1);
    }
}

void print_no_def(Node* nd)
{
    printf("НЕ %s ", nd -> data);
}

void print_def(Node* nd)
{
    printf("%s ", nd -> data);
}