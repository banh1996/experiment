// Simple grepn.  Only supports ^ . * $ operators.
// ashed Abdulla Alyammahi - 780696944
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

char buf[1024];
int match(char*, char*);

void
catn(char *filename)
{
  int fd;
  int n, i = 0, line = 0;

  if((fd = open(filename, 0)) < 0){
    fprintf(2, "grepn: cannot open %s\n", filename);
    exit(1);
  }

  memset(buf, sizeof(buf), 0);
  while((n = read(fd, &buf[i], 1)) > 0) {
    i++;
    if (buf[i-1] == '\n') {
      line++;
      fprintf(1, "%d %s", line, buf);
      i = 0;
      memset(buf, sizeof(buf), 0);
    }
  }
  if(n < 0){
    fprintf(2, "catn: read error\n");
    exit(1);
  }
  close(fd);
}

void
grepn(char *pattern, char *filename)
{
  //cat -n README | grep xv6
  //grepn xv6 README
  int pipe1[2];

  pipe(pipe1);
  if(fork() == 0)
  {
    close(1);
    dup(pipe1[1]);
    close(pipe1[0]);
    memset(buf, sizeof(buf), 0);
    //char *cat_arg[] = {"cat", filename, 0};
    //exec("cat", "-n", cat_arg);
    catn(filename);
    exit(0);
  }

  if(fork() == 0)
  {
    close(0);
    close(pipe1[1]);
    dup(pipe1[0]);
    memset(buf, sizeof(buf), 0);
    char *grep_arg[] = {"grep", pattern, 0};
    exec("grep", grep_arg);
    exit(0);
  }
  close(pipe1[0]);
  close(pipe1[1]);
  wait(0); //Wait for the first child to finish
  wait(0); //Wait fot the second one
}

int
main(int argc, char *argv[])
{
  int i;
  char *pattern;

  if(argc <= 1){
    fprintf(2, "usage: grepn pattern [file ...]\n");
    exit(1);
  }
  pattern = argv[1];

  if(argc <= 2){
    //grepn(pattern, NULL);
    exit(0);
  }

  for(i = 2; i < argc; i++){
    // if((fd = open(argv[i], 0)) < 0){
    //   printf("grepn: cannot open %s\n", argv[i]);
    //   exit(1);
    // }
    grepn(pattern, argv[i]);
    //close(fd);
  }
  exit(0);
}

// Regexp matcher from Kernighan & Pike,
// The Practice of Programming, Chapter 9.

