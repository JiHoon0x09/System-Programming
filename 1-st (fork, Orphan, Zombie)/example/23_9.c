#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

main()
{
    int pid, child_pid, status;

    /* 첫 번째 자식 프로세스 생성 */
    if ((pid=fork()) == -1) 
       perror("fork failed");
    /* 부모 프로세스 */
    else if (pid != 0) {
       /* 두 번째 자식 프로세스 생성 */
       if ((pid=fork()) == -1)
          perror("fork failed");
       /* 부모 프로세스 */
       else if (pid != 0) {
          /* 아무 자식 프로세스나 종료되기를 기다림.
            여러 자식 프로세스가 있다면 아무 프로세스나 종료되기를 기다림 */
          child_pid = wait(&status);
          printf("child[pid:%d] terminated with code %x\n", child_pid, status);
       /* 두 번째 자식 프로세스 */
       } else {
          printf("run child2[pid:%u]\n", getpid());
          exit(3);
       }
    /* 첫 번째 자식 프로세스 */
    } else {
       printf("run child1[pid:%u]\n", getpid());
       exit(2);
    }
}