#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

main()
{
    int pid1, pid2, child_pid, status;

    /* 첫 번째 자식 프로세스 생성 */
    if ((pid1=fork()) == -1)
       perror("fork failed");
    /* 부모 프로세스 */
    else if (pid1 != 0) {
       /* 두 번째 자식 프로세스 생성 */
       if ((pid2=fork()) == -1)
          perror("fork failed");
       /* 부모 프로세스 */
       else if (pid2 != 0) {
          /* pid1 프로세스가 종료되기를 기다림 */
          child_pid = waitpid(pid1, &status, 0);
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