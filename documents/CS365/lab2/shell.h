#ifndef CMD_PARSE_H
#define CMD_PARSE_H

#define MAX_STR_LEN 1000
#define MAX_CMD_NUM 16

#define EXIT_CMD "exit"

#define PIPE_DELIM  "|"
#define SPACE_DELIM " "

#define PROMPT_STR ">>"

// A list of param_t elements.
typedef struct param_s
{
    char *param;
    struct param_s *next;
} param_t;

// A linked list that has a linked list as a member.
typedef struct cmd_s
{
    char    *raw_cmd;
    char    *cmd;
    int     param_count;
    param_t *param_list;
    int     list_location;
    struct cmd_s *next;
} cmd_t;

typedef struct cmd_list_s
{
    cmd_t *head;
    cmd_t *tail;
    int count;
} cmd_list_t;

#endif // CMD_PARSE_H
