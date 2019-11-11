#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSG "hello world\n"
#define MAX_LINE 80

int main(int argc, char **argv)
{
  int n, fd[2];
  pid_t pid;
  char line[MAX_LINE];
  
  if (pipe(fd) < 0) {
    perror("pipe");
    exit(-1);
  }
  if ((pid=fork()) < 0) {
    perror("fork");
    exit(-1);
  } else if (pid > 0) {   // parent
    close(fd[0]);
    write(fd[1], MSG, strlen(MSG));
  } else {    // child
    close(fd[1]);
    n = read(fd[0], line, MAX_LINE);
    line[n]='\0';
    printf("%s", line);
  }
  exit(0);
}
