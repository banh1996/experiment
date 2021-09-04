#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "sys/wait.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main()
{
    char line[100];
    pid_t pid;
    int fd[2];
    int status;
    char* ls_arguments[] = {"ls", "-l", NULL};
    char* tail_arguments[] = {"tail", "-n", "2", NULL};
    pipe(fd);
    pid = fork();
    if(pid == 0)//ls client
    {
        close(1);
        dup(fd[1]);
        close(fd[0]);
        execvp("ls", ls_arguments);
    }
    pid = fork();
    if(pid == 0)//tail client
    {
        close(0);
        close(fd[1]);
        dup(fd[0]);
        execvp("tail", tail_arguments);
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL); // Wait for the first child to finish
    wait(NULL); // Wait fot the second one
}
