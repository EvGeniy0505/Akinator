#include <stdio.h>
#include <math.h>

#include "user_answer.h"

static bool check_input_yes_or_no(const char* all_strings[], char answer[], size_t quantity_of_strs);

bool check_input_yes(char answer[])
{
    const char* yes_strings[] = {
        "yes",
        "y",
        "да",
        "хочу",
        "сэр да сэр"
    };

    const size_t size_yes_strings = ARRAY_LENGTH(yes_strings);

    return check_input_yes_or_no(yes_strings, answer, size_yes_strings);
}

bool check_input_no(char answer[])
{
    const char* no_strings[] = {
        "no",
        "n",
        "нет",
        "иди нахуй",
        "неа"
    };

    const size_t size_no_strings = ARRAY_LENGTH(no_strings);

    return check_input_yes_or_no(no_strings, answer, size_no_strings);
}

static bool check_input_yes_or_no(const char* all_strings[], char answer[], size_t quantity_of_strs)
{
    for(size_t i = 0; i < quantity_of_strs; i++)
    {
        if(strcasecmp_russ(all_strings[i], answer) == 0)
        {
            return true;
        }
    }
    return false;
}

int strcasecmp_russ(const char* str_1, const char* str_2)
{
    while(((*str_1 == *str_2) || (abs(*str_1 - *str_2) == 32)) && *str_1 && *str_2)
    {
        str_1++;
        str_2++;

        if(*str_2 == '\0' && *str_1 == '\0')
        {
            return 0;
        }
    }

    return *str_1 - *str_2;
}

void user_request(char answer[])
{
    fgets(answer, 256, stdin);

    int i = 0;

    while(answer[i] != '\n' && answer[i] != '\0' && answer[i] != EOF)
    {
        i++;
    }

    if(answer[i] == '\n')
    {
        answer[i] = '\0';
    }
}