#include <stdio.h>
#include <unistd.h>
#define SIZE 4

main()
{
    char *arg[3] = {"abc", "def", "ghi"};
    char buffer[SIZE];
    int pipes[2], i;

    /* 파이프 생성 */
    if(pipe(pipes) == -1) {
       perror("pipe failed");
       exit(1);
    }

    /* 자식 프로세스를 생성하고 부모 프로세스는 */
    if(fork()) {
       for(i=0; i<3; i++) {
          /* 파이프에 arg[i]를 쓰기 */
          write(pipes[1], arg[i], SIZE);
          printf("parent process write to pipe: %s\n", arg[i]);
       }
    /* 자식 프로세스는 */
    } else {
       for(i=0; i<3; i++) {
          /* 파이프로부터 읽기 */
          read(pipes[0], buffer, SIZE);
          printf("child process read from pipe: %s\n", buffer);
       }
    }
    exit(0);
}