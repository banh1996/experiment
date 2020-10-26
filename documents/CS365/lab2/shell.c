#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "shell.h"

static int _execute_cmd(cmd_list_t *cmds)
{
    int j;
    cmd_t *cmd = cmds->head;
    int *pipes = alloca(sizeof(int*)*2*(cmds->count - 1)); //use alloca to no need free after

    while (cmd != NULL)
    {
        int i, fd_output = STDOUT_FILENO, fd_input = STDIN_FILENO;
        char **args;
        param_t *temp_param = NULL;
        pid_t pid = -1;

        if (cmd != cmds->tail) //if last and jump to parent process
        {
            pipe(pipes + (2*cmd->list_location));
        }
        pid = fork();
        if (pid == 0)
        {
            //child process
            args = alloca(sizeof(char*)*(cmd->param_count+2));
            args[0] = alloca(strlen(cmd->cmd));
            memcpy(args[0], cmd->cmd, strlen(cmd->cmd));
            temp_param = cmd->param_list;

            for (i = 1; i < cmd->param_count+1; i++)
            {
                if (temp_param != NULL)
                {
                    args[i] = alloca(strlen(temp_param->param) + 1);
                    memcpy(args[i], temp_param->param, strlen(temp_param->param));
                    args[i][strlen(temp_param->param)] = '\0'; //set the last character = 0
                }
                temp_param = temp_param->next;
            }
            args[cmd->param_count+1] = NULL;

            if (cmd != cmds->tail) //if not the last cmd list
            {
                if(dup2(pipes[cmd->list_location*2 + STDOUT_FILENO], fd_output) < 0)
                {
                    perror("dup2 pipe out error");
                    _exit(1);
                }
                close(pipes[cmd->list_location*2 + STDIN_FILENO]);
                close(pipes[cmd->list_location*2 + STDOUT_FILENO]);
            }

            if (cmd != cmds->head) //if not the first cmd list
            {
                if(dup2(pipes[cmd->list_location*2 - 2 + STDIN_FILENO], fd_input) < 0)
                {
                    perror("dup2 pipe in error");
                    _exit(1);
                }
                close(pipes[cmd->list_location*2 - 2 + STDIN_FILENO]);
                close(pipes[cmd->list_location*2 - 2 + STDOUT_FILENO]);
            }

            if (execvp(cmd->cmd, args) < 0)
            {
                _exit(3);
            }
        }
        else
        {
            //parent process
            if (cmd != cmds->head) //if not the first cmd list
            {
                close(pipes[cmd->list_location*2 - 2]);
                close(pipes[cmd->list_location*2 - 2 + STDOUT_FILENO]);
            }
        }
        cmd = cmd->next;
    }

    // wait all execute processes done
    for (j = 0; j < cmds->count; j++)
        wait(NULL);

    return 0;
}

/* @brief: function to parse command lines
 */
static void parse_cmd(cmd_list_t *cmd_list)
{
    cmd_t *cmd = cmd_list->head;
    char *arg;
    char *raw;

    while (cmd)
    {
        // use alloca to allocate memory on stack, then no need to free
        raw = alloca(strlen(cmd->raw_cmd) + 1);
        strcpy(raw, cmd->raw_cmd);

        arg = strtok(raw, SPACE_DELIM);
        if (NULL == arg)
        {
            cmd = cmd->next;
            continue;
        }
        if (arg[0] == '\'')
        {
            arg++;
        }
        if (arg[strlen(arg) - 1] == '\'')
        {
            arg[strlen(arg) - 1] = '\0';
        }
        cmd->cmd = strdup(arg);

        while ((arg = strtok(NULL, SPACE_DELIM)) != NULL)
        {
            // add next param
            param_t *param = (param_t *) calloc(1, sizeof(param_t));
            param_t *cparam = cmd->param_list;

            cmd->param_count++;
            // Put something in here to strip out the single quotes if
            // they are the first/last characters in arg.
            if (arg[0] == '\'')
            {
                arg++;
            }
            if (arg[strlen(arg) - 1] == '\'')
            {
                arg[strlen(arg) - 1] = '\0';
            }
            param->param = strdup(arg);
            if (NULL == cparam)
            {
                cmd->param_list = param;
            }
            else
            {
                // should put a tail pointer on this.
                while (cparam->next != NULL)
                {
                    cparam = cparam->next;
                }
                cparam->next = param;
            }
        }

        // No need free with alloca memory.
        cmd = cmd->next;
    }
}

/* @brief: function to execute command lines
 */
static void exec_cmd(cmd_list_t *cmds)
{
    char s[100];
    pid_t pid = -1;
    cmd_t *cmd = cmds->head;

    if (1 == cmds->count)
    {
        // if there's only 1 cmd, then execute without pipe
        if (!cmd->cmd)
        {
            // if it is an empty command, bail.
            return;
        }

        pid = fork();
        if (pid == -1)
        {
            perror("err pid\n");
            exit(1);
        }
        else if (pid == 0)
        {
            //child process
            int i;
            char **args;
            param_t *temp_param = NULL;

            args = alloca(sizeof(char*)*(cmd->param_count+2));
            args[0] = alloca(strlen(cmd->cmd));
            memcpy(args[0], cmd->cmd, strlen(cmd->cmd));
            temp_param = cmd->param_list;

            for (i = 1; i < cmd->param_count+1; i++)
            {
                if (temp_param != NULL)
                {
                    args[i] = alloca(strlen(temp_param->param) + 1);
                    memcpy(args[i], temp_param->param, strlen(temp_param->param));
                    args[i][strlen(temp_param->param)] = '\0';
                }
                temp_param = temp_param->next;
            }
            args[cmd->param_count+1] = NULL;

            execvp(cmd->cmd, args);
            exit(1);
        }
        else
        {
            //parent process
            wait(NULL);
        }
    }
    else
    {
        if (!cmd->cmd)
        {
            // if it is an empty command, bail.
            return;
        }
        else
        {
            // if there are more than 1 cmd, then execute with pipeline
            _execute_cmd(cmds);
        }
    }
}

static void free_cmd(cmd_t *cmd)
{
    param_t *temp_param;
    free(cmd->raw_cmd);
    free(cmd->cmd);
    while(cmd->param_list != NULL)
    {
        free(cmd->param_list->param);
        temp_param = cmd->param_list;
        cmd->param_list = cmd->param_list->next;
        free(temp_param);
    }
}

/* @brief: function to free all created cmd string
 */
static void free_list(cmd_list_t *cmd_list)
{
    cmd_t *temp_cmd;
    cmd_t *cmd = cmd_list->head;

    while(cmd != NULL)
    {
        free_cmd(cmd);
        temp_cmd = cmd;
        cmd = cmd->next;
        free(temp_cmd);
    }
    free(cmd_list);
}

/* @brief: loop function to parse&execute cmd
 */
static int main_process(void)
{
    char str[MAX_STR_LEN];
    char *ret_val;
    char *raw_cmd;
    cmd_list_t *cmd_list = NULL;
    int cmd_count = 0;
    char prompt[30];

    // Set up a prompt.
    sprintf(prompt, PROMPT_STR);
    while(1)
    {
        fputs(prompt, stdout);
        memset(str, 0, MAX_STR_LEN);
        ret_val = fgets(str, MAX_STR_LEN, stdin);

        if (NULL == ret_val)
        {
            // end of input, a control-D was pressed. Then exit
            break;
        }

        str[strlen(str) - 1] = 0;
        if (strlen(str) == 0)
        {
            // An empty command line, nothing to do
            continue;
        }

        if (strcmp(str, EXIT_CMD) == 0)
        {
            // receive exit cmd, then exit
            break;
        }

        raw_cmd = strtok(str, PIPE_DELIM);

        cmd_list = (cmd_list_t *) calloc(1, sizeof(cmd_list_t));

        cmd_count = 0;
        while (raw_cmd != NULL && cmd_list->count < MAX_CMD_NUM)
        {
            cmd_t *cmd = (cmd_t *) calloc(1, sizeof(cmd_t));

            cmd->raw_cmd = strdup(raw_cmd);
            cmd->list_location = cmd_count++;

            if (cmd_list->head == NULL)
            {
                // An empty list.
                cmd_list->tail = cmd_list->head = cmd;
            }
            else
            {
                // Make this the last in the list of cmds
                cmd_list->tail->next = cmd;
                cmd_list->tail = cmd;
            }
            cmd_list->count++;

            // Get the next raw command.
            raw_cmd = strtok(NULL, PIPE_DELIM);
        }

        parse_cmd(cmd_list);
        exec_cmd(cmd_list);
        free_list(cmd_list);
        cmd_list = NULL;
    }

    return(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    int ret = 0;

    ret = main_process();

    return(ret);
}
