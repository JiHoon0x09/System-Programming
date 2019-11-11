#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

main()
{
    int pid, status;

    if ((pid=fork()) == -1)
       perror("fork failed");
    /* 부모 프로세스 */
    else if (pid != 0) {
       /* 세 번째 인수를 WNOHANG으로 설정하여 호출하면 부모 프로세스는
         자식 프로세스가 종료되지 않더라도 블록화 되지 않고 다른 일을 실행.
         자식 프로세스가 종료되지 않은 상태에서 waitpid가 반환하는 값은 0 */
      while (waitpid(pid, &status, WNOHANG)==0) {
          printf("still waiting\n");
          sleep(1);
       }
    /* 자식 프로세스 */
    } else {
       printf("run child\n");
       sleep(5);
       exit(0);
    }
}