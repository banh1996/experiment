/*
 * R Jesse Chaney
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "cmd_parse.h"

// Remember how I told you that use of alloca() is
// dangerous? You can trust me. I'm a professional.
// And, if you mention this in class, I'll deny it
// ever happened. What happens in stralloca stays in
// stralloca.
#define stralloca(_R,_S) {(_R) = alloca(strlen(_S) + 1); strcpy(_R,_S);}

// I have this a global so that I don't have to pass it to every
// function where I might want to use it. Yes, I know global variables
// are frowned upon, but there are a couple useful uses for them.
// This is one.
unsigned short isVerbose = 0;

static int _execute_command_lines(cmd_list_t *cmds)
{
    int j, p_trail;
    cmd_t *cmd = cmds->head;

    while (cmd != NULL)
    {
        int fd_output = STDOUT_FILENO, fd_input = STDIN_FILENO, i;
        int *pipes;
        char **args;
        param_t *temp_param = NULL;
        pid_t pid = -1;

        if (cmd != cmds->tail) //if last and jump to parent process
        {
            pipes = alloca(sizeof(int)*2);
            pipe(pipes);
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
                    args[i][strlen(temp_param->param)] = '\0';
                }
                temp_param = temp_param->next;
            }
            args[cmd->param_count+1] = NULL;

            if (cmd == cmds->tail)
            {
                if (cmd->output_dest == REDIRECT_FILE)
                {
                    fd_output = open(cmd->output_file_name, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
                    if(fd_output==-1)
                    {
                        printf("file cannot create.\n");
                        //_exit(1);
                    }
                    else
                    {
                        fd_output = STDOUT_FILENO;
                    }
                }
                else
                {
                    fd_output = STDOUT_FILENO;
                }
            }
            else if (cmd == cmds->head)
            {
                if (cmd->input_src == REDIRECT_FILE)
                {
                    fd_input = open(cmd->input_file_name, O_RDONLY);
                    if(fd_input==-1)
                    {
                        printf("file cannot open.\n");
                        //_exit(1);
                    }
                    else
                    {
                        fd_input = STDIN_FILENO;
                    }
                }
                else
                {
                    fd_input = STDIN_FILENO;
                }
            }

            if (cmd != cmds->tail) //if !last
            {
                if(dup2(pipes[STDOUT_FILENO], fd_output) < 0)
                {
                    perror("dup2 STDOUT_FILENO barf");
                    _exit(1);
                }
                // close(fd_output);
            }
printf("child %d %d\n", cmd->list_location, p_trail);
            if (cmd != cmds->head) //if !first
            {
                if(dup2(p_trail, fd_input) < 0)
                {
                    perror("dup2 STDIN_FILENO barf");
                    _exit(1);
                }
                // close(fd_input);
            }

            close(pipes[STDIN_FILENO]);
            close(pipes[STDOUT_FILENO]);

            if (execvp(cmd->cmd, args) < 0)
            {
                perror("sad panda");
                _exit(3);
            }
        }
        else
        {
            //parent process
            printf("parent %d %d\n", cmd->list_location, p_trail);
            if (cmd != cmds->tail) //if !last
            {
                close(pipes[STDOUT_FILENO]);
                p_trail = pipes[STDIN_FILENO];
                if(dup2(p_trail, pipes[STDIN_FILENO]) < 0)
                {
                    perror("parent barf");
                    _exit(4);
                }
            }

            if (cmd != cmds->head) //if !first
            {
                close(p_trail);
            }
        }
        cmd = cmd->next;
    }
    for (j = 0; j < cmds->count; j++)
        wait(NULL);
    printf("end parent %d\n", p_trail);

    return 0;
}

//int main( int argc, char *argv[] )
int process_user_input_simple(void)
{
    char str[MAX_STR_LEN];
    char *ret_val;
    char *raw_cmd;
    cmd_list_t *cmd_list = NULL;
    int cmd_count = 0;
    char prompt[30];

    // Set up a cool user prompt.
    sprintf(prompt, PROMPT_STR " %s :-) ", getenv("LOGNAME"));
    for ( ; ; ) {
        fputs(prompt, stdout);
        memset(str, 0, MAX_STR_LEN);
        ret_val = fgets(str, MAX_STR_LEN, stdin);

        if (NULL == ret_val) {
            // end of input, a control-D was pressed.
            // Bust out of the input loop and go home.
            break;
        }

        // STOMP on the trailing newline returned from fgets(). I should be
        // more careful about STOMPing on the last character, just in case
        // it is something other than a newline, but I'm being bold and STOMPing.
        str[strlen(str) - 1] = 0;
        if (strlen(str) == 0) {
            // An empty command line.
            // Just jump back to the promt and fgets().
            // Don't start telling me I'm going to get cooties by
            // using continue.
            continue;
        }

        if (strcmp(str, EXIT_CMD) == 0) {
            // Pickup your toys and go home. I just hope there are not
            // any memory leaks.
            break;
        }
        // Basic commands are pipe delimited.
        // This is really for Stage 2.
        raw_cmd = strtok(str, PIPE_DELIM);

        cmd_list = (cmd_list_t *) calloc(1, sizeof(cmd_list_t));

        // This block should probably be put into its own function.
        cmd_count = 0;
        while (raw_cmd != NULL ) {
            cmd_t *cmd = (cmd_t *) calloc(1, sizeof(cmd_t));

            cmd->raw_cmd = strdup(raw_cmd);
            cmd->list_location = cmd_count++;

            if (cmd_list->head == NULL) {
                // An empty list.
                cmd_list->tail = cmd_list->head = cmd;
            }
            else {
                // Make this the last in the list of cmds
                cmd_list->tail->next = cmd;
                cmd_list->tail = cmd;
            }
            cmd_list->count++;

            // Get the next raw command.
            raw_cmd = strtok(NULL, PIPE_DELIM);
        }
        // Now that I have a linked list of the pipe delimited commands,
        // go through each individual command.
        parse_commands(cmd_list);

        // This is a really good place to call a function to exec the
        // the commands just parsed from the user's command line.
        exec_commands(cmd_list);

        // We (that includes you) need to free up all the stuff we just
        // allocated from the heap. That linked list is linked lists looks
        // like it will be nasty to free up, but just follow the memory.
        free_list(cmd_list);
        cmd_list = NULL;
    }

    return(EXIT_SUCCESS);
}

void simple_argv(int argc, char *argv[] )
{
    int opt;

    while ((opt = getopt(argc, argv, "hv")) != -1) {
        switch (opt) {
        case 'h':
            // help
            // Show something helpful
            fprintf(stdout, "You must be out of your Vulcan mind if you think\n"
                    "I'm going to put helpful things in here.\n\n");
            exit(EXIT_SUCCESS);
            break;
        case 'v':
            // verbose option to anything
            // I have this such that I can have -v on the command line multiple
            // time to increase the verbosity of the output.
            isVerbose++;
            if (isVerbose) {
                fprintf(stderr, "verbose: verbose option selected: %d\n"
                        , isVerbose);
            }
            break;
        case '?':
            fprintf(stderr, "*** Unknown option used, ignoring. ***\n");
            break;
        default:
            fprintf(stderr, "*** Oops, something strange happened <%c> ... ignoring ...***\n", opt);
            break;
        }
    }
}

void exec_commands( cmd_list_t *cmds ) 
{
    char s[100];
    pid_t pid = -1;
    cmd_t *cmd = cmds->head;

    if (1 == cmds->count)
    {
        if (!cmd->cmd) {
            // if it is an empty command, bail.
            return;
        }
        if (0 == strcmp(cmd->cmd, CD_CMD)) {
            if (0 == cmd->param_count) {
                // Just a "cd" on the command line without a target directory
                // need to cd to the HOME directory.

                // Is there an environment variable, somewhere, that contains
                // the HOME directory that could be used as an argument to
                // the chdir() fucntion?
                //printf("%s\n", getcwd(s, 100));
                memset(s, 0, sizeof(s));
                sprintf(s, "/home/%s", getenv("LOGNAME"));
                chdir(s);
            }
            else {
                // try and cd to the target directory. It would be good to check
                // for errors here.
                if (0 == chdir(cmd->param_list->param)) {
                    // a happy chdir!  ;-)
                }
                else {
                    printf("No such file or directory\n");
                    // a sad chdir.  :-(
                }
            }
        }
        else if (0 == strcmp(cmd->cmd, PWD_CMD)) {
            char str[MAXPATHLEN];

            // Fetch the current working directory.
            // aka - get country western dancing
            getcwd(str, MAXPATHLEN); 
            printf(" " PWD_CMD ": %s\n", str);
        }
        else if (0 == strcmp(cmd->cmd, ECHO_CMD)) {
            // insert code here
            // insert code here
            // Is that an echo?
            if (cmd->param_list->param[0] == '"')
            {
                /* code */
                memset(s, 0, sizeof(s));
                sprintf(s, "%s", &cmd->param_list->param[1]);
                s[strlen(s) - 1] = '\0';
            }
            else
            {
                sprintf(s, "%s", cmd->param_list->param);
            }
            
            //getenv("PATH");
            if (s[0] == '$')
            {
                printf("%s\n", getenv("PATH"));
            }
            else
            {
                printf("%s\n", s);
            }   
        }
        else {
            //printf("check: 1 %s 2 %s 3 %s count %d\n", cmd->raw_cmd, cmd->cmd, cmd->param_list->param, cmd->param_count);
            // a single command to create and exec
            // if you really do things correctly, you don't need a special
            // for a single command, as distinguished from multiple commands.
            pid = fork();
            if (pid == -1)
            {
                perror("err pid\n");
                exit(1);
            }
            else if (pid == 0)
            {
                //child process
                int fd_output, fd_input, i;
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
                if (cmd->output_dest == REDIRECT_FILE)
                {
                    fd_output = open(cmd->output_file_name, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
                    if(fd_output==-1)
                    {
                        printf("file cannot create.\n");
                        _exit(1);
                    }
                    else
                    {
                        if(dup2(fd_output, STDOUT_FILENO) < 0)
                        {
                            perror("dup2 barf");
                            _exit(1);
                        }
                    }
                    close(fd_output);
                }
                if (cmd->input_src == REDIRECT_FILE)
                {
                    fd_input = open(cmd->input_file_name, O_RDONLY);
                    if(fd_input==-1)
                    {
                        printf("file cannot open.\n");
                        _exit(1);
                    }
                    else
                    {
                        if(dup2(fd_input, STDIN_FILENO) < 0)
                        {
                            perror("dup2 barf");
                            _exit(1);
                        }
                    }
                    close(fd_input);
                }
                execvp(cmd->cmd, args);
                exit(1);
            }
            else
            {
                wait(NULL);
                //parent process
            }
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
            _execute_command_lines(cmds);
        }
        // Other things???
        // More than one command on the command line. Who'da thunk it!
        // This really falls into Stage 2.
    }
}

void free_list(cmd_list_t *cmd_list)
{
    cmd_t *temp_cmd;
    cmd_t *cmd = cmd_list->head;

    // Proof left to the student.
    // You thought I was going to do this for you! HA! You get
    // the enjoyment of doing it for yourself.
    while(cmd != NULL)
    {
        free_cmd(cmd);
        temp_cmd = cmd;
        cmd = cmd->next;
        free(temp_cmd);
    }
    free(cmd_list);
}

void print_list(cmd_list_t *cmd_list)
{
    cmd_t *cmd = cmd_list->head;

    while (NULL != cmd) {
        print_cmd(cmd);
        cmd = cmd->next;
    }
}

void free_cmd (cmd_t *cmd)
{
    // Proof left to the student.
    // Yep, on yer own.
    // I beleive in you.
    param_t *temp_param;
    free(cmd->raw_cmd);
    free(cmd->cmd);
    if (cmd->input_src != REDIRECT_NONE)
        free(cmd->input_file_name);
    if (cmd->output_dest != REDIRECT_NONE)
        free(cmd->output_file_name);
    while(cmd->param_list != NULL)
    {
        free(cmd->param_list->param);
        temp_param = cmd->param_list;
        cmd->param_list = cmd->param_list->next;
        free(temp_param);
    }
}

// Oooooo, this is nice. Show the fully parsed command line in a nice
// asy to read and digest format.
void print_cmd(cmd_t *cmd)
{
    param_t *param = NULL;
    int pcount = 1;

    fprintf(stderr,"raw text: +%s+\n", cmd->raw_cmd);
    fprintf(stderr,"\tbase command: +%s+\n", cmd->cmd);
    fprintf(stderr,"\tparam count: %d\n", cmd->param_count);
    param = cmd->param_list;

    while (NULL != param) {
        fprintf(stderr,"\t\tparam %d: %s\n", pcount, param->param);
        param = param->next;
        pcount++;
    }

    fprintf(stderr,"\tinput source: %s\n"
            , (cmd->input_src == REDIRECT_FILE ? "redirect file" :
               (cmd->input_src == REDIRECT_PIPE ? "redirect pipe" : "redirect none")));
    fprintf(stderr,"\toutput dest:  %s\n"
            , (cmd->output_dest == REDIRECT_FILE ? "redirect file" :
               (cmd->output_dest == REDIRECT_PIPE ? "redirect pipe" : "redirect none")));
    fprintf(stderr,"\tinput file name:  %s\n"
            , (NULL == cmd->input_file_name ? "<na>" : cmd->input_file_name));
    fprintf(stderr,"\toutput file name: %s\n"
            , (NULL == cmd->output_file_name ? "<na>" : cmd->output_file_name));
    fprintf(stderr,"\tlocation in list of commands: %d\n", cmd->list_location);
    fprintf(stderr,"\n");
}


void parse_commands(cmd_list_t *cmd_list)
{
    cmd_t *cmd = cmd_list->head;
    char *arg;
    char *raw;

    while (cmd) {
        // Because I'm going to be calling strtok() on the string, which does
        // alter the string, I want to make a copy of it. That's why I strdup()
        // it.
        // Given that command lines should not be tooooo long, this might
        // be a reasonable place to try out alloca(), to replace the strdup()
        // used below. It would reduce heap fragmentation.
        //raw = strdup(cmd->raw_cmd);

        // Following my comments and trying out alloca() in here. I feel the rush
        // of excitement from the pending doom of alloca(), from a macro even.
        // It's like double exciting.
        stralloca(raw, cmd->raw_cmd);

        arg = strtok(raw, SPACE_DELIM);
        if (NULL == arg) {
            // The way I've done this is like ya'know way UGLY.
            // Please, look away.
            // If the first command from the command line is empty,
            // ignore it and move to the next command.
            // No need free with alloca memory.
            //free(raw);
            cmd = cmd->next;
            // I guess I could put everything below in an else block.
            continue;
        }
        // I put something in here to strip out the single quotes if
        // they are the first/last characters in arg.
        if (arg[0] == '\'') {
            arg++;
        }
        if (arg[strlen(arg) - 1] == '\'') {
            arg[strlen(arg) - 1] = '\0';
        }
        cmd->cmd = strdup(arg);
        // Initialize these to the default values.
        cmd->input_src = REDIRECT_NONE;
        cmd->output_dest = REDIRECT_NONE;

        while ((arg = strtok(NULL, SPACE_DELIM)) != NULL) {
            if (strcmp(arg, REDIR_IN) == 0) {
                // redirect stdin

                // If the input_src is something other than REDIRECT_NONE, then
                // this is an improper command.

                // If this is anything other than the FIRST cmd in the list,
                // then this is an error.

                cmd->input_file_name = strdup(strtok(NULL, SPACE_DELIM));
                cmd->input_src = REDIRECT_FILE;
            }
            else if (strcmp(arg, REDIR_OUT) == 0) {
                // redirect stdout

                // If the output_dest is something other than REDIRECT_NONE, then
                // this is an improper command.

                // If this is anything other than the LAST cmd in the list,
                // then this is an error.

                cmd->output_file_name = strdup(strtok(NULL, SPACE_DELIM));
                cmd->output_dest = REDIRECT_FILE;
            }
            else {
                // add next param
                param_t *param = (param_t *) calloc(1, sizeof(param_t));
                param_t *cparam = cmd->param_list;

                cmd->param_count++;
                // Put something in here to strip out the single quotes if
                // they are the first/last characters in arg.
                if (arg[0] == '\'') {
                    arg++;
                }
                if (arg[strlen(arg) - 1] == '\'') {
                    arg[strlen(arg) - 1] = '\0';
                }
                param->param = strdup(arg);
                if (NULL == cparam) {
                    cmd->param_list = param;
                }
                else {
                    // I should put a tail pointer on this.
                    while (cparam->next != NULL) {
                        cparam = cparam->next;
                    }
                    cparam->next = param;
                }
            }
        }
        // This could overwite some bogus file redirection.
        if (cmd->list_location > 0) {
            cmd->input_src = REDIRECT_PIPE;
        }
        if (cmd->list_location < (cmd_list->count - 1)) {
            cmd->output_dest = REDIRECT_PIPE;
        }

        // No need free with alloca memory.
        //free(raw);
        cmd = cmd->next;
    }

    if (isVerbose > 0) {
        print_list(cmd_list);
    }
}
