#ifndef OTHER_FUNC
#define OTHER_FUNC

#define ARRAY_LENGTH(arr) (sizeof(arr)/sizeof(arr[0]))

enum text_colors
{
    BLACK = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    LIGHT_BLUE,
    WHITE
};

bool check_input_yes(char answer[]);

bool check_input_no(char answer[]);

void user_request(char answer[]);

void normal_question_check(char* user_answer);

int strcasecmp_russ(const char* str_1, const char* str_2);

void color_printf(FILE* stream, int color, const char* format, ...);

#endif