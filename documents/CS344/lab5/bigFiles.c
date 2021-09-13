#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int opt = 0;
    int pipe1[2] = {-1, -1}, pipe2[2] = {-1, -1}, pipe3[2] = {-1, -1};
    pid_t pid1 = -1, pid2 = -1, pid3 = -1;
    char *count = NULL;

    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
        case 'n':
            count = optarg;
            break;
        default:
            break;
        }
    }

    pipe(pipe1);
    pid1 = fork();
    if (pid1 == 0)
    {
        //child process handle ls
        // close(STDOUT_FILENO);
        if(dup2(pipe1[STDOUT_FILENO],STDOUT_FILENO) < 0)
        {
            perror("child 1 barf");
            _exit(1);
        }
        close(pipe1[STDIN_FILENO]);
        close(pipe1[STDOUT_FILENO]);
        
        if (execlp("ls", "ls", NULL) < 0)
        {
            perror("sad panda 1");
            _exit(3);
        }
    }
    else
    {
        pipe(pipe2);
        pid2 = fork();
        if (pid2 == 0)
        {
            //child process handle xargs
            if(dup2(pipe1[STDIN_FILENO], STDIN_FILENO) < 0)
            {
                perror("child 2-1 barf");
                _exit(1);
            }
            if(dup2(pipe2[STDOUT_FILENO], STDOUT_FILENO) < 0)
            {
                perror("child 2-2 barf");
                _exit(1);
            }
            close(pipe1[STDIN_FILENO]);
            close(pipe1[STDOUT_FILENO]);
            close(pipe2[STDIN_FILENO]);
            close(pipe2[STDOUT_FILENO]);
            if (execlp("xargs", "xargs", "du", "-s", NULL) < 0)
            {
                perror("sad panda 2");
                _exit(3);
            }
        }
        else
        {
            close(pipe1[STDIN_FILENO]);
            close(pipe1[STDOUT_FILENO]);
            pipe(pipe3);
            pid3 = fork();
            if (pid3 == 0)
            {
                //child process handle sort
                if(dup2(pipe2[STDIN_FILENO],STDIN_FILENO) < 0)
                {
                    perror("child 3-1 barf");
                    _exit(1);
                }
                if(dup2(pipe3[STDOUT_FILENO],STDOUT_FILENO) < 0)
                {
                    perror("child 3-2 barf");
                    _exit(1);
                }
                close(pipe2[STDIN_FILENO]);
                close(pipe2[STDOUT_FILENO]);
                close(pipe3[STDIN_FILENO]);
                close(pipe3[STDOUT_FILENO]);
                if (execlp("sort", "sort", "-nr", NULL) < 0)
                {
                    perror("sad panda 3");
                    _exit(3);
                }
            }
            else
            {
                //parent process
                
                close(pipe2[STDIN_FILENO]);
                close(pipe2[STDOUT_FILENO]);

                if(dup2(pipe3[STDIN_FILENO],STDIN_FILENO) < 0)
                {
                    perror("parent barf");
                    _exit(4);
                }
                close(pipe3[STDIN_FILENO]);
                close(pipe3[STDOUT_FILENO]);
                if (count != NULL)
                {
                    if (execlp("head", "head", "-n", count, NULL) < 0)
                    {
                        perror("sad panda 4");
                        _exit(3);
                    }
                }
                else
                {
                    if (execlp("head", "head", NULL) < 0)
                    {
                        perror("sad panda 4");
                        _exit(3);
                    }
                }
            }
        }
    }

    return 0;
}
