#include <stdio.h>
#include <unistd.h>
#define SIZE 4

main()
{
    char *arg[3] = {"abc", "def", "ghi"};
    char buffer[SIZE];
    int pipes[2], i;

    /* 파이프 생성. pipes[0]은 파이프로부터 데이터를 읽어 들일 때 사용하는
      파일 식별자가 되고 pipes[1]은 파이프에 데이터를 쓸 때 사용하는 파일 식별자가 됨 */
    if(pipe(pipes) == -1) {
       perror("pipe failed");
       exit(1);
    }

    for(i=0; i<3; i++) {
       /* 파이프에 arg[i]를 쓰기 */
       write(pipes[1], arg[i], SIZE);
    }
    for(i=0; i<3; i++) {
       /* 파이프로부터 데이터 읽기 */
       read(pipes[0], buffer, SIZE);
       printf("%s\n", buffer);
    }

    exit(0);
}